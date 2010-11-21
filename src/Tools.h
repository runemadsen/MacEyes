#pragma once

class Timer 
{
public:
	
	int state; 
	float time, duration;
	bool upDown;
	
	Timer() 
	{
		upDown = false;
		time = 0.0; 
		duration = 0.0; 
		state = 1;
	}
	
	void tick()
	{
		time += state;
		
		if (time > duration) 
		{
			time = duration;
			state = upDown ? -1 : 0;
		}
		else if(time < 0)
		{
			time = 0;
			state = upDown ? 1 : 0;
		}
	}
};
