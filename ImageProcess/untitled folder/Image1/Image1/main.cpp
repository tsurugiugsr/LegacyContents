//
//  main.cpp
//  Image1
//
//  Created by 結城朝日 on 2022/02/28.
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

int main(int argc, const char * argv[]) {
    
    unsigned char r,g,b,grey,greyr;
    
    FILE *ibmp =fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image3/Image3/grey3.bmp","rb");
    FILE *obmp1=fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image1/Image1/rgb1.bmp","wb");
    FILE *obmp2=fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image1/Image1/rgb2.bmp","wb");
    FILE *obmp3r=fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image1/Image1/rgb3r.bmp","wb");
    FILE *obmp3g=fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image1/Image1/rgb3g.bmp","wb");
    FILE *obmp3b=fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image1/Image1/rgb3b.bmp","wb");
    
    BITMAPFILEHEADER *bmpHead=(BITMAPFILEHEADER*)malloc(sizeof(BITMAPFILEHEADER));
    BITMAPINFOHEADER *bmpInfo=(BITMAPINFOHEADER*)malloc(sizeof(BITMAPINFOHEADER));
    RGBQUAD * palette=(RGBQUAD*)malloc(256*sizeof(RGBQUAD));
    
    fread(bmpHead, sizeof(BITMAPFILEHEADER), 1,ibmp);
    fread(bmpInfo,sizeof(BITMAPINFOHEADER), 1, ibmp);
    
    bmpInfo->biSizeImage=((bmpInfo->biWidth*3+3)/4)*4*bmpInfo->biHeight;
    bmpInfo->biBitCount=8;
    bmpHead->bfOffBits=sizeof(BITMAPINFOHEADER)+sizeof(BITMAPFILEHEADER)+sizeof(RGBQUAD)*256;
    bmpHead->bfSize=bmpInfo->biSizeImage+bmpHead->bfOffBits;
    
    palette = (RGBQUAD *)malloc(256 * sizeof(RGBQUAD));
    for (int i = 0; i < 256; i++)
        palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = i;
    
    fwrite(bmpHead, sizeof(BITMAPFILEHEADER), 1,   obmp1);
    fwrite(bmpInfo, sizeof(BITMAPINFOHEADER), 1,   obmp1);
    fwrite(palette     , sizeof(RGBQUAD)         , 256, obmp1);
    fwrite(bmpHead, sizeof(BITMAPFILEHEADER), 1,   obmp2);
    fwrite(bmpInfo, sizeof(BITMAPINFOHEADER), 1,   obmp2);
    fwrite(palette     , sizeof(RGBQUAD)         , 256, obmp2);
    fwrite(bmpHead, sizeof(BITMAPFILEHEADER), 1,   obmp3r);
    fwrite(bmpInfo, sizeof(BITMAPINFOHEADER), 1,   obmp3r);
    fwrite(palette     , sizeof(RGBQUAD)         , 256, obmp3r);
    fwrite(bmpHead, sizeof(BITMAPFILEHEADER), 1,   obmp3g);
    fwrite(bmpInfo, sizeof(BITMAPINFOHEADER), 1,   obmp3g);
    fwrite(palette     , sizeof(RGBQUAD)         , 256, obmp3g);
    fwrite(bmpHead, sizeof(BITMAPFILEHEADER), 1,   obmp3b);
    fwrite(bmpInfo, sizeof(BITMAPINFOHEADER), 1,   obmp3b);
    fwrite(palette     , sizeof(RGBQUAD)         , 256, obmp3b);
    
    for (int i = 0; i < bmpInfo->biHeight; i++)
    {
        for (int j = 0; j < (bmpInfo->biWidth + 3) / 4 * 4; j++)
        {
            fread(&b, 1, 1, ibmp);
            fread(&g, 1, 1, ibmp);
            fread(&r, 1, 1, ibmp);
            
            grey = (unsigned char)((float)b * 0.114 +(float)g * 0.587 + (float)r * 0.299);
            greyr=(unsigned char)(255-(float)grey);
            
            fwrite(&grey, 1, 1, obmp1);
            fwrite(&greyr, 1, 1, obmp2);
            fwrite(&r, 1, 1, obmp3r);
            fwrite(&g, 1, 1, obmp3g);
            fwrite(&b, 1, 1, obmp3b);
        }
    }
    
    fclose(ibmp);
    fclose(obmp1);
    fclose(obmp2);
    fclose(obmp3r);
    fclose(obmp3g);
    fclose(obmp3b);
    
    return 0;
}
