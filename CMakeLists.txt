cmake_minimum_required(VERSION 3.15)

project(cxxutility
	LANGUAGES									CXX
	VERSION										0.1.0)

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY				"${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY				"${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY				"${CMAKE_CURRENT_SOURCE_DIR}/bin")

# Compiler flags
set(CMAKE_CXX_STANDARD							17)

if(UNIX)
	set(CMAKE_CXX_FLAGS_RELEASE						"-O3 -flto -march=native -mtune=native")
	set(CMAKE_CXX_FLAGS_DEBUG						"-g")
elseif(MSVC)
else()
	message(FATAL_ERROR "Unsupported platform")
endif()


# Installation settings
set(CMAKE_SKIP_BUILD_RPATH						FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH				TRUE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH			TRUE)
#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS			TRUE)

set(CXXUTILITY_PUBLIC_HEADERS
	"include/cxxutility/debugstream.h"
	"include/cxxutility/definitions.h"
	"include/cxxutility/test.h"
	"include/cxxutility/sfinae.h")

set(CXXUTILITY_SOURCES
	"src/debugstream.cpp"
	"src/test.cpp")

if(UNIX)
	set(CXXUTILITY_LIBRARY_DESTINATION				"${CMAKE_INSTALL_PREFIX}/lib")
	set(CXXUTILITY_HEADER_DESTINATION				"${CMAKE_INSTALL_PREFIX}/include/cxxutility")
	set(CXXUTILITY_CMAKE_DIRECTORY					"${CMAKE_INSTALL_PREFIX}/lib/cmake/cxxutility")
elseif(MSVC)
	set(CXXUTILITY_LIBRARY_DESTINATION				"lib")
	set(CXXUTILITY_HEADER_DESTINATION				"include/cxxutility")
	set(CXXUTILITY_CMAKE_DIRECTORY					"lib/cmake/cxxutility")
endif()

set(CXXUTILITY_TARGETS								"${PROJECT_NAME}Targets")

# Targets
# Utility library
if(UNIX)
	add_library(${PROJECT_NAME} SHARED ${CXXUTILITY_SOURCES} ${CXXUTILITY_PUBLIC_HEADERS})
elseif(MSVC)
	add_library(${PROJECT_NAME} STATIC ${CXXUTILITY_SOURCES} ${CXXUTILITY_PUBLIC_HEADERS})
endif()

target_include_directories(${PROJECT_NAME}
	PUBLIC										$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
												$<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>)

# Package
set(CPACK_PACKAGE_NAME							"CXXUtility")
set(CPACK_PACKAGE_VENDOR						"Niklas Dallmann")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY			"C++ utility library")
set(CPACK_PACKAGE_VERSION						${PROJECT_VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR					${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR					${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH					${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE					"${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README					"${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_SOURCE_IGNORE_FILES
	"/.git"
	"/bin"
	"/lib"
	".gitignore"
	"CMakeLists.txt.user"
	"CMakeLists.txt.autosave")

if(UNIX)
	set(CPACK_SOURCE_GENERATOR					"TGZ")
elseif(MSVC)
	set(CPACK_SOURCE_GENERATOR					"NSIS")
	set(CPACK_PACKAGE_INSTALL_DIRECTORY			${PROJECT_NAME})
endif()

# Installation
install(TARGETS									${PROJECT_NAME}
		EXPORT									${CXXUTILITY_TARGETS}
		INCLUDES DESTINATION					"${CXXUTILITY_HEADER_DESTINATION}"
		LIBRARY DESTINATION						"${CXXUTILITY_LIBRARY_DESTINATION}")

install(FILES									${CXXUTILITY_PUBLIC_HEADERS}
		DESTINATION								"${CXXUTILITY_HEADER_DESTINATION}")

install(EXPORT									${CXXUTILITY_TARGETS}
		DESTINATION								${CXXUTILITY_CMAKE_DIRECTORY}
		FILE									"cxxutility-config.cmake")

include(CPack)
