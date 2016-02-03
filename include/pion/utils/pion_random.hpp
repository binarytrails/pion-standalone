
#ifndef H_PION_RANDOM
#define H_PION_RANDOM

#ifdef ASIO_STANDALONE

#include <random>

namespace pion
{
	using std::mt19937;
	using std::uniform_int_distribution;
}

#else

// #pragma diagnostic is only supported by GCC >= 4.2.1
#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 2) || (__GNUC__ == 4 && __GNUC_MINOR__ == 2 && __GNUC_PATCHLEVEL__ >= 1)
    #pragma GCC diagnostic ignored "-Wunused-parameter"
    #include <boost/random.hpp>
	#include <boost/random/uniform_int_distribution.hpp>
    #pragma GCC diagnostic warning "-Wunused-parameter"
#else
    #include <boost/random.hpp>
	#include <boost/random/uniform_int_distribution.hpp>
#endif

namespace pion
{
	using boost::mt19937;
	using boost::random::uniform_int_distribution;
}

#endif

#endif
