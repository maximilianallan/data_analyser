#include"analyser.h"
#include"helper_functions.h"

image_analyser::image_analyser(){

  images.reserve(10);

}


image_analyser::~image_analyser(){


}

void
image_analyser::push(const cv::Mat &im, const cv::Mat &msk){
  images.push_back(std::make_pair(im,msk));
}

void
image_analyser::push(const std::string &filename, const std::string &maskname){
  images.push_back(std::make_pair(cv::imread(filename),cv::imread(maskname)));
}

void 
image_analyser::push(const std::pair<cv::Mat,cv::Mat> &im_pair){
  images.push_back(im_pair);
}

void
image_analyser::push_all(const std::string &root_dir){

  std::vector<std::pair<std::string,std::string> > files;
  
  find_dsets(root_dir,files); //`files` returns full pathnames for datasets in root_dir 
  read_ims(files,images); // read them into this->images

}

std::pair<cv::Mat,cv::Mat> &
image_analyser::get(const size_t n){
  
  return images[n];

}
