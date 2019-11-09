cmake_minimum_required(VERSION 3.10.2)

set(ANIMAL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../Animal)
if(NOT TARGET Animal)
	add_subdirectory(${ANIMAL_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/Animal)
endif()

project(dog_src)

set(SOURCE_DOG Dog.cpp)

add_library(Dog ${SOURCE_DOG})

target_include_directories(Dog PUBLIC ${ANIMAL_INCLUDE_DIR})
target_link_libraries(Dog Animal)
