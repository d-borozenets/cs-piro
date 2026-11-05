cmake_minimum_required(VERSION 4.0)
project(lab15 C)
find_package(MPI REQUIRED COMPONENTS C)

set(CMAKE_C_STANDARD 11)

add_executable(lab15 main.c)
target_link_libraries(lab15 PRIVATE MPI::MPI_C)
