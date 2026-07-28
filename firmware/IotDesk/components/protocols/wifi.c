#include "wifi.h"
#include "esp_log.h"
#include "esp_wifi.h"

#define TAG "WIFI"

static uint8_t s_retry_num = 0;

static void event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
    {
        ESP_LOGI(TAG, "WIFI_EVENT_STA_START");
        esp_wifi_connect();
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        wifi_event_sta_disconnected_t *disconn = (wifi_event_sta_disconnected_t *)event_data;
        switch (disconn->reason)
        {
        case WIFI_REASON_AUTH_FAIL:
            ESP_LOGE(TAG, "密码错误");
            break;
        case WIFI_REASON_NO_AP_FOUND:
            ESP_LOGE(TAG, "未找到WiFi网络");
            break;
        case WIFI_REASON_ASSOC_FAIL:
            ESP_LOGE(TAG, "路由器拒绝");
            break;
        case WIFI_REASON_ASSOC_TOOMANY:
            ESP_LOGE(TAG, "路由器连接设备已满");
            break;
        case WIFI_REASON_NO_AP_FOUND_IN_RSSI_THRESHOLD:
            ESP_LOGE(TAG, "WiFi信号太弱");
            break;
        case WIFI_REASON_NO_AP_FOUND_W_COMPATIBLE_SECURITY:
            ESP_LOGE(TAG, "加密方式不兼容");
            break;
        case WIFI_REASON_STA_LEAVING:
        case WIFI_REASON_ASSOC_LEAVE:
        case WIFI_REASON_AUTH_LEAVE:
            ESP_LOGI(TAG, "主动断开");
            break;
        default:
            if (s_retry_num < 5)
            {
                s_retry_num++;
                esp_wifi_connect();
            }
            else
            {
                s_retry_num = 0;
                ESP_LOGE(TAG, "WiFi sta disconnected");
            }
            break;
        }
    }
}

void wifi_sta_init(wifi_status_callback_t cb)
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(
        esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL, &instance_any_id));
    ESP_ERROR_CHECK(
        esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL, &instance_got_ip));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "wifi_init_sta finished.");
}