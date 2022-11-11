//
//  main.cpp
//  Image4
//
//  Created by 結城朝日 on 2022/03/21.
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

    FILE *ibmp =fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image4/Image4/grey.bmp","rb");
    FILE *bmpScale =fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image4/Image4/scale.bmp","wb");
    FILE *bmpTrans =fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image4/Image4/trans.bmp","wb");
    FILE *bmpMirror =fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image4/Image4/mirror.bmp","wb");
    FILE *bmpRotate =fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image4/Image4/rotate.bmp","wb");


    BITMAPFILEHEADER *bmpHead=(BITMAPFILEHEADER*)malloc(sizeof(BITMAPFILEHEADER));
    BITMAPINFOHEADER *bmpInfo=(BITMAPINFOHEADER*)malloc(sizeof(BITMAPINFOHEADER));
    RGBQUAD * palette=(RGBQUAD*)malloc(256*sizeof(RGBQUAD));
    
    fread(bmpHead, sizeof(BITMAPFILEHEADER), 1,ibmp);
    fread(bmpInfo,sizeof(BITMAPINFOHEADER), 1, ibmp);
    fread(palette,sizeof(RGBQUAD),256,ibmp);
    
    fwrite(bmpHead, sizeof(BITMAPFILEHEADER), 1, bmpTrans);
    fwrite(bmpInfo, sizeof(BITMAPINFOHEADER), 1, bmpTrans);
    fwrite(palette, sizeof(RGBQUAD), 256, bmpTrans);
    fwrite(bmpHead, sizeof(BITMAPFILEHEADER), 1, bmpMirror);
    fwrite(bmpInfo, sizeof(BITMAPINFOHEADER), 1, bmpMirror);
    fwrite(palette, sizeof(RGBQUAD), 256, bmpMirror);
    fwrite(bmpHead, sizeof(BITMAPFILEHEADER), 1, bmpRotate);
    fwrite(bmpInfo, sizeof(BITMAPINFOHEADER), 1, bmpRotate);
    fwrite(palette, sizeof(RGBQUAD), 256, bmpRotate);
    
    bmpInfo->biHeight*=2;
    bmpInfo->biSizeImage*=2;
    fwrite(bmpHead, sizeof(BITMAPFILEHEADER), 1, bmpScale);
    fwrite(bmpInfo, sizeof(BITMAPINFOHEADER), 1, bmpScale);
    fwrite(palette, sizeof(RGBQUAD), 256, bmpScale);
    bmpInfo->biHeight/=2;
    
    unsigned char *o = (unsigned char*)malloc(bmpInfo->biWidth*bmpInfo->biHeight);
    unsigned char *s = (unsigned char*)malloc(bmpInfo->biWidth*2*bmpInfo->biHeight);
    unsigned char *t = (unsigned char*)malloc(bmpInfo->biWidth*bmpInfo->biHeight);
    unsigned char *m = (unsigned char*)malloc(bmpInfo->biWidth*bmpInfo->biHeight);
    unsigned char *r = (unsigned char*)malloc(bmpInfo->biWidth*bmpInfo->biHeight);

    fread(o, bmpInfo->biWidth*bmpInfo->biHeight, 1, ibmp);
    for(int hh = 0;hh<bmpInfo->biWidth*bmpInfo->biHeight;hh++){
        t[hh]=255;
        m[hh]=255;
        r[hh]=255;
    }
    for(int hh = 0;hh<bmpInfo->biWidth*2*bmpInfo->biHeight;hh++){
        s[hh]=255;
    }
    
    int i = 0, j = 0, x, y;
    float angle = 0.1;
    
    while (i<bmpInfo->biHeight) {
        while (j<bmpInfo->biWidth) {
            s[i*bmpInfo->biWidth*2+j]=o[i*bmpInfo->biWidth+j];
            s[i*bmpInfo->biWidth*2+bmpInfo->biWidth+j]=o[i*bmpInfo->biWidth+j];
            
            if (j+128<bmpInfo->biWidth) {
                t[i*bmpInfo->biWidth+j+128]=o[i*bmpInfo->biWidth+j];
            }
            
            m[i*bmpInfo->biWidth+(bmpInfo->biWidth-1-j)]=o[i*bmpInfo->biWidth+j];
            
            x = j * cos(angle) - i * sin(angle);
            y =  j * sin(angle) + i * cos(angle);
            if (0<=x&&x<bmpInfo->biWidth&&0<=y&&y<bmpInfo->biHeight) {
                r[i*bmpInfo->biWidth+j]=o[y*bmpInfo->biWidth+x];
            }
            
            j++;
        }
        j=0;
        i++;
    }
    
    fwrite(s,bmpInfo->biWidth*2*bmpInfo->biHeight, 1,bmpScale);
    fwrite(t,bmpInfo->biWidth*bmpInfo->biHeight, 1,bmpTrans);
    fwrite(m,bmpInfo->biWidth*bmpInfo->biHeight, 1,bmpMirror);
    fwrite(r,bmpInfo->biWidth*bmpInfo->biHeight, 1,bmpRotate);
    
    fclose(ibmp);
    fclose(bmpScale);
    fclose(bmpTrans);
    fclose(bmpMirror);
    fclose(bmpRotate);
    
    return 0;
}
