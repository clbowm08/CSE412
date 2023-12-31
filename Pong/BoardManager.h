/*
 * BoardManager.h
 *
 * Created: 7/28/2023 10:29:37 AM
 *  Author: Clbow
 */ 
#include <avr/io.h>

#ifndef BOARDMANAGER_H_
#define BOARDMANAGER_H_

void ResetBoard(struct Player *player);

void UpdateBoard(struct Player *player,struct Ball *ball);

void DetectUpdateScore(struct Player *player,struct Ball *ball, char *resetDeltaTime);
#endif /* BOARDMANAGER_H_ */