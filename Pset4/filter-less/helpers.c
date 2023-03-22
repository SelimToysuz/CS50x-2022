#include "helpers.h"
#include <math.h>


int rearrange(float colour);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE original = image[i][j];

            image[i][j].rgbtRed =
                rearrange(.393 * original.rgbtRed + .769 * original.rgbtGreen + .189 * original.rgbtBlue);
            image[i][j].rgbtGreen =
                rearrange(.349 * original.rgbtRed + .686 * original.rgbtGreen + .168 * original.rgbtBlue);
            image[i][j].rgbtBlue =
                rearrange(.272 * original.rgbtRed + .534 * original.rgbtGreen + .131 * original.rgbtBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, k = 1, middle = round((width / 2) - 0.5); j < middle; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - k];
            image[i][width - k] = temp;

            k++;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE originals[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originals[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float totalRed = 0;
            float totalGreen = 0;
            float totalBlue = 0;
            float piece = 0;

            for (int k = (i - 1); k < (i + 2); k++)
            {
                if (k < 0 || k >= height)
                {
                    continue;
                }

                for (int l = (j - 1); l < (j + 2); l++)
                {
                    if (l < 0 || l >= width)
                    {
                        continue;
                    }

                    totalRed += originals[k][l].rgbtRed;
                    totalGreen += originals[k][l].rgbtGreen;
                    totalBlue += originals[k][l].rgbtBlue;
                    piece++;
                }
            }
            image[i][j].rgbtRed = rearrange(totalRed / piece);
            image[i][j].rgbtGreen = rearrange(totalGreen / piece);
            image[i][j].rgbtBlue = rearrange(totalBlue / piece);
        }
    }
    return;
}

// 255'den büyük olanları tespit ediyor
int rearrange(float colour)
{
    colour = round(colour);

    if (colour > 255)
    {
        colour = 255;
    }
    return colour;
}
