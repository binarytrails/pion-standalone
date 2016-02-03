
#ifndef H_PION_ASSERT
#define H_PION_ASSERT

#ifdef ASIO_STANDALONE

#include <cassert>
#define PION_ASSERT assert

#else

#include <boost/assert.hpp>
#define PION_ASSERT BOOST_ASSERT

#endif

#endif
