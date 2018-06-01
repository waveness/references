#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{

  //////////////////Demo1(3ά����)///////////////////////////////////////////  
  printf("//////////////////////Demo1(3ά����)////////////////////////\n");
  //��������������(�У���),ȷ����һ����  
  //��һ�����ν�ά�Ĺ���  
  //8,10������棬5���棬�����������  
  int matSize[] = { 5,8,10 };//ÿһάԪ�صĸ�����8���У�10����  
  Mat mat1(3, matSize, CV_16UC3, Scalar::all(0));

  //��step[i]�Ĵ�С:ÿһάԪ�صĴ�С(��λ�ֽ�)  
  printf("\n///////step[i]�Ĵ�С//////////\n");
  printf("step[0]:%d\n", mat1.step[0]);//480����Ĵ�С(��һά)  
  printf("step[1]:%d\n", mat1.step[1]);//60���ߵĴ�С(�ڶ�ά)  
  printf("step[2]:%d\n", mat1.step[2]);//6����Ĵ�С(����ά)  

                                       //��size[i]��ÿһάԪ�صĸ���  
  printf("\n///////size[i]�Ĵ�С///////\n");
  printf("size[0]:%d\n", mat1.size[0]);//5����  
  printf("size[1]:%d\n", mat1.size[1]);//8����  
  printf("size[2]:%d\n", mat1.size[2]);//10����  

                                       //��step1(i)��ÿһάԪ�ص�ͨ����  
  printf("\n///////step1(i)�Ĵ�С///////\n");
  printf("step1(0):%d\n", mat1.step1(0));//240:��  
  printf("step1(1):%d\n", mat1.step1(1));//30:��  
  printf("step1(2):%d\n", mat1.step1(2));//3:��  

                                         //��elemSize��ÿ��Ԫ�صĴ�С(��λ�ֽ�)  
  printf("\n///////elemSize�Ĵ�С///////\n");
  printf("elemSize:%d\n", mat1.elemSize());//6��ÿ��Ԫ�صĴ�С  

                                           //��elemSize1��ÿ��ͨ���Ĵ�С(��λ�ֽ�)  
  printf("\n///////elemSize1�Ĵ�С///////\n");
  printf("elemSize1:%d\n", mat1.elemSize1());//2��ÿ��ͨ���Ĵ�С  

  getchar();
  return 0;
}