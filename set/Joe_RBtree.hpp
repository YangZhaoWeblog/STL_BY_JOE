// **********************************************************
// Author       : Joe_Yang
// Last modified: 2018-07-22 14:00
// Email        : 1514784049@qq.com || 1514784049yz@gmail.com
// Weblog       : https://blog.csdn.net/pursue_my_life/
// Filename     : Joe_RBtree.hpp
// Description  :
// **********************************************************
//In this container, we will not use nullptr, just use 0. It is so efficenty!!  0 is not only a color type, but also is it a address. via this feature, wo don't have to add another dummy node. We can just use only one dummy node which is contain three pointer to root, mostleft, and mostright.  advise: don't try to use (void*)0 in c++, just use 0, Otherwise you will debug whole of you life. The reason you can google.

#ifndef __Joe_RBtree__
#define __Joe_RBtree__
#include <iostream>
#include <cstddef>
#include <new>
#include "iterator.hpp"
#include "allocator.hpp"
#define debug(); cout<<__LINE__<<endl;
using namespace std;

//RBtree
template<typename key, typename value, typename keyofvalue, typename Compare = std::less<key>, typename  Alloc = Joe::allocator< rb_tree_node<key>  > >
class rb_tree
{
protected:// This is for node;
    using node_type	   = rb_tree_node<value>; //include a node type
    using node_pointer = node_type*;
    using node_reference = node_type&;

public://This is for value, key, key of value...
    using value_type				=    value;
    using reference					=    value_type&;
    using pointer					=    value_type*;
    using const_value_type			=    const value_type;
    using const_pointer             =    const value_type*;
    using const_reference           =    const value_type&;

    using difference_type           =	 ptrdiff_t;
    using size_type                 =	 size_t;
    using key_type					=	 key;
    using iterator					=	 rb_tree_iterator<value_type, reference, node_pointer>;
    using const_iterator			=    const_rb_tree_iterator<value_type, const_reference, node_pointer>;

    using reverse_iterator          =	 reverse_rb_tree_iterator<value_type, reference, node_pointer>;
    using const_reverse_iterator    =	 const_reverse_rb_tree_iterator<value_type, const_reference, node_pointer>;
    using Compared                  =    Compare;
    using allocator_type                 =    Alloc;
protected://This is base stuff of rb_tree
    //Alloc*        allocator;
    node_pointer  Head;
    size_type     node_count;
    Compared      key_compare;

protected://This is assist function
    inline node_pointer creat_node(const_value_type& val=value_type());//apply_memory and construct object
    inline node_pointer clone_node();
    inline void         destroy_node(node_pointer& tmp);
    inline void         __rebalance(node_pointer& new_node);
    inline void         __erase(node_pointer);
    inline void		    right_rotation(node_pointer);
    inline void			left_rotation (node_pointer);

public://This is all for iterator.
    inline void         clear();
    node_pointer&       root()
    {
        return Head->prev;
    }
    iterator erase(iterator position);
    void erase(iterator first, iterator last);

    iterator        begin()
    {
        return iterator(Head->left);
    }
    iterator          end()
    {
        return iterator(Head);
    }
    const_iterator cbegin()
    {
        return const_iterator(Head->left);
    }
    const_iterator   cend()
    {
        return const_iterator(Head);
    }

    reverse_iterator rbegin()
    {
        return reverse_iterator(Head->right);
    }
    reverse_iterator rend()
    {
        return   reverse_iterator(Head);
    };
    const_reverse_iterator crbegin()
    {
        return const_reverse_iterator(Head->right);
    }
    const_reverse_iterator crend()
    {
        return const_reverse_iterator(Head);
    }

public:
    bool      empty()const
    {
        return node_count == 0;
    }
    size_type size()const
    {
        return node_count;
    }
    size_type max_size()const
    {
        return size_type(-1);    //what is mean??
    }
    Compared  key_comp()const
    {
        return key_compare;
    }

    allocator_type  get_allocator()const noexcept
    {
        return new allocator_type;
    }
    const_iterator  lower_bound(const value_type& val)const;
    const_iterator  lower_bound(const value_type& val);
    const_iterator  upper_bound(const value_type& val);
    const_iterator  upper_bound(const value_type& val)const;

public:
    //insert_unique
    inline std::pair<const_iterator, bool>  insert_unique(const_value_type& val);
    inline std::pair<const_iterator,bool>   insert_unique(value_type&& val);
    inline void								insert_unique (const_iterator first, const_iterator last);

    inline const_iterator					insert_unique (const_iterator position, const value_type& val);
    inline const_iterator					insert_unique (const_iterator position, value_type&& val);
    inline void								insert_unique (initializer_list<value_type> il);

    inline std::pair<const_iterator, bool>  emplace_unique(const_value_type& val);

    //insert_equal
    inline iterator                         emplace_equal(const_value_type& val);
    inline iterator                         insert_equal(const_value_type& val);
    inline const_iterator                   find(const_value_type& val);
    void swap(rb_tree& x);

public:
    rb_tree():node_count(0)
    {
        Head        =  creat_node();
        Head->left  =  Head;
        Head->right =  Head;
    }
    rb_tree(std::initializer_list<value_type> il ):rb_tree()
    {
        for(auto i = il.begin(); i != il.end(); ++i)
            insert_equal(*i);
    }

    rb_tree(const rb_tree& x)
    {
        for(auto& i: x)
            insert_equal(i);
    }

    ~rb_tree()
    {
        this->clear();
        destroy_node(Head);
    }
};

template<typename key, typename value, typename keyofvalue, typename Compare, typename  Alloc>
inline	std::pair<typename rb_tree<key, value, keyofvalue, Compare, Alloc>::const_iterator,   bool >//return value_type
rb_tree<key, value, keyofvalue, Compare, Alloc>::insert_unique(const_value_type& val)
{
    node_pointer tmp      = this->Head;
    node_pointer pionner  = this->root();
    node_pointer ptr      = this->creat_node( val);

    while( pionner )
    {
        tmp = pionner;
        pionner = key_compare(val, pionner->date) ? (pionner->left): (pionner->right);
    }

    //insert a node after  tmp;
    if(tmp == Head)
    {
        this->Head->prev  = ptr;
        this->Head->left  = ptr;
        this->Head->right = ptr;

        this->Head->color = color_type::RED;
        ptr->color = color_type::BLACK;
    }
    else if(val == tmp->date)
    {
        return std::pair<const_iterator, bool>( const_iterator(ptr), false);
    }
    else if( key_compare(val, tmp->date) )     //new node be left_child
    {
        tmp->left   =  ptr;
        if(tmp == this->Head->left)
            Head->left = ptr;
    }
    else  							   //new node be right_child
    {
        tmp->right   =   ptr;
        if(tmp == this->Head->right)
            Head->right = ptr;
    }

    ptr->prev  =  tmp;
    ++(this->node_count);

    __rebalance(ptr);
    return std::pair<const_iterator, bool>( const_iterator(ptr), true);
}

template<typename key, typename value, typename keyofvalue, typename Compare, typename  Alloc>
inline	std::pair<typename rb_tree<key, value, keyofvalue, Compare, Alloc>::const_iterator,   bool >//return value_type
rb_tree<key, value, keyofvalue, Compare, Alloc>::insert_unique(value_type&& val)
{
    node_pointer tmp      = this->Head;
    node_pointer pionner  = this->root();
    node_pointer ptr      = this->creat_node( val);

    while( pionner )
    {
        tmp = pionner;
        pionner = key_compare(val, pionner->date) ? (pionner->left): (pionner->right);
    }

    //insert a node after  tmp;
    if(tmp == Head)
    {
        this->Head->prev  = ptr;
        this->Head->left  = ptr;
        this->Head->right = ptr;

        this->Head->color = color_type::RED;
        ptr->color = color_type::BLACK;
    }
    else if(val == tmp->date)
    {
        return std::pair<const_iterator, bool>( const_iterator(ptr), false);
    }
    else if( key_compare(val, tmp->date) )     //new node be left_child
    {
        tmp->left   =  ptr;
        if(tmp == this->Head->left)
            Head->left = ptr;
    }
    else  							   //new node be right_child
    {
        tmp->right   =   ptr;
        if(tmp == this->Head->right)
            Head->right = ptr;
    }

    ptr->prev  =  tmp;
    ++(this->node_count);

    __rebalance(ptr);
    return std::pair<const_iterator, bool>( const_iterator(ptr), true);
}

template<typename key, typename value, typename keyofvalue, typename Compare, typename  Alloc>
inline typename rb_tree<key, value, keyofvalue, Compare, Alloc>::const_iterator
rb_tree<key, value, keyofvalue, Compare, Alloc>::insert_unique(const_iterator position, const value_type& val)
{
    if(this->size() == 0)
    {
        node_pointer ptr = creat_node(val);
        this->Head->prev  = ptr;
        this->Head->left  = ptr;
        this->Head->right = ptr;

        this->Head->color = color_type::RED;
        ptr->color = color_type::BLACK;
        return const_iterator(ptr);
    }
    else if( val <  position && val > --position )
    {
        position.get_ptr()->left = creat_node(val);
        position.get_ptr()->left->prev = position.get_ptr();
        ++(this->node_count);
        __rebalance(position.get_ptr()->left);
        return const_iterator(position.get_ptr()->left);
    }
    else if(val > position && val < ++position)
    {
        position.get_ptr()->right = creat_node(val);
        position.get_ptr()->right = position.get_ptr();
        ++(this->node_count);
        __rebalance(position.get_ptr()->right);
        return const_iterator(position.get_ptr()->right);
    }
    else
    {
        return this->insert_unique(val);
    }
}

template<typename key, typename value, typename keyofvalue, typename Compare, typename  Alloc>
inline typename rb_tree<key, value, keyofvalue, Compare, Alloc>::const_iterator
rb_tree<key, value, keyofvalue, Compare, Alloc>::insert_unique (const_iterator position, value_type&& val)
{
    if(this->size() == 0)
    {
        node_pointer ptr = creat_node(val);
        this->Head->prev  = ptr;
        this->Head->left  = ptr;
        this->Head->right = ptr;

        this->Head->color = color_type::RED;
        ptr->color = color_type::BLACK;
        return const_iterator(ptr);
    }
    else if( val <  position && val > --position )
    {
        position.get_ptr()->left = creat_node(val);
        position.get_ptr()->left->prev = position.get_ptr();
        ++(this->node_count);
        __rebalance(position.get_ptr()->left);
        return const_iterator(position.get_ptr()->left);
    }
    else if(val > position && val < ++position)
    {
        position.get_ptr()->right = creat_node(val);
        position.get_ptr()->right->prev = position.get_ptr();
        ++(this->node_count);
        __rebalance(position.get_ptr()->right);
        return const_iterator(position.get_ptr()->right);
    }
    else
    {
        return this->insert_unique(val);
    }
}



template<typename key, typename value, typename keyofvalue, typename Compare, typename  Alloc>
inline	void rb_tree<key, value, keyofvalue, Compare, Alloc>::insert_unique(const_iterator first, const_iterator last)
{
    for(auto i = first; i != last; ++i)
        this->insert_unique(*i);
}

template<typename key, typename value, typename keyofvalue, typename Compare, typename  Alloc>
inline	void rb_tree<key, value, keyofvalue, Compare, Alloc>::insert_unique(std::initializer_list<value_type> il )
{
    for(auto& i : il)
        this->insert_unique(i);
}



template<typename key, typename value, typename keyofvalue, typename Compare, typename  Alloc>
inline typename rb_tree<key, value, keyofvalue, Compare, Alloc>::node_pointer //return value_type
rb_tree<key, value, keyofvalue, Compare, Alloc>::creat_node(const_value_type& val)
{
    allocator_type allocator;
    node_pointer tmp =  allocator.apply_memory(1);
    allocator.construct_object(tmp, node_type(val));
    return tmp;
}


template<typename key, typename value, typename keyofvalue, typename Compare, typename  Alloc>
void rb_tree<key, value, keyofvalue, Compare, Alloc>::destroy_node(node_pointer& tmp)
{
    allocator_type allocator;
    allocator.deconstruct_object(tmp);
    allocator.recycle_memroy(tmp);
}

template<typename key, typename value, typename keyofvalue, typename Compare, typename  Alloc>
inline	std::pair<typename rb_tree<key, value, keyofvalue, Compare, Alloc>::const_iterator,   bool >//return value_type
rb_tree<key, value, keyofvalue, Compare, Alloc>::emplace_unique(const_value_type& val)
{
    allocator_type        allocator;
    node_pointer tmp      = this->Head;
    node_pointer pionner  = this->root();
    node_pointer ptr      = allocator.apply_memory(1);
    allocator.construct_object(ptr, node_type(val));

    while( pionner )
    {
        tmp = pionner;
        pionner = key_compare(val, pionner->date) ? (pionner->left): (pionner->right);
    }

    //insert a node after  tmp;
    if(tmp == Head)
    {
        this->Head->prev  = ptr;
        this->Head->left  = ptr;
        this->Head->right = ptr;

        this->Head->color = color_type::RED;
        ptr->color = color_type::BLACK;
    }
    else if(val == tmp->date)
    {
        return std::pair<const_iterator, bool>( const_iterator(ptr), false);
    }
    else if( key_compare(val, tmp->date) )     //new node be left_child
    {
        tmp->left   =  ptr;
        if(tmp == this->Head->left)
            Head->left = ptr;
    }
    else  							   //new node be right_child
    {
        tmp->right   =   ptr;
        if(tmp == this->Head->right)
            Head->right = ptr;
    }

    ptr->prev  =  tmp;
    ++(this->node_count);

    __rebalance(ptr);
    return std::pair<const_iterator, bool>( const_iterator(ptr), true);

}

template<typename key, typename value, typename keyofvalue, typename Compare, typename  Alloc>
inline typename rb_tree<key, value, keyofvalue, Compare, Alloc>::iterator //return value_type
rb_tree<key, value, keyofvalue, Compare, Alloc>::insert_equal(const_value_type& val)
{
    node_pointer tmp      = this->Head;
    node_pointer pionner  = this->root();
    node_pointer ptr      = this->creat_node( val);
    //159 162 167
    while( pionner )
    {
        tmp = pionner;
        pionner = key_compare(val, pionner->date) ? (pionner->left): (pionner->right);
    }

    //insert a node after  tmp;
    if(tmp == Head)
    {
        this->Head->prev  = ptr;
        this->Head->left  = ptr;
        this->Head->right = ptr;

        this->Head->color = color_type::RED;
        ptr->color = color_type::BLACK;
    }
    else if( key_compare(val, tmp->date) )     //new node be left_child
    {
        tmp->left   =  ptr;
        if(tmp == this->Head->left)
            Head->left = ptr;
    }
    else  							   //new node be right_child
    {
        tmp->right   =   ptr;
        if(tmp == this->Head->right)
            Head->right = ptr;
    }

    ptr->prev  =  tmp;
    ++(this->node_count);

    __rebalance(ptr );
    return iterator(ptr);
}

template<typename key, typename value, typename keyofvalue, typename Compare, typename  Alloc>
void rb_tree<key, value, keyofvalue, Compare, Alloc>::__rebalance(node_pointer& new_node)
{

    node_pointer grandfather = new_node->prev->prev;
    node_pointer father      = new_node->prev;
    node_pointer uncle       = static_cast<int>(color_type::RED);


    while(new_node != root() &&  father->color == color_type::RED)   //From bottom to top,
    {
        if(father == grandfather->left)   //for duicheng
        {
            uncle = grandfather->right;
            if( uncle && uncle->color == color_type::RED)
            {
                //only this for while
                if(new_node == father->right)
                {
                    left_rotation(new_node);
                    right_rotation(new_node);
                    //just change the color of father
                    father->color = color_type::BLACK;

                    if(new_node != root())
                    {
                        father   = new_node->prev;
                        grandfather = father->prev;
                    }
                    else
                        break;
                }
                else
                {
                    right_rotation(father);
                    //just change the color of new_node
                    new_node->color = color_type::BLACK;

                    new_node = new_node->prev;

                    if(new_node != root())
                    {
                        father   = new_node->prev;
                        grandfather = father->prev;
                    }
                    else
                        break;
                }
                //end of for while
            }
            else if(uncle && uncle->color == color_type::BLACK)     //uncle is BLACK
            {
                if( father->right == new_node)   //new_node is right
                {
                    left_rotation(new_node);//will be  recall father...
                    new_node->color = color_type::BLACK;
                    grandfather->color = color_type::RED;//end of while
                    right_rotation(new_node );
                }
                else     //new_node is left
                {
                    right_rotation(father);
                    //need change father and grandfather color
                    father->color = color_type::BLACK;
                    grandfather->color = color_type::RED;
                }
            }
            else
                break;
        }
        else     //fuicheng
        {
            uncle = grandfather->left;
            if( uncle && uncle->color == color_type::RED)
            {
                //This is for while!!!!
                if(new_node == father->left)
                {
                    right_rotation(new_node);
                    left_rotation(new_node);
                    //just change the color of father
                    father->color = color_type::BLACK;

                    if(new_node != root())
                    {
                        father   = new_node->prev;
                        grandfather = father->prev;
                    }
                    else
                        break;
                }
                else
                {
                    left_rotation(father);
                    //just change the color of new_node
                    new_node->color = color_type::BLACK;

                    new_node = new_node->prev;

                    if(new_node != root())
                    {
                        father   = new_node->prev;
                        grandfather = father->prev;
                    }
                    else
                        break;
                }
                //end of for while!!!!
            }
            else if(uncle && uncle->color == color_type::BLACK)     //uncle is BLACK
            {
                if( father->left == new_node)   //new_node is right
                {
                    right_rotation(new_node);//will be  recall father...
                    new_node->color = color_type::BLACK;
                    grandfather->color = color_type::RED;
                    left_rotation(new_node );
                }
                else     //new_node is left
                {
                    left_rotation(father);
                    //need change father and grandfather color
                    father->color = color_type::BLACK;
                    grandfather->color = color_type::RED;
                }
            }
            else
                break;
        }
    }//end of while

    root()->color = color_type::BLACK;
}

template<typename key, typename value, typename keyofvalue, typename Compare, typename  Alloc>
void rb_tree<key, value, keyofvalue, Compare, Alloc>::right_rotation(node_pointer tmp )
{
    node_pointer up = tmp->prev;
    node_pointer up_father = up->prev;

    if(tmp->right)
    {
        tmp->right->prev = up;
    }

    up->left = tmp->right; //up to tmp's ri_chid

    //tmp to up's father
    tmp->prev = up_father;
    if(up == root())
        up_father->prev = tmp;
    else if(up == up_father->left)
        up_father->left = tmp;
    else
        up_father->right = tmp;

    up->prev = tmp;//tmp to up
    tmp->right    = up;
}

template<typename key, typename value, typename keyofvalue, typename Compare, typename  Alloc>
inline typename rb_tree<key, value, keyofvalue, Compare, Alloc>::const_iterator //return value_type
rb_tree<key, value, keyofvalue, Compare, Alloc>::find(const_value_type& val)
{
    node_pointer tmp = root();
    while(tmp)
    {
        if(val == tmp->date )
        {
            return const_iterator(tmp);
        }
        else if(key_compare(val, tmp->date))
        {
            tmp = tmp->left;
        }
        else
        {
            tmp = tmp->right;
        }
    }
    return const_iterator( Head );
}

template<typename key, typename value, typename keyofvalue, typename Compare, typename  Alloc>
void rb_tree<key, value, keyofvalue, Compare, Alloc>::left_rotation(node_pointer tmp)
{
    node_pointer up = tmp->prev;
    node_pointer up_father = up->prev;

    if(tmp->left)
    {
        tmp->left->prev = up;
    }

    up->right = tmp->left; //up to tmp's ri_chid

    //tmp to up's father
    tmp->prev = up_father;
    if(up == root())
        up_father->prev = tmp;
    else if(up == up_father->left)
        up_father->left = tmp;
    else
        up_father->right = tmp;

    up->prev = tmp;//tmp to up
    tmp->left    = up;
}



template<typename key, typename value, typename keyofvalue, typename Compare, typename  Alloc>
void rb_tree<key, value, keyofvalue, Compare, Alloc>::__erase(node_pointer tmp )
{
    if(tmp->left)
        __erase(tmp->left);
    if(tmp->right)
        __erase(tmp->right);

    destroy_node(tmp);
}

template<typename key, typename value, typename keyofvalue, typename Compare, typename  Alloc>
void rb_tree<key, value, keyofvalue, Compare, Alloc>::clear()
{
    if(node_count != 0)
    {
        __erase(root());
    }

    Head->left  = Head;
    Head->right = Head;
    node_count  = 0;
    root()      = 0;
}

template<typename key, typename value, typename keyofvalue, typename Compare, typename  Alloc>
inline typename rb_tree<key, value, keyofvalue, Compare, Alloc>::const_iterator //return value_type
rb_tree<key, value, keyofvalue, Compare, Alloc>::lower_bound(const value_type& val)const
{
    auto be = cbegin();
    while(key_compare(val, *be) && *be != cend())
        ++be;

    return const_iterator(be);
}

template<typename key, typename value, typename keyofvalue, typename Compare, typename  Alloc>
inline typename rb_tree<key, value, keyofvalue, Compare, Alloc>::const_iterator //return value_type
rb_tree<key, value, keyofvalue, Compare, Alloc>::lower_bound(const value_type& val)
{
    //2 4 6 8 10
    auto be = cbegin();
    while(key_compare(val, *be) && be != cend() && *be != val)
        ++be;

    return const_iterator(be);
}

template<typename key, typename value, typename keyofvalue, typename Compare, typename  Alloc>
inline typename rb_tree<key, value, keyofvalue, Compare, Alloc>::const_iterator //return value_type
rb_tree<key, value, keyofvalue, Compare, Alloc>::upper_bound(const value_type& val)const
{
    auto be = cbegin();
    while(key_compare(val, *be) && be != end() && *be != val)
        ++be;

    return const_iterator(be);
}

template<typename key, typename value, typename keyofvalue, typename Compare, typename  Alloc>
inline typename rb_tree<key, value, keyofvalue, Compare, Alloc>::const_iterator //return value_type
rb_tree<key, value, keyofvalue, Compare, Alloc>::upper_bound(const value_type& val)
{
    auto be = cbegin();
    while(key_compare(val, *be) && be != end())
        ++be;

    return const_iterator(be);
}
#endif // __Joe_RBtree__


template<typename key, typename value, typename keyofvalue, typename Compare, typename  Alloc>
inline void rb_tree<key, value, keyofvalue, Compare, Alloc>::swap(rb_tree& x)
{
    node_pointer tmp = this->creat_node();
    tmp->prev = x.root();
    tmp->left = x.end().get_ptr()->left;
    tmp->right = x.end().get_ptr()->right;
    x.root()->prev = tmp;


    x.end().get_ptr()->prev  = this->end().get_ptr()->prev;
    x.end().get_ptr()->left  = this->end().get_ptr()->left;
    x.end().get_ptr()->right = this->end().get_ptr()->right;
    this->root()->prev   = x.end().get_ptr();

    this->end().get_ptr()->prev  = tmp->prev;
    this->end().get_ptr()->left  = tmp->left;
    this->end().get_ptr()->right = tmp->right;
    tmp->prev->prev    = this->end().get_ptr();
}










