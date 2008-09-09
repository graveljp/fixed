file(GLOB MainSrcs ../../../externals/UnitTest++/src/*.cpp)
file(GLOB MainIncs ../../../externals/UnitTest++/src/*.h)

if(WIN32)
	file(GLOB OSSrcs ../../../externals/UnitTest++/src/Win32/*.cpp)
	file(GLOB OSIncs ../../../externals/UnitTest++/src/Win32/*.h)
else(WIN32)
	file(GLOB OSSrcs ../../../externals/UnitTest++/src/Posix/*.cpp)
	file(GLOB OSIncs ../../../externals/UnitTest++/src/Posix/*.h)
endif(WIN32)

set(SRCS ${MainSrcs} ${OSSrcs})
set(INCS ${MainIncs} ${OSIncs})

add_library(UnitTest++ ${SRCS} ${INCS})

include_directories(../../../externals/UnitTest++/src ${fixed_SOURCE_DIR}/fixed)

set(SRCS comparison.cpp construction.cpp main.cpp)
add_executable(unit_tests ${SRCS})
target_link_libraries(unit_tests UnitTest++)
