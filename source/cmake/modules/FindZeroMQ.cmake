if(UNIX)
    set(PKG_CONFIG_USE_CMAKE_PREFIX_PATH ON)
    find_package(PkgConfig)
    pkg_check_modules(PC_LIBZMQ QUIET libzmq)
endif(UNIX)

set(PC_LIBZMQ_LIBDIR C:/packages/pg/prod/libzmq/4.3.2/vs14_2015_x64)
set(PC_LIBZMQ_LIBDIR_BIN C:/packages/pg/prod/libzmq/4.3.2/vs14_2015_x64)

set(ZeroMQ_VERSION ${PC_LIBZMQ_VERSION})

find_library(ZeroMQ_LIBRARY NAMES libzmq.so libzmq.dylib libzmq-v140-mt-4_3_2.dll
             PATHS ${PC_LIBZMQ_LIBDIR_BIN} )
find_library(ZeroMQ_STATIC_LIBRARY NAMES libzmq-static.a libzmq.a libzmq.dll.a libzmq-v140-mt-s-4_3_2.dll
             PATHS ${PC_LIBZMQ_LIBDIR} )

# set this env var to locat the cppzmq include dir:
set(CPPZMQ_INCLUDE_DIRS $ENV{CPPZMQ_INCLUDE})

if(ZeroMQ_LIBRARY AND ZeroMQ_STATIC_LIBRARY)
    set(ZeroMQ_FOUND ON)
endif()

if (TARGET libzmq)
    # avoid errors defining targets twice
    return()
endif()

add_library(libzmq SHARED IMPORTED)
set_property(TARGET libzmq PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${PC_LIBZMQ_INCLUDE_DIRS})
set_property(TARGET libzmq PROPERTY IMPORTED_LOCATION ${ZeroMQ_LIBRARY})

add_library(libzmq-static STATIC IMPORTED ${PC_LIBZMQ_INCLUDE_DIRS})
set_property(TARGET libzmq-static PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${PC_LIBZMQ_INCLUDE_DIRS})
set_property(TARGET libzmq-static PROPERTY IMPORTED_LOCATION ${ZeroMQ_STATIC_LIBRARY})
