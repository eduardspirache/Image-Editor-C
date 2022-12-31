# C Image Editor

I developed a Netpbm image editor during my first year at university, which did not rely on the predefined libnetpbm library. Instead, I used only basic C libraries to implement the program. The application receives commands from the command-line, and can perform a variety of operations on PPM and PGM images, both as plain text (ASCII) and binary files.

|        TYPE        |        ASCII        |        BINARY       |               COLORS                |
| ------------------ | ------------------- | ------------------- | ----------------------------------- |
|      GRAYSCALE     |         P2          |         P5          |    0 - 255 (black & white shade)    |
|      RGB           |         P3          |         P6          |            16.777.216 (RGB)         |

# RUN EXAMPLE: 
"C:" represents keyboard typed command
```C: LOAD test_file```
Loaded test_file
```C: SELECT 0 1 8 10```
Selected 0 1 8 10
```C: CROP```
Image cropped
```C: SAVE my_binary_file```
Saved my_binary_file
```C: LOAD non_existent_file```
Failed to load non_existent_file
```C: LOAD color_file```
Loaded color_file
```C:GRAYSCALE```
Grayscale filter applied
```C: SEPIA```
Sepia filter not available
```C: SAVE my_plain_file ascii```
Saved my_plain_file
```C: EXIT```

# GENERATE YOUR OWN IMAGE:
To generate your own PNM and PGM files, use the "convert" utility that converts png / jpeg / jpg files to these formats:
• Setup: 
$ sudo apt update 
$ sudo apt-get install build-essential
$ sudo apt-get install imagemagick
• Documentation: man convert
• Examples:
    convert foo.jpg foo.ppm (transforms foo.jpg în foo.ppm, binary RGB)<br/>
    convert foo.jpg foo.pgm (transforms foo.jpg în foo.pgm, binary grayscale)<br/>
    convert foo.jpg -compress None foo.ppm (transforms foo.jpg în foo.ppm, ASCII RGB)<br/>
    convert foo.jpg -compress None foo.pgm transforms foo.jpg în foo.ppm, ASCII grayscale)<br/>


