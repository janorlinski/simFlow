// test a function that gives phi from px and py

#include "TMath.h"

Double_t getPhi (Double_t px, Double_t py) {

	Double_t phi = 0.;

	if (px > 0 && py > 0) phi = TMath::RadToDeg() * atan(px/py);
	if (px > 0 && py < 0) phi = 180 + TMath::RadToDeg() * atan(px/py);
	if (px < 0 && py < 0) phi = 180 + TMath::RadToDeg() * atan(px/py);
	if (px < 0 && py > 0) phi = 360 + TMath::RadToDeg() * atan(px/py);

	return phi;

}

void testPhi (Double_t angle) {
	
	Double_t px = sin(TMath::DegToRad()*angle);
	Double_t py = cos(TMath::DegToRad()*angle);
	Double_t phi = getPhi (px, py);
	
	cout << "Real phi = " << angle <<", calculated phi = " << phi << endl;

}
