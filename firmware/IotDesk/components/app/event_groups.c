#include "event_groups.h"
#include "esp_log.h"

#define TAG "EVENT_GROUPS"

static EventGroupHandle_t s_event_group = NULL;

void event_group_init(void)
{
    if (s_event_group == NULL)
    {
        s_event_group = xEventGroupCreate();
        if (s_event_group == NULL)
        {
            ESP_LOGE(TAG, "Failed to create event group");
        }
    }
}

EventBits_t event_group_set_bit(const EventBits_t uxBitsToSet)
{
    if (xPortInIsrContext()) // 判断是否在中断里
    {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        EventBits_t bits = xEventGroupSetBitsFromISR(s_event_group, uxBitsToSet, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        return bits;
    }
    else
    {
        return xEventGroupSetBits(s_event_group, uxBitsToSet);
    }
}

EventBits_t event_group_clear_bit(const EventBits_t uxBitsToClear)
{
    if (xPortInIsrContext())
    {
        return xEventGroupClearBitsFromISR(s_event_group, uxBitsToClear);
    }
    else
    {
        return xEventGroupClearBits(s_event_group, uxBitsToClear);
    }
}

EventBits_t event_group_wait_bits(const EventBits_t uxBitsToWaitFor, const BaseType_t xClearOnExit,
                                  const BaseType_t xWaitForAllBits, TickType_t xTicksToWait)
{
    return xEventGroupWaitBits(s_event_group, uxBitsToWaitFor, xClearOnExit, xWaitForAllBits, xTicksToWait);
}