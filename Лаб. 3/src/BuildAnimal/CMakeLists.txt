cmake_minimum_required(VERSION 3.10.2)

project(BuildAnimal_src)

# ------- Setting used libs -------

# Adding Cat
set(
	CAT_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/../Animals/Cat
)
if(NOT TARGET Cat)
	add_subdirectory(
		${CAT_INCLUDE_DIR}
		${CMAKE_CURRENT_BINARY_DIR}/Animals/Cat
	)
endif()

# Adding Dog
set(
	DOG_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/../Animals/Dog
)
if(NOT TARGET Dog)
	add_subdirectory(
		${DOG_INCLUDE_DIR}
		${CMAKE_CURRENT_BINARY_DIR}/Animals/Dog
	)
endif()

# Adding Fox
set(
	FOX_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/../Animals/Fox
)
if(NOT TARGET Fox)
	add_subdirectory(
		${FOX_INCLUDE_DIR}
		${CMAKE_CURRENT_BINARY_DIR}/Animals/Fox
	)
endif()

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

# ---------------------------------

set(SOURCE BuildAnimal.cpp)

add_library(BuildAnimal ${SOURCE})

set_target_properties(BuildAnimal PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS ON
)

target_include_directories(BuildAnimal PUBLIC
		${CAT_INCLUDE_DIR}
		${DOG_INCLUDE_DIR}
		${FOX_INCLUDE_DIR}
		${JSON_INCLUDE_DIR}
)
target_link_libraries(BuildAnimal
		Cat
		Dog
		Fox
		nlohmann_json::nlohmann_json
)
