//for const insert
//iterator ++
#ifndef __LIST__
#define __LIST__
#include <iostream>
#include <climits>
#define debug(); cout<<__LINE__<<endl;
using namespace std;

template<typename iterator>
void swap(iterator a_head, iterator b_head)
{
	           
}

template<typename node_pointer, typename reference,typename difference_type>
class iter
{
	protected:
		node_pointer ptr;
	public:
		bool operator==(const iter& x){ return x.ptr == ptr;	}
		bool operator!=(const iter& x){ return x.ptr != ptr;	}

		reference  operator*()const { return ptr->date;     }//must return reference
		node_pointer  operator->()const{ return &(operator*());	}

		iter operator++(){	ptr = ptr->next; return ptr; };
		iter operator--(){	ptr = ptr->prev; return ptr; };
		iter operator++(int){	iter tmp = ptr; ptr = ptr->next; return tmp; }
		iter operator--(int){   iter tmp = ptr; ptr = ptr->prev; return tmp; }

		iter operator+(difference_type& diff)	{ node_pointer tmp = ptr; while(diff--) tmp = tmp->next; return tmp;	}
		iter operator-(difference_type& diff)	{ node_pointer tmp = ptr; while(diff--) tmp = tmp->prev; return tmp;	}
		iter operator+=(difference_type& diff){ while(diff--)	ptr = ptr->next;  }
		iter operator-=(difference_type& diff){ while(diff--)	ptr = ptr->prev;  }

		iter( node_pointer& p=nullptr):ptr(p){	}
		iter(const node_pointer& p=nullptr):ptr(p){	}
		node_pointer self(){return ptr;	}
};

template<typename node_pointer, typename const_reference,typename difference_type>
class c_iter
{
	protected:
		node_pointer ptr;
	public:
		bool operator==(const c_iter& x){ return x.ptr == ptr;	}
		bool operator!=(const c_iter& x){ return x.ptr != ptr;	}

		const_reference operator*()const { return ptr->date;     }//must return reference
		node_pointer  operator->()const{ return &(operator*());	}

		c_iter operator++(){	ptr = ptr->next; return ptr; };
		c_iter operator--(){	ptr = ptr->prev; return ptr; };
		c_iter operator++(int){	c_iter tmp = ptr; ptr = ptr->next; return tmp; }
		c_iter operator--(int){ c_iter tmp = ptr; ptr = ptr->prev; return tmp; }

		c_iter operator+(difference_type& diff)	{ node_pointer tmp = ptr; while(diff--) tmp = tmp->next; return tmp;	}
		c_iter operator-(difference_type& diff)	{ node_pointer tmp = ptr; while(diff--) tmp = tmp->prev; return tmp;	}
		c_iter operator+=(difference_type& diff){ while(diff--)	ptr = ptr->next;  }
		c_iter operator-=(difference_type& diff){ while(diff--)	ptr = ptr->prev;  }

		c_iter( node_pointer& p=nullptr):ptr(p){	}
		c_iter(const node_pointer& p=nullptr):ptr(p){	}
		node_pointer self(){return ptr;	}
};


template<typename node_pointer, typename reference,typename difference_type>
class re_iter
{
	protected:
		node_pointer ptr;
	public:
		bool operator==(const re_iter& x){ return x.ptr == ptr;	}
		bool operator!=(const re_iter& x){ return x.ptr != ptr;	}

		reference operator*()const { return ptr->date;     }//must return reference
		node_pointer  operator->()const{ return &(operator*());	}
		re_iter operator++(){	ptr = ptr->prev; return ptr; };
		re_iter operator--(){	ptr = ptr->next; return ptr; };
		re_iter operator++(int){   re_iter tmp = ptr; ptr = ptr->prev; return tmp; }
		re_iter operator--(int){   re_iter tmp = ptr; ptr = ptr->next; return tmp; }

		re_iter operator+(difference_type& diff)	{ node_pointer tmp = ptr; while(diff--) tmp = tmp->prev; return tmp;	}
		re_iter operator-(difference_type& diff)	{ node_pointer tmp = ptr; while(diff--) tmp = tmp->next; return tmp;	}
		re_iter operator+=(difference_type& diff){ while(diff--)	ptr = ptr->prev;  }
		re_iter operator-=(difference_type& diff){ while(diff--)	ptr = ptr->next;  }
		re_iter( node_pointer& p=nullptr):ptr(p){	}
		re_iter(const node_pointer& p=nullptr):ptr(p){	}
		node_pointer self(){return ptr;	}
};

template<typename node_pointer, typename const_reference,typename difference_type>
class c_re_iter
{
	protected:
		node_pointer ptr;
	public:
		bool operator==(const c_re_iter& x){ return x.ptr == ptr;	}
		bool operator!=(const c_re_iter& x){ return x.ptr != ptr;	}

		const_reference operator*()const { return ptr->date;     }//must return reference
		node_pointer  operator->()const{ return &(operator*());	}
		c_re_iter operator++(){	ptr = ptr->prev; return ptr; };
		c_re_iter operator--(){	ptr = ptr->next; return ptr; };
		c_re_iter operator++(int){   c_re_iter tmp = ptr; ptr = ptr->prev; return tmp; }
		c_re_iter operator--(int){   c_re_iter tmp = ptr; ptr = ptr->next; return tmp; }

		c_re_iter operator+(difference_type& diff)	{ node_pointer tmp = ptr; while(diff--) tmp = tmp->prev; return tmp;	}
		c_re_iter operator-(difference_type& diff)	{ node_pointer tmp = ptr; while(diff--) tmp = tmp->next; return tmp;	}
		c_re_iter operator+=(difference_type& diff){ while(diff--)	ptr = ptr->prev;  }
		c_re_iter operator-=(difference_type& diff){ while(diff--)	ptr = ptr->next;  }
		c_re_iter( node_pointer& p=nullptr):ptr(p){	}
		c_re_iter(const node_pointer& p=nullptr):ptr(p){	}
		node_pointer self(){return ptr;	}

};

template<typename T>
struct list_Node
{
	list_Node* prev;
	list_Node* next;
	T date;
	list_Node():prev(prev), next(next), date(666){	}
};


template <typename T>
class List
{
	private:
		using Node = list_Node<T>;

	public:
		using value_type       = T; 
		using const_value_type = const T; 
		using pointer          =  value_type*; 
		using reference        = value_type&;
		using const_reference  = const value_type&;

		using node_type       = Node;
		using node_pointer    = node_type* ;
		using node_reference  = node_type&;
		using difference_type = ptrdiff_t;
		using size_type       = size_t;

		using iterator            =  iter<node_pointer, reference, difference_type>;
		using re_iterator         =  re_iter<node_pointer, reference, difference_type>;
		using const_iterator      =  c_iter<node_pointer, const_reference,difference_type>;
		using const_re_iterator   =  c_re_iter<node_pointer, const_reference, difference_type>;

	private:
		size_type length;
		node_pointer   Head;

	public:
		List():length(0), Head(new node_type){ }

		explicit List(size_type n, value_type val):List()
		{
			while(n--)	push_back(val);	
		}

		List (const List& x):List()
		{
			for(auto i = x.begin(); i != x.end(); ++i)
				this->push_back(*i);		
		}
		
		List(iterator first, iterator last):List()
		{
			for(auto i = first; i != last; ++i)
				push_back(*i);
		}

		List(std::initializer_list<value_type> il ):List()
		{
			for(auto& i: il)
					push_back(i);
		}

		iterator begin(){return (Head->next);}
		iterator end(){ return (Head);}
		const_iterator begin()const{return (Head->next);}
		const_iterator	end()const{ return (Head);}
		const_iterator cbegin(){return (Head->next);}
		const_iterator cend(){ return (Head);}

		re_iterator rbegin(){return Head->prev;}
		re_iterator rend(){ return (Head);}
		const_re_iterator rbegin()const{return Head->prev;}
		const_re_iterator rend()const{ return (Head);}

		const_re_iterator crbegin(){return Head->prev;}
		const_re_iterator crend(){ return (Head);}

		value_type front(){return *(begin());	}
		value_type back(){return *(--end());	}
		size_type size(){return length;}
		bool empty(){return size()== 0; }
		size_type max_size(){return UINT_MAX/sizeof(node_type);}
		void clear();

		List& operator=(const List& x)
		{ 
			for(auto i = x.begin(); i != x.end(); ++i)
				this->push_back(*i);		
		}

		iterator insert(iterator pos, const_value_type& val);
		iterator insert (iterator pos, size_type n, const_value_type& val);
		iterator insert (iterator pos, iterator first, iterator last);
		iterator insert (iterator pos, value_type&& val);
		iterator insert (iterator pos, initializer_list<value_type> il);

		void re_move(const_value_type& val);
		//      void re_move_if(Predicate pred );
		iterator erase(iterator pos);
		iterator erase(iterator first, iterator last);
		iterator emplace(const_iterator pos, const_value_type& val);

		void assign(iterator first, iterator last);
		void assign(size_type n, const_value_type& val);
		void assign(initializer_list<value_type> il);

		void push_front(const_value_type& val)  { insert(begin(), val );	}
		void push_back (const_value_type& val)	{ insert(end(),   val );	}
		iterator emplace_front( const_value_type& val){ insert(begin(), val );	}
		iterator emplace_back( const_value_type& val){ insert(begin(), val );	}

		void pop_back() {  erase(--end());	}
		void pop_front(){  erase(begin());	}

		void resize (size_type n, const_value_type& val = value_type());
		void reverse() noexcept;

		void sort();
		void merge();
		//void sort (Compare comp);
		void unique();
		~List( ){clear(); delete Head; Head = nullptr;	}
};

	template<typename T>
inline void List<T>::assign(size_type n, const_value_type& val)
{
	clear(); 
	while(n--)
		push_back(val);
}
	template<typename T>
inline void List<T>::assign(iterator first, iterator last)
{
	clear();
	for(auto i = first; i != last; ++i)
		push_back(*i);
}

	template<typename T>
inline 	void List<T>::assign(initializer_list<value_type> il)
{
	clear();
	for(auto i = il.end(); i != il.begin(); --i)
		push_back(*i);
}
	template<typename T>
inline typename List<T>::iterator List<T>::erase(iterator pos)
{
	if(empty())
		cerr <<  "List is empty" << endl;

	pos.self()->prev->next = pos.self()->next;
	pos.self()->next->prev = pos.self()->prev;
	delete pos.self();
	--length;
	return pos;
}

	template<typename T>
inline typename List<T>::iterator List<T>::erase(iterator first, iterator last)
{
	for(auto i = first; i != last; ++i)
		erase(i);
}

	template<typename T>
inline typename List<T>::iterator List<T>::insert(iterator pos, const_value_type& val)
{
	node_pointer tmp = new node_type;
	tmp->date        = val;

	if(empty())
	{
		Head->next = tmp;
		Head->prev = tmp;
		tmp->next  = Head;
		tmp->prev  = Head;
		++length;
		return tmp; 
	}

	tmp->next = pos.self();
	tmp->prev = pos.self()->prev;
	pos.self()->prev->next = tmp;
	pos.self()->prev       = tmp;
	++length;
	return tmp;
}

	template<typename T>
inline typename List<T>::iterator List<T>::insert (iterator pos, size_type n, const_value_type& val)
{
	while(n--)
		insert(pos, val);           
	return pos;
}

	template<typename T>
inline typename List<T>::iterator List<T>::insert (iterator pos, value_type&& val)
{
	insert(pos, val);           
	return pos;
}

	template<typename T>
inline typename List<T>::iterator List<T>::insert (iterator pos, iterator first, iterator last)
{
	for(auto i = last; i != first; --i)
		insert(pos, *i);
	return pos;
}


	template<typename T>
inline typename	List<T>::iterator List<T>::insert (iterator pos, initializer_list<value_type> il)
{
	for(auto i = il.end(); i != il.begin(); --i)
		insert(pos, *i );
}

	template<typename T>
inline void List<T>::re_move(const_value_type& val)
{
	for(auto i = begin(); i != end(); ++i)
		if(*i == val)
			erase(i);
}

	template<typename T>
inline 	void List<T>::resize (size_type n, const_value_type& val )
{
		if( n > max_size() )	
			cerr << "out of mempry" << endl;
		else if(n > size())
		{
			int tmp = n-size();
			while(tmp--)
				push_back(val);
		}
		else if(n > 0)
		{
			for(int i = 0; i < n-size(); ++i)
				pop_back();	
		}
}

	template<typename T>
inline void List<T>::reverse() noexcept//I can't understand why It is O(n) of STL, why they don't move iterator??
{
	//node_pointer tmp = Head->next;	           
	//Head->next = Head->prev;
	//Head->prev = tmp;
	std::swap(Head->next, Head->prev);
}

	template<typename T>
inline void List<T>::clear()
{
	//using iterator are more simple;
	if(empty())
		return; 

	for(auto i = begin(); i != end(); ++i)
		delete i.self();
	length = 0;
	Head->next = Head;
	Head->prev = Head;
}



#endif


