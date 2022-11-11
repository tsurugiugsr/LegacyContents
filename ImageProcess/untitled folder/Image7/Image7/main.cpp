//
//  main.cpp
//  Image7
//
//  Created by 松岡東矢 on 2022/05/09.
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
    
    unsigned char *pic, *op1, *op2, *picgaussed, *op3, grey, z1, z2, z3, z4, z5, z6, z7, z8, z9;
    int gx, gy;
    
    FILE *ibmp =fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image7/Image7/input.bmp","rb");
    FILE *obmp1=fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image7/Image7/output1.bmp","wb");
    FILE *obmp2=fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image7/Image7/output2.bmp","wb");
    FILE *obmp3=fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image7/Image7/output3.bmp","wb");
    
    BITMAPFILEHEADER *bmpHead=(BITMAPFILEHEADER*)malloc(sizeof(BITMAPFILEHEADER));
    BITMAPINFOHEADER *bmpInfo=(BITMAPINFOHEADER*)malloc(sizeof(BITMAPINFOHEADER));
    RGBQUAD * palette=(RGBQUAD*)malloc(256*sizeof(RGBQUAD));
    
    fread(bmpHead, sizeof(BITMAPFILEHEADER), 1,ibmp);
    fread(bmpInfo,sizeof(BITMAPINFOHEADER), 1, ibmp);
    fread(palette,sizeof(RGBQUAD),256,ibmp);
    
    fwrite(bmpHead, sizeof(BITMAPFILEHEADER), 1,   obmp1);
    fwrite(bmpInfo, sizeof(BITMAPINFOHEADER), 1,   obmp1);
    fwrite(palette     , sizeof(RGBQUAD)         , 256, obmp1);
    fwrite(bmpHead, sizeof(BITMAPFILEHEADER), 1,   obmp2);
    fwrite(bmpInfo, sizeof(BITMAPINFOHEADER), 1,   obmp2);
    fwrite(palette     , sizeof(RGBQUAD)         , 256, obmp2);
    fwrite(bmpHead, sizeof(BITMAPFILEHEADER), 1,   obmp3);
    fwrite(bmpInfo, sizeof(BITMAPINFOHEADER), 1,   obmp3);
    fwrite(palette     , sizeof(RGBQUAD)         , 256, obmp3);
    
    pic = (unsigned char*)malloc(bmpInfo->biSizeImage);
    op1 = (unsigned char*)malloc(bmpInfo->biSizeImage);
    op2 = (unsigned char*)malloc(bmpInfo->biSizeImage);
    picgaussed = (unsigned char*)malloc(bmpInfo->biSizeImage);
    op3 = (unsigned char*)malloc(bmpInfo->biSizeImage);
    
    for (int i = 0; i < bmpInfo->biHeight; i++)
    {
        for (int j = 0; j < (bmpInfo->biWidth + 3) / 4 * 4; j++)
        {
            fread(&grey, 1, 1, ibmp);
            pic[i*bmpInfo->biWidth+j] = grey;
            op1[i*bmpInfo->biWidth+j] = 0;
            op2[i*bmpInfo->biWidth+j] = 0;
            picgaussed[i*bmpInfo->biWidth+j] = 0;
            op3[i*bmpInfo->biWidth+j] = 0;
        }
    }
    
    for (int j = 1; j < bmpInfo->biHeight - 1; j++) {
        for (int i = 1; i < bmpInfo->biWidth - 1; i++) {
            z1 = pic[(j - 1) * bmpInfo->biWidth + (i - 1)];
            z2 = pic[(j - 1) * bmpInfo->biWidth + (i)];
            z3 = pic[(j - 1) * bmpInfo->biWidth + (i + 1)];
            z4 = pic[j * bmpInfo->biWidth + (i - 1)];
            z5 = pic[j * bmpInfo->biWidth + (i)];
            z6 = pic[j * bmpInfo->biWidth + (i + 1)];
            z7 = pic[(j + 1) * bmpInfo->biWidth + (i - 1)];
            z8 = pic[(j + 1) * bmpInfo->biWidth + (i)];
            z9 = pic[(j + 1) * bmpInfo->biWidth + (i + 1)];
            
            gx = z7 + z8 + z9 - z1 - z2 - z3;
            gy = z3 + z6 + z9 - z1 - z4 - z7;
            if (abs(gx) > 100 || abs(gy) > 100) {
                op1[j * bmpInfo->biWidth + (i)] = 255;
            }
        }
    }
    
    for (int j = 1; j < bmpInfo->biHeight - 1; j++) {
        for (int i = 1; i < bmpInfo->biWidth - 1; i++) {
            z1 = pic[(j - 1) * bmpInfo->biWidth + (i - 1)];
            z2 = pic[(j - 1) * bmpInfo->biWidth + (i)];
            z3 = pic[(j - 1) * bmpInfo->biWidth + (i + 1)];
            z4 = pic[j * bmpInfo->biWidth + (i - 1)];
            z5 = pic[j * bmpInfo->biWidth + (i)];
            z6 = pic[j * bmpInfo->biWidth + (i + 1)];
            z7 = pic[(j + 1) * bmpInfo->biWidth + (i - 1)];
            z8 = pic[(j + 1) * bmpInfo->biWidth + (i)];
            z9 = pic[(j + 1) * bmpInfo->biWidth + (i + 1)];
            
            gx = z7 + 2 * z8 + z9 - z1 - 2 * z2 - z3;
            gy = z3 + 2 * z6 + z9 - z1 - 2 * z4 - z7;
            if (abs(gx) > 100 || abs(gy) > 100) {
                op2[j * bmpInfo->biWidth + (i)] = 255;
            }
        }
    }
    
    int size = 3;
    double sqrSigma = 0.1;
    double** gaus = new double*[size];
    for (int i = 0; i < size; i++)
    {
        gaus[i] = new double[size];
    }
    const double pi = 4.0 * atan(1.0);
    const int center = size / 2;
    double sum = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            gaus[i][j] = (1 / (2 * pi*sqrSigma))*exp(-((1 - center)*(1 - center) + (j - center)*(j - center)) / (2 * sqrSigma));
            sum += gaus[i][j];
        }
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            gaus[i][j] /= sum;
        }
    }
    for (int i = 1; i < bmpInfo->biHeight - 1; i++)
    {
        for (int j = 1; j < bmpInfo->biWidth - 1; j++)
        {
            int sum = 0;
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    sum += pic[i + x + (j + y)*bmpInfo->biWidth] * gaus[2 - (x + 1)][y + 1];
                }
                
            }
            picgaussed[i * bmpInfo->biWidth + j] = sum;
        }
    }
    for (int j = 1; j < bmpInfo->biHeight - 1; j++) {
        for (int i = 1; i < bmpInfo->biWidth - 1; i++) {
            z1 = picgaussed[(j - 1) * bmpInfo->biWidth + (i - 1)];
            z2 = picgaussed[(j - 1) * bmpInfo->biWidth + (i)];
            z3 = picgaussed[(j - 1) * bmpInfo->biWidth + (i + 1)];
            z4 = picgaussed[j * bmpInfo->biWidth + (i - 1)];
            z5 = picgaussed[j * bmpInfo->biWidth + (i)];
            z6 = picgaussed[j * bmpInfo->biWidth + (i + 1)];
            z7 = picgaussed[(j + 1) * bmpInfo->biWidth + (i - 1)];
            z8 = picgaussed[(j + 1) * bmpInfo->biWidth + (i)];
            z9 = picgaussed[(j + 1) * bmpInfo->biWidth + (i + 1)];
            
            gx = z1 + z2 + z3 + z4 - 8 * z5 + z6 + z7 + z8 + z9;
            if (abs(gx) > 100) {
                op3[i * bmpInfo->biWidth + (j)] = 255;
            }
        }
    }
    
    fwrite(op1, sizeof(unsigned char), bmpInfo->biSizeImage, obmp1);
    fwrite(op2, sizeof(unsigned char), bmpInfo->biSizeImage, obmp2);
    fwrite(op3, sizeof(unsigned char), bmpInfo->biSizeImage, obmp3);
    
    fclose(ibmp);
    fclose(obmp1);
    fclose(obmp2);
    fclose(obmp3);
    
    return 0;
}
