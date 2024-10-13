cmake_minimum_required(VERSION 3.10)
project(snake CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Iincludes -I/usr/include/freetype2 -I/usr/include/libpng16")

include_directories(includes)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
# Copy resource files and shaders to the build directory
file(COPY resources/ DESTINATION ${CMAKE_BINARY_DIR}/bin/resources)
file(COPY shaders/ DESTINATION ${CMAKE_BINARY_DIR}/bin/shaders)

set(SOURCES main.cpp utils/utils.cpp math/math.cpp utils/logger.cpp utils/text.cpp graphics/shader.cpp graphics/model.cpp graphics/render.cpp)

add_executable(snake ${SOURCES})

target_include_directories(snake PRIVATE ${GLEW_INCLUDE_DIRS})
target_link_libraries(snake GLFW GL GLEW m freetype)

set_target_properties(snake PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_custom_target(run
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR}/bin ./snake
    DEPENDS snake
)
