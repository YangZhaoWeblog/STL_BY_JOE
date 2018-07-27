#ifndef __ITORATOR__
#define __ITORATOR__

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

	rb_tree_node(value_type val=value_type()): left(static_cast<int>(color_type::RED) ), 
											   right(static_cast<int>(color_type::RED)),
											   prev(static_cast<int>(color_type::RED) ),
											   date(val), color(color_type::RED) { 	  }
};



template<typename value_type, typename reference, typename node_pointer> 
class rb_tree_iterator
{
	private:	           
		node_pointer ptr;	
		void for_plus()
		{
			if(ptr->right == static_cast<int>(color_type::RED) )
			{
				node_pointer	father = ptr->prev;
				if(father->left == ptr)//if left child
				{
					ptr = father;			
				}
				else//not left child
				{
					while(ptr == father->right)
					{
						ptr = father;
						father = father->prev;
					}
					ptr = father;
				}
			}
			else
			{
				ptr = ptr->right;
				while(ptr->left != static_cast<int>(color_type::RED))
				{
					ptr = ptr->left;
				}
			}
		}
		void for_minus()
		{
			if(ptr->prev->prev == ptr && ptr->color == color_type::RED)//if ptr point to Head /*using end()*/, 
			{
					ptr = ptr->right;	
					return;
			}

			if(ptr->left == static_cast<int>(color_type::RED) )
			{
				node_pointer	father = ptr->prev;
				if(father->right == ptr)//if left child
				{
					ptr = father;			
				}
				else//not left child
				{
					while(ptr == father->left)
					{
						ptr = father;
						father = father->prev;
					}
					ptr = father;
				}
			}
			else
			{
				ptr = ptr->left;
				while(ptr->right != static_cast<int>(color_type::RED))
				{
					ptr = ptr->right;
				}
			}

		}

	public:
		node_pointer get_ptr(){ return ptr;	}
		reference operator*( )const{ return this->ptr->date;	}
		bool operator==(const rb_tree_iterator& x)const{ return ptr == x.ptr;	}
		bool operator!=(const rb_tree_iterator& x)const{ return ptr != x.ptr;	}
		node_pointer operator->()const{ return &(operator*());	}
		rb_tree_iterator()=default;
		~rb_tree_iterator()=default;
		rb_tree_iterator(node_pointer tmp):ptr(tmp){	}
		rb_tree_iterator(const rb_tree_iterator& x){ ptr = x.ptr;	}
		rb_tree_iterator operator++()
		{
			for_plus();
			return rb_tree_iterator(ptr);
		}

		rb_tree_iterator operator++(int)
		{
			node_pointer tmp = ptr;
			for_plus();
			return rb_tree_iterator(tmp);
		}

		rb_tree_iterator operator--()
		{
			for_minus();
			return rb_tree_iterator(ptr);
		}

		rb_tree_iterator operator--(int)
		{
			node_pointer tmp = ptr;
			for_minus();
			return rb_tree_iterator(tmp);
		}
};

template<typename value_type, typename reference, typename node_pointer> 
class const_rb_tree_iterator
{

};
template<typename value_type, typename reference, typename node_pointer> 
class reverse_rb_tree_iterator
{
	private:	           
		node_pointer ptr;	
		void for_plus()
		{
			if(ptr->right == static_cast<int>(color_type::RED) )
			{
				node_pointer	father = ptr->prev;
				if(father->left == ptr)//if left child
				{
					ptr = father;			
				}
				else//not left child
				{
					while(ptr == father->right)
					{
						ptr = father;
						father = father->prev;
					}
					ptr = father;
				}
			}
			else
			{
				ptr = ptr->right;
				while(ptr->left != static_cast<int>(color_type::RED))
				{
					ptr = ptr->left;
				}
			}
		}
		void for_minus()
		{
			if(ptr->prev->prev == ptr && ptr->color == color_type::RED)//if ptr point to Head /*using end()*/, 
			{
					ptr = ptr->right;	
					return;
			}

			if(ptr->left == static_cast<int>(color_type::RED) )
			{
				node_pointer	father = ptr->prev;
				if(father->right == ptr)//if left child
				{
					ptr = father;			
				}
				else//not left child
				{
					while(ptr == father->left)
					{
						ptr = father;
						father = father->prev;
					}
					ptr = father;
				}
			}
			else
			{
				ptr = ptr->left;
				while(ptr->right != static_cast<int>(color_type::RED))
				{
					ptr = ptr->right;
				}
			}

		}

	public:
		node_pointer get_ptr(){ return ptr;	}
		reference operator*( )const{ return this->ptr->date;	}
		bool operator==(const reverse_rb_tree_iterator& x)const{ return ptr == x.ptr;	}
		bool operator!=(const reverse_rb_tree_iterator& x)const{ return ptr != x.ptr;	}
		node_pointer operator->()const{ return &(operator*());	}
		reverse_rb_tree_iterator()=default;
		~reverse_rb_tree_iterator()=default;
		reverse_rb_tree_iterator(node_pointer tmp):ptr(tmp){	}
		reverse_rb_tree_iterator(const reverse_rb_tree_iterator& x){ ptr = x.ptr;	}
		reverse_rb_tree_iterator operator++()
		{
			for_minus();
			return reverse_rb_tree_iterator(ptr);
		}

		reverse_rb_tree_iterator operator++(int)
		{
			node_pointer tmp = ptr;
			for_minus();
			return reverse_rb_tree_iterator(tmp);
		}

		reverse_rb_tree_iterator operator--()
		{
			for_plus();
			return reverse_rb_tree_iterator(ptr);
		}

		reverse_rb_tree_iterator operator--(int)
		{
			node_pointer tmp = ptr;
			for_plus();
			return reverse_rb_tree_iterator(tmp);
		}

};

template<typename value_type, typename reference, typename node_pointer> 
class const_reverse_rb_tree_iterator
{

};

#endif //__ITORATOR__

