#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

int main()
{
	set<int> a;
    a.insert(3);
    a.insert(2);
    a.insert(7);
    a.insert(4);
    a.insert(2);
    a.insert(6);

	for(auto i = a.rbegin(); i != a.rend(); ++i)
		cout << *i << endl;

}

