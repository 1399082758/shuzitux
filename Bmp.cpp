#include "stdafx.h"

BITMAPINFO* lpBitsInfo=NULL;

BOOL loadBmpFile(char* BmpFileName)
{
	FILE *fp;
	if(NULL==(fp=fopen(BmpFileName,"rb")))
		return false;

	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;

	fread(&bf,14,1,fp);
	fread(&bi,40,1,fp);
	
	DWORD NumColors;
	if(bi.biClrUsed != 0)
		NumColors = bi.biClrUsed;
	else{
		switch(bi.biBitCount){
		case 1:
			NumColors = 2;break;
		case 4:
			NumColors = 16;break;
		case 8:
			NumColors = 256;break;
		case 24:
			NumColors = 0;break;
	}
	}
	DWORD PalSize = NumColors * 4;
	DWORD ImgSize = (bi.biWidth * bi.biBitCount + 31)/32 * 4 * bi.biHeight; 
    DWORD size = 40+PalSize + ImgSize;
	
	if(NULL == (lpBitsInfo = (BITMAPINFO*)malloc(size)))
		return false;

	fseek(fp,14,SEEK_SET);

	fread((char*)lpBitsInfo,size,1,fp);

	lpBitsInfo->bmiHeader.biClrUsed=NumColors;
	return true;

	
}
void gray(){

	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	int LineBytes_gray=(w * 8 + 31)/32 * 4;
	DWORD size_gray = 40 + 1024 + LineBytes_gray * h;

	BITMAPINFO* lpBitsInfo_gray = (BITMAPINFO*)malloc(size_gray);
	memcpy (lpBitsInfo_gray, lpBitsInfo, 40);
	lpBitsInfo_gray->bmiHeader.biBitCount = 8;
	lpBitsInfo_gray->bmiHeader.biClrUsed = 256;

	int i,j;
	for(i = 0; i < 256; i ++){
		lpBitsInfo_gray->bmiColors[i].rgbBlue = i;
		lpBitsInfo_gray->bmiColors[i].rgbGreen = i;
		lpBitsInfo_gray->bmiColors[i].rgbRed = i;
		lpBitsInfo_gray->bmiColors[i].rgbReserved = 0;
	}

	
	BYTE* lpBits_gray = (BYTE*)&lpBitsInfo_gray->bmiColors[256];

	BYTE* R, *G,*B, avg, *pixel;
	

	for(i = 0; i < h; i ++){
		for(j = 0; j < w; j ++){
			B = lpBits + (h - 1 - i) * LineBytes + j * 3;
			G = B + 1;
			R = G + 1;
			avg = (*R + *G + *B)/3;
			pixel = lpBits_gray + (h - 1 - i)*LineBytes_gray + j;
			*pixel = avg;
		}
	}
	free(lpBitsInfo);
	lpBitsInfo = lpBitsInfo_gray;

}
bool if_gray(){
	bool flag=1;//默认是灰度
	//if(lpBitsInfo->bmiHeader.biBitCount==8)  //先得是8位图
		for(int i=0;i<256;i++)    //根据调色板判断不是256彩色
			if(lpBitsInfo->bmiColors[i].rgbBlue!=i){
				flag=0;
				break;
			}
	//else flag=0;
	return flag;
}  // 1 gray; 0 non gray
void pixel(int i,int j, char* rgb){

	if(NULL==lpBitsInfo)
		return;

	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	BYTE *pixel;
	int r, g, b;

	if(i > w || j > h)
		return;

	switch(lpBitsInfo->bmiHeader.biBitCount){
		case 24:
			pixel=lpBits + (h - 1 - i) * LineBytes + j * 3;
			b = *pixel;
			g = *(pixel + 1);
			r = *(pixel + 2);
			sprintf(rgb,"R:%d G:%d B:%d",r,g,b);
			break;	

		case 8:
			pixel=lpBits + (h - 1 - i) * LineBytes + j ;
			if(!if_gray())
			{
			b = lpBitsInfo->bmiColors[*pixel].rgbBlue;
			g = lpBitsInfo->bmiColors[*pixel].rgbGreen;
			r = lpBitsInfo->bmiColors[*pixel].rgbRed;
			sprintf(rgb,"R:%d G:%d B:%d",r,g,b);
			}
			else
			{
				b = lpBitsInfo->bmiColors[*pixel].rgbBlue;
				sprintf(rgb,"灰度值:%d",b);
			}
			break;

		case 4:
			pixel=lpBits + (h - 1 - i) * LineBytes + j ;
			BYTE bv;
			if(j%2){
			bv=*pixel>>4;
			b = lpBitsInfo->bmiColors[bv].rgbBlue;
			g = lpBitsInfo->bmiColors[bv].rgbGreen;
			r = lpBitsInfo->bmiColors[bv].rgbRed;
			}
			else{
				bv=*pixel&16;
				b = lpBitsInfo->bmiColors[bv].rgbBlue;
				g = lpBitsInfo->bmiColors[bv].rgbGreen;
				r = lpBitsInfo->bmiColors[bv].rgbRed;
			}
			sprintf(rgb,"R:%d G:%d B:%d",r,g,b);
			break;

		case 1:
			pixel=lpBits + (h - 1 - i) * LineBytes + j ;
			bv=(*pixel)&(1<<(7-j%8));  //像素所在位:7-j%8
			bv=bv>>(7-j%8);
			if(bv>0)
				sprintf(rgb,"前景色");
			else
				sprintf(rgb,"后景色");
	}
}
DWORD H[256];
DWORD H_R[256];
DWORD H_G[256];
DWORD H_B[256];
void Histogram(){

	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	BYTE *pixel;
	
	int i,j=0,avg;
	for(i=0;i<256;i++){
		H[i]=0;
		H_R[i]=0;
		H_G[i]=0;
		H_B[i]=0;
	}
	switch(lpBitsInfo->bmiHeader.biBitCount)
	{
		case 24:
			for( i;i<h;i++){
				for( j;j<w;j++){
					pixel=lpBits + (h - 1 - i) * LineBytes + j * 3;
					H_B[*pixel]++;
					H_G[*(pixel+1)]++;
					H_R[*(pixel+2)]++;
					avg=(*pixel+*(pixel+1)+*(pixel+2))/3;
					H[avg]++;
				}
		}
	}

}


