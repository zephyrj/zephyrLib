add_executable(psychTests tests.cpp)
target_link_libraries(psychTests PRIVATE catchMain psych)

add_test(psychTests psychTests -r junit -o JUNIT_RESULTS.xml)