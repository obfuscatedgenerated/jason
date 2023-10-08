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
#set_target_properties(jason PROPERTIES PUBLIC_HEADER "${HEADERS}") # TODO: maybe distribute separate headers for public api, or unite into a single header

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


# installation target
include(GNUInstallDirs)

install(TARGETS jason
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)#PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# using this rather than PUBLIC_HEADER to retain directory structure
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
