#ifndef APP_SETTING_H
#define APP_SETTING_H

#include "nvs_flash.h"

void setting_init(void);
esp_err_t setting_load_i8(const char *key, int8_t *out_value);
esp_err_t setting_load_i16(const char *key, int16_t *out_value);
esp_err_t setting_load_i32(const char *key, int32_t *out_value);
esp_err_t setting_load_u8(const char *key, uint8_t *out_value);
esp_err_t setting_load_u16(const char *key, uint16_t *out_value);
esp_err_t setting_load_u32(const char *key, uint32_t *out_value);

#endif