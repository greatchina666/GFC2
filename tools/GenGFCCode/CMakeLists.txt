﻿cmake_minimum_required(VERSION 2.8)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/../../lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/../../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/../../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/../../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/../../bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/../../bin)
#set(CMAKE_DEBUG_POSTFIX d)

project(GenGFCCode)

include_directories(
	${PROJECT_SOURCE_DIR}/../../thirdparty/tinyxml
	${PROJECT_SOURCE_DIR}/../../src/EntitySchema
	${PROJECT_SOURCE_DIR}/../../src/GfcCommon
	)
link_directories(${CMAKE_SOURCE_DIR}/../../lib)

FILE(GLOB SRC_FILES "./*.c*") 
FILE(GLOB HEAD_FILES "./*.h") 

add_compile_definitions("TIXML_USE_STL" "_CRT_SECURE_NO_DEPRECATE")

#创建工程文件
add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEAD_FILES})

#set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX d)

target_link_libraries(${PROJECT_NAME} debug tinyxmld optimized tinyxml)
target_link_libraries(${PROJECT_NAME} debug EntitySchemad optimized EntitySchema)
target_link_libraries(${PROJECT_NAME} debug GfcCommond optimized GfcCommon)