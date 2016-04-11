//
//  camRecorder.h
//  sys05_twinlink
//
//  Created by Ovis aries on 2016/02/26.
//
//

#ifndef camRecorder_h
#define camRecorder_h

#include "ofMain.h"
#include "ofxDxfExport.h"

class camRecorder{
public:
	
	void setup(ofVec2f camPos, bool inverse);
	void addCam(ofVec2f pos);
	void drawCam();
	
	bool bInv;
	deque<float> dists;
	ofVec2f camAxis;
	
	void Export(string filename);
};

#endif /* camRecorder_h */
