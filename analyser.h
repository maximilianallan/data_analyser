#pragma once
#include"headers.h"
#include"histogram.h"
#include"converter_functions.h"

class image_analyser{

 public:
  image_analyser();
  ~image_analyser();
  
  void push(const cv::Mat &, const cv::Mat &);
  void push(const std::string &, const std::string &);
  void push(const std::pair<cv::Mat,cv::Mat> &);
  void push_all();

  std::pair<cv::Mat,cv::Mat> &get(const size_t);
  void create_histograms() const;
  




 protected:
  std::vector<std::pair<cv::Mat,cv::Mat> > images;


};
