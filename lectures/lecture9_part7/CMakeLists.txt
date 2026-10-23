cmake_minimum_required(VERSION 4.0)
project(lecture9_part7 C)
find_package(MPI REQUIRED COMPONENTS C)

set(CMAKE_C_STANDARD 11)

add_executable(lecture9_part7 main.c)
target_link_libraries(lecture9_part7 PRIVATE MPI::MPI_C)
