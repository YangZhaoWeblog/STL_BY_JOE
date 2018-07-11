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

	cout << "const test" << endl;
	auto j = a.cbegin();
	*j = 777;

	for(auto i = a.begin(); i != a.end(); ++i )
		cout << *i << ' '; cout << endl;

	for(auto i = a.rbegin(); i != a.rend(); ++i )
		cout << *i << ' '; cout << endl;

	for(auto i = a.cbegin(); i != a.cend(); ++i )
		cout << *i << ' '; cout << endl;

	cout << "size   :" <<  a.size() << endl;
}

