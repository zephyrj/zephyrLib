add_library(core director/Amy.cpp
                 secretary/Aaron.cpp)
                 
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(test)