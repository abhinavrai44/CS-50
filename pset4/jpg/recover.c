#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
 
int main(int argc, char* argv[])
{
    // TODO
    // Open card.raw file
    FILE* file = fopen("card.raw", "r");
    if( file == NULL)
        {
        printf("Could not open file. \n ");
        return 0;
        }
    // define buffer
    FILE* img;
    uint8_t buffer[512];
    int c=0;
    int imgcount = 0;
    char title[8];
    fread(&buffer, 512, 1, file);
    // repeat until the end of file
    while(fread(&buffer, 512, 1, file) > 0)
        {
        // if it is the start of a jpg
        if(buffer[0] == 0xff  && buffer[1] == 0xd8  && buffer[2] == 0xff && (buffer[3]== 0xe1 || buffer[3]== 0xe0))
            {
            sprintf(title, "%03d.jpg", imgcount);
            if(c==0)
                {
                img = fopen(title, "w");
                c=1;
                }
            if(c==1)
                {
                fclose(img);
                img = fopen(title, "w");
                fwrite(&buffer, 512, 1, img);
                imgcount++;
                }
            }
        else
            {
            if(c==1)
                {
                fwrite(&buffer, 512, 1, img);
                }
            }
    }
    // close infile
    if(img)
        fclose(img);
    fclose(file);
    return 0;
}
