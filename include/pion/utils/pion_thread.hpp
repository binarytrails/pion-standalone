
#ifndef H_PION_THREAD
#define H_PION_THREAD

#ifdef ASIO_STANDALONE

#include <thread>

namespace pion
{
	using std::thread;
	namespace this_thread = std::this_thread;
}

#else

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 2) || (__GNUC__ == 4 && __GNUC_MINOR__ == 2 && __GNUC_PATCHLEVEL__ >= 1)
    #pragma GCC diagnostic ignored "-Wunused-parameter"
    #include <boost/thread.hpp>
    #pragma GCC diagnostic warning "-Wunused-parameter"
#else
    #include <boost/thread.hpp>
#endif

namespace pion
{
	using boost::thread;
	namespace this_thread = boost::this_thread;
}

#endif

#endif
