#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

#define FILTER_SIZE 5

using namespace cv;
using namespace std;



int main( int argc, char** argv )
{   
    //intializing clocks
    clock_t t1,t2;
    //starting timer
    t1=clock();
    if( argc != 2)
    {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }
    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    if(! image.data )
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    Mat img(Size(image.cols,image.rows),CV_8UC3);
    if(! img.data )
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    //initializing variables
    int i,j,k,l;
    int count = 0;
    double d = 0.15;//1500000000;
    //int arrayi[100000];
    //int arrayj[100000];
    int *arrayi = new int[505000];
    int *arrayj = new int[505000];


//duplicating the image into another image
for(i=0;i<img.rows-1;i++){
    for(j=0;j<img.cols-1;j++){
            img.at<cv::Vec3b>(i, j)[0] = image.at<cv::Vec3b>(i, j)[0];
            img.at<cv::Vec3b>(i, j)[1] = image.at<cv::Vec3b>(i, j)[1];
            img.at<cv::Vec3b>(i, j)[2] = image.at<cv::Vec3b>(i, j)[2];
    }
}


//finding salt and pepper noise using canberra distance
#pragma omp parallel for schedule(dynamic,100) num_threads(1000)
double d0 =0,d1=0,d2=0;
    for(i=1;i<img.rows;i++){
        for(j=1;j<img.cols;j++){

            for(k=-1;k<=1;k++){
                for(l=-1;l<=1;l++){
      d0 = d0+(abs(image.at<cv::Vec3b>(i+k, j+l)[0]-image.at<cv::Vec3b>(i, j)[0])/(abs(image.at<cv::Vec3b>(i+k, j+l)[0])+abs(image.at<cv::Vec3b>(i, j)[0])));
      d1 = d1+(abs(image.at<cv::Vec3b>(i+k, j+l)[1]-image.at<cv::Vec3b>(i, j)[1])/(abs(image.at<cv::Vec3b>(i+k, j+l)[1])+abs(image.at<cv::Vec3b>(i, j)[1])));
      d2 = d2+(abs(image.at<cv::Vec3b>(i+k, j+l)[2]-image.at<cv::Vec3b>(i, j)[2])/(abs(image.at<cv::Vec3b>(i+k, j+l)[2])+abs(image.at<cv::Vec3b>(i, j)[2])));
}
}
                    double ans = (d0+d1+d2)/27;
                    //cout<<ans<<endl;
                    //cout<<" individuals "<<d0<<" "<<d1<<" "<<d2<<" "<<endl;
                    if(ans>d){
                        arrayi[count] = i;
                        arrayj[count] = j;
                        count = count+1;
                    }
d0=d1=d2=0;


}
}

cout<<count<<endl;


//averaging the noise by using 5*5 filter
#pragma omp parallel for schedule(dynamic,100) num_threads(1000)
    for(i=0;i<count;i++){
            int sum0 = 0;
            int sum1 = 0;
            int sum2 = 0;


for(int k = -2;k<=2;k++){
    for(int l=-2;l<=2;l++){
        sum0 = sum0 + image.at<cv::Vec3b>(arrayi[i]+k, arrayj[i]+l)[0];
        sum1 = sum1 + image.at<cv::Vec3b>(arrayi[i]+k, arrayj[i]+l)[1];
        sum2 = sum2 + image.at<cv::Vec3b>(arrayi[i]+k, arrayj[i]+l)[2];

    }
}

//changing values of noise to averaged value
        img.at<cv::Vec3b>(arrayi[i], arrayj[i])[0] = (int)(sum0/pow(FILTER_SIZE,2));
        img.at<cv::Vec3b>(arrayi[i], arrayj[i])[1] = (int)(sum1/pow(FILTER_SIZE,2));
        img.at<cv::Vec3b>(arrayi[i], arrayj[i])[2] = (int)(sum2/pow(FILTER_SIZE,2));
        
        
}
//end clock
    t2 = clock();
//calculate time
    float diff ((float(t2)-float(t1))/CLOCKS_PER_SEC);
    cout<<"time taken for canberra metric with filter size 5 is: "<<diff<<" seconds"<<endl;
//output image as file
    imwrite("/home/adithya/Desktop/parallel_opencv/canberra_5.jpg",img);
    return 0;
}

