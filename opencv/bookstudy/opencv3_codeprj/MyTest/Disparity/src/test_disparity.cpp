#include <iostream>
#include<string>
#include<opencv2\core\core.hpp>
#include<opencv2\calib3d\calib3d.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

void calDisparity(Mat left, Mat right, Mat & disparity);

int main()
{
  Mat display, vdisplay;

  Mat left = imread("9.png", 0);
  Mat right = imread("10.png", 0);
  calDisparity(left, right, display);

  normalize(display, vdisplay, 0, 255, CV_MINMAX);

  imshow("ÊÓ²îÍ¼", display);
  imshow("ÊÓ²îÍ¼2", vdisplay);
  waitKey(0);
  return 0;
}

void calDisparity(Mat left, Mat right, Mat & disparity)
{
  Mat _left = left;
  Mat _right = right;
  Rect leftROI, rightROI;
  cv::imshow("left", _left);
  cv::imshow("right", _right);
  cv::waitKey(0);
  cv::Ptr<cv::StereoBM> bm = cv::StereoBM::create(16, 9);
  bm->setPreFilterType(CV_STEREO_BM_XSOBEL);  //CV_STEREO_BM_NORMALIZED_RESPONSE»òÕßCV_STEREO_BM_XSOBEL
  bm->setPreFilterSize(9);
  bm->setPreFilterCap(31);
  bm->setBlockSize(15);
  bm->setMinDisparity(0);
  bm->setNumDisparities(32);//64
  bm->setTextureThreshold(10);
  bm->setUniquenessRatio(15);
  bm->setSpeckleWindowSize(100);
  bm->setSpeckleRange(32);
  bm->setDisp12MaxDiff(1);
  bm->setROI1(leftROI);
  bm->setROI2(rightROI);
  int pfs = bm->getPreFilterSize();
  int pfc = bm->getPreFilterCap();
  int bs = bm->getBlockSize();
  int md = bm->getMinDisparity();
  int nd = bm->getNumDisparities();
  int tt = bm->getTextureThreshold();
  int ur = bm->getUniquenessRatio();
  int sw = bm->getSpeckleWindowSize();
  int sr = bm->getSpeckleRange();
  int dw = bm->getDisp12MaxDiff();
#if 1
  copyMakeBorder(_left, _left, 0, 0, 80, 0, IPL_BORDER_REPLICATE);  //·ÀÖ¹ºÚ±ß
  cv::imshow("border_left", _left);
  copyMakeBorder(_right, _right, 0, 0, 80, 0, IPL_BORDER_REPLICATE);
  cv::imshow("border_right", _right);
#endif
  bm->compute(_left, _right, disparity);

  disparity = disparity.colRange(80, _left.cols);
  disparity.convertTo(disparity, CV_32F, 1.0f/16);
  cv::imshow("test", disparity);
}



















#if 0

#include <iostream>
#include <cmath>
#include <opencv2\opencv.hpp>
using namespace  cv;
using namespace std;
const int area = 50;
float compute(Mat& imgl, Mat& imgr, Mat& dstDisparity)
{
  MatConstIterator_<float> l = imgl.begin<float>();
  MatConstIterator_<float> r = imgr.begin<float>();
  float s = 0.0;
  for (; l != imgl.end<float>(); l++, r++)
  {
    s += powf(*l - *r, 2);
  }
  return s;
}
int main()
{
  Mat srcLeft = imread("C:\\Users\\16114\\Desktop\\Photoshop\\Í¼Æ¬ËØ²Ä\\·ç¾°ËØ²Ä\\9.png", 0);
  Mat srcRight = imread("C:\\Users\\16114\\Desktop\\Photoshop\\Í¼Æ¬ËØ²Ä\\·ç¾°ËØ²Ä\\10.png", 0);
  srcLeft.convertTo(srcLeft, CV_32FC1);
  srcRight.convertTo(srcRight, CV_32FC1);
  Mat dstDisparity;
  int windowsize = 5;
  int winsize = windowsize / 2;
  int mindis = 0;
  dstDisparity.create(srcLeft.size(), srcLeft.type());
  int height = srcLeft.rows;
  int width = srcLeft.cols;

  for (int i = winsize; i<height - winsize; i++)
    for (int j = winsize; j<width - winsize; j++)
    {
      int s;
      int disp = 0;
      Mat imgl = srcLeft(Rect(j - winsize, i - winsize, windowsize, windowsize));
      for (int k = 0; k<area; k++)
      {
        int d = mindis + k;
        if (j - d<winsize)
          continue;
        Mat imgr = srcRight(Rect(j - d - winsize, i - winsize, windowsize, windowsize));
        float m = compute(imgl, imgr, dstDisparity);
        if (k == 0)
          s = m;
        else if (s>m)
        {
          s = m;
          disp = d;
        }
        dstDisparity.at<float>(i, j) = disp;
      }
    }
  double min, max;
  minMaxLoc(dstDisparity, &min, &max);
  dstDisparity = (dstDisparity - min) / (max - min) * 255;

  imwrite("disparity.png", dstDisparity);
  dstDisparity = imread("disparity.png");
  dstDisparity.convertTo(dstDisparity, CV_8UC1, 255, 0);
  imshow("disparity", dstDisparity);
  waitKey(0);
  return 0;
}
#endif