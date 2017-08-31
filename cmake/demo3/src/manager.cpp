#include "config.h"
#include "module1.h"
#include "module2.h"
#include <iostream>

void init(){
    std::cout << "manager init+" << std::endl;
    //do something
    std::cout << "VERSION is" << DEMO_VERSION_MAJOR << ":" << DEMO_VERSION_MINOR << std::endl;
    std::cout << "manager init-" << std::endl;
}

void start(){
    std::cout << "manager start+" << std::endl;
    test_module1();
    test_module2();
    std::cout << "manager start-" << std::endl;
}

void stop(){
  std::cout << "manager stop+" << std::endl;
    //do something
#ifdef TEST_CMAKE_DEFINE
  std::cout << "You define MACRO TEST_CMAKE_DEFINE in CMakeLists.txt" << std::endl;
#endif
  std::cout << "manager stop-" << std::endl;
}
void release(){
  std::cout << "manager release+" << std::endl;
    //do something
  std::cout << "manager release-" << std::endl;
}
