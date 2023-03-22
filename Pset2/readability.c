#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string Text = get_string("Text: ");
    int letter = count_letters(Text);
    float word = count_words(Text);
    int sentence = count_sentences(Text);

    //printf("%i\n",letter);
    //printf("%f\n",word);
    //printf("%i\n",sentence);

    float grade = 5.88 * letter / word - 29.6 * sentence / word - 15.8;
    //printf("%f\n",grade);
    grade = (float) round(grade);

    //printf("%i\n",grade);

    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int) grade);
    }
}

//Harf sayısını hesaplayan kod
int count_letters(string text)
{
    int letter = 0;

    for (int i=0 , length = strlen(text); i<length; i++)
    {
        if (isalpha(text[i]))
        {
            letter++;
        }
    }
    return letter;
}

//Kelime sayısını hesaplayan kod
int count_words(string text)
{
    int word = 1;

    for (int i=0 , length = strlen(text); i<length; i++)
    {
        if (text[i] == ' ')
        {
            word++;
        }
    }
    return word;
}

//Cümle sayısını hesaplayan kod
int count_sentences(string text)
{
    int sentence = 0;

    for (int i=0 , length = strlen(text); i<length; i++)
    {
        if (text[i] == '!' || text[i] == '?' || text[i] == '.')
        {
            sentence++;
        }
    }
    return sentence;
}