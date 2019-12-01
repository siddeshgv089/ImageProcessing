#include <iostream>
#include<stdio.h>

using namespace std;

int main()
{


    FILE *fin = fopen("fruits.bmp","rb");
    FILE *fout = fopen("fruits_sephia.bmp","wb");


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

    float r,g,b;

    for(int i = 0; i < imgSize; i++)
    {

        inBuffer[i][2] = getc(fin); //R
        inBuffer[i][1] = getc(fin);// G
        inBuffer[i][0] = getc(fin); // B


        r = (inBuffer[i][0] * 0.393 + inBuffer[i][1] * 0.769 + inBuffer[i][2] * 0.189);
        g = (inBuffer[i][0] * 0.349 + inBuffer[i][1] * 0.686 + inBuffer[i][2] * 0.168);
        b = (inBuffer[i][0] * 0.272 + inBuffer[i][1] * 0.534 + inBuffer[i][2] * 0.131);

        putc(b,fout);
        putc(g,fout);
        putc(r,fout);

    }


    fclose(fin);
    fclose(fout);

    return 0;

}
