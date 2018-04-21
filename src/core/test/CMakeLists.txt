add_executable(coreFrameworkTests tests.cpp)
target_link_libraries(coreFrameworkTests PRIVATE catchMain core)

add_test(coreFrameworkTests coreFrameworkTests -r junit -o JUNIT_RESULTS.xml)