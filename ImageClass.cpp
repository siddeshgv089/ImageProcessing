#include <iostream>
#include "ImageProcessing.h"
using namespace std;

int main()
{

    int width,height,bitDepth;
    unsigned char imgHeader[HEADER];
    unsigned char colorTable[COLORTABLE];
    unsigned char inBuffer[BUFFERSIZE];
    unsigned char outBuffer[BUFFERSIZE];

    float hist[GREYSCALE];

    const char * inImage = "C:\\Users\\SIDDESH\\Desktop\\ImageProcessing\\ImageCopy\\ImageProcessing\\cameraman.bmp";
    const char * outImage = "C:\\Users\\SIDDESH\\Desktop\\ImageProcessing\\ImageCopy\\ImageProcessing\\cameraman_line.bmp";


    ImageProcessing *image = new ImageProcessing(inImage,outImage,&width,&height,&bitDepth,imgHeader,colorTable,inBuffer,outBuffer);
    image->readImage();
    //image->histogram(inBuffer,height,width,hist);
    //image->equalizeHistogram(inBuffer,outBuffer,height,width);
    //image->negativeImage(inBuffer,outBuffer,height,width);

    image->detectLine(inBuffer,outBuffer,height,width,LINE_DETECTOR_LDIA_MASK);

    image->writeImage();

    printf("width : %d\n",width);
    printf("height : %d\n",height);
    printf("bitDepth : %d\n",bitDepth);

    //image->copyImageBuffer(inBuffer,outBuffer,BUFFERSIZE);

    //image->brightnessUp(inBuffer,outBuffer,BUFFERSIZE,-10);

    //image->brightnessDown(inBuffer,outBuffer,BUFFERSIZE,100);

    //image->writeImage();

    std::cout << "Success" <<std::endl;



    return 0;
}
