#include "ofMain.h"
#include "ofApp.h"

/* same size as iPod touch screen, for now */
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 1136

//========================================================================
int main( ){
	ofSetupOpenGL(WINDOW_WIDTH,WINDOW_HEIGHT,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
