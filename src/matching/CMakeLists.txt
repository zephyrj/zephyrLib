add_custom_command(OUTPUT AssertionType.pb.h
                          AssertionType.pb.cc
                          ConjunctionType.pb.h
                          ConjunctionType.pb.cc
                   COMMAND protoc
                           -I ${CMAKE_CURRENT_SOURCE_DIR}
                           --cpp_out=${CMAKE_CURRENT_BINARY_DIR}
                           ${CMAKE_CURRENT_SOURCE_DIR}/AssertionType.proto
                           ${CMAKE_CURRENT_SOURCE_DIR}/ConjunctionType.proto
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/AssertionType.proto
                           ${CMAKE_CURRENT_SOURCE_DIR}/ConjunctionType.proto)

add_library(matching AssertionType.pb.cc
                     ConjunctionType.pb.cc)

target_link_libraries(matching PUBLIC protobuf)

target_include_directories(matching PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                           ${CMAKE_CURRENT_BINARY_DIR})