set(wifi_srcs "src/wifiConfig.cpp")

idf_component_register(SRCS "${wifi_srcs}"
                       INCLUDE_DIRS "include"
                       REQUIRES nvs_flash
)