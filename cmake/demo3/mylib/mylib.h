#ifndef __MY_LIB__H__
#define __MY_LIB__H__
#include <string>

#if defined (_WIN32) 
  #if defined(mylib_EXPORTS)
  #define MYLIB_EXPORT __declspec(dllexport)
  #else
  #define MYLIB_EXPORT __declspec(dllimport)
  #endif
#else
  #define MYLIB_EXPORT
#endif
 
void MYLIB_EXPORT lib_fun(std::string& msg);

#endif
