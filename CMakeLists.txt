cmake_minimum_required(VERSION 3.16)

set(NAME "taskmanager")
set(SOURCE "src/main.c")
set(DESCRIPTION "Example description")
set(BUILD "1.0.0")

project(${NAME}
	VERSION ${BUILD}
	DESCRIPTION ${DESCRIPTION}
	LANGUAGES C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_C_STANDARD 23)

add_subdirectory(lib/cJSON-1.7.18)

add_executable(${NAME} ${SOURCE})
