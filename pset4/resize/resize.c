/**
 * Resizes a BMP using the rewrite method
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize # infile outfile\n");
        return 1;
    }
    // remember scale factor
    int scale = atoi(argv[1]);
    
    // ensure resize factor is correct
    if (scale < 0 || scale > 100)
    {
        fprintf(stderr, "Please enter a number 0 < x < 100");
        return 1;
    }
    
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // separate old and new header
    int oldheight = bi.biHeight;
    int oldwidth = bi.biWidth;
    // change size of height and width
    bi.biHeight *= scale;
    bi.biWidth *= scale;

     // determine padding for scanlines
    int oldpad = (4 - (oldwidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
   
    // change outfile's HEADERS
    bi.biSizeImage = (sizeof(RGBTRIPLE) * bi.biWidth + padding) * abs(bi.biHeight);
    bf.bfSize = (bi.biSizeImage) + (sizeof(BITMAPFILEHEADER) +sizeof(BITMAPINFOHEADER));
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // buffer array for resizing vertically
    RGBTRIPLE* buffer = malloc(bi.biWidth*sizeof(RGBTRIPLE));
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(oldheight); i < biHeight; i++)
    {
        int track = 0;
        
        // iterate over pixels in scanline
        for (int j = 0; j < oldwidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // resize horizontally and save pixels to array
            for (int l = 0; l < scale; l++)
            {
            *(buffer + track) = triple;
            track++;
            }
        }
        
        //write array to outfile to resize vertically
        for (int m = 0; m < scale; m++)
        {
            // write the actual arary
            fwrite(buffer, sizeof(RGBTRIPLE), bi.biWidth, outptr);
                
            //padding for each row
            for (int k = 0; k < padding; k++)
                fputc(0x00, outptr);
        }
        
        
        // skip over padding, if any
        fseek(inptr, oldpad, SEEK_CUR);
    }
    
    // release memory
    free(buffer);
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
