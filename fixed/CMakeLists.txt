SET(INCS fixed.hpp integer_types.hpp promote_traits.hpp QXpr.hpp SimpleOptimizer.hpp XprOptimizer.hpp SimpleFiPU.hpp)

add_library(fixed ${INCS})

set_target_properties(fixed PROPERTIES LINKER_LANGUAGE CXX)