@echo off

rd /s /q build

mkdir build
cd build

SET USD_LIB_VARIANT=HDK
SET LIBTURRET_ROOT=C:/packages/pg/prod/turret_lib/1.1.17
SET PYTHON_LIBS=C:/Python27/libs

SET LIBZMQ_ROOT=C:/packages/pg/prod/libzmq/4.3.2
SET LIBZMQ_INCLUDE_DIR=%LIBZMQ_ROOT%/include
SET LIBZMQ_LIB_DIR=%LIBZMQ_ROOT%/vs14_2015_x64/libzmq-v140-mt-4_3_2.lib

SET HOUDINI_ROOT=C:/Program Files/Side Effects Software/Houdini 18.0.391
SET USD_ROOT=%HOUDINI_ROOT%/toolkit
SET REZ_BOOST_ROOT=%USD_ROOT%
SET REZ_TBB_ROOT=C:/USD_build
SET REZ_USD_ROOT=%USD_ROOT%

SET USE_HDK_USD=1
SET USE_HDK_MONOLITHIC_USD=0
SET REZ_TBB_ROOT=C:/USD_build/src/tbb2017_20170226oss
SET TBB_LIBRARIES=C:/USD_build/src/tbb2017_20170226oss/lib/intel64/vc14

cmake -DUSD_LIB_VARIANT:STRING=%USD_LIB_VARIANT% -DPC_LIBZMQ_LIBDIR:STRING=%LIBZMQ_ROOT% -DZeroMQ_LIBRARY:STRING=%LIBZMQ_LIB_DIR% -DPC_LIBZMQ_INCLUDE_DIRS:STRING=%LIBZMQ_INCLUDE_DIR% -DCMAKE_INSTALL_PREFIX="C:/packages/pg/prod/turret_houdini/1.1.5" -G "Visual Studio 14 2015 Win64" ..
cmake --build . --config Release --target install -- /M:16

cd ..
