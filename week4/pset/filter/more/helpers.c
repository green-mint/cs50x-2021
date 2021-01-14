#include "helpers.h"
#include <math.h>


float min(float a, float b);
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++) {
        for (int j = 0; j < width; j ++) {
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++) {
        for (int j = 0; j < width/2. ; j ++) {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int Gy[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};

    RGBTRIPLE cpy_image[height][width];

    // make a copy of the image
    for (int i = 0; i < height; i += 1)
    {
        for (int j = 0; j < width; j += 1)
        {
            cpy_image[i][j].rgbtRed = image[i][j].rgbtRed;
            cpy_image[i][j].rgbtGreen = image[i][j].rgbtGreen;
            cpy_image[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width ; j ++)
        {
            float GxRed, GxBlue, GxGreen, GyRed, GyBlue, GyGreen;
            GxRed = GxBlue = GxGreen = GyRed = GyBlue = GyGreen = 0.0;


            for (int a = -1; a <= 1; a++)
            {
                for (int b = -1; b <= 1; b++)
                {
                    int image_height_index = i + a;
                    int image_width_index = j + b;
                    int kernel_height_index =  a + 1;
                    int kernel_width_index = b + 1;



                    if ((image_height_index >= 0) && (image_height_index <= height - 1) && (image_width_index >= 0) && (image_width_index <= width - 1))
                    {
                        
                        GxRed += cpy_image[image_height_index][image_width_index].rgbtRed * Gx[kernel_height_index][kernel_width_index];
                        GxBlue += cpy_image[image_height_index][image_width_index].rgbtBlue * Gx[kernel_height_index][kernel_width_index];
                        GxGreen += cpy_image[image_height_index][image_width_index].rgbtGreen * Gx[kernel_height_index][kernel_width_index];

                        GyRed += cpy_image[image_height_index][image_width_index].rgbtRed * Gy[kernel_height_index][kernel_width_index];
                        GyBlue += cpy_image[image_height_index][image_width_index].rgbtBlue * Gy[kernel_height_index][kernel_width_index];
                        GyGreen += cpy_image[image_height_index][image_width_index].rgbtGreen * Gy[kernel_height_index][kernel_width_index];

                    }
                }
            }

            image[i][j].rgbtRed = min(round(sqrt(pow(GxRed,2) + pow(GyRed,2))),255.0);
            image[i][j].rgbtGreen = min(round(sqrt(pow(GxGreen,2) + pow(GyGreen,2))),255.0);
            image[i][j].rgbtBlue = min(round(sqrt(pow(GxBlue,2) + pow(GyBlue,2))),255.0);
            
        }
    }

    return;
}

float min(float a, float b)
{
    if (a <= b)
    {
        return a;
    }
    else
    {
        return b;
    }
}