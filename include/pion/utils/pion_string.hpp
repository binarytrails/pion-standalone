
#ifndef H_PION_STRING
#define H_PION_STRING

#include <string>
#include <vector>

#ifdef ASIO_STANDALONE

#include <locale>

namespace pion
{
	using std::stoi;
	using std::stoull;
	using std::stoul;
	using std::to_string;

	std::vector<std::string> split( const std::string &s, char sep );
	
	bool iequals( const std::string &a, const std::string &b, const std::locale &l = std::locale() );
	void trim( std::string &s );
	void to_lower( std::string &s );
}

#else

#include <boost/lexical_cast.hpp>
#include <boost/cstdint.hpp>
#include <boost/algorithm/string.hpp>

namespace pion
{

	inline int stoi( const std::string &s )
	{
		return boost::lexical_cast<int>( s );
	}

	inline boost::uint64_t stoull( const std::string &s )
	{
		return boost::lexical_cast<boost::uint64_t>( s );
	}

	inline unsigned long stoul( const std::string &s )
	{
		return boost::lexical_cast<unsigned long>( s );
	}

	inline std::string to_string( int i )
	{
		return boost::lexical_cast<std::string>( i );
	}

	std::vector<std::string> split( const std::string &s, char sep );

	using boost::algorithm::iequals;
	using boost::algorithm::trim;
	using boost::algorithm::to_lower;
}

#endif

#endif
