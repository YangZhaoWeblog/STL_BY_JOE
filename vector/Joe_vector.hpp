#ifndef __JOE_VECTOR__
#define __JOE_VECTOR__

#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <new>
#include <climits>
#define debug(); cout<<"__LINE__"<<666666<<endl;
using namespace std;
const int default_kuo = 2;//默认扩展倍数


	template<typename it>
inline void destory(it* p)
{
	p->~it();           
}

	template<typename it>
inline void destory(it* first, it* last)
{
	for(auto i = first; i != last; ++i)
		destory(i);
}

	template<typename it, typename T>
inline void contruct(it& finish, T value)
{
	new(finish) T(value);		      
}

	template<typename it, typename T>
inline void apply_memory(it& start, it& finish, it& end_of_storage ,T x)
{
	ptrdiff_t cha = finish-start;
	it new_start = 0;
	if(cha == 0)
	{

		new_start= (it)(::operator new(sizeof(T)*default_kuo));
		finish = start = new_start;
		end_of_storage = start + default_kuo;
		contruct(finish, x);
		++finish;
	}
	else
	{
		new_start= (it)(::operator new(sizeof(T)*default_kuo*cha));
		memmove(new_start, start, sizeof(T)*cha);
		delete [] start;
		start = new_start;
		finish = start+ cha;
		end_of_storage = start + cha*default_kuo;
		contruct(finish, x);
		++finish;
	}

}


template<typename T >
class Joe_vector
{
	public:
		typedef T 						value_type;
		typedef const T					const_value_type;
		typedef value_type* 			pointer;
		typedef const value_type*		const_pointer;
		typedef value_type* 			iterator;
		typedef value_type& 			refrence;	
		typedef size_t					size_type;	
		typedef ptrdiff_t				difference_type;
	protected:
		iterator start;
		iterator finish;
		iterator end_of_storage;
		class reverse_iterator
		{
			private:
				iterator ptr; 
			public:
				bool  operator!=(const reverse_iterator& it)const{return ptr != it.ptr; }
				bool  operator==(const reverse_iterator& it)const{return ptr == it.ptr; }
				refrence  operator*(){return *ptr; }

				reverse_iterator operator++(){			return --ptr; }
				reverse_iterator operator--(){        return ++ptr; }

				const reverse_iterator operator++(int){iterator tmp = ptr;	--ptr;	return tmp; }
				const reverse_iterator operator--(int){iterator tmp = ptr;	++ptr;	return tmp; }

				reverse_iterator operator+(size_type& diff){	return ptr-diff; }
				reverse_iterator operator-(size_type& diff){	return ptr+diff; }

				reverse_iterator(iterator p = nullptr) : ptr(p) {}
		};



	public:
		Joe_vector():start(nullptr),finish(nullptr),end_of_storage(nullptr){ }
		Joe_vector(size_type n, const_value_type value);//范围定值初始化
		Joe_vector(Joe_vector & x);

		iterator begin()const{return start; };
		iterator end()const{ return finish; };
		reverse_iterator rbegin()const{ return (finish-1); };
		reverse_iterator rend()const{ return (start-1); };

		refrence front(){ return *begin();  };
		refrence back(){ return *(end()-1); };

		size_type size()const{ return size_type(finish - start); };
		size_type capacity()const { return size_type(end_of_storage - start); };
		refrence operator[](size_type n){return *(begin()+n); }


		void push_back(const value_type& x);
		void pop_back();
		iterator erase(iterator pos);
		iterator erase(iterator first, iterator last);
		//删除区间左闭右开

		void resize();
		void clear(){	while(size()) pop_back(); };
		bool empty()const {return begin() == end();  };

		~Joe_vector(){delete[] start; };
};

	template<typename T>
inline void Joe_vector<T>::push_back(const value_type& x)
{
	if(finish != end_of_storage)
	{
		contruct(finish, x);
		finish++;
	}
	else
	{
		apply_memory(start, finish, end_of_storage , x);
	}
}


	template<typename T>
inline void Joe_vector<T>::pop_back()
{
	--finish; 
	destory(finish);
}


	template<typename T>
inline T* Joe_vector<T>::erase(iterator first, iterator last)
{
	if(last == end() )
	{
		destory(first, last);	
		for(auto i = first; i != end(); ++i)
			--finish;
	}
	else
	{
		memmove(first, last, end()-last );
		auto i = finish-last+first;
		destory(i, last);	
		for(auto j = i; j != end(); ++i)
			--finish;
	}
	return first; 
}


	template<typename T>
inline T* Joe_vector<T>::erase(iterator pos)
{
	if(pos+1 != end())
		memmove(pos, pos+1, end()-pos);
	--finish;
	destory(finish);
	return pos;
}



	template<typename T>
Joe_vector<T>::Joe_vector(size_type n, const_value_type value )
{
	finish = start= (iterator)(::operator new(sizeof(T)*n));
	end_of_storage = start + sizeof(T)*n;
	for(int i = 0; i < n; ++i)
		push_back(value);
}

	template<typename T>
Joe_vector<T>::Joe_vector(Joe_vector & x)
{
	start = new value_type[x.capacity()];
	memmove(start, x.begin(), x.capacity()*sizeof(T));
	finish = start + x.size();
	end_of_storage = start + x.capacity();
}


#endif //__JOE_VECTOR__













