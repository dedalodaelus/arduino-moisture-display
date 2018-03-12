/*
 * pin_def.h
 *
 *  Created on: 12 mar. 2018
 *      Author: dedalodaelus
 */

#define led_id LED_BUILTIN

#ifndef PIN_DEF_H_
#define PIN_DEF_H_

#define ENC_A A2
#define ENC_B A3
#define ENC_BTN 8

#define DHTTYPE DHT11   // DHT 11
#define DHTPIN 12 // what digital pin we're connected to


#define PIN_RESET 7  // LCD1 Reset
#define PIN_SCE   6  // LCD2 Chip Select
#define PIN_DC    5   // LCD3 Dat/Command
#define PIN_SDIN  4   // LCD4 Data in
#define PIN_SCLK  13   // LCD5 Clk
#define PIN_BL    9   // LCD7 Vled
              // LCD6 Vcc
              // LCD7 Vled
              // LCD8 Gnd



#endif /* PIN_DEF_H_ */
