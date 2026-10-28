#include <iostream>

#include "TROOT.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TLine.h"

using namespace std;

const Int_t nRootFiles = 1;
TString filelist[nRootFiles] = {"PHSD_runs_101_to_110.root"};

/*
TString filelist[nRootFiles] = {
"PHSD_runs_1_to_5.root",
"PHSD_runs_6_to_15.root",
"PHSD_runs_16_to_30.root",
"PHSD_runs_31_to_45.root",
"PHSD_runs_46_to_60.root",
"PHSD_runs_61_to_65.root",
"PHSD_runs_66_to_70.root",
"PHSD_runs_71_to_75.root",
"PHSD_runs_76_to_80.root",
"PHSD_runs_81_to_90.root",
"PHSD_runs_91_to_100.root",
"PHSD_runs_101_to_110.root",
"PHSD_runs_111_to_120.root",
"PHSD_runs_121_to_130.root",
"PHSD_runs_131_to_140.root",
"PHSD_runs_141_to_150.root",
"PHSD_runs_151_to_160.root",
"PHSD_runs_161_to_170.root",
"PHSD_runs_171_to_180.root",
"PHSD_runs_181_to_190.root",
"PHSD_runs_191_to_200.root"
};
*/

const Double_t midRap = 0.8219;

const Int_t nScaledRapBins = 11;
const Int_t nPtBins = 7; // adjusted to standard fillHistFromTree_Lambda
//const Int_t nPtBins = 8;
//const Int_t nPhiBins = 36;
const Int_t nPhiBins = 12; // adjusted to standard fillHistFromTree_Lambda

//const Double_t ScaledRapMin = -1.0;
//const Double_t ScaledRapMax = 1.0;
// adjusted to standard
const Double_t ScaledRapMin = -1.1;
const Double_t ScaledRapMax = 1.1;

// adjusted to standard
const Double_t PtMin = 100.0;
const Double_t PtMax = 1500.0;

//* Max B within data = 15.8806
//* For Centrality = [ 10 : 40 ] % ,  range of B = [ 3.37704 : 6.76032 ] fm . 

// select 10-40% centrality class
//const Double_t bParMin = 3.37704;
//const Double_t bParMax = 6.76032;

const Double_t bParMin = 3.8;
const Double_t bParMax = 7.7;

// angle constraints for Fwall
const Double_t FWall_minAngle = 0.34; // deg
const Double_t FWall_maxAngle = 7.4; // deg

// angle constraints for flow analysis with Fwall EP reco
const Double_t HADES_minAngle = 18.0; // deg
const Double_t HADES_maxAngle = 85.0; // deg

#include "getFlowFromTree.C"
//#include "getPlots.C"

void runFlowAnalysis () {

	getFlowFromTree();
	//getPlots();

}
