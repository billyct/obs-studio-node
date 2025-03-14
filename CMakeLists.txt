﻿cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

IF(CLANG_ANALYZE_CONFIG)
	set(CMAKE_C_COMPILER_WORKS 1)
	set(CMAKE_CXX_COMPILER_WORKS 1)
	
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xclang -fexceptions -Xclang -fcxx-exceptions")
ENDIF()

set(VERSION_FULL 0.3.21)
set(VERSION_BUILD 0)

project(obs-studio-node VERSION ${VERSION_FULL}.${VERSION_BUILD})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# CppCheck
IF( NOT CLANG_ANALYZE_CONFIG)
	include(cppcheck)

	cppcheck(EXCLUDE "${PROJECT_SOURCE_DIR}/node_modules")
ENDIF()

if(WIN32)
	# Resource VersionInfo
	set(PROJECT_PRODUCT_NAME "OBS Studio for Node.JS")
	set(PROJECT_COMPANY_NAME "Streamlabs")
	set(PROJECT_COPYRIGHT "Streamlabs © 2017 - 2018")
	set(PROJECT_LEGAL_TRADEMARKS_1 "")
	set(PROJECT_LEGAL_TRADEMARKS_2 "")

	configure_file(
		${PROJECT_SOURCE_DIR}/cmake/version.rc.in
		${PROJECT_BINARY_DIR}/version.rc
		@ONLY
	)

	# ToDo: Figure out a better way to tell the test setup where to find our binaries.
	configure_file(
		${PROJECT_SOURCE_DIR}/cmake/obs.js.in
		${PROJECT_SOURCE_DIR}/tests/helpers/obs.js
		@ONLY
	)
endif()

configure_file(
	${PROJECT_SOURCE_DIR}/cmake/index.ts.in
	${PROJECT_SOURCE_DIR}/tests/osn-tests/osn/index.ts
	@ONLY
)

############################
# Setup global dependencies
############################

include(ExternalProject)
include(DownloadProject)
include(FetchContent)

if(MSVC)
	add_definitions(/MP)
	add_link_options(/debug:fastlink)
endif()

if (WIN32)
	# Override a test flag
	set(StackWalker_DISABLE_TESTS true CACHE BOOL "" FORCE)

	# StackWalker (Callstack rewind
	FetchContent_Declare(
	stackwalker
	GIT_REPOSITORY https://github.com/stream-labs/StackWalker
	)

	FetchContent_GetProperties(stackwalker)
	if(NOT stackwalker_POPULATED)
	FetchContent_Populate(stackwalker)
	add_subdirectory(${stackwalker_SOURCE_DIR} ${stackwalker_BINARY_DIR})
	endif()
endif()

# Nlohmann JSON (modern JSON for C++)
FetchContent_Declare(
  nlohmannjson
  GIT_REPOSITORY https://github.com/nlohmann/json
  GIT_TAG        aa0e847e5b57a00696bdcb6a834b927231b81613 # v3.10.3
)

FetchContent_GetProperties(nlohmannjson)
if(NOT nlohmannjson_POPULATED)
  FetchContent_Populate(nlohmannjson)
endif()

add_subdirectory(lib-streamlabs-ipc)
add_subdirectory(obs-studio-client)
add_subdirectory(obs-studio-server)

include(CPack)