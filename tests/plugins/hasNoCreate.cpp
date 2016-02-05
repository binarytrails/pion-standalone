// ---------------------------------------------------------------------
// pion:  a Boost C++ framework for building lightweight HTTP interfaces
// ---------------------------------------------------------------------
// Copyright (C) 2007-2014 Splunk Inc.  (https://github.com/splunk/pion)
//
// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt
//

#include "hasNoCreate.hpp"
#include <pion/config.hpp>

/// arbitrary function for the library to export
extern "C" PION_PLUGIN int f()
{
    return 4;
}
