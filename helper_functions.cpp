#include"helper_functions.h"
#include"histogram.h"

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
find_dsets(std::vector<std::pair<std::string,std::string> > &images){
  
#ifdef __linux__

  DIR *r_dir = opendir(".");
  
  for(;;){
    //check if dirent is a data_set and open it
    dirent *dset = readdir(r_dir);
    if(!dset) break;
    std::string dset_name(dset->d_name);
    if(dset_name.find("data") == std::string::npos) continue;
    if(images.size() > 5) break;
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
    }
          

}

void 
convert(const std::pair<cv::Mat,cv::Mat> &ims, void (*multi_convert)(cv::Mat &), const std::string &heading){

  cv::Mat n_im = ims.first.clone();
  //convert image with conversion function
  multi_convert(n_im);
    
  std::vector<std::vector<double> > c1_pix_vals;
  std::vector<std::vector<double> > c2_pix_vals;  

  //create the inverse bitmask for the background
  cv::Mat not_im = ~ims.second;
  prepare_data(n_im,ims.second,c1_pix_vals);  
  prepare_data(n_im,not_im,c2_pix_vals);

  //create the historgrams for background and forground for each colour channel
  for(int n=0;n<n_im.channels();n++){

    histogram<> c1_histogram(*max_element(c1_pix_vals[n].begin(),c1_pix_vals[n].end()));
    c1_histogram.fill(c1_pix_vals[n]);
    c1_histogram.draw();

    histogram<> c2_histogram(*max_element(c2_pix_vals[n].begin(),c2_pix_vals[n].end()));
    c2_histogram.fill(c2_pix_vals[n]);    
    c2_histogram.draw();
  }


}

/* 
   pushes pixels (of either uchar,float or double) into vector of pix_vals according to bitmask
*/

void prepare_data(const cv::Mat &im, const cv::Mat &msk, std::vector<std::vector<double> > & pix_vals){

  const int rows = im.rows;
  const int cols = im.cols;
  const int chans = im.channels();
  const size_t elem_size = im.elemSize1();
  unsigned char *msk_ptr = (unsigned char *)msk.data;
  unsigned char *im_ptr = (unsigned char *)im.data;

  //create the vectors for each colour channel
  for(int i=0;i<chans;i++){
    std::vector<double> tmp;
    pix_vals.push_back(tmp);
  }
  
  for(int r=0;r<rows;r++){
    for(int c=0;c<cols;c++){

      int index = (r*cols + c)*chans;
      const bool msk_val = msk_ptr[index] ==  (unsigned char)255;
      index *= elem_size;

      //is pixel true in bitmask?
      if(msk_val){
	
	//for each colour channel
	for(int n=0;n<chans;n++){
	  
	  //copy the pixel data according to element size
	  void *data = malloc(elem_size*sizeof(char));
	  memcpy( data,&im_ptr[index+n],elem_size);
	  
	  if(elem_size == sizeof(char)){
	    unsigned char tmp = *(unsigned char *)data;
	    pix_vals[n].push_back( (double)tmp );
	  }

	  if(elem_size == sizeof(float)){
	    float tmp = *(float *)data;
	    pix_vals[n].push_back( (double)tmp);
	  }

	  if(elem_size == sizeof(double)){
	    pix_vals[n].push_back(*(double *)data);
	  }

	  free(data);
	}
      }
    }
  }
}
			


