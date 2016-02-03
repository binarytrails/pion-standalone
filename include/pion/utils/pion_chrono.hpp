
#ifndef H_PION_CHRONO
#define H_PION_CHRONO

#ifdef ASIO_STANDALONE

#include <chrono>

// bring chrono in the pion namespace
namespace pion
{
	namespace chrono = std::chrono;
}

#else

#include <boost/chrono.hpp>

// bring chrono in the pion namespace
namespace pion
{
	namespace chrono = boost::chrono;
}

#endif

#endif
