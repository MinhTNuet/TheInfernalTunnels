#ifndef TIMER_H
#define TIMER_H

#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <bits/stdc++.h>
#include "gamefunc.h"

using namespace std;

class Timer
{
public:
	Timer(float setTimeSMax, float setTimeSCurrent = 0.0f);
	void countDown(float dT);
	void resetToMax();
	bool timeSIsZero();
	bool timeSIsGreaterThanOrEqualTo(float timeSCheck);
    float getTimeRemaining() ;
    bool checktime = true;
private:

	float timeSMax;
	float timeSCurrent;
};

#endif // TIMER_H
