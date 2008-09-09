file(GLOB MainSrcs UnitTest++/src/*.cpp)
file(GLOB MainIncs UnitTest++/src/*.h)

if(WIN32)
	file(GLOB OSSrcs UnitTest++/src/Win32/*.cpp)
	file(GLOB OSIncs UnitTest++/src/Win32/*.h)
else(WIN32)
	file(GLOB OSSrcs UnitTest++/src/Posix/*.cpp)
	file(GLOB OSIncs UnitTest++/src/Posix/*.h)
endif(WIN32)

set(SRCS ${MainSrcs} ${OSSrcs})
set(INCS ${MainIncs} ${OSIncs})

add_library(unittest++ ${SRCS} ${INCS})

include_directories(UnitTest++/src ${fixed_SOURCE_DIR}/fixed)

set(SRCS comparison.cpp construction.cpp main.cpp)
add_executable(unittests ${SRCS})
target_link_libraries(unittests unittest++)
