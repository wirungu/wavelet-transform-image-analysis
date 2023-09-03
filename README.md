# Wavelet transforms and image analysis

This is my implementation of one of the longer projects in Rouben Rostamian's *Programming Projects in C*: 1D and 2D Haar wavelet transforms applied to image compression and analysis.

## Project Overview

The goal of this project is to apply Haar wavelet transforms to image data for compression and analysis. The Haar wavelet transform is a mathematical technique that allows you to represent an image in a different basis, making it possible to analyze its frequency content and compress it effectively.

## Features

- **1D and 2D Haar Wavelet Transforms**: This project provides implementations for both 1D and 2D Haar wavelet transforms. The 1D transform can be applied to signals, while the 2D transform is designed for images.

- **Image Import and Export**: The project includes functions for reading and writing PGM and PPM image files. This enables you to process existing images or save the results of your wavelet analysis.

- **Compression**: You can apply the Haar wavelet transform to an image and discard coefficients to achieve compression while controlling the truncation error.

- **Analysis**: The code also allows you to analyze the frequency content of an image using the wavelet transform.

## Getting Started

To get started with this project, you'll need to set up a development environment with CMake and Netpbm installed. You can then compile the code and run the `image-analysis` executable to apply wavelet transforms and analyze images.

## Usage

Here's an example of how to use the `image-analysis` executable:

```bash
$ ./image-analysis 0.9 profile.pgm profile-9.pgm
```
## Examples
![**Original image**](/image-analysis/profile.pgm)

![**Compressed image**](/image-analysis/profile-9.pgm)

## Acknowledgments

Rouben Rostamian for the inspiration and project idea.
