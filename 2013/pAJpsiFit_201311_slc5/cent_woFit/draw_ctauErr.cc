#include <iostream>
#include <math.h>
#include <fstream>

#include <TROOT.h>
#include "TSystem.h"
#include <TFile.h>
#include <TTree.h>
#include <TGraphErrors.h>
#include <TVector3.h>
#include "TH1.h"
#include <TH1D.h>
#include "TLorentzVector.h"
#include "TRandom3.h"
#include "TClonesArray.h"
#include "TChain.h"

#include <TCanvas.h>
#include "TStyle.h"
#include <TPaveStats.h>
#include <TLegend.h>

#include <sstream>

using namespace std;
void SetHistStyle(TH1* h, Int_t c, Int_t m);
void SetLegendStyle(TLegend* l);
void SetTextStyle(TPaveText* t);

void draw_ctauErr()
{ 
	gROOT->Macro("/afs/cern.ch/work/k/kyolee/private/cms442/src/JpsiStyle.C");
		
	static const double PDGJpsiM = 3.096916;
//	static const double Jpsi_CtMin = -1.5;
//	static const double Jpsi_CtMax = 3.0;
	static const double Jpsi_CtErrMin = -0.0;
	static const double Jpsi_CtErrMax = 0.4;

	// --- Import Trees
	// for Pbp
	TFile *inFilePbp=TFile::Open("/afs/cern.ch/work/k/kyolee/private/cms442/src/pAJpsi/outTree/Jpsi_v2.24_muLessPV_Histos_Runs_210498-211256.root");
	TTree *treePbp=(TTree*)inFilePbp->Get("myTree");
	// for pPb
	TFile *inFilepPb=TFile::Open("/afs/cern.ch/work/k/kyolee/private/cms442/src/pAJpsi/outTree/Jpsi_v2.24_muLessPV_Histos_Runs_211313-211631.root");
	TTree *treepPb=(TTree*)inFilepPb->Get("myTree");


	// hist name : 1.beamType(Pbp/pPb) 2.rapidityRange(y>0/y<0) 
	//3.sideband region(low=2.6-2.9/high=3.3-3.5 MeV/c^2) 4.mass(JpsiPDGValue/DiMuonInvariantMass)
	string histName[]={
		"pbp_ctauErr", "ppb_ctauErr"
	};
	string histTitle[]={
		"Pbp CtErr for integrated region ([2.6,3.5] MeV/c^{2}, [6.5,30]GeV/c, y[0,2.4];Ctau Error [mm];Counts", 
		"pPb CtErr for integrated region ([2.6,3.5] MeV/c^{2}, [6.5,30]GeV/c, y[0,2.4];Ctau Error [mm];Counts", 
	};
	string condition[]= {
		"Reco_QQ_mupl_4mom->Eta()>-2.4 && Reco_QQ_mupl_4mom->Eta()<2.4 && Reco_QQ_mumi_4mom->Eta()>-2.4 && Reco_QQ_mumi_4mom->Eta()<2.4 && (Reco_QQ_trig&1)==1 && Reco_QQ_sign==0 && Reco_QQ_4mom->M()>2.6 && Reco_QQ_4mom->M()<3.5 && Reco_QQ_ctau>-1.5 && Reco_QQ_ctau<3.0 && Reco_QQ_4mom->Pt()>6.5 && Reco_QQ_4mom->Pt()<30.0 && Reco_QQ_4mom->Rapidity()>-2.4 && Reco_QQ_4mom->Rapidity()<2.4"
	};
	//int nBin[] = {80}; 
	int nBin=50; 

	const int nHist = sizeof(histName)/sizeof(string);
	cout << " nHist = "<< nHist << endl; 

	// --- Define histograms
	TH1D * histCtErr[nHist];
	Int_t colorIndex;
	for (Int_t i=0; i<nHist; i++) {
		histCtErr[i] = new TH1D(histName[i].c_str(), histTitle[i].c_str(), nBin, Jpsi_CtErrMin, Jpsi_CtErrMax);
//		histCtErr[i]->Sumw2();
		colorIndex=0;
//		if (i%2==0) {colorIndex=3;} else {colorIndex=4;}
//		cout << i<<"th colorIndex=" << colorIndex << endl;
		SetHistStyle(histCtErr[i],colorIndex,0);
	}

	// --- Draw Ct Error distribution
	//TCanvas c1; c1.cd();
	TCanvas* c1 = new TCanvas("c1","canvas",600,600);
	c1->cd();
	gPad->SetLogy(1);

	//draw the Text
	//TPaveText *text = new TPaveText(0.37, 0.15, 0.67, 0.35, "NDC"); // bottom middle
	//TPaveText *text = new TPaveText(0.41, 0.15, 0.50, 0.30, "NDC"); // bottom middle small
	TPaveText *text = new TPaveText(0.37, 0.67, 0.80, 0.90, "NDC"); // upper right
	SetTextStyle(text);

	//draw the Legends
	TLegend *leg = new TLegend(0.50, 0.74, 0.80, 0.90); // upper right
	SetLegendStyle(leg);

	// 1.pbp_loose_cut
	treePbp->Draw("Reco_QQ_ctauErr>>pbp_ctauErr", condition[0].c_str(),"");
//	treePbp->Draw("Reco_QQ_ctauErr>>pbp_ctauErr", condition[0].c_str(),"e");
	cout << "histogram entries =" << histCtErr[0]->GetEntries() <<endl;
	text->AddText("Pbp (18/nb)");
	text->AddText("-2.4 < y_{lab} < 2.4");
	text->AddText("6.5<p_{T}<30 GeV/c");
	text->AddText("[2.6-3.5] GeV/c^{2}");
	text->AddText("HLT_PAL1DoubleMuOpen");
	text->Draw();	
	//leg -> AddEntry(histCtErr[0],"[2.6-2.9] GeV/c^{2}","lp");
	//leg -> AddEntry(histCtErr[1],"[3.3-3.5] GeV/c^{2}","lp");
	//leg->Draw();
	c1->SaveAs(Form("%s.png",histName[0].c_str()));
	c1->Clear();
	text->Clear();
	//leg->Clear();

	// 2.ppb_loose_cut
	treepPb->Draw("Reco_QQ_ctauErr>>ppb_ctauErr", condition[0].c_str(),"");
//	treepPb->Draw("Reco_QQ_ctau>>ppb_ctauErr", condition[0].c_str(),"e");
	cout << "histogram entries =" << histCtErr[1]->GetEntries() <<endl;
	text->AddText("pPb (12/nb)");
	text->AddText("-2.4 < y_{lab} < 2.4");
	text->AddText("6.5<p_{T}<30 GeV/c");
	text->AddText("[2.6-3.5] GeV/c^{2}");
	text->AddText("HLT_PAL1DoubleMuOpen");
	text->Draw();	
	//leg -> AddEntry(histCtErr[2],"[2.6-2.9] GeV/c^{2}","lp");
	//leg -> AddEntry(histCtErr[3],"[3.3-3.5] GeV/c^{2}","lp");
	//leg->Draw();
	c1->SaveAs(Form("%s.png",histName[1].c_str()));
	c1->Clear();
	text->Clear();
	//leg->Clear();

	return;
}

void SetHistStyle(TH1* h, Int_t c, Int_t m) {
	Int_t colorArr[] = { kGray+3, kRed-4, kBlue, kOrange+7, kGreen+3, kAzure+8, kViolet-4, kBlack };
	//Int_t colorArr[] = { kGray+3, kRed-4, kBlue, kOrange+1, kGreen-3, kAzure+8, kViolet-4, kBlack };
	Int_t markerFullArr[] = {kFullCircle, kFullTriangleUp, kFullTriangleDown, kFullSquare};
	//Int_t markerOpenArr[] = {kOpenCircle, kOpenTriangleUp, kOpenTriangleDown, kOpenSquare};

	h-> SetMarkerColor(colorArr[c]);
	h-> SetMarkerStyle(markerFullArr[m]);
	h-> SetMarkerSize(1.2);
	h-> SetLineColor(colorArr[c]);
	h-> SetLineWidth(1.8);
}

void SetLegendStyle(TLegend* l) {
	l->SetFillColor(0);
	l->SetFillStyle(4000); //transparent (not for PDF)
	l->SetBorderSize(0);
	l->SetMargin(0.2);
	l->SetTextSize(0.040);
}

void SetTextStyle(TPaveText* t) {
	t->SetFillColor(0);
	t->SetFillStyle(4000);
	t->SetBorderSize(0);
	t->SetMargin(0.2);
	t->SetTextSize(0.035);
	//t->SetTextSize(0.026);
}
