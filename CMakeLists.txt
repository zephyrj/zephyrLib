cmake_minimum_required(VERSION 3.9)
project(zephyrLib)

set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/externalProjects)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmakeModules)

set(CMAKE_CXX_STANDARD 17)
set(GCC_OPTION_FLAGS "-std=c++1z -fopenacc -fvisibility-inlines-hidden -fdiagnostics-generate-patch")
set(GCC_WARNING_FLAGS "-Wall -Weffc++ -Wextra -Wnoexcept -Wformat -Wold-style-cast -Woverloaded-virtual -Wnull-dereference -Wimplicit-fallthrough -Wmissing-include-dirs -Wunused-parameter -Wuninitialized -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wsuggest-attribute=format -Wmissing-format-attribute  -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override -Walloc-zero -Wduplicated-branches -Wduplicated-cond -Wtrampolines -Wfloat-equal -Wshadow=compatible-local -Wpointer-arith -Wundef -Wcast-qual -Wcast-align -Wconversion -Wzero-as-null-pointer-constant -Wuseless-cast -Wmissing-declarations -Wpacked -Wredundant-decls -Wdisabled-optimization")
set(GCC_RELEASE_SPECIFIC_FLAGS "-ggdb3 -Og")
set(GCC_DEBUG_SPECIFIC_FLAGS "-ggdb3 -Og")

set(FUTURE_GCC_FLAGS "-fdiagnostics-show-template-tree -Wcatch-value=3 -Wextra-semi")

set(GCC_COMPILATION_FLAGS "${GCC_OPTION_FLAGS} ${GCC_WARNING_FLAGS} ${GCC_DEBUG_SPECIFIC_FLAGS}")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILATION_FLAGS}")

include(CheckIPOSupported)
check_ipo_supported(RESULT supported OUTPUT error)
if( supported )
    message(STATUS "IPO / LTO enabled")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
    message(STATUS "IPO / LTO not supported: <${error}>")
endif()

# Includes Catch in the project:
add_subdirectory(${EXT_PROJECTS_DIR}/catch)
include_directories(${CATCH_INCLUDE_DIR} ${COMMON_INCLUDES})
enable_testing(true)  # Enables unit-testing.

SET(BOOST_ROOT "/usr/local/boost/")
find_package( Boost REQUIRED system )

find_package(OpenMP)
if(OpenMP_C_FOUND)
    if(OpenMP_CXX_FOUND)
        set(GCC_OPTION_FLAGS "${GCC_OPTION_FLAGS} ${OpenMP_CXX_FLAGS}")
    endif()
endif()

add_subdirectory(src/async)
add_subdirectory(src/comms)