#include <iostream>
#include<stdio.h>
using namespace std;

int main()
{


   FILE *fin = fopen("lena512.bmp","rb");
   FILE *fout = fopen("lena512_Rotate.bmp","wb");

   if(fin == NULL)
   {

       printf("Unable to open the file\n");
       return -1;
   }

   unsigned char header[54];
   unsigned char colorTable[1024];

   fread(header,sizeof(unsigned char),54,fin);

   int width = (*(int*)&header[18]);
   int height = (*(int *)&header[22]);
   int bitDepth = (*(int *)&header[28]);

    int option;

   if(bitDepth <= 8)
   {
       fread(colorTable,sizeof(unsigned char),1024,fin);

   }



   unsigned char inBuffer[width][height];
   unsigned char outBuffer[width][height];

    printf("Enter the following options:\n");
    printf("press 1 to rotate image right\n");
    printf("press 2 to rotate image left\n");
    printf("press 3 to rotate image by 180 degree\n");

    fread(inBuffer,sizeof(unsigned char),width*height,fin);

    scanf("%d",&option);

    switch(option)
    {
    case 1:
        {
            for(int i = 0; i < width; i++)
            {
                for(int j =0; j < height; j++)
                {
                    outBuffer[j][height-1-i] = inBuffer[i][j];
                }
            }

            break;
        }
    case 2:
        {
            for(int i = 0; i < width; i++)
            {
                for(int j = 0; j < height; j++)
                {
                    outBuffer[j][i] = inBuffer[i][j];
                }
            }

            break;
        }

    case 3:
        {
            for(int i = 0; i < width; i++)
            {
                for(int j = 0; j < height; j++)
                {
                    outBuffer[width-i][j] = inBuffer[i][j];
                }
            }

            break;

        }

    default:
        {
            printf("Invalid option Entry\n");
            break;
        }
    }

        int s = width * height;

    fwrite(header,sizeof(unsigned char),54,fout);
    fwrite(colorTable,sizeof(unsigned char),1024,fout);
    fwrite(outBuffer,sizeof(unsigned char),s,fout);

    fclose(fout);
    fclose(fin);


    return 0;
}
