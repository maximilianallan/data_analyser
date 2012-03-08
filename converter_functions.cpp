#include"converter_functions.h"

void 
rgb(cv::Mat &im){
  return;
}

/*
  convert im from rgb to hsv
*/

void 
rgb2hsv(cv::Mat &im){
  
  cv::Mat n_im(im.size(),im.type());

  cv::cvtColor(im,n_im,CV_RGB2HSV);

  im = n_im.clone();

}

/* 
   convert im from rgb to cie
*/

void 
rgb2cie(cv::Mat &im){

  cv::Mat n_im(im.size(),im.type());

  cv::cvtColor(im,n_im,CV_RGB2XYZ);
  
  im = n_im.clone();

}


void
rgb2sift(cv::Mat &im){

  cv::Mat n_im(im.size(),CV_32FC1);
  cv::Mat g_im(im.size(),CV_8UC1);
  const int rows = im.rows;
  const int cols = im.cols;

  cv::cvtColor(im,g_im,CV_RGB2GRAY);

  std::vector<cv::KeyPoint> keypoints;

  for(int r=0;r<rows;r++)
    for(int c=0;c<cols;c++)
      keypoints.push_back( cv::KeyPoint(c,r,1.f) );

  cv::SiftDescriptorExtractor ext;
  ext.compute(g_im,keypoints,n_im);

  im = n_im.clone();

}


void
rgb2norm_r(cv::Mat &im){

  const int rows = im.rows;
  const int cols = im.cols;
  const int n = im.channels();
  cv::Mat n_im(im.size(),CV_32FC1);
  unsigned char *im_data = (unsigned char *)im.data;
  float *nim_data = (float *)n_im.data;

  for(int r=0;r<rows;r++){
    for(int c=0;c<cols;c++){
      const int index = (r*cols + c)*n;
      nim_data[r*cols+c] = float(im_data[index])/
	(im_data[index] + im_data[index+1] + im_data[index+2]);
    }
  }
  
  im = n_im.clone();
    
}

void
rgb2norm_g(cv::Mat &im){

  const int rows = im.rows;
  const int cols = im.cols;
  const int n = im.channels();
  cv::Mat n_im(im.size(),CV_32FC1);
  unsigned char *im_data = (unsigned char *)im.data;
  float *nim_data = (float *)n_im.data;

  for(int r=0;r<rows;r++){
    for(int c=0;c<cols;c++){
      const int index = (r*cols + c)*n;
      nim_data[r*cols+c] = float(im_data[index+1])/
	(im_data[index] + im_data[index+1] + im_data[index+2]);
    }
  }
  
  im = n_im.clone();

}


void 
rgb2opp1(cv::Mat &im){

  const int rows = im.rows;
  const int cols = im.cols;
  const int n = im.channels();
  cv::Mat n_im(im.size(),CV_32FC1);
  unsigned char *im_data = (unsigned char *)im.data;
  float *nim_data = (float *)n_im.data;
  
  for(int r=0;r<rows;r++){
    for(int c=0;c<cols;c++){
      const int index = (r*cols + c)*n;
      nim_data[r*cols + c] = 0.5*(im_data[index] - im_data[index+1]);
    }
  }
      
}

void
rgb2opp2(cv::Mat &im){

  const int rows = im.rows;
  const int cols = im.cols;
  const int n = im.channels();
  cv::Mat n_im(im.size(),CV_32FC1);
  unsigned char *im_data = (unsigned char *)im.data;
  float *nim_data = (float *)n_im.data;
  
  for(int r=0;r<rows;r++){
    for(int c=0;c<cols;c++){
      const int index = (r*cols + c)*n;
      nim_data[r*cols + c] = 0.5*im_data[index+2] - 0.25*(im_data[index] + im_data[index+1]);
    }
  }

}



