
//--------------------------------------【程序说明】-------------------------------------------
//		程序说明：《OpenCV3编程入门》OpenCV3版书本配套示例程序49
//		程序描述：漫水填充floodFill函数用法示例
//		开发测试所用操作系统： Windows 7 64bit
//		开发测试所用IDE版本：Visual Studio 2010
//		开发测试所用OpenCV版本：	3.0 beta
//		2014年11月 Created by @浅墨_毛星云
//		2014年12月 Revised by @浅墨_毛星云
//------------------------------------------------------------------------------------------------


//---------------------------------【头文件、命名空间包含部分】----------------------------
//		描述：包含程序所使用的头文件和命名空间
//------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
using namespace cv;  

#define WIDTH	1280
#define HEIGHT	720
//-----------------------------------【main( )函数】--------------------------------------------  
//      描述：控制台应用程序的入口函数，我们的程序从这里开始  
//----------------------------------------------------------------------------------------------- 
#if 0
int main(int argc, char* argv[])
{  

#if 0
  cv::Mat srcImg = cv::imread("LDW_83021.jpeg");
  cv::Mat yuv;
  cv::cvtColor(srcImg, yuv, cv::COLOR_BGR2YUV_I420);
  int size = yuv.size().area();

  FILE* fp = fopen("mytest.yuv", "wb");
  fwrite(yuv.data, size, 1, fp);
  fclose(fp);
#else
  if (argc < 1)
  {
    std::cout << "usage: yuv2bgr yuv420p_xx.yuv" << std::endl;
    cv::waitKey(0);
    return 0;
  }
  int wid = WIDTH;
  int hei = HEIGHT;

  FILE* fp = fopen("E:\\Works\\Exercise\\opencv\\bookstudy\\opencv3_codeprj\\MyTest\\ResizeYUV420\\camera_yuv30", "rb");
  if (!fp) {
	  printf("file not exsit\n");
	  return 0;
  }
  int size = WIDTH * HEIGHT * 1.5;
  char *buf = new char[size];

  fread(buf, 1, size, fp);
  fclose(fp);

  Mat mY(hei*1.5, wid, CV_8UC1, buf);
  Mat dst;
  cv::Mat show1;
  cv::cvtColor(mY, show1, cv::COLOR_YUV2BGR_NV21);
  cv::imshow("origin", show1);

  cv::Mat show2;
  resize(show1, show2, cv::Size(640, 360));

  cv::imshow("origin_resize", show2);
  cv::waitKey(0);

  // start resize yuv420sp directly
  char *y_ptr = buf;
  char *uv_ptr = buf + WIDTH * HEIGHT;
  cv::Mat y_mat(hei, wid, CV_8UC1, y_ptr);
  cv::Mat uv_mat(hei / 2, wid / 2, CV_8UC2, uv_ptr);
  char* rz_buf = new char[640 * 360 * 1.5];
  char* rz_y_ptr = rz_buf;
  char* rz_uv_ptr = rz_buf + 640 * 360;
  cv::Mat y_rz(360, 640, CV_8UC1, rz_y_ptr);
  cv::Mat uv_rz(360 / 2, 640 / 2, CV_8UC2, rz_uv_ptr);
  cv::resize(y_mat, y_rz, cv::Size(640, 360));
  cv::resize(uv_mat, uv_rz, cv::Size(640/2, 360/2));

  cv::Mat yuv420sp(360*1.5, 640, CV_8UC1, rz_buf);
  cv:Mat show;
  cv::cvtColor(yuv420sp, show, cv::COLOR_YUV2BGR_NV21);
  cv::imshow("resize yuv", show);
  cv::waitKey(0);

  delete[] buf;
#endif
  return 0;
}  
#else
int main(int argc, char* argv[])
{
	if (argc < 1)
	{
		std::cout << "usage: yuv2bgr yuv420p_xx.yuv" << std::endl;
		cv::waitKey(0);
		return 0;
	}
	int wid = 640;
	int hei = 320;

	FILE* fp = fopen("E:\\dump_half_yb", "rb");
	if (!fp) {
		printf("file not exsit\n");
		return 0;
	}
	int size = wid * hei;
	char *buf = new char[size];

	fread(buf, 1, size, fp);
	fclose(fp);

	Mat mY(hei, wid, CV_8UC1, buf);
	cv::imshow("origin", mY);
	cv::waitKey(0);
	return 0;
}
#endif