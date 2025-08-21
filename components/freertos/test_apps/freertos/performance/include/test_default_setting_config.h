/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
/*
 * Default target test framework settings for ESP-IDF Unity-based tests.
 * Platforms can override by providing test_setting_config.h per test
 * when configTARGET_TEST_USE_CUSTOM_SETTING == 1.
 */

#pragma once

#ifndef testRUN_TEST_CASE_FUNCTION
#define testRUN_TEST_CASE_FUNCTION( fxn )    RUN_TEST( fxn )
#endif

#ifndef testBEGIN_FUNCTION
#define testBEGIN_FUNCTION    UNITY_BEGIN
#endif

#ifndef testEND_FUNCTION
#define testEND_FUNCTION      UNITY_END
#endif

#ifndef testSETUP_FUNCTION_PROTOTYPE
#define testSETUP_FUNCTION_PROTOTYPE( fxn )   void fxn( void )
#endif

#ifndef testTEARDOWN_FUNCTION_PROTOTYPE
#define testTEARDOWN_FUNCTION_PROTOTYPE( fxn )   void fxn( void )
#endif

#ifndef testENTRY_FUNCTION_PROTOTYPE
#define testENTRY_FUNCTION_PROTOTYPE( fxn )   void fxn( void )
#endif
