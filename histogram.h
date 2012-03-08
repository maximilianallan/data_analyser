#pragma once
#include"headers.h"

template<typename T=double>
class histogram{

 public:

 histogram();
 histogram(T);
 histogram(T,T);
 void fill(std::vector<T> &);
 void draw() const;
 void init();
 void end() const;

 protected:

 PyObject *visualiser;
 const static int resolution;  
 const T h_start;
 const T h_end;
 std::vector<T> histogram_;

};

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

template<typename T>
histogram<T>::histogram():h_start(0),h_end(0){

}

template<typename T>
histogram<T>::histogram(T h_end):h_start(0),h_end(h_end){
}


template<typename T>
histogram<T>::histogram(T h_start, T h_end):h_start(h_start),h_end(h_end){
}

template<typename T>
const int histogram<T>::resolution = 255;


/*
  just copy the pixels - do this with a pointer
*/

template<typename T>
void
histogram<T>::fill(std::vector<T> &pixels){
  histogram_ = pixels;
}

template<typename T>
void
histogram<T>::init() {

  std::cout << "about to init" << std::endl;
  Py_Initialize();

  std::cout << "importing sys"  << std::endl;
  PyRun_SimpleString("import sys");
  PyRun_SimpleString("sys.path.append(\".\")");

  std::cout << "importing visualiser"  << std::endl;
  PyObject *name = PyString_FromString("visualiser");
  PyObject *mod = PyImport_Import(name);
  std::cout << "imported..."  << std::endl;
  if( mod ){
    PyObject *mod_dict = PyModule_GetDict(mod);
    PyObject *visualiser_mod = PyDict_GetItemString(mod_dict,"visualiser");
    
    if(PyCallable_Check(visualiser_mod)){
      visualiser = PyObject_CallObject(visualiser_mod,NULL);
    }else{
      throw(std::runtime_error("unable to create visualiser object"));
    }
  }else{
    throw(std::runtime_error("could not load python visualiser module"));
  }
  

}

template<typename T>
void
histogram<T>::end() const {

  Py_Finalize();

}

template<typename T>
void
histogram<T>::draw() const {
  
 
  PyObject *list = PyList_New(0);
  for(size_t i=0;i<histogram_.size();i++){
      
    int ret = PyList_Append(list , PyFloat_FromDouble(histogram_[i]));
    if(ret == -1) throw(std::runtime_error("bad append"));
    
  }
  
  assert( (int)PyList_Size(list) == (int)histogram_.size());
  
  PyObject_CallMethodObjArgs(visualiser,PyString_FromString("set_bins"),list,NULL);
  PyObject_CallMethodObjArgs(visualiser,PyString_FromString("set_title"),PyString_FromString("data_1"),NULL);
  PyObject_CallMethod(visualiser,"draw",NULL);
  
}
  

template<typename T>
void
init_histogram(const cv::Mat &im, const cv::Mat &mask, histogram<T> &hgram){




}


