#pragma once
#include"headers.h"

void parse_dset(const std::string &, std::vector<std::pair<std::string,std::string> > &);
void find_dsets(const std::string &, std::vector<std::pair<std::string,std::string> > &);
void read_ims(const std::vector<std::pair<std::string,std::string> > &, std::vector<std::pair<cv::Mat,cv::Mat> >&);
void get_filenames(const std::string &, const std::string &, const std::string &, std::vector<std::pair<std::string,std::string> > &);
