cmake_minimum_required(VERSION 3.6)

project(TotoCompiler
        VERSION 0.0.1
        DESCRIPTION "Custom funny compiler"
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 17)

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

# Loop over file
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)


message(" FILE  ${SRC_FILES}")

enable_testing()

add_subdirectory(test/)

add_subdirectory(vendor/googletest)

add_library(${PROJECT_NAME}Lib STATIC ${SRC_FILES} ${HEADER_FILES})

add_executable(TotoCompiler main.cpp ${SRC_FILES} ${HEADER_FILES})
