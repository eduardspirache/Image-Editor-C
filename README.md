# C Image Editor

I developed a Netpbm image editor during my first year at university, which did not rely on the predefined libnetpbm library. Instead, I used only basic C libraries to implement the program. The application receives commands from the command-line, and can perform a variety of operations on PPM and PGM images, both as plain text (ASCII) and binary files.

|        TYPE        |        ASCII        |        BINARY       |               COLORS                |
| ------------------ | ------------------- | ------------------- | ----------------------------------- |
|      GRAYSCALE     |         P2          |         P5          |    0 - 255 (black & white shade)    |
|      RGB           |         P3          |         P6          |            16.777.216 (RGB)         |

# How to Use Example
``` These are commands typed by the user ``` <br/>
```LOAD test_file```  <br/>
Loaded test_file <br/>
```SELECT 0 1 8 10``` <br/>
Selected 0 1 8 10 <br/>
```CROP```<br/>
Image cropped<br/>
```SAVE my_binary_file```<br/>
Saved my_binary_file<br/>
```LOAD non_existent_file```<br/>
Failed to load non_existent_file<br/>
```LOAD color_file```<br/>
Loaded color_file<br/>
```GRAYSCALE```<br/>
Grayscale filter applied<br/>
```SEPIA```<br/>
Sepia filter not available<br/>
```SAVE my_plain_file ascii```<br/>
Saved my_plain_file<br/>
```EXIT```<br/>

# Generate Own Image
To generate your own PNM and PGM files, use the "convert" utility that converts png / jpeg / jpg files to these formats:<br/>
• Setup: <br>
$ sudo apt update <br>
$ sudo apt-get install build-essential <br>
$ sudo apt-get install imagemagick<br/> <br>
• Documentation: man convert<br/>
• Examples:<br/>
    convert foo.jpg foo.ppm (transforms foo.jpg în foo.ppm, binary RGB)<br/>
    convert foo.jpg foo.pgm (transforms foo.jpg în foo.pgm, binary grayscale)<br/>
    convert foo.jpg -compress None foo.ppm (transforms foo.jpg în foo.ppm, ASCII RGB)<br/>
    convert foo.jpg -compress None foo.pgm transforms foo.jpg în foo.ppm, ASCII grayscale)<br/>


