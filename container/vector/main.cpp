//resize()
//reserve()

//copy();
//iterator turn to public
//iterative 指向操作
//+=
//-=
//cend() cbenin()
#include <iostream>
#include "Joe_vector.hpp"
using namespace std;

int main()
{
    //int ia[5] = {0, 1, 2, 3, 4};
    //vector<int, Joe::allocator<int> >  iv(ia, ia+5);
    //vector<int, std::allocator<int> >  iv(ia, ia+5);
    //for(unsigned i = 0; i < iv.size(); ++i)
    //{
    // 		 cout << iv[i] << ' ';
    // 		 cout << endl;
    //}
    Joe_vector<int> b;
    cout << "capacity" << ':' << b.capacity() << endl;
    b.push_back(1);
    cout << "capacity" << ':' << b.capacity() << endl;
    b.push_back(2);
    cout << "capacity" << ':' << b.capacity() << endl;
    b.push_back(3);
    cout << "capacity" << ':' << b.capacity() << endl;
    b.push_back(4);
    b.push_back(5);
    b.push_back(6);
    b.push_back(7);
    b.push_back(8);
    b.push_back(9);


    cout << "capacity" << ':' << b.capacity() << endl;
    cout << "size" << ':' << b.size() << endl;

    cout << "iForward iterative output" << endl;
    for(auto i = b.begin(); i != b.end(); ++i)//正向迭代
        cout << *i << endl;
    cout << endl;

    cout << "After insert a element which positon is 1" << endl;
    auto tmp = b.begin();
    b.insert( tmp, 666);

    for(auto i = b.begin(); i != b.end(); ++i)//正向迭代
        cout << *i << endl;
    cout << endl;

    cout << "After erase a element which positon is 3" << endl;
    auto p = b.begin()+3;
    b.erase( p);

    for(auto i = b.begin(); i != b.end(); ++i)//正向迭代
        cout << *i << endl;
    cout << endl;

    cout << "After erase thre element which range is 3-5" << endl;
    auto pt = b.begin()+2;
    b.erase(pt, pt+2);

    for(auto i = b.begin(); i != b.end(); ++i)//正向迭代
        cout << *i << endl;

    cout << endl;
    cout << "front" << ":  " << b.front() << endl;
    cout << "back" << ":  " << b.back() << endl;
    cout << endl;

    cout << "Delete the last three elements" << endl;
    b.pop_back();
    b.pop_back();
    b.pop_back();


    cout << "on size" << endl;
    for(unsigned i = 0; i != b.size(); ++i)
        cout << b[i] << ' ';
    cout << endl;

    cout << "Reverse iterative output" << endl;
    for(auto i = b.rbegin(); i != b.rend(); i++)
        cout << *i << ' ';
    cout << endl;

    cout << "clear" << endl;
    b.clear();

    cout << "Reverse iterative output" << endl;
    for(auto i = b.rbegin(); i != b.rend(); ++i)
        cout << *i << ' ';
    cout << endl;

    cout << "This is the a object" << endl;
    Joe_vector<int> a(5, 666);
    cout << "Reverse iterative output" << endl;
    for(auto i = a.rbegin(); i != a.rend(); ++i)
        cout << *i << ' ';
    cout << endl;


    cout << "This is the c object" << endl;

    Joe_vector<int> c(a);
    cout << "along iterative output" << endl;
    for(auto i = c.begin(); i != c.end(); ++i)
        cout << *i << ' ';
    cout << endl;

    //cout << "test cbegin and crbegin" << endl;
    //auto t = b.cbegin();
    //cout << *t << endl;
    //*t = 99;
    //cout << *t << endl;

    cout << "Before shift to fit len:" <<  a.capacity() << endl;
    a.shift_to_fit();
    cout << "After shift to fit  len:" <<  a.capacity() << endl;

    cout << "Before reserve:" <<  a.capacity() << endl;
    a.reserve(50);
    cout << "After reserve:" <<  a.capacity() << endl;
    cout << endl;

    cout << "Before resize:" <<  a.capacity() << endl;
    c.resize(50);
    for(auto i = c.begin(); i != c.end(); ++i)
        cout << *i << ' ';
    cout << endl;
    cout << "After resize:" <<  a.capacity() << endl;

}





