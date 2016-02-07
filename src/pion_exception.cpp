
#include <pion/utils/pion_exception.hpp>

namespace pion
{

std::string diagnostic_information( const std::exception &ex )
{
	return ex.what();
}

}
