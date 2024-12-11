cmake_minimum_required(VERSION 3.11.0...3.31.2)
project(tests LANGUAGES CXX)

# Get some dependencies
include(FetchContent)

# googletest library for the testing framework
set(gtest_force_shared_crt ON)
FetchContent_Declare(
   GTest
   GIT_REPOSITORY https://github.com/google/googletest.git
   GIT_TAG        main
   OVERRIDE_FIND_PACKAGE)
FetchContent_MakeAvailable(GTest)

# tests executable
add_executable(${PROJECT_NAME}
   dad_bot_test.cpp)
target_include_directories(${PROJECT_NAME}
   PRIVATE
      ../src)
target_link_libraries(${PROJECT_NAME}
   PRIVATE
      GTest::gmock_main
      HiImDadBot_lib)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
