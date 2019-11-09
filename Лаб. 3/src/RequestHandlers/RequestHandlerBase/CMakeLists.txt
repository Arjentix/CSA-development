cmake_minimum_required(VERSION 3.10.2)

project(request_handlers)

# Adding HTTPHandler
set(
	HTTPHANDLER_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/../../HTTPHandler
)
if(NOT TARGET HTTPHandler)
	add_subdirectory(${HTTPHANDLER_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/HTTPHandler)
endif()

# Adding Animal
set(
	ANIMAL_MANAGER_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/../../AnimalManager
)
if(NOT TARGET Animal)
	add_subdirectory(${ANIMAL_MANAGER_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/AnimalManager)
endif()


set(SOURCE_REQUEST_HANDLER_BASE
		RequestHandlerBase.cpp
)

add_library(RequestHandlerBase ${SOURCE_REQUEST_HANDLER_BASE})

set_target_properties(RequestHandlerBase PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS ON
)

target_include_directories(RequestHandlerBase PUBLIC
	${HTTPHANDLER_INCLUDE_DIR}
	${ANIMAL_MANAGER_INCLUDE_DIR}
)

target_link_libraries(RequestHandlerBase
		HTTPHandler
		AnimalManager
)
