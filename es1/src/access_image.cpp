#include "image.h"
#include <cstring>
#include <chrono>
#include <iostream>

// HW0 #1
// const Image& im: input image
// int x,y: pixel coordinates
// int ch: channel of interest
// returns the 0-based location of the pixel value in the data array
int pixel_address(const Image &im, int x, int y, int ch) {
    return (im.w*im.h*ch) + (im.w*y + x);;
}

// HW0 #1
// const Image& im: input image
// int x,y,ch: pixel coordinates and channel of interest
// returns the value of the clamped pixel at channel ch
float get_clamped_pixel(const Image &im, int x, int y, int ch) {
    if(x>=im.w) {
        x = im.w-1;
    } else if(x<0){
        x = 0;        
    }

    if(y >= im.h){
        y = im.h-1;
    } else if(y<0){
        y = 0;
    }
    int addr = pixel_address(im, x, y, ch);

    float res = im.data[addr];
    return res;
}


// HW0 #1
// Image& im: input image
// int x,y,ch: pixel coordinates and channel of interest
void set_pixel(Image &im, int x, int y, int c, float value) {
    if((x >= im.w || x < 0) || (y >= im.h || y < 0))
        return;
    
    int addr = pixel_address(im, x, y, c);
    im.data[addr] = value;
}


// HW0 #2
// Copies an image
// Image& to: destination image
// const Image& from: source image
void copy_image(Image &to, const Image &from) {
    // allocating data for the new image
    to.data = (float *) calloc(from.w * from.h * from.c, sizeof(float));
    to.c = from.c;
    to.h = from.h;
    to.w = from.w;

    memcpy(to.data, from.data, to.w*to.h*to.c*sizeof(float));
}
