
//--------------------------------------������˵����-------------------------------------------
//		����˵������OpenCV3������š�OpenCV3���鱾����ʾ������49
//		������������ˮ���floodFill�����÷�ʾ��
//		�����������ò���ϵͳ�� Windows 7 64bit
//		������������IDE�汾��Visual Studio 2010
//		������������OpenCV�汾��	3.0 beta
//		2014��11�� Created by @ǳī_ë����
//		2014��12�� Revised by @ǳī_ë����
//------------------------------------------------------------------------------------------------


//---------------------------------��ͷ�ļ��������ռ�������֡�----------------------------
//		����������������ʹ�õ�ͷ�ļ��������ռ�
//------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
using namespace cv;  


//-----------------------------------��main( )������--------------------------------------------  
//      ����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼ  
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

  char* filename = argv[2];
    
  FILE* fp = fopen(filename, "rb");
  if (!fp) {
    return 0;
  }
#if 0
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
  int size = 1280 * 720 * 3;
  char *buf = new char[size];
  fread(buf, 1, size, fp);
  fclose(fp);
  cv::Mat yuvImg(720, 1280, CV_8UC3, buf);
  cv::Mat rgbImg;
  //cv::cvtColor(yuvImg, rgbImg, CV_YUV2BGR_I420);
  //cv::cvtColor(yuvImg, rgbImg, CV_RGBA2BGRA);
  cv::imshow("720p_scale_0.5", yuvImg);
#endif
#else
  char *buf = new char[540 * 960 * 4];
  fread(buf, 1, 540 * 960 * 4, fp);
  fclose(fp);
  cv::Mat test_mat(540, 960, CV_8UC4, buf);
  cv::Mat temp2;

  //cv::cvtColor(test_mat, temp2, CV_YUV2BGRA_NV12);
  cv::imshow("test", test_mat);
#endif

#endif
  cv::waitKey(0);
	return 0;    
}  