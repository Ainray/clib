cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
option(CMAKE_GNUtoMS "Generate Windows libraries" ON)

project(ainrayc C CXX)
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 1)

#prevent insource build
string (TOLOWER "${CMAKE_CURRENT_SOURCE_DIR}" SOURCE_DIR_LOWER)
string (TOLOWER "${CMAKE_CURRENT_BINARY_DIR}" BINARY_DIR_LOWER )
if (SOURCE_DIR_LOWER STREQUAL BINARY_DIR_LOWER)
    message (FATAL_ERROR "Compiling LAPACKPP with CMake requires an out-of-source build. 
	To proceed:
    rm -rf CMakeCache.txt CMakeFiles/   # delete files in ${CMAKE_CURRENT_SOURCE_DIR}
    mkdir build
    cd build
    cmake ..
    make")
	return()
endif ()

# prevent inbuild install
string(TOLOWER "${CMAKE_INSTALL_PREFIX}" _PREFIX)
string(TOLOWER "${ITK_BINARY_DIR}" _BUILD)
if("${_PREFIX}" STREQUAL "${_BUILD}")
  message(FATAL_ERROR
    "The current CMAKE_INSTALL_PREFIX points at the build tree:\n"
    "  ${CMAKE_INSTALL_PREFIX}\n"
    "This is not supported."
    )
endif()

# MACRO DEFINITIONS
# add_compile_definitions()

# Export all symbols on Windows when building shared libraries
# reduces __declspec(dllimport) 
SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# options
# By default shared library
option(BUILD_SHARED_LIBS "Generate shared library" ON)

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_definitions(_UNIX_)
	option(BUILD_WIN32API "Build win32 api" ON)
elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    add_compile_definitions(_WIN_ _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_WARNINGS)
	option(BUILD_WIN32API "Build win32 api" ON)
else()
    message(FATAL_ERROR "Only GNU and MSVC are supported now. Please contact to
        Ainray, wwzhang0421@163.com to extend platforms.")
endif()

# --------------------------------------------------
# install 
set(CMAKE_INSTALL_PREFIX ${ainrayc_BINARY_DIR}/install)
set(AINRAYC_INSTALL_EXPORT_NAME orebs-targets)
macro(ainrayc_install_library lib)
  install(TARGETS ${lib}
    EXPORT ${AINRAYC_INSTALL_EXPORT_NAME}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT RuntimeLibraries
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT RuntimeLibraries
  )
endmacro()

# --------------------------------------------------
# Organize output files.  On Windows this also keeps .dll files next
# to the .exe files that need them, making tests easy to run.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${orebs_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${orebs_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${orebs_BINARY_DIR}/lib)

include_directories(include ${ainrayc_BINARY_DIR}/include)
add_subdirectory(include)
add_subdirectory(src)
#add_subdirectory(test)