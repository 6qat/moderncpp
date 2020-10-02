cmake_minimum_required(VERSION 3.17)
project(moderncpp)

#set(Boost_DIR D:\\dev\\boost-mingw\\lib\\cmake\\Boost-1.74.0)
set(Boost_DIR /home/guiga/Dev/boost/lib/cmake/Boost-1.74.0)
find_package(Boost REQUIRED COMPONENTS random filesystem )

set (rxcpp_INCLUDE_DIRS /home/guiga/Dev/rxcpp/include/rxcpp)
#find_package(rxcpp REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(moderncpp main.cpp random.hpp)
target_include_directories(moderncpp PRIVATE ${Boost_INCLUDE_DIRS} )
target_link_libraries(moderncpp ${Boost_LIBRARIES})

add_executable(c-poc creational-poc.cpp)
add_executable(c-lsp creational-lsp.cpp)
add_executable(c-isp creational-isp.cpp)
add_executable(c-dip creational-dip.cpp)

add_executable(constr constructors.cpp)
target_include_directories(constr PRIVATE ${Boost_INCLUDE_DIRS} )

add_executable(threads threads.cpp)
target_link_libraries(threads pthread)

add_executable(rx rx.cpp)
target_include_directories(rx PRIVATE ${rxcpp_INCLUDE_DIRS})
target_link_libraries(rx pthread)

if(Boost_Found)

endif()

