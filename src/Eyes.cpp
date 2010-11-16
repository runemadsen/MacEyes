#include "Eyes.h"

Eyes::Eyes(float scale, float xPos, float yPos)
{
	_scale = scale;
	
	_loc.set(xPos, yPos);
	_faceLocNorm.set(0, 0);
	
	_leftEye.loadImage("lefteye.png");
	_leftIris.loadImage("leftpoint.png");
	_rightEye.loadImage("righteye.png");
	_rightIris.loadImage("rightpoint.png");
	
	if(scale != 1.0)
	{
		_leftEye.resize(_leftEye.width * _scale, _leftEye.height * _scale);
		_leftIris.resize(_leftIris.width * _scale, _leftIris.height * _scale);
		_rightEye.resize(_rightEye.width * _scale, _rightEye.height * _scale);
		_rightIris.resize(_rightIris.width * _scale, _rightIris.height * _scale);
	}
	
	_leftIris.setAnchorPercent(0.5, 0.5);
	_rightIris.setAnchorPercent(0.5, 0.5);
	
	float marginX = _leftEye.width / 5;
	float marginY = _leftEye.height / 5;
	
	_leftIrisArea.x = _loc.x + marginX;
	_leftIrisArea.y = _loc.y + marginY;
	_leftIrisArea.width = _leftEye.width - ( 2 * marginX);
	_leftIrisArea.height = _leftEye.height - ( 2 * marginY );
	
	_rightIrisArea = _leftIrisArea;
	_rightIrisArea.x += _leftEye.width - 10;
		
	assignedID = DISABLED;
}

void Eyes::draw()
{	
	ofFill();
	
	/*ofSetColor(255, 0, 0);
	ofRect(_leftIrisArea.x, _leftIrisArea.y, _leftIrisArea.width, _leftIrisArea.height);
	ofRect(_rightIrisArea.x, _rightIrisArea.y, _rightIrisArea.width, _rightIrisArea.height);*/
	
	ofSetColor(255, 255, 255);
	
	ofEnableAlphaBlending();
	
	_leftEye.draw(_loc.x, _loc.y);
	_rightEye.draw(_loc.x + (_leftEye.width - 10), _loc.y);
	
	float leftIrisX = _leftIrisArea.x +  (_leftIrisArea.width * _faceLocNorm.x);
	float leftIrisY = _leftIrisArea.y +  (_leftIrisArea.height * _faceLocNorm.y);
	
	float rightIrisX = _rightIrisArea.x +  (_rightIrisArea.width * _faceLocNorm.x);
	float rightIrisY = _rightIrisArea.y +  (_rightIrisArea.height * _faceLocNorm.y);
	
	_leftIris.draw(leftIrisX, leftIrisY);	
	_rightIris.draw(rightIrisX, rightIrisY);
	
	ofDisableAlphaBlending();
}

void Eyes::look(float normX, float normY)
{
	float diff = 0.005;
	
	if(fabs(normX - _faceLocNorm.x) > diff || fabs(normY - _faceLocNorm.y) > diff)
	{
		_faceLocNorm.x = normX;
		_faceLocNorm.y = normY;
	}
}