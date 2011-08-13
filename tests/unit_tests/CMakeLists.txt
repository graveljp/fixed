set(SRCS comparison.cpp construction.cpp main.cpp multiplication.cpp)
add_executable(unit_tests ${SRCS})

include_directories(${fixed_SOURCE_DIR}/fixed)

add_definitions( -DFIXED_DEBUG_MODE )