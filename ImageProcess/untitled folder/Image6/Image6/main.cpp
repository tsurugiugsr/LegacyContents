//
//  main.cpp
//  Image6
//
//  Created by 結城朝日 on 2022/05/09.
//

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

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

unsigned char* op1, *op1seeded, *op2, *op2splited;
int w = 1, h = 1;

void split(int sX, int sY, int eX, int eY, unsigned char dy, unsigned char mid) {
    
    if (sX + 1 >= eX || sY + 1 >= eY) {
        return;
    }
    
    unsigned char dyMin = 127, dyMax = 128, dyPin = 0;
    
    for (int j = sY; j < eY; j++) {
        for (int i = sX; i < eX; i++) {
            if (op2[j*w+i] < dyMin) {
                dyMin = op2[j*w+i];
            }
            if (op2[j*w+i] > dyMax) {
                dyMax = op2[j*w+i];
            }
        }
    }
    
    if (dyMax - dyMin <= dy/50) {
        return;
    }
    
    dyPin = (dyMin + dyMax)/2;
    dyPin = mid;
    
    for (int j = sY; j <= (eY + sY)/2; j++) {//LU
        for (int i = sX; i <= (eX + sX)/2; i++) {
            if (op2[j*w+i] < dyMin) {
                dyMin = op2[j*w+i];
            }
            if (op2[j*w+i] > dyMax) {
                dyMax = op2[j*w+i];
            }
        }
    }
    if ((dyMin + dyMax)/2 < dyPin) {
        for (int j = sY; j <= (eY + sY)/2; j++) {
            for (int i = sX; i <= (eX + sX)/2; i++) {
                op2splited[j*w+i] = 0;
            }
        }
    }
    else {
        for (int j = sY; j <= (eY + sY)/2; j++) {
            for (int i = sX; i <= (eX + sX)/2; i++) {
                op2splited[j*w+i] = 255;
            }
        }
    }
        
    for (int j = sY; j <= (eY + sY)/2; j++) {//RU
        for (int i = (eX + sX)/2; i <= eX; i++) {
            if (op2[j*w+i] < dyMin) {
                dyMin = op2[j*w+i];
            }
            if (op2[j*w+i] > dyMax) {
                dyMax = op2[j*w+i];
            }
        }
    }
    if ((dyMin + dyMax)/2 < dyPin) {
        for (int j = sY; j <= (eY + sY)/2; j++) {
            for (int i = (eX + sX)/2; i <= eX; i++) {
                op2splited[j*w+i] = 0;
            }
        }
    }
    else {
        for (int j = sY; j <= (eY + sY)/2; j++) {
            for (int i = (eX + sX)/2; i <= eX; i++) {
                op2splited[j*w+i] = 255;
            }
        }
    }
    
    for (int j = (eY + sY)/2; j <= eY; j++) {//LD
        for (int i = sX; i <= (eX + sX)/2; i++) {
            if (op2[j*w+i] < dyMin) {
                dyMin = op2[j*w+i];
            }
            if (op2[j*w+i] > dyMax) {
                dyMax = op2[j*w+i];
            }
        }
    }
    if ((dyMin + dyMax)/2 < dyPin) {
        for (int j = (eY + sY)/2; j <= eY; j++) {
            for (int i = sX; i <= (eX + sX)/2; i++) {
                op2splited[j*w+i] = 0;
            }
        }
    }
    else {
        for (int j = (eY + sY)/2; j <= eY; j++) {
            for (int i = sX; i <= (eX + sX)/2; i++) {
                op2splited[j*w+i] = 255;
            }
        }
    }
    
    for (int j = (eY + sY)/2; j <= eY; j++) {//RD
        for (int i = (eX + sX)/2; i <= eX; i++) {
            if (op2[j*w+i] < dyMin) {
                dyMin = op2[j*w+i];
            }
            if (op2[j*w+i] > dyMax) {
                dyMax = op2[j*w+i];
            }
        }
    }
    if ((dyMin + dyMax)/2 < dyPin) {
        for (int j = (eY + sY)/2; j <= eY; j++) {
            for (int i = (eX + sX)/2; i <= eX; i++) {
                op2splited[j*w+i] = 0;
            }
        }
    }
    else {
        for (int j = (eY + sY)/2; j <= eY; j++) {
            for (int i = (eX + sX)/2; i <= eX; i++) {
                op2splited[j*w+i] = 255;
            }
        }
    }
    split(sX, sY, (eX+sX)/2, (eY+sY)/2, dy, mid);
    split(sX, (eY+sY)/2, (eX+sX)/2, eY, dy, mid);
    split((eX+sX)/2, sY, eX, (eY+sY)/2, dy, mid);
    split((eX+sX)/2, (eY+sY)/2, eX, eY, dy, mid);
}

int main(int argc, const char * argv[]) {
    
    unsigned char grey, dyMin = 127, dyMax = 128, th = 0, colorSelection = 0;
    int seedX = 0, seedY = 0;
    
    FILE *ibmp =fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image6/Image6/input.bmp","rb");
    FILE *obmp1=fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image6/Image6/output1.bmp","wb");
    FILE *obmp2=fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image6/Image6/output2.bmp","wb");
    
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
    
    op1 = (unsigned char*)malloc(bmpInfo->biSizeImage);
    op1seeded = (unsigned char*)malloc(bmpInfo->biSizeImage);
    op2 = (unsigned char*)malloc(bmpInfo->biSizeImage);
    op2splited = (unsigned char*)malloc(bmpInfo->biSizeImage);
    
    for (int i = 0; i < bmpInfo->biHeight; i++)
    {
        for (int j = 0; j < (bmpInfo->biWidth + 3) / 4 * 4; j++)
        {
            fread(&grey, 1, 1, ibmp);
            if (grey < dyMin)
                dyMin = grey;
            else if (grey > dyMax)
                dyMax = grey;
            op1[i*bmpInfo->biWidth+j] = grey;
            op1seeded[i*bmpInfo->biWidth+j] = '0';
            op2[i*bmpInfo->biWidth+j] = grey;
            op2splited[i*bmpInfo->biWidth+j] = '0';
        }
    }
    
    th = (dyMax - dyMin)/50;
    
    colorSelection = op1[(bmpInfo->biHeight/2)*bmpInfo->biWidth+bmpInfo->biWidth/2];
    if (colorSelection >= 128) {
        colorSelection = 255;
    } else {
        colorSelection = 0;
    }
    
    seedX = bmpInfo->biWidth/2;
    seedY = bmpInfo->biHeight/2;
    op1seeded[seedY*bmpInfo->biWidth+seedX] = colorSelection;
    
    for (int i = seedX; i < bmpInfo->biWidth-1; i++) {
        int j = seedY;
        if (abs(op1[(j-1)*bmpInfo->biWidth+(i-1)]-op1[j*bmpInfo->biWidth+i])<=th) {
            op1seeded[(j-1)*bmpInfo->biWidth+(i-1)] = colorSelection;
        }
        if (abs(op1[(j-1)*bmpInfo->biWidth+(i)]-op1[j*bmpInfo->biWidth+i])<=th) {
            op1seeded[(j-1)*bmpInfo->biWidth+(i)] = colorSelection;
        }
        if (abs(op1[(j-1)*bmpInfo->biWidth+(i+1)]-op1[j*bmpInfo->biWidth+i])<=th) {
            op1seeded[(j-1)*bmpInfo->biWidth+(i+1)] = colorSelection;
        }
        if (abs(op1[(j)*bmpInfo->biWidth+(i-1)]-op1[j*bmpInfo->biWidth+i])<=th) {
            op1seeded[(j)*bmpInfo->biWidth+(i-1)] = colorSelection;
        }
        if (abs(op1[(j)*bmpInfo->biWidth+(i+1)]-op1[j*bmpInfo->biWidth+i])<=th) {
            op1seeded[(j)*bmpInfo->biWidth+(i+1)] = colorSelection;
        }
        if (abs(op1[(j+1)*bmpInfo->biWidth+(i-1)]-op1[j*bmpInfo->biWidth+i])<=th) {
            op1seeded[(j+1)*bmpInfo->biWidth+(i-1)] = colorSelection;
        }
        if (abs(op1[(j+1)*bmpInfo->biWidth+(i)]-op1[j*bmpInfo->biWidth+i])<=th) {
            op1seeded[(j+1)*bmpInfo->biWidth+(i)] = colorSelection;
        }
        if (abs(op1[(j+1)*bmpInfo->biWidth+(i+1)]-op1[j*bmpInfo->biWidth+i])<=th) {
            op1seeded[(j+1)*bmpInfo->biWidth+(i+1)] = colorSelection;
        }
    }
    
    for (int i = seedX; i > 0; i--) {
        int j = seedY;
        if (abs(op1[(j-1)*bmpInfo->biWidth+(i-1)]-op1[j*bmpInfo->biWidth+i])<=th) {
            op1seeded[(j-1)*bmpInfo->biWidth+(i-1)] = colorSelection;
        }
        if (abs(op1[(j-1)*bmpInfo->biWidth+(i)]-op1[j*bmpInfo->biWidth+i])<=th) {
            op1seeded[(j-1)*bmpInfo->biWidth+(i)] = colorSelection;
        }
        if (abs(op1[(j-1)*bmpInfo->biWidth+(i+1)]-op1[j*bmpInfo->biWidth+i])<=th) {
            op1seeded[(j-1)*bmpInfo->biWidth+(i+1)] = colorSelection;
        }
        if (abs(op1[(j)*bmpInfo->biWidth+(i-1)]-op1[j*bmpInfo->biWidth+i])<=th) {
            op1seeded[(j)*bmpInfo->biWidth+(i-1)] = colorSelection;
        }
        if (abs(op1[(j)*bmpInfo->biWidth+(i+1)]-op1[j*bmpInfo->biWidth+i])<=th) {
            op1seeded[(j)*bmpInfo->biWidth+(i+1)] = colorSelection;
        }
        if (abs(op1[(j+1)*bmpInfo->biWidth+(i-1)]-op1[j*bmpInfo->biWidth+i])<=th) {
            op1seeded[(j+1)*bmpInfo->biWidth+(i-1)] = colorSelection;
        }
        if (abs(op1[(j+1)*bmpInfo->biWidth+(i)]-op1[j*bmpInfo->biWidth+i])<=th) {
            op1seeded[(j+1)*bmpInfo->biWidth+(i)] = colorSelection;
        }
        if (abs(op1[(j+1)*bmpInfo->biWidth+(i+1)]-op1[j*bmpInfo->biWidth+i])<=th) {
            op1seeded[(j+1)*bmpInfo->biWidth+(i+1)] = colorSelection;
        }
    }
    
    for (int j = seedY; j < bmpInfo->biHeight-1; j++) {
        for (int i = 1; i < bmpInfo->biWidth-1; i++) {
            if (abs(op1[(j-1)*bmpInfo->biWidth+(i-1)]-op1[j*bmpInfo->biWidth+i])<=th) {
                op1seeded[(j-1)*bmpInfo->biWidth+(i-1)] = colorSelection;
            }
            if (abs(op1[(j-1)*bmpInfo->biWidth+(i)]-op1[j*bmpInfo->biWidth+i])<=th) {
                op1seeded[(j-1)*bmpInfo->biWidth+(i)] = colorSelection;
            }
            if (abs(op1[(j-1)*bmpInfo->biWidth+(i+1)]-op1[j*bmpInfo->biWidth+i])<=th) {
                op1seeded[(j-1)*bmpInfo->biWidth+(i+1)] = colorSelection;
            }
            if (abs(op1[(j)*bmpInfo->biWidth+(i-1)]-op1[j*bmpInfo->biWidth+i])<=th) {
                op1seeded[(j)*bmpInfo->biWidth+(i-1)] = colorSelection;
            }
            if (abs(op1[(j)*bmpInfo->biWidth+(i+1)]-op1[j*bmpInfo->biWidth+i])<=th) {
                op1seeded[(j)*bmpInfo->biWidth+(i+1)] = colorSelection;
            }
            if (abs(op1[(j+1)*bmpInfo->biWidth+(i-1)]-op1[j*bmpInfo->biWidth+i])<=th) {
                op1seeded[(j+1)*bmpInfo->biWidth+(i-1)] = colorSelection;
            }
            if (abs(op1[(j+1)*bmpInfo->biWidth+(i)]-op1[j*bmpInfo->biWidth+i])<=th) {
                op1seeded[(j+1)*bmpInfo->biWidth+(i)] = colorSelection;
            }
            if (abs(op1[(j+1)*bmpInfo->biWidth+(i+1)]-op1[j*bmpInfo->biWidth+i])<=th) {
                op1seeded[(j+1)*bmpInfo->biWidth+(i+1)] = colorSelection;
            }
        }
    }
    
    for (int j = seedY; j > 0; j--) {
        for (int i = bmpInfo->biWidth-1; i > 0; i--) {
            if (abs(op1[(j-1)*bmpInfo->biWidth+(i-1)]-op1[j*bmpInfo->biWidth+i])<=th) {
                op1seeded[(j-1)*bmpInfo->biWidth+(i-1)] = colorSelection;
            }
            if (abs(op1[(j-1)*bmpInfo->biWidth+(i)]-op1[j*bmpInfo->biWidth+i])<=th) {
                op1seeded[(j-1)*bmpInfo->biWidth+(i)] = colorSelection;
            }
            if (abs(op1[(j-1)*bmpInfo->biWidth+(i+1)]-op1[j*bmpInfo->biWidth+i])<=th) {
                op1seeded[(j-1)*bmpInfo->biWidth+(i+1)] = colorSelection;
            }
            if (abs(op1[(j)*bmpInfo->biWidth+(i-1)]-op1[j*bmpInfo->biWidth+i])<=th) {
                op1seeded[(j)*bmpInfo->biWidth+(i-1)] = colorSelection;
            }
            if (abs(op1[(j)*bmpInfo->biWidth+(i+1)]-op1[j*bmpInfo->biWidth+i])<=th) {
                op1seeded[(j)*bmpInfo->biWidth+(i+1)] = colorSelection;
            }
            if (abs(op1[(j+1)*bmpInfo->biWidth+(i-1)]-op1[j*bmpInfo->biWidth+i])<=th) {
                op1seeded[(j+1)*bmpInfo->biWidth+(i-1)] = colorSelection;
            }
            if (abs(op1[(j+1)*bmpInfo->biWidth+(i)]-op1[j*bmpInfo->biWidth+i])<=th) {
                op1seeded[(j+1)*bmpInfo->biWidth+(i)] = colorSelection;
            }
            if (abs(op1[(j+1)*bmpInfo->biWidth+(i+1)]-op1[j*bmpInfo->biWidth+i])<=th) {
                op1seeded[(j+1)*bmpInfo->biWidth+(i+1)] = colorSelection;
            }
        }
    }
    
    for (int j = 0; j < bmpInfo->biHeight; j++) {
        for (int i = 0; i < bmpInfo->biWidth; i++) {
            if (op1seeded[j*bmpInfo->biWidth+i] == '0') {
                op1seeded[j*bmpInfo->biWidth+i] = 255-colorSelection;
            }
        }
    }
    
    w = bmpInfo->biWidth;
    h = bmpInfo->biHeight;
    split(0, 0, bmpInfo->biWidth, bmpInfo->biHeight, dyMax - dyMin, (dyMin + dyMax) / 2);
    
    fwrite(op1seeded, sizeof(unsigned char), bmpInfo->biSizeImage, obmp1);
    fwrite(op2splited, sizeof(unsigned char), bmpInfo->biSizeImage, obmp2);
    
    fclose(ibmp);
    fclose(obmp1);
    fclose(obmp2);
    
    return 0;
}
