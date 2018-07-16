#ifndef __Joe_RBtree__
#define __Joe_RBtree__
#include <iostream>
#include <cstddef>
#include <new>
#include "iterator.hpp"
#include "allocator.hpp"
using namespace std;



namespace Joe
{
	//RBtree
	template<typename key, typename value, typename keyofvalue, typename Compare >
		class rb_tree
		{
			protected:
				enum class Type{RED, BLACK};
				using node_type	   = rb_tree_node<value>; //include a node type
				using node_pointer = node_type*;
			public:
				using value_type      = value;
				using reference       = value_type&;
				using pointer         = value_type*;
				using const_reference       = const value_type&;
				using const_pointer         = const value_type*;

				using difference_type = ptrdiff_t;
				using size_type       = size_t;
				using key_type        = key;   //this is for STL::map
				using iterator        = rb_tree_iterator<value_type, reference, pointer>;

			public:
				rb_tree();
				bool empty();	
				iterator erase(iterator position);
				void erase(iterator first, iterator last);
				~rb_tree();
		};
}


#endif // __Joe_RBtree__


















