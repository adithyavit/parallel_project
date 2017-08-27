#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

#define FILTER_SIZE 7

using namespace cv;
using namespace std;
/*
int avg, sum0, sum1, sum2, k, l;
int mean_filterB(int r,int c,int i,int j,){
for(k = 0;k<r+i;k++){
for(l = 0;l<c+j;l++){
sum0 = sum0+image.at<cv::Vec3b>(k, l)[0];
}
}
avg0 = (int)(sum0/FILTER_SIZE^2);
return avg0;
}
*/
int main( int argc, char** argv )
{   
    clock_t t1,t2;
    t1=clock();
    if( argc != 2)
    {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }
    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    //Mat gray;
    
    //cvtColor(image, gray, CV_BGR2GRAY);
    if(! image.data )
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    //namedWindow( "Display window", WINDOW_AUTOSIZE );
    //imshow( "Display window", image );
    //waitKey(0);
    //buffer = image;
    Mat img(Size(image.cols,image.rows),CV_8UC3);
    //fastNlMeansDenoisingColored(image, img,3000,3,7,21);
    if(! img.data )
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    cout<<img.rows<<endl;
    cout<<img.cols<<endl;
    int i,j,k,l;

    //int k = (int)(image.at<cv::Vec3b>(i, j)[0] + image.at<cv::Vec3b>(i-1, j-1)[0])/2;
    //cout<<k<<endl;
    //img[0:100] = (0,0,255);
    cout<<pow(3,2)<<endl;
    #pragma omp parallel for schedule(dynamic,100) num_threads(2)
    for(i=FILTER_SIZE-2;i<img.rows-FILTER_SIZE+2;i++){
        for(j=FILTER_SIZE-2;j<img.cols-FILTER_SIZE+2;j++){
            int sum0 = 0;
            int sum1 = 0;
            int sum2 = 0;
            //img.at<uchar>(i, j) = cv::Scalar(155,0,0);
            //img.at<cv::Vec3b>(i, j)[0] = (int)((image.at<cv::Vec3b>(i, j+1)[0] + image.at<cv::Vec3b>(i+1, j+1)[0]+image.at<cv::Vec3b>(i-1, j)[0]+image.at<cv::Vec3b>(i, j)[0]+image.at<cv::Vec3b>(i+1, j)[0]+image.at<cv::Vec3b>(i-1, j-1)[0]+image.at<cv::Vec3b>(i, j-1)[0]+image.at<cv::Vec3b>(i+1, j-1)[0]+image.at<cv::Vec3b>(i-1, j+1)[0])/9);
            //img.at<cv::Vec3b>(i, j)[1] = (int)((image.at<cv::Vec3b>(i, j+1)[1] + image.at<cv::Vec3b>(i+1, j+1)[1]+image.at<cv::Vec3b>(i-1, j)[1]+image.at<cv::Vec3b>(i, j)[1]+image.at<cv::Vec3b>(i+1, j)[1]+image.at<cv::Vec3b>(i-1, j-1)[1]+image.at<cv::Vec3b>(i, j-1)[1]+image.at<cv::Vec3b>(i+1, j-1)[1])/9);
            //img.at<cv::Vec3b>(i, j)[2] = (int)((image.at<cv::Vec3b>(i, j+1)[2] + image.at<cv::Vec3b>(i+1, j+1)[2]+image.at<cv::Vec3b>(i-1, j)[2]+image.at<cv::Vec3b>(i, j)[2]+image.at<cv::Vec3b>(i+1, j)[2]+image.at<cv::Vec3b>(i-1, j-1)[2]+image.at<cv::Vec3b>(i, j-1)[2]+image.at<cv::Vec3b>(i+1, j-1)[2]+image.at<cv::Vec3b>(i-1, j+1)[2])/9);
        //i-FILTER_SIZE+3;        
        for(k = i-FILTER_SIZE/2;k<=i+FILTER_SIZE/2;k++){
        for(l = j-FILTER_SIZE/2;l<=j+FILTER_SIZE/2;l++){
                
        sum0 = sum0+image.at<cv::Vec3b>(k, l)[0];
        sum1 = sum1+image.at<cv::Vec3b>(k, l)[1];
        sum2 = sum2+image.at<cv::Vec3b>(k, l)[2];
        }
        }
        img.at<cv::Vec3b>(i, j)[0] = (int)(sum0/pow(FILTER_SIZE,2));
        img.at<cv::Vec3b>(i, j)[1] = (int)(sum1/pow(FILTER_SIZE,2));
        img.at<cv::Vec3b>(i, j)[2] = (int)(sum2/pow(FILTER_SIZE,2));
        
}
        }
    
    t2 = clock();
    float diff ((float(t2)-float(t1))/CLOCKS_PER_SEC);
    cout<<"time taken is: "<<diff<<" seconds"<<endl;
    imwrite("/home/adithya/Desktop/parallel_opencv/denoised_house.jpg",img);
    //namedWindow( "Display window2", WINDOW_AUTOSIZE );
    //imshow( "Display window2", img );
    //waitKey(0);
    return 0;
}
