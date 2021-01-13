#include "helpers.h"
#include <math.h>

int cap_255(int number);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg;
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            RGBTRIPLE pixel = image[i][j];
            avg = round((pixel.rgbtBlue + pixel.rgbtRed + pixel.rgbtGreen)/3.0);
            pixel.rgbtBlue = avg;
            pixel.rgbtGreen = avg;
            pixel.rgbtRed = avg;
            image[i][j] = pixel;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int r,b,g;
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            r = image[i][j].rgbtRed;
            b = image[i][j].rgbtBlue;
            g = image[i][j].rgbtGreen;

            image[i][j].rgbtRed = cap_255((int) round(0.393 * r + 0.769 * g + 0.189 * b));
            image[i][j].rgbtGreen = cap_255((int) round(0.349 * r + 0.686 * g + 0.168 * b));
            image[i][j].rgbtBlue = cap_255((int) round(0.272 * r + 0.534 * g + 0.131 * b));
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i=0; i<height; i++) {
        for (int j=0; j<width/2; j++) {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE cpy_image[height][width];

    /* A copy of image is necessary here because, if we change one pixel's 
    original value, it may be needed in calculation by the next pixel */
    
    for (int i = 0; i < height; i += 1)
    {
        for (int j = 0; j < width; j += 1)
        {
            cpy_image[i][j].rgbtRed = image[i][j].rgbtRed;
            cpy_image[i][j].rgbtGreen = image[i][j].rgbtGreen;
            cpy_image[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i ++) {
        for (int j = 0; j < width ; j ++) {

            int sum_r=0,sum_b=0,sum_g=0;
            float count = 0.0;

            // Blur Box
            for (int a = -1; a <= 1; a++) {
                for (int b = -1; b <= 1; b++) {
                    int h_index = i + a;
                    int w_index = j + b;

                    if ((h_index >= 0) && (h_index <= height - 1) && (w_index >= 0) && (w_index <= width - 1)) {
                        sum_r += cpy_image[h_index][w_index].rgbtRed;
                        sum_g += cpy_image[h_index][w_index].rgbtGreen;
                        sum_b += cpy_image[h_index][w_index].rgbtBlue;
                        count++;
                    }
                }
            }
            image[i][j].rgbtRed = round(sum_r / count);
            image[i][j].rgbtGreen = round(sum_g / count);
            image[i][j].rgbtBlue = round(sum_b / count);
        }
    }
    return;
}


int cap_255(int number) {
    if (number > 255) return 255;
    else return number;
}