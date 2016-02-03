
#ifndef H_PION_STDINT
#define H_PION_STDINT

#ifdef ASIO_STANDALONE

#include <cstdint>

namespace pion
{
	using std::int8_t;
	using std::int16_t;
	using std::int32_t;
	using std::int64_t;
	using std::uint8_t;
	using std::uint16_t;
	using std::uint32_t;
	using std::uint64_t;
}

#else

#include <boost/cstdint.hpp>

namespace pion
{
	using boost::int8_t;
	using boost::int16_t;
	using boost::int32_t;
	using boost::int64_t;
	using boost::uint8_t;
	using boost::uint16_t;
	using boost::uint32_t;
	using boost::uint64_t;
}

#endif

#endif
