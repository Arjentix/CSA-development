cmake_minimum_required(VERSION 3.10.2)

project(GetByIdRequestHandler_src)

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

# Adding Cat
set(
	CAT_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/../../Animals/Cat
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
	${CMAKE_CURRENT_SOURCE_DIR}/../../Animals/Dog
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
	${CMAKE_CURRENT_SOURCE_DIR}/../../Animals/Fox
)
if(NOT TARGET Fox)
	add_subdirectory(
		${FOX_INCLUDE_DIR}
		${CMAKE_CURRENT_BINARY_DIR}/Animals/Fox
	)
endif()

# ---------------------------------

set(SOURCE GetByIdRequestHandler.cpp)

add_library(GetByIdRequestHandler ${SOURCE})

set_target_properties(GetByIdRequestHandler PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS ON
)

target_include_directories(GetByIdRequestHandler PUBLIC
		${REQUEST_HANDLER_BASE_INCLUDE_DIR}
		${CAT_INCLUDE_DIR}
		${DOG_INCLUDE_DIR}
		${FOX_INCLUDE_DIR}
)
target_link_libraries(GetByIdRequestHandler
		RequestHandlerBase
		Cat
		Dog
		Fox
)
