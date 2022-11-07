set(PROJECT_NAME_TEST ${CMAKE_PROJECT_NAME}test)

message("-- Compile ${CMAKE_PROJECT_NAME} Test")
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

add_executable(${PROJECT_NAME_TEST} ${TEST_SOURCES})

add_test(NAME ${PROJECT_NAME_TEST} COMMAND ${PROJECT_NAME_TEST})


target_link_libraries(${PROJECT_NAME_TEST}
        PUBLIC
        ${CMAKE_PROJECT_NAME}_lib
        gtest)