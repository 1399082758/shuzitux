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
	bool flag=1;//Ĭ���ǻҶ�
	//if(lpBitsInfo->bmiHeader.biBitCount==8)  //�ȵ���8λͼ
		for(int i=0;i<256;i++)    //���ݵ�ɫ���жϲ���256��ɫ
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
				sprintf(rgb,"�Ҷ�ֵ:%d",b);
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
			bv=(*pixel)&(1<<(7-j%8));  //��������λ:7-j%8
			bv=bv>>(7-j%8);
			if(bv>0)
				sprintf(rgb,"ǰ��ɫ");
			else
				sprintf(rgb,"��ɫ");
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

		case 8: //�ֲ�ɫ��ڰף���Ҫ��ɫ��ת����ɫ
			if(if_gray())   //256�Ҷ�
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
			else   //256��ɫ
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
						pixel=lpBits+LineBytes*(h-i-1)+j/2;  //�ҵ����������ڵ��ֽ�
						if(j%2) //����λ(ǰ)��>>4
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
						else //����λ(��)��&00001111
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
		case 8: //�ֲ�ɫ��ڰף���Ҫ��ɫ��ת����ɫ
			if(if_gray())   //256�Ҷ�
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
			else   //256��ɫ
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
						pixel=lpBits+LineBytes*(h-i-1)+j/2;  //�ҵ����������ڵ��ֽ�
						if(j%2) //����λ(ǰ)��>>4
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
						else //����λ(��)��&00001111
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
bool if_equalization(){
	bool equal=0;
	if(lpBitsInfo->bmiHeader.biBitCount==24||if_gray())
		equal=1;
	return equal;
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
//һ�׸���Ҷ�仯
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
//һ�׸���Ҷ���仯
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

void FFT(complex<double> * TD, complex<double> * FD, int r)
{
	// ���㸶��Ҷ�任����
	LONG count = 1 << r;
	// �����Ȩϵ��
	int i;
	double angle;
	complex<double>* W = new complex<double>[count / 2];
	for(i = 0; i < count / 2; i++)
	{
		angle = -i * PI * 2 / count;
		W[i] = complex<double> (cos(angle), sin(angle));
	}
	// ��ʱ���д��X1
	complex<double>* X1 = new complex<double>[count];
	memcpy(X1, TD, sizeof(complex<double>) * count);
	
	// ���õ����㷨���п��ٸ���Ҷ�任�����ΪƵ��ֵX2
	complex<double>* X2 = new complex<double>[count]; 

	int k,j,p,size;
	complex<double>* temp;
	for (k = 0; k < r; k++)
	{
		for (j = 0; j < 1 << k; j++)
		{
			size = 1 << (r-k);
			for (i = 0; i < size/2; i++)
			{
				p = j * size;
				X2[i + p] = X1[i + p] + X1[i + p + size/2];
				X2[i + p + size/2] = (X1[i + p] - X1[i + p + size/2]) * W[i * (1<<k)];
			}
		}
		temp  = X1;
		X1 = X2;
		X2 = temp;
	}
	
	// ����������λ�������У�
	for (j = 0; j < count; j++)
	{
		p = 0;
		for (i = 0; i < r; i++)
		{
			if (j & (1<<i))
			{
				p += 1<<(r-i-1);
			}
		}
		FD[j]=X1[p];
		FD[j] /= count;
	}
	
	// �ͷ��ڴ�
	delete W;
	delete X1;
	delete X2;
}

void FFourier()
{
	//ͼ��Ŀ�Ⱥ͸߶�
	int width = lpBitsInfo->bmiHeader.biWidth;
	int height = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (width * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	//ָ��ͼ������ָ��
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[256];

	// FFT��ȣ�����Ϊ2�������η���
	int FFT_w = 1;
	// FFT��ȵ�����������������
	int wp = 0;
	while(FFT_w * 2 <= width)
	{
		FFT_w *= 2;
		wp ++;
	}

	// FFT�߶ȣ�����Ϊ2�������η���
	int FFT_h = 1;
	// FFT�߶ȵ�����������������
	int hp = 0;
	while(FFT_h * 2 <= height)
	{
		FFT_h *= 2;
		hp ++;
	}

	// �����ڴ�
	complex<double>* TD = new complex<double>[FFT_w * FFT_h];
	complex<double>* FD = new complex<double>[FFT_w * FFT_h];
	
	int i, j;
	BYTE* pixel;
	
	for(i = 0; i < FFT_h; i++)  // ��
	{
		for(j = 0; j < FFT_w; j++)  // ��
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			pixel = lpBits + LineBytes * (height - 1 - i) + j;

			// ��ʱ��ֵ
			TD[j + FFT_w * i] = complex<double>(*pixel* pow(-1,i+j), 0);
		}
	}
	
	for(i = 0; i < FFT_h; i++)
	{
		// ��y������п��ٸ���Ҷ�任
		FFT(&TD[FFT_w * i], &FD[FFT_w * i], wp);
	}
	
	// �����м�任���
	for(i = 0; i < FFT_h; i++)
	{
		for(j = 0; j < FFT_w; j++)
		{
			TD[i + FFT_h * j] = FD[j + FFT_w * i];
		}
	}
	
	for(i = 0; i < FFT_w; i++)
	{
		// ��x������п��ٸ���Ҷ�任
		FFT(&TD[i * FFT_h], &FD[i * FFT_h], hp);
	}

	// ɾ����ʱ����
	delete TD;

	//����Ƶ��ͼ��
	//ΪƵ��ͼ������ڴ�
	LONG size = 40 + 1024 + LineBytes * height;
	lpDIB_FT = (LPBITMAPINFO) malloc(size);
	if (NULL == lpDIB_FT)
		return;
	memcpy(lpDIB_FT, lpBitsInfo, size);

	//ָ��Ƶ��ͼ������ָ��
	lpBits = (BYTE*)&lpDIB_FT->bmiColors[256];

	double temp;
	for(i = 0; i < FFT_h; i++) // ��
	{
		for(j = 0; j < FFT_w; j++) // ��
		{
			// ����Ƶ�׷���
			temp = sqrt(FD[j * FFT_h + i].real() * FD[j * FFT_h + i].real() + 
				        FD[j * FFT_h + i].imag() * FD[j * FFT_h + i].imag()) *2000;
			
			// �ж��Ƿ񳬹�255
			if (temp > 255)
			{
				// ���ڳ����ģ�ֱ������Ϊ255
				temp = 255;
			}
			
			pixel = lpBits + LineBytes * (height - 1 - i) + j;

			// ����Դͼ��
			*pixel = (BYTE)(temp);
		}
	}

	gFD=FD;

}
void IFFT(complex<double> * FD, complex<double> * TD, int r)
{
	// ����Ҷ�任����
	LONG	count;
	// ���㸶��Ҷ�任����
	count = 1 << r;

	// ������������洢��
	complex<double> * X = new complex<double>[count];
	// ��Ƶ���д��X
	memcpy(X, FD, sizeof(complex<double>) * count);
	
	// ����
	for(int i = 0; i < count; i++)
		X[i] = complex<double> (X[i].real(), -X[i].imag());
	
	// ���ÿ��ٸ���Ҷ�任
	FFT(X, TD, r);
	
	// ��ʱ���Ĺ���
	for(i = 0; i < count; i++)
		TD[i] = complex<double> (TD[i].real() * count, -TD[i].imag() * count);
	
	// �ͷ��ڴ�
	delete X;
}

void IFFourier()
{
	//ͼ��Ŀ�Ⱥ͸߶�
	int width = lpBitsInfo->bmiHeader.biWidth;
	int height = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (width * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	// FFT��ȣ�����Ϊ2�������η���
	int FFT_w = 1;
	// FFT��ȵ�����������������
	int wp = 0;
	while(FFT_w * 2 <= width)
	{
		FFT_w *= 2;
		wp ++;
	}

	// FFT�߶ȣ�����Ϊ2�������η���
	int FFT_h = 1;
	// FFT�߶ȵ�����������������
	int hp = 0;
	while(FFT_h * 2 <= height)
	{
		FFT_h *= 2;
		hp ++;
	}

	// �����ڴ�
	complex<double>* TD = new complex<double>[FFT_w * FFT_h];
	complex<double>* FD = new complex<double>[FFT_w * FFT_h];
	
	int i, j;
	for(i = 0; i < FFT_h; i++)  // ��
		for(j = 0; j < FFT_w; j++)  // ��
			FD[j + FFT_w * i] = gFD[i + FFT_h*j];
	
	// ��ˮƽ������п��ٸ���Ҷ�任
	for(i = 0; i < FFT_h; i++)
		IFFT(&FD[FFT_w * i], &TD[FFT_w * i], wp);
	
	// �����м�任���
	for(i = 0; i < FFT_h; i++)
		for(j = 0; j < FFT_w; j++)
			FD[i + FFT_h * j] = TD[j + FFT_w * i];
	
	// �ش�ֱ������п��ٸ���Ҷ�任
	for(i = 0; i < FFT_w; i++)
		IFFT(&FD[i * FFT_h], &TD[i * FFT_h], hp);

	//Ϊ���任ͼ������ڴ�
	LONG size = 40 + 1024 + LineBytes * height;

	lpDIB_IFT = (LPBITMAPINFO) malloc(size);
	if (NULL == lpDIB_IFT)
		return;
	memcpy(lpDIB_IFT, lpBitsInfo, size);

	//ָ�򷴱任ͼ������ָ��
	BYTE* lpBits = (BYTE*)&lpDIB_IFT->bmiColors[256];
	BYTE* pixel;
	double temp;
	for(i = 0; i < FFT_h; i++) // ��
	{
		for(j = 0; j < FFT_w; j++) // ��
		{
			pixel = lpBits + LineBytes * (height - 1 - i) + j;
			temp= (TD[j*FFT_h + i].real() / pow(-1, i+j));
			if (temp < 0)
				temp = 0;
			else if (temp >255)
				temp = 255;
			*pixel = (BYTE)temp;
		}
	}

	// ɾ����ʱ����
	delete FD;
	delete TD;
	delete gFD;
gFD = NULL;
}

void Template(int* Array, float coef){
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	
	LONG size = 40 + 1024 + LineBytes * h;
	BITMAPINFO* new_lpBitsInfo = (BITMAPINFO*)malloc(size);
	memcpy(new_lpBitsInfo,lpBitsInfo,size);
	BYTE* new_lpBits = (BYTE*)& new_lpBitsInfo->bmiColors[new_lpBitsInfo->bmiHeader.biClrUsed];

	int i,j,k,l;
	BYTE *pixel,*new_pixel;
	float temp;

	for(i = 1;i < h - 1;i++)
	{
		for(j = 1;j < w - 1;j++)
		{
			new_pixel = new_lpBits + LineBytes * (h - 1 - i) + j;
			temp = 0;
			for(k = 0;k < 3;k++)
			{
				for(l = 0;l < 3;l++)
				{
					pixel = lpBits + LineBytes * (h - i - k) + j - 1 + l;
					temp += (*pixel) * Array[k * 3 + l];
				}
			}
			temp *= coef;
			if(temp < 0)
				*new_pixel = 0;
			else if(temp > 255)
				*new_pixel = 255;
			else
				*new_pixel = (BYTE)(temp + 0.5);
		}
	}
	free(lpBitsInfo);
	lpBitsInfo = new_lpBitsInfo;

}
void AverageFilter(){
	int array[9];
	array[0] = 1;array[1] = 1;array[2] = 1;
	array[3] = 1;array[4] = 1;array[5] = 1;
	array[6] = 1;array[7] = 1;array[8] = 1;
	Template(array,(float)1/9);
/*
	array[0] = 1;array[1] = 2;array[2] = 1;
	array[3] = 2;array[4] = 9;array[5] = 2;
	array[6] = 1;array[7] = 2;array[8] = 1;
	tempcon(array,(float)1/16);

*/
	
	
}
void RaplasSharp()
{
	int Array[9];
	Array[0]=-1; Array[1]=-1; Array[2]=-1;
	Array[3]=-1; Array[4]=9; Array[5]=-1;
	Array[6]=-1; Array[7]=-1; Array[8]=-1;
	Template(Array,(float)1);
}
BYTE GetMidNum(BYTE* Array)
{
	int i,j,t;
	for(j=0;j<8;j++){
		for(i=0;i<8-j;i++)
		{
			if(Array[i]>Array[i+1])
			{
				t=Array[i];
				Array[i]=Array[i+1];
				Array[i+1]=t;
			}
		}
	}
	return (Array[4]);
}
void MedianFilter(){
	int w= lpBitsInfo->bmiHeader.biWidth;
	int h= lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;//ÿ���ֽ���
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed]; //ָ��λͼ���ݵ�ָ��

	LONG size=40+1024+LineBytes*h;
	BITMAPINFO* new_lpBitsInfo=(BITMAPINFO* )malloc(size);
	memcpy(new_lpBitsInfo,lpBitsInfo,size);
	BYTE* new_lpBits = (BYTE*)&new_lpBitsInfo->bmiColors[new_lpBitsInfo->bmiHeader.biClrUsed]; //ָ��λͼ���ݵ�ָ��


	int i,j,k,l;
	BYTE *pixel;
	BYTE *new_pixel;
	BYTE Value[9];

	for(i=1;i<h-1;i++)  //��Ե������
	{
		for(j=1;j<w-1;j++)
		{
			new_pixel=new_lpBits+LineBytes*(h-1-i)+j;  //ָ��Ҫ����������ص�λ��
			for(k=0;k<3;k++)  //��ÿ�����ؽ��У�3*3ģ������
			{
				for(l=0;l<3;l++)
				{
					pixel = lpBits+LineBytes*(h-k-i)+j-1+l;  
					Value[k*3+l]=*pixel;
				}
			}
			*new_pixel=(BYTE)GetMidNum(Value);
		}
	}
	free(lpBitsInfo);
	lpBitsInfo=new_lpBitsInfo;   //����ͼ���滻 ԭͼ��
}
void GradSharp(){
	int w= lpBitsInfo->bmiHeader.biWidth;
	int h= lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;//ÿ���ֽ���
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed]; //ָ��λͼ���ݵ�ָ��

	LONG size=40+1024+LineBytes*h;
	BITMAPINFO* new_lpBitsInfo=(BITMAPINFO* )malloc(size);
	memcpy(new_lpBitsInfo,lpBitsInfo,size);
	BYTE* new_lpBits = (BYTE*)&new_lpBitsInfo->bmiColors[new_lpBitsInfo->bmiHeader.biClrUsed]; //ָ��λͼ���ݵ�ָ��


	int i,j;
	BYTE *pixel,*pixel1,*pixel2;
	BYTE *new_pixel;
	BYTE temp;

	for(i=0;i<h-1;i++)  //��Ե������
	{
		for(j=0;j<w-1;j++)
		{
			new_pixel=new_lpBits+LineBytes*(h-1-i)+j;  //ָ��Ҫ����������ص�λ��
			pixel = lpBits + LineBytes * (h-1-i)+j;
			pixel1 = lpBits + LineBytes * (h-1-i)+j+1;
			pixel2 = lpBits + LineBytes * (h-2-i)+j;
			temp=abs(*pixel-*pixel1)+abs(*pixel-*pixel2);
			*new_pixel=(BYTE)temp;
		}
	}
	free(lpBitsInfo);
	lpBitsInfo=new_lpBitsInfo;   //����ͼ���滻 ԭͼ��
}
void FFT_Filter(int D){
	int w = lpDIB_FT->bmiHeader.biWidth;
	int h = lpDIB_FT->bmiHeader.biHeight;
	int LineBytes = (w * lpDIB_FT->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE* lpBits = (BYTE*)&lpDIB_FT->bmiColors[lpDIB_FT->bmiHeader.biClrUsed];
	
	complex<double>* origin_FD = new complex<double>[w * h];
	for(int n=0;n<w*h;n++){
		origin_FD[n]=gFD[n];
	}
	int i,j;
	double dis;
	for(i=0;i<h;i++){
		for(j=0;j<w;j++){
			dis = sqrt((i - h/2)*(i - h/2)+(j - w/2)*(j - w/2)+1);
			if(D>0)//LOW
			{
				if(dis>D)
					gFD[i*w+j]=0;
			}
			else//HIGH
			{
				if(dis<-D)
					gFD[i*w+j]=0;
			}
		}
	}
	double temp;
	BYTE* pixel;
	for(i = 0;i < h;i++)
	{
		for(j = 0; j < w;j++)
		{
			pixel = lpBits + LineBytes * (h - 1 - i) + j;
			temp = sqrt(gFD[j * h + i].real()*gFD[j * h + i].real()+
				gFD[j * h + i].imag()*gFD[j * h + i].imag())*2000;
			if(temp > 255)
				temp = 255;
			*pixel = (BYTE)(temp);
		}
	}

	IFFourier();

	delete gFD;
	gFD = origin_FD;
}
void FFT_BLPFF(int D){
	int w = lpDIB_FT->bmiHeader.biWidth;
	int h = lpDIB_FT->bmiHeader.biHeight;
	int LineBytes = (w * lpDIB_FT->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE* lpBits = (BYTE*)&lpDIB_FT->bmiColors[lpDIB_FT->bmiHeader.biClrUsed];
	
	complex<double>* origin_FD = new complex<double>[w * h];
	for(int n=0;n<w*h;n++){
		origin_FD[n]=gFD[n];
	}
	int i,j;
	double dis;
	for(i=0;i<h;i++){
		for(j=0;j<w;j++){
			dis = sqrt((i - h/2)*(i - h/2)+(j - w/2)*(j - w/2)+1);
			if(D>0)//LOW
			{
				gFD[i* h + j] *=  1/(1 + pow(dis/D,4)) ;
			}
			else//HIGH
			{
			gFD[i* h + j] *= 1 - 1/(1 + pow(dis/D,4)) ;
			}
		}
	}
	double temp;
	BYTE* pixel;
	for(i = 0;i < h;i++)
	{
		for(j = 0; j < w;j++)
		{
			pixel = lpBits + LineBytes * (h - 1 - i) + j;
			temp = sqrt(gFD[j * h + i].real()*gFD[j * h + i].real()+
				gFD[j * h + i].imag()*gFD[j * h + i].imag())*2000;
			if(temp > 255)
				temp = 255;
			*pixel = (BYTE)(temp);
		}
	}

	IFFourier();

	delete gFD;
	gFD = origin_FD;
}
void FFT_GLPFF(int D){
	int w = lpDIB_FT->bmiHeader.biWidth;
	int h = lpDIB_FT->bmiHeader.biHeight;
	int LineBytes = (w * lpDIB_FT->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE* lpBits = (BYTE*)&lpDIB_FT->bmiColors[lpDIB_FT->bmiHeader.biClrUsed];
	
	complex<double>* origin_FD = new complex<double>[w * h];
	for(int n=0;n<w*h;n++){
		origin_FD[n]=gFD[n];
	}
	int i,j;
	double dis;
	for(i=0;i<h;i++){
		for(j=0;j<w;j++){
			dis = sqrt((i - h/2)*(i - h/2)+(j - w/2)*(j - w/2)+1);
			if(D>0)//LOW
			{
				gFD[i* h + j] *=  exp(-pow(dis,2)/(2*D*D));
			}
			else//HIGH
			{
				gFD[i* h + j] *= 1 - exp(-pow(dis,2)/(2*D*D)) ;
			}
		}
	}
	double temp;
	BYTE* pixel;
	for(i = 0;i < h;i++)
	{
		for(j = 0; j < w;j++)
		{
			pixel = lpBits + LineBytes * (h - 1 - i) + j;
			temp = sqrt(gFD[j * h + i].real()*gFD[j * h + i].real()+
				gFD[j * h + i].imag()*gFD[j * h + i].imag())*2000;
			if(temp > 255)
				temp = 255;
			*pixel = (BYTE)(temp);
		}
	}

	IFFourier();

	delete gFD;
	gFD = origin_FD;
}