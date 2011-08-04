cmake_minimum_required(VERSION 2.8)
project(fixed)

SET(EXTERNALS_ROOT ../externals)
SET(BOOST_ROOT ${EXTERNALS_ROOT}/Boost_1_46_1)

SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_USE_MULTITHREAD OFF)
FIND_PACKAGE( Boost 1.46.1 )

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

add_subdirectory(tests)
add_subdirectory(fixed)