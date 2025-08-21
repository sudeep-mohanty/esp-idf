/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
/*
 * ESP-IDF target test framework mapping for lock_contention_end_to_end test.
 * Maps the generic test macros to Unity/IDF constructs.
 */

#pragma once

/* Required headers for this test */
#include "sdkconfig.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "esp_cpu.h"
#include "unity.h"

/* Test-specific configuration macros */
#define portTEST_GET_TIME()    ( ( UBaseType_t ) esp_cpu_get_cycle_count() )
#define portTEST_NUM_SAMPLES    128
#define portTEST_NUM_ITEMS      64

/* Test framework macro mappings */
#define testRUN_TEST_CASE_FUNCTION( x )    x()

#define testBEGIN_FUNCTION               setup_idf
#define testEND_FUNCTION                 teardown_idf

#define testSETUP_FUNCTION_PROTOTYPE( fxn ) static void fxn( void )
#define testTEARDOWN_FUNCTION_PROTOTYPE( fxn ) static void fxn( void )
#define testENTRY_FUNCTION_PROTOTYPE( fxn ) TEST_CASE( "Test Performance: Lock Contention End To End", "[freertos]" )
