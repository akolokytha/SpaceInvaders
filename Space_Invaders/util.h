#pragma once
#include <random>

//Disk struct for collisions
struct Disk
{
	float cx, cy;
	float radius;
};

//Return a number in a range of 0 to max variable
int rand0toGiven(int max);