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
        a.insert(12);
        a.insert(1);
        a.insert(9);
        a.insert(2);
        a.insert(0);
        a.insert(11);
        a.insert(7);
        a.insert(19);
        a.insert(4);
        a.insert(15);
        a.insert(18);
        a.insert(5);
        a.insert(14);
        a.insert(13);
        a.insert(10);
        a.insert(16);
        a.insert(6);
        a.insert(3);
        a.insert(8);
        a.insert(17);
        a.insert(17);
        a.insert(17);


        for(auto i = a.begin(); i != a.end(); ++i)
            cout << *i << ' ';
        cout << endl;

        a.clear();

        for(auto i = a.begin(); i != a.end(); ++i)
            cout << *i << ' ';
        cout << endl;

        set<int, cmp> example;
        example.insert(2);
        example.insert(4);
        example.insert(6);
        example.insert(8);

        auto search = example.find(6);
        if (search != example.end())
        {
            std::cout << "Found " << (*search) << '\n';
        }
        else
        {
            std::cout << "Not found\n";
        }

        cout << example.max_size() << endl;

        cout << example.count(1) << endl;

        example.emplace(10);

        for(auto i = example.begin(); i != example.end(); ++i)
            cout << *i << ' ';
        cout << endl;

        cout << *(example.lower_bound(5)) << endl;

        set<int> one = {30, 20, 70, 60, 90};
        set<int> two;

        two.insert(888);
        two.insert(999);
        two.insert(666);
        two.insert(333);
        two.insert(111);
        two.insert(897);

        for(auto& i : one)
            cout << i <<  ' ';
        cout << endl;

        for(auto& i : two)
            cout << i <<  ' ';
        cout << endl;

        cout << "After swap" << endl;
        one.swap(two);

        for(auto& i : one)
            cout << i <<  ' ';
        cout << endl;

        for(auto& i : two)
            cout << i <<  ' ';
        cout << endl;


        set<int> three = {1, 99999	};
        auto first = one.begin();
        auto last  = one.end();

        three.insert(first, last);
        for(auto& i : three)
            cout << i <<  ' ';
        cout << endl;

    }
}
























