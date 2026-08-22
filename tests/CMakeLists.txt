add_executable(strings_tests strings_tests.cpp)
target_include_directories(strings_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_executable(number_tests number_tests.cpp)
target_include_directories(number_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_executable(hex_to_int_tests hex_to_int_tests.cpp)
target_include_directories(hex_to_int_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)

