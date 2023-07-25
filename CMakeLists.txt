cmake_minimum_required(VERSION 3.12)
project(haar_wavelet)

# Add source files
set(SOURCES
    wavelet.c
    wavelet.h
    array.h
    wavelet-test.c
    xmalloc.c
    xmalloc.h
)

# Create executable target and link libraries
add_executable(haar_wavelet ${SOURCES})
target_link_libraries(haar_wavelet m)
