#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long cardNum;
    //Prompt user for credit card number
    do
    {
        cardNum = get_long("Insert card number: ");
    }
    //Card number should be greater than 0
    while(cardNum <= 0);

    //For first set of digits
    long testNum = cardNum;
    int firstSum = 0;

    //As we are dividing by a 100 we use a wile loop to scan the whole number
    while (testNum > 0)
    {
        //First Set of sums stating with the second to last number
        int secLastDigit = (testNum / 10) % 10;

        //Multiplying digit by 2 and adding to firstSum
        int timesTwo = secLastDigit * 2;
        //Adding the products of the digits together
        firstSum = firstSum + (timesTwo % 10) + (timesTwo / 10) % 10;

        //Moving two digits over
        testNum = testNum / 100;
    }
    //Second set of digits
    testNum = cardNum;
    int secondSum;
    while (testNum > 0)
    {
        //Second set of digits start with the last number
        int lastDigit = testNum % 10;
        //Summing these digits
        secondSum = secondSum + lastDigit;
        testNum = testNum / 100;
    }

    int C = secondSum + firstSum;
    //Use to check the Checksum
    //printf("Total sum: %i\n", checkSum);

    long testType = cardNum;
    long counter = 0;
    while (testType > 100)
    {
        //To get the first two digits
        testType = testType / 10;
        counter++;
    }
    if (testType < 100 && checkSum % 10 == 0)
    {
        //Counter two digits less that cardNum as showing first two digits
        //Test for AMEX
        if (counter == 13 && (testType == 34 || testType == 37))
        {
            printf("AMEX\n");
        }
        //Test for MASTERCARD
        else if (counter == 14 && testType > 50 && testType < 56)
        {
            printf("MASTERCARD\n");
        }
        //Test for VISA
        else if ((counter == 11 || counter == 14) && (testType / 10 == 4))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    //If checkSum is invalid
    else
    {
        printf("INVALID\n");
    }
    


}