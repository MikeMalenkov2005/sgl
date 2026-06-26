find_package(OpenGL REQUIRED)

add_library(glad STATIC "src/glad.c")

target_link_libraries(glad OpenGL::GL)

target_include_directories(glad PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
