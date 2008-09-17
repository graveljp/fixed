SET(INCS fixed.hpp integer_types.hpp promote_traits.hpp QXpr.hpp SimpleFiPU.hpp XprFiPU.hpp)

add_library(fixed ${INCS})

set_target_properties(fixed PROPERTIES LINKER_LANGUAGE CXX)