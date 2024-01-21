cmake_minimum_required(VERSION 3.10)
project(snake C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Iincludes")

include_directories(includes)
# Copy resource files and shaders to the build directory
file(COPY resources/ DESTINATION ${CMAKE_BINARY_DIR}/bin/resources)
file(COPY shaders/ DESTINATION ${CMAKE_BINARY_DIR}/bin/shaders)

set(SOURCES main.c utils/utils.c math/math.c utils/logger.c graphics/shader.c graphics/model.c graphics/render.c)

add_executable(snake ${SOURCES})

target_link_libraries(snake glfw GL GLEW m)

set_target_properties(snake PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_custom_target(run COMMAND "${CMAKE_BINARY_DIR}/bin/snake")