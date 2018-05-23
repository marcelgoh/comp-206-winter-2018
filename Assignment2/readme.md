# COMP 206 Assignment 2

## Question 1: BMP Info
Displays information about a BMP file.  
Usage:  
`$ gcc bmp_info.c A2_bmp_helpers.c -o bmp_info`  
`$ ./bmp_info <bmp_file>`  

## Question 2: BMP Mask
Overlays a coloured rectangular mask over a BMP file.  
Usage:  
`$ gcc bmp_mask.c A2_bmp_helpers.c -o bmp_mask`  
`$ ./bmp_mask <input_file> <output_file> <x_min> <y_min> <x_max> <y_max> <red> <green> <blue>`  

## Question 3: BMP Collage 
Opens two BMP files and overlays bmp1 onto bmp2 at certain offset.  
Usage:  
`$ gcc bmp_collage.c A2_bmp_helpers.c -o bmp_collage`  
`$ ./bmp_collage <bmp1> <bmp2> <output> <x_offset> <y_offset>`  
Run `bash create_metro_collage.bash` to get the pieces of the Montreal Metro map to fit together.

## Authors:  
Code template: Prof. David Meger  
Assignment solution: Marcel Goh  
Posted after the course end date with permission from Prof. David Meger.
