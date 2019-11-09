cmake_minimum_required(VERSION 3.10.2)

project(fox_src)

set(ANIMAL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../Animal)
if(NOT TARGET Animal)
	add_subdirectory(${ANIMAL_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/Animal)
endif()

set(SOURCE_FOX Fox.cpp)

add_library(Fox ${SOURCE_FOX})

target_include_directories(Fox PUBLIC ${ANIMAL_INCLUDE_DIR})
target_link_libraries(Fox Animal)
