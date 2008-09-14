set(SRCS comparison.cpp construction.cpp main.cpp)
add_executable(unit_tests ${SRCS})

include_directories(${fixed_SOURCE_DIR}/fixed)
