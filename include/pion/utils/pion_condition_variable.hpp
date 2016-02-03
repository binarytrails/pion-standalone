
#ifndef H_PION_CONDITION_VARIABLE
#define H_PION_CONDITION_VARIABLE

#ifdef ASIO_STANDALONE

#include <condition_variable>

// bring condition_variable in the pion namespace
namespace pion
{
	using std::condition_variable;
}

#else

#include <boost/thread/condition_variable.hpp>

// bring condition_variable in the pion namespace
namespace pion
{
	using boost::condition_variable;
}

#endif

#endif
