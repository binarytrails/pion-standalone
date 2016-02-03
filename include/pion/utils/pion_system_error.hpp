
#ifndef H_PION_SYSTEM_ERROR
#define H_PION_SYSTEM_ERROR

#ifdef ASIO_STANDALONE

#include <system_error>

namespace pion
{
	using std::error_code;
	using std::error_category;
	using std::error_condition;
	using std::system_category;
	using std::errc;
}

#else

#include <boost/system/system_error.hpp>
#include <boost/system/error_code.hpp>

namespace pion
{
	using boost::system::error_code;
	using boost::system::error_category;
	using boost::system::error_condition;
	using boost::system::system_category;
	namespace errc = boost::system::errc;
}

#endif

#endif
