add_library(psych SHARED impl/schema/Schema.cpp
                         impl/schema/GraphImpl.cpp)

target_include_directories(psych PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                 PRIVATE ${Boost_INCLUDE_DIRS})

target_link_libraries(psych PUBLIC pthread ${Boost_SYSTEM_LIBRARY})

add_subdirectory(test)