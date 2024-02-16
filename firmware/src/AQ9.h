/* 
 * File:   AQ9.h
 * Author: M43098
 *
 * Created on January 5, 2024, 5:45 PM
 */

#ifndef AQ9_H
#define	AQ9_H

#ifdef	__cplusplus
extern "C" {
#endif


// 7-bit I2C Address for ENS160 air quality sensor. 0x52 if address select jumper on 
// AQ9 Click board on default position, 0x53 otherwise
#define ENS160_I2C_ADDRESS  0x52

#define ENS160_REG_ID 0x00
#define ENS160_ID_VALUE 0x0160

#define ENS160_REG_OPMODE 0x10

#define ENS160_OPMODE_DEEPSLEEP 0x00
#define ENS160_OPMODE_IDLE 0x01
#define ENS160_OPMODE_ACTIVE 0x02
    
#define ENS160_REG_INT_CONFIG 0x11
#define ENS160_REG_COMMAND 0x12

#define ENS160_REG_TEMP_IN 0x13
#define ENS160_REG_RH_IN 0x15
    
#define ENS160_REG_STATUS 0x20

#define ENS160_REG_AQI 0x21
#define ENS160_REG_TVOC 0x22
#define ENS160_REG_ECO2 0x24
    

#ifdef	__cplusplus
}
#endif

#endif	/* AQ9_H */

