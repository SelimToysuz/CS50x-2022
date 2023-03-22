#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool only_letters(string argv);
bool only_26(string argv);
bool different(string argv);

int main(int argc, string argv[])
{
    //Command line argumendin uygunluğunu kontrol eden kod
    if (argc != 2 || only_letters(argv[1]) || only_26(argv[1]) || different(argv[1]))
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string text = get_string("plaintext: ");
    printf("ciphertext: ");

    //Texti şifreli hala çeviren kod
    for (int i = 0 , length = strlen(text); i < length; i++)
    {
        if (islower(text[i]))
        {
            int s = text[i] - 'a';
            text[i] = tolower(argv[1][s]);
        }
        else if (isupper(text[i]))
        {
            int s = text[i] - 'A';
            text[i] = tolower(argv[1][s]) - 32;
        }
    }
    printf("%s\n", text);
}

//Sadece harfleri command line argumend olarak kabul eden kod
bool only_letters(string argv)
{
    for (int i = 0 , length = strlen(argv); i < length; i++)
    {
        if (isalpha(argv[i]) == 0)
        {
            return true;
        }
    }
    return false;
}

//Sadece 26 harfli command line argumend kabul eden kod
bool only_26(string argv)
{
    if (argv[26] == '\0')
    {
        return false;
    }
    return true;
}

//Tüm harflerin farklı olmasını gerektiren kod
bool different(string argv)
{
    for (int i = 0 , length = strlen(argv); i < length - 1; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            if (argv[i] == argv[j])
            {
                return true;
            }
        }
    }
    return false;
}