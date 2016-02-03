
#ifndef H_PION_EXCEPTION
#define H_PION_EXCEPTION

#ifdef ASIO_STANDALONE


namespace pion
{
}

#else

#include <boost/exception/exception.hpp>
#include <boost/exception/info.hpp>
#include <boost/exception/error_info.hpp>
#include <boost/exception/get_error_info.hpp>
#include <boost/throw_exception.hpp>

// #pragma diagnostic is only supported by GCC >= 4.2.1
#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 2) || (__GNUC__ == 4 && __GNUC_MINOR__ == 2 && __GNUC_PATCHLEVEL__ >= 1)
	#pragma GCC diagnostic ignored "-Wunused-parameter"
	#include <boost/units/io.hpp>
	#pragma GCC diagnostic warning "-Wunused-parameter"
#else
	#include <boost/units/io.hpp>
#endif

namespace pion
{
	typedef boost::exception exception_base;
	using boost::get_error_info;
	using boost::error_info;
	using boost::throw_file;
	using boost::throw_line;
}

#define PION_THROW_EXCEPTION BOOST_THROW_EXCEPTION

#endif

#endif
