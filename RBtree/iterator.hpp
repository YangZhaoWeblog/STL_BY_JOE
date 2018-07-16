#ifndef __ITORATOR__
#define __ITORATOR__

template<typename value_type, typename reference, typename pointer> 
class rb_tree_iterator
{
	private:	           
		pointer ptr;
	public:
	   pointer operator*( const pointer);
		
};


#endif //__ITORATOR__

