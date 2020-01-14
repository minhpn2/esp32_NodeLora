#include "wifiConfig.hpp"

wifiConfig::wifiConfig()
{
    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_LOGI(this->TAG, "ESP_WIFI_MODE_AP");

    printf(this->TAG);
    this->wifi_init_softap();    
}

wifiConfig::~wifiConfig()
{
    // do_nothing
}


void wifiConfig::wifi_event_handler(void* event_handler_arg, 
                                    esp_event_base_t event_base, 
                                    int32_t event_id, 
                                    void* event_data)
{
    // wifiConfig* m_wifiConfig = (wifiConfig*)event_handler_arg;

    if(event_id == WIFI_EVENT_AP_STACONNECTED)
    {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        ESP_LOGI("wifi softAP", "station " MACSTR " join, AID=%d",
                 MAC2STR(event->mac), event->aid);
    }

    else if(event_id == WIFI_EVENT_AP_STADISCONNECTED)
    {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        ESP_LOGI("wifi softAP", "station " MACSTR " leave, AID=%d",
                MAC2STR(event->mac), event->aid);
    }
}


void wifiConfig::wifi_init_softap(void)
{
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifiConfig::wifi_event_handler, this));

    wifi_config_t wifi_setting = {};
    strcpy((char*)wifi_setting.ap.ssid, ESP_WIFI_SSID);
    strcpy((char*)wifi_setting.ap.password, ESP_WIFI_PASS);
    wifi_setting.ap.ssid_len = strlen(ESP_WIFI_SSID);
    wifi_setting.ap.max_connection = MAX_STA_CONN;
    wifi_setting.ap.authmode = WIFI_AUTH_WPA_WPA2_PSK;

    if (strlen(ESP_WIFI_PASS) == 0) {
        wifi_setting.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_setting));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(this->TAG, "wifi_init_softap finished. SSID:%s password:%s",
             ESP_WIFI_SSID, ESP_WIFI_PASS);
}