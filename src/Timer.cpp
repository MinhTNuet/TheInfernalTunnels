#include "Timer.h"

Timer::Timer(float setTimeSMax, float setTimeSCurrent) :
	timeSMax(setTimeSMax), timeSCurrent(setTimeSCurrent) {

}

void Timer::countDown(float dT) {
	if (timeSCurrent > 0.0f) {
		timeSCurrent -= dT;
		if (timeSCurrent < 0.0f)
			timeSCurrent = 0.0f;
	}
}

void Timer::resetToMax() {
	timeSCurrent = timeSMax;
}

bool Timer::timeSIsZero() {
	return (timeSCurrent <= 0.0f);
}

bool Timer::timeSIsGreaterThanOrEqualTo(float timeSCheck) {
	return (timeSCurrent >= timeSCheck);
}

float Timer::getTimeRemaining() {
    return timeSCurrent;
}
