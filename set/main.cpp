#include <iostream>
#include "set.hpp"
using namespace std;
using namespace Joe;

int main()
{
	{
		struct cmp
		{
			bool operator()(const int a, const int b)
			{
				return a < b;
			}
		};
		
		set<int, cmp> a;
		
		a.insert(3);
		a.insert(2);
		a.insert(7);
		a.insert(4);
		a.insert(2);
		a.insert(6);
		a.insert(9);
		a.insert(0);
		a.insert(-777);

		for(auto i = a.begin(); i != a.end(); ++i)
			cout << *i << endl;
	}
}




























