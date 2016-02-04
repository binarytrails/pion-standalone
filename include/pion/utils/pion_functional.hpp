
#ifndef H_PION_FUNCTIONAL
#define H_PION_FUNCTIONAL

#ifdef ASIO_STANDALONE

#include <functional>

namespace pion
{
	using std::function;
	using std::bind;
	using std::ref;
	namespace placeholders = std::placeholders;
}

#else

#include <boost/function.hpp>
#include <boost/bind.hpp>

namespace pion
{
	using boost::function;
	using boost::bind;
	using boost::ref;
	
	namespace placeholders
	{
		using ::_1;
		using ::_2;
		using ::_3;
	}
}

#endif

#endif
