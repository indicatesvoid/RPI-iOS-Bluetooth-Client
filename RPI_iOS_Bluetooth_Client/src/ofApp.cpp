#include "ofApp.h"

#define CIRCLE_RADIUS 30
#define BAUD 57600

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(ofColor::black);
    
#if defined(TARGET_LINUX)
    string prefixMatch = "/dev/tty.AMA"; // Raspi UART
#else
    string prefixMatch = "/dev/tty.usbserial"; // Serial comm cable
#endif

    vector<ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    
    string port = "";
    bFoundPort = false;
    for(size_t i = 0; i < deviceList.size(); i++) {
        string n = deviceList[i].getDevicePath();
        ofLogNotice("path: " + n);
        if(std::string::npos != n.find(prefixMatch)) {
            port = n;
            bFoundPort = true;
            break;
        }
    }
    
    if(bFoundPort) {
        serial.setup(port, BAUD);
    }
    
    // variable init //
    circleX = ofGetWindowWidth()/2;
    circleY = ofGetWindowHeight()/2;
    bytesRemaining = PACKET_SIZE;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    if(!bFoundPort) return;
    
    // flush serial buffer up to latest packet if we have a queue of several packets //
    int available = serial.available();
    if( available > PACKET_SIZE && available % PACKET_SIZE == 0) {
        for(size_t i = 0; i < available - PACKET_SIZE; i++) {
            serial.readByte();
        }
    }
    
    if(bytesRemaining > 0) {
        if( serial.available() > 0 ) {
            // try to read - note offset into the bytes[] array, this is so
            // that we don't overwrite the bytes we already have
            int bytesArrayOffset = PACKET_SIZE - bytesRemaining;
            int result = serial.readBytes( &bytes[bytesArrayOffset],
                                          bytesRemaining );
            
//            ofLogNotice("byte " + ofToString(bytesArrayOffset) + " : " + ofToString((uint8_t)bytes[bytesArrayOffset]));
        
            // check for error code
            if ( result == OF_SERIAL_ERROR ) {
                // something bad happened
                ofLog( OF_LOG_ERROR, "unrecoverable error reading from serial" );
                // bail out
//                break;
            } else if ( result == OF_SERIAL_NO_DATA ) {
                // nothing was read, try again
            } else {
                // we read some data!
                bytesRemaining -= result;
            }
        }
    }
    
    else if(bytesRemaining <= 0) {
        // full packet received, set circle position //
        // TO-DO: opcode parsing if performing more than one operation (move) //
        uint8_t x = (uint8_t)bytes[1];
        uint8_t y = (uint8_t)bytes[2];
        // re-scale 8-bit uint (0-255) to window size //
        circleX = (float)(x / 255.0) * ofGetWindowWidth();
        circleY = (float)(y / 255.0) * ofGetWindowHeight();
        
//        ofLogNotice("Received x, y: " + ofToString(circleX) + " , " + ofToString(circleY));
        
        // reset counters //
        bytesRemaining = PACKET_SIZE;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofCircle(circleX, circleY, CIRCLE_RADIUS);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
