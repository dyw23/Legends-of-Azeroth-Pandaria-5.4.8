# Copyright (C) 2011-2016 Project SkyFire <http://www.projectskyfire.org/>
# Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

# Before project or language initialization
cmake_minimum_required(VERSION 3.16)

# add this options before PROJECT keyword
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)


# Set projectname (must be done AFTER setting configurationtypes)
project(Pandaria_5.4.8)

# CMake policies (can not be handled elsewhere)
cmake_policy(SET CMP0005 NEW)
cmake_policy(SET CMP0043 NEW) # Ignore COMPILE_DEFINITIONS_<Config> properties
cmake_policy(SET CMP0054 NEW) # Only interpret if() arguments as variables or keywords when unquoted - prevents intepreting if(SOME_STRING_VARIABLE MATCHES "MSVC") as if(SOME_STRING_VARIABLE MATCHES "1")
cmake_policy(SET CMP0074 NEW) # find_package() uses <PackageName>_ROOT variables

if(POLICY CMP0144)
  cmake_policy(SET CMP0144 NEW) # find_package() uses upper-case <PACKAGENAME>_ROOT variables
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set RPATH-handing (CMake parameters)
set(CMAKE_SKIP_BUILD_RPATH 0)
set(CMAKE_BUILD_WITH_INSTALL_RPATH 0)
set(APPEND CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH 1)
	   
# set macro-directory
list(APPEND CMAKE_MODULE_PATH
  "${CMAKE_SOURCE_DIR}/cmake/macros")

# build in Release-mode by default if not explicitly set
if( NOT CMAKE_BUILD_TYPE )
  set(CMAKE_BUILD_TYPE "Release")
endif()

include(CheckSymbolExists)
include(CheckCXXSourceRuns)
include(CheckIncludeFiles)

# set default buildoptions and print them
include(cmake/options.cmake)

# turn off PCH totally if enabled (hidden setting, mainly for devs)
if( NOPCH )
  set(USE_COREPCH 0)
  set(USE_SCRIPTPCH 0)
endif()

include(CheckPlatform)

find_package(Threads REQUIRED)

#Debug compile time
set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")

if( UNIX )
  find_package(BZip2)
endif()

if(WIN32)
  add_definitions(-DBOOST_DATE_TIME_NO_LIB -DBOOST_REGEX_NO_LIB -DBOOST_CHRONO_NO_LIB -DBOOST_SERIALIZATION_NO_LIB)
  set(BOOST_DEBUG OFF)
  if(DEFINED ENV{BOOST_ROOT})
    set(BOOST_ROOT $ENV{BOOST_ROOT})
    list(APPEND BOOST_LIBRARYDIR
      ${BOOST_ROOT}/lib${PLATFORM}-msvc-14.2 )
  endif()


  set(Boost_USE_STATIC_LIBS        ON)
  set(Boost_USE_MULTITHREADED      ON)
  set(Boost_USE_STATIC_RUNTIME     OFF)
else()
  set(Boost_USE_STATIC_LIBS ON)
endif()

find_package(Boost COMPONENTS system locale thread serialization filesystem program_options iostreams regex
    REQUIRED
)

# find mysql client binary (needed by genrev)
find_package(MySQL OPTIONAL_COMPONENTS binary)

# Find revision ID and hash of the sourcetree
include(cmake/genrev.cmake)

# print out the results before continuing
include(cmake/showoptions.cmake)

# add dependencies
add_subdirectory(dep)

# add core sources
add_subdirectory(src)
