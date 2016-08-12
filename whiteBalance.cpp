#include "stdlib.h"
#include "iostream"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;


void findColor(const Mat &image,Mat &result, int target[]);
void combineImgs(const Mat &image, Mat &result);
void erodeImg(Mat &image);
void dilateImg(Mat &image);
void findRegionColor(Mat& result,int color,int regions[]);
void findRegionColorMain();

int main (int argc,char** argv){
	 findRegionColorMain();
	 system("pause");
	return 0;
}
 
void findColor(const Mat &image,Mat &result, int target[]){
	

	for(int i=0;i<image.rows;i++){
		for(int j=0;j<image.cols;j++){
			if(image.at<Vec3b>(i,j)[0]>=target[0] && image.at<Vec3b>(i,j)[0]<=target[1]){
				result.at<uchar>(i,j)=0;
				
			}else{
				result.at<uchar>(i,j)=255;
			}
		}
	}
}
void findEndPoints(const Mat &image, int* result){
	int count=0, x=0, y=0;
	
	for(int i=0;i<image.rows;i++){
		for(int j=0;j<image.cols;j++){
			if(image.at<uchar>(i,j)==0){
				count++;
				x+=j;
				y+=i;
			}
		}
	}
	if(count==0)return;
	result[0] = x/count;
	result[1] = y/count;

}
void combineImgs(const Mat &image, Mat &result){
	Mat mix(image.rows,image.cols,CV_8UC3);
	vector<Mat> planes;
	split(image,planes);
	planes[0]+=result*0.3;
	planes[1]+=result*0.3;
	planes[2]+=result*0.3;
	merge(planes,image);
}
void erodeImg(Mat &image){
	erode(image,image,Mat());
}
void dilateImg(Mat &image){
	dilate(image,image,Mat());
}

void findRegionColorMain(){
		int regions[8] = {0};
		for(int colorID = 1;colorID<=1;colorID++){
			Mat image = imread("1.jpg");
			if(!image.data)system("pause");
			
			Mat result(image.rows,image.cols,CV_8UC1);
			image.copyTo(result);
			cvtColor(image,image,COLOR_BGR2HSV);
			cvtColor(result,result, COLOR_BGR2GRAY);
			int vec[2];
			switch(colorID){
				case 1:vec[0] = 100;vec[1] = 110;break;
				case 2:vec[0] = 26;vec[1] = 50;break;
				case 3:vec[0] = 130;vec[1] = 160;break;
				default:vec[0] = 100;vec[1] = 124;break;
			}
			
		findColor(image,result,vec);
		imwrite("result.png",result);
		findRegionColor(result,colorID,regions);
		waitKey(1);
		}
		for(int i=0;i<8;i++){
			cout<<regions[i]<<endl;}
		
}

//check colors for different regions of the image
void findRegionColor(Mat& result,int color,int regions[]){
	for(int k=0;k<8;k++){
		int count=0;
		switch(k){
			case 0: 
				count=0;
				for(int i=0;i<result.rows/10;i++){
					for(int j=0;j<result.cols/5;j++){
						if(result.at<uchar>(i,j)==0){
							count++;count++;count++;}
						else
							count--;
					}}
				if(count>0)regions[k] = color;break;
				
			case 1: count=0;
				for(int i=0;i<result.rows/10;i++){
					for(int j=2*result.cols/5;j<3*result.cols/5;j++){
						if(result.at<uchar>(i,j)==0){
							count++;count++;count++;}
						else
							count--;
					}}break;
			case 2: count=0;
				for(int i=0;i<result.rows/10;i++){
					for(int j=4*result.cols/5;j<result.cols;j++){
						if(result.at<uchar>(i,j)==0){
							count++;count++;count++;}
						else
							count--;
					}}break;
			case 3: count=0;
				for(int i=2*result.rows/5;i<3*result.rows/5;i++){
					for(int j=0;j<result.cols/5;j++){
						if(result.at<uchar>(i,j)==0){
							count++;count++;count++;}
						else
							count--;
					}}break;
			case 4: count=0;
				for(int i=2*result.rows/5;i<3*result.rows/5;i++){
					for(int j=4*result.cols/5;j<result.cols;j++){
						if(result.at<uchar>(i,j)==0){
							count++;count++;count++;}
						else
							count--;
					}}break;
			case 5: count=0;
				for(int i=result.rows-10;i<result.rows;i++){
					for(int j=0;j<2*result.cols/5;j++){
						if(result.at<uchar>(i,j)==0){
							count++;count++;count++;}
						else
							count--;
					}}break;
			case 6: count=0;
				for(int i=result.rows-10;i<result.rows;i++){
					for(int j=2*result.cols/5;j<3*result.cols/5;j++){
						if(result.at<uchar>(i,j)==0){
							count++;count++;count++;}
						else
							count--;
					}}break;
			case 7: count=0;
				for(int i=result.rows-10;i<result.rows;i++){
					for(int j=4*result.cols/5;j<result.cols/5;j++){
						if(result.at<uchar>(i,j)==0){
							count++;count++;count++;}
						else
							count--;
					}}break;
		}
	}
}
