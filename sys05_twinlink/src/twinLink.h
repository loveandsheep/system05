//
//  twinLink.h
//  sys05_twinlink
//
//  Created by Ovis aries on 2016/02/25.
//
//

#ifndef twinLink_h
#define twinLink_h

#include "ofMain.h"
#include "camRecorder.h"

class singleArm{
public:
	
	~singleArm()
	{
		axis.clearParent();
		camNode.clearParent();
		node.clearParent();
		node2.clearParent();
		gearNode.clearParent();
	}
	
	void setup(ofVec2f axisPos, int length, int length2, bool flip);
	void update(ofVec2f pos, float degAngle = 45);
	void draw();
	
	ofNode camNode;
	ofNode axis;
	ofNode node;
	ofNode node2;
	ofNode gearNode;
	ofVec3f target;
	int armLength;
	int targLength;
	bool bFlip;
};

class twinLink{
public:
	
	void setup(int lenArm1, int lenArm2);
	void update(ofVec2f pos, bool addCam);
	void draw();

	camRecorder camA, camB;
	singleArm arm_A, arm_B;
};

#endif /* twinLink_h */
