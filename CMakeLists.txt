cmake_minimum_required(VERSION 3.11.0...3.31.2)
project(HiImDadBot VERSION 0.1.0 LANGUAGES CXX)

# Set C++20 and create compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_TESTS "Enable tests" ON)

# Get some external libraries
include(FetchContent)

# Get the Abseil library as a dependency for the RE2 library
set(ABSL_PROPAGATE_CXX_STD ON)
set(ABSL_ENABLE_INSTALL ON)
FetchContent_Declare(
   absl
   GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
   GIT_TAG        20240722.0
   OVERRIDE_FIND_PACKAGE)
FetchContent_MakeAvailable(absl)

# Get the RE2 library
FetchContent_Declare(
   re2
   GIT_REPOSITORY https://github.com/google/re2.git
   GIT_TAG        2024-07-02
   OVERRIDE_FIND_PACKAGE)
FetchContent_MakeAvailable(re2)

# D++ is required and should be installed separately
find_package(dpp REQUIRED)
find_package(re2 REQUIRED)

# Make library of all source files
add_library(HiImDadBot_lib
   src/dad_bot.cpp
   src/message_listener.cpp
   src/slash_commands.cpp)
target_link_libraries(HiImDadBot_lib
   PRIVATE
      dpp::dpp
      re2::re2)

# Main executable
add_executable(HiImDadBot
   src/main.cpp)
target_link_libraries(HiImDadBot
   PRIVATE
      dpp::dpp
      re2::re2
      HiImDadBot_lib)

# Tests
if (ENABLE_TESTS)
   include(CTest)
   enable_testing()
   add_subdirectory(tests)
endif()

# Install package and CPack stuff
install(TARGETS HiImDadBot RUNTIME DESTINATION bin)

set(BUILD_TYPE $<CONFIG>)
set(CPACK_PROPERTIES_FILE "${CMAKE_BINARY_DIR}/${PROJECT_NAME}CPackProperties.cmake")
file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/${PROJECT_NAME}CPackProperties.cmake" #allows use of generator expression to retrieve CONFIG
      CONTENT "set(CPACK_PACKAGE_FILE_NAME ${PROJECT_NAME}-${PROJECT_VERSION}-\$\{CPACK_SYSTEM_NAME\}-${BUILD_TYPE}\)\n")
include(CPack)
