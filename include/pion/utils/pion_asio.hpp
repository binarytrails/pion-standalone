
#ifndef H_PION_ASIO
#define H_PION_ASIO

#include <pion/config.hpp>

#ifdef ASIO_STANDALONE

#include <asio.hpp>
#include <asio/system_timer.hpp>
#include <functional>

#ifdef PION_HAVE_SSL
    #if defined(__APPLE__)
        // suppress warnings about OpenSSL being deprecated in OSX
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    #endif
    #include <asio/ssl.hpp>
#endif

namespace asio { namespace placeholders
{
	constexpr auto error = std::placeholders::_1;
	constexpr auto bytes_transferred = std::placeholders::_2;
} }

// bring asio in the pion namespace
namespace pion
{
	namespace asio = ::asio;
	
}

#else

#include <boost/asio.hpp>
#include <boost/asio/system_timer.hpp>

#ifdef PION_HAVE_SSL
    #if defined(__APPLE__)
        // suppress warnings about OpenSSL being deprecated in OSX
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    #endif
    #include <boost/asio/ssl.hpp>
#endif

// bring asio in the pion namespace
namespace pion
{
	namespace asio = boost::asio;
}

#endif

#endif
