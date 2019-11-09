cmake_minimum_required(VERSION 3.10.2)

project(ChangeRequestHandler_src)

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

# Adding Dog
set(
	DOG_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/../../Animals/Dog
)
if(NOT TARGET Dog)
	add_subdirectory(
		${DOG_INCLUDE_DIR}
		${CMAKE_CURRENT_BINARY_DIR}/Animals/Dog
	)
endif()

# ---------------------------------

set(SOURCE ChangeRequestHandler.cpp)

add_library(ChangeRequestHandler ${SOURCE})

set_target_properties(ChangeRequestHandler PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS ON
)

target_include_directories(ChangeRequestHandler PUBLIC
		${REQUEST_HANDLER_BASE_INCLUDE_DIR}
		${DOG_INCLUDE_DIR}
)
target_link_libraries(ChangeRequestHandler
		RequestHandlerBase
		Dog
)
