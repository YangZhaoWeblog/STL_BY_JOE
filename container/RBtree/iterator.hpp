#ifndef __ITORATOR__
#define __ITORATOR__

enum class color_type : bool {RED = 0, BLACK = 1};

template<typename value_type>
struct rb_tree_node
{
    using node_pointer = rb_tree_node*;
    node_pointer left;
    node_pointer right;
    node_pointer prev;
    value_type date;
    color_type color;

    rb_tree_node(value_type val = value_type()): left(static_cast<int>(color_type::RED) ),
        right(static_cast<int>(color_type::RED)),
        prev(static_cast<int>(color_type::RED) ),
        date(val), color(color_type::RED) { 	  }
};



template<typename value_type, typename reference, typename node_pointer>
class rb_tree_iterator
{
protected:
    node_pointer ptr;
    void for_plus()
    {
        if(this->ptr->prev->prev == ptr && ptr->color == color_type::RED)//if ptr point to Head /*using end()*/,
        {
            ptr = ptr->left;
            return;
        }
        if(this->ptr->right == (void*)static_cast<int>(color_type::RED) )
        {
            node_pointer	father = ptr->prev;
            if(father->left == ptr)//if left child
            {
                ptr = father;
            }
            else//not left child
            {
                while(ptr == father->right)
                {
                    ptr = father;
                    father = father->prev;
                }
                ptr = father;
            }
        }
        else
        {
            ptr = ptr->right;
            while(ptr->left != (void*)static_cast<int>(color_type::RED))
            {
                ptr = ptr->left;
            }
        }
    }
    void for_minus()
    {
        if(ptr->prev->prev == ptr && ptr->color == color_type::RED)//if ptr point to Head /*using end()*/,
        {
            ptr = ptr->right;
            return;
        }

        if(ptr->left == (void*)static_cast<int>(color_type::RED) )
        {
            node_pointer	father = ptr->prev;
            if(father->right == ptr)//if left child
            {
                ptr = father;
            }
            else//not left child
            {
                while(ptr == father->left)
                {
                    ptr = father;
                    father = father->prev;
                }
                ptr = father;
            }
        }
        else
        {
            ptr = ptr->left;
            while(ptr->right != (void*)static_cast<int>(color_type::RED))
            {
                ptr = ptr->right;
            }
        }

    }

public:
    node_pointer& get_ptr()
    {
        return ptr;
    }
    reference operator*( )const
    {
        return this->ptr->date;
    }
    bool operator==(const rb_tree_iterator& x)const
    {
        return ptr == x.ptr;
    }
    bool operator!=(const rb_tree_iterator& x)const
    {
        return ptr != x.ptr;
    }
    node_pointer operator->()const
    {
        return &(operator*());
    }
    rb_tree_iterator() = default;
    ~rb_tree_iterator() = default;


    rb_tree_iterator(node_pointer& tmp): ptr(tmp) {	}
    rb_tree_iterator(const node_pointer& tmp): ptr(tmp) {	}

    void operator=(const rb_tree_iterator& x)const
    {
        ptr = x.get_ptr();
    }

    rb_tree_iterator operator++()
    {
        this->for_plus();
        return rb_tree_iterator(ptr);
    }

    rb_tree_iterator operator++(int)
    {
        node_pointer tmp = ptr;
        //rb_tree_iterator<int, int &, rb_tree_node<int> *>::for_plus();
        this->for_plus();
        return rb_tree_iterator(tmp);
    }

    rb_tree_iterator operator--()
    {
        this->for_minus();
        return rb_tree_iterator(ptr);
    }

    rb_tree_iterator operator--(int)
    {
        node_pointer tmp = ptr;
        this->for_minus();
        return rb_tree_iterator(tmp);
    }
};

template<typename value_type, typename const_reference, typename node_pointer>
class const_rb_tree_iterator
{
protected:
    node_pointer ptr;
    void for_plus()
    {
        if(ptr->prev->prev == ptr && ptr->color == color_type::RED)//if ptr point to Head /*using end()*/,
        {
            ptr = ptr->left;
            return;
        }
        if(ptr->right == (void*)static_cast<int>(color_type::RED) )
        {
            node_pointer	father = ptr->prev;
            if(father->left == ptr)//if left child
            {
                ptr = father;
            }
            else//not left child
            {
                while(ptr == father->right)
                {
                    ptr = father;
                    father = father->prev;
                }
                ptr = father;
            }
        }
        else
        {
            ptr = ptr->right;
            while(ptr->left != (void*)static_cast<int>(color_type::RED))
            {
                ptr = ptr->left;
            }
        }
    }
    void for_minus()
    {
        if(ptr->prev->prev == ptr && ptr->color == color_type::RED)//if ptr point to Head /*using end()*/,
        {
            ptr = ptr->right;
            return;
        }

        if(ptr->left == (void*)static_cast<int>(color_type::RED) )
        {
            node_pointer	father = ptr->prev;
            if(father->right == ptr)//if left child
            {
                ptr = father;
            }
            else//not left child
            {
                while(ptr == father->left)
                {
                    ptr = father;
                    father = father->prev;
                }
                ptr = father;
            }
        }
        else
        {
            ptr = ptr->left;
            while(ptr->right != (void*)static_cast<int>(color_type::RED))
            {
                ptr = ptr->right;
            }
        }

    }

public:
    node_pointer& get_ptr()
    {
        return ptr;
    }
    const_reference operator*( )const
    {
        return this->ptr->date;
    }
    bool operator==(const const_rb_tree_iterator& x)const
    {
        return ptr == x.ptr;
    }
    bool operator!=(const const_rb_tree_iterator& x)const
    {
        return ptr != x.ptr;
    }
    node_pointer operator->()const
    {
        return &(operator*());
    }
    const_rb_tree_iterator() = default;
    ~const_rb_tree_iterator() = default;

    const_rb_tree_iterator(node_pointer& tmp): ptr(tmp) {	}
    const_rb_tree_iterator(const node_pointer& tmp): ptr(tmp) {	}

    void operator=(const_rb_tree_iterator& x)const
    {
        ptr = x.get_ptr();
    }

    const_rb_tree_iterator operator++()
    {
        this->for_plus();
        return const_rb_tree_iterator(ptr);
    }

    const_rb_tree_iterator operator++(int)
    {
        node_pointer tmp = ptr;
        this->for_plus();
        return const_rb_tree_iterator(tmp);
    }

    const_rb_tree_iterator operator--()
    {
        this->for_minus();
        return const_rb_tree_iterator(ptr);
    }

    const_rb_tree_iterator operator--(int)
    {
        node_pointer tmp = ptr;
        this->for_minus();
        return const_rb_tree_iterator(tmp);
    }

};

template<typename value_type, typename reference, typename node_pointer>
class reverse_rb_tree_iterator
{
protected:
    node_pointer ptr;
    void for_plus()
    {
        if(ptr->prev->prev == ptr && ptr->color == color_type::RED)//if ptr point to Head /*using end()*/,
        {
            ptr = ptr->left;
            return;
        }
        if(ptr->right == (void*)static_cast<int>(color_type::RED) )
        {
            node_pointer	father = ptr->prev;
            if(father->left == ptr)//if left child
            {
                ptr = father;
            }
            else//not left child
            {
                while(ptr == father->right)
                {
                    ptr = father;
                    father = father->prev;
                }
                ptr = father;
            }
        }
        else
        {
            ptr = ptr->right;
            while(ptr->left != (void*)static_cast<int>(color_type::RED))
            {
                ptr = ptr->left;
            }
        }
    }
    void for_minus()
    {
        if(ptr->prev->prev == ptr && ptr->color == color_type::RED)//if ptr point to Head /*using end()*/,
        {
            ptr = ptr->right;
            return;
        }

        if(ptr->left == (void*)static_cast<int>(color_type::RED) )
        {
            node_pointer	father = ptr->prev;
            if(father->right == ptr)//if left child
            {
                ptr = father;
            }
            else//not left child
            {
                while(ptr == father->left)
                {
                    ptr = father;
                    father = father->prev;
                }
                ptr = father;
            }
        }
        else
        {
            ptr = ptr->left;
            while(ptr->right != (void*)static_cast<int>(color_type::RED))
            {
                ptr = ptr->right;
            }
        }

    }

public:
    node_pointer& get_ptr()
    {
        return ptr;
    }
    reference operator*( )const
    {
        return this->ptr->date;
    }
    bool operator==(const reverse_rb_tree_iterator& x)const
    {
        return ptr == x.ptr;
    }
    bool operator!=(const reverse_rb_tree_iterator& x)const
    {
        return ptr != x.ptr;
    }
    node_pointer operator->()const
    {
        return &(operator*());
    }
    reverse_rb_tree_iterator() = default;
    ~reverse_rb_tree_iterator() = default;

    reverse_rb_tree_iterator(node_pointer& tmp): ptr(tmp) {	}
    reverse_rb_tree_iterator(const node_pointer& tmp): ptr(tmp) {	}

    void operator=(const reverse_rb_tree_iterator& x)const
    {
        ptr = x.get_ptr();
    }

    reverse_rb_tree_iterator operator++()
    {
        this->for_minus();
        return reverse_rb_tree_iterator(ptr);
    }

    reverse_rb_tree_iterator operator++(int)
    {
        node_pointer tmp = ptr;
        this->for_minus();
        return reverse_rb_tree_iterator(tmp);
    }

    reverse_rb_tree_iterator operator--()
    {
        this->for_plus();
        return reverse_rb_tree_iterator(ptr);
    }

    reverse_rb_tree_iterator operator--(int)
    {
        node_pointer tmp = ptr;
        this->for_plus();
        return reverse_rb_tree_iterator(tmp);
    }
};

template<typename value_type, typename const_reference, typename node_pointer>
class const_reverse_rb_tree_iterator
{
protected:
    node_pointer ptr;
    void for_plus()
    {
        if(ptr->prev->prev == ptr && ptr->color == color_type::RED)//if ptr point to Head /*using end()*/,
        {
            ptr = ptr->left;
            return;
        }
        if(ptr->right == (void*)static_cast<int>(color_type::RED) )
        {
            node_pointer	father = ptr->prev;
            if(father->left == ptr)//if left child
            {
                ptr = father;
            }
            else//not left child
            {
                while(ptr == father->right)
                {
                    ptr = father;
                    father = father->prev;
                }
                ptr = father;
            }
        }
        else
        {
            ptr = ptr->right;
            while(ptr->left != (void*)static_cast<int>(color_type::RED))
            {
                ptr = ptr->left;
            }
        }
    }
    void for_minus()
    {
        if(ptr->prev->prev == ptr && ptr->color == color_type::RED)//if ptr point to Head /*using end()*/,
        {
            ptr = ptr->right;
            return;
        }

        if(ptr->left == (void*)static_cast<int>(color_type::RED) )
        {
            node_pointer	father = ptr->prev;
            if(father->right == ptr)//if left child
            {
                ptr = father;
            }
            else//not left child
            {
                while(ptr == father->left)
                {
                    ptr = father;
                    father = father->prev;
                }
                ptr = father;
            }
        }
        else
        {
            ptr = ptr->left;
            while(ptr->right != (void*)static_cast<int>(color_type::RED))
            {
                ptr = ptr->right;
            }
        }

    }

public:
    node_pointer& get_ptr()
    {
        return ptr;
    }
    const_reference operator*( )const
    {
        return this->ptr->date;
    }
    bool operator==(const const_reverse_rb_tree_iterator& x)const
    {
        return ptr == x.ptr;
    }
    bool operator!=(const const_reverse_rb_tree_iterator& x)const
    {
        return ptr != x.ptr;
    }
    node_pointer operator->()const
    {
        return &(operator*());
    }
    const_reverse_rb_tree_iterator() = default;
    ~const_reverse_rb_tree_iterator() = default;

    const_reverse_rb_tree_iterator(node_pointer& tmp): ptr(tmp) {	}
    const_reverse_rb_tree_iterator(const node_pointer& tmp): ptr(tmp) {	}

    void operator=(const const_reverse_rb_tree_iterator& x)const
    {
        ptr = x.get_ptr();
    }


    const_reverse_rb_tree_iterator operator++()
    {
        this->for_minus();
        return const_reverse_rb_tree_iterator(ptr);
    }

    const_reverse_rb_tree_iterator operator++(int)
    {
        node_pointer tmp = ptr;
        this->for_minus();
        return const_reverse_rb_tree_iterator(tmp);
    }

    const_reverse_rb_tree_iterator operator--()
    {
        this->for_plus();
        return const_reverse_rb_tree_iterator(ptr);
    }

    const_reverse_rb_tree_iterator operator--(int)
    {
        node_pointer tmp = ptr;
        this->for_plus();
        return const_reverse_rb_tree_iterator(tmp);
    }
};

#endif //__ITORATOR__

