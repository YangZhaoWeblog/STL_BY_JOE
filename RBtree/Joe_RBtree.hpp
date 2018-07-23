//#!/usr/bin/env bash
//# **********************************************************
//# Author       : Joe_Yang
//# Last modified: 2018-07-22 14:00
//# Email        : 1514784049@qq.com || 1514784049yz@gmail.com
//# Weblog       : https://blog.csdn.net/pursue_my_life/
//# Filename     : Joe_RBtree.hpp
//# Description  : 
//# **********************************************************
//In this container, we will not use nullptr, just use 0. It is so effective!!  0 is not only a color type, but also is it a address. via this feature, wo don't have to add another dummy node. We can just use only one dummy node which is contain three pointer to root, mostleft, and mostright.  advise: don't try to use (void*)0 in c++, just use 0, Otherwise you will debug whole of you life. The reason you can google. 

#ifndef __Joe_RBtree__
#define __Joe_RBtree__
#include <iostream>
#include <cstddef>
#include <new>
//#include "iterator.hpp"
#include "allocator.hpp"
using namespace std;

enum class color_type:bool{RED=0, BLACK=1};

template<typename value_type>
struct rb_tree_node
{
	using node_pointer = rb_tree_node*;
	node_pointer left;
	node_pointer right;
	node_pointer prev;
	value_type date;
	color_type color;

	rb_tree_node(value_type val=value_type()):left(this), right(this), prev(0), date(val), color(color_type::RED) { 	}
};


template<typename value_type, typename reference, typename pointer> 
class rb_tree_iterator
{
	private:	           
		pointer ptr;
	public:
		pointer operator*( const pointer);
};

//RBtree
template<typename key, typename value, typename keyofvalue, typename Compare = std::less<key>, typename  Alloc = Joe::allocator< rb_tree_node<key>  > >
class rb_tree
{
	protected:
		using node_type	   = rb_tree_node<value>; //include a node type
		using node_pointer = node_type*;

	public:
		using value_type            =    value;
		using reference				=    value_type&;
		using pointer				=    value_type*;
		using const_value_type      =    const value_type;
		using const_pointer         =    const value_type*;
		using const_reference       =    const value_type&;

		using difference_type		=	 ptrdiff_t;
		using size_type             =	 size_t;
		using key_type              =	 key;   //this is for STL::map
		using iterator              =	 rb_tree_iterator<value_type, reference, pointer>;

	protected:

		Alloc* allocator;//for kongjian
		node_pointer head;
		size_type node_count;

	protected:
		inline node_pointer get_node();
		inline node_pointer push_node();
		inline node_pointer creat_node();
		inline node_pointer clone_node();
		void                destroy_node();

	public:
		rb_tree()
		{
			head       = creat_node();
			node_count = 0;
		}
		bool empty();	
		iterator erase(iterator position);
		void erase(iterator first, iterator last);

		iterator begin(){return head->next; }
		//rbegin();
		//cbegin();
		//crbegin();
		iterator end(){return head->prev;	}
		//rend();
		//cend();
		//crend();
		bool empty()const;
		void clear();
		size_type size()const{return node_count;	}
		size_type max_size()const{return size_type(-1); }
		~rb_tree()
		{

		}

	public:
		std::pair<iterator, bool> insert_unique(const_value_type& val);	
		iterator insert_equal(const_value_type& val);	
};

template<typename key, typename value, typename keyofvalue, typename Compare, typename  Alloc>
	inline typename rb_tree<key, value, keyofvalue, Compare, Alloc>::node_pointer //return value_type
rb_tree<key, value, keyofvalue, Compare, Alloc>::get_node()
{

	return allocator->apply_memory(1);
}

template<typename key, typename value, typename keyofvalue, typename Compare, typename  Alloc>
	inline typename rb_tree<key, value, keyofvalue, Compare, Alloc>::node_pointer //return value_type
rb_tree<key, value, keyofvalue, Compare, Alloc>::creat_node()
{
	allocator = new Alloc;
	node_pointer tmp = get_node();
	allocator->construct_object(tmp);
	return tmp;
}



#endif // __Joe_RBtree__


