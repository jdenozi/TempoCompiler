cmake_minimum_required(VERSION 3.6)

project(TotoCompiler
        VERSION 0.0.1
        DESCRIPTION "Custom funny compiler"
        LANGUAGES CXX
        )

if(_change_MSVC_flags)
    # Modify compile flags to change MSVC runtime from /MD to /MT
    set(_re_match "([\\/\\-]M)D")
    set(_re_replace "\\1T")
    string(REGEX REPLACE ${_re_match} ${_re_replace}
            CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    string(REGEX REPLACE ${_re_match} ${_re_replace}
            CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    string(REGEX REPLACE ${_re_match} ${_re_replace}
            CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
    string(REGEX REPLACE ${_re_match} ${_re_replace}
            CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL}")
    string(REGEX REPLACE ${_re_match} ${_re_replace}
            CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
endif()

set(CMAKE_CXX_STANDARD 20)

if (WIN32)
    set(PLATFORM windows)
    if(CMAKE_VERSION VERSION_LESS 3.15.0)
        set(_change_MSVC_flags TRUE)
    else()
        # Set MSVC runtime to MultiThreaded (/MT)
        cmake_policy(SET CMP0091 NEW)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    endif()
endif(WIN32)

if (UNIX)
    set(PLATFORM unix)
endif (UNIX)

if(APPLE)
    set(PLATFORM apple)
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(TARGET x64)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(TARGET x86)
endif()

set(BUILD_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin/${PLATFORM}/${CMAKE_BUILD_TYPE}/${TARGET}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_PATH})

# Loop over file
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

message(" FILE  ${SRC_FILES}")

enable_testing()

add_subdirectory(test/)

add_subdirectory(vendor/googletest)

add_library(${PROJECT_NAME}Lib STATIC ${SRC_FILES} ${HEADER_FILES})

add_executable(TotoCompiler main.cpp ${SRC_FILES} ${HEADER_FILES})
