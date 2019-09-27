#include "Rbtree.c"

//比较函数,必须由用户自己实现
_Bool ccompare(const void* const a, const void* const b)
{
  return *((int*)a) < *((int*)b) ? true : false;
}


int main()
{
    RBtree rbtree;
    int data_size = sizeof(int);

    KeyCompare_type comp = ccompare;

    Init_RBtree(&rbtree, data_size, comp);
    printf("%d\n", rbtree.IsEmpty(&rbtree));

    int a[20] = {
      12, 1, 9, 2, 0, 11, 7, 19, 4, 15, 18, 5, 14, 13, 10, 16, 6, 3, 8, 17,
    };

    printf("数目为:%d\n", rbtree.node_count );
    for(int i = 0; i < 20; ++i)
    {
        printf("%d ", a[i]);
        insert(&rbtree, &a[i], 0);
    }
    putchar('\n');

    for(Iterator i = rbtree.Begin(&rbtree);
            i.compare(&i, rbtree.End(&rbtree) );
            i.next(&i)
       )
    {
        printf("%d ", *(int*)i.get_value(&i) );
    }
    putchar('\n');

    printf("数目为:%d\n", rbtree.node_count );
    Destory_RBtree(&rbtree);
    return 0;
}



