cmake_minimum_required(VERSION 3.10.2)

project(animal_src)

# Adding json
set(
	JSON_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/../../json
)
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")
if(NOT TARGET nlohmann_json::nlohmann_json)
	add_subdirectory(
		${JSON_INCLUDE_DIR}
		${CMAKE_CURRENT_BINARY_DIR}/json
	)
endif()

set(SOURCE_ANIMAL Animal.cpp)

add_library(Animal ${SOURCE_ANIMAL})

target_include_directories(Animal PUBLIC
		${JSON_INCLUDE_DIR}
)

target_link_libraries(Animal
		nlohmann_json::nlohmann_json
)
