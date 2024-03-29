/*
    \file   led.h

    \brief  led header file.

    (c) 2018 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip software and any
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party
    license terms applicable to your use of third party software (including open source software) that
    may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS
    FOR A PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
    SOFTWARE.
*/


#ifndef LED_H_
#define LED_H_
#include <stdint.h>
#include <stdbool.h>
#include "definitions.h"

#define LED_ON  false
#define LED_OFF true

#define LED_YELLOW_SetHigh_EX() LED_DAT_GPIO_PA11_Set()
#define LED_GREEN_SetHigh_EX()  LED_CON_GPIO_PA20_Set()
#define LED_BLUE_SetHigh_EX()   LED_WIFI_GPIO_PA21_Set()
#define LED_RED_SetHigh_EX()    LED_ERR_GPIO_PA10_Set()

#define LED_YELLOW_SetLow_EX() LED_DAT_GPIO_PA11_Clear()
#define LED_GREEN_SetLow_EX()  LED_CON_GPIO_PA20_Clear()
#define LED_BLUE_SetLow_EX()   LED_WIFI_GPIO_PA21_Clear()
#define LED_RED_SetLow_EX()    LED_ERR_GPIO_PA10_Clear()

#define LED_YELLOW_Toggle_EX() LED_DAT_GPIO_PA11_Toggle()
#define LED_GREEN_Toggle_EX()  LED_CON_GPIO_PA20_Toggle()
#define LED_BLUE_Toggle_EX()   LED_WIFI_GPIO_PA21_Toggle()
#define LED_RED_Toggle_EX()    LED_ERR_GPIO_PA10_Toggle()

#define LED_FLAG_EMPTY 0

typedef enum
{
    LED_BLUE,
    LED_GREEN,
    LED_YELLOW,
    LED_RED
} led_number_t;

typedef union
{
    struct
    {
        uint16_t red : 1;
        uint16_t green : 1;
        uint16_t blue : 1;
        uint16_t yellow : 1;
        uint16_t reserved : 12;
    };
    uint16_t as_uint16;
} led_change_t;

typedef union
{
    struct
    {
        uint16_t red : 3;
        uint16_t green : 3;
        uint16_t blue : 3;
        uint16_t yellow : 3;
        uint16_t reserved : 6;
    };
    uint16_t as_uint16;
} led_state_t;

typedef struct led
{
    led_change_t change_flag;
    led_state_t  state_flag;
} led_status_t;

typedef enum
{
    LED_STATE_OFF        = 0,
    LED_STATE_HOLD       = (1 << 0),
    LED_STATE_BLINK_FAST = (1 << 1),
    LED_STATE_BLINK_SLOW = (1 << 2),
    LED_STAT_MAX         = INT16_MAX
} led_set_state_t;

typedef enum
{
    LED_INDICATOR_OFF     = 0,
    LED_INDICATOR_PENDING = (1 << 0),
    LED_INDICATOR_SUCCESS = (1 << 1),
    LED_INDICATOR_ERROR   = (1 << 2)
} led_indicator_name_t;

void LED_test(void);
void LED_init(void);

void LED_SetBlue(led_set_state_t newState);
void LED_SetGreen(led_set_state_t newState);
void LED_SetYellow(led_set_state_t newState);
void LED_SetRed(led_set_state_t newState);
void LED_ToggleRed(void);
void LED_SetWiFi(led_indicator_name_t state);
void LED_SetCloud(led_indicator_name_t state);

#endif /* LED_H_ */
