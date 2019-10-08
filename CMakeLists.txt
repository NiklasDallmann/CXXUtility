 cmake_minimum_required(VERSION 3.15)

 project(cxxutility LANGUAGES CXX)
 
 # Output directories
 set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
 set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
 set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
 
 # Compiler flags
 set(CMAKE_CXX_STANDARD 17)
 set(CMAKE_CXX_FLAGS_RELEASE "-O3 -flto -march=native -mtune=native")
 set(CMAKE_CXX_FLAGS_DEBUG "-g")

 # Installation settings
 set(CMAKE_SKIP_BUILD_RPATH FALSE)
 set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
 set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
 set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib/toypt)
 
 set(CXXUTILITY_PUBLIC_HEADERS
	 "include/cxxutility/debugstream.h"
	 "include/cxxutility/globals.h")
 
 set(CXXUTILITY_SOURCES
	 "src/debugstream.cpp")
 
 # Targets
 # Utility library
 add_library(${PROJECT_NAME} SHARED ${CXXUTILITY_SOURCES} ${CXXUTILITY_PUBLIC_HEADERS})
	
 target_include_directories(${PROJECT_NAME}
	 PUBLIC
		 $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/cxxutility>)

# Installation
install(TARGETS			${PROJECT_NAME}
		LIBRARY			DESTINATION		${CMAKE_INSTALL_PREFIX}/lib)

install(DIRECTORY		${CMAKE_CURRENT_SOURCE_DIR}/include
		DESTINATION		${CMAKE_INSTALL_PREFIX}/include)
