#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    // n sıfır ve dokuz arasında olmalı
    do
    {
        n = get_int("Yükseklik: ");
    }
    while (n < 1 || n > 8);


    //Piramiti yazdıran kısım
    for (int i = 0; i < n; i++)
    {
        for (int j = n - i - 1; j > 0; j--)
        {
            printf(" ");
        }
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
