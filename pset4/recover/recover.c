/**
 * Recover jpeg files from a memory card
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // check for proper usage
    if (argc != 2)
    {
        fprintf(stderr, "usage: ./recover file\n");
        return 1;
    }  
    
    // open card file and create file ptr for jpegs
    FILE* card = fopen(argv[1], "r");
    FILE* img = NULL;
    
    // creating buffer and char to store jpeg names
    BYTE buffer[512];
    char jpg[8];
    
    // count file name
    int filenum = 0;
    
    // loop through the source until the buffer is less than 512
    while (fread(buffer, sizeof(buffer), 1, card) == 1)
    {
        // check if first 4 bytes = jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            
            // close a file if there is one already open
            if (filenum > 0)
                fclose(img);
                
            // create new file, open it and increase the filenumber counter
            sprintf(jpg, "%03d.jpg", filenum);
            img = fopen(jpg, "w");
            filenum++;
            
            // error checking (in case img could not be created)
            if (img == NULL)
            {
                fprintf(stderr, "Error! Could not create the file!\n");
                return 1;
            }
        }
        
        // write blocks to file until new jpeg is found (only start after a jpeg has been found)
        if (img != NULL)
            fwrite(buffer, sizeof(buffer), 1, img);
    }
    
    // close remaining files
    fclose(img);
    fclose(card);
    return 0;
}