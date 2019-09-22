cmake_minimum_required(VERSION 3.10.2)

set(SOURCE server.cpp recv_send.h)

add_executable(server ${SOURCE})

set_target_properties(server PROPERTIES
			CMAKE_CXX_STANDARD 17
			CMAKE_CXX_STANDARD_REQUIRED ON
)
