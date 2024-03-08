#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>

#include "image.h"

using namespace std;

// HW0 #3
// const Image& im: input image
// return the corresponding grayscale image
Image rgb_to_grayscale(const Image &im) {
    assert(im.c == 3); // only accept RGB images
    Image gray(im.w,im.h,1); // create a new grayscale image (note: 1 channel)
    
    for(int i = 0; i < im.w; i++){
        for (int j = 0; j < im.h; j++){
            float gray_val = 0.299*get_clamped_pixel(im,i,j,0) + \
                0.587*get_clamped_pixel(im,i,j,1) + 0.114*get_clamped_pixel(im,i,j,2);
            set_pixel(gray, i, j, 0, gray_val);
        }
    }
    return gray;
}


// Example function that changes the color of a grayscale image
Image grayscale_to_rgb(const Image &im, float r, float g, float b) {
    assert(im.c == 1);
    Image rgb(im.w, im.h, 3);

    for (int q2 = 0; q2 < im.h; q2++)
        for (int q1 = 0; q1 < im.w; q1++) {
            rgb(q1, q2, 0) = r * im(q1, q2);
            rgb(q1, q2, 1) = g * im(q1, q2);
            rgb(q1, q2, 2) = b * im(q1, q2);
        }

    return rgb;
}


// HW0 #4
// Image& im: input image to be modified in-place
// int c: which channel to shift
// float v: how much to shift
void shift_image(Image &im, int c, float v) {
    assert(c>=0 && c<im.c); // needs to be a valid channel
    for(int i = 0; i < im.w; i++){
        for(int j = 0; j < im.h; j++){
            float val = get_clamped_pixel(im, i, j, c);
            val += v;
            set_pixel(im, i, j, c, val);
        }
    }
}

// HW0 #8
// Image& im: input image to be modified in-place
// int c: which channel to scale
// float v: how much to scale
void scale_image(Image &im, int c, float v) {
    assert(c>=0 && c<im.c); // needs to be a valid channel

    for(int i = 0; i < im.w; i++){
        for(int j = 0; j < im.h; j++){
            float val = get_clamped_pixel(im, i, j, c);
            val *= v;
            set_pixel(im, i, j, c, val);
        }
    }
}


// HW0 #5
// Image& im: input image to be modified in-place
void clamp_image(Image &im) {
    for(int k = 0; k < im.c; k++){
        for(int i = 0; i < im.w; i++){
            for(int j = 0; j < im.h; j++){
                float val = get_clamped_pixel(im, i, j, k);
                if(val < 0) {
                    val = 0;
                } else if(val > 1){
                    val = 1;
                } 
                set_pixel(im, i, j, k, val);
            }
        }
    }
}

// These might be handy
float max(float a, float b, float c) {
    return max({a, b, c});
}

float min(float a, float b, float c) {
    return min({a, b, c});
}


// HW0 #6
// Image& im: input image to be modified in-place
void rgb_to_hsv(Image &im) {
    assert(im.c==3 && "only works for 3-channels images");

    for(int i = 0; i < im.w; i++){
        for(int j = 0; j < im.h; j++){
            float r = get_clamped_pixel(im, i, j, 0); 
            float g = get_clamped_pixel(im, i, j, 1); 
            float b = get_clamped_pixel(im, i, j, 2);
            float value = max(r, g, b);
            float saturation = 0;
            float C = value - min(r, g, b);
            float hue = 0;
            if(value != 0){
                saturation = C / value;
            } if(C  != 0){
                float hcap = 0;
                if(value == r){
                    hcap = (g-b) / C;
                } else if(value == g){
                    hcap = ((b-r) / C) + 2; 
                } else{
                    hcap = ((r-g) / C) + 4;
                }
                hue = (hcap < 0)? (hcap/6)+1 : (hcap/6);
            }
            set_pixel(im, i, j, 0, hue); set_pixel(im, i, j, 1, saturation); set_pixel(im, i, j, 2, value);
        }
    }
}

// HW0 #7
// Image& im: input image to be modified in-place
void hsv_to_rgb(Image &im) {
    assert(im.c==3 && "only works for 3-channels images");

    for(int i = 0; i < im.w; i++){
        for(int j = 0; j < im.h; j++){
            float h = get_clamped_pixel(im, i, j, 0); 
            float s = get_clamped_pixel(im, i, j, 1); 
            float v = get_clamped_pixel(im, i, j, 2);

            float c = v*s;
            float x = c *(1 - abs(fmod(6*h, 2.0) - 1));
            float m = v-c;

            float r = 0;
            float g = 0;
            float b = 0;
            if(h >= 0.0 && h < 1.0/6){
                r = c+m;
                g = x+m;
                b = m;
            } else if(h>=1.0/6 && h < 2.0/6){
                r = x+m;
                g = c+m;
                b = m;
            } else if(h>=2.0/6 && h < 3.0/6){
                r = m;
                g = c+m;
                b = x+m;
            } else if(h>=3.0/6 && h < 4.0/6){
                r = m;
                g = x+m;
                b = c+m;
            } else if(h>=4.0/6 && h < 5.0/6){
                r = x+m;
                g = m;
                b = c+m;
            } else if(h>=5.0/6 && h < 1.0){
                r = c+m;
                g = m;
                b = x+m;
            }
            set_pixel(im, i, j, 0, r); 
            set_pixel(im, i, j, 1, g); 
            set_pixel(im, i, j, 2, b);
        }
    }
}

// HW0 #9
// Image& im: input image to be modified in-place
void rgb_to_lch(Image& im)
{
    assert(im.c==3 && "only works for 3-channels images");

    // TODO: Convert all pixels from RGB format to LCH format


    NOT_IMPLEMENTED();

}

// HW0 #9
// Image& im: input image to be modified in-place
void lch_to_rgb(Image& im)
{
    assert(im.c==3 && "only works for 3-channels images");

    // TODO: Convert all pixels from LCH format to RGB format

    NOT_IMPLEMENTED();

}


// Implementation of member functions
void Image::clamp(void) { clamp_image(*this); }

void Image::shift(int c, float v) { shift_image(*this, c, v); }

void Image::scale(int c, float v) { scale_image(*this, c, v); }

void Image::HSVtoRGB(void) { hsv_to_rgb(*this); }

void Image::RGBtoHSV(void) { rgb_to_hsv(*this); }

//void Image::LCHtoRGB(void) { lch_to_rgb(*this); }
