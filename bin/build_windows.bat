@echo off

rd /s /q build

mkdir build
cd build

SET USD_LIB_VARIANT=PXR
SET LIBTURRET_ROOT=C:/packages/pg/prod/turret_lib/1.1.17
SET PYTHON_LIBS=C:/Python27/libs

SET LIBZMQ_ROOT=C:/packages/pg/prod/libzmq/4.3.2
SET LIBZMQ_INCLUDE_DIR=%LIBZMQ_ROOT%/include
SET LIBZMQ_LIB_DIR=%LIBZMQ_ROOT%/vs14_2015_x64/libzmq-v140-mt-4_3_2.lib

SET USD_ROOT=C:/USD_build
SET REZ_BOOST_ROOT=C:/packages/pg/prod/boost/1.61.0
SET REZ_TBB_ROOT=%USD_ROOT%/src/tbb2017_20170226oss
SET REZ_USD_ROOT=%USD_ROOT%
SET TBB_LIBRARIES=%USD_ROOT%/src/tbb2017_20170226oss/lib/intel64/vc14

cmake -DPC_LIBZMQ_LIBDIR:STRING=%LIBZMQ_ROOT% -DZeroMQ_LIBRARY:STRING=%LIBZMQ_LIB_DIR% -DPC_LIBZMQ_INCLUDE_DIRS:STRING=%LIBZMQ_INCLUDE_DIR% -DCMAKE_INSTALL_PREFIX="C:/packages/pg/prod/turret_usd/1.1.5" -G "Visual Studio 14 2015 Win64" ..
cmake --build . --config Release --target install -- /M:16

cd ..
