#ifndef APP_EVENT_GROUPS_H
#define APP_EVENT_GROUPS_H

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

#define WIFI_CONNECTED_BIT BIT0
#define WIIF_DISCONNECTED_BIT BIT1

/**
 * @brief 创建事件组
 */
void event_group_init(void);

/**
 * @brief 设置事件组位
 * @param uxBitsToSet 要设置的位
 * @return 返回事件组的位
 */
EventBits_t event_group_set_bit(const EventBits_t uxBitsToSet);

/**
 * @brief 清除事件组位
 * @param uxBitsToClear 要清除的位
 * @return 返回事件组的位
 */
EventBits_t event_group_clear_bit(const EventBits_t uxBitsToClear);

/**
 * @brief 等待事件组
 * @param uxBitsToWaitFor 要等待的位
 * @param xClearOnExit 是否在退出时清除位
 * @param xWaitForAllBits 是否等待所有位
 * @param xTicksToWait 等待的时间
 * @return 返回事件组的位
 */
EventBits_t event_group_wait_bits(const EventBits_t uxBitsToWaitFor, const BaseType_t xClearOnExit,
                                  const BaseType_t xWaitForAllBits, TickType_t xTicksToWait);

#endif