#include "RBtreeNode.c"
#include "RBtreeNode.c"

typedef struct RBtree RBtree;
//以下定义了函数指针
typedef _Bool (*Insert_type)
(RBtree* thiz, void *data, void (*assign)(void*, const void*));

typedef void (*LeftRotation_type)(RBtree* const rbtree, node_pointer tmp);
typedef void (*RightRotation_type)(RBtree* const rbtree, node_pointer tmp);
typedef Iterator (*Begin_type)(RBtree* const rbtree);
typedef Iterator (*End_type)(RBtree* const rbtree);
typedef node_pointer (*Parameter_only_rbtree_type)(const RBtree* const thiz);

typedef _Bool (*KeyCompare_type)(const void* const a, const void* const b);
typedef _Bool (*IsEmpty_type)(const RBtree* const thiz);
typedef void (*ReBalance_type)(RBtree* rbtree, node_pointer new_node);
typedef void (*Clear_type)(RBtree* thiz);
typedef void (*EraseAllNode_type)(node_pointer thiz);

struct RBtree
{
    node_pointer Head;
    size_type  node_count;
    size_type  data_size;
//Compared      key_compare;

    //function
    Begin_type Begin;
    Begin_type End;
    Begin_type rBegin;
    Begin_type rEnd;
    Insert_type Insert;
    LeftRotation_type  _LeftRotation;
    RightRotation_type _RightRotation;
    Parameter_only_rbtree_type root; 
    KeyCompare_type key_compare;
    IsEmpty_type IsEmpty;
    ReBalance_type ReBalance;
    EraseAllNode_type _EraseAllNode;
    Clear_type clear;
};

//这两个函数不被用作模拟面向对象的方式, 因为必须要用 至少一个函数 来绑定 函数指针与 函数
void Init_RBtree(RBtree* rbtree, size_type data_size,
                 _Bool (*KeyCompare_type)(const void* const a, const void* const b));//其中keycompare 为这个函数指针

void Destory_RBtree(RBtree* rbtree);

//以下定义了要被函数指针指向的 函数
Iterator begin_(RBtree* const rbtree);
Iterator end_(RBtree* const rbtree);

Iterator rbegin_(RBtree* const rbtree);
Iterator rend_(RBtree* const rbtree);

void left_rotation(RBtree* const rbtree, node_pointer tmp);
void right_rotation(RBtree* const rbtree, node_pointer tmp);
_Bool insert(RBtree* thiz, void *data,
             void (*assign)(void*, const void*));
void _delete(const void* const val);
node_pointer root_(const RBtree* const rbtree);


_Bool isEmpty(const RBtree* const thiz);
void reBalance(RBtree* rbtree, node_pointer new_node);
void clear(RBtree* thiz);
void eraseAllNode(node_pointer);

//操作接口

void Init_RBtree(RBtree* rbtree, size_type data_size,
                 _Bool (*KeyCompare_func)(const void* const a, const void* const b))//其中keycompare 为这个函数指针
{
    rbtree->key_compare = KeyCompare_func;

    rbtree->Head = create_rb_tree_node(0, data_size);
    rbtree->Head->left = rbtree->Head;
    rbtree->Head->right = rbtree->Head;

    //function
    rbtree->Begin = begin_;
    rbtree->End = end_;
    rbtree->rBegin = rbegin_;
    rbtree->rEnd = rend_;
    rbtree->root = root_;

    rbtree->Insert = insert;
    rbtree->_LeftRotation = left_rotation;
    rbtree->_RightRotation = right_rotation;
    rbtree->IsEmpty = isEmpty;
    rbtree->ReBalance = reBalance;
    rbtree->_EraseAllNode = eraseAllNode;
    rbtree->clear = clear;
    rbtree->data_size = data_size;
}

node_pointer root_(const RBtree* const rbtree)
{
    return rbtree->Head->prev;
}


Iterator begin_(RBtree* const rbtree)
{
    Iterator tmp;
    init_Iterator(&tmp);
    tmp.ptr = rbtree->Head->left;

    return tmp;
}

Iterator end_(RBtree* const rbtree)
{
    Iterator tmp;
    init_Iterator(&tmp);
    tmp.ptr = rbtree->Head;

    return tmp;
}

Iterator rbegin_(RBtree* const rbtree)
{
    Iterator tmp;
    init_Iterator(&tmp);
    tmp.ptr = rbtree->Head->right;

    return tmp;
}

Iterator rend_(RBtree* const rbtree)
{
    Iterator tmp;
    init_Iterator(&tmp);
    tmp.ptr = rbtree->Head;

    return tmp;
}

void left_rotation(RBtree* const rbtree, node_pointer tmp)
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
    if(up == rbtree->root(rbtree))
    {
        up_father->prev = tmp;
    }
    else if(up == up_father->left)
        up_father->left = tmp;
    else
        up_father->right = tmp;

    up->prev = tmp;//tmp to up
    tmp->left    = up;


}

void right_rotation(RBtree* const rbtree, node_pointer tmp)
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
    if(up == rbtree->root(rbtree))
        up_father->prev = tmp;
    else if(up == up_father->left)
        up_father->left = tmp;
    else
        up_father->right = tmp;

    up->prev = tmp;//tmp to up
    tmp->right    = up;

}

_Bool insert(RBtree* thiz, void *data,
             void (*assign)(void*, const void*))
{
    node_pointer tmp = thiz->Head;
    node_pointer pointer = thiz->root(thiz);

    node_pointer ptr =  create_rb_tree_node(data, thiz->data_size);//创建节点

    if(assign)
    {
        //执行自定义的 拷贝复制函数, 为了应对深拷贝与浅拷贝,
        //为完成
        assign(ptr->data, data);
        return true;
    }

    while(pointer)
    {
        tmp = pointer;
        pointer = thiz->key_compare(&data, &(pointer->data))
                  ? (pointer->left) : (pointer->right);
    }

    if(tmp == thiz->Head)
    {
        thiz->Head->prev = ptr;
        thiz->Head->left = ptr;
        thiz->Head->right = ptr;

        thiz->Head->color = RED;
        ptr->color = BLACK;
    }
    else if(data == tmp->data)
    {
        printf("有重复数据，插入失败");
        return false;
    }
    else if( thiz->key_compare(&data, &(tmp->data)))
    {
        tmp->left   =  ptr;
        if(tmp == thiz->Head->left)
            thiz->Head->left = ptr;
    }
    else
    {
        tmp->right = ptr;
        if(tmp == thiz->Head->right)
            thiz->Head->right = ptr;
    }

    ptr->prev  =  tmp;
    ++(thiz->node_count);

    reBalance(thiz, ptr);
    return true;
}

void _delete(const void* const val)
{

}

_Bool isEmpty(const RBtree* const thiz)
{
    return thiz->node_count == 0;
}

void reBalance(RBtree* rbtree, node_pointer new_node)
{
    node_pointer grandfather = new_node->prev->prev;
    node_pointer father      = new_node->prev;
    node_pointer uncle       = (void*)RED;

    while(new_node !=  rbtree->root(rbtree)
            &&  father->color == RED)   //From bottom to top,
    {
        if(father == grandfather->left)   //for duicheng
        {
            uncle = grandfather->right;
            if( uncle && uncle->color == RED)
            {
                //only this for while
                if(new_node == father->right)
                {
                    left_rotation(rbtree, new_node);
                    right_rotation(rbtree, new_node);
                    //just change the color of father
                    father->color = BLACK;

                    if(new_node != rbtree->root(rbtree))
                    {
                        father   = new_node->prev;
                        grandfather = father->prev;
                    }
                    else
                        break;
                }
                else
                {
                    right_rotation(rbtree, father);
                    //just change the color of new_node
                    new_node->color = BLACK;

                    new_node = new_node->prev;

                    if(new_node != rbtree->root(rbtree))
                    {
                        father   = new_node->prev;
                        grandfather = father->prev;
                    }
                    else
                        break;
                }
                //end of for while
            }
            else if(uncle && uncle->color == BLACK)     //uncle is BLACK
            {
                if( father->right == new_node)   //new_node is right
                {
                    left_rotation(rbtree, new_node);//will be  recall father...
                    new_node->color = BLACK;
                    grandfather->color = RED;//end of while
                    right_rotation(rbtree, new_node );
                }
                else     //new_node is left
                {
                    right_rotation(rbtree, father);
                    //need change father and grandfather color
                    father->color = BLACK;
                    grandfather->color = RED;
                }
            }
            else
                break;
        }
        else     //fuicheng
        {
            uncle = grandfather->left;
            if( uncle && uncle->color == RED)
            {
                //This is for while!!!!
                if(new_node == father->left)
                {
                    right_rotation(rbtree, new_node);
                    left_rotation(rbtree, new_node);
                    //just change the color of father
                    father->color = BLACK;

                    if(new_node != rbtree->root(rbtree))
                    {
                        father   = new_node->prev;
                        grandfather = father->prev;
                    }
                    else
                        break;
                }
                else
                {
                    left_rotation(rbtree, father);
                    //just change the color of new_node
                    new_node->color = BLACK;

                    new_node = new_node->prev;

                    if(new_node != rbtree->root(rbtree))
                    {
                        father   = new_node->prev;
                        grandfather = father->prev;
                    }
                    else
                        break;
                }
                //end of for while!!!!
            }
            else if(uncle && uncle->color == BLACK)     //uncle is BLACK
            {
                if( father->left == new_node)   //new_node is right
                {
                    right_rotation(rbtree, new_node);//will be  recall father...
                    new_node->color = BLACK;
                    grandfather->color = RED;
                    left_rotation(rbtree, new_node );
                }
                else     //new_node is left
                {
                    left_rotation(rbtree, father);
                    //need change father and grandfather color
                    father->color = BLACK;
                    grandfather->color = RED;
                }
            }
            else
                break;
        }
    }//end of while

    rbtree->root(rbtree)->color = BLACK;

}

void clear(RBtree* thiz)
{
    if(thiz->node_count != 0)
    {
        eraseAllNode(thiz->root(thiz));
    }

    thiz->Head->left  = thiz->Head;
    thiz->Head->right = thiz->Head;
    thiz->node_count  = 0;

    thiz->Head->prev = 0;
}

void eraseAllNode(node_pointer tmp)
{
    if(tmp->left)
        eraseAllNode(tmp->left);
    if(tmp->right)
        eraseAllNode(tmp->right);

    destory_rb_tree_node(tmp);
}


void Destory_RBtree(RBtree* thiz)
{
    thiz->clear(thiz);
    destory_rb_tree_node(thiz->Head);
}


