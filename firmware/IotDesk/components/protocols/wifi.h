#ifndef PROTOCOLS_WIFI_H
#define PROTOCOLS_WIFI_H

#include <stdint.h>

typedef enum
{
    WIFI_STATUS_CONNECTED,
    WIFI_STATUS_DISCONNECTED
} wifi_status_t;

typedef void (*wifi_status_callback_t)(wifi_status_t status);

/**
 * @brief 连接Wi-Fi
 * @param Wi-Fi状态回调函数
 */
void wifi_sta_init(wifi_status_callback_t cb);

const char *wifi_get_error_txt(uint8_t language);

#endif