
#ifndef H_PION_FUNCTIONAL
#define H_PION_FUNCTIONAL

#ifdef ASIO_STANDALONE

#include <functional>

namespace pion
{
	using std::function;
	using std::bind;
	using std::ref;
}

#else

#include <boost/function.hpp>
#include <boost/bind.hpp>

namespace pion
{
	using boost::function;
	using boost::bind;
	using boost::ref;
}

#endif

#endif
