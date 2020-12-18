#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //Input check function argc must = 2
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    int n = strlen(argv[1]);
    char keys[n];

    //Key check function
    for (int i = 0; i < n; i++)
    {
        //all values of argv[1][i] (key) must be alphabetical
        if (argv[1][i] < 'A' || argv[1][i] > 'z')
        {
            printf("Key must only contain alphabetical characters!\n");
            return 1;
        }
        //length of key must be 26
        else if (n != 26)
        {
            printf("Key must contain 26 characters!\n");
            return 1;
        }

        //assigning each character in key to keys[] array
        keys[i] = argv[1][i];

        //identifies if the key has a character that already exists in keys[], small or capital
        for (int j = 0; j < i; j++)
        {

            if (argv[1][i] == keys[j] || argv[1][i] == (keys[j] + 32) || argv[1][i] == (keys[j] - 32))
            {
                printf("Key cannot have repeated characters!\n");
                return 1;
            }
        }
    }

    //Encryption
    string p = get_string("plaintext: ");

    int a = strlen(p);
    char c[a];

    printf("ciphertext: ");

    for (int i = 0; i < a; i++)
    {
        //print lower case letters as lower case, -97 because 'a' = 97 so the result would be
        //the numerical position in the key, the same goes of upper case
        if (p[i] >= 'a' && p[i] <= 'z')
        {
            printf("%c", tolower(argv[1][p[i] - 97]));
        }
        else if (p[i] >= 'A' && p[i] <= 'Z')
        {
            printf("%c", toupper(argv[1][p[i] - 65]));
        }
        //Non numerical characters unchanged
        else
        {
            printf("%c", p[i]);
        }
    }
    printf("\n");
    return 0;

}