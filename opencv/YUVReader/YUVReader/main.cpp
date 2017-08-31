#include <opencv2/opencv.hpp>

using namespace cv;

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