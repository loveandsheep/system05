#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	links.setup(100, 100);
	
	pdf.load("test.pdf");
	
	ofVec2f offset = ofVec2f(-27.5,130);
	ofVec2f p = offset;
	ofVec2f ac = ofVec2f(0,0);
	
	bool startCenter = false;//原点スタート
	
	for (int i = 0;i < pdf.getNumPath();i++)
	{
		ofPath pdfpath = pdf.getPathAt(i);

		for (int j = 0;j < pdfpath.getOutline().size();j++)
		{
			
			int counter = 0;
			ofPolyline pathClone = pdfpath.getOutline()[j];

			ofVec2f tg = pathClone[counter] +
						 ofVec2f(-pdf.getWidth() / 2.0, -pdf.getHeight() / 2.0) + offset;

			if ((i == (pdf.getNumPath() - 1)) && (startCenter))
			{
				pathClone.addVertex(ofVec2f(pdf.getWidth() / 2.0,
											pdf.getHeight() / 2.0));
			}
				else if (!startCenter)
			{
				ofVec2f mod = ofVec2f(-pdf.getWidth() / 2.0, -pdf.getHeight() / 2.0) + offset;
				
				if (i == 0) p = pathClone[0] + mod;
				if (i == (pdf.getNumPath() - 1)) pathClone.addVertex(pathClone[0]);
			}
			
			
			ofVec2f lastP = p;
			while (counter < pathClone.size())
			{
//				ac = (tg - p) / 10.0;
//				ac *= 0.9;
//				if (ac.lengthSquared() > 3) ac = ac / ac.lengthSquared() * 3.0;
//				p += ac;
				p.interpolate(tg, 0.1);
				path.addVertex(p);
				while ((counter < pathClone.size()) &&
					   (p.squareDistance(tg) < 1))
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
//		if (pathCounter < path.size())
//			links.update(path.getVertices()[ofGetFrameNum() % path.size()],true);
//		pathCounter++;

		while (pathCounter < path.size())
		{
			links.update(path.getVertices()[pathCounter],true);
			pathCounter++;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(0, 0, 0);
	
	ofPushMatrix();
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
	ofScale(1.0, 1.0);
	links.draw();
	ofDrawCircle(path.getVertices()[ofGetFrameNum() % path.size()], 3);
	path.draw();
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
//	links.camA.dists.clear();
//	links.camB.dists.clear();
	if (key == ' ') {
		links.camA.Export("camA");
		links.camB.Export("camB");
	}
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
