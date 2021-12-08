cmake_minimum_required(VERSION 3.0.0)
project(21Z-EADS-TASK1-SZACHNO-JAN VERSION 0.1.0)

add_executable(21Z-EADS-TASK1-SZACHNO-JAN main.cpp)

target_link_libraries(21Z-EADS-TASK1-SZACHNO-JAN PUBLIC gtest_main)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
SET(CMAKE_CXX_FLAGS  "-Wall -Wextra -Werror")
include(CPack)

include(FetchContent)
FetchContent_Declare(googletest GIT_REPOSITORY https://github.com/google/googletest.git GIT_TAG main)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    tests
    tests.cpp
)
target_link_libraries(
    tests
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
