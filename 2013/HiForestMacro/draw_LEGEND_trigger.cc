#include <Riostream.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TDirectory.h>
#include <TLegend.h>
 
#include <sstream>
#include <string>

using namespace std;
void SetHistStyle(TH1* h, int i) ;
void SetLegendStyle(TLegend* l);

void draw_LEGEND_trigger()
{
	//Set style
	gROOT->Macro("/afs/cern.ch/user/k/kyolee/private/cms538HI_test/src/01_SimpleHist/styleTH1D.C"); 

	//draw histograms
	string histName[] ={
		"All_Global_muons",
		"HLT_PAL1DoubleMuOpen_v1", 
		"HLT_PAL1DoubleMu0_HighQ_v1", 
		"HLT_PAL2DoubleMu3_v1", 
		"HLT_PAPxlTrkMulti100_L2DouMu3_v1", 
		"HLT_PAMu3_v1", 
		"HLT_PAMu7_v1", 
		"HLT_PAMu12_v1" 
	};
	string histTitle = "Glb_pt;Global muon p_{T} [GeV/c];Counts";
	const Int_t nBins = 60;
	const Double_t xMin = 0.;
	const Double_t xMax = 30.;

	const int nHist = sizeof(histName)/sizeof(string);
	cout<< "nHist = " << nHist << endl;

	TH1D *hist1D[nHist];	

	for(Int_t i=0; i<nHist; i++){
		hist1D[i] = new TH1D(histName[i].c_str(),histTitle.c_str(),nBins,xMin,xMax);
		SetHistStyle(hist1D[i],i);
		hist1D[i]->Sumw2();
	}

	TLegend *leg = new TLegend(0.05,0.45,0.90,0.95);
	SetLegendStyle(leg);

	for (Int_t i=0; i<nHist; i++) {
		leg->AddEntry(hist1D[i],histName[i].c_str(),"lp");
	}

	TCanvas* c1 = new TCanvas();
	c1->cd(); 
	leg->Draw();
	
	c1->SaveAs("LEGEND_trigger_single_double.pdf");

	return;
}

void SetHistStyle(TH1* h, int i) {
	//  int colorArr[6] = {kBlack, kBlue, kRed, kGreen+2, kOrange, kMagenta+2};
	//  int colorArr[] = {kGray+2, kBlack, kRed, kRed+2, kOrange+1, kOrange+8, kGreen+2, kGreen+4, kAzure+1, kAzure+3, kViolet+5, kViolet+3, kMagenta, kMagenta+2};
	//int colorArr[] = { kBlack, kRed+1, kOrange+1, kOrange-8, kGreen+2, kAzure+1, kBlue+2, kViolet+5, kViolet-4, kMagenta, kMagenta+2};
	int colorArr[] = { kBlack, kGreen+2, kAzure+1, kViolet+5, kMagenta, kRed+1, kOrange+1, kBlue+2};
	int markerFullArr[6] = {kFullCircle, kFullSquare, kFullTriangleUp, kFullTriangleDown, kFullStar, kFullDiamond};
	int markerOpenArr[6] = {kOpenCircle, kOpenSquare, kOpenTriangleUp, kOpenTriangleDown, kOpenStar, kOpenDiamond};
				  
	h->SetLineColor(colorArr[i]);
	//h->SetLineWidth(2.4);
	h->SetMarkerColor(colorArr[i]);
	h->SetMarkerStyle(kFullCircle);
	//  if (i < 10)  h->SetMarkerStyle(markerFullArr[i]);
	//  else h->SetMarkerStyle(markerOpenArr[i-10]);
	h->SetMarkerSize(1.1);

	return;
}

void SetLegendStyle(TLegend* l) {
 	l->SetFillColor(0);
	l->SetFillStyle(4100);
//	l->SetFillStyle(4000); //transparent
//	l->SetBorderSize(1);
	l->SetBorderSize(0);
	l->SetMargin(0.1);
}

