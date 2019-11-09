cmake_minimum_required(VERSION 3.10.2)

project(cat_src)

set(ANIMAL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../Animal)
if(NOT TARGET Animal)
	add_subdirectory(${ANIMAL_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/Animal)
endif()

set(SOURCE_CAT Cat.cpp)

add_library(Cat ${SOURCE_CAT})

target_include_directories(Cat PUBLIC ${ANIMAL_INCLUDE_DIR})
target_link_libraries(Cat Animal)
