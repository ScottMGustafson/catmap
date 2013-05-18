/*
  a simple program exhibitng Arnold's Cat Map.

  written by Scott Gustafson
  email: s1gustaf@gmail.com
*/
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

void show(Mat img){
//show the new image
  int delay = 250;   //the delay time (in ms) before new image is shown
  namedWindow("cat", CV_WINDOW_AUTOSIZE);
  imshow("cat", img);
  waitKey(delay);
  return;
}

Mat catmap(Mat oldimg){
//perform the mapping
  int i,j,x,y,newX,newY;
  Mat newimg;
  oldimg.copyTo(newimg);
  int n = oldimg.rows;
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      newX = (j+2*i)%n;
      newY = (i+j)%n;
      newimg.at<Vec3b>(newX,newY) = oldimg.at<Vec3b>(i,j);   
    }
  }
  oldimg.release();
  return(newimg);
}

bool squareImage(Mat img){
//test for square image.  
  if(img.rows==img.cols){
    return true;
  }else{
    std::cout<<"critical error: need square image"<<std::endl;
    return false;
  }
}

int main(){
  int iter;
  Mat img = imread("cat.jpg");
  int maxIter = 3*img.cols;    //max number of iterations.

  show(img);
  for(iter=0;iter<maxIter;iter++){
    if (!squareImage(img)){
      return 0;  
    }
    catmap(img).copyTo(img);
    show(img);
  }

  return 0;
}



