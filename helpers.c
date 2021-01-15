#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float Red, Green, Blue;
    int avg;

    //loop through rows and initialise values
    for (int i = 0; i < height; i++)
    {
        Red = Green = Blue = avg = 0;

        //loop through columns
        for (int j = 0; j < width; j++)
        {
            //extract channel value and compute average
            Red = image[i][j].rgbtRed;
            Green = image[i][j].rgbtGreen;
            Blue = image[i][j].rgbtBlue;

            avg = round((Red + Green + Blue) / 3);

            //Assign average value to each channel
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;

    //loop through each row
    for (int i = 0; i < height; i++)
    {
        //loop through each column
        for (int j = 0 ; j < width / 2; j++) //keep swapping until halfway or the pixels swap back
        {
            //assign pixel to temp and replace with reflection pixel
            //then replace that pixel with temp
            temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float Red, Green, Blue;
    RGBTRIPLE temp[height][width];
    int count;

    //Create a temporay image array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    //Loop through rows
    for (int i = 0; i < height; i++)
    {
        //loop through columns and initialise values
        for (int j = 0; j < width; j++)
        {
            count = 0;
            Red = Blue = Green = 0;
            for (int l = i - 1; l <= i + 1; l++)
            {
                //move onto next step if pixel within image
                if (i + l >= 0 && l < height)
                {
                    for (int k = j - 1; k <= j + 1; k++)
                    {
                        if (j + k >= 0 && k < width)
                        {
                            //add to channel count
                            Red += temp[l][k].rgbtRed;
                            Green += temp[l][k].rgbtGreen;
                            Blue += temp[l][k].rgbtBlue;

                            count++;
                        }
                    }
                }
            }

            //find the channel number from respective total average
            int RedAvg = round(Red / count);
            int GreenAvg = round(Green / count);
            int BlueAvg = round(Blue / count);

            //assign new channel value to pixel in image
            image[i][j].rgbtRed = RedAvg;
            image[i][j].rgbtGreen = GreenAvg;
            image[i][j].rgbtBlue = BlueAvg;
        }
    }
    return;
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    float Redgx, Greengx, Bluegx, Redgy, Greengy, Bluegy;
    int Red, Green, Blue;
    RGBTRIPLE temp[height][width];

    //Initialise Sobel Array
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    //Create a temporary image array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    // loop through the rows
    for (int i = 0; i < height; i++)
    {
        //Loop through the columns
        for (int j = 0; j < width; j++)
        {
            //initialise G values
            Redgx = Greengx = Bluegx = Redgy = Greengy = Bluegy = 0;

            //loop through each row in the box
            for (int l = i - 1; l <= i + 1; l++)
            {
                if (i + l >= 0 && l < height)
                {
                    // if the pixel is not within the boundaries height and width move onto the next iteration
                    for (int k = j - 1; k <= j + 1; k++)
                    {

                        if (j + k >= 0 && k < width)
                        {
                            //Adding 1 to the l and k values so they are understood by G arrays
                            //pixels outside image are set to zero by omitting them in previous steps
                            //add 1 because Solber array
                            Redgx += temp[l][k].rgbtRed * Gx[l - i + 1][k - j + 1];
                            Greengx += temp[l][k].rgbtGreen * Gx[l - i + 1][k - j + 1];
                            Bluegx += temp[l][k].rgbtBlue * Gx[l - i + 1][k - j + 1];
                            Redgy += temp[l][k].rgbtRed * Gy[l - i + 1][k - j + 1];
                            Greengy += temp[l][k].rgbtGreen * Gy[l - i + 1][k - j + 1];
                            Bluegy += temp[l][k].rgbtBlue * Gy[l - i + 1][k - j + 1];
                        }
                    }
                }
            }

            //compute each new channel value as the square root of Gx^2 + Gy^2
            Red = round(sqrt(pow(Redgx, 2) + pow(Redgy, 2)));
            Green = round(sqrt(pow(Greengx, 2) + pow(Greengy, 2)));
            Blue = round(sqrt(pow(Bluegx, 2) + pow(Bluegy, 2)));

            //Capping max channel value
            if (Red > 255)
            {
                Red = 255;
            }
            if (Green > 255)
            {
                Green = 255;
            }
            if (Blue > 255)
            {
                Blue = 255;
            }

            //assign channel value to pixel in image
            image[i][j].rgbtRed = Red;
            image[i][j].rgbtGreen = Green;
            image[i][j].rgbtBlue = Blue;

        }
    }
    return;
}