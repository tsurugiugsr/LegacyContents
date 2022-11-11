//
//  main.cpp
//  Image2
//
//  Created by 結城朝日 on 2022/03/07.
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
    
    unsigned char grey;
    int d[256];
    unsigned char o[1024][1000];
    int c=0;
    
    for(int i=0 ; i<256; i++){
        d[i]=0;
    }
    
    for(int i=0;i<1024;i++){
        for (int j=0;j<1000;j++){
            o[i][j]=255;
        }
    }
    
    FILE *ibmp =fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image2/Image2/grey.bmp","rb");
    FILE *obmp1=fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image2/Image2/output.bmp","wb");

    
    BITMAPFILEHEADER *bmpHead=(BITMAPFILEHEADER*)malloc(sizeof(BITMAPFILEHEADER));
    BITMAPINFOHEADER *bmpInfo=(BITMAPINFOHEADER*)malloc(sizeof(BITMAPINFOHEADER));
    RGBQUAD * palette=(RGBQUAD*)malloc(256*sizeof(RGBQUAD));
    
    fread(bmpHead, sizeof(BITMAPFILEHEADER), 1,ibmp);
    fread(bmpInfo,sizeof(BITMAPINFOHEADER), 1, ibmp);
    fread(palette,sizeof(RGBQUAD),256,ibmp);
    for (int i = 0; i < bmpInfo->biHeight; i++)
    {
        for (int j = 0; j < (bmpInfo->biWidth + 3) / 4 * 4; j++)
        {
            fread(&grey, 1, 1, ibmp);
            d[(int)grey]+=1;
        }
    }
    
    bmpInfo->biSizeImage=1000*1024;
    bmpInfo->biHeight=1000;
    bmpInfo->biWidth=1024;
    bmpHead->bfOffBits=sizeof(BITMAPINFOHEADER)+sizeof(BITMAPFILEHEADER)+sizeof(RGBQUAD)*256;
    bmpHead->bfSize=bmpInfo->biSizeImage+bmpHead->bfOffBits;
    
    palette = (RGBQUAD *)malloc(256 * sizeof(RGBQUAD));
    for (int i = 0; i < 256; i++)
        palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = i;
    
    fwrite(bmpHead, sizeof(BITMAPFILEHEADER), 1,   obmp1);
    fwrite(bmpInfo, sizeof(BITMAPINFOHEADER), 1,   obmp1);
    fwrite(palette     , sizeof(RGBQUAD)         , 256, obmp1);
    
    

    
    for(int i=0 ; i<256; i++){
        c+=d[i];
        //cout<<i<<" "<<d[i]<<" ";
    }
    cout<<c;
    
    for(int i=0;i<256;i++){
        for(int j=0;(j<(int)((float)((float)d[i]/(float)c)*10000)&&j<1000);j++){
            o[i*4][j]=(unsigned char)(float)0;
            o[i*4+1][j]=(unsigned char)(float)0;
            o[i*4+2][j]=(unsigned char)(float)0;
            o[i*4+3][j]=(unsigned char)(float)0;
            //cout<<"["<<i<<","<<j<<"]";
        }
    }
    
    for(int i=0;i<1000;i++){
        for(int j=0;j<1024;j++){
            fwrite(&(o[j][i]), 1, 1, obmp1);

        }
    }
    
    fclose(ibmp);
    fclose(obmp1);
    
    return 0;
}
