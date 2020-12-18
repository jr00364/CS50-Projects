#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    //Gets the required hieight of teh pyramids
    do 
    {
        n = get_int("height: ");
    }
    //The numeric conditions which get_int runs again
    while (n < 1 || n > 8); 
    //Creating new lines
    for (int i = 0; i < n; i++)
    {
        //Creating spaces for the first pyramid
        for (int j = (n - 2); j >= i; j--)
        {
            printf(" ");
        }
        //Creating blocks
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }
        //Creating the space between the two pyramids
        printf("  ");
        //Creating blocks (same as before)
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }
        //Starting a new line
        printf("\n");
    }

}