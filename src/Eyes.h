#pragma once

#include "ofMain.h"
#include "Eye.h"
#include "Constants.h"

class Eyes
{
	
public:
	
	Eyes();
	void draw();
	void look(float normX, float normY);
	
	int assignedID;
	
private:
	
	vector <Eye *> eyes;
	ofPoint lastPos;
};

	