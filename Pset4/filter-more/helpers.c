#include "helpers.h"
#include <math.h>

typedef struct
{
    float totalRed;
    float totalGreen;
    float totalBlue;
}
total;

int rearrange(float colour);
total gx(int i, int j, int height, int width, RGBTRIPLE originals[height][width]);
total gy(int i, int j, int height, int width, RGBTRIPLE originals[height][width]);

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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
            total x = gx(i, j, height, width, originals);
            total y = gy(i, j, height, width, originals);

            image[i][j].rgbtRed = rearrange(pow((x.totalRed + y.totalRed), .5));
            image[i][j].rgbtGreen = rearrange(pow((x.totalGreen + y.totalGreen), .5));
            image[i][j].rgbtBlue = rearrange(pow((x.totalBlue + y.totalBlue), .5));
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

//Gx sayısını buluyor ve karesini alıyor.
total gx(int i, int j, int height, int width, RGBTRIPLE originals[height][width])
{
    total totals;

    float totalRed = 0;
    float totalGreen = 0;
    float totalBlue = 0;

    for (int k = (i - 1); k < (i + 2); k++)
    {
        if (k < 0 || k >= height)
        {
            continue;
        }

        for (int l = (j - 1); l < (j + 2); l++)
        {
            if (l < 0 || l >= width || l == j)
            {
                continue;
            }

            if (l < j)
            {
                if (k == i)
                {
                    totalRed += (-2 * (originals[k][l].rgbtRed));
                    totalGreen += (-2 * (originals[k][l].rgbtGreen));
                    totalBlue += (-2 * (originals[k][l].rgbtBlue));
                }

                else
                {
                    totalRed += (-1 * (originals[k][l].rgbtRed));
                    totalGreen += (-1 * (originals[k][l].rgbtGreen));
                    totalBlue += (-1 * (originals[k][l].rgbtBlue));
                }
            }

            if (l > j)
            {
                if (k == i)
                {
                    totalRed += 2 * (originals[k][l].rgbtRed);
                    totalGreen += 2 * (originals[k][l].rgbtGreen);
                    totalBlue += 2 * (originals[k][l].rgbtBlue);
                }

                else
                {
                    totalRed += (originals[k][l].rgbtRed);
                    totalGreen += (originals[k][l].rgbtGreen);
                    totalBlue += (originals[k][l].rgbtBlue);
                }
            }
        }
    }

    totals.totalRed = pow(totalRed, 2);
    totals.totalGreen = pow(totalGreen, 2);
    totals.totalBlue = pow(totalBlue, 2);

    return totals;
}

//Gy sayısını buluyor ve karesini alıyor.
total gy(int i, int j, int height, int width, RGBTRIPLE originals[height][width])
{
    total totals;

    float totalRed = 0;
    float totalGreen = 0;
    float totalBlue = 0;

    for (int k = (i - 1); k < (i + 2); k++)
    {
        if (k < 0 || k >= height || k == i)
        {
            continue;
        }

        for (int l = (j - 1); l < (j + 2); l++)
        {
            if (l < 0 || l >= width)
            {
                continue;
            }

            if (k < i)
            {
                if (l == j)
                {
                    totalRed += -2 * (originals[k][l].rgbtRed);
                    totalGreen += -2 * (originals[k][l].rgbtGreen);
                    totalBlue += -2 * (originals[k][l].rgbtBlue);
                }

                else
                {
                    totalRed += -1 * (originals[k][l].rgbtRed);
                    totalGreen += -1 * (originals[k][l].rgbtGreen);
                    totalBlue += -1 * (originals[k][l].rgbtBlue);
                }
            }

            if (k > i)
            {
                if (l == j)
                {
                    totalRed += 2 * (originals[k][l].rgbtRed);
                    totalGreen += 2 * (originals[k][l].rgbtGreen);
                    totalBlue += 2 * (originals[k][l].rgbtBlue);
                }

                else
                {
                    totalRed += (originals[k][l].rgbtRed);
                    totalGreen += (originals[k][l].rgbtGreen);
                    totalBlue += (originals[k][l].rgbtBlue);
                }
            }
        }
    }

    totals.totalRed = pow(totalRed, 2);
    totals.totalGreen = pow(totalGreen, 2);
    totals.totalBlue = pow(totalBlue, 2);

    return totals;
}