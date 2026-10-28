#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <cmath>

#include "TROOT.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"

#include "getPhi.h"

using namespace std;

// define constants, settings, options, etc.
const TString pathToRepo = "/u/jorlinsk/lustre2/hades/user/kpiaseck/jam2/";
const TString codeName = "agag1.58ms2_Lpot0";
const Int_t run1 = 1001;
const Int_t run2 = 2000; 

void makeLambdaTree ()  {
	
	cout << "Testing the getPhi function..." << endl;

	Double_t Bmin[] = {  0.0 } ;
	Double_t Bmax[] = {  8.0 } ;

	const Int_t NBs = sizeof(Bmin) / sizeof(Bmin[0]) ;

//  string Names[] = ( "eta" , "K+" , "K0" , "Lam" , "Sig" , "Evts" );

	Int_t    Neta[NBs] = {}, NKp[NBs] = {} , NK0[NBs] = {} , NLam[NBs] = {} , NSig0[NBs] = {} , Nevts[NBs] = {};
	Double_t Yeta[NBs] = {}, YKp[NBs] = {} , YK0[NBs] = {} , YLam[NBs] = {} , YSig0[NBs] = {} , Yevts[NBs] = {} ;
	
	TString fileName;
	string line, word, str_Nparts , str_Bpar , str_PDG;
	
	Double_t t, x, y, z, mass, p0, px, py, pz, form_time, xsecfac, time_last_coll, bpar;
	Double_t pt, rap, phi;
	Int_t pdg, ID, charge, ncoll, proc_id_origin, proc_type_origin, pdg_mother1, pdg_mother2, baryon_number;
	Int_t iB;
	
	TFile* f = new TFile (Form("%s_runs_%i_to_%i.root", codeName.Data(), run1, run2), "RECREATE");
	
	TTree* tree = new TTree ("t", "t");
	tree->Branch ("BPar" , &bpar , "bpar/D");
	tree->Branch ("Mass" , &mass , "mass/D");
	tree->Branch ("E" , &p0 , "p0/D");
	tree->Branch ("Momx" , &px , "px/D");
	tree->Branch ("Momy" , &py , "py/D");
	tree->Branch ("Momz" , &pz , "pz/D");
	tree->Branch ("Pt" , &pt , "pt/D");
	tree->Branch ("Y" , &rap , "rap/D");
	tree->Branch ("Phi" , &phi , "phi/D");
	
	cout << "Generating tree from runs " << run1 << " to " << run2 << endl; 
	
	for (Int_t run = run1; run <= run2; run++) {
	  
    cout << "\r| Run " << run << ' ' << flush;
    
    fileName = pathToRepo + codeName + "/jam2_" + TString(to_string(run)) + "/phase.dat" ;
    string fname(fileName.Data());
    // cout << "Fetching file '" << fname << "'..." << endl;
    ifstream fin (fname);
    
    if (! fin.is_open() ) {
      cerr << "<W> file " << fname << " could not be opened.\n";
    }
    
    getline ( fin, line ) ;

    Int_t ievt = 0, Nparts ;
    Int_t NetaEvt, NKpEvt, NK0Evt, NLamEvt, NSig0Evt ;

    bpar = -1 ; 

    while ( getline ( fin, line ) ) 
    {
      if ( line.at(0) == '#' ) {

        if ( bpar != -1) {
          for (iB = 0; iB < NBs; iB++) {
            if (bpar >= Bmin[iB] && bpar < Bmax[iB]) {
              Neta [iB] += NetaEvt ;
              NKp  [iB] += NKpEvt  ;
              NK0  [iB] += NK0Evt  ;
              NLam [iB] += NLamEvt ;
              NSig0[iB] += NSig0Evt;
              Nevts[iB] ++ ;
            }
          }
        }

        ievt++;
        NetaEvt = 0 , NKpEvt = 0 , NK0Evt = 0 , NLamEvt = 0 , NSig0Evt = 0;

        istringstream iss (line);
        iss >> word >> word >> Nparts >> word >> word >> bpar ;
// cout << ievt << ' ' << bpar << ' ' << Nparts << " | " << flush;
      }

      for (int part = 0; part < Nparts; part++)  {
// cout << part << ' ' << flush;
			getline (fin, line);
			istringstream iss2 (line);
			iss2 >> word >> pdg >> word >> mass >> px >> py >> pz >> p0;
			
			if (pdg ==  221) NetaEvt ++;
			if (pdg ==  321) NKpEvt  ++;
			if (pdg ==  311) NK0Evt  ++;
			if (pdg == 3122) NLamEvt ++;
			if (pdg == 3212) NSig0Evt ++;
			
			if (pdg == 3122) {
				//cout << "Filling lambda with m = " << mass <<", E = " << p0 << ", px = " << px << ", py = " << py << ", pz = " << pz << "\n";
				pt = sqrt(px*px + py*py);
				phi = getPhi(px, py);
				rap = 0.5 * log((p0 + pz)/(p0 - pz));
				tree->Fill(); // fill tree with lambdas
			}
      }
// cout << endl;
    }
    fin.close();
  }

  for (iB = 0; iB < NBs ; iB++) {
    Yeta [iB] = Neta [iB] / (double) Nevts[iB] ;
    YKp  [iB] = NKp  [iB] / (double) Nevts[iB] ;
    YK0  [iB] = NK0  [iB] / (double) Nevts[iB] ;
    YLam [iB] = NLam [iB] / (double) Nevts[iB] ;
    YSig0[iB] = NSig0[iB] / (double) Nevts[iB] ;
  }

  cout << "\n\nCounts";
  cout << "\n        \t ";  for (iB = 0; iB < NBs; iB++) cout << Bmin [iB] <<':'<< Bmax[iB] <<'\t'<<flush;
  cout << "\nN(eta ) \t ";  for (iB = 0; iB < NBs; iB++) cout << Neta [iB] <<'\t'<<flush;
  cout << "\nN(K+  ) \t ";  for (iB = 0; iB < NBs; iB++) cout << NKp  [iB] <<'\t'<<flush;
  cout << "\nN(K0  ) \t ";  for (iB = 0; iB < NBs; iB++) cout << NK0  [iB] <<'\t'<<flush;
  cout << "\nN(Lam ) \t ";  for (iB = 0; iB < NBs; iB++) cout << NLam [iB] <<'\t'<<flush;
  cout << "\nN(Sig0) \t ";  for (iB = 0; iB < NBs; iB++) cout << NSig0[iB] <<'\t'<<flush;
  cout << endl;
  cout << "\nN_evts  \t ";  for (iB = 0; iB < NBs; iB++) cout << Nevts[iB] <<'\t'<<flush;

  cout << "\n\n\nYields:";
  cout << "\n        \t ";  for (iB = 0; iB < NBs; iB++) cout << Bmin [iB] <<':'<< Bmax[iB] <<"     "<<flush;
  cout << scientific << setprecision(2);
  cout << "\nY(eta ) \t ";  for (iB = 0; iB < NBs; iB++) cout << Yeta [iB] <<"   "<<flush;
  cout << "\nY(K+  ) \t ";  for (iB = 0; iB < NBs; iB++) cout << YKp  [iB] <<"   "<<flush;
  cout << "\nY(K0  ) \t ";  for (iB = 0; iB < NBs; iB++) cout << YK0  [iB] <<"   "<<flush;
  cout << "\nY(Lam ) \t ";  for (iB = 0; iB < NBs; iB++) cout << YLam [iB] <<"   "<<flush;
  cout << "\nY(Sig0) \t ";  for (iB = 0; iB < NBs; iB++) cout << YSig0[iB] <<"   "<<flush;

  cout << "\n\n"; 
  
  tree->Write();
  f->Save();
  f->Close();
  
  //return 0;
}
