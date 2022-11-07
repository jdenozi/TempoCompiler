cmake_minimum_required(VERSION 3.23)
project(TotoCompiler
        VERSION 0.0.1
        DESCRIPTION "Custom funny compiler"
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 20)

if (WIN32)
    set(PLATFORM windows)
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

add_subdirectory(test)

add_subdirectory(vendor/googletest)

add_executable(TotoCompiler main.cpp include/Lexer/Lexer.h test/test.cpp)
