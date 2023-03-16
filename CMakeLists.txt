cmake_minimum_required(VERSION 3.22)
project(mywhs_demo C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

add_executable(mywhs_demo main.c)

include_directories(mywhs)
add_subdirectory(mywhs)
target_link_libraries(mywhs_demo mywhs)

add_subdirectory(tests)
