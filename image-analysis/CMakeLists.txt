cmake_minimum_required(VERSION 3.5)
project(ImageAnalysis C)

# Add the source files for the project
set(SOURCES
    image-analysis.c
    image-io.c
    image-io.h
    array.h
    wavelet.c
    wavelet.h
    xmalloc.c
    xmalloc.h
)

# Had to do this for my machine. Fedora couldn't find these libraries.
set(NETPBM_INCLUDE_DIRS "/usr/include/netpbm")
set(NETPBM_LIBRARY_DIRS "/usr/include/netpbm")

# Specify the Netpbm libraries to link against
set(NETPBM_LIBRARIES "-lnetpbm")

# Create the executable for image-analysis
add_executable(image-analysis ${SOURCES})

# Link libraries (Netpbm and m)
target_link_libraries(image-analysis PRIVATE ${NETPBM_LIBRARIES} m)

# Include Netpbm headers
target_include_directories(image-analysis PRIVATE ${NETPBM_INCLUDE_DIRS})

# Specify Netpbm library directories
link_directories(${NETPBM_LIBRARY_DIRS})

# Copy input image to the build directory
configure_file(profile.pgm ${CMAKE_CURRENT_BINARY_DIR}/profile.pgm COPYONLY)

# Copy input image to the build directory
configure_file(profile.ppm ${CMAKE_CURRENT_BINARY_DIR}/profile.ppm COPYONLY)

