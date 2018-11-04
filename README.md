# C++17 `constexpr` Compile-Time Mandelbrot Image Generator

## Description
This project allows to generate mandelbrot images entirely in compile-time using `constexpr` functions in C++17.

## Preview
![50% centre](./ConstexprMandelbrot/mandelbrot.png)

## Limitations
- The Visual C++ compiler crashes for large images because it runs out of memory.

## Runtime image generator
Large images can be generated within a few seconds, because the fact how much the compiler can optimize the code.

## Dependencies
- [stb_image_write.h](https://github.com/nothings/stb/blob/master/stb_image_write.h) to write PNG images