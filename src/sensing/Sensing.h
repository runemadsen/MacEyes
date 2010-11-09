#pragma once

#include "ofMain.h"
#include "ofxCvBlobTracker.h"
#include "ofxCvTrackedBlob.h"
#include "ofxCvConstants_Track.h"
#include "ofxSimpleGuiToo.h"
#include "ofxFBOTexture.h"
#include "ofxVec2f.h"
#include "Constants.h"
#include "ofxCvHaarFinder.h"

class Sensing  
{
	
public:
	
	static Sensing * getInstance();
	
	void update();
	void draw();
	
	bool show;
	
	bool debug();
	
	ofxCvBlobTracker  blobTracker;	
	void setListener(ofxCvBlobListener * listener);
	
	vector <ofxCvTrackedBlob> getBlobs();
	
private:
	
	// singleton stuff
	Sensing();  // Private so that it can  not be called
	Sensing(Sensing const&){};             // copy constructor is private
	Sensing& operator=(Sensing const&){};  // assignment operator is private
	static Sensing* m_pInstance;
		
	bool maskToggle;
	bool debugToggle;
	
	int threshold;
	int blurAmount;
	
	ofVideoGrabber  vidGrabber;
	ofImage mask;
	
	ofxCvHaarFinder finder;
	
	ofxFBOTexture outputTexture;
	
	ofxCvColorImage  colorImg;
	ofxCvGrayscaleImage  grayImg;
	
	unsigned char * maskPixels;
	unsigned char * grayPixels;
};