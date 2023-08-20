cmake_minimum_required(VERSION 3.5)
project(wavelet_test C)

# Add the source files for the project
set(SOURCES
    wavelet.c
    wavelet.h
    wavelet-test.c
    array.h
    xmalloc.h
    xmalloc.c
)

# Create the executable for wavelet-test
add_executable(wavelet_test ${SOURCES})

# Link libraries (m)
target_link_libraries(wavelet_test PRIVATE m)
