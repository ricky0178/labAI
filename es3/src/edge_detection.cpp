#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "image.h"

#define M_PI 3.14159265358979323846


/*
Smooths a grayscale image by convolving it with a Gaussian kernel of standard deviation sigma.
Input:
    Image im: the input image
    float sigma: the standard deviation of the Gaussian kernel
Output:
    Image: the smoothed image (im.w, im.h, 1)
*/
Image smooth_image(const Image& im, float sigma)
{
    return convolve_image(im, make_gaussian_filter(sigma), false);
}


/*
Computes the magnitude and direction of the gradient of an image.
Input:
    Image im: the input image
Output:
    pair<Image,Image>: the magnitude and direction of the gradient of the image
                       with magnitude in [0,1] and direction in [-pi,pi
*/
pair<Image,Image> compute_gradient(const Image& im)
{
    pair<Image,Image> pair = sobel_image(im);
    Image mag = pair.first;

    feature_normalize(mag);
    return {mag, pair.second};
}


/*
Performs non-maximum suppression on an image.
Input:
    Image mag: the magnitude of the gradient of the image [0,1]
    Image dir: the direction of the gradient of the image [-pi,pi]
Output:
    Image: the image after non-maximum suppression
*/
Image non_maximum_suppression(const Image& mag, const Image& dir)
{
    Image nms(mag.w, mag.h, 1);
    float neighbor1, neighbor2;

    // Iterate through the image and perform non-maximum suppression
    for (int y = 0; y < mag.h; y++) {
        for (int x = 0; x < mag.w; x++) {
            
            // TODO: Your code here
            float current_mag = mag.clamped_pixel(x, y);
            // Get the direction of the gradient at the current pixel
            float current_dir = dir.clamped_pixel(x, y);
            // Round the direction to the nearest multiple of PI/4
            float bef_diff = INFINITY, curr_diff, next_diff, now, next, multiplier = -4;
            while(multiplier <= 4){
                now = multiplier*(M_PI/4);
                next = (multiplier+1)*(M_PI/4);
                curr_diff = abs(current_dir - now);
                next_diff = abs(current_dir - next);
                if(curr_diff<=bef_diff && curr_diff <= next_diff){
                    break;
                }
                bef_diff = curr_diff;
                multiplier++;
            }

            // Get the magnitude of the gradient of the two neighbors along that direction
            // (Hint: use clamped_pixel to avoid going out of bounds)            

            int x_new = round(cos(now));
            int y_new = round(sin(now));
            neighbor1 = mag.clamped_pixel(x+x_new, y+y_new);
            neighbor2 = mag.clamped_pixel(x-x_new, y-y_new);
            // If the magnitude of the gradient of the current pixel is greater than that of both neighbors,
            // then it is a local maximum

            if(current_mag >= neighbor1 && current_mag >= neighbor2){
                nms(x,y) = current_mag;
            }
            else{
                nms(x,y) = 0;
            }
        }
    }

    return nms;
}



/*
    Applies double thresholding to an image.
    Input:
        Image im: the input image
        float lowThreshold: the low threshold value
        float highThreshold: the high threshold value
        float strongVal: the value to use for strong edges
        float weakVal: the value to use for weak edges
    Output:
        Image: the thresholded image
*/
Image double_thresholding(const Image& im, float lowThreshold, float highThreshold, float strongVal, float weakVal)
{
    Image res(im.w, im.h, im.c);

    for(int c = 0; c < res.c; c++){
        for(int x = 0; x < res.w; x++){
            for(int y = 0; y < res.h; y++){
                float pixel = im(x,y,c);
                if(pixel > lowThreshold){
                    if(pixel < highThreshold){
                        pixel = weakVal;
                    } else{
                        pixel = strongVal;
                    }
                } else{
                    pixel = 0;
                }
                res(x,y,c) = pixel;
            }
        }
    }

    return res;
}


/*
    Applies hysteresis thresholding to an image.
    Input:
        Image im: the input image
        float weak: the value of the weak edges
        float strong: the value of the strong edges
    Output:
        Image: the image after hysteresis thresholding, with only strong edges
*/
Image edge_tracking(const Image& im, float weak, float strong)
{
    Image res(im.w, im.h, im.c);

    for (int y=0; y < im.h; ++y) {
        for (int x=0; x < im.w; ++x) {
            if(im(x,y) == weak){
                res(x,y) = 0;
                for(int i = -1; i <= 1; i++){
                    for(int j = -1; j <= 1; j++){
                        if(im.clamped_pixel(x+i, y+j) == strong){
                            res(x,y) = strong;
                            break;
                        }
                    }
                }
            } else{
                res(x,y) = im(x,y);
            }
        }
    }
    return res;

}
