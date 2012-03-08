#pragma once
#include"headers.h"

template<typename T=double>
class histogram{

 public:

 histogram(T);
 histogram(T,T);
 void fill(std::vector<T> &);
 void draw() const;

 protected:

 const static int resolution;  
 const T h_start;
 const T h_end;
 std::vector<T> histogram_;
};

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

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
histogram<T>::draw() const {
  
  Py_Initialize();
  
  PyRun_SimpleString("import sys");
  PyRun_SimpleString("sys.path.append(\".\")");

  PyObject *name = PyString_FromString("visualiser");
  PyObject *mod = PyImport_Import(name);
  
  if( mod ){
    PyObject *mod_dict = PyModule_GetDict(mod);
    PyObject *visualiser = PyDict_GetItemString(mod_dict,"visualiser");
    PyObject *v_instance;
    if(PyCallable_Check(visualiser)){
      v_instance = PyObject_CallObject(visualiser,NULL);
    }else{
      throw(std::runtime_error("unable to create visualiser object"));
    }
        
    PyObject *list = PyList_New(0);
    for(size_t i=0;i<histogram_.size();i++){
      
      int ret = PyList_Append(list , PyFloat_FromDouble(histogram_[i]));
      if(ret == -1) throw(std::runtime_error("bad append"));
      
    }

    assert( (int)PyList_Size(list) == (int)histogram_.size());

    PyObject_CallMethodObjArgs(v_instance,PyString_FromString("set_bins"),list,NULL);
    PyObject_CallMethodObjArgs(v_instance,PyString_FromString("set_title"),PyString_FromString("data_1"),NULL);
    PyObject_CallMethod(v_instance,"draw",NULL);
  
  }else{
    throw(std::runtime_error("could not load python visualiser module"));
  }
  Py_Finalize();
}
  

template<typename T>
void
init_histogram(const cv::Mat &im, const cv::Mat &mask, histogram<T> &hgram){




}


