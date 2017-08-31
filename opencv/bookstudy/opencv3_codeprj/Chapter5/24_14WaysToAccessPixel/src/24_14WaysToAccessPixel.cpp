//---------------------------------��ͷ�ļ��������ռ�������֡�-----------------------------
//		����������������ʹ�õ�ͷ�ļ��������ռ�
//-------------------------------------------------------------------------------------------------
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

//---------------------------------���궨�岿�֡�---------------------------------------------
//		����������������ʹ�ú궨��
//-------------------------------------------------------------------------------------------------
#define NTESTS 14
#define NITERATIONS 20

//----------------------------------------- ������һ��-------------------------------------------
//		˵��������.ptr �� []
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

//-----------------------------------����������-------------------------------------------------
//		˵�������� .ptr �� * ++ 
//-------------------------------------------------------------------------------------------------
void colorReduce1(Mat &image, int div = 64) {

	int nl = image.rows; //����
	int nc = image.cols * image.channels(); //ÿ��Ԫ�ص���Ԫ������

	for (int j = 0; j<nl; j++)
	{

		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i<nc; i++)
		{

			//-------------��ʼ����ÿ������-------------------

			*data++ = *data / div*div + div / 2;

			//-------------�������ش���------------------------

		} //���д������              
	}
}

//-----------------------------------------����������-------------------------------------------
//		˵��������.ptr �� * ++ �Լ�ģ����
//-------------------------------------------------------------------------------------------------
void colorReduce2(Mat &image, int div = 64) {

	int nl = image.rows; //����
	int nc = image.cols * image.channels(); //ÿ��Ԫ�ص���Ԫ������

	for (int j = 0; j<nl; j++)
	{

		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i<nc; i++)
		{

			//-------------��ʼ����ÿ������-------------------

			int v = *data;
			*data++ = v - v%div + div / 2;

			//-------------�������ش���------------------------

		} //���д������                   
	}
}

// -----------------------------------�������š� ------------------------------------------------
//		˵��������Mat_ iterator
//-------------------------------------------------------------------------------------------------
void colorReduce8(Mat &image, int div = 64) {

	//��ȡ������
	Mat_<Vec3b>::iterator it = image.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend = image.end<Vec3b>();

	for (; it != itend; ++it) {

		//-------------��ʼ����ÿ������-------------------

		(*it)[0] = (*it)[0] / div*div + div / 2;
		(*it)[1] = (*it)[1] / div*div + div / 2;
		(*it)[2] = (*it)[2] / div*div + div / 2;

		//-------------�������ش���------------------------
	}//���д������  
}

//--------------------------------------������ʮ����--------------------------------------------
//		˵�������ö�̬��ַ�������at
//-------------------------------------------------------------------------------------------------
void colorReduce11(Mat &image, int div = 64) {

	int nl = image.rows; //����
	int nc = image.cols; //����

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


//----------------------------------������ʮ����----------------------------------------------- 
//		˵��������ͼ������������
//-------------------------------------------------------------------------------------------------
void colorReduce12(const Mat &image, //����ͼ��
	Mat &result,      // ���ͼ��
	int div = 64) {
	int nl = image.rows;
	int nc = image.cols;

	int channel = image.channels();

	//׼���ó�ʼ�����Mat�����ͼ��
	result.create(image.rows, image.cols, image.type());

	//��������������ͼ��
	nc = nc*nl;
	nl = 1;

	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	//����ֵ
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

//--------------------------------------������ʮ�ġ�------------------------------------------- 
//		˵�������ò���������
//-------------------------------------------------------------------------------------------------
void colorReduce13(Mat &image, int div = 64) {

	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	//����ֵ
	uchar mask = 0xFF << n; // e.g. ����div=16, mask= 0xF0

							//����ɫ�ʻ�ԭ
	image = (image&Scalar(mask, mask, mask)) + Scalar(div / 2, div / 2, div / 2);
}

//-----------------------------------��ShowHelpText( )������-----------------------------
//		���������һЩ������Ϣ
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//�����ӭ��Ϣ��OpenCV�汾
	printf("\n\n\t\t\t�ǳ���л����OpenCV3������š�һ�飡\n");
	printf("\n\n\t\t\t��Ϊ����OpenCV3��ĵ�24������ʾ������\n");
	printf("\n\n\t\t\t   ��ǰʹ�õ�OpenCV�汾Ϊ��" CV_VERSION);
	printf("\n\n  ----------------------------------------------------------------------------\n");

	printf("\n\n���ڽ��д�ȡ���������Եȡ���\n\n");
}

//-----------------------------------��main( )������--------------------------------------------
//		����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼ
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

	//ʱ��ֵ��Ϊ0
	for (int i = 0; i<NTESTS; i++)
		t[i] = 0;


	// ����ظ�����
	int n = NITERATIONS;
	for (int k = 0; k<n; k++)
	{
		cout << k << " of " << n << endl;

		//������ʮ���� ����ͼ������������
		image1 = imread("1.png");
		tinit = getTickCount();
		Mat result;
		colorReduce12(image1, result);
		t[12] += getTickCount() - tinit;
		image2 = result;


		//------------------------------
	}
	//���ͼ��   
	imshow("ԭʼͼ��", image0);
	imshow("���", image2);
	imshow("ͼ����", image1);


	waitKey();
	return 0;
}
