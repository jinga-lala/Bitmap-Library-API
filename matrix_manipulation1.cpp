#include <cstdio>
#include <math.h>
#include <iostream>
#include <math.h>
#include "bitmap_image.hpp"
using namespace std;

void hflip(bitmap_image&);
void vflip(bitmap_image&);
void rotate(bitmap_image&,float);
void rotateright(bitmap_image&);
void vmirror(bitmap_image&);
void fourinone(bitmap_image&);
void translate(bitmap_image&,int,int); //Shift the image by x pixels to the Right and y pixels below
void wraparound(bitmap_image&,int,int);

void hflip(bitmap_image& image){
   int width= image.width();
   int height=image.height();
   bitmap_image new_image(width,height);
   
   //int h = b.height();
   unsigned char red,green,blue;
   for (std::size_t y = 0; y < height; ++y)
   {
      for (std::size_t x = 0; x < width; ++x)
      {
          image.get_pixel(x,y,red,green,blue);
          new_image.set_pixel(width-x-1,y,red,green,blue);
      }
   }
   new_image.save_image("hflip.bmp");
}
bitmap_image hflipnew(bitmap_image& image){
   int width= image.width();
   int height=image.height();
   bitmap_image new_image(width,height);
   
   //int h = b.height();
   unsigned char red,green,blue;
   for (std::size_t y = 0; y < height; ++y)
   {
      for (std::size_t x = 0; x < width; ++x)
      {
          image.get_pixel(x,y,red,green,blue);
          new_image.set_pixel(width-x-1,y,red,green,blue);
      }
   }
   return new_image;
}
void vflip(bitmap_image& image){
   int width= image.width();
   int height=image.height();
   bitmap_image new_image(width,height);
   
   //int h = b.height();
   unsigned char red,green,blue;
   for (std::size_t y = 0; y < height; ++y)
   {
      for (std::size_t x = 0; x < width; ++x)
      {
          image.get_pixel(x,y,red,green,blue);
          new_image.set_pixel(x,height-y-1,red,green,blue);
      }
   }
   new_image.save_image("vflip.bmp");
}

void rotate(bitmap_image& image, float theeta){
   int width= image.width();
   int height=image.height();
   bitmap_image new_image(width,height);
   unsigned char red,green,blue;
   int cx= width/2;
   int cy = height/2;
   float angle;   
   for (std::size_t y = 0; y < height; ++y)
   {
      //cout<<"outside "<<y<<endl;
      for (std::size_t x = 0; x < width; ++x)
      {
          //cout<<y<<" "<<(int)y-cy<<endl;
         float n,m;
         image.get_pixel(x,y,red,green,blue);

         float r= sqrt(((int)x-(int)cx)*((int)x-(int)cx) + ((int)y-(int)cy)*((int)y-(int)cy));
         n = (int)y-(int)cy;
         m =(int)x-(int)cx;
         float s =sin(theeta);
         float c =cos(theeta);
         int p = m*c-n*s + cx;
         int q = n*c+m*s + cy;
         if( p >=0 && p < width &&q >=0 && q < height)
            new_image.set_pixel(p,q,red,green,blue);
      }
   }
   new_image.save_image("rotated.bmp");

}  

void rotateright(bitmap_image& image){
   double theeta = acos(0.0);
   int width= image.width();
   int height=image.height();
   bitmap_image new_image(height,width);
   unsigned char red,green,blue;
   int cx= width/2;
   int cy = height/2;
   float angle;  
   for (std::size_t y = 0; y < height; ++y)
   {
      //cout<<"outside "<<y<<endl;
      for (std::size_t x = 0; x < width; ++x)
      {
          //cout<<y<<" "<<(int)y-cy<<endl;
         float n,m;
         image.get_pixel(x,y,red,green,blue);
         new_image.set_pixel(height-y-1,x,red,green,blue);
         //new_image = hflipnew(new_image);
      }
   }
   new_image.save_image("rotatedright.bmp");

}


void fourinone(bitmap_image& image){
   int width= image.width();
   int height=image.height();
   bitmap_image new_image(width,height);
   
   //int h = b.height();
   unsigned char red,green,blue;
   size_t a = 0,b=0;
   for (std::size_t y = 0; y < height; ++y)
   {
      for (std::size_t x = 0; x < width; ++x)
      {
          image.get_pixel(x,y,red,green,blue);
          new_image.set_pixel(a++,b,red,green,blue);
          x=x+1;
      }
      y=y+1;b++;a=0;
   }
   a=width/2;
   for (std::size_t y = 0; y < height; ++y)
   {
      for (std::size_t x = 0; x < width; ++x)
      {
         new_image.get_pixel(x%a,y%b,red,green,blue);
         new_image.set_pixel(x,y,red,green,blue);
      }
   }
   new_image.save_image("4in1.bmp");
}


void translate(bitmap_image& image,int tx,int ty){
   int width= image.width();
   int height=image.height();
   bitmap_image new_image(width,height);
   
   //int h = b.height();
   unsigned char red,green,blue;
   for (std::size_t y = 0; y < height; ++y)
   {
      for (std::size_t x = 0; x < width; ++x)
      {
          image.get_pixel(x,y,red,green,blue);
          if(x+tx < width && y+ty < height && y >=0 && x >=0)
          new_image.set_pixel(x+tx,y + ty,red,green,blue);
      }
   }
   new_image.save_image("translated.bmp");
}

void wraparound(bitmap_image& image,int tx,int ty){
   int width= image.width();
   int height=image.height();
   bitmap_image new_image(width,height);
   
   //int h = b.height();
   unsigned char red,green,blue;
   for (std::size_t y = 0; y < height; ++y)
   {
      for (std::size_t x = 0; x < width; ++x)
      {
          image.get_pixel(x,y,red,green,blue);
          new_image.set_pixel((x+tx)% width,(y + ty)%height,red,green,blue);
      }
   }
   new_image.save_image("wrappedaround.bmp");  
}

void vmirror(bitmap_image& image){
   int width= image.width();
   int height=image.height();
   bitmap_image new_image(width,height);
   new_image= hflipnew(image);
   //int h = b.height();
   unsigned char red,green,blue;
   for (std::size_t y = 0; y < height; ++y)
   {
      for (std::size_t x = 0; x < width/2; ++x)
      {
          image.get_pixel(x,y,red,green,blue);
          new_image.set_pixel(x,y,red,green,blue);
      }
   }
   new_image.save_image("vmirror.bmp");
}

int main()
{
   string img;
   float theta;
   float cost,sint;
   img = "input.bmp" ;
   theta = 0.45;
   cost=cos(theta);
   sint=sin(theta);

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
   hflip(image);
   vflip(image);
   rotate(image,theta);
   rotateright(image);  
   translate(image,40, 50); 
   wraparound(image,40, 50);
   fourinone(image);
   vmirror(image);

}

