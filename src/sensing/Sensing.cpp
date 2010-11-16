#include "Sensing.h"

/* Singleton stuff
 ___________________________________________________________ */

Sensing * Sensing::m_pInstance = NULL;

Sensing * Sensing::getInstance()
{
	if (!m_pInstance)   // Only allow one instance of class to be generated.
		m_pInstance = new Sensing;
	
	return m_pInstance;
}

/* Set listener
 ___________________________________________________________ */

void Sensing::setListener(ofxCvBlobListener * listener)
{
	blobTracker.setListener(listener);
}

/* Constructor
 ___________________________________________________________ */

Sensing::Sensing()
{
	finder.setup("haarcascade_frontalface_default.xml");
	
	threshold = 0;
	blurAmount = 0;
	
	show = false;
	maskToggle = true;
	debugToggle = false;
	
	colorImg.allocate( CAM_WIDTH, CAM_HEIGHT );
	grayImg.allocate( CAM_WIDTH, CAM_HEIGHT );
	
	grayPixels = new unsigned char [CAM_WIDTH * CAM_HEIGHT]; 
	outputTexture.allocate(CAM_WIDTH, CAM_HEIGHT, GL_RGB);
	
	mask.loadImage("mask.png");
	mask.setImageType(OF_IMAGE_GRAYSCALE);
	maskPixels = mask.getPixels();
	
	gui.addTitle("Input");
	gui.addContent("Input", outputTexture);
	gui.addSlider("Threshold", threshold , 0.0, 255);
	gui.addSlider("Bluring", blurAmount , 0, 40);
	gui.addContent("Difference", grayImg);
	gui.addToggle("Mask", maskToggle);
	gui.addToggle("Debug", debugToggle);
	gui.show();
	
	for (int i=0; i<CAM_WIDTH*CAM_HEIGHT; i++) 
	{
		if (maskPixels[i]!=0)
		{
			maskPixels[i]==1;			
		} 
	}
	
	//vidGrabber.setDeviceID(6);
	vidGrabber.initGrabber(CAM_WIDTH, CAM_HEIGHT );
}

/* Update
 ___________________________________________________________ */

void Sensing::update()
{
	vidGrabber.grabFrame();
	
	if( vidGrabber.isFrameNew() ) 
	{
        colorImg = vidGrabber.getPixels();
        colorImg.mirror(false, true);
		grayImg = colorImg;
		//grayImg.blur(blurAmount);
        //grayImg.threshold(threshold);
		grayPixels = grayImg.getPixels();
		
		/*if(maskToggle) 
		{
			for (int i=0; i<CAM_WIDTH*CAM_HEIGHT; i++) 
			{
				grayPixels[i]=maskPixels[i]&&grayPixels[i]; 
			}
		}*/
		
		grayImg.setFromPixels(grayPixels, CAM_WIDTH,CAM_HEIGHT);
        
		//findContures( img, minSize, maxSize, nMax, inner contours yes/no )
        finder.findHaarObjects(grayImg);
		
		//contourFinder.findContours( grayImg, area, 300000, 20, false);
        blobTracker.trackBlobs(finder.blobs);
    }
}

/* Draw
 ___________________________________________________________ */

void Sensing::draw()
{	
	if(show) 
	{
		gui.draw();
		
		outputTexture.begin();
		ofSetColor( 0xffffff );
		colorImg.draw(0, 0);
		blobTracker.draw(0, 0);
		outputTexture.end();
	}
}

/* Getter / Setter
 ___________________________________________________________ */

vector <ofxCvTrackedBlob> Sensing::getBlobs()
{
	return blobTracker.blobs;
}

bool Sensing::debug()
{
	return debugToggle;
}
