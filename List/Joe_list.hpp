#ifndef __LIST__
#define __LIST__
#include <iostream>
#define debug(); cout<<__LINE__<<endl;
using namespace std;

template<typename node_pointer, typename reference,typename size_type>
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

		iter operator+(size_type& diff)	{ node_pointer tmp = ptr; while(diff--) tmp = tmp->next; return tmp;	}
		iter operator-(size_type& diff)	{ node_pointer tmp = ptr; while(diff--) tmp = tmp->prev; return tmp;	}
		iter operator+=(size_type& diff){ while(diff--)	ptr = ptr->next;  }
		iter operator-=(size_type& diff){ while(diff--)	ptr = ptr->prev;  }

		iter( node_pointer& p=nullptr):ptr(p){	}
		iter(const node_pointer& p=nullptr):ptr(p){	}
		node_pointer self(){return ptr;	}
};

template<typename node_pointer, typename reference,typename size_type>
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

		re_iter operator+(size_type& diff)	{ node_pointer tmp = ptr; while(diff--) tmp = tmp->prev; return tmp;	}
		re_iter operator-(size_type& diff)	{ node_pointer tmp = ptr; while(diff--) tmp = tmp->next; return tmp;	}
		re_iter operator+=(size_type& diff){ while(diff--)	ptr = ptr->prev;  }
		re_iter operator-=(size_type& diff){ while(diff--)	ptr = ptr->next;  }
		re_iter( node_pointer& p=nullptr):ptr(p){	}
		re_iter(const node_pointer& p=nullptr):ptr(p){	}
		node_pointer self(){return ptr;	}
};



template <typename T>
class List
{//亚元节点
	private:
		struct Node
		{
			Node* prev;
			Node* next;
			T date;
			Node():prev(prev), next(next), date(666){	}
		};

	public:

		using value_type = T; 
		using const_value_type = const T; 
		using pointer =  value_type*; 
		using reference = value_type&;
		using const_reference = const value_type&;

		using node_type  = Node;
		using node_pointer    = node_type* ;
		using node_reference  = node_type&;
		using difference = ptrdiff_t;
		using size_type  = size_t;

		using iterator      = iter<node_pointer, reference, size_type>;
		using re_iterator   = re_iter<node_pointer, reference, size_type>;
	private:
		size_type length;
		node_pointer   Head;
	public:

	public:
		List():length(0), Head(new node_type){ }
		iterator begin(){return (Head->next);}
		iterator end(){ return (Head);}
		iterator cbegin(){return (Head->next);}
		iterator cend(){ return (Head);}

		re_iterator rbegin(){return Head->prev;}
		re_iterator rend(){ return (Head);}

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
typename List<T>::iterator List<T>::insert(iterator pos, const_value_type& val)
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
void List<T>::clear()
{
	//using iterator are more simple;
	if(empty())
		return; 
	node_pointer p = Head->next;
	while( p != Head )
	{
		node_pointer tail = p->next;
		delete p;
		p = tail;
	}
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


