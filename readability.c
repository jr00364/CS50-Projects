#include <cs50.h>
#include <stdio.h>
#include <string.h> 
#include <math.h>

float grade(int letters, int words, int sentences);
int sentenceCount(string s);
int wordCount(string s);
int letterCount(string s);
int main(void)
{
    string s = get_string("Text: ");
    int letters = letterCount(s);
    //printf("%i letter(s)\n", letters);

    int words = wordCount(s);
    //printf("%i words(s)\n", words);
    
    int sentences = sentenceCount(s);
    //printf("%i sentences(s)\n", sentences);
   
    float grading = grade(letters, words, sentences);
    {
        if (grading < 1)
        {
            printf("Before Grade 1\n");
        }
        else if (grading >= 16)
        {
            printf("Grade 16+\n");
        }
        else
        {
        printf("Grade %i\n", (int) round(grading));
        }
    }
}

//Coleman-Liau index
float grade(int letters, int words, int sentences)
{
    float index = 0.0588 * (((float)letters/(float)words) * 100) - 0.296 * (((float)sentences/(float)words) * 100) - 15.8;
    return index;
}

//Number of sentences
int sentenceCount(string s)
{
    int counter = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        //sentence ending puctuation
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            counter++;
        }
    }
    return counter;
}

//Number of words
int wordCount(string s)
{
    int counter = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        //if theres a space followed by a letter or punctuation it will be counted as a word
        if ((s[i] == ' ' && (s[i + 1] >= 'a' || s[i + 1] >= 'A') && (s[i + 1] <= 'z' || s[i + 1] <= 'Z')) || 
        (s[i] == ' ' && (s[i + 1] == '"' || s[i + 1] == '(' || s[i + 1] == '['))) 
        {
            counter ++;
        }
    }
    // counter + 1 as theres no space after the last word
    return counter + 1;
}

//Number of letters
int letterCount(string s)
{
    int counter = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        //if s[i] is a letter 
        if ((s[i] >= 'a' || s[i] >= 'A') && (s[i] <= 'z' || s[i] <= 'Z'))
        {
            counter++;
        }
    }
    return counter;
}
