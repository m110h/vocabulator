cmake_minimum_required(VERSION 3.10)

set(PROJECT vocabulator)

project(${PROJECT} VERSION 1.0 LANGUAGES CXX)

option(OPTIMIZE "Allow compiler optimizations. Set to OFF to disable" OFF)

# Set a default build type if none was specified by option -DCMAKE_BUILD_TYPE=Release
set(default_build_type "Release")

if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
  set(default_build_type "Debug")
endif()
 
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
	set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
else()
	message("Configuration: ${CMAKE_BUILD_TYPE}")
endif()

# Check a platform
if(WIN32)
	message("Platform: WIN32")
else()
	message("Unsupported platform yet")
	return()
endif()

#add_subdirectory(thirdparty/sfml)

#set(BUILD_EXAMPLES ON CACHE BOOL "Disable examples for libconfig")
#set(BUILD_SHARED_LIBS OFF CACHE BOOL "Disable shared libraries for libconfig")
#set(BUILD_TESTS OFF CACHE BOOL "Disable tests for libconfig")
#add_subdirectory(thirdparty/libconfig)

#set(PLOG_BUILD_SAMPLES OFF CACHE BOOL "Disable samples for plog")
#add_subdirectory(thirdparty/plog)

file(GLOB SOURCES_LIST "*.cpp" "*.hpp")

add_executable(${PROJECT} ${SOURCES_LIST})

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_link_options(${PROJECT} PRIVATE -mwindows)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	target_link_options(${PROJECT} PRIVATE -s -mwindows)
	# Disable optimizations
	if(NOT OPTIMIZE)
		string(REGEX REPLACE "(\-O[011123456789])" "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS}")
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O0")
		message("Optimizations were disabled")
	endif()
else()
	message("Unknown configuration name ${CMAKE_BUILD_TYPE}. Stop")
	return()
endif()

# Enable c++17
target_compile_features(${PROJECT} PRIVATE cxx_std_17)

# Additional directories that contain header files
target_include_directories(${PROJECT} PRIVATE
	${CMAKE_BINARY_DIR}/include
	${CMAKE_BINARY_DIR}/include/random
	${CMAKE_BINARY_DIR}/include/libconfig
	)

# Additional directories that contain libraries
target_link_directories(${PROJECT} PRIVATE
	${CMAKE_BINARY_DIR}/lib/sfml
	${CMAKE_BINARY_DIR}/lib/libconfig
#	${CMAKE_SOURCE_DIR}/out
#	${CMAKE_SOURCE_DIR}/thirdparty/sfml/lib
	)

# Define libs
set(sfmllibs sfml-main sfml-system sfml-window sfml-graphics sfml-audio)

target_link_libraries(${PROJECT} config++ ${sfmllibs})
