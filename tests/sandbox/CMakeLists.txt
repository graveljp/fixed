#SET(Boost_USE_STATIC_LIBS ON)
#SET(Boost_USE_MULTITHREAD OFF)
#find_package(Boost REQUIRED)

#include_directories(${Boost_INCLUDE_DIR} ${fixed_SOURCE_DIR}/fixed)
#link_directories(${Boost_LIBRARY_DIRS})

include_directories(${fixed_SOURCE_DIR}/fixed)

set(SRCS main.cpp)
add_executable(sandbox ${SRCS})