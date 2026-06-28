cmake_minimum_required(VERSION 3.16)
project(sgl C)

set(CMAKE_C_STANDARD 90)

if (TARGET ${PROJECT_NAME})
  message(WARNING "${PROJECT_NAME} is included twice!")
else()
  add_subdirectory("external/glad" EXCLUDE_FROM_ALL)
  add_subdirectory("external/glfw" EXCLUDE_FROM_ALL)

  file(GLOB SGL_SOURCES "src/*.c")
  add_library(${PROJECT_NAME} STATIC ${SGL_SOURCES})
  target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw)
  target_include_directories(${PROJECT_NAME}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>
    PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/external/stb>
  )
  target_compile_definitions(${PROJECT_NAME}
    PUBLIC _CRT_SECURE_NO_WARNINGS _USE_MATH_DEFINES
  )
endif()
