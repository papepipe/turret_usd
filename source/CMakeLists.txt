project(usd)

if (WIN32)
    cmake_minimum_required(VERSION 3.1.1)
else()
    cmake_minimum_required(VERSION 2.8.8)
endif()

if (NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    if (WIN32)
        message(FATAL_ERROR "Compiler does not support 64-bit builds. "
                "If you are using Visual Studio, make sure you are in the "
                "x64 command prompt and have specified the Win64 cmake "
                "generator (e.g., -G \"Visual Studio 14 2015 Win64\")")
    else()
        message(FATAL_ERROR "Compiler does not support 64-bit builds.")
    endif()
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/defaults
                      ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules
                      ${CMAKE_CURRENT_SOURCE_DIR}/cmake/macros)

include(Options)

# Versions prior to 3.1.0 on Unix platforms built archive libraries
# incorrectly.  Require at least that version if necessary.
if((NOT BUILD_SHARED_LIBS OR PXR_BUILD_MONOLITHIC) AND NOT WIN32)
    cmake_minimum_required(VERSION 3.1.0)
endif()

include(ProjectDefaults)
include(Packages)

# This has to be defined after Packages is included, because it relies on the
# discovered path to the python executable.
set(PXR_PYTHON_SHEBANG "${PYTHON_EXECUTABLE}" 
    CACHE 
    STRING
    "Replacement path for Python #! line."
)

# CXXDefaults will set a variety of variables for the project.
# Consume them here. This is an effort to keep the most common
# build files readable.
include(CXXDefaults)
add_definitions(${_PXR_CXX_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${_PXR_CXX_FLAGS} ${CMAKE_CXX_FLAGS}")

include(Public)

add_subdirectory(plugin)

function(_addIfExists pkg pkgCmakeLists)
    if (EXISTS ${pkgCmakeLists})
        add_subdirectory(${pkg})
    else()
        message(WARNING "Specified third party package '${pkgName}' was not found. Please check that '${pkgCmakeLists}' exists")
    endif()
endfunction()

function(_enableThirdPartyPlugin identifier)
    set(pkg third_party/${identifier}) 
    set(pkgCmakeLists ${CMAKE_CURRENT_SOURCE_DIR}/${pkg}/CMakeLists.txt)
    _addIfExists(${pkg} ${pkgCmakeLists})
endfunction()

