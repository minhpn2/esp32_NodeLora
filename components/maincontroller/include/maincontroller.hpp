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

    static void taskWifiStart(void* pvParam);
    static void taskTest(void* pvParam);

private:
    wifiConfig*  m_wifiConfig;
};