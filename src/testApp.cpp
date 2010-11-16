#include "testApp.h"

void testApp::setup() 
{
	eyes = new Eyes();
	
	ofSetFrameRate(60);
	ofBackground( 0, 0, 0 );

	Sensing::getInstance()->setListener(this);
}

void testApp::update() 
{	
	Sensing::getInstance()->update();
	
	for(int i = 0; i < Sensing::getInstance()->blobTracker.blobs.size(); i++)
	{
		ofxCvTrackedBlob& blob = Sensing::getInstance()->blobTracker.blobs[i];
		
		if(blob.id == eyes->assignedID)
		{
			float xNorm = (float) blob.centroid.x / (float) ofGetWidth();
			float yNorm = (float) blob.centroid.y / (float) ofGetHeight();
			
			eyes->look(xNorm, yNorm);
		}
	}
}

void testApp::draw() 
{	
	ofSetColor(255, 255, 255);
	
	eyes->draw();
	
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
	
	if (eyes->assignedID == DISABLED) 
	{
		eyes->assignedID = id;
	}
}

void testApp::blobMoved(int x, int y, int id, int order)
{
	//cout << "Blob moved: " << id << endl;
}

void testApp::blobOff( int x, int y, int id, int order ) 
{	
	cout << "Blob off: " << id << endl;
	
	if (eyes->assignedID == id) 
	{
		eyes->assignedID = DISABLED;
	}
}



