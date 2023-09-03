# Wavelet transforms and image analysis

This is my implementation of one of the longer projects in Rouben Rostamian's *Programming Projects in C*: 1D and 2D Haar wavelet transforms applied to image compression and analysis.

## Project Overview

The goal of this project is to implement [Haar wavelet transforms](https://en.wikipedia.org/wiki/Haar_wavelet) and then apply them to image data for compression and analysis.

## Features

- **1D and 2D Haar Wavelet Transforms**: This project provides implementations for both 1D and 2D Haar wavelet transforms. The 1D transform can be applied to signals, while the 2D transform is designed for images.

- **Image Import and Export**: The project includes functions for reading and writing PGM and PPM image files. This enables you to process existing images or save the results of your wavelet analysis.

- **Compression**: You can apply the Haar wavelet transform to an image and discard coefficients to achieve compression while controlling the truncation error.

- **Analysis**: The code also allows you to analyze the frequency content of an image using the wavelet transform.

## Getting Started

To get started with this project, you'll need to set up CMake and Netpbm. You can then compile the code and run e.g. the `image-analysis` executable to apply wavelet transforms and analyze images. Each folder corresponds to a project chapter in the book. They are self-contained and meant to be built separately. Full details are of course in the book.

## Usage

Here's an example of how to use the `image-analysis` executable to compress a grayscale image:

```bash
$ ./image-analysis 0.9 profile.pgm profile-9.pgm
```
## Examples
**Original image**

<img src="https://i.imgur.com/YBNGYJs.jpg" width="256">

**Compressed image**

<img src="https://i.imgur.com/8T6Cep4.jpg" width="256">
## Acknowledgments

Rouben Rostamian for the inspiration and project idea.
