#include "wifi.h"
#include "esp_log.h"
#include "esp_wifi.h"

#define TAG "WIFI"

void wifi_sta_init(void)
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
}