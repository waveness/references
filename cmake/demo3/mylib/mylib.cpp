#include <stdio.h>
#include <string>
#include <mylib.h>

void lib_fun(std::string& msg){
    printf("[lib_fun]--->msg is %s\n", msg.c_str());
}
