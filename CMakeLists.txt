cmake_minimum_required(VERSION 3.14)
project(rower)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()

include_directories(
    src
)


add_executable(
  rower_test
  src/rower.cpp
  src/jsonPresenter.cpp
  test/jsonPresenter_test.cc
  test/rower_test.cc
)


target_link_libraries(
  rower_test
  gmock
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(rower_test)
