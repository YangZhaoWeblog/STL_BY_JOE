#ifndef __Joe_RBtree__
#define __Joe_RBtree__
#include <iostream>
#include <cstddef>
#include <new>
#include "iterator.hpp"

using namespace std;

namespace Joe
{
	//RBtree
	enum class Type:char{RED, BLACK};
	template<typename key, typename value, typename keyofvalue, class Compare>/*no allocator， just extern function*/
		class rb_tree
		{
			public:
				using value_type      = value;
				using key_type        = key;   //this is for STL::map
				using iterator        = rb_tree_iterator<value_type, reference, pointer>;
				using difference_type = ptrdiff_t;
				using size_type       = size_t;

			public:
				rb_tree();
				bool empty();	
				iterator erase(iterator position);
				void erase(iterator first, iterator last);
				~rb_tree();
		};
}


#endif // __Joe_RBtree__


















