#include <cstdio>
#include <math.h>
#include <iostream>
#include <math.h>
#include<bits/stdc++.h>
#include "bitmap_image.hpp"
using namespace std;


void biaspixel(bitmap_image& image){
   int width= image.width();
   int height=image.height();
   bitmap_image new_image(image);
   map< int, int> m;
   int max_val=0;
   unsigned char red,green,blue;
   for (std::size_t y = 0; y < height; ++y)
   {
      for (std::size_t x = 0; x < width; ++x)
      {
          m[image.red_channel(x,y)]++;
          max_val = max(max_val,(int)image.red_channel(x,y));
      }
   }
/*   int maxi=0,prev=0,val;
   for (map<int,int> :: iterator i = m.begin(); i!=m.end();++i)
   {
      maxi=max(maxi,i->second);
      if(prev!=maxi){
         prev=maxi;
         val = i->first;
      }
   }*/
   for (std::size_t y = 0; y < height; ++y)
   {
      for (std::size_t x = 0; x < width; ++x)
      {
         int p = image.red_channel(x,y);
         if(p!=max_val){
            new_image.red_channel(x,y,0);
         }
      }
   }   
   new_image.save_image("biased.bmp");  
}
void scale(bitmap_image& image);


int main()
{
   string img;
   img = "input2.bmp" ;

   bitmap_image image(img);

   if (!image)
   {
       printf("Error - Failed to open: input.bmp\n");
       return 1;
   }

   unsigned char red;
   unsigned char green;
   unsigned char blue;

   const unsigned int height = image.height();
   const unsigned int width  = image.width();

/* The following commmented code is for illustration of how to use 
 * the bitmap API for accessing and manipulating images.
 *
   // each image is represented as a set of pixels (height and width) 
   // with intensity levels of three colors/channels red, green, blue
   
   // create new 'blank' image with all pixel intensity values 
   // set at 0 for all colors (Note this image is complete black!)
   bitmap_image new_image(width,height);  
   
   for (std::size_t y = 0; y < height; ++y)
   {
      for (std::size_t x = 0; x < width; ++x)
      {
         // get the red,green,blue intensity levels for pixel x,y
	 // intensity values vary from 0 to 255
         image.get_pixel(x,y,red,green,blue); 

	 // set intensity values for each channel for pixel x,y 
	 new_image.set_pixel(x,y,red,green,blue); 
      }
   }

   // save new image to a file black.bmp
   new_image.save_image("black.bmp"); 
   
   // print image statistics 
   printf("Image width and height: %d and %d\n", width, height);

   // create new image based on an existing image
   //bitmap_image new_image(image);  // create new_image, same as image!
   //new_image.save_image("output.bmp");  // saves  new_image as output.bmp
*/

   // call to functions for each type of operation
   
   // for each of the 3 colors zero-out all pixels other than pixels biased with value.
   biaspixel(image);

   // scale image intensities to 0 to 255
  // scale(image);

   return 0;
}


