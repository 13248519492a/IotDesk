#include "task.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "wifi.h"
#include "event_groups.h"
#include "setting.h"

static void wifi_sta_cb(wifi_status_t status)
{
    event_group_set_bit(status);
}

static void core0_task(void *parm)
{
    uint32_t bits;
    wifi_sta_init(wifi_sta_cb);
    while (1)
    {
        bits = event_group_wait_bits(WIFI_CONNECTED_BIT | WIIF_DISCONNECTED_BIT, true, false, portMAX_DELAY);
        if (bits & WIFI_CONNECTED_BIT)
        {
        }
        else if (bits & WIIF_DISCONNECTED_BIT)
        {
        }
    }
}

static void core1_task(void *parm)
{
    while (1)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void task_create(void)
{
    setting_init();
    event_group_init();

    xTaskCreatePinnedToCore(core0_task, "core0_task", 4096, NULL, 5, NULL, 0);
    xTaskCreatePinnedToCore(core1_task, "core1_task", 4096, NULL, 5, NULL, 1);
}