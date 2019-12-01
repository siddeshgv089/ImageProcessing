
#include<stdio.h>
#define HEADER 54
#define COLORTABLE 1024
#define BUFFER_SIZE 256*256

void imageReader(const char *name, int *height, int* width,int *bitDepth, unsigned char *header, unsigned char *colorTable, unsigned char *buffer);
void imageWriter(const char *name, unsigned char *header, unsigned char *colorTable, unsigned char* buffer, int *bitDepth);

int main()
{

    int width,height,bitDepth;
    unsigned char imgHeader[HEADER];
    unsigned char colorTable[COLORTABLE];
    unsigned char buffer[BUFFER_SIZE];

    const char * inImage = "cameraman.bmp";
    const char * outImage = "cameraman_out.bmp";

    imageReader(inImage,&height,&width,&bitDepth,imgHeader,colorTable,buffer);
    imageWriter(outImage,imgHeader,colorTable,buffer,&bitDepth);

    printf("Image copying Success\n");

    return 0;
}


void imageWriter(const char *name, unsigned char *header, unsigned char *colorTable, unsigned char* buffer, int *bitDepth)
{

    FILE *fout = fopen(name,"wb");

    if(fout == NULL)
    {

        printf("Unable to open the file :\n");
        return;
    }

    fwrite(header,sizeof(unsigned char),HEADER,fout);

    if(*bitDepth <= 8)
    {

        fwrite(colorTable,sizeof(unsigned char),COLORTABLE, fout);
    }

    fwrite(buffer,sizeof(unsigned char),BUFFER_SIZE,fout);

    fclose(fout);
}

void imageReader(const char *name, int *height, int* width,int *bitDepth, unsigned char *header, unsigned char *colorTable, unsigned char *buffer)
{
    FILE *fin = fopen(name,"rb");

    if(fin == NULL)
    {
        printf("Unable to open the file\n");
        return;
    }

    fread(header,sizeof(unsigned char),HEADER,fin);

    *width = (*(int *)&header[18]);
    *height = (*(int *)&header[22]);
    *bitDepth = (*(int *)&header[28]);

    if(*bitDepth <= 8)
    {

        fread(colorTable,sizeof(unsigned char),COLORTABLE,fin);
    }

    fread(buffer,sizeof(unsigned char),BUFFER_SIZE,fin);

    fclose(fin);

}
