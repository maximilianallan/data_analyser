#pragma once
#include"headers.h"
#include"histogram.h"

class image_analyser{

 public:
  image_analyser();
  ~image_analyser();
  
  void push(const cv::Mat &, const cv::Mat &);
  void push(const std::string &, const std::string &);
  void push(const std::pair<cv::Mat,cv::Mat> &);
  void push_all(const std::string &);

  std::pair<cv::Mat,cv::Mat> &get(const size_t);
  
  




 protected:
  std::vector<std::pair<cv::Mat,cv::Mat> > images;


};
