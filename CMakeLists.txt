cmake_minimum_required(VERSION 3.5.0)
project(HiImDadBot VERSION 0.1.0 LANGUAGES CXX)

# Set C++23 and create compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_TESTS "Enable tests" ON)

# Get the re2 library. However, re2 depends on Abseil so get that too
include(FetchContent)
set(ABSL_PROPAGATE_CXX_STD ON)
set(ABSL_ENABLE_INSTALL ON)
FetchContent_Declare(
   absl
   GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
   GIT_TAG        20240722.0
   OVERRIDE_FIND_PACKAGE)
FetchContent_MakeAvailable(absl)
FetchContent_Declare(
   re2
   GIT_REPOSITORY https://github.com/google/re2.git
   GIT_TAG        2024-07-02
   OVERRIDE_FIND_PACKAGE)
FetchContent_MakeAvailable(re2)

# D++ is required and should be installed separately
find_package(dpp REQUIRED)
find_package(re2 REQUIRED)

# Main executable
add_executable(HiImDadBot
   src/dad_bot.cpp
   src/message_listener.cpp
   src/main.cpp)

target_link_libraries(HiImDadBot
   PRIVATE
      dpp::dpp
      re2::re2)

if (ENABLE_TESTS)
   include(CTest)
   enable_testing()

   # Library used for testing
   add_library(HiImDadBot_library
      src/dad_bot.cpp
      src/message_listener.cpp)
   set_property(TARGET HiImDadBot_library PROPERTY CXX_STANDARD 23)
   target_link_libraries(HiImDadBot_library
      PRIVATE
         dpp::dpp
         re2::re2)

   add_subdirectory(tests)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
