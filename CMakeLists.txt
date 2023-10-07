cmake_minimum_required(VERSION 3.5)
project(jason C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.c")
add_library(jason SHARED ${SOURCES})

file(GLOB_RECURSE TEST_SOURCES "test/*.c")
add_executable(jason_test ${TEST_SOURCES})
target_link_libraries(jason_test jason)

enable_testing()

add_test(NAME jason_test COMMAND jason_test)

# run script/gen_headers.cmake when any file in include/ is changed
file(GLOB_RECURSE INCLUDES "include/*.h")
add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_SOURCE_DIR}/script/gen_headers.cmake
        DEPENDS ${INCLUDES}
        COMMENT "Regenerating headers"
        VERBATIM
)
