#pragma once

#include "ofMain.h"

class Eye
{
	
public:
	
	Eye(string e, string p, ofPoint location);
	void draw();
	
	void look(float normX, float normY);
	
private:
	
	ofPoint _loc;
	ofImage _eye;
	ofImage _iris;
	
	float _normX, _normY;
};