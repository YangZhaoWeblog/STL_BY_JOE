#include "Joe_list.hpp"

int main()
{
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
		cout << *i << ' '; cout << endl;

	cout << "const test" << endl;
	auto i = a.begin();
	*i = 89;

//	cout << "const test" << endl;
//	auto j = a.crbegin();
//	*j = 777;

	cout << "reverse iterator output" << endl;
	for(auto i = a.rbegin(); i != a.rend(); ++i )
		cout << *i << ' '; cout << endl;

	List<int> b(5, 666);

	for(auto i = b.cbegin(); i != b.cend(); ++i )
		cout << *i << ' '; cout << endl;

	cout << "After copy constructer" << endl;
	List<int> c(a);
	for(auto i = c.cbegin(); i != c.cend(); ++i )
		cout << *i << ' '; cout << endl;

	cout << "After clear  " << endl; c.clear();
	
	c.push_front(5);
	c.push_front(4);
	c.push_front(3);
	c.push_front(2);
	c.push_front(1);

	for(auto i = c.cbegin(); i != c.cend(); ++i )
		cout << *i << ' '; cout << endl; 

	c.pop_front();
	c.pop_front();
	c.pop_back();
	c.pop_back();

	for(auto i = c.cbegin(); i != c.cend(); ++i )
		cout << *i << ' '; cout << endl;

	c.assign(2, 777);
	for(auto i = c.cbegin(); i != c.cend(); ++i )
		cout << *i << ' '; cout << endl;
	
	c.insert(++c.begin(), 5, 999);

	for(auto i = c.cbegin(); i != c.cend(); ++i )
		cout << *i << ' '; cout << endl;

}








