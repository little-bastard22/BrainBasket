#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char *argv[])
{

    //checks number of args
    if (argc != 2)
    {
        printf("Usage: recover filename\n");
        return 1;
    }
    
    int file_num = 0; //first file number
    char *infile = argv[1]; //file name for reading
    char outfile[6]; //file name for writing
    unsigned char block[512]; //
     
    //opens RAW file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    
    //prepares NULL pointer for writing
    FILE *outptr = NULL;
    
    //reads raw data in 512 BYTE-sized blocks
    while (fread(&block, 1, 512, inptr) == 512)
    {
        unsigned char block0 = block[0];
        unsigned char block1 = block[1];
        unsigned char block2 = block[2];
        unsigned char block3 = block[3];
        
        //checks for JPEG file header
        if ((block0 != 0xff) || (block1 != 0xd8) || (block2 != 0xff) || (block3 > 0xef && block3 < 0xe0))
        {
            //writes if outfile ready for writing
            if (outptr != NULL)
            {
                fwrite(block, 1, 512, outptr);
            }
            //skips for first file
            else
            {
                continue;
            }
        }
        
        // for JPEG header block
        else
        {
            //closes outfile if pointer assigned
            if (outptr != NULL)
            {
                fclose(outptr);
            }
            
            // prepares new file for writing
            sprintf(outfile, "%03d.jpg", file_num);
            outptr = fopen(outfile, "w");
            if (outptr == NULL)
            {
                fclose(inptr);
                fclose(outptr);
                return 3;
            }
            
            //writes the current block of code
            fwrite(block, 1, 512, outptr);

            //increment for next file
            file_num++;
        }
    }

    // close infile
    fclose(inptr);
    
    //closes outfile if needed
    if (outptr != NULL)
    {
        fclose(outptr);
    }


    // success
    return 0;
    
}