
#include "stdlib.h"
#include "iostream"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void salt(Mat &image,int n);
void colorReduce(Mat &image,int div);
void sharpen(const Mat &image, Mat &result);
void sharpen2D(const Mat &image, Mat &result);

int main (int argc,char** argv){

	/*
	Mat is the basic data structure to store matrix data such as images.
	It by default to be initialized to the size of 0, but we can also determine it.
	cv::Mat ima(240,320,CV_8U,cv::Scalar(100);
	CV_8U represents 8 bits unsigned data. For colored images, we need CV_8UC3. 3 for three colors. 
	Note: like many objects, assign one obj to another variable only assign the reference. To get a complete new copy, use img.copyTo(Mat imgNew).
	*/


	//initialize an image
	cv::Mat image;
	cout<<"Image height: "<<image.size().height <<" Image width: "<< image.size().width<<endl;
	//read an img to Mat image
		cout<<image.cols;
	image = imread("1.jpg");
		cout<<image.cols;
	if(!image.data)return -1;//return -1 if it can't be opened

	//initialize a new window
	namedWindow("image");
	

	Mat result;
	sharpen(image, result);
	imwrite("img.png",result);
	imshow("image",result);
	waitKey(0);

	return 0;
}

//CAUTION: use Vec3b for 3-channels color imgs!!!
void sharpen(const Mat &image, Mat &result){
	result.create(image.size(),image.type());
	for(int i = 1;i<image.rows-1;i++){ 
		for(int j=1;j<(image.cols-1);j++){
			//previous row
			int previousB = image.at<Vec3b>(i-1,j)[0];
			int previousG = image.at<Vec3b>(i-1,j)[1];
			int previousR = image.at<Vec3b>(i-1,j)[2];
			//current row
			int currentB = image.at<Vec3b>(i,j)[0];
			int currentG = image.at<Vec3b>(i,j)[1];
			int currentR = image.at<Vec3b>(i,j)[2];
			//previous column
			int currentBP = image.at<Vec3b>(i,j-1)[0];
			int currentGP = image.at<Vec3b>(i,j-1)[1];
			int currentRP = image.at<Vec3b>(i,j-1)[2];
			//next column
			int currentBN = image.at<Vec3b>(i,j+1)[0];
			int currentGN = image.at<Vec3b>(i,j+1)[1];
			int currentRN = image.at<Vec3b>(i,j+1)[2];
			//next row
			int nextB = image.at<Vec3b>(i+1,j)[0];
			int nextG = image.at<Vec3b>(i+1,j)[1];
			int nextR = image.at<Vec3b>(i+1,j)[2];

			//saturate_cast<uchar> is used to cut off all numbers that go over the range,
			//	say any neg number become 0 and any number over 255 become 255.
			//	float numbers become closest int numbers.
			result.at<Vec3b>(i,j)[0] = (saturate_cast<uchar>)(5*currentB-previousB-nextB-currentBP-currentBN);
			result.at<Vec3b>(i,j)[1] = (saturate_cast<uchar>)(5*currentG-previousG-nextG-currentGP-currentGN);
			result.at<Vec3b>(i,j)[2] = (saturate_cast<uchar>)(5*currentR-previousR-nextR-currentRP-currentRN);
		}
	}
	//use Scalar(0,0,0) for 3-channels img
	result.row(0).setTo(Scalar(0,0,0));
	result.row(result.rows-1).setTo(Scalar(0,0,0));
	result.col(0).setTo(Scalar(0,0,0));
	result.col(result.cols-1).setTo(Scalar(0,0,0));
}
void sharpen2D(const Mat &image,Mat &result){
	//define the kernel matrix.
	Mat kernel(3,3,CV_8S,Scalar(0));
	kernel.at<uchar>(1,1)=5;
	kernel.at<uchar>(0,1)=kernel.at<uchar>(2,1)=kernel.at<uchar>(1,2)=kernel.at<uchar>(1,0)=-1;
	//filter the image with kernel then outputs result.
	filter2D(image,result,image.depth(),kernel);
}
