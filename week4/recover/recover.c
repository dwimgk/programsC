#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }
    FILE *card = fopen(argv[1], "r");
    if (card == NULL || card == 0)
    {
        printf("Could not open card.raw.\n");
        return 1;
    }

    uint8_t buffer[BUFFER_SIZE];
    int file_count = 0;

    char *filename = malloc(8 * sizeof(char));
    FILE *output = NULL;

    while (fread(buffer, 1, BUFFER_SIZE, card) == BUFFER_SIZE)
    {
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF)
        {

            if ((buffer[3] & 0xf0) == 0xe0)
            {
                // 0xe1 (1110 0001)
                // 0xf0 (1111 0000)
                //--------------
                // 0xe0 (1110 0000)

                // 0x - hexadecimal value
                //
                // EXAMPLE - using &(bitwise and) we compare each bit of the first value (e1),
                // with each corresponding bit of the second value(f0)
                // like in basics of computer technologies and communications
                // AND works, where the output is 1 only when both values are 1s
                // so when e1 and f0 are compared and the result is e0

                if (file_count != 0)
                {
                    fclose(output);
                }
                    sprintf(filename, "%03i.jpg", file_count);
                    output = fopen(filename, "w");
                    fwrite(buffer, 1, BUFFER_SIZE, output);

                    file_count++;
            }
        }
        else if (file_count > 0)
        {
            fwrite(buffer, 1, BUFFER_SIZE, output);
        }
    }
    free(filename);
    fclose(card);
    fclose(output);
}
