cmake_minimum_required(VERSION 3.10.2)

project(AddNewRequestHandler_src)

# ------- Setting used libs -------

# Adding RequestHandlerBase
set(
	REQUEST_HANDLER_BASE_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/../RequestHandlerBase
)
if(NOT TARGET RequestHandlerBase)
	add_subdirectory(
		${REQUEST_HANDLER_BASE_INCLUDE_DIR}
		${CMAKE_CURRENT_BINARY_DIR}/RequestHandlerBase
	)
endif()

# Adding BuildAnimal
set(
	BUILD_ANIMAL_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/../../BuildAnimal
)
if(NOT TARGET BuildAnimal)
	add_subdirectory(
		${BUILD_ANIMAL_INCLUDE_DIR}
		${CMAKE_CURRENT_BINARY_DIR}/BuildAnimal
	)
endif()


# ---------------------------------

set(SOURCE AddNewRequestHandler.cpp)

add_library(AddNewRequestHandler ${SOURCE})

set_target_properties(AddNewRequestHandler PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS ON
)

target_include_directories(AddNewRequestHandler PUBLIC
		${REQUEST_HANDLER_BASE_INCLUDE_DIR}
		${BUILD_ANIMAL_INCLUDE_DIR}
)
target_link_libraries(AddNewRequestHandler
		RequestHandlerBase
		BuildAnimal
		nlohmann_json::nlohmann_json
)
