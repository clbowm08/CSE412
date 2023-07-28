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

void Write4Bits(uint8_t value);

void ExpanderWrite(uint8_t value);

void BeginTransmisson(uint8_t address);

void WriteData(uint8_t data);

void EndTransmisson();

void PulseEnable(uint8_t value);

void SendCommand(uint8_t command);

void DisplayCursor(uint8_t* displayControl);

void SendData(uint8_t value);

void SetCursorPosition(uint8_t xCoord, uint8_t yCoord);

#endif /* LCD_H_ */