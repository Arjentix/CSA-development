cmake_minimum_required(VERSION 3.10.2)

project(animal_manager)

# Adding Animal
set(
	ANIMAL_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/../Animals/Animal
)
if(NOT TARGET Animal)
	add_subdirectory(${ANIMAL_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/Animal)
endif()

set(SOURCE_ANIMAL_MANAGER
		AnimalManager.cpp
)

add_library(AnimalManager ${SOURCE_ANIMAL_MANAGER})

set_target_properties(AnimalManager PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS ON
)

target_include_directories(AnimalManager PUBLIC
	${ANIMAL_INCLUDE_DIR}
)

target_link_libraries(AnimalManager
		Animal
)
