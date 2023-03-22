#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool only_digits(string argv);


int main(int argc, string argv[])
{
    //Sadece bir command line argumand kabul eden kod
    if (argc != 2 || only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string text = get_string("plaintext: ");
    printf("ciphertext: ");

    //Harfleri dönüştüren kod
    for (int i = 0 , length = strlen(text) , key = atoi(argv[1]); i < length; i++)
    {
        if (isupper(text[i]))
        {
            text[i] += key % 26;

            if (text[i] > 'Z')
            {
                text[i] -= 26;
            }
            printf("%c" , text[i]);
        }
        else if (islower(text[i]))
        {
            text[i] -= 26;
            text[i] += key % 26;

            if (text[i] < 'a')
            {
                text[i] += 26;
            }
            printf("%c" , text[i]);
        }
        else
        {
            printf("%c" , text[i]);
        }
    }
    printf("\n");
}

//Sadece sayıları kabul eden kod
bool only_digits(string argv)
{
    for (int i = 0 , length = strlen(argv); i < length; i++)
    {
        if (argv[i] < '0' || argv[i] > '9')
        {
            return true;
        }
    }
    return false;

}