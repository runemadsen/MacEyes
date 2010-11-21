#include "testApp.h"

void testApp::setup() 
{
	eyes = new Eyes(1, 50, 20);
	
	ofSetFrameRate(60);
	ofBackground( 0, 0, 0 );

	Sensing::getInstance()->setListener(this);
}

void testApp::update() 
{	
	Sensing::getInstance()->update();
	
	if(eyes->getAssignedID() == DISABLED && Sensing::getInstance()->blobTracker.blobs.size() > 0)
	{
		ofxCvTrackedBlob& blob = Sensing::getInstance()->blobTracker.blobs[0];
		
		float xNorm = (float) blob.centroid.x / (float) CAM_WIDTH;
		float yNorm = (float) blob.centroid.y / (float) CAM_HEIGHT;
		
		//cout << "Setting blob from draw function normx: " << xNorm << " normy: " << yNorm << endl;
		
		eyes->assignID(blob.id);
		eyes->look(xNorm, yNorm);
	}
	else 
	{
		for(int i = 0; i < Sensing::getInstance()->blobTracker.blobs.size(); i++)
		{
			ofxCvTrackedBlob& blob = Sensing::getInstance()->blobTracker.blobs[i];
			
			if(blob.id == eyes->getAssignedID())
			{
				// is blob centroid normalized?
				float xNorm = (float) blob.centroid.x / (float) CAM_WIDTH;
				float yNorm = (float) blob.centroid.y / (float) CAM_HEIGHT;
				
				//cout << "Updating blob from draw normx: " << xNorm << " normy: " << yNorm << endl;
				
				eyes->look(xNorm, yNorm);
			}
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
	
	if (eyes->getAssignedID() == DISABLED) 
	{
		eyes->assignID(id);
	}
}

void testApp::blobMoved(int x, int y, int id, int order)
{
	//cout << "Blob moved: " << id << endl;
}

void testApp::blobOff( int x, int y, int id, int order ) 
{	
	cout << "Blob off: " << id << endl;
	
	if (eyes->getAssignedID() == id) 
	{
		eyes->removeID();
	}
}



