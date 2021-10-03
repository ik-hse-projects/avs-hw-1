cmake_minimum_required(VERSION 3.10)

project(AVS1)

set(SOURCE_FILES src/task.c
                 src/buffer.c
                 src/circle.c
                 src/color.c
                 src/point.c
                 src/rectangle.c
                 src/shape.c
                 src/task.c
                 src/triangle.c
                 src/vector.c)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
add_executable(AVS1 ${SOURCE_FILES})
target_link_libraries(AVS1 m -fsanitize=address -fsanitize=undefined)
