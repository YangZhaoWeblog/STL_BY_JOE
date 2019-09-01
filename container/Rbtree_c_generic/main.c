#include "Rbtree.c"
//比较函数,必须由用户自己实现
_Bool compare(const void* const a, const void* const b)
{
    return (double*)a < (double*)b;
}

int main()
{
    RBtree rbtree;
    int data_size = sizeof(int);

    Init_RBtree(&rbtree, data_size, compare);
    printf("%d\n", rbtree.IsEmpty(&rbtree));

    for(int i = 0; i < 10; ++i)
    {
        insert(&rbtree, &i, 0);
    }


    for(Iterator i = rbtree.Begin(&rbtree);
            i.compare(&i, rbtree.End(&rbtree));
            i.next(&i)
       )
    {
        printf("%d ", *(int*)i.get_value(&i) );
    }
    putchar('\n');

    Destory_RBtree(&rbtree);
    return 0;
}



