add_executable(strings_tests strings_tests.cpp)
add_executable(number_tests number_tests.cpp)

target_include_directories(strings_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(number_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)