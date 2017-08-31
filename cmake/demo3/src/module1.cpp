#include "mylib.h"
#include <iostream>

//void __declspec(dllimport) lib_fun(std::string& msg);

void test_module1(){
    std::cout << "test_module1 +" << std::endl;
    // do something
    std::string str = "call from module1";
    lib_fun(str);
    std::cout << "test_module1 -" << std::endl;
}
