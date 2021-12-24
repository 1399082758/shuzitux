#include "stdafx.h"
#include <math.h>
#include<complex>
using namespace std;
#define PI 3.14159265435

BITMAPINFO* lpBitsInfo=NULL;
BITMAPINFO* lpDIB_FT=NULL;
BITMAPINFO* lpDIB_IFT=NULL;

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
	
	int i,j,avg,r,g,b,color_index;
	for(i=0;i<256;i++){
		H[i]=0;
		H_R[i]=0;
		H_G[i]=0;
		H_B[i]=0;
	}
	switch(lpBitsInfo->bmiHeader.biBitCount)
	{
		case 24:
			for( i=0;i<h;i++){
				for( j=0;j<w;j++){
					pixel=lpBits + (h - 1 - i) * LineBytes + j * 3;
					H_B[*pixel]++;
					H_G[*(pixel+1)]++;
					H_R[*(pixel+2)]++;
					avg=(*pixel+*(pixel+1)+*(pixel+2))/3;
					H[avg]++;
				}
		}
			break;

		case 8: //分彩色与黑白，需要调色板转换颜色
			if(if_gray())   //256灰度
			{
				for(i=0;i<h;i++)
				{
					for(j=0;j<w;j++)
					{
						pixel=lpBits+LineBytes*(h-1-i)+j;
						H[*pixel]++;
					}
				}
			}
			else   //256彩色
			{
				for(i=0;i<h;i++)
				{
					for(j=0;j<w;j++)
					{
						pixel=lpBits+LineBytes*(h-1-i)+j;
						r=lpBitsInfo->bmiColors[*pixel].rgbRed;
						g=lpBitsInfo->bmiColors[*pixel].rgbGreen;
						b=lpBitsInfo->bmiColors[*pixel].rgbBlue;
						H_B[b]++;
						H_G[g]++;
						H_R[r]++;
						avg=(r+g+b)/3;
						H[avg]++;
					}
				}
			}
			break;

			case 4:
			for(i=0;i<h;i++)
				{
					for(j=0;j<w;j++)
					{
						pixel=lpBits+LineBytes*(h-i-1)+j/2;  //找到该像素所在的字节
						if(j%2) //高四位(前)：>>4
						{
							color_index=*pixel>>4;
							r=lpBitsInfo->bmiColors[color_index].rgbRed;
							g=lpBitsInfo->bmiColors[color_index].rgbGreen;
							b=lpBitsInfo->bmiColors[color_index].rgbBlue;
							H_B[b]++;
							H_G[g]++;
							H_R[r]++;
							avg=(r+g+b)/3;
							H[avg]++;
						}
						else //低四位(后)：&00001111
						{
							color_index=*pixel%16;
							r=lpBitsInfo->bmiColors[color_index].rgbRed;
							g=lpBitsInfo->bmiColors[color_index].rgbGreen;
							b=lpBitsInfo->bmiColors[color_index].rgbBlue;
							H_B[b]++;
							H_G[g]++;
							H_R[r]++;
							avg=(r+g+b)/3;
							H[avg]++;
						}
					}
				}
			break;
			default:break;
	}

}
void linear(int a,int b){
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	BYTE *pixel;
	
	int i,j,r,g,bb,color_index;

	switch(lpBitsInfo->bmiHeader.biBitCount)
	{
		case 24:
			for( i=0;i<h;i++){
				for( j=0;j<w;j++){
					pixel=lpBits + (h - 1 - i) * LineBytes + j * 3;
					*pixel=*pixel*a+b;
					*(pixel+1)=*(pixel+1)*a+b;
					*(pixel+2)=*(pixel+2)*a+b;
				
				}
		}
			break;
		case 8: //分彩色与黑白，需要调色板转换颜色
			if(if_gray())   //256灰度
			{
				for(i=0;i<h;i++)
				{
					for(j=0;j<w;j++)
					{
						pixel=lpBits+LineBytes*(h-1-i)+j;
						*pixel=*pixel*a+b;
						if(*pixel>255)
						*pixel = 255;
						else if(*pixel<0)
						*pixel = 0;
					}
				}
			}
			else   //256彩色
			{
				for(i=0;i<h;i++)
				{
					for(j=0;j<w;j++)
					{
						pixel=lpBits+LineBytes*(h-1-i)+j;
						r=lpBitsInfo->bmiColors[*pixel].rgbRed;
						g=lpBitsInfo->bmiColors[*pixel].rgbGreen;
						bb=lpBitsInfo->bmiColors[*pixel].rgbBlue;
						r=r*a+b;
						g=g*a+b;
						bb=bb*a+b;
						if(r > 255)
							r = 255;
						else if(r < 0)
							r = 0;
						if(g > 255)
							g = 255;
						else if(g < 0)
							g = 0;
						if(bb > 255)
							bb = 255;
						else if(bb < 0)
							bb = 0;
						lpBitsInfo->bmiColors[*pixel].rgbRed = (BYTE)(r+0.5);
						lpBitsInfo->bmiColors[*pixel].rgbGreen = (BYTE)(g+0.5);
						lpBitsInfo->bmiColors[*pixel].rgbBlue = (BYTE)(bb+0.5); 
					}
				}
			}
			break;

			case 4:
			for(i=0;i<h;i++)
				{
					for(j=0;j<w;j++)
					{
						pixel=lpBits+LineBytes*(h-i-1)+j/2;  //找到该像素所在的字节
						if(j%2) //高四位(前)：>>4
						{
							color_index=*pixel>>4;
							r=lpBitsInfo->bmiColors[color_index].rgbRed;
							g=lpBitsInfo->bmiColors[color_index].rgbGreen;
							bb=lpBitsInfo->bmiColors[color_index].rgbBlue;
							r=r*a+b;
							g=g*a+b;
							bb=bb*a+b;
							if(r > 255)
								r = 255;
							else if(r < 0)
								r = 0;
							if(g > 255)
								g = 255;
							else if(g < 0)
								g = 0;
							if(bb > 255)
								bb = 255;
							else if(bb < 0)
								bb = 0;
							r=lpBitsInfo->bmiColors[color_index].rgbRed=(BYTE)(r+0.5);
							g=lpBitsInfo->bmiColors[color_index].rgbGreen=(BYTE)(g+0.5);
							bb=lpBitsInfo->bmiColors[color_index].rgbBlue=(BYTE)(bb+0.5);
						}
						else //低四位(后)：&00001111
						{
							color_index=*pixel%16;
							r=lpBitsInfo->bmiColors[color_index].rgbRed;
							g=lpBitsInfo->bmiColors[color_index].rgbGreen;
							bb=lpBitsInfo->bmiColors[color_index].rgbBlue;
							r=r*a+b;
							g=g*a+b;
							bb=bb*a+b;
							if(r > 255)
								r = 255;
							else if(r < 0)
								r = 0;
							if(g > 255)
								g = 255;
							else if(g < 0)
								g = 0;
							if(bb > 255)
								bb = 255;
							else if(bb < 0)
								bb = 0;
							r=lpBitsInfo->bmiColors[color_index].rgbRed=(BYTE)(r+0.5);
							g=lpBitsInfo->bmiColors[color_index].rgbGreen=(BYTE)(g+0.5);
							bb=lpBitsInfo->bmiColors[color_index].rgbBlue=(BYTE)(bb+0.5);
						}
					}
				}
			break;
			default:break;
	}
}
void equalization(){
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	int i,j;
	BYTE *pixel;
	BYTE Map[256];
	BYTE MapR[256];
	BYTE MapG[256];
	BYTE MapB[256];
	DWORD temp;
	DWORD tempR;
	DWORD tempG;
	DWORD tempB;
	bool if_gray();
	void Histogram();
	switch(lpBitsInfo->bmiHeader.biBitCount){
	case 8:
		Histogram();
		if(if_gray()){
		for(i = 0;i < 256;i++)
		{
			temp = 0;
			for(j = 0;j <= i;j++)
			{
				temp += H[j];
			}
			Map[i] = (BYTE)(temp * 255 / (w * h) + 0.5);
		}
	
		for(i = 0;i < h;i++)
		{
			for(j = 0;j < w;j++)
			{
				pixel = lpBits + LineBytes * (h - 1 - i) + j;
				*pixel = Map[*pixel];
			}
		}
		}
		else{
			break;		
		}
		break;

	case 24:
		Histogram();
		for(i = 0;i < 256;i++)
		{
			tempR = tempG = tempB = 0;
			for(j = 0;j <= i;j++)
			{
				tempR += H_R[j];
				tempG += H_G[j];
				tempB += H_B[j];
			}
			MapR[i] = (BYTE)(tempR * 255 / (w * h) + 0.5);
			MapG[i] = (BYTE)(tempG * 255 / (w * h) + 0.5);
			MapB[i] = (BYTE)(tempB * 255 / (w * h) + 0.5);
		}
	
		for(i = 0;i < h;i++)
		{	
			for(j = 0;j < w;j++)
			{
				pixel = lpBits + LineBytes * (h - 1 - i) + j * 3;
				*pixel = MapB[*pixel];
				*(pixel+1) = MapG[*(pixel+1)];
				*(pixel+2) = MapR[*(pixel+2)];
			}
		}
		break;
	}
}
void FT(complex<double>* TD,complex<double> * FD,int m)
//一阶傅里叶变化
{
	int u,x;
	double angle;
	for(u = 0;u < m;u++)
	{
		FD[u]=0;
		for(x = 0; x < m;x++)
		{
			angle = -2 * PI * u * x / m;
			FD[u] += TD[x] * complex<double>(cos(angle),sin(angle));

		}
		FD[u] /= m;
	}
}
void IFT(complex<double>* FD,complex<double> * TD,int m)
//一阶傅里叶反变化
{
	int u,x;
	double angle;
	for(x = 0;x < m;x++)
	{
		TD[x]=0;
		for(u = 0; u < m;u ++)
		{
			angle = 2 * PI * u * x / m;
			TD[x] += FD[u] * complex<double>(cos(angle),sin(angle));

		}
	}
}
complex<double>* gFD=NULL;
BOOL is_gFD_OK()
{
	return (gFD!=NULL);
}

void Fourier(){	
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	complex<double>* TD =new complex<double>[w*h];
	complex<double>* FD =new complex<double>[w*h];

	int i,j;
	BYTE* pixel;
	for(i = 0;i < h;i++)
		{	
			for(j = 0;j < w;j++)
			{	
				pixel = lpBits + LineBytes * (h - 1 - i) + j;
				TD[w * i + j] = complex<double>(*pixel * pow(-1,i + j),0);
				//
			}
		}
	for(i=0;i<h;i++)
		FT(&TD[i*w],&FD[i*w],w);
	for(i=0;i<h;i++)
		for(j=0;j<w;j++)
			TD[j*h+i] = FD[i*w+j];
	for(i=0;i<w;i++)
		FT(&TD[i*h],&FD[i*h],h);

	delete TD;
	gFD=FD;


	LONG size = 40 + 1024 + LineBytes * h;
	lpDIB_FT = (BITMAPINFO*)malloc(size);
	memcpy(lpDIB_FT,lpBitsInfo,size);
	lpBits = (BYTE*)& lpDIB_FT->bmiColors[lpDIB_FT->bmiHeader.biClrUsed];

	double temp;
	for(i=0;i<h;i++){
		for(j=0;j<w;j++){
			pixel = lpBits + LineBytes * (h-1-i)+j;
			temp = sqrt(FD[j * h + i].real() * FD[j * h + i].real() +
						FD[j * h + i].imag() * FD[j * h + i].imag()) * 2000;
			if(temp > 255)
			{
				temp = 255;
			}
			*pixel = (BYTE)(temp);
		}
	}
}
void IFourier(){
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	complex<double>* TD =new complex<double>[w*h];
	complex<double>* FD =new complex<double>[w*h];

	int i,j;
	BYTE* pixel;
	for(i = 0;i < h;i++)	
			for(j = 0;j < w;j++)
				FD[w * i + j] = gFD[h *j + i]; 
				
	for(i=0;i<h;i++)
		IFT(&FD[i*w],&TD[i*w],w);
	for(i=0;i<h;i++)
		for(j=0;j<w;j++)
			FD[j*h+i] = TD[i*w+j];
	for(i=0;i<w;i++)
		IFT(&FD[i*h],&TD[i*h],h);

	LONG size = 40 + 1024 + LineBytes * h;
	lpDIB_IFT = (BITMAPINFO*)malloc(size);
	memcpy(lpDIB_IFT,lpBitsInfo,size);
	lpBits = (BYTE*)& lpDIB_IFT->bmiColors[lpDIB_IFT->bmiHeader.biClrUsed];

	for(i=0;i<h;i++){
		for(j=0;j<w;j++){
			pixel = lpBits + LineBytes * (h-1-i)+j;			
			*pixel = (BYTE)(TD[h*j+i].real()/pow(-1,i+j));
		}
	}
	delete FD;
	delete TD;
	delete gFD;
	gFD = NULL;
}
