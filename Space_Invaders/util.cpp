#include "util.h"
#include "graphics.h"

//Return a number in a range of 0 to max variable
int rand0toGiven(int max)
{
	//Randomize seed initialization with Global Time
	srand(graphics::getGlobalTime()); 
	max = max + 1;
	int randNum = rand() % max;
	return randNum;
}