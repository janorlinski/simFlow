const Int_t markerStyle = 20;
const Int_t lineStyle = 1;
const Double_t markerSize = 1.6;
const Double_t lineWidth = 2;

const Int_t myBlue = kBlue + 3;
const Int_t myRed = kRed + 1;

void getPlots (TString codeNamePotOpt = "")  {
	
	gStyle->SetOptStat(0);
    gStyle->SetPadTopMargin(0.12);
    gStyle->SetPadBottomMargin(0.2);
    gStyle->SetPadRightMargin(0.12);
    gStyle->SetPadLeftMargin(0.2);
    gStyle->SetPadBorderMode(0);

	cout << "Getting plots..." << endl;

	TFile* fin = new TFile ("FLOW_PHSD.root", "READ");
	TFile* fout = new TFile ("PLOTS_PHSD.root", "RECREATE");
	
	TH2F* hEffMass_pot0 = (TH2F*) fin_pot0->Get("hEffMass");
	TH2F* hEffMass_pot1 = (TH2F*) fin_pot1->Get("hEffMass");
	
	TH2F* hV1_PtInt_pot0 = (TH2F*) fin_pot0->Get("hV1_PtInt");
	TH2F* hV1_PtInt_pot1 = (TH2F*) fin_pot1->Get("hV1_PtInt");
	
	TH2F* hV2_PtInt_pot0 = (TH2F*) fin_pot0->Get("hV2_PtInt");
	TH2F* hV2_PtInt_pot1 = (TH2F*) fin_pot1->Get("hV2_PtInt");
	
	TH2F* hV1_YInt_pot0 = (TH2F*) fin_pot0->Get("hV1_YInt");
	TH2F* hV1_YInt_pot1 = (TH2F*) fin_pot1->Get("hV1_YInt");
	
	TH2F* hV2_YInt_pot0 = (TH2F*) fin_pot0->Get("hV2_YInt");
	TH2F* hV2_YInt_pot1 = (TH2F*) fin_pot1->Get("hV2_YInt");
	
	TH2F* hPty_pot0 = (TH2F*) fin_pot0->Get("hpty");
	TH2F* hPty_pot1 = (TH2F*) fin_pot1->Get("hpty");
	
	// V1_PtInt(y)
	
	TCanvas* cV1PtInt = new TCanvas();
	cV1PtInt->cd();
	
	hV1_PtInt_pot0->SetTitle("p_{t}-integrated v_{1}(y_{0}) distribution for Lambdas in 0 < p_{t} [MeV/c] < 1000; y_{0}; v_{1}");
	hV1_PtInt_pot0->GetXaxis()->SetNdivisions(505);
	hV1_PtInt_pot0->GetXaxis()->SetLabelSize(0.05);
	//hV1_PtInt_pot0->GetXaxis()->SetLabelOffset(0.02);
	hV1_PtInt_pot0->GetXaxis()->SetTitleSize(0.05);
	hV1_PtInt_pot0->GetXaxis()->SetTitleOffset(1.15);
	
	hV1_PtInt_pot0->GetYaxis()->SetNdivisions(505);
	hV1_PtInt_pot0->GetYaxis()->SetLabelSize(0.05);
	//hV1_PtInt_pot0->GetYaxis()->SetLabelOffset(0.07);
	hV1_PtInt_pot0->GetYaxis()->SetTitleSize(0.05);
	hV1_PtInt_pot0->GetYaxis()->SetTitleOffset(1.5);
	hV1_PtInt_pot0->GetYaxis()->SetRangeUser(-0.35, 0.35);
	
	TLine* lh1 = new TLine (ScaledRapMin, 0, ScaledRapMax, 0);
	lh1->SetLineStyle(2);
	
	TLine* lv1 = new TLine (0, -0.35, 0, 0.35);
	lv1->SetLineStyle(2);
	
	// set markers and other details
	hV1_PtInt_pot0->SetMarkerStyle(markerStyle);
	hV1_PtInt_pot0->SetMarkerSize(markerSize);
	hV1_PtInt_pot0->SetMarkerColor(myBlue);
	hV1_PtInt_pot0->SetLineStyle(lineStyle);
	hV1_PtInt_pot0->SetLineWidth(lineWidth);
	hV1_PtInt_pot0->SetLineColor(myBlue);
	
	hV1_PtInt_pot1->SetMarkerStyle(markerStyle);
	hV1_PtInt_pot1->SetMarkerSize(markerSize);
	hV1_PtInt_pot1->SetMarkerColor(myRed);
	hV1_PtInt_pot1->SetLineStyle(lineStyle);
	hV1_PtInt_pot1->SetLineWidth(lineWidth);
	hV1_PtInt_pot1->SetLineColor(myRed);
	
	hV1_PtInt_pot0->Draw("P E1");
	hV1_PtInt_pot1->Draw("P E1 same");
	
	lh1->Draw("same");
	lv1->Draw("same");
	
	TLegend* leg1 = new TLegend(0.219198, 0.70913, 0.706304, 0.85138);
	leg1->AddEntry(hV1_PtInt_pot0, "  JAM2 w/o potential", "ple");
	leg1->AddEntry(hV1_PtInt_pot1, "  JAM2 with potential", "ple");
	leg1->SetBorderSize(0);
	//leg1->SetFillStyle(0);
	leg1->Draw("same");
	
	
	// V2_PtInt(y)
	
	TCanvas* cV2PtInt = new TCanvas();
	cV2PtInt->cd();
	
	hV2_PtInt_pot0->SetTitle("p_{t}-integrated v_{2}(y_{0}) distribution for Lambdas in 0 < p_{t} [MeV/c] < 1000; y_{0}; v_{2}");
	hV2_PtInt_pot0->GetXaxis()->SetNdivisions(505);
	hV2_PtInt_pot0->GetXaxis()->SetLabelSize(0.05);
	//hV2_PtInt_pot0->GetXaxis()->SetLabelOffset(0.02);
	hV2_PtInt_pot0->GetXaxis()->SetTitleSize(0.05);
	hV2_PtInt_pot0->GetXaxis()->SetTitleOffset(1.15);
	
	hV2_PtInt_pot0->GetYaxis()->SetNdivisions(505);
	hV2_PtInt_pot0->GetYaxis()->SetLabelSize(0.05);
	//hV2_PtInt_pot0->GetYaxis()->SetLabelOffset(0.07);
	hV2_PtInt_pot0->GetYaxis()->SetTitleSize(0.05);
	hV2_PtInt_pot0->GetYaxis()->SetTitleOffset(1.5);
	hV2_PtInt_pot0->GetYaxis()->SetRangeUser(-0.08, 0.07);
	
	TLine* lh2 = new TLine (ScaledRapMin, 0, ScaledRapMax, 0);
	lh2->SetLineStyle(2);
	
	TLine* lv2 = new TLine (0, -0.08, 0, 0.07);
	lv2->SetLineStyle(2);
	
	// set markers and other details
	hV2_PtInt_pot0->SetMarkerStyle(markerStyle);
	hV2_PtInt_pot0->SetMarkerSize(markerSize);
	hV2_PtInt_pot0->SetMarkerColor(myBlue);
	hV2_PtInt_pot0->SetLineStyle(lineStyle);
	hV2_PtInt_pot0->SetLineWidth(lineWidth);
	hV2_PtInt_pot0->SetLineColor(myBlue);
	
	hV2_PtInt_pot1->SetMarkerStyle(markerStyle);
	hV2_PtInt_pot1->SetMarkerSize(markerSize);
	hV2_PtInt_pot1->SetMarkerColor(myRed);
	hV2_PtInt_pot1->SetLineStyle(lineStyle);
	hV2_PtInt_pot1->SetLineWidth(lineWidth);
	hV2_PtInt_pot1->SetLineColor(myRed);
	
	hV2_PtInt_pot0->Draw("P E1");
	hV2_PtInt_pot1->Draw("P E1 same");
	
	lh2->Draw("same");
	lv2->Draw("same");
	
	TLegend* leg2 = new TLegend(0.212034, 0.22293, 0.69914, 0.363057);
	leg2->AddEntry(hV2_PtInt_pot0, "  JAM2 w/o potential", "ple");
	leg2->AddEntry(hV2_PtInt_pot1, "  JAM2 with potential", "ple");
	leg2->SetBorderSize(0);
	//leg2->SetFillStyle(0);
	leg2->Draw("same");
	
	
	// V1_YInt(y)
	
	TCanvas* cV1YInt = new TCanvas();
	cV1YInt->cd();
	
	hV1_YInt_pot0->SetTitle("y-integrated v_{1}(p_{t}) distribution for Lambdas in  0 < y_{0} < 1; p_{t}; v_{1}");
	hV1_YInt_pot0->GetXaxis()->SetNdivisions(505);
	hV1_YInt_pot0->GetXaxis()->SetLabelSize(0.05);
	//hV1_YInt_pot0->GetXaxis()->SetLabelOffset(0.02);
	hV1_YInt_pot0->GetXaxis()->SetTitleSize(0.05);
	hV1_YInt_pot0->GetXaxis()->SetTitleOffset(1.15);
	
	hV1_YInt_pot0->GetYaxis()->SetNdivisions(505);
	hV1_YInt_pot0->GetYaxis()->SetLabelSize(0.05);
	//hV1_YInt_pot0->GetYaxis()->SetLabelOffset(0.07);
	hV1_YInt_pot0->GetYaxis()->SetTitleSize(0.05);
	hV1_YInt_pot0->GetYaxis()->SetTitleOffset(1.5);
	hV1_YInt_pot0->GetYaxis()->SetRangeUser(0.0, 0.14);
	
	TLine* lh3 = new TLine (PtMin, 0, PtMax, 0);
	lh3->SetLineStyle(2);
	
	// set markers and other details
	hV1_YInt_pot0->SetMarkerStyle(markerStyle);
	hV1_YInt_pot0->SetMarkerSize(markerSize);
	hV1_YInt_pot0->SetMarkerColor(myBlue);
	hV1_YInt_pot0->SetLineStyle(lineStyle);
	hV1_YInt_pot0->SetLineWidth(lineWidth);
	hV1_YInt_pot0->SetLineColor(myBlue);
	
	hV1_YInt_pot1->SetMarkerStyle(markerStyle);
	hV1_YInt_pot1->SetMarkerSize(markerSize);
	hV1_YInt_pot1->SetMarkerColor(myRed);
	hV1_YInt_pot1->SetLineStyle(lineStyle);
	hV1_YInt_pot1->SetLineWidth(lineWidth);
	hV1_YInt_pot1->SetLineColor(myRed);
	
	hV1_YInt_pot0->Draw("P E1");
	hV1_YInt_pot1->Draw("P E1 same");
	
	lh3->Draw("same");
	
	TLegend* leg3 = new TLegend(0.391117, 0.227176, 0.878223, 0.367304);
	leg3->AddEntry(hV1_YInt_pot0, "  JAM2 w/o potential", "ple");
	leg3->AddEntry(hV1_YInt_pot1, "  JAM2 with potential", "ple");
	leg3->SetBorderSize(0);
	leg3->SetFillStyle(0);
	leg3->Draw("same");
	
	
	// V2_YInt(y)
	
	TCanvas* cV2YInt = new TCanvas();
	cV2YInt->cd();
	
	hV2_YInt_pot0->SetTitle("y-integrated v_{2}(p_{t}) distribution for Lambdas in  0 < y_{0} < 1; p_{t}; v_{2}");
	hV2_YInt_pot0->GetXaxis()->SetNdivisions(505);
	hV2_YInt_pot0->GetXaxis()->SetLabelSize(0.05);
	//hV2_YInt_pot0->GetXaxis()->SetLabelOffset(0.02);
	hV2_YInt_pot0->GetXaxis()->SetTitleSize(0.05);
	hV2_YInt_pot0->GetXaxis()->SetTitleOffset(1.15);
	
	hV2_YInt_pot0->GetYaxis()->SetNdivisions(505);
	hV2_YInt_pot0->GetYaxis()->SetLabelSize(0.05);
	//hV2_YInt_pot0->GetYaxis()->SetLabelOffset(0.07);
	hV2_YInt_pot0->GetYaxis()->SetTitleSize(0.05);
	hV2_YInt_pot0->GetYaxis()->SetTitleOffset(1.5);
	hV2_YInt_pot0->GetYaxis()->SetRangeUser(-0.1, 0.09);

	TLine* lh4 = new TLine (PtMin, 0, PtMax, 0);
	lh4->SetLineStyle(2);
	
	// set markers and other details
	hV2_YInt_pot0->SetMarkerStyle(markerStyle);
	hV2_YInt_pot0->SetMarkerSize(markerSize);
	hV2_YInt_pot0->SetMarkerColor(myBlue);
	hV2_YInt_pot0->SetLineStyle(lineStyle);
	hV2_YInt_pot0->SetLineWidth(lineWidth);
	hV2_YInt_pot0->SetLineColor(myBlue);
	
	hV2_YInt_pot1->SetMarkerStyle(markerStyle);
	hV2_YInt_pot1->SetMarkerSize(markerSize);
	hV2_YInt_pot1->SetMarkerColor(myRed);
	hV2_YInt_pot1->SetLineStyle(lineStyle);
	hV2_YInt_pot1->SetLineWidth(lineWidth);
	hV2_YInt_pot1->SetLineColor(myRed);
	
	hV2_YInt_pot0->Draw("P E1");
	hV2_YInt_pot1->Draw("P E1 same");
	
	lh4->Draw("same");
	
	TLegend* leg4 = new TLegend(0.219198, 0.70913, 0.706304, 0.85138);
	leg4->AddEntry(hV2_YInt_pot0, "  JAM2 w/o potential", "ple");
	leg4->AddEntry(hV2_YInt_pot1, "  JAM2 with potential", "ple");
	leg4->SetBorderSize(0);
	leg4->SetFillStyle(0);
	leg4->Draw("same");
	
	// effective mass
	
	TCanvas* cEffMass = new TCanvas();
	cEffMass->cd();
	
	//hEffMass_pot0->SetTitle("y-integrated v_{2}(p_{t}) distribution for Lambdas in  0 < y_{0} < 1; p_{t}; v_{2}");
	hEffMass_pot0->GetXaxis()->SetNdivisions(505);
	hEffMass_pot0->GetXaxis()->SetLabelSize(0.05);
	//hEffMass_pot0->GetXaxis()->SetLabelOffset(0.02);
	hEffMass_pot0->GetXaxis()->SetTitleSize(0.05);
	hEffMass_pot0->GetXaxis()->SetTitleOffset(1.15);
	
	hEffMass_pot0->GetYaxis()->SetNdivisions(505);
	hEffMass_pot0->GetYaxis()->SetLabelSize(0.05);
	//hEffMass_pot0->GetYaxis()->SetLabelOffset(0.07);
	hEffMass_pot0->GetYaxis()->SetTitleSize(0.05);
	hEffMass_pot0->GetYaxis()->SetTitleOffset(1.5);
	//hEffMass_pot0->GetYaxis()->SetRangeUser(-0.08, 0.08);
	
	// set markers and other details
	hEffMass_pot0->SetMarkerStyle(markerStyle);
	hEffMass_pot0->SetMarkerSize(markerSize);
	hEffMass_pot0->SetMarkerColor(myBlue);
	hEffMass_pot0->SetLineStyle(lineStyle);
	hEffMass_pot0->SetLineWidth(lineWidth);
	hEffMass_pot0->SetLineColor(myBlue);
	
	hEffMass_pot1->SetMarkerStyle(markerStyle);
	hEffMass_pot1->SetMarkerSize(markerSize);
	hEffMass_pot1->SetMarkerColor(myRed);
	hEffMass_pot1->SetLineStyle(lineStyle);
	hEffMass_pot1->SetLineWidth(lineWidth);
	hEffMass_pot1->SetLineColor(myRed);
	
	hEffMass_pot0->Draw("P E1 X0");
	hEffMass_pot1->Draw("P E1 X0 same");
	
	TLegend* legEffMass = new TLegend(0.219198, 0.70913, 0.706304, 0.85138);
	legEffMass->AddEntry(hEffMass_pot0, "JAM2 w/o potential", "p");
	legEffMass->AddEntry(hEffMass_pot1, "JAM2 with potential", "p");
	legEffMass->Draw("same");
	
	cEffMass->SetLogy(0);
	
	// pty lpot0
	
	TCanvas* cPty_pot0 = new TCanvas();
	cPty_pot0->cd();
	
	hPty_pot0->SetTitle("Lambda pty; y_{0}; p_{t}");
	hPty_pot0->GetXaxis()->SetNdivisions(505);
	hPty_pot0->GetXaxis()->SetLabelSize(0.05);
	//hPty_pot0->GetXaxis()->SetLabelOffset(0.02);
	hPty_pot0->GetXaxis()->SetTitleSize(0.05);
	hPty_pot0->GetXaxis()->SetTitleOffset(1.15);
	
	hPty_pot0->GetYaxis()->SetNdivisions(505);
	hPty_pot0->GetYaxis()->SetLabelSize(0.05);
	//hPty_pot0->GetYaxis()->SetLabelOffset(0.07);
	hPty_pot0->GetYaxis()->SetTitleSize(0.05);
	hPty_pot0->GetYaxis()->SetTitleOffset(1.5);
	//hPty_pot0->GetYaxis()->SetRangeUser(-0.08, 0.08);
	
	// set markers and other details
	
	hPty_pot0->Draw("colz");
	//hEffMass_pot1->Draw("P E1 X0 same");
	
	
	// pty lpot1
	
	TCanvas* cPty_pot1 = new TCanvas();
	cPty_pot1->cd();
	
	hPty_pot1->SetTitle("Lambda pty; y_{0}; p_{t}");
	hPty_pot1->GetXaxis()->SetNdivisions(505);
	hPty_pot1->GetXaxis()->SetLabelSize(0.05);
	//hPty_pot1->GetXaxis()->SetLabelOffset(0.02);
	hPty_pot1->GetXaxis()->SetTitleSize(0.05);
	hPty_pot1->GetXaxis()->SetTitleOffset(1.15);
	
	hPty_pot1->GetYaxis()->SetNdivisions(505);
	hPty_pot1->GetYaxis()->SetLabelSize(0.05);
	//hPty_pot1->GetYaxis()->SetLabelOffset(0.07);
	hPty_pot1->GetYaxis()->SetTitleSize(0.05);
	hPty_pot1->GetYaxis()->SetTitleOffset(1.5);
	//hPty_pot1->GetYaxis()->SetRangeUser(-0.08, 0.08);
	
	// set markers and other details
	
	hPty_pot1->Draw("colz");
	//hEffMass_pot1->Draw("P E1 X0 same");
	
	fout->cd();
	
	cEffMass->Print(Form("PDF_" + codeNamePotOpt + "_runs_%i_to_%i.pdf(", run1, run2));
	cPty_pot0->Print(Form("PDF_" + codeNamePotOpt + "_runs_%i_to_%i.pdf(", run1, run2));
	cPty_pot1->Print(Form("PDF_" + codeNamePotOpt + "_runs_%i_to_%i.pdf(", run1, run2));
	cV1PtInt->Print(Form("PDF_" + codeNamePotOpt + "_runs_%i_to_%i.pdf", run1, run2));
	cV2PtInt->Print(Form("PDF_" + codeNamePotOpt + "_runs_%i_to_%i.pdf", run1, run2));
	cV1YInt->Print(Form("PDF_" + codeNamePotOpt + "_runs_%i_to_%i.pdf", run1, run2));
	cV2YInt->Print(Form("PDF_" + codeNamePotOpt + "_runs_%i_to_%i.pdf)", run1, run2));
	
	cEffMass->Write();
	cPty_pot0->Write();
	cPty_pot1->Write();
	cV1PtInt->Write();
	cV2PtInt->Write();
	cV1YInt->Write();
	cV2YInt->Write();
	
	fout->Save();
	fout->Close();
	
	return;
	
}
	
