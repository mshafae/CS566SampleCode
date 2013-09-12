/* Your Name Here
* somebody at something dot TLD
* CS 566
* September 20XX
*
*/
/*
 * Copyright (c) 2005-2013 Michael Shafae
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met: 
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * $Id: Image.cpp 4419 2013-09-12 04:16:46Z mshafae $
 *
 *
 *
 * The image class defines a trivial encoding for images known as PPM
 * format; it simply consists of an array or RGB triples, with one byte
 * per component, preceeded by a simple header giving the size of the
 * image.
 */

#include "Image.h"

std::ostream& operator <<( std::ostream &out, const Pixel &p ){
  p.write( out );
  return( out );
}


Pixel& Image::operator()( int i, int j ) { return *( pixels + ( i * width + j ) ); }  

Image::Image( int x_res, int y_res ){
  width  = x_res;
  height = y_res;
  pixels = new Pixel[ width * height ];
  Pixel *p = pixels;
  for( int i = 0; i < width * height; i++ ) *p++ = Pixel(0,0,0);
}

unsigned char* Image::read( const char *file_name ){
  char buffer[100];
  FILE *fp;
  int size_x, size_y, maxval;
  unsigned char c;
  int i;

  // open file
  if ((fp=fopen (file_name, "rb"))==NULL){
    fprintf (stderr, "unable to open file%c\n", 7);
    exit (1);
  }

  // read file identifier (magic number)
  fgets (buffer, sizeof (buffer), fp);
  if ((buffer[0] != 'P') || (buffer[1] != '6')){
    fprintf (stderr, "incorrect file type%c\n", 7);
    exit (1);
  }

  // read image size
  do
    fgets (buffer, sizeof (buffer), fp);
  while (buffer[0] == '#' || buffer[0] == ' ');

  sscanf (buffer, "%d %d", &size_x, &size_y);

  printf( "Image width: %d, Image height: %d\n", size_x, size_y );

  // read maximum pixel value (usually 255)
  do{
    fgets (buffer, sizeof (buffer), fp);
  }while (buffer[0] == '#');

  sscanf (buffer, "%d", &maxval);

  // allocate RGBA texture buffer
  unsigned char *texture = (unsigned char *)malloc(size_x*size_y*4*sizeof(unsigned char));

  // read RGB data and calculate alpha value
  for (i=0; i < size_x*size_y*4; i++){
    // insert alpha value (0 or 255) after each RGB
    if ((i%4) == 3){
      // alpha channel example: make all nearly black pixels transparent
      texture[i]=(unsigned char)
        (((texture[i-3]+texture[i-2]+texture[i-1])<10)?0:255);
    }else{
      c=fgetc(fp);
      texture[i]=(unsigned char) c;
    }
  }

  // close input file
  fclose(fp);
  return(texture);
}

bool Image::write( const char *file_name ){
  Pixel *p = pixels;
  FILE  *fp = fopen( file_name, "w+b" );
  if( fp == NULL ){
    return false;
  }
  fprintf( fp, "P6\n%d %d\n255\n", width, height );
  for( int i = 0; i < width * height; i++ ){
    fprintf( fp, "%c%c%c", p->r, p->g, p->b );
    p++;
  }
  fclose( fp );
  return true;
}
