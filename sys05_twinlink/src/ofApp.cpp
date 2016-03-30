#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	links.setup(100, 100);
	
	pdf.load("sentence.pdf");
	
	ofVec2f offset = ofVec2f(0,120);
	ofVec2f p = offset;
	ofVec2f ac = ofVec2f(0,0);
	
	for (int i = 0;i < pdf.getNumPath();i++)
	{
		ofPath pdfpath = pdf.getPathAt(i);

		for (int j = 0;j < pdfpath.getOutline().size();j++)
		{
			
			int counter = 0;
			ofPolyline pathClone = pdfpath.getOutline()[j];

			ofVec2f tg = pathClone[counter] +
						 ofVec2f(-pdf.getWidth() / 2.0, -pdf.getHeight() / 2.0) + offset;

			if (i == (pdf.getNumPath() - 1))
			{
				pathClone.addVertex(ofVec2f(pdf.getWidth() / 2.0,
											pdf.getHeight() / 2.0));
			}
			
			
			while (counter < pathClone.size())
			{
				ac += (tg - p) / 40.0;
				ac *= 0.9;
				if (ac.lengthSquared() > 3) ac = ac / ac.lengthSquared() * 3.0;
				p += ac;
				path.addVertex(p);
				while ((counter < pathClone.size()) &&
					   (p.squareDistance(tg) < 10))
				{
					counter++;
					tg = pathClone[counter] +
						 ofVec2f(-pdf.getWidth() / 2.0, -pdf.getHeight() / 2.0) + offset;
				}
			}
			
		}
	}
	
	pathCounter = 0;
}

//--------------------------------------------------------------
void ofApp::update()
{
	
	if (path.size() > 0)
	{
		links.update(path.getVertices()[ofGetFrameNum() % path.size()],true);

//		while (pathCounter < path.size())
//		{
//			links.update(path.getVertices()[pathCounter],true);
//			pathCounter++;
//		}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(0, 0, 0);
	
	ofPushMatrix();
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
	links.draw();
	ofDrawCircle(path.getVertices()[ofGetFrameNum() % path.size()], 3);
	path.draw();
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
//	links.camA.dists.clear();
//	links.camB.dists.clear();
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
