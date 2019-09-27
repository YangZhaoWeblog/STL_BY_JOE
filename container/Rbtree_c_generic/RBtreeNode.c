//头文件保护符
#ifndef __RBTREENODE__//如果为真,继续往下。如果为假，退出文件
#define __RBTREENODE__

#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <memory.h>
#include <malloc.h>
#include <string.h>

//类型解析
enum color_type {RED = 0, BLACK = 1};//C语言中
struct rb_tree_node;//声明 rb_tree_node 类型
typedef struct rb_tree_node rb_tree_node;

typedef  int value_type;    //声明 数据类型(泛型的特化) 为 int
typedef size_t size_type;
typedef struct rb_tree_node* node_pointer;//

//**************************** 定义 节点 **********************************
struct rb_tree_node
{
    node_pointer left;
    node_pointer right;
    node_pointer prev;

    void* data;

    enum color_type color;

};

node_pointer create_rb_tree_node(void* val, size_type data_size)
{
    node_pointer new_node = (node_pointer)malloc(sizeof(rb_tree_node) );
    if(!new_node)
    {
        printf("memory problem");
    }

    //new_node->data = val;
    if(data_size && val)
    {
        new_node->data = malloc(data_size);//分配内存，相当于 operator_new
        memcpy(new_node->data, val, data_size);//复制数据,相当于 placement_new
    }

    new_node->left = 0;
    new_node->right = 0;
    new_node->prev = 0;
    new_node->color = RED;
    return new_node;
}

void destory_rb_tree_node(rb_tree_node* tmp)
{
    free(tmp);
    tmp = (void*)0;
}


//**************************** 定义 迭代器 **********************************
struct iterator;
typedef struct iterator Iterator;
//这里 typedef 的用法: https://blog.csdn.net/qll125596718/article/details/6891881
//形式1：typedef  返回类型(*新类型)(参数表)
//eg: IteratorNext 为这个函数指针的别名
//定义这种类型为 指向某种函数的指针
typedef Iterator (*IteratorNext)(Iterator *thiz);
typedef Iterator (*IteratorPrev)(Iterator *thiz);
typedef void (*IteratorAdvance)(Iterator *thiz, size_t off_set);
typedef void (*IteratorReduce)(Iterator *thiz, size_t off_set);

typedef void (*IteratorBegin)(Iterator *thiz);
typedef void (*IteratorEnd)(Iterator *thiz);

typedef _Bool (*IteratorCompare)(Iterator *x, Iterator y);
typedef void (*IteratorSet)(Iterator *thiz, void* data, size_type data_size);

typedef void* (*IteratorGet)(Iterator* thiz);
typedef void (*IteratorDestroy)(Iterator* thiz);

void init_Iterator(Iterator* thiz);
static inline void* iterator_get_ptr(Iterator *thiz);
static inline void  iterator_set(Iterator *thiz, void* data, size_type data_size);

static inline Iterator iterator_next(Iterator *thiz);
static inline Iterator iterator_prev(Iterator *thiz);
static inline void iterator_advance(Iterator *thiz, size_t off_set);
static inline void iterator_reduce(Iterator *thiz, size_t off_set);
static inline _Bool iterator_compare_equall(Iterator *x, Iterator y);
static inline void* iterator_get_value(Iterator *thiz);

struct iterator
{
    void* ptr;

    //定义了多个函数指针
    IteratorNext next;//下一个
    IteratorPrev prev;//前一个
    IteratorAdvance advance;
    IteratorReduce reduce;
    IteratorCompare compare;
    /*IteratorDestroy destory;*/

    IteratorGet get;//得到 ptr 指针
    IteratorSet set;
    IteratorGet get_value;
};


void init_Iterator(Iterator* thiz)
{
    thiz->ptr = 0;
    thiz->next = iterator_next;
    thiz->prev = iterator_prev;
    thiz->advance = iterator_advance;
    thiz->reduce = iterator_reduce;

    thiz->compare = iterator_compare_equall;

    thiz->get = iterator_get_ptr;
    thiz->get_value = iterator_get_value;
    thiz->set = iterator_set;

    /*thiz->destory = ;*/
}

//extern和static是C语言中的两个修饰符，extern可用于修饰函数或者变量，表示该变量或者函数在其他文件中进行了定义；static也可用于修饰函数或者变量，表示该函数或者变量只能在该文件中使用。可利用它们对数据或者函数进行隐藏或者限制访问权限。
//static 修饰的内联函数，一般情况下不会产生函数本身的代码，而是全部被嵌入在被调用的地方。如果不加static，则表示该函数有可能会被其他编译单元所调用，所以一定会产生函数本身的代码。

static inline Iterator iterator_next(Iterator *thiz)//特化
{
    node_pointer thiz_ptr = (node_pointer)thiz->ptr;
    Iterator tmp;
    init_Iterator(&tmp);



    if(thiz_ptr->prev->prev == thiz_ptr
            && thiz_ptr->color == RED)//if thiz_ptr point to Head /*using end()*/,
    {
        thiz->ptr = thiz_ptr->left;
        tmp.ptr = thiz->ptr;
        return tmp;
    }
    if(thiz_ptr->right == RED )
    {
        node_pointer	father = thiz_ptr->prev;
        if(father->left == thiz_ptr)//if left child
        {
            thiz->ptr = father;
        }
        else//not left child
        {
            while(thiz_ptr == father->right)
            {
                thiz_ptr = father;
                father = father->prev;
            }
            thiz->ptr = father;
        }
    }
    else
    {
        thiz_ptr = thiz_ptr->right;
        while(thiz_ptr->left != RED)
        {
            thiz_ptr = thiz_ptr->left;
        }
        thiz->ptr = thiz_ptr;
    }

    tmp.ptr = thiz->ptr;
    return tmp;
}

static inline Iterator iterator_prev(Iterator *thiz)//特化
{
    node_pointer thiz_ptr = (node_pointer)thiz->ptr;
    Iterator tmp;
    init_Iterator(&tmp);

    if(thiz_ptr->prev->prev == thiz_ptr && thiz_ptr->color == RED)//if thiz_ptr point to Head /*using end()*/,
    {
        thiz->ptr = thiz_ptr->right;
        tmp.ptr = thiz->ptr;
        return tmp;
    }

    if(thiz_ptr->left == RED)
    {
        node_pointer	father = thiz_ptr->prev;
        if(father->right == thiz_ptr)//if left child
        {
            thiz->ptr = father;
        }
        else//not left child
        {
            while(thiz_ptr == father->left)
            {
                thiz_ptr = father;
                father = father->prev;
            }
            thiz->ptr = father;
        }
    }
    else
    {
        thiz_ptr = thiz_ptr->left;
        while(thiz_ptr->right != RED)
        {
            thiz_ptr = thiz_ptr->right;
        }
        thiz->ptr = thiz_ptr->right;
    }

    tmp.ptr = thiz->ptr;
    return tmp;
}

static inline void iterator_advance(Iterator *thiz, size_t off_set)//针对红黑树特化
{
    assert(thiz != (void*)0 && thiz->advance != (void*)0);
    while(off_set--)
    {
        thiz->next(thiz);
    }
    return;
}

static inline void iterator_reduce(Iterator *thiz, size_t off_set)//针对红黑树特化
{
    assert(thiz != (void*)0 && thiz->reduce != (void*)0);
    while(off_set--)
    {
        thiz->prev(thiz);
    }
    return;
}

static inline _Bool iterator_compare_equall(Iterator *x, Iterator y)
{
    return x->get(x) != y.get(&y);
}

static inline void* iterator_get_ptr(Iterator *thiz)//通用
{
    assert(thiz != (void*)0 && thiz->ptr != (void*)0);
    return thiz->ptr;
}

static inline void* iterator_get_value(Iterator *thiz)//通用
{
    return ((node_pointer)thiz->ptr)->data;
}

static inline void iterator_set(Iterator *thiz, void* data, size_type data_size)//通用
{
    assert(thiz != (void*)0 && thiz->ptr != (void*)0);
    if(data)
    {
        node_pointer tmp = (node_pointer)(thiz->ptr);
        memcpy(
            tmp->data,
            data,
            data_size
        );
    }
    thiz->ptr = thiz->get(thiz);//这里发生了隐式类型转换
    return;
}

#endif //__RBTREENODE__

