
#ifndef H_PION_EXCEPTION
#define H_PION_EXCEPTION

#ifdef ASIO_STANDALONE

#include <memory>

namespace pion
{

class exception_base
{
	protected:
		exception_base() = default;
	
	public:
		virtual ~exception_base() = default;
	
		template<typename T>
		const exception_base &operator<<( const T & ) const
		{
			return *this;
		}

	private:
};

template<typename T,typename V>
struct error_info
{
	error_info( const V &i_value ) : _value( i_value ){}

	typedef T type_value;
	typedef const V value_type;
	
	value_type _value;
};

typedef pion::error_info<struct throw_file_,const char *> throw_file;
typedef pion::error_info<struct throw_line_,int> throw_line;

template<typename T>
typename T::value_type *get_error_info( const exception_base & )
{
	return nullptr;
}

}

#define PION_THROW_EXCEPTION(e) throw (e << pion::throw_file(__FILE__) << pion::throw_line(__LINE__))
#define PION_DEMANGLE_EXCEPTION(e) typeid(e).name()

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
#define PION_DEMANGLE_EXCEPTION(e) boost::units::detail::demangle(BOOST_EXCEPTION_DYNAMIC_TYPEID(e).type_->name())

#endif

#endif
