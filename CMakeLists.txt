cmake_minimum_required(VERSION 3.5)
project(jason C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.c")
add_library(jason SHARED ${SOURCES})

file(GLOB_RECURSE FULL_ACCESS_TEST_SOURCES "test/full_access/*.c")
add_executable(jason_full_access_test ${FULL_ACCESS_TEST_SOURCES})
target_link_libraries(jason_full_access_test jason)

target_compile_definitions(jason PRIVATE JASON_SHOW_PRIVATES)
target_compile_definitions(jason_full_access_test PRIVATE JASON_SHOW_PRIVATES)

file(GLOB_RECURSE OOS_TEST_SOURCES "test/oos/*.c")
add_executable(jason_oos_test ${OOS_TEST_SOURCES})
target_link_libraries(jason_oos_test jason)

enable_testing()

add_test(NAME jason_full_access_test COMMAND jason_full_access_test)
add_test(NAME jason_oos_test COMMAND jason_oos_test)
