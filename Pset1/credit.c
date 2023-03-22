#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    long number=get_long("Number: ");
// Basamak sayısını bulan kod
    int basamak=-1;
    long bolen=1,bolum=5;
    do
    {
        bolum=number/bolen;
        bolen*=10;
        basamak++;
    }
    while(bolum!=0);
    int digit[basamak+2];
    digit[basamak+1]=0;


// Her bir rakamı bir diziye toplayan kod
    for(long i=10,j=1; i<=pow(10,basamak); i*=10)
    {
        digit[j]=(number%i)/(i/10);
        number=number-(digit[j]*(i/10));
        j++;
    }
    printf("\n");


// Luhn's sum degeri
    int sum=digit[1];
    for(int i=2; i<=basamak; i+=2)
    {
        if(digit[i]>4)
        {
            sum=(digit[i]*2)%10+1+sum;
        }
        else
        {
            sum=digit[i]*2+sum;
        }
        sum=digit[i+1]+sum;
    }

//Sınıflandırma
    int ilk= digit[basamak]*10 + digit[basamak-1];
    if(sum%10==0)
    {
        if(basamak==13)
        {
            if(digit[13]==4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if(basamak==15)
        {
            if(ilk==34||ilk==37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if(basamak==16)
        {
            if(digit[16]==4)
            {
                printf("VISA\n");
            }
            else if(ilk==51||ilk==52||ilk==53||ilk==54||ilk==55)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}