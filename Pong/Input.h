/*
 * Input.h
 *
 * Created: 7/25/2023 11:46:20 AM
 *  Author: Clbow
 */ 

#define BUTTON_PORTS				PINC
#define FIRST_BUTTON_PIN_LOCATION	0x08
#define SECOND_BUTTON_PIN_LOCATION	0x04
#define THIRD_BUTTON_PIN_LOCATION	0x02
#define FOURTH_BUTTON_PIN_LOCATION	0x01

#include <stdbool.h>

#ifndef INPUT_H_
#define INPUT_H_

typedef struct Player 
{
	bool upFlag;
	bool downFlag;
	float xPos;
	float yPos;
	unsigned char score;
}Player_t;

void InitInputs(struct Player *player);

void PollInputs(struct Player *player);

void CheckInputs(struct Player *player);

void ExecuteInputs(struct Player *player, float deltaTime);


#endif /* INPUT_H_ */