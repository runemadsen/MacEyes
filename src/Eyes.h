#pragma once

#include "ofMain.h"
#include "Constants.h"
#include "Tools.h"

class Eyes
{
	
public:
	
	Eyes(float scale, float xPos, float yPos);
	void draw();
	void look(float normX, float normY);
	
	void assignID(int aid);
	void removeID();
	int getAssignedID() { return assignedID; }
	
private:
	
	ofImage _leftEye;
	ofImage _leftIris;
	ofImage _rightEye;
	ofImage _rightIris;
	
	ofPoint _loc;
	ofPoint _faceLocNorm;
	
	ofRectangle _leftIrisArea;
	ofRectangle _rightIrisArea;
	
	float _scale;
	
	int assignedID;
	
	Timer _timer;
};

	