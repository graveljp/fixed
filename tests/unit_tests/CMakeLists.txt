set(SRCS comparison.cpp construction.cpp main.cpp multiplication.cpp utilities.impl.h)
set(INCS utilities.h)

add_executable(unit_tests ${SRCS} ${INCS})

include_directories(${fixed_SOURCE_DIR}/fixed)

add_definitions( -DFIXED_DEBUG_MODE )

set_target_properties(unit_tests PROPERTIES COMPILE_FLAGS /MP)