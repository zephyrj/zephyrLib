add_library(core SHARED impl/director/Director.cpp
                        impl/director/Amy.cpp
                        impl/secretary/Secretary.cpp
                        impl/secretary/Aaron.cpp
                        impl/workshop/Workshop.cpp
                        impl/workshop/ParentsGarage.cpp)
                 
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                PRIVATE ${Boost_INCLUDE_DIRS})

add_subdirectory(test)