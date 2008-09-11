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
if(MSVC_VERSION EQUAL 1500 OR MSVC_VERSION GREATER 1500)
    # Visual C++ 2008 has version number 1500 and deprecates 'strcpy'
    # This removes the deprecation warning in UnitTest++, an external lib
    set_target_properties(UnitTest++ PROPERTIES COMPILE_FLAGS "/wd 4996")
endif(MSVC_VERSION EQUAL 1500 OR MSVC_VERSION GREATER 1500)


include_directories(../../../externals/UnitTest++/src ${fixed_SOURCE_DIR}/fixed)

set(SRCS comparison.cpp construction.cpp main.cpp)
add_executable(unit_tests ${SRCS})
target_link_libraries(unit_tests UnitTest++)
