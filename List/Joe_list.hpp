#ifndef __LIST__
#define __LIST__
#include <iostream>
#define debug(); cout<<__LINE__<<endl;
using namespace std;

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
		using value_type = T; 
		using const_value_type = const T; 
		using pointer =  value_type*; 
		using reference = value_type&;
		using const_reference = const value_type&;

		using node_type  = Node;
		using node_pointer    = node_type* ;
		using node_reference  = node_type&;
		using difference_type = ptrdiff_t;
		using size_type  = size_t;

		using iterator      = iter<node_pointer, reference, difference_type>;
		using re_iterator   = re_iter<node_pointer, reference, difference_type>;
		using const_iterator   = c_iter<node_pointer, const_reference,difference_type>;
		using const_re_iterator   = c_re_iter<node_pointer, const_reference, difference_type>;

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

		reference operator[](difference_type& diff){ iterator tmp; tmp+=diff; return *tmp;	}
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
		void clear();

		iterator operator=(iterator& sth ){ return sth.self();  }
		iterator insert(iterator pos, const_value_type& val);

		void push_front(const_value_type& val)  { insert(begin(), val );	}
		void push_back (const_value_type& val)	{ insert(end(),   val );	}

		void pop_back();
		~List( ){clear(); delete Head; Head = nullptr;	}
};

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


//	template<typename T>
//void List<T>::erase(size_t pos)
//{
//
//	Node* p = Head->next;
//	while(pos--)
//	{
//		p = p->next;
//	}
//
//	Head->date--;
//	p->prev->next = p->next;
//	p->next->prev = p->prev;
//	delete p;
//	p = nullptr;
//}

//
//	template<typename T>
//void List<T>::get_value(size_t pos)
//{
//	Node* p = Head->next;
//	while(pos--)
//	{
//		p = p->next;
//	}
//	cout << p->date << endl;
//}
//

#endif


