cmake_minimum_required(VERSION 3.17)
project(moderncpp)

set(Boost_DIR D:\\dev\\boost-msvc\\lib\\cmake\\Boost-1.74.0)
find_package(Boost REQUIRED COMPONENTS random filesystem chrono regex thread fiber)

set(CMAKE_CXX_STANDARD 17)

add_executable(moderncpp main.cpp random.hpp)
target_include_directories(moderncpp PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(moderncpp ${Boost_LIBRARIES})

if(Boost_Found)

endif()

