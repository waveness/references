
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


//-----------------------------------【main( )函数】--------------------------------------------  
//      描述：控制台应用程序的入口函数，我们的程序从这里开始  
//----------------------------------------------------------------------------------------------- 
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
  if (argc < 2)
  {
    std::cout << "usage: yuv2bgr yuv420p_xx.yuv" << std::endl;
    cv::waitKey(0);
    return 0;
  }

  char* filename = argv[1];
    
  FILE* fp = fopen(filename, "rb");
  if (!fp) {
    return 0;
  }
#if 0
  char *buf = new char[720 * 1280 * 3/2];
  fread(buf, 1, 720 * 1280 * 3 / 2, fp);
  fclose(fp);
  cv::Mat yuvImg(720 * 3 / 2, 1280, CV_8UC1, buf, 1280);
  cv::Mat rgbImg;
  cv::cvtColor(yuvImg, rgbImg, cv::COLOR_YUV2BGR_I420);
  cv::Mat resizeImg;
  cv::resize(rgbImg, resizeImg, cv::Size(640, 320));
  cv::imshow("720p_scale_0.5", resizeImg);
#else
  char *buf = new char[720 * 1280];
  fread(buf, 1, 720 * 1280, fp);
  fclose(fp);
  cv::Mat yuvImg(720, 1280, CV_8UC1, buf, 1280);
  cv::Mat rgbImg;
  cv::cvtColor(yuvImg, rgbImg, cv::COLOR_GRAY2RGB);
  cv::imshow("720p_scale_0.5", rgbImg);
#endif

#endif
  cv::waitKey(0);
	return 0;    
}  