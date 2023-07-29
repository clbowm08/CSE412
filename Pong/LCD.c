
#define F_CPU 16000000UL

#include "LCD.h"
#include <util/delay.h>
#define ADDRESS 0x27
#define BACKLIGHT_VALUE 0x08
#define ENABLE 4
#define DDRAM_PRESCALER 0x80

uint8_t ball[8] = {0b00000,0b01110,0b11111,0b11111,0b11111,0b01110,0b00000,0b00000};
char left_wall[8]={0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10};
char right_wall[8]={0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01};


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
	
	SendCommand(0x28);
	SendCommand(0x0C);
	CreateCustomChar(0x04,ball);
	CreateCustomChar(0x02,left_wall);
	CreateCustomChar(0x03,right_wall);
	SendCommand(0x01);
	SendCommand(0x02);
	SendCommand(0x06);
	SendCommand(0x0C);
}

void SendCommand(uint8_t command)
{
	Write4Bits(command & 0xF0);
	Write4Bits((command << 4) & 0xF0);
	_delay_ms(1);
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
	_delay_ms(1);
}
void CreateCustomChar(uint8_t location, uint8_t charmap[]){
	
	for(int i=0; i<8; i++){
		SendCommand(0x40|((location&0x07)<<3)+i);
		SendData(charmap[i]&0b00011111);
	}
}

void SetCursorPosition(uint8_t xCoord, uint8_t yCoord)
{
	/*SendCommand(0x02);
	uint8_t createdAddress = 0;
	
	switch (yCoord)
	{
		case 2:
		yCoord = 3;
		break;
		case 3:
		yCoord = 2;
		break;
		default:
		break;
	}

	for (int i = yCoord; i > 1; i--)
	{
		createdAddress += 20;
	}
	createdAddress += xCoord;
	for (int i = 0; i <= createdAddress; i++)
	{
		SendCommand(0x14);
	}*/
	uint8_t coordset = xCoord-1;
	switch(yCoord){
		case 1:
		coordset +=0;
		break;
		case 2:
		coordset +=0x40;
		break;
		case 3:
		coordset +=0x14;
		break;
		case 4:
		coordset +=0x54;
		break;
	}
	SendCommand(coordset | DDRAM_PRESCALER);

	//createdAddress += xCoord;
	//
	//SendCommand(createdAddress | DDRAM_PRESCALER);
}