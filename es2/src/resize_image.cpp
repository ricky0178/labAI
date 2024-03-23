#include <cmath>
#include "image.h"

using namespace std;

// HW1 #1
// float x,y: inexact coordinates
// int c: channel
// returns the nearest neighbor to pixel (x,y,c)
float Image::pixel_nearest(float x, float y, int c) const
{
  return clamped_pixel(round(x), round(y), c);
}

// HW1 #1
// float x,y: inexact coordinates
// int c: channel
// returns the bilinearly interpolated pixel (x,y,c)
float Image::pixel_bilinear(float x, float y, int c) const
{
  // Since you are inside class Image you can
  // use the member function pixel(a,b,c)

  return 0;
}

// HW1 #1
// int w,h: size of new image
// const Image& im: input image
// return new Image of size (w,h,im.c)
Image nearest_resize(const Image &im, int w, int h)
{
  Image ret(w, h, im.c);

  // TODO: Your code here
  float scale_w = (float)w / im.w;
  float scale_h = (float)h / im.h;
  for (int z = 0; z < im.c; z++)
  {
    for (int x = 0; x < w; x++)
    {
      for (int y = 0; y < h; y++)
      {
        ret(x, y, z) = im.pixel_nearest(-1.0/2 + ((x+ (1.0/2)) / scale_w), 
                                        -1.0/2 + ((y+ (1.0/2)) / scale_h), z);
      }
    }
  }
  return ret;
}

// HW1 #1
// int w,h: size of new image
// const Image& im: input image
// return new Image of size (w,h,im.c)
Image bilinear_resize(const Image &im, int w, int h)
{

  // TODO: Your code here

  NOT_IMPLEMENTED();

  return Image();
}
