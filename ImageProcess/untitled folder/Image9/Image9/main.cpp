//
//  main.cpp
//  Image9
//
//  Created by 松岡東矢 on 2022/05/10.
//

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef uint8_t  CHAR;
typedef uint16_t WORD;
typedef uint32_t DWORD;

typedef int8_t  BYTE;
typedef int16_t SHORT;
typedef int32_t LONG;

typedef LONG INT;
typedef INT BOOL;

using namespace std;

#pragma pack(push,1)

typedef struct tagBITMAPFILEHEADER { // bmfh
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER{
    DWORD   biSize; //该结构的长度，为40
    LONG        biWidth; //图像宽度
    LONG        biHeight; //图像高度
    WORD        biPlanes; //位平面数，必须为1
    WORD        biBitCount; //颜色位数，
    DWORD   biCompression; //是否压缩
    DWORD   biSizeImage; //实际位图数据占用的字节数
    LONG        biXPelsPerMeter;//目标设备水平分辨率
    LONG        biYPelsPerMeter;//目标设备垂直分辨率
    DWORD   biClrUsed;//实际使用的颜色数
    DWORD   biClrImportant;//图像中重要的颜色数
} BITMAPINFOHEADER;

typedef struct tagRGBQUAD
{
    unsigned char rgbBlue;   //该颜色的蓝色分量  (值范围为0-255)
    unsigned char rgbGreen;  //该颜色的绿色分量  (值范围为0-255)
    unsigned char rgbRed;    //该颜色的红色分量  (值范围为0-255)
    unsigned char rgbReserved;// 保留，必须为0
}RGBQUAD;

#pragma pack(pop)

int main(int argc, const char * argv[]) {
    
    unsigned char *pic, *op1, grey;
    int curr = 1, mintag = 10000, lap;
    
    FILE *ibmp =fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image9/Image9/input.bmp","rb");
    FILE *obmp1=fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image9/Image9/output1.bmp","wb");
    
    BITMAPFILEHEADER *bmpHead=(BITMAPFILEHEADER*)malloc(sizeof(BITMAPFILEHEADER));
    BITMAPINFOHEADER *bmpInfo=(BITMAPINFOHEADER*)malloc(sizeof(BITMAPINFOHEADER));
    RGBQUAD * palette=(RGBQUAD*)malloc(256*sizeof(RGBQUAD));
    
    fread(bmpHead, sizeof(BITMAPFILEHEADER), 1,ibmp);
    fread(bmpInfo,sizeof(BITMAPINFOHEADER), 1, ibmp);
    fread(palette,sizeof(RGBQUAD),256,ibmp);
    
    fwrite(bmpHead, sizeof(BITMAPFILEHEADER), 1,   obmp1);
    fwrite(bmpInfo, sizeof(BITMAPINFOHEADER), 1,   obmp1);
    fwrite(palette     , sizeof(RGBQUAD)         , 256, obmp1);
    
    pic = (unsigned char*)malloc(bmpInfo->biSizeImage);
    op1 = (unsigned char*)malloc(bmpInfo->biSizeImage);
    for (int i = 0; i < bmpInfo->biHeight; i++)
    {
        for (int j = 0; j < (bmpInfo->biWidth + 3) / 4 * 4; j++)
        {
            fread(&grey, 1, 1, ibmp);
            pic[i*bmpInfo->biWidth+j] = grey;
            op1[i*bmpInfo->biWidth+j] = '0';
        }
    }
    
    for (int i = 1; i < bmpInfo->biHeight-1; i++) {
        for (int j = 1; j < bmpInfo->biWidth-1; j++) {
            if (pic[i * bmpInfo->biWidth + j] < 127) {
                if (op1[(i) * bmpInfo->biWidth + j - 1] == '0' && op1[(i - 1) * bmpInfo->biWidth + j - 1] == '0' && op1[(i - 1) * bmpInfo->biWidth + j] == '0' && op1[(i - 1) * bmpInfo->biWidth + j + 1] == '0') {
                    op1[i * bmpInfo->biWidth + j] = curr;
                    curr++;
                }
                else {
                    mintag = 10000000;
                    if (op1[(i) * bmpInfo->biWidth + j - 1] != '0' && op1[(i) * bmpInfo->biWidth + j - 1] < mintag) {
                        mintag = op1[(i) * bmpInfo->biWidth + j - 1];
                    }
                    if (op1[(i - 1) * bmpInfo->biWidth + j - 1] != '0' && op1[(i - 1) * bmpInfo->biWidth + j - 1] < mintag) {
                        mintag = op1[(i - 1) * bmpInfo->biWidth + j - 1];
                    }
                    if (op1[(i - 1) * bmpInfo->biWidth + j] != '0' && op1[(i - 1) * bmpInfo->biWidth + j] < mintag) {
                        mintag = op1[(i - 1) * bmpInfo->biWidth + j];
                    }
                    if (op1[(i - 1) * bmpInfo->biWidth + j + 1] != '0' && op1[(i - 1) * bmpInfo->biWidth + j + 1] < mintag) {
                        mintag = op1[(i - 1) * bmpInfo->biWidth + j + 1];
                    }
                    op1[i * bmpInfo->biWidth + j] = mintag;
                    if (op1[(i) * bmpInfo->biWidth + j - 1] != '0') {
                        op1[(i) * bmpInfo->biWidth + j - 1] = mintag;
                    }
                    if (op1[(i - 1) * bmpInfo->biWidth + j - 1] != '0') {
                        op1[(i - 1) * bmpInfo->biWidth + j - 1] = mintag;
                    }
                    if (op1[(i - 1) * bmpInfo->biWidth + j] != '0') {
                        op1[(i - 1) * bmpInfo->biWidth + j] = mintag;
                    }
                    if (op1[(i - 1) * bmpInfo->biWidth + j + 1] != '0') {
                        op1[(i - 1) * bmpInfo->biWidth + j + 1] = mintag;
                    }
                }
            }
        }
    }
    lap = 255 / (curr - 1);
    for (int i = 0; i < bmpInfo->biHeight; i++) {
        for (int j = 0; j < bmpInfo->biWidth; j++) {
            if (op1[i * bmpInfo->biWidth + j] != '0') {
                op1[i * bmpInfo->biWidth + j] = op1[i * bmpInfo->biWidth + j] * lap;
            }
            else
                op1[i * bmpInfo->biWidth + j] = 255;
        }
    }
    
    fwrite(op1, sizeof(unsigned char), bmpInfo->biSizeImage, obmp1);
    
    fclose(ibmp);
    fclose(obmp1);
    
    return 0;
}
