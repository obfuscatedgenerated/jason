file(GLOB_RECURSE HEADERS "include/*.h")

# copy all headers to new directory in build in correct structure
file(COPY ${HEADERS} DESTINATION ${CMAKE_BINARY_DIR}/include)

# rewrite copied files to remove any lines starting with PRIVATE
#file(GLOB_RECURSE PRIVATE_HEADERS "${CMAKE_BINARY_DIR}/include/*.h")
#foreach(PRIVATE_HEADER ${PRIVATE_HEADERS})
#    file(READ ${PRIVATE_HEADER} HEADER_CONTENTS)
#    string(REGEX REPLACE "PRIVATE.*\n" "" HEADER_CONTENTS "${HEADER_CONTENTS}")
#    file(WRITE ${PRIVATE_HEADER} "${HEADER_CONTENTS}")
#endforeach()
