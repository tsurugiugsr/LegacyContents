//
//  main.cpp
//  Image3
//
//  Created by 松岡東矢 on 2022/03/09.
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


unsigned char sortNine(unsigned char a,unsigned char b,unsigned char c,unsigned char d,unsigned char e,unsigned char f ,unsigned char g,unsigned char h,unsigned char i){
    
    float x[9];
    unsigned char t=0;
    x[0]=(float)a;x[1]=(float)b;x[2]=(float)c;x[3]=(float)d;x[4]=(float)e;x[5]=(float)f;x[6]=(float)g;x[7]=(float)h;x[8]=(float)i;
    for(int m=0;m<9;m++){
        for(int n=0;n<8;n++){
            if (x[n]>x[n+1]){
                t=x[n];
                x[n]=x[n+1];
                x[n+1]=t;
            }
        }
    }
    //cout<<(int)x[4];
    return (unsigned char)x[4];
}

int main(int argc, const char * argv[]) {
    
    int i=0,j=0;
    
    FILE *ibmp =fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image4/Image4/grey.bmp","rb");
    FILE *obmp1=fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image3/Image3/output.bmp","wb");
    FILE *obmp2=fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image3/Image3/output2.bmp","wb");

    BITMAPFILEHEADER *bmpHead=(BITMAPFILEHEADER*)malloc(sizeof(BITMAPFILEHEADER));
    BITMAPINFOHEADER *bmpInfo=(BITMAPINFOHEADER*)malloc(sizeof(BITMAPINFOHEADER));
    RGBQUAD * palette=(RGBQUAD*)malloc(256*sizeof(RGBQUAD));
    
    fread(bmpHead, sizeof(BITMAPFILEHEADER), 1,ibmp);
    fread(bmpInfo,sizeof(BITMAPINFOHEADER), 1, ibmp);
    fread(palette,sizeof(RGBQUAD),256,ibmp);
    
    fwrite(bmpHead, sizeof(BITMAPFILEHEADER), 1, obmp1);
    fwrite(bmpInfo, sizeof(BITMAPINFOHEADER), 1, obmp1);
    fwrite(palette, sizeof(RGBQUAD), 256, obmp1);
    fwrite(bmpHead, sizeof(BITMAPFILEHEADER), 1, obmp2);
    fwrite(bmpInfo, sizeof(BITMAPINFOHEADER), 1, obmp2);
    fwrite(palette, sizeof(RGBQUAD), 256, obmp2);
    
    unsigned char *b = (unsigned char*)malloc(bmpInfo->biWidth*bmpInfo->biHeight);
    unsigned char *m = (unsigned char*)malloc(bmpInfo->biWidth*bmpInfo->biHeight);
    fread(b, bmpInfo->biWidth*bmpInfo->biHeight, 1, ibmp);
    for(int hh = 0;hh<bmpInfo->biWidth*bmpInfo->biHeight;hh++){
        m[hh]=b[hh];
    }
    
    while(i<bmpInfo->biHeight){//平均处理
        while(j<bmpInfo->biWidth){
            if(j==0||j==bmpInfo->biWidth-1||i==0||i==bmpInfo->biHeight-1){//边界处理
                
                if(j+i==0||j+i==bmpInfo->biWidth-1||j+i==(bmpInfo->biWidth-1)*2){//四个顶点保留
                    
                }
                else{//四边缘向外复制一行
                    if (j==0) {
                        b[i*bmpInfo->biWidth+j]=(b[(i-1)*bmpInfo->biWidth+(j)]+b[(i-1)*bmpInfo->biWidth+(j)]+b[(i-1)*bmpInfo->biWidth+(j+1)]+b[(i)*bmpInfo->biWidth+(j)]+b[(i)*bmpInfo->biWidth+(j)]+b[(i)*bmpInfo->biWidth+(j+1)]+b[(i+1)*bmpInfo->biWidth+(j)]+b[(i+1)*bmpInfo->biWidth+(j+1)]+b[(i+1)*bmpInfo->biWidth+(j)])/9;
                    }
                    if (i==0) {
                        b[i*bmpInfo->biWidth+j]=(b[(i)*bmpInfo->biWidth+(j)]+b[(i)*bmpInfo->biWidth+(j-1)]+b[(i)*bmpInfo->biWidth+(j+1)]+b[(i)*bmpInfo->biWidth+(j-1)]+b[(i)*bmpInfo->biWidth+(j)]+b[(i)*bmpInfo->biWidth+(j+1)]+b[(i+1)*bmpInfo->biWidth+(j)]+b[(i+1)*bmpInfo->biWidth+(j+1)]+b[(i+1)*bmpInfo->biWidth+(j-1)])/9;
                    }
                    if (j==bmpInfo->biWidth-1) {
                        b[i*bmpInfo->biWidth+j]=(b[(i-1)*bmpInfo->biWidth+(j)]+b[(i-1)*bmpInfo->biWidth+(j-1)]+b[(i-1)*bmpInfo->biWidth+(j)]+b[(i)*bmpInfo->biWidth+(j-1)]+b[(i)*bmpInfo->biWidth+(j)]+b[(i)*bmpInfo->biWidth+(j)]+b[(i+1)*bmpInfo->biWidth+(j)]+b[(i+1)*bmpInfo->biWidth+(j)]+b[(i+1)*bmpInfo->biWidth+(j-1)])/9;
                    }
                    if (i==bmpInfo->biHeight-1) {
                        b[i*bmpInfo->biWidth+j]=(b[(i-1)*bmpInfo->biWidth+(j)]+b[(i-1)*bmpInfo->biWidth+(j-1)]+b[(i-1)*bmpInfo->biWidth+(j+1)]+b[(i)*bmpInfo->biWidth+(j-1)]+b[(i)*bmpInfo->biWidth+(j)]+b[(i)*bmpInfo->biWidth+(j+1)]+b[(i)*bmpInfo->biWidth+(j)]+b[(i)*bmpInfo->biWidth+(j+1)]+b[(i)*bmpInfo->biWidth+(j-1)])/9;
                    }
                }
                
                j++;
            }
            else{//边界以内
                b[i*bmpInfo->biWidth+j]=(b[(i-1)*bmpInfo->biWidth+(j)]+b[(i-1)*bmpInfo->biWidth+(j-1)]+b[(i-1)*bmpInfo->biWidth+(j+1)]+b[(i)*bmpInfo->biWidth+(j-1)]+b[(i)*bmpInfo->biWidth+(j)]+b[(i)*bmpInfo->biWidth+(j+1)]+b[(i+1)*bmpInfo->biWidth+(j)]+b[(i+1)*bmpInfo->biWidth+(j+1)]+b[(i+1)*bmpInfo->biWidth+(j-1)])/9;
                j++;
            }
        }
        j=0;
        i++;
    }
    
    fwrite(b, bmpInfo->biWidth*bmpInfo->biHeight, 1, obmp1);
    
    i=0;
    j=0;
    
    while(i<bmpInfo->biHeight){//中值滤波
        while(j<bmpInfo->biWidth){
            if(j==0||j==bmpInfo->biWidth-1||i==0||i==bmpInfo->biHeight-1){//边界处理
                
                if(j+i==0||j+i==bmpInfo->biWidth-1||j+i==(bmpInfo->biWidth-1)*2){//四个顶点保留
                    
                }
                else{//四边缘向外复制一行
                    if (j==0) {
                        m[i*bmpInfo->biWidth+j]=sortNine(m[(i-1)*bmpInfo->biWidth+(j)],m[(i-1)*bmpInfo->biWidth+(j)],m[(i-1)*bmpInfo->biWidth+(j+1)],m[(i)*bmpInfo->biWidth+(j)],m[(i)*bmpInfo->biWidth+(j)],m[(i)*bmpInfo->biWidth+(j+1)],m[(i+1)*bmpInfo->biWidth+(j)],m[(i+1)*bmpInfo->biWidth+(j+1)],m[(i+1)*bmpInfo->biWidth+(j)]);
                    }
                    if (i==0) {
                        m[i*bmpInfo->biWidth+j]=sortNine(m[(i)*bmpInfo->biWidth+(j)],m[(i)*bmpInfo->biWidth+(j-1)],m[(i)*bmpInfo->biWidth+(j+1)],m[(i)*bmpInfo->biWidth+(j-1)],m[(i)*bmpInfo->biWidth+(j)],m[(i)*bmpInfo->biWidth+(j+1)],m[(i+1)*bmpInfo->biWidth+(j)],m[(i+1)*bmpInfo->biWidth+(j+1)],m[(i+1)*bmpInfo->biWidth+(j-1)]);
                    }
                    if (j==bmpInfo->biWidth-1) {
                        m[i*bmpInfo->biWidth+j]=sortNine(m[(i-1)*bmpInfo->biWidth+(j)],m[(i-1)*bmpInfo->biWidth+(j-1)],m[(i-1)*bmpInfo->biWidth+(j)],m[(i)*bmpInfo->biWidth+(j-1)],m[(i)*bmpInfo->biWidth+(j)],m[(i)*bmpInfo->biWidth+(j)],m[(i+1)*bmpInfo->biWidth+(j)],m[(i+1)*bmpInfo->biWidth+(j)],m[(i+1)*bmpInfo->biWidth+(j-1)]);
                    }
                    if (i==bmpInfo->biHeight-1) {
                        m[i*bmpInfo->biWidth+j]=sortNine(m[(i-1)*bmpInfo->biWidth+(j)],m[(i-1)*bmpInfo->biWidth+(j-1)],m[(i-1)*bmpInfo->biWidth+(j+1)],m[(i)*bmpInfo->biWidth+(j-1)],m[(i)*bmpInfo->biWidth+(j)],m[(i)*bmpInfo->biWidth+(j+1)],m[(i)*bmpInfo->biWidth+(j)],m[(i)*bmpInfo->biWidth+(j+1)],m[(i)*bmpInfo->biWidth+(j-1)]);
                    }
                }
                
                j++;
            }
            else{
                m[i*bmpInfo->biWidth+j]=sortNine(m[(i-1)*bmpInfo->biWidth+(j)],m[(i-1)*bmpInfo->biWidth+(j-1)],m[(i-1)*bmpInfo->biWidth+(j+1)],m[(i)*bmpInfo->biWidth+(j-1)],m[(i)*bmpInfo->biWidth+(j)],m[(i)*bmpInfo->biWidth+(j+1)],m[(i+1)*bmpInfo->biWidth+(j)],m[(i+1)*bmpInfo->biWidth+(j+1)],m[(i+1)*bmpInfo->biWidth+(j-1)]);
                j++;
            }
        }
        j=0;
        i++;
    }
    
    fwrite(m, bmpInfo->biWidth*bmpInfo->biHeight, 1, obmp2);
    
    fclose(ibmp);
    fclose(obmp1);
    fclose(obmp2);
    
    return 0;
}
