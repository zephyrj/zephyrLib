add_executable(asyncFrameworkTests tests.cpp)
target_link_libraries(asyncFrameworkTests catchMain async)

add_test(asyncFrameworkTests asyncFrameworkTests -r junit -o JUNIT_RESULTS.xml)