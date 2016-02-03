
#ifndef H_PION_MUTEX
#define H_PION_MUTEX

#ifdef ASIO_STANDALONE

#include <mutex>

namespace pion
{
	using std::mutex;
	using std::unique_lock;
	using std::once_flag;
	using std::call_once;
}

#else

#include <boost/thread/mutex.hpp>
#include <boost/thread/once.hpp>
#include <boost/thread/locks.hpp>

namespace pion
{
	using boost::mutex;
	using boost::unique_lock;
	using boost::once_flag;

	// just reverse args order
	template<typename Callable>
	inline void call_once( boost::once_flag& flag, Callable &f )
	{
		boost::call_once( f, flag );
	}
}

#endif

#endif
