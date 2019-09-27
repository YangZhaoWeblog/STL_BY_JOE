#include "RBtreeNode.c"
#include <stdio.h>

typedef struct RBtree RBtree;
//以下定义了函数指针
typedef _Bool (*Insert_type)
(RBtree* thiz, void *data, node_pointer (*assign)(void*, const void*));

// <返回类型> (*函数指针名)(参数列表)
// typedef <返回类型> (*函数指针名)(参数列表)
// 函数指针名就成为了　一个类型
// eg: 
//typedef void (*LeftRotation_type)(RBtree* const rbtree, node_pointer tmp);
//  LeftRotation_type left_rotation;
//  left_rotation = _left();

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
             node_pointer (*assign)(void*, const void*));
void _delete(const void* const val);
node_pointer root_(const RBtree* const rbtree);


_Bool isEmpty(const RBtree* const thiz);
void reBalance(RBtree* rbtree, node_pointer new_node);
void clear(RBtree* thiz);
void eraseAllNode(node_pointer);

//操作接口
void Init_RBtree(RBtree* rbtree, size_type data_size,
                 KeyCompare_type compare)//其中keycompare 为这个函数指针
{
    rbtree->key_compare = compare;

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

    rbtree->node_count = 0;
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
    if(up == rbtree->Head->prev)
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
    if(up == rbtree->Head->prev)
        up_father->prev = tmp;
    else if(up == up_father->left)
        up_father->left = tmp;
    else
        up_father->right = tmp;

    up->prev = tmp;//tmp to up
    tmp->right    = up;

}

_Bool insert(RBtree* thiz, void *data,
             node_pointer (*assign)(void*, const void*))
{

    node_pointer father = thiz->Head;
    node_pointer pointer = thiz->Head->prev;
    node_pointer new_node =  create_rb_tree_node(data, thiz->data_size);//创建节点

    if(assign != (void*)0)
    {
        //执行自定义的 拷贝复制函数, 为了应对深拷贝与浅拷贝,
        //为完成
        new_node = assign(new_node, data);
        printf("using diy assign copy function");
    }

    while(pointer)//找爸爸
    {
        father = pointer;
        pointer = thiz->key_compare(data, pointer->data)//这里写错了，差点死亡
                  ? (pointer->left) : (pointer->right);
    }//结果必然为 faher 指向爸爸, poiner 指向空
    

    //****************** 插入操作　×××××××××××××××××××
    if(father == thiz->Head)//要插入的节点为唯一的一个节点.
    {
        thiz->Head->prev = new_node;
        thiz->Head->left = new_node;
        thiz->Head->right = new_node;

        thiz->Head->color = RED;
        new_node->color = BLACK;
    }
    else if(data == father->data)
    {
        printf("有重复数据，插入失败");
        return false;
    }
    else if( thiz->key_compare(data, father->data) != 0)// != 0 含义为 != 假
    {
        father->left   =  new_node;
        if(father == thiz->Head->left)//如果父亲最左
            thiz->Head->left = new_node;
    }
    else// key_compare 返回　假
    {
        father->right = new_node;
        if(father == thiz->Head->right)
            thiz->Head->right = new_node;
    }

    new_node->prev  =  father;
    ++(thiz->node_count);

    reBalance(thiz, new_node);//平衡
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
    node_pointer uncle       = 0;

    while(new_node !=  rbtree->Head->prev
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

                    if(new_node != rbtree->Head->prev)
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

                    if(new_node != rbtree->Head->prev)
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

                    if(new_node != rbtree->Head->prev)
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

                    if(new_node != rbtree->Head->prev)
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

    rbtree->Head->prev->color = BLACK;

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


