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


    //İlk piramiti yazdıran kısım
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
        //Boşluklar
        printf("  ");
        //İkinci piramit
        for (int l=0; l<i+1; l++)
        {
            printf("#");
        }
        //Satır sonu
        printf("\n");
    }
}
