#include"analyser.h"
#include<boost/gil/gil_all.hpp>


int main(int argc, char **argv){

  std::string root_dir;
  std::string home_dir; 
  
#ifdef __linux__
  size_t size = 100;
  char *cwd = new char[size];
  getcwd(cwd,size);
  home_dir = cwd;
  delete [] cwd;
#elif defined _WIN32 || _WIN64
#endif
  
  
  if(argc > 1){
#ifdef __linux__
    char * rl_path = realpath(argv[1],NULL);
    root_dir = rl_path;
    free(rl_path);
#elif defined _WIN32 || _WIN64
#endif
  }else{
    root_dir = home_dir;
  }

  image_analyser ia;
  
#ifdef __linux__
  chdir(root_dir.c_str());
#elif defined _WIN32 || _WIN64
#endif

  ia.push_all();

#ifdef __linux__
  chdir(home_dir.c_str());
#elif defined _WIN32 || _WIN64
#endif

  ia.create_histograms();
  return 0;

}
