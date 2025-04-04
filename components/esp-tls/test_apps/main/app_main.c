/*
 * SPDX-FileCopyrightText: 2021-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "unity.h"
#include "mbedtls/aes.h"
#include "memory_checks.h"
#include "soc/soc_caps.h"
#if SOC_SHA_SUPPORT_PARALLEL_ENG
#include "sha/sha_parallel_engine.h"
#else
#include "sha/sha_core.h"
#endif
#include "esp_newlib.h"

#if SOC_SHA_SUPPORT_SHA512
#define SHA_TYPE SHA2_512
#else
#define SHA_TYPE SHA2_256
#endif //SOC_SHA_SUPPORT_SHA512

/* setUp runs before every test */
void setUp(void)
{
#if SOC_SHA_SUPPORTED
    // Execute esp_sha operation to allocate internal SHA semaphore (in case of ESP32)
    // and initial DMA setup memory which is considered as leaked otherwise
    const uint8_t input_buffer[64] = {0};
    uint8_t output_buffer[64];
    esp_sha(SHA_TYPE, input_buffer, sizeof(input_buffer), output_buffer);
#endif // SOC_SHA_SUPPORTED

#if SOC_AES_SUPPORTED
    // Execute mbedtls_aes_init operation to allocate AES interrupt
    // allocation memory which is considered as leak otherwise
    const uint8_t plaintext[16] = {0};
    uint8_t ciphertext[16];
    const uint8_t key[16] = { 0 };
    mbedtls_aes_context ctx;
    mbedtls_aes_init(&ctx);
    mbedtls_aes_setkey_enc(&ctx, key, 128);
    mbedtls_aes_crypt_ecb(&ctx, MBEDTLS_AES_ENCRYPT, plaintext, ciphertext);
    mbedtls_aes_free(&ctx);
#endif // SOC_AES_SUPPORTED

    test_utils_record_free_mem();
    TEST_ESP_OK(test_utils_set_leak_level(0, ESP_LEAK_TYPE_CRITICAL, ESP_COMP_LEAK_GENERAL));
    TEST_ESP_OK(test_utils_set_leak_level(0, ESP_LEAK_TYPE_WARNING, ESP_COMP_LEAK_GENERAL));

}

/* tearDown runs after every test */
void tearDown(void)
{
    /* some FreeRTOS stuff is cleaned up by idle task */
    vTaskDelay(5);

    /* clean up some of the newlib's lazy allocations */
    esp_reent_cleanup();

    /* check if unit test has caused heap corruption in any heap */
    TEST_ASSERT_MESSAGE( heap_caps_check_integrity(MALLOC_CAP_INVALID, true), "The test has corrupted the heap");

    test_utils_finish_and_evaluate_leaks(test_utils_get_leak_level(ESP_LEAK_TYPE_WARNING, ESP_COMP_LEAK_ALL),
            test_utils_get_leak_level(ESP_LEAK_TYPE_CRITICAL, ESP_COMP_LEAK_ALL));

}

void app_main(void)
{
    unity_run_menu();
}
