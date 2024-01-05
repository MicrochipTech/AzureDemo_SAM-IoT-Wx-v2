
/*
    \file   mqtt_exchange_buffer.h

    \brief  MQTT buffer handling header file.

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

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct
{
    uint8_t* start;
    uint8_t* currentLocation;
    uint16_t bufferLength;
    uint16_t dataLength;
} exchangeBuffer;


typedef struct
{
    exchangeBuffer txbuff;
    exchangeBuffer rxbuff;
} mqttBuffers;


bool     MQTT_ExchangeBufferInit(exchangeBuffer* buffer);
uint16_t MQTT_ExchangeBufferPeek(exchangeBuffer* buffer, uint8_t* data, uint16_t length);
uint16_t MQTT_ExchangeBufferWrite(exchangeBuffer* buffer, uint8_t* data, uint16_t length);
uint16_t MQTT_ExchangeBufferRead(exchangeBuffer* buffer, uint8_t* data, uint16_t length);