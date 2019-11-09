cmake_minimum_required(VERSION 3.10.2)

project(GetByTypeRequestHandler_src)

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

# ---------------------------------

set(SOURCE GetByTypeRequestHandler.cpp)

add_library(GetByTypeRequestHandler ${SOURCE})

set_target_properties(GetByTypeRequestHandler PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS ON
)

target_include_directories(GetByTypeRequestHandler PUBLIC
		${REQUEST_HANDLER_BASE_INCLUDE_DIR}
)
target_link_libraries(GetByTypeRequestHandler
		RequestHandlerBase
)
