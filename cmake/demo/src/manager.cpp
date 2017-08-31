#include "hobotlog/hobotlog.hpp"
#include "config.h"
#include "module1.h"
#include "module2.h"

#define MODULE_TAG "Manager"

void init(){
    LOGI_T(MODULE_TAG) << "manager init+";
    LogTimestamps(true);
    SetLogLevelVar(static_cast<rtc::LoggingSeverity >(2));
    //do something
    LOGI_T(MODULE_TAG) << "VERSION is" << DEMO_VERSION_MAJOR << ":" << DEMO_VERSION_MINOR;
    LOGI_T(MODULE_TAG) << "manager init-";
}

void start(){
    LOGI_T(MODULE_TAG) << "manager start+";
    test_module1();
    test_module2();
    LOGI_T(MODULE_TAG) << "manager start-";
}

void stop(){
    LOGI_T(MODULE_TAG) << "manager stop+";
    //do something
#ifdef TEST_CMAKE_DEFINE
    LOGI_T(MODULE_TAG) << "You define MACRO TEST_CMAKE_DEFINE in CMakeLists.txt";
#endif
    LOGI_T(MODULE_TAG) << "manager stop-";
}
void release(){
    LOGI_T(MODULE_TAG) << "manager release+";
    //do something
    LOGI_T(MODULE_TAG) << "manager release-";
}
