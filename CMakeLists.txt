cmake_minimum_required(VERSION 3.16)
project(CppRayTracer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(RayTracer src/main.cpp)

if(MSVC)
    target_compile_options(RayTracer PRIVATE /W4 /O2 /pthread)
else()
    target_compile_options(RayTracer PRIVATE -Wall -Wextra -O3 -pthread)
endif()
