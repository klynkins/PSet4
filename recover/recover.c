#include <cs50.h>
#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
     if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    char *file = argv[1];
    // open card.raw and read it
    FILE *card = fopen(file, "r");
    if (card == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", file);
        return 2;
    }

    // read in 512 bytes from card.raw
    int file_counter = 0;
    unsigned char buffer[512];
    char filename[8];
    FILE* new_jpg =fopen(filename, "w");

    while (fread(buffer, 512, 1, card))
    {
        // header patterns of bytes
        if (buffer[0] == 0xff &&
        buffer[1] == 0xd8 &&
        buffer[2] == 0xff &&
        (buffer[3] & 0xf0) == 0xe0)
        {
            if (new_jpg != NULL)
            {
                fclose(new_jpg);
            }

            sprintf(filename, "%03i.jpg", file_counter++);

                new_jpg = fopen(filename, "w");
                // write from buffer into new_jpg_ptr
                fwrite(buffer, sizeof(char), 512 , new_jpg);

        }
        else
        {
                fwrite(buffer, sizeof(char), 512 , new_jpg);
        }
    }

    // close all files and free memory
    fclose(new_jpg);
    fclose(card);
}