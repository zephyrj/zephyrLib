add_library(core SHARED impl/director/Director.cpp
            impl/director/Amy.cpp
            impl/secretary/Secretary.cpp
            impl/secretary/Aaron.cpp
            impl/workshop/Workshop.cpp
            impl/workshop/ParentsGarage.cpp
            exception/Exception.cpp)
                 
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                PRIVATE ${Boost_INCLUDE_DIRS})

target_link_libraries(core PUBLIC pthread ${Boost_SYSTEM_LIBRARY})

add_subdirectory(test)