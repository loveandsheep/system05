//
//  twinLink.cpp
//  sys05_twinlink
//
//  Created by Ovis aries on 2016/02/25.
//
//

#include "twinLink.h"

void twinLink::setup(int lenArm1, int lenArm2)
{
	arm_A.setup(ofVec2f( 0, 0), lenArm1, lenArm2);
	arm_B.setup(ofVec2f(-50, 0), lenArm1, lenArm2);
	
	arm_A.camNode.setParent(arm_A.axis);
	arm_A.camNode.setPosition(lenArm1/1.5, 0, 0);
	arm_B.camNode.setParent(arm_B.axis);
	arm_B.camNode.setPosition(-lenArm1/1.5, 0, 0);
	
	camA.setup(ofVec2f( 50 * 1.3, -100), false);
	camB.setup(ofVec2f(-50 * 1.3, -100), true);
}

void twinLink::update(ofVec2f pos, bool addCam)
{
	arm_A.update(pos, -45.0);
	arm_B.update(pos, 45.0);
	
	if (addCam)
	{
		camA.addCam(arm_A.camNode.getGlobalPosition());
		camB.addCam(arm_B.camNode.getGlobalPosition());		
	}
}

void twinLink::draw()
{
	arm_A.draw();
	arm_B.draw();
	camA.drawCam();
	camB.drawCam();
}

void singleArm::setup(ofVec2f axisPos, int length, int length2)
{
	axis.setGlobalPosition(axisPos);
	node.setParent(axis);
	node.setPosition(0, length, 0);
	node2.setParent(node);
	node2.setPosition(0, length2, 0);

	camNode.setParent(axis);
	camNode.setPosition(-length/2, 0, 0);
	
	armLength = length;
	targLength = length2;
}

void singleArm::update(ofVec2f pos, float defAngle)
{
	float mover = defAngle / 2.0;
	float root = defAngle;
	float angle_a, angle_b;
	float dst_a, dst_b;
	float powLT = powf(targLength, 2.0);
	ofNode vChild;
	
	axis.setOrientation(ofVec3f(0,0,0));
	for (int j = 0;j < 30;j++)
	{
		angle_a = root + mover;
		angle_b = root - mover;
		vChild.setParent(axis);
		vChild.setPosition(sin(ofDegToRad(-angle_a)) * armLength,
						   cos(ofDegToRad(-angle_a)) * armLength, 0);
		dst_a = vChild.getGlobalPosition().squareDistance(pos);
		
		vChild.setPosition(sin(ofDegToRad(-angle_b)) * armLength,
						   cos(ofDegToRad(-angle_b)) * armLength, 0);
		dst_b = vChild.getGlobalPosition().squareDistance(pos);
		
		root = abs(dst_a - powLT) < abs(dst_b - powLT) ? angle_a : angle_b;
		mover /= 1.2;
	}
	axis.setOrientation(ofVec3f(0,0,root));
	node.lookAt(pos);
	node.tilt(-90);
}

void singleArm::draw()
{
	camNode.draw();
	axis.draw();
	node.draw();
	node2.draw();

	ofDrawLine(axis.getGlobalPosition(), camNode.getGlobalPosition());
	ofDrawLine(axis.getGlobalPosition(), node.getGlobalPosition());
	ofDrawLine(node.getGlobalPosition(), node2.getGlobalPosition());
}