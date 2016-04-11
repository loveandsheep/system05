//
//  camRecorder.cpp
//  sys05_twinlink
//
//  Created by Ovis aries on 2016/02/26.
//
//

#include "camRecorder.h"

void camRecorder::setup(ofVec2f camPos, bool inverse)
{
	camAxis = camPos;
	dists.clear();
	bInv = inverse;
}

void camRecorder::addCam(ofVec2f pos)
{
	dists.push_back(camAxis.distance(pos));
}

void camRecorder::drawCam()
{
	if (dists.size() == 0) return;
	
	ofPushMatrix();
	ofTranslate(camAxis);
	
	ofDrawCircle(0, 0, 5);
	glBegin(GL_LINE_LOOP);
	for (int i = 0;i < 360;i+=2)
	{
		float p = i / 360.0;
		glVertex2d(cos(ofDegToRad(i + (bInv ? 180 : 0))) * dists[int(p * dists.size())],
				   sin(ofDegToRad(i + (bInv ? 180 : 0))) * dists[int(p * dists.size())]);
	}
	glEnd();
	ofPopMatrix();
}

void camRecorder::Export(string filename)
{
	ofVec2f size = ofVec2f(400, 400);
	vector<ofVec3f> pts;
	ofPolyline poly;
	for (int i = 0;i < 360;i++)
	{
		float p = i / 360.0;
		pts.push_back(ofVec3f(cos(ofDegToRad(i + (bInv ? 180 : 0))) * dists[int(p * dists.size())],
							  sin(ofDegToRad(i + (bInv ? 180 : 0))) * dists[int(p * dists.size())],0));
		
		pts.back() += size / 2.0;
	}
	pts.push_back(pts[0]);
	
	poly.addVertices(pts);
	
	ofBeginSaveScreenAsPDF(filename+".pdf", false, false,
						   ofRectangle(0,0,size.x,size.y));
	poly.draw();
	ofEndSaveScreenAsPDF();
	
}