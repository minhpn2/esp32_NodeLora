#include "maincontroller.hpp"

maincontroller::maincontroller()
{

}

maincontroller::~maincontroller()
{
    
}

void maincontroller::start()
{
    // Initilize wifi function
    this->m_wifiConfig = new wifiConfig(); 
    xTaskHandle hanleTask;
    xTaskCreatePinnedToCore(&this->taskWifiStart,
                            "taskWifi",
                            2048,
                            NULL,
                            5,
                            NULL,
                            1);
    xTaskCreatePinnedToCore(&this->taskTest,
                            "taskTesk",
                            2048,
                            NULL,
                            2,
                            NULL,
                            0);
}
#define CHIP_NAME "ESP32"

void maincontroller::taskWifiStart(void* pvParam)
{
    wifiConfig* test = (wifiConfig*)pvParam;
    test->startWifiSoftAP();
    while (1)
    {
        /* code */
        vTaskDelay(500/portTICK_RATE_MS);
    }
    
}

extern "C" void maincontroller::taskTest(void* pvParam) 
{
    // static_cast<maincontroller*>(pvParam);
    printf("Hello world!\n");

    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU cores, WiFi%s%s, ",
            CHIP_NAME,
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    for(;;)
    {
        printf("Hello World task2!\n");
        vTaskDelay(1000/portTICK_RATE_MS);
    }
}