/*
 * LCD.h
 *
 * Created: 7/26/2023 1:51:50 PM
 *  Author: Clbow
 */ 
#include <avr/io.h>

#define LCD_SDA_PORT PORTC4
#define LCD_SCL_PORT PORTC5
#define LCD_I2C_ADDR 0x27

#ifndef LCD_H_
#define LCD_H_

void InitLCD();

void SendCommand(int command);



#endif /* LCD_H_ */