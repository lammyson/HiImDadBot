cmake_minimum_required(VERSION 3.5.0)
project(tests LANGUAGES CXX)

include(FetchContent)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_Declare(
   GTest
   GIT_REPOSITORY https://github.com/google/googletest.git
   GIT_TAG        main
   OVERRIDE_FIND_PACKAGE)
FetchContent_MakeAvailable(GTest)

add_executable(${PROJECT_NAME}
   dad_bot_test.cpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)

# TODO - Can this be automatically done or something?
target_include_directories(${PROJECT_NAME}
   PRIVATE
      ../src)

target_link_libraries(${PROJECT_NAME}
   PRIVATE
      GTest::gmock_main
      HiImDadBot_library)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
