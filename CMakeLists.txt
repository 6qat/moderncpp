cmake_minimum_required(VERSION 3.17)
project(moderncpp)

#set(Boost_DIR D:\\dev\\boost-mingw\\lib\\cmake\\Boost-1.74.0)
set(Boost_DIR /home/guiga/Dev/boost/lib/cmake/Boost-1.74.0)
find_package(Boost REQUIRED COMPONENTS random filesystem chrono regex thread fiber)

set(CMAKE_CXX_STANDARD 20)

add_executable(moderncpp main.cpp random.hpp)
target_include_directories(moderncpp PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(moderncpp ${Boost_LIBRARIES})

add_executable(c-poc creational-poc.cpp)
add_executable(c-lsp creational-lsp.cpp)
add_executable(c-isp creational-isp.cpp)
add_executable(c-dip creational-dip.cpp)

if(Boost_Found)

endif()

