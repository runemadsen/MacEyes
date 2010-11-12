#include "testApp.h"

void testApp::setup() 
{
	ofSetFrameRate(60);
	ofBackground( 0, 0, 0 );

	Sensing::getInstance()->setListener(this);
	
	eyes.push_back( new Eye("lefteye.png", "leftpoint.png", ofPoint(30, 40)));
	eyes.push_back( new Eye("righteye.png", "rightpoint.png", ofPoint(300, 40)));
}

void testApp::update() 
{	
	Sensing::getInstance()->update();
}

void testApp::draw() 
{	
	ofSetColor(255, 255, 255);
	
	eyes[0]->draw();
	eyes[1]->draw();
	
	Sensing::getInstance()->draw();
	
	if(Sensing::getInstance()->debug())
	{
		string fpsStr = "frame rate: "+ofToString(ofGetFrameRate(), 2);
		
		ofSetColor(255, 255, 255);
		
		ofDrawBitmapString(fpsStr, 10, 10);
	}
}

void testApp::keyPressed( int key ) 
{
	if (key =='f' || key=='F') 
	{
		ofToggleFullscreen();
	} 
	else if (key ==' ')
	{
		Sensing::getInstance()->show =! Sensing::getInstance()->show;
	}
}

void testApp::mouseMoved( int x, int y ) {}
void testApp::mouseDragged( int x, int y, int button ) {}
void testApp::mousePressed( int x, int y, int button ) {}
void testApp::mouseReleased() {}


void testApp::blobOn( int x, int y, int id, int order ) 
{		
	cout << "Blob on: " << id << endl;
}

void testApp::blobMoved(int x, int y, int id, int order)
{
	cout << "Blob moved: " << id << endl;
	
	//if(id == 1)
	//{
		float xNorm = (float) x / (float) ofGetWidth();
		float yNorm = (float) y / (float) ofGetHeight();
		
		eyes[0]->look(xNorm, yNorm);
		eyes[1]->look(xNorm, yNorm);
	//}
}

void testApp::blobOff( int x, int y, int id, int order ) 
{	
	cout << "Blob off: " << id << endl;
}



