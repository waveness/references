#include "hobotlog/hobotlog.hpp"

#define MODULE_TAG "TAG"
void test_module1(){
    LOGI_T(MODULE_TAG) << "test_module1 +";
    // do something
    LOGI_T(MODULE_TAG) << "test_module1 -";
}
