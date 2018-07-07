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


	template<typename it, typename T>
inline void contruct(it& finish, T value)
{
	new(finish) T(value);		      
}

	template<typename it, typename T>
inline void apply_memory(it& start, it& finish, it& end_of_storage ,T x)
{
	ptrdiff_t cha = finish-start;
	it new_start = nullptr;
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
		copy(start, finish, new_start);
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
		typedef const T*				const_iterator;	
		typedef const T*				const_refrence;	
	protected:
		iterator start;
		iterator finish;
		iterator end_of_storage;
	public:
		class reverse_iterator
		{
			private:
				iterator ptr; 
			public:
				bool  operator!=(const reverse_iterator& it)const{return ptr != it.ptr; }
				bool  operator==(const reverse_iterator& it)const{return ptr == it.ptr; }
				refrence  operator*(){return *ptr; }

				reverse_iterator operator++(){	   	return --ptr; }
				reverse_iterator operator--(){      return ++ptr; }

				const reverse_iterator operator++(int){iterator tmp = ptr;	--ptr;	return tmp; }
				const reverse_iterator operator--(int){iterator tmp = ptr;	++ptr;	return tmp; }

				reverse_iterator operator+(size_type& diff){	return ptr-diff; }
				reverse_iterator operator+=(size_type& diff){	return ptr+=diff; }
				reverse_iterator operator-(size_type& diff){	return ptr+diff; }
				reverse_iterator operator-=(size_type& diff){	return ptr-=diff; }

				reverse_iterator(iterator p = nullptr) : ptr(p) {}
		};

	public:
		Joe_vector():start(nullptr),finish(nullptr),end_of_storage(nullptr){ }
		Joe_vector(size_type n, const_value_type value);//范围定值初始化
		Joe_vector(Joe_vector & x);

		iterator begin()const{return start; };
		iterator end()const{ return finish; };
		const_iterator cbegin()const{return  start; };
		const_iterator cend(){ return  finish; };

		reverse_iterator rbegin()const{ return (finish-1); };
		reverse_iterator rend()const{ return (start-1); };
		//const reverse_iterator crbegin(){	return (finish-1); }
		//const reverse_iterator crend(){	return (start-1); }

		refrence front(){ return *begin();  };
		refrence back(){ return *(end()-1); };

		size_type size()const{ return size_type(finish - start); };
		size_type max_size()const{return UINT_MAX/sizeof(value_type); };
		size_type capacity()const { return size_type(end_of_storage - start); };
		refrence operator[](size_type n){return *(begin()+n); }


		void push_back(const value_type& x);
		void pop_back();
		iterator erase(iterator pos);
		iterator erase(iterator first, iterator last);
		void insert(iterator pos, const_value_type x);
		//删除区间左闭右开

		void resize(size_type sz, value_type c = value_type() );//for size
		void reserve(size_type n);//for capacity
		void shift_to_fit(){ end_of_storage = finish; };


		void clear(){ finish = start; };//update
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
	if(last != end())
		copy(last, end(), first);

	finish -= (last-first);
	return first; 
}


	template<typename T>
inline T* Joe_vector<T>::erase(iterator pos)
{
	if(pos+1 != end())
		copy(pos+1, end(), pos);
	--finish;
	destory(finish);
	return pos;
}


	template<typename T>
inline void Joe_vector<T>::insert(iterator pos, const_value_type x)
{
	copy(pos, finish, pos+1 );
	contruct(pos, x);
	++finish;
}

	template<typename T>
inline void Joe_vector<T>::reserve(size_type n)
{
	if(n > size() )	           
	{
		if( max_size() > n)
		{
			iterator new_start = (iterator) (::operator new(sizeof(value_type)*n));
			copy(start, finish, new_start);
			finish = new_start + (difference_type)(end()-begin()) ; 
			start = new_start;
			end_of_storage = start+n;
		}
		else
			cerr << "out of max_size" << endl;
	}
}

	template<typename T>
inline void Joe_vector<T>::resize(size_type n, value_type c  )
{
	if(max_size() < n)
		cerr << "out of max_size" << endl;
	else if(n < size())
		erase(end()-n , end());
	else if( size() < n )
	{
		if(capacity() < n)
		{
			iterator new_start= (iterator)(::operator new(sizeof(T)*n));
			copy(start, finish, new_start);
			finish = new_start + size();
			end_of_storage = new_start + n;
			start = new_start;
			while(n--)
				push_back(c);
		}
		else
		{
			while(n--)
				push_back(c);
		}
	}

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
	//	memmove(start, x.begin(), x.capacity()*sizeof(T));
	copy(x.begin(), x.end(), start);
	finish = start + x.size();
	end_of_storage = start + x.capacity();
}


#endif //__JOE_VECTOR__











