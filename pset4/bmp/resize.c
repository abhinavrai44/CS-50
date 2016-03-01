/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Enlarge a BMP, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    int l,k;
    
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    float n = atof(argv[1]);
    printf("%f",n);
    
     // temporary storage
     RGBTRIPLE triple;
 
    // n must be between 1 and 100
    if(n<0 || n>100)
        {
        exit(0);
        }
    
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf,o_bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    o_bf=bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, o_bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    o_bi=bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // find the new dimensions
    o_bi.biWidth = bi.biWidth * n;
    o_bi.biHeight = bi.biHeight * n;
    
    // determine the paddings
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) %4) % 4;
    int o_padding = (4 - (o_bi.biWidth * sizeof(RGBTRIPLE)) %4) % 4;
    
    o_bf.bfSize = 54 + o_bi.biWidth * abs(o_bi.biHeight) * 3 + abs(o_bi.biHeight) * o_padding;
    o_bi.biSizeImage = ((((o_bi.biWidth * o_bi.biBitCount) + 31) & ~31) / 8) * abs(o_bi.biHeight);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&o_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&o_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    if(n>=1)
    {
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (k = 0; k < n; k++)
            {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
                {
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
                // write RGB triple to outfile
                for (l = 0; l < n; l++)
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
        // add a new padding
        for (l = 0; l < o_padding; l++)
            fputc(0x00, outptr);
        
        // return to the beginning of a scanline
        if (k < n - 1)
            fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
            }
        
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }
    }
    
    else if (n>0 && n<1)
    {
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
       
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
                {
                // read RGB triple from infile
                for(k=0;k<(1/n);k++)
                    {
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                    j++;
                    }
                    
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
        
        fseek(inptr, padding, SEEK_CUR);
        // add a new padding
        for (l = 0; l < o_padding; l++)
            fputc(0x00, outptr);
        
        for(k=0;k<((1/n)-1);k++)
            {
            for (int j = 0; j < bi.biWidth; j++)
                {
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                }
            fseek(inptr, padding, SEEK_CUR);
            i++;
            }
           
    }
    }
    
    else
    {
    printf("Error :-(..........\n");
    }
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
