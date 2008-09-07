file(GLOB MainSrcs UnitTest++/src/*.cpp)
if(WIN32)
	file(GLOB OSSrcs UnitTest++/src/Win32/*.cpp)
else(WIN32)
	file(GLOB OSSrcs UnitTest++/src/Posix/*.cpp)
endif(WIN32)

set(SRCS ${MainSrcs} ${OSSrcs})
add_library(unittest++ ${SRCS})



include_directories(UnitTest++/src ${fixed_SOURCE_DIR}/fixed)

set(SRCS comparison.cpp construction.cpp main.cpp)
add_executable(unittests ${SRCS})
target_link_libraries(unittests unittest++)
