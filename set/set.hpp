#ifndef __SET__
#define __SET__
#include "Joe_RBtree.hpp"

//   set <key,  Compare, Alloc>
//rbtree <key,  key,     idenity<key>,  Compare=less<key>,  Alloc=allocator<key>    >

template<typename key, typename Compare=std::less<key>, typename Alloc=Joe::allocator< rb_tree_node<key> >  >
class set
{
	public:
		using value_type = key;
		using key_type   = key;
		using key_compare   = Compare;
		using value_compare = Compare;
	private:
		using rb_type = rb_tree<key_type, value_type, value_type, key_compare, Alloc  >;
		rb_type true_tree;
	public:
		using iterator    =  typename rb_type::const_iterator;
		using re_iterator =  typename rb_type::const_reverse_iterator;

	public:
		iterator   begin()const{return true_tree.cbegin(); }
		iterator   end()const  {return true_tree.cend();   }
		bool empty(){return true_tree.empty();       }
		void insert(const value_type& val)const{ true_tree.insert_equal(val);  	}
};

#endif //__SET__
