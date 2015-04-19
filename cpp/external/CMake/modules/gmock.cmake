# Use a variable to point to the root of googlemock within the External
# directory. This makes it easier to update to new releases as desired.
SET(GOOGLEMOCK_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../gmock")
INCLUDE_DIRECTORIES(${GOOGLEMOCK_ROOT}/fused-src)
# Make the file lists.
SET(INCLUDE_FILES ${GOOGLEMOCK_ROOT}/fused-src/gtest/gtest.h
    ${GOOGLEMOCK_ROOT}/fused-src/gmock/gmock.h)
SET(SOURCE_FILES ${GOOGLEMOCK_ROOT}/fused-src/gmock-gtest-all.cc
    ${GOOGLEMOCK_ROOT}/fused-src/gmock_main.cc)

# Add as a static library target and ignore compiler warnings for gmock.
ADD_LIBRARY(gmock STATIC ${INCLUDE_FILES} ${SOURCE_FILES})
SET_PROPERTY(TARGET gmock APPEND_STRING PROPERTY COMPILE_FLAGS "-w")

# ADD_GMOCK_TEST(<target> <sources>...)
#
# Adds a googlemock based test executable, <target>, built from <sources> and
# adds the test so that CTest will run it. Both the executable and the test
# will be named <target>.
FUNCTION(ADD_GMOCK_TEST TARGET)
    ADD_EXECUTABLE(${TARGET} ${ARGN})
    TARGET_LINK_LIBRARIES(${TARGET} gmock)
    INCLUDE_DIRECTORIES(${GMOCK_INCLUDE_DIRS})
    ADD_TEST(${TARGET} ${TARGET})

    ADD_CUSTOM_COMMAND(TARGET ${TARGET} POST_BUILD
        COMMAND ${TARGET}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Running ${TARGET}" VERBATIM)
ENDFUNCTION(ADD_GMOCK_TEST)
