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

# Adding BuildAnimal
set(
	BUILD_ANIMAL_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/../BuildAnimal
)
if(NOT TARGET BuildAnimal)
	add_subdirectory(${BUILD_ANIMAL_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/BuildAnimal)
endif()

# Adding Logger
set(
	LOGGER_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/../Logger
)
if(NOT TARGET Logger)
	add_subdirectory(${LOGGER_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/Logger)
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
	${BUILD_ANIMAL_INCLUDE_DIR}
	${LOGGER_INCLUDE_DIR}
)

target_link_libraries(AnimalManager
		Animal
		BuildAnimal
		Logger
)
