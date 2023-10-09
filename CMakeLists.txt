cmake_minimum_required(VERSION 3.5)
project(jason VERSION 0.0.1 LANGUAGES C DESCRIPTION "{ •͜ʖ• }  jason - the friendly JSON parser.")

set(CMAKE_C_STANDARD 11)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.c")
file(GLOB_RECURSE HEADERS "include/*.h")
add_library(jason SHARED ${SOURCES})

# create pkg-config
configure_file(src/${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)

set_target_properties(jason PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(jason PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

file(GLOB_RECURSE FULL_ACCESS_TEST_SOURCES "test/full_access/*.c")
add_executable(jason_full_access_test ${FULL_ACCESS_TEST_SOURCES})
target_link_libraries(jason_full_access_test jason)

target_compile_definitions(jason PRIVATE JASON_SHOW_PRIVATES)
target_compile_definitions(jason_full_access_test PRIVATE JASON_SHOW_PRIVATES)

file(GLOB_RECURSE PRIV_TEST_SOURCES "test/priv/*.c")
add_executable(jason_priv_test ${PRIV_TEST_SOURCES})
target_link_libraries(jason_priv_test jason)

enable_testing()

add_test(NAME jason_full_access_test COMMAND jason_full_access_test)
add_test(NAME jason_priv_test COMMAND jason_priv_test)


# run script/public_headers.sh (or .bat on windows)
set(SCRIPT_ARG0 "${CMAKE_SOURCE_DIR}/include")
set(SCRIPT_ARG1 "${CMAKE_BINARY_DIR}")
if (WIN32)
    set(SCRIPT_SUFFIX ".bat")
    string(REPLACE "/" "\\" SCRIPT_ARG0 "${SCRIPT_ARG0}")
    string(REPLACE "/" "\\" SCRIPT_ARG1 "${SCRIPT_ARG1}")
else()
    set(SCRIPT_SUFFIX ".sh")
endif()

add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/include/
        COMMAND ${CMAKE_SOURCE_DIR}/script/public_headers${SCRIPT_SUFFIX} ${SCRIPT_ARG0} ${SCRIPT_ARG1}
        DEPENDS ${HEADERS}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating public headers"
        VERBATIM)
add_custom_target(public_headers ALL DEPENDS ${CMAKE_BINARY_DIR}/include/)

# also run the script now
message(STATUS "Generating public headers (first time)")
execute_process(COMMAND ${CMAKE_SOURCE_DIR}/script/public_headers${SCRIPT_SUFFIX} ${SCRIPT_ARG0} ${SCRIPT_ARG1}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

file(GLOB_RECURSE PUB_HEADERS ${CMAKE_BINARY_DIR}/include/*.h)

# installation target
include(GNUInstallDirs)

install(TARGETS jason
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})


# using public_header flattens everything to one dir (and overwrites string.h :O)
# so install manually
install(DIRECTORY ${CMAKE_BINARY_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
