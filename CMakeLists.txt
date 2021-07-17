cmake_minimum_required(VERSION 3.10)

set(PROJECT vocabulator)

project(${PROJECT} VERSION 1.0 LANGUAGES CXX)

# Check a platform
#if(WIN32)
#	message("Platform: WIN32")
#else()
#	message("Unsupported platform yet")
#	return()
#endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#option(OPTIMIZE "Allow compiler optimizations. Set to OFF to disable" OFF)

# Set a default build type if none was specified by option -DCMAKE_BUILD_TYPE=Release
if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
  set(default_build_type "Debug")
else()
  set(default_build_type "Release")
endif()
 
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
	set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
else()
	message("Configuration: ${CMAKE_BUILD_TYPE}")
endif()

set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib)
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)

set(BUILD_SHARED_LIBS FALSE CACHE BOOL "Disable shared libraries for SFML" FORCE)
set(SFML_BUILD_NETWORK FALSE CACHE BOOL "Disable networking module for SFML" FORCE)
ADD_SUBDIRECTORY(thirdparty/sfml)

#set(BUILD_EXAMPLES OFF CACHE BOOL "Disable examples for libconfig" FORCE)
#set(BUILD_TESTS OFF CACHE BOOL "Disable tests for libconfig" FORCE)
ADD_SUBDIRECTORY(thirdparty/libconfig)

set(PLOG_BUILD_SAMPLES OFF CACHE BOOL "Disable samples for plog" FORCE)
ADD_SUBDIRECTORY(thirdparty/plog)

file(GLOB SOURCES_LIST "src/*.cpp" "src/*.hpp")

add_executable(${PROJECT} ${SOURCES_LIST})

#if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#	target_link_options(${PROJECT} PRIVATE -mwindows)
#elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
#	target_link_options(${PROJECT} PRIVATE -s -mwindows)
	# Disable optimizations
#	if(NOT OPTIMIZE)
#		string(REGEX REPLACE "(\-O[011123456789])" "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS}")
#		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O0")
#		message("Optimizations were disabled")
#	endif()
#else()
#	message("Unknown configuration name ${CMAKE_BUILD_TYPE}. Stop")
#	return()
#endif()

# Enable c++17
target_compile_features(${PROJECT} PRIVATE cxx_std_17)

# Additional directories that contain header files
target_include_directories(${PROJECT} PRIVATE
	${CMAKE_HOME_DIRECTORY}/thirdparty/random/include
	${CMAKE_HOME_DIRECTORY}/thirdparty/plog/include
	${CMAKE_HOME_DIRECTORY}/thirdparty/sfml/include
	${CMAKE_HOME_DIRECTORY}/thirdparty/libconfig/lib
	)

if(WIN32)
    set(THIRD_PARTY_LIBS sfml-main sfml-system sfml-window sfml-graphics sfml-audio config++)
else()
    set(THIRD_PARTY_LIBS sfml-system sfml-window sfml-graphics sfml-audio config++)
endif()

target_link_libraries(${PROJECT} ${THIRD_PARTY_LIBS})

