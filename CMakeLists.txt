project(wide-integer)

cmake_minimum_required(VERSION 3.16.3)

find_package(Boost)
if (Boost_FOUND)
  include(CTest)

  add_subdirectory("examples")
  add_subdirectory("test")
endif()

add_library(WideInteger INTERFACE)
target_compile_features(WideInteger INTERFACE cxx_std_11)

target_include_directories(
  WideInteger INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>)
