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
void normalizeByBinWidth(TH1D *histo);

void draw_centDependency()
{ 
	gROOT->Macro("/afs/cern.ch/work/k/kyolee/private/cms442/src/JpsiStyle.C");
		
	static const double PDGJpsiM = 3.096916;
	static const double PDGpsi2M = 3.686111;
//	static const double Jpsi_CtMin = -1.5;
//	static const double Jpsi_CtMax = 3.0;

	// --- Import Trees
	// for Pbp
	TFile *inFilePbp=TFile::Open("/afs/cern.ch/work/k/kyolee/private/cms442/src/pAJpsi/outTree/Jpsi_v2.24_muLessPV_Histos_Runs_210498-211256.root");
	TTree *treePbp=(TTree*)inFilePbp->Get("myTree");
	// for pPb
	TFile *inFilepPb=TFile::Open("/afs/cern.ch/work/k/kyolee/private/cms442/src/pAJpsi/outTree/Jpsi_v2.24_muLessPV_Histos_Runs_211313-211631.root");
	TTree *treepPb=(TTree*)inFilepPb->Get("myTree");

	// hist name : 1.beamType(Pbp/pPb) 2. massRange ([2.95,3.25]/[3.53,3.83]) 3.xAxis (centrality/Ntrk/EtHF) 
	string histName[]={
		"pbp_Jpsi_cent", "pbp_psi2s_cent",
		"pbp_Jpsi_Ntrk", "pbp_psi2s_Ntrk", 
		"pbp_Jpsi_EtHF", "pbp_psi2s_EtHF",
		"ppb_Jpsi_cent", "ppb_psi2s_cent", 
		"ppb_Jpsi_Ntrk", "ppb_psi2s_Ntrk",
		"ppb_Jpsi_EtHF", "ppb_psi2s_EtHF"
	};
	string histTitle[]={
		"Pbp yields [2.95,3.25] MeV/c^{2}, y_cm<1.93;Centrality;Counts", 
		"Pbp yields [3.53,3.83] MeV/c^{2}, y_cm<1.93;Centrality;Counts", 
		"Pbp yields [2.95,3.25] MeV/c^{2}, y_cm<1.93;N_{tracks};Counts", 
		"Pbp yields [3.53,3.83] MeV/c^{2}, y_cm<1.93;N_{tracks};Counts", 
		"Pbp yields [2.95,3.25] MeV/c^{2}, y_cm<1.93;E_{T}^{HF |#eta|>4};Counts", 
		"Pbp yields [3.53,3.83] MeV/c^{2}, y_cm<1.93;E_{T}^{HF |#eta|>4};Counts", 
		"pPb yields [2.95,3.25] MeV/c^{2}, y_cm<1.93;Centrality;Counts", 
		"pPb yields [3.53,3.83] MeV/c^{2}, y_cm<1.93;Centrality;Counts", 
		"pPb yields [2.95,3.25] MeV/c^{2}, y_cm<1.93;N_{tracks};Counts", 
		"pPb yields [3.53,3.83] MeV/c^{2}, y_cm<1.93;N_{tracks};Counts", 
		"pPb yields [2.95,3.25] MeV/c^{2}, y_cm<1.93;E_{T}^{HF |#eta|>4};Counts", 
		"pPb yields [3.53,3.83] MeV/c^{2}, y_cm<1.93;E_{T}^{HF}|#eta|>4;Counts" 
	};
	// CUT : sglMu eta, trigSelection, dblMu oppositSign, dblMu Mass, dblMu pT, dblMu y, Reco_QQ_size
	// [0] : J/psi dbleMu&singluMu -2.4< y_lab(eta_lab) <1.47 for Pbp ( |y_cm| <1.93 ) 
	// [1] : psi2s dbleMu&singluMu -2.4< y_lab(eta_lab) <1.47 for Pbp 
	// [2] : J/psi dbleMu&singluMu -1.47< y_lab(eta_lab) <2.4 for pPb
	// [3] : psi2s dbleMu&singluMu -1.47< y_lab(eta_lab) <2.4 for pPb
	string condition[]= {
		"Reco_QQ_mupl_4mom->Eta()>-2.4 && Reco_QQ_mupl_4mom->Eta()<1.47 && Reco_QQ_mumi_4mom->Eta()>-2.4 && Reco_QQ_mumi_4mom->Eta()<1.47 && (Reco_QQ_trig&1)==1 && Reco_QQ_sign==0 && Reco_QQ_4mom->M()>2.95 && Reco_QQ_4mom->M()<3.25 && Reco_QQ_4mom->Pt()>6.5 && Reco_QQ_4mom->Pt()<30.0 && Reco_QQ_4mom->Rapidity()>-2.4 && Reco_QQ_4mom->Rapidity()<1.47 && Reco_QQ_size==1",
		"Reco_QQ_mupl_4mom->Eta()>-2.4 && Reco_QQ_mupl_4mom->Eta()<1.47 && Reco_QQ_mumi_4mom->Eta()>-2.4 && Reco_QQ_mumi_4mom->Eta()<1.47 && (Reco_QQ_trig&1)==1 && Reco_QQ_sign==0 && Reco_QQ_4mom->M()>3.53 && Reco_QQ_4mom->M()<3.83 && Reco_QQ_4mom->Pt()>6.5 && Reco_QQ_4mom->Pt()<30.0 && Reco_QQ_4mom->Rapidity()>-2.4 && Reco_QQ_4mom->Rapidity()<1.47 && Reco_QQ_size==1",
		"Reco_QQ_mupl_4mom->Eta()>-1.47 && Reco_QQ_mupl_4mom->Eta()<2.4 && Reco_QQ_mumi_4mom->Eta()>-1.47 && Reco_QQ_mumi_4mom->Eta()<2.4 && (Reco_QQ_trig&1)==1 && Reco_QQ_sign==0 && Reco_QQ_4mom->M()>2.95 && Reco_QQ_4mom->M()<3.25 && Reco_QQ_4mom->Pt()>6.5 && Reco_QQ_4mom->Pt()<30.0 && Reco_QQ_4mom->Rapidity()>-2.4 && Reco_QQ_4mom->Rapidity()<2.4 && Reco_QQ_size==1",
		"Reco_QQ_mupl_4mom->Eta()>-1.47 && Reco_QQ_mupl_4mom->Eta()<2.4 && Reco_QQ_mumi_4mom->Eta()>-1.47 && Reco_QQ_mumi_4mom->Eta()<2.4 && (Reco_QQ_trig&1)==1 && Reco_QQ_sign==0 && Reco_QQ_4mom->M()>3.53 && Reco_QQ_4mom->M()<3.83 && Reco_QQ_4mom->Pt()>6.5 && Reco_QQ_4mom->Pt()<30.0 && Reco_QQ_4mom->Rapidity()>-2.4 && Reco_QQ_4mom->Rapidity()<2.4 && Reco_QQ_size==1"
	};
	//int nBin[] = {80}; 
	const int nBin=30; 
	const int nMin[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	const int nMax[] = {100, 100, 300, 300, 250, 250, 100, 100, 300, 300, 250, 250};

	const int nHist = sizeof(histName)/sizeof(string);
	cout << " nHist = "<< nHist << endl; 

	// --- Define histograms
	TH1D * histCent[nHist];
	Int_t colorIndex;
	for (Int_t i=0; i<nHist; i++) {
		histCent[i] = new TH1D(histName[i].c_str(), histTitle[i].c_str(), nBin, nMin[i], nMax[i]);
		histCent[i]->Sumw2();
//		colorIndex=1;
		if (i%2==0) {colorIndex=1;} else {colorIndex=2;}
		cout << i<<"th colorIndex=" << colorIndex << endl;
		SetHistStyle(histCent[i],colorIndex,0);
//		histCent[i]->SetMinimum(0.1);
//		histCent[i]->SetMaximum(10000.0);
	//gPad->SetLogy(1);
	//histRatio[0]->SetMinimum(0.4);
	}

	// --- Draw Ct Error distribution
	//TCanvas c1; c1.cd();
	TCanvas* c1 = new TCanvas("c1","canvas",600,600);
	c1->cd();
	gPad->SetLogy(1);

	//draw the Text
	//TPaveText *text = new TPaveText(0.37, 0.15, 0.67, 0.35, "NDC"); // bottom middle
	TPaveText *text = new TPaveText(0.41, 0.15, 0.50, 0.30, "NDC"); // bottom middle small
	//TPaveText *text = new TPaveText(0.37, 0.67, 0.80, 0.90, "NDC"); // upper right
	SetTextStyle(text);

	//draw the Legends
	//TLegend *leg = new TLegend(0.50, 0.74, 0.80, 0.90); // upper right
	TLegend *leg = new TLegend(0.50, 0.78, 0.78, 0.90); // upper right
	SetLegendStyle(leg);

/*

	// 1.pbp_cent
	treePbp->Draw("Centrality>>pbp_Jpsi_cent", condition[0].c_str(),"e");
	treePbp->Draw("Centrality>>pbp_psi2s_cent", condition[1].c_str(),"esame");
	cout << "histogram entries =" << histCent[0]->GetEntries() <<endl;
	cout << "histogram entries =" << histCent[1]->GetEntries() <<endl;
//	text->AddText("Pbp (18/nb)");
//	text->AddText("-2.4 < y_{lab} < 1.47");
	text->AddText("|y_{cm}| < 1.93");
	text->AddText("6.5<p_{T}<30 GeV/c");
//	text->AddText("[2.95-3.25] GeV/c^{2}");
	text->AddText("HLT_PAL1DoubleMuOpen");
	text->Draw();	
	leg->SetHeader("Pbp (18/nb)");
	leg -> AddEntry(histCent[0],"[2.95-3.25] GeV/c^{2}","lp");
	leg -> AddEntry(histCent[1],"[3.53-3.83] GeV/c^{2}","lp");
	leg->Draw();
	c1->SaveAs(Form("%s.png",histName[0].c_str()));
	c1->Clear();
	text->Clear();
	leg->Clear();

	// 2.pbp_Ntrk
	treePbp->Draw("Ntracks>>pbp_Jpsi_Ntrk", condition[0].c_str(),"e");
	treePbp->Draw("Ntracks>>pbp_psi2s_Ntrk", condition[1].c_str(),"esame");
	cout << "histogram entries =" << histCent[2]->GetEntries() <<endl;
	cout << "histogram entries =" << histCent[3]->GetEntries() <<endl;
	text->AddText("|y_{cm}| < 1.93");
	text->AddText("6.5<p_{T}<30 GeV/c");
	text->AddText("HLT_PAL1DoubleMuOpen");
	text->Draw();	
	leg->SetHeader("Pbp (18/nb)");
	leg -> AddEntry(histCent[2],"[2.95-3.25] GeV/c^{2}","lp");
	leg -> AddEntry(histCent[3],"[3.53-3.83] GeV/c^{2}","lp");
	leg->Draw();
	c1->SaveAs(Form("%s.png",histName[2].c_str()));
	c1->Clear();
	text->Clear();
	leg->Clear();

*/

	// 3.pbp_EtHF
	treePbp->Draw("SumET_HFplusEta4+SumET_HFminusEta4>>pbp_Jpsi_EtHF", condition[0].c_str(),"e");
	treePbp->Draw("SumET_HFplusEta4+SumET_HFminusEta4>>pbp_psi2s_EtHF", condition[1].c_str(),"esame");
	cout << "histogram entries =" << histCent[4]->GetEntries() <<endl;
	cout << "histogram entries =" << histCent[5]->GetEntries() <<endl;
	text->AddText("|y_{cm}| < 1.93");
	text->AddText("6.5<p_{T}<30 GeV/c");
	text->AddText("HLT_PAL1DoubleMuOpen");
	text->Draw();	
	leg->SetHeader("Pbp (18/nb)");
	leg -> AddEntry(histCent[4],"[2.95-3.25] GeV/c^{2}","lp");
	leg -> AddEntry(histCent[5],"[3.53-3.83] GeV/c^{2}","lp");
	leg->Draw();
	c1->SaveAs(Form("%s.png",histName[4].c_str()));
	c1->Clear();
	text->Clear();
	leg->Clear();
/*
	// 4.ppb_cent
	treepPb->Draw("Centrality>>ppb_Jpsi_cent", condition[2].c_str(),"e");
	treepPb->Draw("Centrality>>ppb_psi2s_cent", condition[3].c_str(),"esame");
	cout << "histogram entries =" << histCent[6]->GetEntries() <<endl;
	cout << "histogram entries =" << histCent[7]->GetEntries() <<endl;
	text->AddText("|y_{cm}| < 1.93");
	text->AddText("6.5<p_{T}<30 GeV/c");
	text->AddText("HLT_PAL1DoubleMuOpen");
	text->Draw();	
	leg-> SetHeader("pPb (12/nb)");
	leg -> AddEntry(histCent[6],"[2.95-3.25] GeV/c^{2}","lp");
	leg -> AddEntry(histCent[7],"[3.53-3.83] GeV/c^{2}","lp");
	leg->Draw();
	c1->SaveAs(Form("%s.png",histName[6].c_str()));
	c1->Clear();
	text->Clear();
	leg->Clear();

	// 5.ppb_Ntrk
	treepPb->Draw("Ntracks>>ppb_Jpsi_Ntrk", condition[2].c_str(),"e");
	treepPb->Draw("Ntracks>>ppb_psi2s_Ntrk", condition[3].c_str(),"esame");
	cout << "histogram entries =" << histCent[8]->GetEntries() <<endl;
	cout << "histogram entries =" << histCent[9]->GetEntries() <<endl;
	text->AddText("pPb (12/nb)");
	text->AddText("|y_{cm}| < 1.93");
	text->AddText("6.5<p_{T}<30 GeV/c");
	text->AddText("HLT_PAL1DoubleMuOpen");
	text->Draw();	
	leg-> SetHeader("pPb (12/nb)");
	leg -> AddEntry(histCent[8],"[2.95-3.25] GeV/c^{2}","lp");
	leg -> AddEntry(histCent[9],"[3.53-3.83] GeV/c^{2}","lp");
	leg->Draw();
	c1->SaveAs(Form("%s.png",histName[8].c_str()));
	c1->Clear();
	text->Clear();
	leg->Clear();
*/
	// 6.ppb_EtHF
	treepPb->Draw("SumET_HFplusEta4+SumET_HFminusEta4>>ppb_Jpsi_EtHF", condition[2].c_str(),"e");
	treepPb->Draw("SumET_HFplusEta4+SumET_HFminusEta4>>ppb_psi2s_EtHF", condition[3].c_str(),"esame");
	cout << "histogram entries =" << histCent[10]->GetEntries() <<endl;
	cout << "histogram entries =" << histCent[11]->GetEntries() <<endl;
	text->AddText("|y_{cm}| < 1.93");
	text->AddText("6.5<p_{T}<30 GeV/c");
	text->AddText("HLT_PAL1DoubleMuOpen");
	text->Draw();	
	leg-> SetHeader("pPb (12/nb)");
	leg -> AddEntry(histCent[10],"[2.95-3.25] GeV/c^{2}","lp");
	leg -> AddEntry(histCent[11],"[3.53-3.83] GeV/c^{2}","lp");
	leg->Draw();
	c1->SaveAs(Form("%s.png",histName[10].c_str()));
	c1->Clear();
	text->Clear();
	leg->Clear();

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

void normalizeByBinWidth(TH1D *histo) {
	for(int i = 1; i <= histo->GetNbinsX(); i++) {
		float content = histo->GetBinContent(i);
		float error = histo->GetBinError(i);
		histo->SetBinContent(i,content/histo->GetBinWidth(i));
		histo->SetBinError(i,error/histo->GetBinWidth(i));
	}
}


