cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 14)

add_executable(massage_passing p.cpp c1.cpp c2.cpp preproccesor.h)


add_executable(p p.cpp)
target_link_libraries(p rt)