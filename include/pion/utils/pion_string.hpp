
#ifndef H_PION_STRING
#define H_PION_STRING

#include <string>
#include <vector>
#include <locale>

namespace pion
{
	std::vector<std::string> split( const std::string &s, char sep );

	bool iequals( const std::string &a, const std::string &b, const std::locale &l = std::locale() );
	void trim( std::string &s );
	void to_lower( std::string &s );
}

#endif
