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


		rb_tree<int, int, int, cmp> a;
		
		a.insert_equal(3);
		a.insert_equal(4);
		a.insert_equal(2);
		a.insert_equal(7);
		a.insert_equal(666);
		a.insert_equal(-1);
		a.insert_equal(6);
		a.insert_equal(9);

		auto left = a.begin();
		cout << *left <<  endl;;

		auto head = a.end();
		cout << *head <<  endl;;

		auto rig = a.end();
		cout << rig.get_ptr()->right->date <<  endl;


		cout << "now, is iterator show time" << endl;

		for(auto i = a.begin(); i != a.end(); ++i)
			cout << *i << ' ';
		cout << endl;

		cout << "test pre++" << endl;

		auto it = a.begin();
		cout << *(it++) << endl;
		cout << *it << endl;

		cout << "--    test" << endl;
		for(auto i = --a.end(); i != --a.begin(); i--)
			cout << *i << ' ';
		cout << endl;


		cout << "This is deadline*******************"<< endl;
		rb_tree<int, int, int > b/* = {3, 2, 7, 4, 2, 6, 9, 0, -77}*/;

		b.insert_equal(3);
		b.insert_equal(4);
		b.insert_equal(2);
		b.insert_equal(7);
		b.insert_equal(666);
		b.insert_equal(-1);


		for(auto i = b.rbegin(); i != b.rend(); ++i)
			cout << *i << ' ';
		cout << endl;

		for(auto i = --b.rend(); i != --b.rbegin(); --i)
			cout << *i << ' ';
		cout << endl;

		cout << *(--b.rend()) << endl;
		auto j = --b.rend();
		cout << *(--j) << endl;
		cout << *(----j) << endl;
		cout << *(------j) << endl;
	}
}




























