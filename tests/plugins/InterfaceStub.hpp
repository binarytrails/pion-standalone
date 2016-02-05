// ---------------------------------------------------------------------
// pion:  a Boost C++ framework for building lightweight HTTP interfaces
// ---------------------------------------------------------------------
// Copyright (C) 2007-2014 Splunk Inc.  (https://github.com/splunk/pion)
//
// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt
//

#ifndef __PION_INTERFACE_STUB_HEADER__
#define __PION_INTERFACE_STUB_HEADER__


///
/// Simple interface stub class for other unit test plugins
///
class InterfaceStub
{
public:
    InterfaceStub() = default;
    virtual ~InterfaceStub() = default;
    virtual void method() {}
    virtual void const_method() const {}
};

#endif
