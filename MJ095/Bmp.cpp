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
