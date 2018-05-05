set(FRAMEWORK_SOURCE_FILES framework/Framework.cpp
                           framework/Component.cpp)

set(ASYNC_LIBRARY_SOURCE_FILES ${FRAMEWORK_SOURCE_FILES})

add_library(async SHARED ${ASYNC_LIBRARY_SOURCE_FILES})
target_link_libraries(async ${Boost_SYSTEM_LIBRARY} pthread ${Boost_THREAD_LIBRARY})
target_include_directories(async SYSTEM PUBLIC ${Boost_INCLUDE_DIR})
target_include_directories(async PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/src/common)

add_subdirectory(test)
add_subdirectory(framework/test)