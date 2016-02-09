
#ifndef H_PION_EXCEPTION
#define H_PION_EXCEPTION

#include <pion/config.hpp>
#include <memory>
#include <string>
#include <stdexcept>

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

std::string PION_API diagnostic_information( const std::exception &ex );

}

#define PION_THROW_EXCEPTION(e) throw (e << pion::throw_file(__FILE__) << pion::throw_line(__LINE__))
#define PION_DEMANGLE_EXCEPTION(e) typeid(e).name()

#endif
