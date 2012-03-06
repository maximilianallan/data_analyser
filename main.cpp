#include"analyser.h"
#include<boost/gil/gil_all.hpp>


int main(int argc, char **argv){

  std::string root_dir;
  if(argc > 1){
    char * rl_path = realpath(argv[1],NULL);
    //std::vector<std::string> args(argv+1,argv+argc);
    root_dir = rl_path;
    free(rl_path);
  }else{
    size_t size = 100;
    char *cwd = new char[size];
#ifdef __linux__
    getcwd(cwd,size);
    root_dir = cwd;
    
#elif defined _WIN32 || _WIN64
    
    
#endif
  }

  image_analyser ia;
  ia.push_all(root_dir);
  return 0;

}
