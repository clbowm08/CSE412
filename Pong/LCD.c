
#define F_CPU 16000000UL

#include "LCD.h"
#include <util/delay.h>

void InitLCD()
{
	TWCR0 |= (1 << TWEN);
	
	PORTC |= (1 << LCD_SDA_PORT);
	PORTC |= (1 << LCD_SCL_PORT);
	
	uint32_t desired_bit_rate = 100000UL; // 100 kHz

    // Calculate the closest TWBR value based on the desired bit rate and prescaler
    // The closest prescaler for 100 kHz is 16, so we'll use that
    uint32_t prescaler = 16;
    uint8_t twbr_value = (F_CPU / (2 * desired_bit_rate * prescaler)) - 8;

    // Set the TWBR value and prescaler bits in the TWCR register
    TWBR0 = twbr_value;
    TWSR0 = (0 << TWPS1) | (1 << TWPS0); // Set prescaler to 16

    // Enable TWI
    TWCR0 = (1 << TWEN);
}

void SendCommand(int command)
{
	// Start condition
	TWCR0 = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (!(TWCR0 & (1 << TWINT)));
	
    TWDR0 = (LCD_I2C_ADDR << 1);
    TWCR0 = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR0 & (1 << TWINT)));
	
	TWDR0 = 0x00;
	TWCR0 = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR0 & (1 << TWINT)));
	
	TWDR0 = command;
	TWCR0 = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR0 & (1 << TWINT)));
	
	TWCR0 = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
	_delay_us(100); // Wait for the stop condition to complete
}