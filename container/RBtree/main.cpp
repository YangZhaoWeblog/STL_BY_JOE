#include <iostream>
#include "Joe_RBtree.hpp"
using namespace std;
using namespace Joe;

int main()
{
    //rbtree <key,   value,         keyofvalue,              Compare=std::less<key>,            Alloc=Joe::allocator<rb_tree_node<key>>   >

    //   set <key,   Compare,       Alloc>
    //rbtree <key,   key,           idenity<key>,            Compare=less<key>,                 Alloc=allocator<key>                      >

    //   map <key,   T,			    Compare=less<key>,		 Alloc=allocator<pair<const kry,T>                                            >
    //rbtree <key,   pair<key, T>,  select1st<pair<key,T>>,	 Compare=less<key>,                 Alloc=allocator< pair<const kry,T>        >// T is the true value

    {
        struct cmp
        {
            bool operator()(const int a, const int b)
            {
                return a < b;
            }
        };


//		rb_tree<int, int, int, cmp> a;
//
//		a.insert_equal(3);
//		a.insert_equal(4);
//		a.insert_equal(2);
//		a.insert_equal(7);
//		a.insert_equal(666);
//		a.insert_equal(-1);
//		a.insert_equal(6);
//		a.insert_equal(9);
//
//
//		cout << "now, is iterator show time" << endl;
//
//		for(auto i = a.begin(); i != a.end(); ++i)
//			cout << *i << ' ';
//		cout << endl;
//
//		cout << "test pre++" << endl;
//
//		auto it = a.begin();
//		cout << *(it++) << endl;
//		cout << *it << endl;
//
//		cout << "--    test" << endl;
//		for(auto i = --a.end(); i != --a.begin(); i--)
//			cout << *i << ' ';
//		cout << endl;
//
//
//		cout << "This is deadline******************"<< endl;
//		rb_tree<int, int, int > b = { 3, 2, 7, 4, 2, 789, 2,  2,  0, -77};
//
//
//		for(auto i = b.begin(); i != b.end(); ++i)
//		{
//			cout << *i << ' ';
//		}
//		cout << endl;
//
//		for(auto i = b.rbegin(); i != b.rend(); ++i)
//			cout << *i << ' ';
//		cout << endl;
//
//		for(auto i = --b.rend(); i != --b.rbegin(); --i)
//			cout << *i << ' ';
//		cout << endl;
//
//
//		for(auto i = b.crbegin(); i != b.crend(); ++i)
//		{
//			cout << *i << ' ';
//		}
//		cout << endl;


        cout << "multi test*********" << endl;
        rb_tree<int, int, int > c;

        c.insert_equal(12);
        c.insert_equal(1);
        c.insert_equal(9);
        c.insert_equal(2);
        c.insert_equal(0);
        c.insert_equal(11);
        c.insert_equal(7);
        c.insert_equal(19);
        c.insert_equal(4);
        c.insert_equal(15);
        c.insert_equal(18);
        c.insert_equal(5);
        c.insert_equal(14);
        c.insert_equal(13);
        c.insert_equal(10);
        c.insert_equal(16);
        c.insert_equal(6);
        c.insert_equal(3);
        c.insert_equal(8);
        c.insert_equal(17);


        for(auto& i: c)
            cout << i << ' ';
        cout << endl;
    }
}







