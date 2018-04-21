cmake_minimum_required(VERSION 3.10)
project(zephyrLib)

include(CheckCXXCompilerFlag)
include(CheckIPOSupported)

set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/externalProjects)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmakeModules)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_RELEASE "-ggdb3 -Og")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -Og")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
# clang compiler options
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility-inlines-hidden ")

    CHECK_CXX_COMPILER_FLAG("-fdiagnostics-generate-patch" GCC7_OPTIONS_SUPPORTED)
    if (GCC7_OPTIONS_SUPPORTED)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-generate-patch")
    endif()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Weffc++ -Wextra -Wnoexcept -Wformat -Wold-style-cast -Woverloaded-virtual -Wmissing-include-dirs -Wunused-parameter -Wuninitialized -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wsuggest-attribute=format -Wmissing-format-attribute  -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override  -Wtrampolines -Wfloat-equal -Wpointer-arith -Wundef -Wcast-qual -Wcast-align -Wconversion -Wzero-as-null-pointer-constant -Wuseless-cast -Wmissing-declarations -Wpacked -Wredundant-decls -Wdisabled-optimization")

    CHECK_CXX_COMPILER_FLAG("-Wnull-dereference" GCC7_WARNINGS_SUPPORTED)
    if (GCC7_WARNINGS_SUPPORTED)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnull-dereference -Wimplicit-fallthrough -Walloc-zero -Wduplicated-branches -Wduplicated-cond  -Wshadow=compatible-local")
    endif()

    set(FUTURE_GCC_FLAGS "-fdiagnostics-show-template-tree -Wcatch-value=3 -Wextra-semi")
endif()

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
if(OpenMP_CXX_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

find_package(OpenACC)
if(OpenACC_CXX_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenACC_CXX_FLAGS}")
endif()

add_subdirectory(src/async)
add_subdirectory(src/comms)