//---------------------------------【头文件、命名空间包含部分】-----------------------------
//		描述：包含程序所使用的头文件和命名空间
//-------------------------------------------------------------------------------------------------
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

//---------------------------------【宏定义部分】---------------------------------------------
//		描述：包含程序所使用宏定义
//-------------------------------------------------------------------------------------------------
#define NTESTS 14
#define NITERATIONS 20

//----------------------------------------- 【方法一】-------------------------------------------
//		说明：利用.ptr 和 []
//-------------------------------------------------------------------------------------------------
void colorReduce0(Mat &image, int div=64) {
	int nl = image.rows;
	int nc = image.cols * image.channels();

	for (int j = 0; j < nl; j++) {
		uchar* data = image.ptr<uchar>(j);
		for (int i = 0; i < nc; i++) {
			data[i] = data[i] / div * div + div / 2;
		}
	}
}

//-----------------------------------【方法二】-------------------------------------------------
//		说明：利用 .ptr 和 * ++ 
//-------------------------------------------------------------------------------------------------
void colorReduce1(Mat &image, int div = 64) {

	int nl = image.rows; //行数
	int nc = image.cols * image.channels(); //每行元素的总元素数量

	for (int j = 0; j<nl; j++)
	{

		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i<nc; i++)
		{

			//-------------开始处理每个像素-------------------

			*data++ = *data / div*div + div / 2;

			//-------------结束像素处理------------------------

		} //单行处理结束              
	}
}

//-----------------------------------------【方法三】-------------------------------------------
//		说明：利用.ptr 和 * ++ 以及模操作
//-------------------------------------------------------------------------------------------------
void colorReduce2(Mat &image, int div = 64) {

	int nl = image.rows; //行数
	int nc = image.cols * image.channels(); //每行元素的总元素数量

	for (int j = 0; j<nl; j++)
	{

		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i<nc; i++)
		{

			//-------------开始处理每个像素-------------------

			int v = *data;
			*data++ = v - v%div + div / 2;

			//-------------结束像素处理------------------------

		} //单行处理结束                   
	}
}

// -----------------------------------【方法九】 ------------------------------------------------
//		说明：利用Mat_ iterator
//-------------------------------------------------------------------------------------------------
void colorReduce8(Mat &image, int div = 64) {

	//获取迭代器
	Mat_<Vec3b>::iterator it = image.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend = image.end<Vec3b>();

	for (; it != itend; ++it) {

		//-------------开始处理每个像素-------------------

		(*it)[0] = (*it)[0] / div*div + div / 2;
		(*it)[1] = (*it)[1] / div*div + div / 2;
		(*it)[2] = (*it)[2] / div*div + div / 2;

		//-------------结束像素处理------------------------
	}//单行处理结束  
}

//--------------------------------------【方法十二】--------------------------------------------
//		说明：利用动态地址计算配合at
//-------------------------------------------------------------------------------------------------
void colorReduce11(Mat &image, int div = 64) {

	int nl = image.rows; //行数
	int nc = image.cols; //列数

	for (int j = 0; j < nl; j++)
	{
		for (int i = 0; i < nc; i++)
		{
			image.at<Vec3b>(j, i)[0] = image.at<Vec3b>(i, i)[0] / div * div + div / 2;
			image.at<Vec3b>(j, i)[1] = image.at<Vec3b>(i, i)[1] / div * div + div / 2;
			image.at<Vec3b>(j, i)[2] = image.at<Vec3b>(i, i)[2] / div * div + div / 2;
		}
	}
}


//----------------------------------【方法十三】----------------------------------------------- 
//		说明：利用图像的输入与输出
//-------------------------------------------------------------------------------------------------
void colorReduce12(const Mat &image, //输入图像
	Mat &result,      // 输出图像
	int div = 64) {
	int nl = image.rows;
	int nc = image.cols;

	int channel = image.channels();

	//准备好初始化后的Mat给输出图像
	result.create(image.rows, image.cols, image.type());

	//创建无像素填充的图像
	nc = nc*nl;
	nl = 1;

	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	//掩码值
	uchar mask = 0xFF << n;
	for (int j = 0; j < nl; j++) {
		uchar* data = result.ptr<uchar>(j);
		const uchar* idata = image.ptr<uchar>(j);
		for (int i = 0; i < nc; i++) {
			*data++ = (*idata++)&mask + div / 2;
			*data++ = (*idata++)&mask + div / 2;
			*data++ = (*idata++)&mask + div / 2;
		}
	}
}

//--------------------------------------【方法十四】------------------------------------------- 
//		说明：利用操作符重载
//-------------------------------------------------------------------------------------------------
void colorReduce13(Mat &image, int div = 64) {

	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	//掩码值
	uchar mask = 0xFF << n; // e.g. 比如div=16, mask= 0xF0

							//进行色彩还原
	image = (image&Scalar(mask, mask, mask)) + Scalar(div / 2, div / 2, div / 2);
}

//-----------------------------------【ShowHelpText( )函数】-----------------------------
//		描述：输出一些帮助信息
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//输出欢迎信息和OpenCV版本
	printf("\n\n\t\t\t非常感谢购买《OpenCV3编程入门》一书！\n");
	printf("\n\n\t\t\t此为本书OpenCV3版的第24个配套示例程序\n");
	printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION);
	printf("\n\n  ----------------------------------------------------------------------------\n");

	printf("\n\n正在进行存取操作，请稍等……\n\n");
}

//-----------------------------------【main( )函数】--------------------------------------------
//		描述：控制台应用程序的入口函数，我们的程序从这里开始
//-------------------------------------------------------------------------------------------------
int main()
{
	int64 t[NTESTS], tinit;
	Mat image0;
	Mat image1;
	Mat image2;

	system("color 4F");

	ShowHelpText();

	image0 = imread("1.png");
	if (!image0.data)
		return 0;

	//时间值设为0
	for (int i = 0; i<NTESTS; i++)
		t[i] = 0;


	// 多次重复测试
	int n = NITERATIONS;
	for (int k = 0; k<n; k++)
	{
		cout << k << " of " << n << endl;

		//【方法十三】 利用图像的输入与输出
		image1 = imread("1.png");
		tinit = getTickCount();
		Mat result;
		colorReduce12(image1, result);
		t[12] += getTickCount() - tinit;
		image2 = result;


		//------------------------------
	}
	//输出图像   
	imshow("原始图像", image0);
	imshow("结果", image2);
	imshow("图像结果", image1);


	waitKey();
	return 0;
}
