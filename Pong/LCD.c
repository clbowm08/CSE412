
#define F_CPU 16000000UL

#include "LCD.h"
#include <util/delay.h>

void InitLCD()
{	
	DDRC |= (0 << DDRC4);
	DDRC |= (0 << DDRC5);
	
	PORTC |= (1 << LCD_SDA_PORT);
	PORTC |= (1 << LCD_SCL_PORT);
	
    uint32_t desired_bit_rate = 100000UL; // 100 kHz

    // CPU clock frequency (assuming it's running at 16 MHz)
    uint32_t cpu_clock = 16000000UL;

    // Calculate the closest TWBR value based on the desired bit rate and prescaler
    // The closest prescaler for 100 kHz is 16, so we'll use that
    uint32_t prescaler = 16;
    uint8_t twbr_value = (cpu_clock / (2 * desired_bit_rate * prescaler)) - 8;

    // Set the TWBR value and prescaler bits in the TWCR register
    TWBR0 = twbr_value;
    TWSR0 = (0 << TWPS1) | (1 << TWPS0); // Set prescaler to 16

    // Enable TWI
    TWCR0 = (1 << TWEN);

    // Initialization sequence for I2C LCD2004
    SendCommand(0x33); // Initialization for 4-bit mode
    SendCommand(0x32); // Initialization for 4-bit mode

    // Function Set: 4-bit data length, 2-line display, 5x8 dots font
    SendCommand(0x28);

    // Display ON/OFF Control: Display ON, Cursor OFF, Blinking OFF
    SendCommand(0x0C);

    // Clear Display
    SendCommand(0x01);
    _delay_ms(2); // Wait for >1.64ms

    // Entry Mode Set: Increment cursor, No display shift
    SendCommand(0x06);

    _delay_ms(50); // Wait for initialization to complete
}

void SendCommand(unsigned short command)
{
    // Start condition
	TWCR0 = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);	while (!(TWCR0 & (1 << TWINT)));

    // Send I2C address with write bit (R/W = 0)
    TWDR0 = LCD_I2C_ADDR << 1;
    TWCR0 = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR0 & (1 << TWINT)));

    // Send control byte (command indication)
    TWDR0 = 0x00; // Control byte: Register select (RS=0), R/W=0 (Write mode)
    TWCR0 = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR0 & (1 << TWINT)));

    // Send the command
    TWDR0 = command;
    TWCR0 = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR0 & (1 << TWINT)));

    // Generate I2C stop condition
    TWCR0 = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    _delay_us(100); // Wait for the stop condition to complete
}

void SendData(unsigned short data)
{
    // Start condition
    TWCR0 = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR0 & (1 << TWINT)));

    // Send I2C address with write bit (R/W = 0)
    TWDR0 = LCD_I2C_ADDR << 1;
    TWCR0 = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR0 & (1 << TWINT)));

    // Send control byte (data indication)
    TWDR0 = 0x40; // Control byte: Register select (RS=1), R/W=0 (Write mode)
    TWCR0 = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR0 & (1 << TWINT)));

    // Send the data
    TWDR0 = data;
    TWCR0 = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR0 & (1 << TWINT)));

    // Generate I2C stop condition
    TWCR0 = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    _delay_us(100); // Wait for the stop condition to complete
}