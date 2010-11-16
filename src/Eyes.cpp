#include "Eyes.h"

Eyes::Eyes()
{
	lastPos.x = 0;
	lastPos.y = 0;
	
	assignedID = DISABLED;
	
	eyes.push_back( new Eye("lefteye.png", "leftpoint.png", ofPoint(30, 40)));
	eyes.push_back( new Eye("righteye.png", "rightpoint.png", ofPoint(300, 40)));
}

void Eyes::draw()
{	
	eyes[0]->draw();
	eyes[1]->draw();
}

void Eyes::look(float normX, float normY)
{
	float diff = 0.005;
	
	if(fabs(normX - lastPos.x) > diff || fabs(normY - lastPos.y) > diff)
	{
		eyes[0]->look(normX, normY);
		eyes[1]->look(normX, normY);
	
		lastPos = ofPoint(normX, normY);
	}
}