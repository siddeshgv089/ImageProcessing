#include <iostream>
#include<stdio.h>

using namespace std;

int main()
{


    FILE *fin = fopen("fruits.bmp","rb");
    FILE *fout = fopen("fruits_blur.bmp","wb");


    if(fin == NULL || fout == NULL)
    {
        printf("Unable to open the file\n");
        return -1;
    }

    unsigned char header[54];
    unsigned char colorTable[1024];

    fread(header,sizeof(unsigned char),54,fin);
    fread(colorTable,sizeof(unsigned char),1024,fin);

    int width = (*(int*)&header[18]);
    int height = (*(int*)&header[22]);
    int bitDepth = (*(int*)&header[28]);

    printf("width = %d\n",width);
    printf("height = %d\n",height);
    printf("bitDepth = %d\n",bitDepth);

    int imgSize = width*height;

    fwrite(header,sizeof(unsigned char),54,fout);

    //if(bitDepth <= 8)
        fwrite(colorTable,sizeof(unsigned char),1024,fout);

    unsigned char inBuffer[imgSize][3];
    unsigned char outBuffer[imgSize][3];


    for(int i = 0; i < imgSize; i++)
    {

        inBuffer[i][2] = getc(fin); //R
        inBuffer[i][1] = getc(fin);// G
        inBuffer[i][0] = getc(fin); // B
    }

    float kernel[3][3]  = {{1.0/9.0,1.0/9.0,1.0/9.0},
                            {1.0/9.0,1.0/9.0,1.0/9.0},
                            {1.0/9.0,1.0/9.0,1.0/9.0}};


     for(int x = 0; x < height -1; x++)
     {
         for(int y = 0; y < width - 1; y++)
         {
             float sum0 = 0.0, sum1 = 0.0, sum2 =0.0;

             for(int i = -1; i <= 1; i++)
             {
                 for(int j = -1; j <= 1; j++)
                 {
                     sum0 = sum0 + kernel[i+1][j+1] * inBuffer[(x+i)*width+(y+j)][0]; //B
                     sum1 = sum1 + kernel[i+1][j+1] * inBuffer[(x+i)*width+(y+j)][1]; //G
                     sum2 = sum2 + kernel[i+1][j+1] * inBuffer[(x+i)*width+(y+j)][2]; //R
                 }

                 outBuffer[x*width+y][0] = sum0;
                 outBuffer[x*width+y][1] = sum1;
                 outBuffer[x*width+y][2] = sum2;

             }
         }
     }


     for(int i = 0; i < imgSize; i++)
     {
         putc(outBuffer[i][2],fout);
         putc(outBuffer[i][1],fout);
         putc(outBuffer[i][0],fout);
     }

    fclose(fin);
    fclose(fout);

    return 0;
}
