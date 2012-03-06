#include"helper_functions.h"


void 
parse_dset(const std::string &dset, std::vector<std::pair<std::string,std::string> > &images){
  
  //get the cwd in buffer
  size_t size = 100;
  char *cwd = new char[size]; 
  
#ifdef __linux__
  
  getcwd(cwd,size);

  //cd in the dataset dir - handle errors
  int ret_val = chdir(dset.c_str()); 
  if(ret_val == ENOENT) throw std::runtime_error("could not cd into the dir " + dset);
  else if(ret_val == ENOTDIR) throw std::runtime_error(dset + " is not a dir\n");
  else if(ret_val != 0) throw std::runtime_error("error, unknown error with " + dset);

  //read the dir
  DIR *dset_dir = opendir("."); 
  if(!dset_dir) throw std::runtime_error("could not open dataset " + dset);
  

  std::string ims_dir,msk_dir;
  size_t chk_cnt = 0;
  for(;;){
    dirent *t_dir = readdir(dset_dir); //read each dir in dataset dir
    if(!t_dir) break;
    std::string sim_dir(t_dir->d_name);
    if(sim_dir.find("training") != std::string::npos){
      ims_dir = sim_dir; //find the same of the training set dir
      chk_cnt++;
    }
    if(sim_dir.find("mask") != std::string::npos){
      msk_dir = sim_dir; //find the name ogf the mask dir
      chk_cnt++;
    }
  }
  if(chk_cnt != 2) throw std::runtime_error("ambiguous filenames in " + dset + "\nneed one training dataset and one masks\n");
  get_filenames(ims_dir,msk_dir,cwd + std::string("/") + dset,images);
  
  //change process working dir back to root dir
  if(chdir(cwd)) throw std::runtime_error("error changing back to root_dir\n");
  

#elif _WIN32 || _WIN64 


#endif
  
  delete [] cwd;
  
}



void 
find_dsets(const std::string &root_dir, std::vector<std::pair<std::string,std::string> > &images){
  
#ifdef __linux__

  chdir(root_dir.c_str());
  DIR *r_dir = opendir(root_dir.c_str());
  if(!r_dir) throw std::runtime_error("could not open " + root_dir + "\n");
  
  for(;;){
    //check if dirent is a data_set and open it
    dirent *dset = readdir(r_dir);
    if(!dset) break;
    std::string dset_name(dset->d_name);
    if(dset_name.find("data") == std::string::npos) continue;
    
    //read the filenames into the files vector
    parse_dset(dset_name,images);
  }
  closedir(r_dir);
  
#elif _WIN32 || _WIN64
  
#endif
  
  
}
/*

  params: 
  im_dir - a directory for images
  msk_dir - a directory for masks
  root_dir  - the root directory containing im_dir and msk_dir
  images - vector to stick the filenames for each image and its corresponding mask 
  
*/

void
get_filenames(const std::string &im_dir, const std::string &msk_dir, const std::string &root_dir, std::vector<std::pair<std::string,std::string> > &images){

#ifdef __linux__
  
  DIR *dir = opendir(im_dir.c_str());

  for(;;){
    dirent *image = readdir(dir);
    if(!image) break;
    std::string str_image(image->d_name);
    if(str_image.find(".png") == std::string::npos && str_image.find(".jpg") == std::string::npos) continue;
    std::pair<std::string,std::string> tp(root_dir + "/" + im_dir + "/" + str_image,
				     root_dir + "/" + msk_dir + "/" + str_image);
    images.push_back(tp);
  }
  
#elif defined _WIN32 || _WIN64
  
#endif
}


void
read_ims(const std::vector<std::pair<std::string,std::string> > &files, std::vector<std::pair<cv::Mat,cv::Mat> > &images){

    std::vector<std::pair<std::string,std::string> >::const_iterator m = files.begin();
    for(;m!=files.end();m++){
      cv::Mat im = cv::imread(m->first);
      cv::Mat msk = cv::imread(m->second);
      images.push_back(std::make_pair(im,msk));
      //pair<cv::Mat,cv::Mat> tmp_pr(im,msk);
    }
          

}


