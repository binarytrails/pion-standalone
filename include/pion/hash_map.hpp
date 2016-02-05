// ---------------------------------------------------------------------
// pion:  a Boost C++ framework for building lightweight HTTP interfaces
// ---------------------------------------------------------------------
// Copyright (C) 2007-2014 Splunk Inc.  (https://github.com/splunk/pion)
//
// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt
//

#ifndef __PION_HASH_MAP_HEADER__
#define __PION_HASH_MAP_HEADER__

#include <pion/config.hpp>
#include <string>
#include <locale>
#include <pion/utils/pion_string.hpp>
#include <unordered_map>


namespace pion {    // begin namespace pion

    #define PION_HASH_MAP std::unordered_map
    #define PION_HASH_MULTIMAP std::unordered_multimap
    #define PION_HASH_STRING std::hash<std::string>
    #define PION_HASH(TYPE) std::hash<TYPE>

    /// case insensitive string equality predicate
    /// copied from boost.unordered hash_equality documentation
    /// http://www.boost.org/doc/libs/1_50_0/doc/html/unordered/hash_equality.html
    struct iequal_to
        : std::binary_function<std::string, std::string, bool>
    {
        bool operator()(std::string const& x,
                        std::string const& y) const
        {
            return pion::iequals(x, y, std::locale());
        }
    };

    /// case insensitive hash generic function
    /// copied from boost.unordered hash_equality documentation
    /// http://www.boost.org/doc/libs/1_50_0/doc/html/unordered/hash_equality.html
    struct ihash
        : std::unary_function<std::string, std::size_t>
    {
        std::size_t operator()(std::string const& x) const
        {
            std::string s;
			s.reserve( x.size() );
			for ( auto c : x )
				s.push_back( std::toupper( c ) );
            return std::hash<std::string>()(s);
        }
    };

    /// data type for case-insensitive dictionary of strings
    typedef PION_HASH_MULTIMAP<std::string, std::string, ihash, iequal_to >    ihash_multimap;


}   // end namespace pion

#endif
