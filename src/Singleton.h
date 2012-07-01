#pragma once

template<class T>
class CSingleton
{
public:
  static T* get() { 
    if ( NULL == _pInstance){
      _pInstance = new T;
    }
    return _pInstance;
  }
  
  static void destroy(){
    if ( _pInstance){
      delete _pInstance;
    }
    _pInstance = NULL;
  }
  
  virtual ~CSingleton(){
  }
  
protected:
  CSingleton(){}
  
private:    
  CSingleton(const CSingleton&){}
  
private:
  static T *_pInstance;
};

template <typename T>
T *CSingleton<T>::_pInstance = NULL;