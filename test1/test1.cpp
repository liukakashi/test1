// test1.cpp: 定义控制台应用程序的入口点。
//



#include "stdafx.h"


#include <stdio.h>
#include <stdlib.h>
#include <cv.h>
#include <core\core.hpp>
#include <highgui.h>
#include <features2d\features2d.hpp>
#include <vector>

using namespace std;
using namespace cv;


int main()
{

	IplImage *img1 = cvLoadImage("C:\\Users\\Administrator\\Desktop\\Image X\\119-2.BMP", -1);


	int height = img1->height;
	int width = img1->width;
	int step = img1->widthStep;
	char *data = img1->imageData;

	IplImage *img2 = cvCreateImage(cvGetSize(img1), 8, 1);
	char *data2 = img2->imageData;
	IplImage *img3 = cvCreateImage(cvGetSize(img1), 8, 1);
	char *data3 = img3->imageData;
	IplImage *img4 = cvCreateImage(cvGetSize(img1), 8, 1);
	char *data4 = img4->imageData;
	IplImage *img5 = cvCreateImage(cvGetSize(img1), 8, 1);
	char *data5 = img5->imageData;

	int data6[256 * 256];
	uchar x, y, m, n;
	for (int i = 0; i < height; i++)
	{

		for (int j = 0; j < width; j++)
		{

			data2[i*width + j] = ((int)data[i*width + j]) + 1;
			data3[i*width + j] = ((int)data[i*width + j]) + 1;
			data4[i*width + j] = ((int)data[i*width + j]) + 1;
			data5[i*width + j] = ((int)data[i*width + j]) + 1;
			data6[i*width + j] = (int)data3[i*width + j];


		}
	}
	//使用data2作为程序中的图像数据
	//预留出data3、data4、data5作为三次遍历的数据存储空间
	for (x = 1; x<height - 1; x++)//data3作为处理项//纵坐标
		for (y = 1; y < width - 1; y++)//横坐标
		{
			m = height - 1 - x;
			n = width - 1 - y;
			if (data3[x * width + y] == 0)
			{
				data3[x * width + y] = 0;
			}
			else {
				/*m = MIN(data3[(x - 1) * width + (y + 1)], data3[(x - 1) * width + y]);
				n = MIN(data3[(x - 1) * width + (y - 1)], data3[x * width + (y - 1)]);
				data3[x * width + y] = MIN(m, n)+1;*/
				data3[x * width + y] = MIN(MIN(data3[(x - 1) * width + (y + 1)], data3[(x - 1) * width + y]), MIN(data3[(x - 1) * width + (y - 1)], data3[x * width + (y - 1)])) + 1;
			}
			if (data4[m*width + n] == 0)
			{
				data4[m * width + n] = 0;
			}
			else {
				data4[m * width + n] = MIN(MIN(data4[(m + 1) * width + (n + 1)], data4[(m + 1) * width + n]), MIN(data4[(m + 1) * width + (n - 1)], data4[m * width + (n + 1)])) + 1;
			}
		}
	for (x = 1; x<height - 1; x++)
		for (y = 1; y < width - 1; y++)
		{
			data5[x * width + y] = MIN(data3[x * width + y], data4[x * width + y]);
		}
	for (x = 1; x<height - 1; x++)
		for (y = 1; y < width - 1; y++)
		{
			m = MAX(MAX(MAX(MAX(data5[(x - 1) * width + (y - 1)], data5[(x - 1) * width + y]),
				MAX(data5[(x - 1) * width + (y + 1)], data5[x * width + (y - 1)])),
				MAX(MAX(data5[x * width + (y + 1)], data5[(x + 1) * width + (y - 1)]),
					MAX(data5[(x + 1) * width + y], data5[(x + 1) * width + (y + 1)]))), data5[x*width + y]);
			if (data5[x * width + y] == m)
			{

				data2[x * width + y] = data5[x * width + y];

			}
			else {

				data2[x * width + y] = 0;
			}
		}
	for (int i = 0; i < height; i++)
	{

		for (int j = 0; j < width; j++)
		{
			data2[i * width + j] = data2[i * width + j] - 1;
			data3[i * width + j] = data3[i * width + j] - 1;
			data4[i * width + j] = data4[i * width + j] - 1;
			data5[i * width + j] = data5[i * width + j] - 1;

		}
	}






	printf("\nwidth is %d,height is %d.step is %d", width, height, step);
	cvReleaseImage(&img1);

	cvNamedWindow("img2", CV_WINDOW_NORMAL);
	cvNamedWindow("img3", CV_WINDOW_NORMAL);
	cvNamedWindow("img4", CV_WINDOW_NORMAL);
	cvNamedWindow("img5", CV_WINDOW_NORMAL);
	cvShowImage("img2", img2);
	cvShowImage("img3", img3);
	cvShowImage("img4", img4);
	cvShowImage("img5", img5);
	cvWaitKey(0);
	cvDestroyWindow("img2");
	cvDestroyWindow("img3");
	cvDestroyWindow("img4");
	cvDestroyWindow("img5");
	cvReleaseImage(&img2);
	cvReleaseImage(&img3);
	cvReleaseImage(&img4);
	cvReleaseImage(&img5);

	getchar();




	return 0;
}


