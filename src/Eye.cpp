#include "Eye.h"

Eye::Eye(string e, string p, ofPoint location)
{
	_normX = 0;
	_normY = 0;
	
	_loc = location;
	
	_eye.loadImage(e);
	_iris.loadImage(p);
}

void Eye::draw()
{	
	ofSetColor(255, 255, 255);
	ofFill();
	
	ofEnableAlphaBlending();
	
	_eye.draw(_loc.x, _loc.y);
	
	float xAdd = 300 - (300 * _normX);
	float yAdd = 300 * _normY;
	
	_iris.draw(_loc.x - 100 + xAdd, _loc.y + 60 + yAdd);
	
	ofDisableAlphaBlending();
}

void Eye::look(float normX, float normY)
{
	_normX = normX;
	_normY = normY;
}