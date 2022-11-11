//
//  main.cpp
//  Image5
//
//  Created by 松岡東矢 on 2022/03/28.
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
    
    unsigned char grey;
    int d[256];
    unsigned char o1[1024][1000],o2[1024][1000],o3[1024][1000];
    int c=0;
    
    for(int i=0 ; i<256; i++){
        d[i]=0;
    }
    
    for(int i=0;i<1024;i++){
        for (int j=0;j<1000;j++){
            o1[i][j]=255;
            o2[i][j]=255;
            o3[i][j]=255;
        }
    }
    
    FILE *ibmp =fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image5/Image5/grey.bmp","rb");
    FILE *obmp1=fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image5/Image5/output1.bmp","wb");
    FILE *obmp2=fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image5/Image5/output2.bmp","wb");
    FILE *obmp3=fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image5/Image5/output3.bmp","wb");
    FILE *obmp1p=fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image5/Image5/output1p.bmp","wb");
    FILE *obmp2p=fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image5/Image5/output2p.bmp","wb");
    FILE *obmp3p=fopen("/Users/touyamatsuoka/Documents/作业/2022.2/数字图像处理/untitled folder/Image5/Image5/output3p.bmp","wb");
    
    int tres1 = 128, tres2 = 128, tres3 = 0;
    int size = 0;


    
    BITMAPFILEHEADER *bmpHead=(BITMAPFILEHEADER*)malloc(sizeof(BITMAPFILEHEADER));
    BITMAPINFOHEADER *bmpInfo=(BITMAPINFOHEADER*)malloc(sizeof(BITMAPINFOHEADER));
    RGBQUAD * palette=(RGBQUAD*)malloc(256*sizeof(RGBQUAD));
    
    fread(bmpHead, sizeof(BITMAPFILEHEADER), 1,ibmp);
    fread(bmpInfo,sizeof(BITMAPINFOHEADER), 1, ibmp);
    fread(palette,sizeof(RGBQUAD),256,ibmp);
    
    fwrite(bmpHead, sizeof(BITMAPFILEHEADER), 1,   obmp1p);
    fwrite(bmpInfo, sizeof(BITMAPINFOHEADER), 1,   obmp1p);
    fwrite(palette     , sizeof(RGBQUAD)         , 256, obmp1p);
    fwrite(bmpHead, sizeof(BITMAPFILEHEADER), 1,   obmp2p);
    fwrite(bmpInfo, sizeof(BITMAPINFOHEADER), 1,   obmp2p);
    fwrite(palette     , sizeof(RGBQUAD)         , 256, obmp2p);
    fwrite(bmpHead, sizeof(BITMAPFILEHEADER), 1,   obmp3p);
    fwrite(bmpInfo, sizeof(BITMAPINFOHEADER), 1,   obmp3p);
    fwrite(palette     , sizeof(RGBQUAD)         , 256, obmp3p);
    
    unsigned char* op1 = (unsigned char*)malloc(bmpInfo->biSizeImage);
    unsigned char* op2 = (unsigned char*)malloc(bmpInfo->biSizeImage);
    unsigned char* op3 = (unsigned char*)malloc(bmpInfo->biSizeImage);
    size = bmpInfo->biSizeImage;
    for (int i = 0; i < bmpInfo->biHeight; i++)
    {
        for (int j = 0; j < (bmpInfo->biWidth + 3) / 4 * 4; j++)
        {
            fread(&grey, 1, 1, ibmp);
            d[(int)grey]+=1;
            op1[i*bmpInfo->biWidth+j]=grey;
            op2[i*bmpInfo->biWidth+j]=grey;
            op3[i*bmpInfo->biWidth+j]=grey;
            
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
    fwrite(bmpHead, sizeof(BITMAPFILEHEADER), 1,   obmp2);
    fwrite(bmpInfo, sizeof(BITMAPINFOHEADER), 1,   obmp2);
    fwrite(palette     , sizeof(RGBQUAD)         , 256, obmp2);
    fwrite(bmpHead, sizeof(BITMAPFILEHEADER), 1,   obmp3);
    fwrite(bmpInfo, sizeof(BITMAPINFOHEADER), 1,   obmp3);
    fwrite(palette     , sizeof(RGBQUAD)         , 256, obmp3);
    
    for(int i=0 ; i<256; i++){
        c+=d[i];
    }
    cout<<c;
    
    for(int i=0;i<256;i++){
        for(int j=0;(j<(int)((float)((float)d[i]/(float)c)*50000)&&j<1000);j++){
            o1[i*4][j]=(unsigned char)(float)128;
            o1[i*4+1][j]=(unsigned char)(float)128;
            o1[i*4+2][j]=(unsigned char)(float)128;
            o1[i*4+3][j]=(unsigned char)(float)128;
            o2[i*4][j]=(unsigned char)(float)128;
            o2[i*4+1][j]=(unsigned char)(float)128;
            o2[i*4+2][j]=(unsigned char)(float)128;
            o2[i*4+3][j]=(unsigned char)(float)128;
            o3[i*4][j]=(unsigned char)(float)128;
            o3[i*4+1][j]=(unsigned char)(float)128;
            o3[i*4+2][j]=(unsigned char)(float)128;
            o3[i*4+3][j]=(unsigned char)(float)128;
            //cout<<"["<<i<<","<<j<<"]";
        }
    }
    
    int tres2n = 0,tres2l = 0,tres2r = 0,tres2lc = 0,tres2rc = 0;
    do {
        tres2n=tres2;
        for (int i=0; i<256; i++) {
            if(d[i]!=0)
            {
                if (i<tres2) {
                    tres2l+=d[i]*i;
                    tres2lc+=d[i];
                }
                else{
                    tres2r+=d[i]*i;
                    tres2rc+=d[i];
                }
            }
        }
        tres2=(tres2l/tres2lc+tres2r/tres2rc)/2;
        cout<<endl;
        cout<<tres2<<" "<<tres2n;
        //cout<<tres2n;
    } while (!(abs( tres2-tres2n)<=2));
    
    cout<<endl;
    double tres3s[256];
    double tres3l=0,tres3lc=0,tres3r=0,tres3rc=0,tres3la=0,tres3ra=0;
    for (int i = 0; i<256; i++) {
        tres3s[i]=0;
    }
    
    for (int i =0; i<256; i++) {
        for (int j = 0; j<256; j++) {
            if (j<i) {
                tres3l+=d[j]*j;
                tres3lc+=d[j];
            }
            else
            {
                tres3r+=d[j]*j;
                tres3rc+=d[j];
            }
        }
        if(tres3lc!=0)
        tres3la=tres3l/tres3lc;
        if(tres3rc!=0)
        tres3ra=tres3r/tres3rc;
        for (int j =0; j<256; j++) {
            if(d[j]!=0){if (j<i) {
                tres3s[i]+=((float)d[j]/(float)c)*((float)j-tres3la)*((float)j-tres3la);
            }
            else
            {
                tres3s[i]+=((float)d[j]/(float)c)*((float)j-tres3ra)*((float)j-tres3ra);
            }}
        }
        cout<<i<<" "<<tres3la<<" "<<tres3ra<<" "<< tres3s[i]<<endl;
        tres3l=0;
        tres3lc=0;
        tres3r=0;
        tres3rc=0;
        tres3la=0;
        tres3ra=0;

    }
    int temp;
    temp = tres3s[0];
    for (int i = 0; i<256; i++) {
        if (tres3s[i]<temp) {
            temp=tres3s[i];
            tres3=i;
        }
    }
    cout<<endl<<tres3;
    
    for (int i = 0; i<size; i++) {
        if (op1[i]<tres1) {
            op1[i]=0;
        }
        else{
            op1[i]=255;
        }
        if (op2[i]<tres2) {
            op2[i]=0;
        }
        else{
            op2[i]=255;
        }
        if (op3[i]<tres3) {
            op3[i]=0;
        }
        else{
            op3[i]=255;
        }
    }
    
    for (int i = 0; i<1000; i++) {
        o1[tres1*4][i]=0;
        o2[tres2*4][i]=0;
        o3[tres3*4][i]=0;
        o1[tres1*4+1][i]=0;
        o2[tres2*4+1][i]=0;
        o3[tres3*4+1][i]=0;
        o1[tres1*4+2][i]=0;
        o2[tres2*4+2][i]=0;
        o3[tres3*4+2][i]=0;
        o1[tres1*4+3][i]=0;
        o2[tres2*4+3][i]=0;
        o3[tres3*4+3][i]=0;
    }
    
    for(int i=0;i<1000;i++){
        for(int j=0;j<1024;j++){
            fwrite(&(o1[j][i]), 1, 1, obmp1);
            fwrite(&(o2[j][i]), 1, 1, obmp2);
            fwrite(&(o3[j][i]), 1, 1, obmp3);

        }
    }
    
    fwrite(op1, 1, size, obmp1p);
    fwrite(op2, 1, size, obmp2p);
    fwrite(op3, 1, size, obmp3p);
    
    fclose(ibmp);
    fclose(obmp1);
    fclose(obmp2);
    fclose(obmp3);
    fclose(obmp1p);
    fclose(obmp2p);
    fclose(obmp3p);
    
    return 0;
}
