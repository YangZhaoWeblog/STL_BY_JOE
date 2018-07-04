#include <iostream>
#include "Joe_vector.h"
using namespace std;

int main()
{
		  //int ia[5] = {0, 1, 2, 3, 4};
		  //vector<int, Joe::allocator<int> >  iv(ia, ia+5);
		  //vector<int, std::allocator<int> >  iv(ia, ia+5);
		  //首先, vector的两个参数,空间适配器是第二个参数，有默认参数
		  //for(unsigned i = 0; i < iv.size(); ++i)
		  //{
		  // 		 cout << iv[i] << ' ';
		  // 		 cout << endl;
		  //}
		  //构造函数构造一片空间
		  Joe_vector<int> b;
		  cout << "capacity" << ':' << b.capacity() << endl;
		  b.push_back(1);
		  b.push_back(2);
		  b.push_back(3);
		  b.push_back(4);
		  b.push_back(5);
		  b.push_back(6);
		  cout << "capacity" << ':' << b.capacity() << endl;
		  cout << "size" << ':' << b.size() << endl;

		  cout << "正向迭代输出" << endl;
		  for(auto i = b.begin(); i != b.end(); ++i)//正向迭代
					 cout << *i << endl;
		  cout << endl;

		  cout << "front" << ":  " << b.front() << endl;
		  cout << "back" << ":  " << b.back() << endl;
		  cout << endl;

		  cout << "删除尾部三个元素后" << endl;
		  b.pop_back();
		  b.pop_back();
		  b.pop_back();//删除为巴

			
		  cout << "size输出" << endl;
		  for(unsigned i = 0; i != b.size(); ++i)//size输出
					 cout << b[i] << endl;
		  cout << endl;

		  cout << "逆向迭代输出" << endl;
		  for(auto i = b.rbegin(); i != b.rend(); ++i)//反向迭代
					 cout << *i << endl;
		  cout << endl;

			cout << "清空后" << endl;
		  b.clear();//清空

		  cout << "逆向迭代输出" << endl;
		  for(auto i = b.rbegin(); i != b.rend(); ++i)//反向迭代
					 cout << *i << endl;
		  cout << endl;
}


//空间适配器运行完好



