//#include <opencv2/opencv.hpp>

//using namespace cv;

#if 0
#define WIDTH	1280
#define HEIGHT	720
int main(void)
{
	int wid = WIDTH;
	int hei = HEIGHT;

	FILE* fp = fopen("camera_yuv30", "rb");
	if (!fp){
		printf("file not exsit");
		return 0;
	}
	int size = WIDTH * HEIGHT * 1.5;
	char *buf = new char[size];

	fread(buf, 1, size, fp);
	fclose(fp);

	Mat mY(hei, wid, CV_8UC1, buf);

	imshow("gray", mY);
	waitKey(0);

	delete[] buf;

	return 0;
}
#endif

#if 1
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <iostream>

void uyvy_to_yuv420P(char *in, char*out, int width, int height)
{
	char *y = out;
	char *u = out + (width * height);
	char *v = out + (width * height * 5 / 4);
	size_t index_y = 0;
	size_t index_u = 0;
	size_t index_v = 0;
	size_t lane = width * 2;	// should width *2; if j < height * 2 will blurred screen
	for (size_t j = 0; j < height; j++)
	{
		size_t ww = lane * j;
		for (size_t i = 0; i < lane; i = i + 4)
		{
			*(y + (index_y++)) = *(in + ww + i + 1);
			*(y + (index_y++)) = *(in + ww + i + 3);
			if (j % 2 == 0) {
				*(u + (index_u++)) = *(in + ww + i);
				*(v + (index_v++)) = *(in + ww + i + 2);
			}
		}
	}
	return;
}

void uyvy_to_yuv420SP(char *in, char*out, int width, int height)
{
	char *y = out;
	char *uv = out + (width * height);
	size_t index_y = 0;
	size_t index_uv = 0;
	size_t lane = width * 2;	// should width *2; if j < height * 2 will blurred screen
	for (size_t j = 0; j < height; j++)
	{
		size_t ww = lane * j;
		for (size_t i = 0; i < lane; i = i + 4)
		{
			*(y + (index_y++)) = *(in + ww + i + 1);
			*(y + (index_y++)) = *(in + ww + i + 3);
			if (j % 2 == 0) {
				*(uv + (index_uv++)) = *(in + ww + i);
				*(uv + (index_uv++)) = *(in + ww + i + 2);
			}
		}
	}
	return;
}


int main() {
	FILE *fp = NULL;
	FILE *fp1 = NULL;
	const size_t uyuv_sz = 1280 * 720 * 2;
	const size_t yuv420p_sz = 1280 * 720 * 3 >> 1;
	char *pbuf = new char[uyuv_sz];
	char *outbuf = new char[yuv420p_sz];

	fp = fopen("dump_1.yuv", "r");
	if (fp == NULL) {
		return -1;
	}
	int size = fread(pbuf, 1, uyuv_sz, fp);
	if (size != uyuv_sz) {
		std::cout << "read size error, real size = " << size << std::endl;
		return -1;
	}
	uyvy_to_yuv420P(pbuf, outbuf, 1280, 720);
	fp1 = fopen("dump_22.yuv", "w");
	fwrite(outbuf, 1, yuv420p_sz, fp1);
	fclose(fp);
	fclose(fp1);
	return 0;
}

#endif
