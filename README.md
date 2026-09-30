# PGM Image Processor in C

This project is a C library and tool designed for reading, manipulating, and writing grayscale images in the **PGM ASCII (P2)** format.

## Features

* **PGM Loading & Saving:** Full support for reading PGM files, including comment handling (`#`) and header parsing.
* **Color Inversion:** Generates the negative version of an image.
* **Rotation:** Rotates the image 90 degrees clockwise with dynamic memory reallocation.
* **Box Blur Filter:** Image smoothing algorithm based on neighboring pixel averaging.
* **Efficient Memory Management:** Explicit control over dynamic allocation (`malloc`) and deallocation (`free`) of pixel matrices.

## Project Structure

* `imagen.h`: Header file defining the `Imagen` struct and function prototypes.
* `imagen.c`: Implementation of the image processing logic and operations.
* `main.c`: Test program demonstrating automated image transformations.
* `Makefile`: Build script for automated compilation using `gcc`.

## Building and Execution

To compile the project, make sure you have `gcc` and `make` installed, then run:

```bash
make
