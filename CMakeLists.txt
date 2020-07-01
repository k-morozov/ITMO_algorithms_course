cmake_minimum_required(VERSION 3.5)
project(ITMO_course LANGUAGES CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

add_executable(${PROJECT_NAME} main.cpp)
find_package(Threads REQUIRED)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lstdc++fs -O3 -Wall -Wextra -pedantic")
set_target_properties(${PROJECT_NAME} PROPERTIES
                CXX_STANDARD 17
                CXX_STANDARD_REQUIRED ON
                LINK_LIBRARIES pthread
                COMPILE_OPTIONS "-std=c++17;-lstdc++fs;-O3;-Wall;-Wextra;-Wpedantic"
                )
target_link_libraries(${PROJECT_NAME} stdc++fs)

#install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
