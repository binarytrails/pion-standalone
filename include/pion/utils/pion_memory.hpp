
#ifndef H_PION_MEMORY
#define H_PION_MEMORY

#ifdef ASIO_STANDALONE

#include <memory>

namespace pion
{
	using std::shared_ptr;
	using std::enable_shared_from_this;
	
	class noncopyable
	{
		public:
			noncopyable() = default;
			virtual ~noncopyable() = default;
			noncopyable( const noncopyable & ) = delete;
	};
}

#else

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/scoped_array.hpp>

namespace pion
{
	using boost::shared_ptr;
	using boost::noncopyable;
	using boost::enable_shared_from_this;
}

#endif

#endif
