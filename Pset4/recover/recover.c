#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (!(argc == 2))
    {
        printf("usage: ./rocover card.raw");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    {
        printf("Can't opened the raw file");
        return 1;
    }

    uint8_t buffer[512];

    int i = -1;
    FILE *img = NULL;

    while (fread(buffer, sizeof(uint8_t), 512, card) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            if ((buffer[3] & 0xf0) == 0xe0)
            {
                if (i >= 0)
                {
                    fclose(img);
                }

                char filename[8];
                i++;

                sprintf(filename, "%03i.jpg", i);
                img = fopen(filename, "a");
            }
        }

        if (!(img == NULL))
        {
            fwrite(buffer, 1, 512, img);
        }
    }

    if (!(img == NULL))
    {
        fclose(img);
    }

    fclose(card);
}