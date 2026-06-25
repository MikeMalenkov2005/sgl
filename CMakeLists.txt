cmake_minimum_required(VERSION 3.16)
project(sgl C)

set(CMAKE_C_STANDARD 90)

if (TARGET ${PROJECT_NAME})
  message(WARNING "${PROJECT_NAME} is included twice!")
else()
  file(GLOB SOURCES "src/*.c")
  add_library(${PROJECT_NAME} STATIC ${SOURCES})
  target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
endif()
