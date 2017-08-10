/**
 * Resizes BMP.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"


int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./copy infile outfile\n");
        return 10;
    }

    // remember filenames 
    int factor = atof(argv[1]);
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
    
    //ensure factor is between 0 and 100
    
    if (factor < 0 || factor > 100)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Resize factor must be between 0 and 100.\n");
        return 5;
    }
    
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    
    //initialize headers of the output file
    BITMAPFILEHEADER new_bf = bf;
    BITMAPINFOHEADER new_bi = bi;

    //prepare new header
    new_bi.biWidth = bi.biWidth * factor; 
    new_bi.biHeight = bi.biHeight * factor;
    int new_padding = (4 - (new_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    new_bi.biSizeImage = ((sizeof(RGBTRIPLE) * new_bi.biWidth) + new_padding) * abs(new_bi.biHeight);
    new_bf.bfSize = new_bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    //init scanline + pointer
    int scanline_size = new_bi.biWidth * sizeof(RGBTRIPLE) + new_padding;
    RGBTRIPLE *scanline = (RGBTRIPLE *) malloc(scanline_size);
    RGBTRIPLE pixel;
    
    //BYTE - sized pointer for creating padding
    char * ch_pad = (char *) scanline;
    
    //fill in padding if needed
    for (int i = new_bi.biWidth * sizeof(RGBTRIPLE); i < scanline_size; i++)
    {
        ch_pad[i] = 0;
    }
    
    
    

    // write outfile's BITMAPFILEHEADER
    fwrite(&new_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&new_bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    //iterate on lines
    for (int i = 0; i < abs(bi.biHeight); i++)
    {
        //initialize pointer control for current line
        int ctr_ptr = 0;
        
        //iterate on pixels in row
        for (int j = 0; j < bi.biWidth; j++)
        {
            //read pixel
            fread(&pixel, sizeof(RGBTRIPLE), 1, inptr);
            
            //write pixel factor times to scanline
            for (int k = 0; k < factor; k++)
            {
                scanline[ctr_ptr] = pixel;
                ctr_ptr++;
            }
        }
        
        //write scanline factor times
        for (int l = 0; l < factor; l++)
        {
            fwrite(scanline, scanline_size, 1, outptr);
        }

        
        //skip padding for readfile
        fseek(inptr, padding, SEEK_CUR);
    }
    
    //free memory
    free(scanline);

    // close infile
    fclose(inptr);
    
    // close outfile
    fclose(outptr);

    // success
    return 0;
}
