#-------------------------------------------------------------------------------------
# Locate ASIO library
# This module defines
#    ASIO_FOUND, if false, do not try to link to include ASIO
#    ASIO_INCLUDE_DIR, where to find asio/asio.hpp
#
#-------------------------------------------------------------------------------------

find_path(ASIO_INCLUDE_DIR
    NAMES
        asio.hpp
    PATH_PREFIXES
        asio
    PATHS
        /usr/local/include
        /usr/include
        /opt/local/include
        /opt/csw/include
        /opt/include
        $ENV{ASIO_DIR}/include
        $ENV{ASIO_ROOT}/include
        ${ASIO_DIR}/include
        ${ASIO_ROOT}/include
    NO_DEFAULT_PATH
)

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(asio DEFAULT_MSG ASIO_INCLUDE_DIR)

MARK_AS_ADVANCED(ASIO_INCLUDE_DIR)
