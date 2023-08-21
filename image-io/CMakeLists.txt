cmake_minimum_required(VERSION 3.5)
project(ImageIOTest C)

# Add the source files for the project
set(SOURCES
    image-io-test-0.c
    image-io.c
    image-io.h
    xmalloc.c
    xmalloc.h
    array.h
)

# Had to do this for my machine. Fedora couldn't find these libraries.
set(NETPBM_INCLUDE_DIRS "/usr/include/netpbm")
set(NETPBM_LIBRARY_DIRS "/usr/include/netpbm")

# Specify the Netpbm libraries to link against
set(NETPBM_LIBRARIES "-lnetpbm")

# Create the executable for wavelet-test
add_executable(image-io-test-0 ${SOURCES})

# Link libraries (Netpbm and m)
target_link_libraries(image-io-test-0 PRIVATE ${NETPBM_LIBRARIES} m)

# Include Netpbm headers
target_include_directories(image-io-test-0 PRIVATE ${NETPBM_INCLUDE_DIRS})

# Specify Netpbm library directories
link_directories(${NETPBM_LIBRARY_DIRS})

# Copy aya_matsuura.pgm to the build directory
configure_file(aya_matsuura.pgm ${CMAKE_CURRENT_BINARY_DIR}/aya_matsuura.pgm COPYONLY)
