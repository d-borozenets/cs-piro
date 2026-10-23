cmake_minimum_required(VERSION 4.0)
project(lecutre9_part4 C)
find_package(MPI REQUIRED COMPONENTS C)

set(CMAKE_C_STANDARD 11)

add_executable(lecutre9_part4 main.c)
target_link_libraries(lecutre9_part4 PRIVATE MPI::MPI_C)
