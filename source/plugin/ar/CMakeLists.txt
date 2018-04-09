set(PXR_PREFIX pxr/usd)
set(PXR_PACKAGE alaResolver)

link_directories($ENV{REZ_USD_ROOT}/lib $ENV{REZ_TBB_ROOT}/lib/intel64/gcc4.4/)


pxr_plugin(${PXR_PACKAGE}
    LIBRARIES
        arch
        tf
        plug
        vt
        ar
        /mnt/ala/software/ext_packages/libzmq/4.2.3/lib/libzmq.so
        ${Boost_PYTHON_LIBRARY}

    INCLUDE_DIRS
        $ENV{REZ_USD_ROOT}/include
        $ENV{REZ_TBB_ROOT}/include
        ${Boost_INCLUDE_DIRS}

    PUBLIC_HEADERS
        alaResolver.h

    CPPFILES
        zmqClient.cpp
        alaResolver.cpp

    RESOURCE_FILES
        plugInfo.json
)


#$ENV{REZ_LIBZMQ_ROOT}
