cmake_minimum_required(VERSION 2.8)
project(zephyrLib)

set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/externalProjects)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmakeModules)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS_RELEASE "-ggdb3 -Og")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -Og")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Weffc++")

# Includes Catch in the project:
add_subdirectory(${EXT_PROJECTS_DIR}/catch)
include_directories(${CATCH_INCLUDE_DIR} ${COMMON_INCLUDES})
enable_testing(true)  # Enables unit-testing.

SET(BOOST_ROOT "/usr/local/boost/")
find_package( Boost REQUIRED system thread )

message("Found boost include directory: ${Boost_INCLUDE_DIRS}")
message("Found boost system library: ${Boost_SYSTEM_LIBRARY}")
message("Found boost thread library: ${Boost_THREAD_LIBRARY}")


add_subdirectory(src/async)
add_subdirectory(src/comms)
add_subdirectory(src/core)
add_subdirectory(src/psych)
