project(wide-integer)

cmake_minimum_required(VERSION 3.16.3)

add_subdirectory("examples")

include(CTest)
add_subdirectory("test")

add_library(wide-integer INTERFACE)
target_compile_features(wide-integer INTERFACE cxx_std_11)

target_include_directories(
  wide-integer INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>)
