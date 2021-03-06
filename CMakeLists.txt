cmake_minimum_required (VERSION 3.2)

if(WIN32)
        add_definitions( -DBOOST_ALL_NO_LIB )
endif(WIN32)

set(CMAKE_MODULE_PATH
   ${CMAKE_SOURCE_DIR}/cmake
   ${CMAKE_MODULE_PATH}
)

macro(set_option option value)
    set(${option} ${value} CACHE INTERNAL ""FORCE)
endmacro()

# At ALA, our usd_houdini_hdk package sets an env var, which we use to automatically
# select the correct USD lib when building variants:
if(DEFINED ENV{USE_HDK_USD})
    if(DEFINED ENV{USE_HDK_MONOLITHIC_USD})
        if($ENV{USE_HDK_MONOLITHIC_USD} STREQUAL "1")
            set_option(USD_LIB_VARIANT HDK_MONOLITHIC)
        else()
            set_option(USD_LIB_VARIANT HDK)
        endif()
    endif()
else()
    set_option(USD_LIB_VARIANT PXR)
endif()

set_option(CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/source)

if(UNIX)
        # jemalloc
        set_option(PXR_MALLOC_LIBRARY $ENV{REZ_JEMALLOC_ROOT}/lib/libjemalloc.so)
endif(UNIX)

# boost
set_option(BOOST_ROOT "$ENV{REZ_BOOST_ROOT}")

# tbb
set_option(TBB_ROOT_DIR "$ENV{REZ_TBB_ROOT}")
set_option(TBB_INCLUDE_DIR "$ENV{REZ_TBB_ROOT}/include")
set_option(TBB_LIBRARY "$ENV{REZ_TBB_ROOT}/lib/intel64/gcc4.4/")
set_option(TBB_LIBRARY "$ENV{TBB_LIBRARIES}")

set_option(PXR_BUILD_IMAGING OFF)
set_option(PXR_BUILD_USD_IMAGING OFF)

add_subdirectory("source")
