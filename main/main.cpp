#include "maincontroller.hpp"

extern "C" int app_main(void)
{ 
    maincontroller m_maincontroller;
    m_maincontroller.start();
    
    return 0;
}