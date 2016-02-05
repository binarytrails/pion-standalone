
#ifndef H_PION_TRIBOOL
#define H_PION_TRIBOOL

#include <cassert>

namespace pion
{

class tribool
{
	public:
		tribool() = default;
		tribool( bool (*)(const tribool &) ) : v( 2 ){}
		tribool( bool b ) : v( b ? 1 : 0 ){}

		inline operator bool() const { assert( v == 0 or v == 1 ); return v == 1; }

	private:
		int v = 2;

		friend bool indeterminate( const tribool & );
};

bool indeterminate( const tribool & );

}

#endif
