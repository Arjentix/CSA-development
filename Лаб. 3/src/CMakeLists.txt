cmake_minimum_required(VERSION 3.10.2)

project(animal_store_src)

# ------ Adding dependencies --------

# Adding RequestHandlerBase
set(
	REQUEST_HANDLER_BASE_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/RequestHandlers/RequestHandlerBase/
)
if(NOT TARGET RequestHandler)
	add_subdirectory(${REQUEST_HANDLER_BASE_INCLUDE_DIR})
endif()

# Adding HTTPHandler
set(
	HTTP_HANDLER_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/HTTPHandler
)
if(NOT TARGET HTTPHandler)
	add_subdirectory(${HTTP_HANDLER_INCLUDE_DIR})
endif()

# Adding HTTPServer
set(
	HTTP_SERVER_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/HTTPServer
)
if(NOT TARGET HTTPServer)
	add_subdirectory(${HTTP_SERVER_INCLUDE_DIR})
endif()

# Adding AnimalManager
set(
	ANIMAL_MANAGER_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/AnimalManager
)
if(NOT TARGET AnimalManager)
	add_subdirectory(${ANIMAL_MANAGER_INCLUDE_DIR})
endif()

# Adding AddNewRequestHandler
set(
	ADD_NEW_REQUEST_HANDLER_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/RequestHandlers/AddNewRequestHandler
)
if(NOT TARGET AddNewRequestHandler)
	add_subdirectory(${ADD_NEW_REQUEST_HANDLER_INCLUDE_DIR})
endif()

# Adding ChangeRequestHandler
set(
	CHANGE_REQUEST_HANDLER_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/RequestHandlers/ChangeRequestHandler
)
if(NOT TARGET ChangeRequestHandler)
	add_subdirectory(${CHANGE_REQUEST_HANDLER_INCLUDE_DIR})
endif()

# Adding PurchaseRequestHandler
set(
	PURCHASE_REQUEST_HANDLER_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/RequestHandlers/PurchaseRequestHandler
)
if(NOT TARGET PurchaseRequestHandler)
	add_subdirectory(${PURCHASE_REQUEST_HANDLER_INCLUDE_DIR})
endif()

# Adding ShowAllRequestHandler
set(
	SHOW_ALL_REQUEST_HANDLER_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/RequestHandlers/ShowAllRequestHandler
)
if(NOT TARGET ShowAllRequestHandler)
	add_subdirectory(${SHOW_ALL_REQUEST_HANDLER_INCLUDE_DIR})
endif()

# Adding GetByIdRequestHandler
set(
	GET_BY_ID_REQUEST_HANDLER_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/RequestHandlers/GetByIdRequestHandler
)
if(NOT TARGET GetByIdRequestHandler)
	add_subdirectory(${GET_BY_ID_REQUEST_HANDLER_INCLUDE_DIR})
endif()

# Adding GetByTypeRequestHandler
set(
	GET_BY_TYPE_REQUEST_HANDLER_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/RequestHandlers/GetByTypeRequestHandler
)
if(NOT TARGET GetByTypeRequestHandler)
	add_subdirectory(${GET_BY_TYPE_REQUEST_HANDLER_INCLUDE_DIR})
endif()

# Adding Logger
set(
	LOGGER_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/Logger
)
if(NOT TARGET Logger)
	add_subdirectory(${LOGGER_INCLUDE_DIR})
endif()

# Adding nlohmann/detail/exceptions.cpp
set(
	JSON_EXCEPTIONS_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/json/include
)

# Searching for Threads lib
find_package(Threads REQUIRED)

# -------------------------


set(SOURCE_EXE
		main.cpp
		ClientHandler.cpp
)

add_executable(AnimalStore ${SOURCE_EXE})

set_target_properties(AnimalStore PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS ON
)

target_include_directories(AnimalStore PRIVATE
		${REQUEST_HANDLER_BASE_INCLUDE_DIR}
		${HTTP_SERVER_INCLUDE_DIR}
		${ADD_NEW_REQUEST_HANDLER_INCLUDE_DIR}
		${CHANGE_REQUEST_HANDLER_INCLUDE_DIR}
		${PURCHASE_REQUEST_HANDLER_INCLUDE_DIR}
		${SHOW_ALL_REQUEST_HANDLER_INCLUDE_DIR}
		${GET_BY_ID_REQUEST_HANDLER_INCLUDE_DIR}
		${GET_BY_TYPE_REQUEST_HANDLER_INCLUDE_DIR}
		${LOGGER_INCLUDE_DIR}
		${JSON_EXCEPTIONS_INCLUDE_DIR}
)

target_link_libraries(AnimalStore
		${CMAKE_THREAD_LIBS_INIT}
		RequestHandlerBase
		HTTPHandler
		HTTPServer
		AddNewRequestHandler
		ChangeRequestHandler
		PurchaseRequestHandler
		ShowAllRequestHandler
		GetByIdRequestHandler
		GetByTypeRequestHandler
		Logger
)

# Installing
install(TARGETS AnimalStore DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../bin)
