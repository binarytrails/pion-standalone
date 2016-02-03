
#ifndef H_PION_REGEX
#define H_PION_REGEX

#ifdef ASIO_STANDALONE

#include <regex>

namespace pion
{
	using std::regex;
	using std::regex_match;
	using std::regex_search;
	using std::match_results;
}

#else

#include <boost/regex.hpp>

namespace pion
{
	using boost::regex;
	using boost::regex_match;
	using boost::regex_search;
	using boost::match_results;
}

#endif

#endif
