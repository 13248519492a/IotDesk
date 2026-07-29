#include "wifi.h"
#include "esp_log.h"
#include "esp_wifi.h"

#define TAG "WIFI"

static const char *s_wifi_errors[][3] = {
    {"密码错误", "Wrong Password", "パスワードエラー"},
    {"未找到WiFi网络", "WiFi Network Not Found", "WiFiネットワークが見つかりません"},
    {"路由器拒绝", "Router Rejected", "ルーターに拒否されました"},
    {"连接设备已满", "Max Devices Reached", "接続デバイス数上限"},
    {"WiFi信号太弱", "WiFi Signal Too Weak", "WiFi電波が弱すぎます"},
    {"加密方式不兼容", "Incompatible Security", "暗号化方式が非対応です"},
};

static uint8_t s_retry_num = 0;
static uint16_t s_wifi_error_num = 0;

static void event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    wifi_status_callback_t cb = (wifi_status_callback_t)arg;

    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
    {
        ESP_LOGI(TAG, "WIFI_EVENT_STA_START");
        esp_wifi_connect();
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        const wifi_event_sta_disconnected_t *disconn = (wifi_event_sta_disconnected_t *)event_data;
        switch (disconn->reason)
        {
        case WIFI_REASON_AUTH_FAIL:
            s_wifi_error_num = 0;
            ESP_LOGE(TAG, "%s", s_wifi_errors[0][0]);
            break;
        case WIFI_REASON_NO_AP_FOUND:
            s_wifi_error_num = 1;
            ESP_LOGE(TAG, "%s", s_wifi_errors[1][0]);
            break;
        case WIFI_REASON_ASSOC_FAIL:
            s_wifi_error_num = 2;
            ESP_LOGE(TAG, "%s", s_wifi_errors[2][0]);
            break;
        case WIFI_REASON_ASSOC_TOOMANY:
            s_wifi_error_num = 3;
            ESP_LOGE(TAG, "%s", s_wifi_errors[3][0]);
            break;
        case WIFI_REASON_NO_AP_FOUND_IN_RSSI_THRESHOLD:
            s_wifi_error_num = 4;
            ESP_LOGE(TAG, "%s", s_wifi_errors[4][0]);
            break;
        case WIFI_REASON_NO_AP_FOUND_W_COMPATIBLE_SECURITY:
            s_wifi_error_num = 5;
            ESP_LOGE(TAG, "%s", s_wifi_errors[5][0]);
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
                if (cb != NULL)
                {
                    cb(WIFI_STATUS_DISCONNECTED);
                }
            }
            break;
        }
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_SCAN_DONE)
    {
        ESP_LOGI(TAG, "WIFI_EVENT_SCAN_DONE");
    }
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        ESP_LOGI(TAG, "IP_EVENT_STA_GOT_IP");
        cb(WIFI_STATUS_CONNECTED);
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
        esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, &cb, &instance_any_id));
    ESP_ERROR_CHECK(
        esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, &cb, &instance_got_ip));

    wifi_config_t wifi_cfg = {
        .sta =
            {
                .ssid = "ChinaNet-cfu6",
                .password = "6vtndlma",
                .listen_interval = 10, // DTIM信标间隔
            },
    };

    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_cfg));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "wifi_init_sta finished.");
}

const char *wifi_get_error_txt(uint8_t language)
{
    return s_wifi_errors[s_wifi_error_num][language];
}