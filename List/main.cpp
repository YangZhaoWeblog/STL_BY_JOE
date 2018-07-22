#include <iostream>
#include "Joe_list.hpp"
using namespace std;

int main()
{
	cout << "*************Object a**********************" << endl;
	List<int> a;
	cout <<"empty?? :" <<  a.empty() << endl;
	cout << "size   :" <<  a.size() << endl;

	a.push_back(3);
	a.push_back(4);
	a.push_front(2);
	a.push_front(1);

	cout << "a.front    :" << a.front() << endl;
	cout << "b.bcak    :" << a.back() << endl;

	for(auto i = a.begin(); i != a.end(); ++i )
		cout << *i << ' ';
	cout << endl;

	cout << "a.begin() = 89" << endl;
	cout << "const test" << endl;
	auto i = a.begin();
	*i = 89;

//	cout << "const test" << endl;
//	auto j = a.crbegin();
//	*j = 777;

	cout << "reverse iterator output" << endl;
	for(auto i = a.rbegin(); i != a.rend(); ++i )
		cout << *i << ' '; 
	cout << endl;


	cout << "*************Object b**********************" << endl;
	List<int> b(5, 666);

	for(auto i = b.cbegin(); i != b.cend(); ++i )
		cout << *i << ' ';
	cout << endl;


	cout << "*************Object c**********************" << endl;
	cout << "object C After copy constructer from b" << endl;
	List<int> c(a);
	for(auto i = c.cbegin(); i != c.cend(); ++i )
		cout << *i << ' ';
	cout << endl;

	cout << "After clear  " << endl; c.clear();

	cout << "push_back" << endl;
	c.push_front(5);
	c.push_front(4);
	c.push_front(3);
	c.push_front(2);
	c.push_front(1);

	for(auto i = c.cbegin(); i != c.cend(); ++i )
		cout << *i << ' ';
	cout << endl; 

	c.pop_front();
	c.pop_front();
	c.pop_back();
	c.pop_back();

	for(auto i = c.cbegin(); i != c.cend(); ++i )
		cout << *i << ' '; 
	cout << endl;

	cout << "c.assign(2, 777)" << endl;
	c.assign(2, 777);
	for(auto i = c.cbegin(); i != c.cend(); ++i )
		cout << *i << ' '; 
	cout << endl;

	cout << "c.insert(++c.begin(), 5, 999)" << endl;
	c.insert(++c.begin(), 5, 999);

	for(auto i = c.cbegin(); i != c.cend(); ++i )
		cout << *i << ' ';
	cout << endl;

cout << "c.insert(++c.begin(),++a.begin() , --a.end())" << endl;
	c.insert(++c.begin(), ++a.begin(), --a.end() );

	for(auto i = c.cbegin(); i != c.cend(); ++i )
		cout << *i << ' ';
	cout << endl;

	cout << "c.re_move(999)" << endl;
	c.re_move(999);

	for(auto i = c.cbegin(); i != c.cend(); ++i )
		cout << *i << ' '; 
	cout << endl;

cout << "*************Object d**********************" << endl;

	List<int> d = {1, 1, 2, 3, 5, 8, 13, 21};	

	for(auto i = d.begin(); i != d.end(); ++i)
		cout << *i << ' ';
	cout << endl;

	d.resize(11, 789);

	for(auto i = d.begin(); i != d.end(); ++i)
		cout << *i << ' ';
	cout << endl;

	d.reverse();

	for(auto i = d.begin(); i != d.end(); ++i)
		cout << *i << ' ';
	cout << endl;

		d.unique();

	for(auto i = d.begin()+1; i != d.end(); ++i)
		cout << *i << ' ';
	cout << endl;

		d.emplace_back(666);
		d.emplace_back(777);
		d.emplace_front(111);
		d.emplace_front(222);

	for(auto i = d.begin(); i != d.end(); ++i)
		cout << *i << ' ';
	cout << endl;
cout << "*************Object m, v**********************" << endl;

	List<int> m = {1,    9	};
	List<int> v = {2, 3, 4, 5, 6,7,8};

	m.splice( m.begin()+1, v  );
	
	for(auto i = m.begin(); i != m.end(); ++i)
		cout << *i << ' ';
	cout << endl;

	m.emplace(m.begin(), 999);

	for(auto i = m.begin(); i != m.end(); ++i)
		cout << *i << ' ';
	cout << endl;


	cout << "Object d" << endl;
	for(auto i = d.begin(); i != d.end(); ++i)
		cout << *i << ' ';
	cout << endl;
	cout << "Object m" << endl;
	for(auto i = m.begin(); i != m.end(); ++i)
		cout << *i << ' ';
	cout << endl;

	cout << "m.swap(d)" << endl;
	m.swap(d);

	cout << "Object d" << endl;
	for(auto i = d.begin(); i != d.end(); ++i)
		cout << *i << ' ';
	cout << endl;
	cout << "Object m" << endl;
	for(auto i = m.begin(); i != m.end(); ++i)
		cout << *i << ' ';
	cout << endl;


cout << "*************Object w, e********************" << endl;
	List<int> w = {1,3,5,7,9	};
	List<int> e = {2,4,6,8,10	};
	w.merge(e);
	for(auto i = w.begin(); i != w.end(); ++i)
		cout << *i << ' ';
	cout << endl;


cout << "*************Object so**********************" << endl;
	List<int> so = {-88, 56, 78, 92, 0, 3, 2, 7	};
	so.sort();
	for(auto i = so.begin(); i != so.end(); ++i)
		cout << *i << ' ';
	cout << endl;
	return 0;
}

















