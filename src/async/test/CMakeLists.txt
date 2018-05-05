add_executable(asyncTests tests.cpp)
target_link_libraries(asyncTests catchMain async)

add_test(asyncTests asyncTests -r junit -o JUNIT_RESULTS.xml)