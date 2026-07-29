#include "setting.h"
#include "esp_log.h"

#define TAG "SETTING"

static nvs_handle_t s_nvs_handle;

void setting_init(void)
{
    ESP_LOGI(TAG, "nvs init");

    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_LOGI(TAG, "nvs init done");
}

esp_err_t setting_load_i8(const char *key, int8_t *out_value)
{
    esp_err_t ret = nvs_open("storage", NVS_READWRITE, &s_nvs_handle);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Error (%s) opening NVS handle!", esp_err_to_name(ret));
        return ret;
    }

    ret = nvs_get_i8(s_nvs_handle, key, out_value);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Error (%s) reading!", esp_err_to_name(ret));
    }

    nvs_close(s_nvs_handle);

    return ret;
}

esp_err_t setting_load_i16(const char *key, int16_t *out_value)
{
    esp_err_t ret = nvs_open("storage", NVS_READWRITE, &s_nvs_handle);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Error (%s) opening NVS handle!", esp_err_to_name(ret));
        return ret;
    }

    ret = nvs_get_i16(s_nvs_handle, key, out_value);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Error (%s) reading!", esp_err_to_name(ret));
    }

    nvs_close(s_nvs_handle);

    return ret;
}

esp_err_t setting_load_i32(const char *key, int32_t *out_value)
{
    esp_err_t ret = nvs_open("storage", NVS_READWRITE, &s_nvs_handle);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Error (%s) opening NVS handle!", esp_err_to_name(ret));
        return ret;
    }

    ret = nvs_get_i32(s_nvs_handle, key, out_value);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Error (%s) reading!", esp_err_to_name(ret));
    }

    nvs_close(s_nvs_handle);

    return ret;
}

esp_err_t setting_load_u8(const char *key, uint8_t *out_value)
{
    esp_err_t ret = nvs_open("storage", NVS_READWRITE, &s_nvs_handle);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Error (%s) opening NVS handle!", esp_err_to_name(ret));
        return ret;
    }

    ret = nvs_get_u8(s_nvs_handle, key, out_value);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Error (%s) reading!", esp_err_to_name(ret));
    }

    nvs_close(s_nvs_handle);

    return ret;
}

esp_err_t setting_load_u16(const char *key, uint16_t *out_value)
{
    esp_err_t ret = nvs_open("storage", NVS_READWRITE, &s_nvs_handle);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Error (%s) opening NVS handle!", esp_err_to_name(ret));
        return ret;
    }

    ret = nvs_get_u16(s_nvs_handle, key, out_value);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Error (%s) reading!", esp_err_to_name(ret));
    }

    nvs_close(s_nvs_handle);

    return ret;
}

esp_err_t setting_load_u32(const char *key, uint32_t *out_value)
{
    esp_err_t ret = nvs_open("storage", NVS_READWRITE, &s_nvs_handle);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Error (%s) opening NVS handle!", esp_err_to_name(ret));
        return ret;
    }

    ret = nvs_get_u32(s_nvs_handle, key, out_value);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Error (%s) reading!", esp_err_to_name(ret));
    }

    nvs_close(s_nvs_handle);

    return ret;
}