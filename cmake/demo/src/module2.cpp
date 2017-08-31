#include "hobotlog/hobotlog.hpp"
#define MODULE_TAG "TAG"
void test_module2(){
    LOGI_T(MODULE_TAG) << "test_module2 +";
    //do something
    LOGI_T(MODULE_TAG) << "test_module2 -";
}
