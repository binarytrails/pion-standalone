#ifndef H_PION_PION_CIRCULAR_BUFFER
#define H_PION_PION_CIRCULAR_BUFFER

namespace pion
{

template<typename T>
class circular_buffer
{
	public:
		circular_buffer( size_t );
		
		void push_back( const T & );
};

}

#endif
