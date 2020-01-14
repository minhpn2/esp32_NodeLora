/*----------------------------------------------------------------------------/
/ WIFI_CONFIG - Wifi include file               (C)ChaN, 2019
/----------------------------------------------------------------------------*/
#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sys.h"

/* The examples use WiFi configuration that you can set via project configuration menu.

   If you'd rather not, just change the below entries to strings with
   the config you want - ie #define EXAMPLE_WIFI_SSID "mywifissid"
*/

#define ESP_WIFI_SSID      "NODE_LORA_1"
#define ESP_WIFI_PASS      "lorawan1"
#define MAX_STA_CONN        4

class wifiConfig 
{
public:
    /* Initilize wifi */
    explicit wifiConfig();
    ~wifiConfig();

    /* Handle wifi event */
    static void wifi_event_handler(void* event_handler_arg, 
                                   esp_event_base_t event_base, 
                                   int32_t event_id, 
                                   void* event_data);

    /* Configure wifi softap mode */
    void wifi_init_softap(void);

private:
    const char *TAG = "wifi softAP";
};

#endif //WIFI_CONFIG_H