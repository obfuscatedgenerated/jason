cmake_minimum_required(VERSION 3.5)
project(jason C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.c")
add_library(jason SHARED ${SOURCES})

file(GLOB_RECURSE TEST_SOURCES "test/*.c")
add_executable(jason_test ${TEST_SOURCES})
target_link_libraries(jason_test jason)

target_compile_definitions(jason PRIVATE JASON_SHOW_PRIVATES)
target_compile_definitions(jason_test PRIVATE JASON_SHOW_PRIVATES)

file(GLOB_RECURSE OOS_TEST_SOURCES "oos-test/*.c")
add_executable(jason_oos_test ${OOS_TEST_SOURCES})
target_link_libraries(jason_oos_test jason)

enable_testing()

add_test(NAME jason_test COMMAND jason_test)
add_test(NAME jason_oos_test COMMAND jason_oos_test)

