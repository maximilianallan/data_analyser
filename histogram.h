#pragma once
#include"headers.h"

template<typename T=double>
class histogram{

 public:
  histogram(int,T);
  histogram(int,int,T,T);
  ~histogram();

 protected:
  const int h_start;
  const int h_end;
  const T v_start;
  const T v_end;
  std::vector<T> histogram_;




};

template<typename T>
histogram<T>::histogram(int h_end, T v_end):h_start(0),h_end(h_end),v_start(0),v_end(v_end){
  
  histogram_.reverse(h_end);

}


template<typename T>
histogram<T>::histogram(int h_start, int h_end, T v_start, T v_end):h_start(h_start),h_end(h_end),v_start(v_start),v_end(v_end){

  histogram_.reverse(h_end-h_start);

}
