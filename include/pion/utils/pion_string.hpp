
#ifndef H_PION_STRING
#define H_PION_STRING

#include <pion/config.hpp>
#include <string>
#include <vector>
#include <locale>

namespace pion
{
	std::vector<std::string> split( const std::string &s, char sep );

	bool PION_API iequals( const std::string &a, const std::string &b, const std::locale &l = std::locale() );
	void PION_API trim( std::string &s );
	void PION_API to_lower( std::string &s );
}

#endif
