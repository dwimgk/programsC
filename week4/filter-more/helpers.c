#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float values_sum = 0;
            int average = 0;
            values_sum += image[i][j].rgbtBlue;
            values_sum += image[i][j].rgbtGreen;
            values_sum += image[i][j].rgbtRed;

            average = (int) round(values_sum / 3.0);

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }

    return;
}

int if_exceed_limit(int current_color)
{
    // the limit for each value in rgb of the sepia filter is 255
    if (current_color >= 255)
    {
        return 255;
    }
    else if (current_color <= 0)
    {
        return 0;
    }
    else
    {
        return current_color;
    }
}
// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalBlue = image[i][j].rgbtBlue;
            int originalGreen = image[i][j].rgbtGreen;
            int originalRed = image[i][j].rgbtRed;

            int sepiaRed = if_exceed_limit(
                round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue));
            int sepiaGreen = if_exceed_limit(
                round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue));
            int sepiaBlue = if_exceed_limit(
                round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue));

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (int) ceil(width / 2); j++)
        {
            RGBTRIPLE temp;

            // copy last pixel to temp
            temp.rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            temp.rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            temp.rgbtRed = image[i][width - 1 - j].rgbtRed;
            // copy first pixel to last index
            image[i][width - 1 - j].rgbtBlue = image[i][j].rgbtBlue;
            image[i][width - 1 - j].rgbtGreen = image[i][j].rgbtGreen;
            image[i][width - 1 - j].rgbtRed = image[i][j].rgbtRed;
            // copy from temp to first index
            image[i][j].rgbtBlue = temp.rgbtBlue;
            image[i][j].rgbtGreen = temp.rgbtGreen;
            image[i][j].rgbtRed = temp.rgbtRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int values_Red = 0;
            int values_Green = 0;
            int values_Blue = 0;
            int average_Red = 0;
            int average_Green = 0;
            int average_Blue = 0;
            int average_of_cells = 0;

            // CORNERS \/
            if (i == 0 && j == 0)
            {
                values_Blue += image[i][j].rgbtBlue;
                values_Blue += image[i][j + 1].rgbtBlue;
                values_Blue += image[i + 1][j].rgbtBlue;
                values_Blue += image[i + 1][j + 1].rgbtBlue;

                values_Green += image[i][j].rgbtGreen;
                values_Green += image[i][j + 1].rgbtGreen;
                values_Green += image[i + 1][j].rgbtGreen;
                values_Green += image[i + 1][j + 1].rgbtGreen;

                values_Red += image[i][j].rgbtRed;
                values_Red += image[i][j + 1].rgbtRed;
                values_Red += image[i + 1][j].rgbtRed;
                values_Red += image[i + 1][j + 1].rgbtRed;

                average_of_cells = 4;
            }
            else if (i == 0 && j == width - 1)
            {
                values_Blue += image[i][j].rgbtBlue;
                values_Blue += image[i][j - 1].rgbtBlue;
                values_Blue += image[i + 1][j].rgbtBlue;
                values_Blue += image[i + 1][j - 1].rgbtBlue;

                values_Green += image[i][j].rgbtGreen;
                values_Green += image[i][j - 1].rgbtGreen;
                values_Green += image[i + 1][j].rgbtGreen;
                values_Green += image[i + 1][j - 1].rgbtGreen;

                values_Red += image[i][j].rgbtRed;
                values_Red += image[i][j - 1].rgbtRed;
                values_Red += image[i + 1][j].rgbtRed;
                values_Red += image[i + 1][j - 1].rgbtRed;

                average_of_cells = 4;
            }
            else if (i == height - 1 && j == 0)
            {
                values_Blue += image[i][j].rgbtBlue;
                values_Blue += image[i][j + 1].rgbtBlue;
                values_Blue += image[i - 1][j].rgbtBlue;
                values_Blue += image[i - 1][j + 1].rgbtBlue;

                values_Green += image[i][j].rgbtGreen;
                values_Green += image[i][j + 1].rgbtGreen;
                values_Green += image[i - 1][j].rgbtGreen;
                values_Green += image[i - 1][j + 1].rgbtGreen;

                values_Red += image[i][j].rgbtRed;
                values_Red += image[i][j + 1].rgbtRed;
                values_Red += image[i - 1][j].rgbtRed;
                values_Red += image[i - 1][j + 1].rgbtRed;

                average_of_cells = 4;
            }
            else if (i == height - 1 && j == width - 1)
            {
                values_Blue += image[i][j].rgbtBlue;
                values_Blue += image[i][j - 1].rgbtBlue;
                values_Blue += image[i - 1][j].rgbtBlue;
                values_Blue += image[i - 1][j - 1].rgbtBlue;

                values_Green += image[i][j].rgbtGreen;
                values_Green += image[i][j - 1].rgbtGreen;
                values_Green += image[i - 1][j].rgbtGreen;
                values_Green += image[i - 1][j - 1].rgbtGreen;

                values_Red += image[i][j].rgbtRed;
                values_Red += image[i][j - 1].rgbtRed;
                values_Red += image[i - 1][j].rgbtRed;
                values_Red += image[i - 1][j - 1].rgbtRed;

                average_of_cells = 4;
            }
            // CORNERS ^

            // TOP AND BOTTOM EDGES
            else if (i == 0)
            {
                values_Blue += image[i][j - 1].rgbtBlue;
                values_Blue += image[i][j].rgbtBlue;
                values_Blue += image[i][j + 1].rgbtBlue;
                values_Blue += image[i + 1][j - 1].rgbtBlue;
                values_Blue += image[i + 1][j].rgbtBlue;
                values_Blue += image[i + 1][j + 1].rgbtBlue;

                values_Green += image[i][j - 1].rgbtGreen;
                values_Green += image[i][j].rgbtGreen;
                values_Green += image[i][j + 1].rgbtGreen;
                values_Green += image[i + 1][j - 1].rgbtGreen;
                values_Green += image[i + 1][j].rgbtGreen;
                values_Green += image[i + 1][j + 1].rgbtGreen;

                values_Red += image[i][j - 1].rgbtRed;
                values_Red += image[i][j].rgbtRed;
                values_Red += image[i][j + 1].rgbtRed;
                values_Red += image[i + 1][j - 1].rgbtRed;
                values_Red += image[i + 1][j].rgbtRed;
                values_Red += image[i + 1][j + 1].rgbtRed;

                average_of_cells = 6;
            }
            else if (i == height - 1)
            {
                values_Blue += image[i][j - 1].rgbtBlue;
                values_Blue += image[i][j].rgbtBlue;
                values_Blue += image[i][j + 1].rgbtBlue;
                values_Blue += image[i - 1][j - 1].rgbtBlue;
                values_Blue += image[i - 1][j].rgbtBlue;
                values_Blue += image[i - 1][j + 1].rgbtBlue;

                values_Green += image[i][j - 1].rgbtGreen;
                values_Green += image[i][j].rgbtGreen;
                values_Green += image[i][j + 1].rgbtGreen;
                values_Green += image[i - 1][j - 1].rgbtGreen;
                values_Green += image[i - 1][j].rgbtGreen;
                values_Green += image[i - 1][j + 1].rgbtGreen;

                values_Red += image[i][j - 1].rgbtRed;
                values_Red += image[i][j].rgbtRed;
                values_Red += image[i][j + 1].rgbtRed;
                values_Red += image[i - 1][j - 1].rgbtRed;
                values_Red += image[i - 1][j].rgbtRed;
                values_Red += image[i - 1][j + 1].rgbtRed;

                average_of_cells = 6;
            }

            // LEFT AND RIGHT EDGES
            else if (j == 0)
            {
                values_Blue += image[i - 1][j].rgbtBlue;
                values_Blue += image[i][j].rgbtBlue;
                values_Blue += image[i + 1][j].rgbtBlue;
                values_Blue += image[i - 1][j + 1].rgbtBlue;
                values_Blue += image[i][j + 1].rgbtBlue;
                values_Blue += image[i + 1][j + 1].rgbtBlue;

                values_Green += image[i - 1][j].rgbtGreen;
                values_Green += image[i][j].rgbtGreen;
                values_Green += image[i + 1][j].rgbtGreen;
                values_Green += image[i - 1][j + 1].rgbtGreen;
                values_Green += image[i][j + 1].rgbtGreen;
                values_Green += image[i + 1][j + 1].rgbtGreen;

                values_Red += image[i - 1][j].rgbtRed;
                values_Red += image[i][j].rgbtRed;
                values_Red += image[i + 1][j].rgbtRed;
                values_Red += image[i - 1][j + 1].rgbtRed;
                values_Red += image[i][j + 1].rgbtRed;
                values_Red += image[i + 1][j + 1].rgbtRed;

                average_of_cells = 6;
            }
            else if (j == width - 1)
            {
                values_Blue += image[i - 1][j].rgbtBlue;
                values_Blue += image[i][j].rgbtBlue;
                values_Blue += image[i + 1][j].rgbtBlue;
                values_Blue += image[i - 1][j - 1].rgbtBlue;
                values_Blue += image[i][j - 1].rgbtBlue;
                values_Blue += image[i + 1][j - 1].rgbtBlue;

                values_Green += image[i - 1][j].rgbtGreen;
                values_Green += image[i][j].rgbtGreen;
                values_Green += image[i + 1][j].rgbtGreen;
                values_Green += image[i - 1][j - 1].rgbtGreen;
                values_Green += image[i][j - 1].rgbtGreen;
                values_Green += image[i + 1][j - 1].rgbtGreen;

                values_Red += image[i - 1][j].rgbtRed;
                values_Red += image[i][j].rgbtRed;
                values_Red += image[i + 1][j].rgbtRed;
                values_Red += image[i - 1][j - 1].rgbtRed;
                values_Red += image[i][j - 1].rgbtRed;
                values_Red += image[i + 1][j - 1].rgbtRed;

                average_of_cells = 6;
            }

            else
            {
                values_Blue += image[i + 1][j - 1].rgbtBlue;
                values_Blue += image[i + 1][j].rgbtBlue;
                values_Blue += image[i + 1][j + 1].rgbtBlue;

                values_Blue += image[i][j - 1].rgbtBlue;
                values_Blue += image[i][j].rgbtBlue;
                values_Blue += image[i][j + 1].rgbtBlue;

                values_Blue += image[i - 1][j - 1].rgbtBlue;
                values_Blue += image[i - 1][j].rgbtBlue;
                values_Blue += image[i - 1][j + 1].rgbtBlue;

                values_Green += image[i + 1][j - 1].rgbtGreen;
                values_Green += image[i + 1][j].rgbtGreen;
                values_Green += image[i + 1][j + 1].rgbtGreen;

                values_Green += image[i][j - 1].rgbtGreen;
                values_Green += image[i][j].rgbtGreen;
                values_Green += image[i][j + 1].rgbtGreen;

                values_Green += image[i - 1][j - 1].rgbtGreen;
                values_Green += image[i - 1][j].rgbtGreen;
                values_Green += image[i - 1][j + 1].rgbtGreen;

                values_Red += image[i + 1][j - 1].rgbtRed;
                values_Red += image[i + 1][j].rgbtRed;
                values_Red += image[i + 1][j + 1].rgbtRed;

                values_Red += image[i][j - 1].rgbtRed;
                values_Red += image[i][j].rgbtRed;
                values_Red += image[i][j + 1].rgbtRed;

                values_Red += image[i - 1][j - 1].rgbtRed;
                values_Red += image[i - 1][j].rgbtRed;
                values_Red += image[i - 1][j + 1].rgbtRed;

                average_of_cells = 9;
            }

            average_Blue = round(values_Blue / average_of_cells);
            average_Green = round(values_Green / average_of_cells);
            average_Red = round(values_Red / average_of_cells);

            copy[i][j].rgbtBlue = if_exceed_limit(average_Blue);
            copy[i][j].rgbtGreen = if_exceed_limit(average_Green);
            copy[i][j].rgbtRed = if_exceed_limit(average_Red);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }

    return;
}
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // sobel
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float Gx_Blue = 0;
            float Gy_Blue = 0;

            float Gx_Green = 0;
            float Gy_Green = 0;

            float Gx_Red = 0;
            float Gy_Red = 0;
            // for each cell calc the surrounding ones
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }
                    Gx_Blue += copy[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1];
                    Gy_Blue += copy[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1];
                    Gx_Green += copy[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];
                    Gy_Green += copy[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];
                    Gx_Red += copy[i + k][j + l].rgbtRed * Gx[k + 1][l + 1];
                    Gy_Red += copy[i + k][j + l].rgbtRed * Gy[k + 1][l + 1];
                }
            }
            int blue_operator = if_exceed_limit(round(sqrt(Gx_Blue * Gx_Blue + Gy_Blue * Gy_Blue)));
            int green_operator =if_exceed_limit(round(sqrt(Gx_Green * Gx_Green + Gy_Green * Gy_Green)));
            int red_operator = if_exceed_limit(round(sqrt(Gx_Red * Gx_Red + Gy_Red * Gy_Red)));

            image[i][j].rgbtBlue = blue_operator;
            image[i][j].rgbtGreen = green_operator;
            image[i][j].rgbtRed = red_operator;
        }
    }
    return;
}
