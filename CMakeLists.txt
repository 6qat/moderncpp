cmake_minimum_required(VERSION 3.17)
project(untitled1)

set(Boost_DIR D:\\dev\\boost-msvc\\lib\\cmake\\Boost-1.74.0)
find_package(Boost REQUIRED COMPONENTS filesystem chrono regex thread fiber)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled1 main.cpp random.hpp)
target_include_directories(untitled1 PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(untitled1 ${Boost_LIBRARIES})

if(Boost_Found)

endif()

