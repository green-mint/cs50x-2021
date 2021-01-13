#include "bmp.h"
#include <stdio.h>

RGBTRIPLE a;
a.rgbtRed 

RGBTRIPLE image[2][1] = {{}}

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i=0; i<height; i++) {
        for (int j=0; j<width/2; j++) {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - j];
            image[i][width - j] = tmp;
        }
    }
    return;
}