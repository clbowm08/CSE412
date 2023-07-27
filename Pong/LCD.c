
#define F_CPU 16000000UL

#include "LCD.h"
#include <util/delay.h>
#define ADDRESS 0x27
#define BACKLIGHT_VALUE 0x08
#define ENABLE 4

void InitLCD()
{	
	DDRC |= (0 << DDRC4);
	DDRC |= (0 << DDRC5);
	
	PORTC |= (1 << LCD_SDA_PORT);
	PORTC |= (1 << LCD_SCL_PORT);

    // Calculate the closest TWBR value based on the desired bit rate and prescaler
    // The closest prescaler for 100 kHz is 16, so we'll use that

    // Set the TWBR value and prescaler bits in the TWCR register
    TWBR0 = 72;
    TWSR0 = (0 << TWPS1) | (0 << TWPS0); // Set prescaler to 16

    // Enable TWI
    TWCR0 = (1 << TWEN);
	
	ExpanderWrite(BACKLIGHT_VALUE);

	Write4Bits(0x03 >> 4); // Initialization for 4-bit mode (First time)
	_delay_us(4500);      // Wait for 5ms

	Write4Bits(0x30 >> 4); // Initialization for 4-bit mode (First time)
	_delay_us(4500);      // Wait for 5ms

	Write4Bits(0x30 >> 4); // Initialization for 4-bit mode (Third time)
	_delay_us(150);    // Wait for 150us

	Write4Bits(0x20 >> 4); // Initialization for 4-bit mode (Final time, sets 4-bit mode)
	
	SendCommand(0x38);	//Two line make cursor
	SendCommand(0x34);	//Two Line no cursor
	SendCommand(0x08);		//4 line, with cursor
	SendCommand(0x0F);
	SendCommand(0x02);
	SendCommand(0x06);
	SendCommand(0x14);
	SendData(0x41);
}

void SendCommand(uint8_t command)
{
	Write4Bits(command & 0xF0);
	Write4Bits((command << 4) & 0xF0);
}

void Write4Bits(uint8_t value)
{
	ExpanderWrite(value);
	PulseEnable(value);
}

void ExpanderWrite(uint8_t value)
{
	BeginTransmisson(ADDRESS);
	
	// Send the data
	TWDR0 = (value | BACKLIGHT_VALUE);
	TWCR0 = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR0 & (1 << TWINT)));
	
	EndTransmisson();
}

void BeginTransmisson(uint8_t address)
{
	// Start condition
	TWCR0 = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (!(TWCR0 & (1 << TWINT)));

	// Send I2C address with write bit (R/W = 0)
	TWDR0 = LCD_I2C_ADDR << 1;
	TWCR0 = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR0 & (1 << TWINT)));
}

void EndTransmisson()
{
	    // Generate I2C stop condition
	    TWCR0 = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
	    _delay_us(100); // Wait for the stop condition to complete
}

void PulseEnable(uint8_t value)
{
	ExpanderWrite(value | ENABLE);
	_delay_us(1);
	
	ExpanderWrite(value & ~ENABLE);
	_delay_us(50);
}

void DisplayCursor(uint8_t* displayControl)
{
	*displayControl |= 0x02;
	SendCommand(*displayControl | 0x08);
}

void SendData(uint8_t value)
{
	Write4Bits((value & 0xF0) | 0x01);
	Write4Bits(((value << 4) & 0xF0) | 0x01);
}