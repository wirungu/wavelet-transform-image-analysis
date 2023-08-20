cmake_minimum_required(VERSION 3.5)
project(netpbm_minimal C)

# Add the source files for the project
set(SOURCES
    wavelet.c
    wavelet.h
    netpbm-minimal.c
    array.h
    xmalloc.h
    xmalloc.c
)

# Had to do this for my machine. Fedora couldn't find these libraries.
set(NETPBM_INCLUDE_DIRS "/usr/include/netpbm")
set(NETPBM_LIBRARY_DIRS "/usr/include/netpbm")

# Specify the Netpbm libraries to link against
set(NETPBM_LIBRARIES "-lnetpbm")

# Create the executable for netpbm-minimal
add_executable(netpbm_minimal ${SOURCES})

# Rename the main function in netpbm-minimal.c
target_compile_definitions(netpbm_minimal PRIVATE MAIN_FUNCTION_NAME=netpbm_main)

# Link libraries (Netpbm and m)
target_link_libraries(netpbm_minimal PRIVATE ${NETPBM_LIBRARIES} m)

# Include Netpbm headers
target_include_directories(netpbm_minimal PRIVATE ${NETPBM_INCLUDE_DIRS})

# Specify Netpbm library directories
link_directories(${NETPBM_LIBRARY_DIRS})

# Copy aya_matsuura.pgm to the build directory
configure_file(aya_matsuura.pgm ${CMAKE_CURRENT_BINARY_DIR}/aya_matsuura.pgm COPYONLY)
