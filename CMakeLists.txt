cmake_minimum_required(VERSION 3.10)

# Check a platform
if(WIN32)
	message("Platform: WIN32")
else()
	message("Unsupported platform yet")
	return()
endif()

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

project(vocabulator VERSION 1.0 LANGUAGES CXX)

set(sources abstractstate.cpp finalscreenstate.cpp gamecontext.cpp gameobjects.cpp gamesettings.cpp gamestate.cpp gamestatistics.cpp main.cpp menustate.cpp resources.cpp splashstate.cpp statisticsstate.cpp)

add_executable(vocabulator ${sources})

# Define libconfig root directory
set(libconfigdir "d:/Development/Projects/words-trainer/lib/libconfig")

# Define libs
set(sfmllibs sfml-main sfml-system sfml-window sfml-graphics sfml-audio)
set(configlib config++.dll)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_link_options(vocabulator PRIVATE -mwindows)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	target_link_options(vocabulator PRIVATE -s -mwindows)
else()
	message("Unknown configuration name ${CMAKE_BUILD_TYPE}. Stop")
	return()
endif()

# Enable c++17
target_compile_features(vocabulator PRIVATE cxx_std_17)

# Additional directories that contain header files
target_include_directories(vocabulator PRIVATE ${libconfigdir}/include)

# Additional directories that contain libraries
target_link_directories(vocabulator PRIVATE ${libconfigdir}/lib)

target_link_libraries(vocabulator ${sfmllibs} ${configlib})
