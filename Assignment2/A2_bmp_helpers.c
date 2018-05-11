/* FILE: A2_bmp_helpers.c is where you will code your answers for Assignment 2.
 * 
 * Each of the functions below can be considered a start for you. 
 *
 * You should leave all of the code as is, except for what's surrounded
 * in comments like "REPLACE EVERTHING FROM HERE... TO HERE.
 *
 * The assignment document and the header A2_bmp_headers.h should help
 * to find out how to complete and test the functions. Good luck!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

int bmp_open( char* bmp_filename,        unsigned int *width, 
              unsigned int *height,      unsigned int *bits_per_pixel, 
              unsigned int *padding,     unsigned int *data_size, 
              unsigned int *data_offset, unsigned char** img_data ){

              
  // YOUR CODE FOR Q1 SHOULD REPLACE EVERYTHING FROM HERE
  FILE *file = fopen(bmp_filename, "rb");
  if (file == NULL) {
      printf("Error opening file.\n");
      return -1;
  }

  /* initialize variables using fseek then rewind the file */
  fseek(file, 2, SEEK_SET);
  fread(data_size, sizeof(unsigned int), 1, file);
  fseek(file, 10, SEEK_SET);
  fread(data_offset, sizeof(unsigned int), 1, file);
  fseek(file, 18, SEEK_SET);
  fread(width, sizeof(unsigned int), 1, file);
  fseek(file, 22, SEEK_SET);
  fread(height, sizeof(unsigned int), 1, file);
  fseek(file, 28, SEEK_SET);
  fread(bits_per_pixel, sizeof(unsigned int), 1, file);
  const unsigned int bytes_per_line = (*bits_per_pixel)*(*width)/8;
  *padding = (bytes_per_line % 4 == 0) ? 0:
                                         4 - bytes_per_line % 4;
  rewind(file);

  /* copy file to img_data pointer and close file */
  *img_data = (unsigned char *) malloc(*data_size);
  if (fread(*img_data, sizeof(unsigned char), *data_size, file) != *data_size) {
      printf("Error reading file.\n");
      return -1;
  }
  fclose(file);
  // TO HERE
  
  return 0;  
}

// We've implemented bmp_close for you. No need to modify this function
void bmp_close( unsigned char **img_data ){

  if( *img_data != NULL ){
    free( *img_data );
    *img_data = NULL;
  }
}

int bmp_mask( char* input_bmp_filename, char* output_bmp_filename, 
              unsigned int x_min, unsigned int y_min, unsigned int x_max, unsigned int y_max,
              unsigned char red, unsigned char green, unsigned char blue )
{
  unsigned int img_width;
  unsigned int img_height;
  unsigned int bits_per_pixel;
  unsigned int data_size;
  unsigned int padding;
  unsigned int data_offset;
  unsigned char* img_data    = NULL;
  
  int open_return_code = bmp_open( input_bmp_filename, &img_width, &img_height, &bits_per_pixel, &padding, &data_size, &data_offset, &img_data ); 
  
  if( open_return_code ){ printf( "bmp_open failed. Returning from bmp_mask without attempting changes.\n" ); return -1; }
 
  // YOUR CODE FOR Q2 SHOULD REPLACE EVERYTHING FROM HERE
  /* ensure mask is within image boundaries */
  if (x_max > img_width || y_max > img_height) {
      printf("Error. Invalid mask coordinates.\n");
      return -1;
  }

  /* constant and pointer initialization */
  unsigned char *output = (unsigned char*) malloc(sizeof(char)*data_size);
  memcpy(output, img_data, data_size);
  const unsigned int num_colors = bits_per_pixel / 8;
  const unsigned int bytes_in_line = num_colors * img_width + padding;
  const unsigned int mask_width = x_max - x_min;
  const unsigned int mask_height = y_max - y_min;
  unsigned char *iter = output + data_offset;

  /*iterate through output array and mask pixels in given area*/
  iter += y_min*bytes_in_line;
  for (int i=0; i<mask_height; i++) {
      iter += (x_min*num_colors);
      for (int j=0; j<mask_width; j++) {
          *(iter++) = blue;
          *(iter++) = green;
          *(iter++) = red;
      }
      iter += bytes_in_line - (x_max*num_colors);
  }
  
  /* write output to output_bmp_filename */
  FILE *file = fopen(output_bmp_filename, "wb");
  if (fwrite(output, sizeof(unsigned char), data_size, file) != data_size) {
      printf("Error writing masked output to file.\n");
      return -1;
  }
  fclose(file);
  free(output);
  output = NULL;
  // TO HERE!
  
  bmp_close( &img_data );
  
  return 0;
}         

int bmp_collage( char* bmp_input1, char* bmp_input2, char* bmp_result, int x_offset, int y_offset ){

  unsigned int img_width1;
  unsigned int img_height1;
  unsigned int bits_per_pixel1;
  unsigned int data_size1;
  unsigned int padding1;
  unsigned int data_offset1;
  unsigned char* img_data1    = NULL;
  
  int open_return_code = bmp_open( bmp_input1, &img_width1, &img_height1, &bits_per_pixel1, &padding1, &data_size1, &data_offset1, &img_data1 ); 
  
  if( open_return_code ){ printf( "bmp_open failed for %s. Returning from bmp_collage without attempting changes.\n", bmp_input1 ); return -1; }
  
  unsigned int img_width2;
  unsigned int img_height2;
  unsigned int bits_per_pixel2;
  unsigned int data_size2;
  unsigned int padding2;
  unsigned int data_offset2;
  unsigned char* img_data2    = NULL;
  
  open_return_code = bmp_open( bmp_input2, &img_width2, &img_height2, &bits_per_pixel2, &padding2, &data_size2, &data_offset2, &img_data2 ); 
  
  if( open_return_code ){ printf( "bmp_open failed for %s. Returning from bmp_collage without attempting changes.\n", bmp_input2 ); return -1; }
  
  // YOUR CODE FOR Q3 SHOULD REPLACE EVERYTHING FROM HERE
  /* ensure input1 and input2 have the same bits_per_pixel value */
  if (bits_per_pixel1 != bits_per_pixel2) {
      printf("Error. Pixel formats do not match.\n");
      return -1;
  }

  /* initialize variables and pointers */
  const unsigned int num_colors = bits_per_pixel1/8;
  unsigned int res_width, res_height;
  if (x_offset < 0) {
      res_width = img_width1 - x_offset;
  } else if (x_offset+img_width2 <= img_width1) {
      res_width = img_width1;
  } else {
      res_width = x_offset+img_width2;
  }
  if (y_offset < 0) {
      res_height = img_height1 - y_offset;
  } else if (y_offset+img_height2 <= img_height1) {
      res_height = img_height1;
  } else {
      res_height = y_offset+img_height2;
  }
  const unsigned int res_padding = (num_colors*res_width % 4 == 0) ? 0:
                                                                     4 - num_colors*res_width%4;
  const unsigned int bytes_in_line = num_colors*res_width + res_padding; 
  const unsigned int res_data_size = data_offset1 + bytes_in_line*res_height;
  unsigned char *res_data = (unsigned char*) malloc(sizeof(unsigned char)*(res_data_size));
  unsigned char *pixel_data1 = img_data1 + data_offset1;
  unsigned char *pixel_data2 = img_data2 + data_offset2;
  unsigned char *res_pixel_data = res_data + data_offset1;

  /* copy input1's header to res_data then change values */
  memcpy(res_data, img_data1, data_offset1);
  for (int i=0; i<4; i++) {
      res_data[2+i] = res_data_size >> (8*i);
  }
  for (int i=0; i<4; i++) {
      res_data[18+i] = res_width >> (8*i);
  }
  for (int i=0; i<4; i++) {
      res_data[22+i] = res_height >> (8*i);
  }
  
  /* shifts pixel_data1 if offsets are negative, otherwise draws it at bottom-left */
  unsigned int x_shift = (x_offset < 0) ? -x_offset:
                                          0;
  unsigned int y_shift = (y_offset < 0) ? -y_offset:
                                          0;
  unsigned int input_iter = 0;
  unsigned int res_iter = y_shift*bytes_in_line;
  for (int i=0; i<img_height1; i++) {
      res_iter += x_shift*num_colors;
      for (int j=0; j<img_width1*num_colors; j++) {
          res_pixel_data[res_iter++] = pixel_data1[input_iter++];
      }
      res_iter += bytes_in_line - num_colors*(x_shift + img_width1);
      input_iter += padding1;
  }
  
  /* overlays pixel_data2 over the bitmap at given offsets */
  x_shift = (x_offset < 0) ? 0:
                             x_offset;
  y_shift = (y_offset < 0) ? 0:
                             y_offset;
  input_iter = 0;
  res_iter = y_shift*bytes_in_line;
  for (int i=0; i<img_height2; i++) {
      res_iter += x_shift*num_colors;
      for (int j=0; j<img_width2*num_colors; j++) {
          res_pixel_data[res_iter++] = pixel_data2[input_iter++];
      }
      res_iter += bytes_in_line - num_colors*(x_shift + img_width2);
      input_iter += padding2;
  }
  
  /* write res_data to bmp_result */
  FILE *file = fopen(bmp_result, "wb");
  if (fwrite(res_data, sizeof(unsigned char), res_data_size, file) != res_data_size) {
      printf("Error writing collage to file.\n");
      return -1;
  }
  fclose(file);
  free(res_data);
  res_data = NULL;
  // TO HERE!
      
  bmp_close( &img_data1 );
  bmp_close( &img_data2 );
  
  return 0;
}                  
