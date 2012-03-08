#include"analyser.h"
#include"helper_functions.h"

image_analyser::image_analyser(){
  images.reserve(100);
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
image_analyser::push_all(){
  std::vector<std::pair<std::string,std::string> > files;
  
  find_dsets(files); //`files` returns full pathnames for datasets in root_dir 
  read_ims(files,images); // read them into this->images

}

std::pair<cv::Mat,cv::Mat> &
image_analyser::get(const size_t n){
  if( n < 0 || n > images.size()) throw(std::out_of_range("tried to get image with bad index"));
  return images[n];
}


void
image_analyser::create_histograms() const{

  typedef void (*multi_convert)(cv::Mat &);

  std::vector<std::pair<multi_convert,std::string> > convert_functions;
  convert_functions.push_back(std::make_pair(rgb,"rgb"));
  convert_functions.push_back(std::make_pair(rgb2hsv,"hsv"));
  convert_functions.push_back(std::make_pair(rgb2cie,"cie"));
  convert_functions.push_back(std::make_pair(rgb2sift,"sift"));
  convert_functions.push_back(std::make_pair(rgb2norm_r,"normalised red"));
  convert_functions.push_back(std::make_pair(rgb2norm_g,"normalised green"));
  convert_functions.push_back(std::make_pair(rgb2opp1,"opponent 1"));
  convert_functions.push_back(std::make_pair(rgb2opp2,"opponent 2"));
  
  

  std::vector<std::pair<cv::Mat,cv::Mat> >::const_iterator m = images.begin();
  for(;m!=images.end();m++){
    std::vector<std::pair<multi_convert,std::string> >::iterator f = convert_functions.begin();
    for(;f!=convert_functions.end();f++){
      convert(*m,f->first,f->second);
    }
  }
}
