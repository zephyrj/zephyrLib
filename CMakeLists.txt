cmake_minimum_required(VERSION 3.8)
project(zephyrLib)

set(LINKTIME_OPTIMIZATION_FLAG "-flto")

set(CMAKE_CXX_STANDARD 17)
set(GCC_OPTION_FLAGS "-std=c++1z -fopenacc -fopenmp -fcilkplus -fgnu-tm -fvisibility-inlines-hidden -fdiagnostics-generate-patch ${LINKTIME_OPTIMIZATION_FLAG}")
set(GCC_WARNING_FLAGS "-Wall -Weffc++ -Wextra -Wnoexcept -Wformat -Wold-style-cast -Woverloaded-virtual -Wnull-dereference -Wimplicit-fallthrough -Wmissing-include-dirs -Wunused-parameter -Wuninitialized -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wsuggest-attribute=format -Wmissing-format-attribute  -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override -Walloc-zero -Wduplicated-branches -Wduplicated-cond -Wtrampolines -Wfloat-equal -Wshadow=compatible-local -Wpointer-arith -Wundef -Wcast-qual -Wcast-align -Wconversion -Wzero-as-null-pointer-constant -Wuseless-cast -Wmissing-declarations -Wpacked -Wredundant-decls -Wdisabled-optimization")
set(GCC_RELEASE_SPECIFIC_FLAGS "-ggdb3 -Og")
set(GCC_DEBUG_SPECIFIC_FLAGS "-ggdb3 -Og")

set(FUTURE_GCC_FLAGS "-fdiagnostics-show-template-tree -Wcatch-value=3 -Wextra-semi")

set(GCC_COMPILATION_FLAGS "${GCC_OPTION_FLAGS} ${GCC_WARNING_FLAGS} ${GCC_DEBUG_SPECIFIC_FLAGS}")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILATION_FLAGS}")

SET(BOOST_ROOT "/usr/local/boost/")
find_package( Boost REQUIRED system )

add_subdirectory(src/async)
add_subdirectory(src/comms)