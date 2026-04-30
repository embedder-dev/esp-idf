/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    printf("Counting to 20:\n");

    for (int i = 1; i <= 20; i++) {
        printf("%d\n", i);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    printf("Done counting!\n");
}
