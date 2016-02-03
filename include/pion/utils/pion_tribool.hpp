
#ifndef H_PION_TRIBOOL
#define H_PION_TRIBOOL

#ifdef ASIO_STANDALONE

#error

#else

#include <boost/logic/tribool.hpp>

namespace pion
{
	using boost::tribool;
	using boost::indeterminate;
}

#endif

#endif
