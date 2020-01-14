// include external library
#include "wifiConfig.hpp"

// library 
extern "C"
{
    #include <string.h>
}

class maincontroller
{
public:
    // Initilize 
    explicit maincontroller();
    ~maincontroller();

    void start();

private:
    wifiConfig*  m_wifiConfig;

};