
#ifndef H_PION_FILESYSTEM
#define H_PION_FILESYSTEM

#ifdef ASIO_STANDALONE

#else

#include <boost/filesystem.hpp>

// bring filesystem in the pion namespace
namespace pion
{
	namespace filesystem = boost::filesystem;
}

#endif

#endif
