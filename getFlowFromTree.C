Double_t funcFourier2(Double_t *x, Double_t *par) {
	return par[0] / (2 * TMath::Pi()) * (1 + 2 * par[1] * TMath::Cos(x[0] * TMath::DegToRad()) + 2 * par[2] * TMath::Cos(2 * x[0] * TMath::DegToRad()));
}

void getFlowFromTree (TString codeName = "")  {
	
	cout << "\nAnalyzing codename " << codeName << "..." <<endl;
	
	TH1F* hbpar = new TH1F("hbpar", "hbar dist; hbar; counts", 100, 0., 25.0);
	TH1F* eventPlane = new TH1F("eventPlane", "event plane reconstructed from FWall angles; [deg]; counts", 360, -180.0, 180.0);
	TH1F* eventPlane_zoom = new TH1F("eventPlane_zoom", "event plane reconstructed from FWall angles; [deg]; counts", 300, -15.0, 15.0);
	TH1F* huQQ = new TH1F("huQQ", "check of momentum conservation effects; #cos(#Delta#phi)_{mom cons}; Counts", 200, -2.0, 2.0);
	TH1F* hTheta = new TH1F("hTheta", "theta distribution; [deg]; counts", 90, 0.0, 90.0);
	TH2F* hPty = new TH2F("hpty", "pty of lambdas; y0; pt", nScaledRapBins, ScaledRapMin, ScaledRapMax, nPtBins, PtMin, PtMax);
	TH2F* hPty_inGeoAcc = new TH2F("hpty_inGeoAcc", "pty of lambdas in geometrical acceptance; y0; pt", nScaledRapBins, ScaledRapMin, ScaledRapMax, nPtBins, PtMin, PtMax);
	TH1F* hPhi[nScaledRapBins][nPtBins];
	TH1F* hPhi_fw[nScaledRapBins][nPtBins];
	TH1F* hPhi_YInt[nPtBins];
	TH1F* hPhi_PtInt[nScaledRapBins];
	TH1F* hEffectiveMass = new TH1F("hEffMass", "Lambda #sqrt{p_{0}^{2} - p_{x}^{2} - p_{y}^{2} - p_{z}^{2}}; eff mass [GeV]", 200, 850.0, 1250.0);
	TH1F* hV1_PtInt = new TH1F("hV1_PtInt", "pt integrated v1 of lambdas; y0", nScaledRapBins, ScaledRapMin, ScaledRapMax);
	TH1F* hV2_PtInt = new TH1F("hV2_PtInt", "pt integrated v2 of lambdas; y0", nScaledRapBins, ScaledRapMin, ScaledRapMax);
	TH1F* hV1_YInt = new TH1F("hV1_YInt", "y integrated v1 of lambdas; pt", nPtBins, PtMin, PtMax);
	TH1F* hV2_YInt = new TH1F("hV2_YInt", "y integrated v2 of lambdas; pt", nPtBins, PtMin, PtMax);
	TH2F* hV1 = new TH2F("hV1", "v1 of lambdas; y0; pt", nScaledRapBins, ScaledRapMin, ScaledRapMax, nPtBins, PtMin, PtMax);
	TH2F* hV2 = new TH2F("hV2", "v2 of lambdas; y0; pt", nScaledRapBins, ScaledRapMin, ScaledRapMax, nPtBins, PtMin, PtMax);
	
	TH2F* hV1_fw = new TH2F("hV1_fw", "v1 of lambdas with FW EP reco; y0; pt", nScaledRapBins, ScaledRapMin, ScaledRapMax, nPtBins, PtMin, PtMax);
	TH2F* hV2_fw = new TH2F("hV2_fw", "v2 of lambdas with FW EP reco; y0; pt", nScaledRapBins, ScaledRapMin, ScaledRapMax, nPtBins, PtMin, PtMax);
	
	TH1F* hPhiRejected = new TH1F ("hPhi_Rejected", "rejected phi dist; phi; counts", nPhiBins, -180.0, 180.0);
	for (Int_t iy=0; iy<nScaledRapBins; iy++) {
		hPhi_PtInt[iy] = new TH1F (Form("hPhi_PtInt_iy%i", iy), "phi dist pt int; phi; counts", nPhiBins, -180.0, 180.0);
		for (Int_t ipt=0; ipt<nPtBins; ipt++) {
			if (iy==0) hPhi_YInt[ipt] = new TH1F (Form("hPhi_YInt_ipt%i", ipt), "phi dist y int; phi; counts", nPhiBins, -180.0, 180.0);
			hPhi[iy][ipt] = new TH1F (Form("hPhi_iy%i_ipt%i", iy, ipt), "phi dist; phi; counts", nPhiBins, -180.0, 180.0);
			hPhi_fw[iy][ipt] = new TH1F (Form("hPhi_fw_iy%i_ipt%i", iy, ipt), "phi (fw) dist; phi; counts", nPhiBins, -180.0, 180.0);
		}
	}
	
	TFile* fout = new TFile ("FLOW_PHSD_101-110.root", "RECREATE");
	
	for (Int_t iF = 0; iF<nRootFiles; iF++) {
		
		TFile* fin = new TFile (filelist[iF], "READ");
		
		TTree* tree = (TTree*) fin->Get("t");
		
		const Int_t nEntr = tree->GetEntries();
		cout << "Getting flow from file " << fin->GetName() << "; tree has n = " << nEntr << " entries..." << endl;
		Int_t nSub, nEvt, PDG;
		Double_t px, py, pz, p0, pt, rap, phi, bpar;
		tree->SetBranchAddress ("PDG" , &PDG );
		tree->SetBranchAddress ("nSub" , &nSub );
		tree->SetBranchAddress ("nEvt" , &nEvt );
		tree->SetBranchAddress ("BPar" , &bpar );
		tree->SetBranchAddress ("Momx" , &px );
		tree->SetBranchAddress ("Momy" , &py );
		tree->SetBranchAddress ("Momz" , &pz );
		tree->SetBranchAddress ("E" , &p0 );
		tree->SetBranchAddress ("Pt" , &pt );
		tree->SetBranchAddress ("Y" , &rap );
		tree->SetBranchAddress ("Phi" , &phi );
		
		Float_t percent;
		Float_t evtPlane = 0.0;
		Int_t eventCode = 0;
		Int_t firstEntryInThisEvent = 0;
		Bool_t firstLoop = kFALSE;
		Int_t evtCounter = 0;
		Double_t Q_x = 0.0; //sum of cos(phi)
		Double_t Q_y = 0.0; //sum of cos(phi)
		//for (Int_t i = 0; i<100; i++) {
		for (Int_t i = 0; i<nEntr; i++) {
			
			percent = (100.0*i)/nEntr;

			//cout << "[main loop] processing entry i=" << i << "eventCode is " << eventCode << endl;
			if (i%1000==0) cout << "\r Status: " << i << Form(" (%.2f %%) ", percent) << " entries analyzed..." << flush;
			
			tree->GetEntry(i);
			if (bpar < bParMin || bpar > bParMax) {
				//cout << "bpar = " << bpar << "!!! Skipping !!!" << endl;
				continue;
			}
			
			// setup of the tree units
			
			Double_t y0 = (rap)/midRap;
			//Double_t y0 = (rap-midRap)/midRap;
			pt *= 1000; //convert GeV to MeV
			px *= 1000; //convert GeV to MeV
			py *= 1000; //convert GeV to MeV
			pz *= 1000; //convert GeV to MeV
			p0 *= 1000; //convert GeV to MeV
			
			// theta_lab and other lorentz calculations
			
			Double_t rap_lab = rap+midRap;
			Double_t effMass = sqrt(p0*p0 - px*px - py*py - pz*pz);
			Double_t mt = sqrt(effMass*effMass + pt*pt);
			Double_t pz_lab = mt * TMath::SinH (rap_lab);
			Double_t theta = TMath::ATan(pt/pz_lab)*TMath::RadToDeg();
			
			// the following is a dirty fix, since getPhi() defines phi as rotation around y-axis (should be around x)
			// --------------------------------
			phi -= 90.;						//-
			
			// this is an event-wise section for event plane calculation
			if (nEvt!=eventCode) {
				if (!firstLoop) {
					//cout << "New event begun at i = " << i << endl;
					eventCode=nEvt;
					firstEntryInThisEvent = i;
					firstLoop=kTRUE;
					Q_y=0.0;
					Q_x=0.0;
				}
				else if (firstLoop) {
					//cout << "Calculating sums done. Calculating EP. Q_y/Qx = " << Q_y/Q_x << " and ep = " << evtPlane << endl;
					evtCounter++;
					evtPlane = TMath::ATan2(Q_y, Q_x)*TMath::RadToDeg();
					eventPlane->Fill(evtPlane);
					eventPlane_zoom->Fill(evtPlane);
					//Q_y=0.0;
					//Q_x=0.0;
					i = firstEntryInThisEvent-1;
					firstLoop=kFALSE;
					continue;	
				}
			}
			
			if (nEvt==eventCode && firstLoop) {
				
				//cout << "[ep calc] processing entry i=" << i << endl;
				//if (pz<0) continue; // skip target spectators
				if (theta>FWall_minAngle && theta<FWall_maxAngle && (PDG==2112 || PDG==2212)) { // accept only protons and neutrons entering the fwall
					
					Q_x += cos(phi*TMath::DegToRad());
					Q_y += sin(phi*TMath::DegToRad());
					
				}
				
				continue;
				
			}
			
			//cout << "[filling histos] processing entry i=" << i << endl;
			
			if (phi < 180.) phi += 360.0;	//-
			// --------------------------------
			if (phi > 180.) phi -= 360.; // convert phi (0, 360) to phi (-180, 180)
			
			hbpar->Fill(bpar);
			// applying PDG cuts
			if (PDG!=3122) continue;
			
			hTheta->Fill(theta);
			hPty->Fill(y0, pt);
			if (theta>HADES_minAngle && theta<HADES_maxAngle) hPty_inGeoAcc->Fill(y0, pt);
			
			// mom cons calc
			
			Double_t u_x = px/pt;
			Double_t u_y = py/pt;
			Double_t udotQ = u_x*Q_x + u_y*Q_y;
			Double_t udotQ_norm = udotQ/sqrt(Q_x*Q_x + Q_y*Q_y);
			
			if (theta>HADES_minAngle && theta<HADES_maxAngle) huQQ->Fill(udotQ_norm);
			
			
			//cout << "track has y0 = "<<y0<<" and pt = "<<pt<< endl;
			Int_t ScaledRapBin = (y0 - ScaledRapMin) / ((ScaledRapMax - ScaledRapMin)/nScaledRapBins);
			Int_t PtBin = (pt - PtMin) / ((PtMax - PtMin)/nPtBins);
			
			if (y0 > ScaledRapMin && y0 < ScaledRapMax && pt > PtMin && pt < PtMax) {
				hEffectiveMass->Fill(effMass);
				hPhi[ScaledRapBin][PtBin]->Fill(phi);
				if (theta>HADES_minAngle && theta<HADES_maxAngle) hPhi_fw[ScaledRapBin][PtBin]->Fill(phi-evtPlane);
				hPhi_PtInt[ScaledRapBin]->Fill(phi);
				if (y0 < 0.0) hPhi_YInt[PtBin]->Fill(phi);
			}
			
			else hPhiRejected->Fill(phi);
		
		}
		
		 cout << "\nTree scanning done!" << endl;
		 
		 fin->Close();
	}
	
	for (Int_t iy=0; iy<nScaledRapBins; iy++) {
	
		TF1* fourierFitPtInt = new TF1 ("fourierFitPtInt", funcFourier2, -180, 180, 3);
		hPhi_PtInt[iy]->Fit(fourierFitPtInt, "IR+");
		Double_t v1 = fourierFitPtInt->GetParameter(1);
		Double_t v2 = fourierFitPtInt->GetParameter(2);
		Double_t v1err = fourierFitPtInt->GetParError(1);
		Double_t v2err = fourierFitPtInt->GetParError(2);
		hV1_PtInt->SetBinContent(iy+1, v1);
		hV2_PtInt->SetBinContent(iy+1, v2);
		hV1_PtInt->SetBinError(iy+1, v1err);
		hV2_PtInt->SetBinError(iy+1, v2err);
		
		for (Int_t ipt=0; ipt<nPtBins; ipt++) {
			
			TF1* fourierFit = new TF1 ("fourierFit", funcFourier2, -180, 180, 3);
			hPhi[iy][ipt]->Fit(fourierFit, "IR+");
			Double_t v1 = fourierFit->GetParameter(1);
			Double_t v2 = fourierFit->GetParameter(2);
			Double_t v1err = fourierFit->GetParError(1);
			Double_t v2err = fourierFit->GetParError(2);
			hV1->SetBinContent(iy+1, ipt+1, v1);
			hV2->SetBinContent(iy+1, ipt+1, v2);
			hV1->SetBinError(iy+1, ipt+1, v1err);
			hV2->SetBinError(iy+1, ipt+1, v2err);
			
			TF1* fourierFit_fw = new TF1 ("fourierFit_fw", funcFourier2, -180, 180, 3);
			hPhi_fw[iy][ipt]->Fit(fourierFit_fw, "IR+");
			Double_t v1_fw = fourierFit_fw->GetParameter(1);
			Double_t v2_fw = fourierFit_fw->GetParameter(2);
			Double_t v1err_fw = fourierFit_fw->GetParError(1);
			Double_t v2err_fw = fourierFit_fw->GetParError(2);
			hV1_fw->SetBinContent(iy+1, ipt+1, v1_fw);
			hV2_fw->SetBinContent(iy+1, ipt+1, v2_fw);
			hV1_fw->SetBinError(iy+1, ipt+1, v1err_fw);
			hV2_fw->SetBinError(iy+1, ipt+1, v2err_fw);
			
			if (iy==0) {
				
				TF1* fourierFitYInt = new TF1 ("fourierFitYInt", funcFourier2, -180, 180, 3);
				hPhi_YInt[ipt]->Fit(fourierFitYInt, "IR+");
				Double_t v1 = fourierFitYInt->GetParameter(1);
				Double_t v2 = fourierFitYInt->GetParameter(2);
				Double_t v1err = fourierFitYInt->GetParError(1);
				Double_t v2err = fourierFitYInt->GetParError(2);
				hV1_YInt->SetBinContent(ipt+1, v1);
				hV2_YInt->SetBinContent(ipt+1, v2);
				hV1_YInt->SetBinError(ipt+1, v1err);
				hV2_YInt->SetBinError(ipt+1, v2err);
				
			}
		}
	}
	
	fout->cd();
	hEffectiveMass->Write();
	eventPlane->Write();
	eventPlane_zoom->Write();
	hbpar->Write();
	hTheta->Write();
	huQQ->Write();
	hPty->Write();
	hPty_inGeoAcc->Write();
	hPhiRejected->Write();
	hV1->Write();
	hV2->Write();
	hV1_fw->Write();
	hV2_fw->Write();
	hV1_PtInt->Write();
	hV2_PtInt->Write();
	hV1_YInt->Write();
	hV2_YInt->Write();
	fout->mkdir("flowhist");
	fout->cd("flowhist");
	for (Int_t iy=0; iy<nScaledRapBins; iy++) {
		for (Int_t ipt=0; ipt<nPtBins; ipt++) {
			
			hPhi[iy][ipt]->Write();
			hPhi_fw[iy][ipt]->Write();
		}
	}
	
	fout->Save();
	fout->Close();
	
	return;
	
}
	
