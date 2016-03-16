#include <iostream>
#include <math.h>
#include <fstream>

#include <TROOT.h>
#include "TSystem.h"
#include <TFile.h>
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

void ctau_Yasym()
{ 
	gROOT->Macro("/afs/cern.ch/work/k/kyolee/private/cms442/src/JpsiStyle.C");
		
	static const double PDGJpsiM = 3.096916;
	static const double Jpsi_CtMin = -1.5;
	static const double Jpsi_CtMax = 3.0;

	// --- Import Trees
	// for Pbp
	TFile *inFilePbp=TFile::Open("/afs/cern.ch/work/k/kyolee/private/cms442/src/pAJpsi_YasymAnal/Jpsi_Histos_Runs_210498-211256.root");
	TTree *treePbp=(TTree*)inFilePbp->Get("myTree");
	// for pPb
	TFile *inFilepPb=TFile::Open("/afs/cern.ch/work/k/kyolee/private/cms442/src/pAJpsi_YasymAnal/Jpsi_Histos_Runs_211313-211631.root");
	TTree *treepPb=(TTree*)inFilepPb->Get("myTree");
	// for pp
	TFile *inFilepp=TFile::Open("/afs/cern.ch/work/k/kyolee/private/cms442/src/pAJpsi_YasymAnal/All_v2.24_Histos_Runs_211739-211831_woPileUpRej_muLessPV.root");
	TTree *treepp=(TTree*)inFilepp->Get("myTree");
	

	// hist name : 1.beamType(Pbp/pPb) 2.rapidityRange(y>0/y<0) 3.mass(JpsiPDGValue/DiMuonInvariantMass)
	string histName[]={"pbp_pos_pdg", "pbp_neg_pdg", "pbp_pos_inv", "pbp_neg_inv",
										"ppb_pos_pdg", "ppb_neg_pdg", "ppb_pos_inv", "ppb_neg_inv",
										"pp_pos_pdg", "pp_neg_pdg","pp_pos_inv","pp_neg_inv"};
	string histTitle[]={
		"Pbp l_{J/#psi} y>0 w/ J/#psi PDG mass;l_{J/#psi} [mm];Events (0.1125 mm)", 
		"Pbp_l_{J/#psi} y<0 w/ J/#psi PDG mass;l_{J/#psi} [mm];Events (0.1125 mm)",
		"Pbp l_{J/#psi} y>0 w/ dimuon Invariant mass;l_{J/#psi} [mm];Events (0.1125 mm)", 
		"Pbp_l_{J/#psi} y<0 w/ dimuon Invariant mass;l_{J/#psi} [mm];Events (0.1125 mm)",
		"pPb l_{J/#psi} y>0 w/ J/#psi PDG mass;l_{J/#psi} [mm];Events (0.1125 mm)", 
		"pPb l_{J/#psi} y<0 w/ J/#psi PDG mass;l_{J/#psi} [mm];Events (0.1125 mm)", 
		"pPb l_{J/#psi} y>0 w/ dimuon Invariant mass;l_{J/#psi} [mm];Events (0.1125 mm)", 
		"pPb l_{J/#psi} y<0 w/ dimuon Invariant mass;l_{J/#psi} [mm];Events (0.1125 mm)", 
		"pp l_{J/#psi} y>0 w/ J/#psi PDG mass;l_{J/#psi} [mm];Events (0.1125 mm)", 
		"pp l_{J/#psi} y<0 w/ J/#psi PDG mass;l_{J/#psi} [mm];Events (0.1125 mm)", 
		"pp l_{J/#psi} y>0 w/ dimuon Invariant mass;l_{J/#psi} [mm];Events (0.1125 mm)", 
		"pp l_{J/#psi} y<0 w/ dimuon Invariant mass;l_{J/#psi} [mm];Events (0.1125 mm)", 
	};
	// CUT : sglMu eta, trigSelection, dblMu oppositSign, dblMu Mass, dlbMu Ct, dblMu pT, dblMu y
	// all the cuts are the same except for dblMu [0]:y>0 ,[1]:y<0
	string condition[]= {
		"Reco_QQ_mupl_4mom->Eta()>-2.4 && Reco_QQ_mupl_4mom->Eta()<2.4 && Reco_QQ_mumi_4mom->Eta()>-2.4 && Reco_QQ_mumi_4mom->Eta()<2.4 && (Reco_QQ_trig&1)==1 && Reco_QQ_sign==0 && Reco_QQ_4mom->M()>2.6 && Reco_QQ_4mom->M()<3.5 && Reco_QQ_ctau>-1.5 && Reco_QQ_ctau<3.0 && Reco_QQ_4mom->Pt()>6.5 && Reco_QQ_4mom->Pt()<30.0 && Reco_QQ_4mom->Rapidity()>0.0 && Reco_QQ_4mom->Rapidity()<2.4",
		"Reco_QQ_mupl_4mom->Eta()>-2.4 && Reco_QQ_mupl_4mom->Eta()<2.4 && Reco_QQ_mumi_4mom->Eta()>-2.4 && Reco_QQ_mumi_4mom->Eta()<2.4 && (Reco_QQ_trig&1)==1 && Reco_QQ_sign==0 && Reco_QQ_4mom->M()>2.6 && Reco_QQ_4mom->M()<3.5 && Reco_QQ_ctau>-1.5 && Reco_QQ_ctau<3.0 && Reco_QQ_4mom->Pt()>6.5 && Reco_QQ_4mom->Pt()<30.0 && Reco_QQ_4mom->Rapidity()>-2.4 && Reco_QQ_4mom->Rapidity()<0.0",
	};

	//int nBin[] = {80}; 
	int nBin=40; 

	const int nHist = sizeof(histName)/sizeof(string);
	cout << " nHist = "<< nHist << endl; 

	// --- Define histograms
	TH1D * histCt[nHist];
	Int_t colorIndex;
	for (Int_t i=0; i<nHist; i++) {
		histCt[i] = new TH1D(histName[i].c_str(), histTitle[i].c_str(), nBin, Jpsi_CtMin, Jpsi_CtMax);
		histCt[i]->Sumw2();
		if (i%2==0) {colorIndex=1;} else {colorIndex=2;}
		cout << i<<"th colorIndex=" << colorIndex << endl;
		SetHistStyle(histCt[i],colorIndex,0);
	}

	// --- Draw Ct distribution
	//TCanvas c1; c1.cd();
	TCanvas* c1 = new TCanvas("c1","canvas",600,600);
	c1->cd();
	gPad->SetLogy(1);

	//draw the Text
	//TPaveText *text = new TPaveText(0.50, 0.74, 0.80, 0.90, "NDC"); // upper right
	TPaveText *text = new TPaveText(0.37, 0.15, 0.67, 0.35, "NDC"); // bottom middle
	SetTextStyle(text);
	//TPaveText *text2 = new TPaveText(0.35, 0.01, 0.70, 0.15, "NDC"); // most bottom
	TPaveText *text2 = new TPaveText(0.59, 0.64, 0.80, 0.73, "NDC"); // most bottom
	text2->SetFillColor(0);
	text2->SetFillStyle(4000);
	text2->SetBorderSize(0);
	text2->SetMargin(0.2);	
	text2->SetTextSize(0.045);
	text2->SetTextColor(kRed);

	//draw the Legends
	//TLegend *leg = new TLegend(0.35, 0.17, 0.75, 0.33); // bottom middle
	TLegend *leg = new TLegend(0.55, 0.74, 0.80, 0.90); // upper right
	SetLegendStyle(leg);

	// 1.pbp_pdg (hist0,1)
	treePbp->Draw("Reco_QQ_ctau>>pbp_pos_pdg", condition[0].c_str(),"e");
	treePbp->Draw("Reco_QQ_ctau>>pbp_neg_pdg", condition[1].c_str(),"esame");
	cout << "histogram entries =" << histCt[0]->GetEntries() <<endl;
	cout << "histogram entries =" << histCt[1]->GetEntries() <<endl;
	text->AddText("Trk-Trk");
	text->AddText("[2.6-3.5] GeV/c^{2}");
	text->AddText("6.5<p_{T}<30 GeV/c");
	text->AddText("HLT_PAL1DoubleMuOpen");
	text->Draw();	
	text2->AddText("Lifetime with");
	text2->AddText("J/#psi PDG mass");
	text2->Draw();
	leg->SetHeader("Pbp (18/nb)");
	leg -> AddEntry(histCt[0],"0 < y_{lab} < 2.4","lp");
	leg -> AddEntry(histCt[1],"-2.4 < y_{lab} < 0","lp");
	leg->Draw();
	//c1->SaveAs(Form("%s.png",histName[0].c_str()));
	c1->SaveAs("pbp_pdg.pdf");
	c1->Clear();
	text->Clear();
	text2->Clear();
	leg->Clear();

	// 2.pbp_inv (hist2,3)
	treePbp->Draw("(Reco_QQ_ctau*(Reco_QQ_4mom->M())/3.096916)>>pbp_pos_inv", condition[0].c_str(),"e");
	treePbp->Draw("(Reco_QQ_ctau*(Reco_QQ_4mom->M())/3.096916)>>pbp_neg_inv", condition[1].c_str(),"esame");
	cout << "histogram entries =" << histCt[2]->GetEntries() <<endl;
	cout << "histogram entries =" << histCt[3]->GetEntries() <<endl;
	text->AddText("Trk-Trk");
	text->AddText("[2.6-3.5] GeV/c^{2}");
	text->AddText("6.5<p_{T}<30 GeV/c");
	text->AddText("HLT_PAL1DoubleMuOpen");
	text->Draw();	
	text2->AddText("Lifetime with");
	text2->AddText("dimuon invariant mass");
	text2->Draw();
	leg->SetHeader("Pbp (18/nb)");
	leg -> AddEntry(histCt[2],"0 < y_{lab} < 2.4","lp");
	leg -> AddEntry(histCt[3],"-2.4 < y_{lab} < 0","lp");
	leg->Draw();
	c1->SaveAs("pbp_inv.pdf");
	c1->Clear();
	text->Clear();
	text2->Clear();
	leg->Clear();

	// 3.ppb_pdg (hist4,5)
	treepPb->Draw("Reco_QQ_ctau>>ppb_pos_pdg", condition[0].c_str(),"e");
	treepPb->Draw("Reco_QQ_ctau>>ppb_neg_pdg", condition[1].c_str(),"esame");
	cout << "histogram entries =" << histCt[4]->GetEntries() <<endl;
	cout << "histogram entries =" << histCt[5]->GetEntries() <<endl;
	text->AddText("Trk-Trk");
	text->AddText("[2.6-3.5] GeV/c^{2}");
	text->AddText("6.5<p_{T}<30 GeV/c");
	text->AddText("HLT_PAL1DoubleMuOpen");
	text->Draw();	
	text2->AddText("Lifetime with");
	text2->AddText("J/#psi PDG mass");
	text2->Draw();
	leg->SetHeader("pPb (12/nb)");
	leg -> AddEntry(histCt[4],"0 < y_{lab} < 2.4","lp");
	leg -> AddEntry(histCt[5],"-2.4 < y_{lab} < 0","lp");
	leg->Draw();
	c1->SaveAs("ppb_pdg.pdf");
	c1->Clear();
	text->Clear();
	text2->Clear();
	leg->Clear();

	// 4.ppb_inv (hist,6, 7)
	treepPb->Draw("(Reco_QQ_ctau*(Reco_QQ_4mom->M())/3.096916)>>ppb_pos_inv", condition[0].c_str(),"e");
	treepPb->Draw("(Reco_QQ_ctau*(Reco_QQ_4mom->M())/3.096916)>>ppb_neg_inv", condition[1].c_str(),"esame");
	cout << "histogram entries =" << histCt[6]->GetEntries() <<endl;
	cout << "histogram entries =" << histCt[7]->GetEntries() <<endl;
	text->AddText("Trk-Trk");
	text->AddText("[2.6-3.5] GeV/c^{2}");
	text->AddText("6.5<p_{T}<30 GeV/c");
	text->AddText("HLT_PAL1DoubleMuOpen");
	text->Draw();	
	text2->AddText("Lifetime with");
	text2->AddText("dimuon invariant mass");
	text2->Draw();
	leg->SetHeader("pPb (12/nb)");
	leg -> AddEntry(histCt[6],"0 < y_{lab} < 2.4","lp");
	leg -> AddEntry(histCt[7],"-2.4 < y_{lab} < 0","lp");
	leg->Draw();
	c1->SaveAs("ppb_inv.pdf");
	c1->Clear();
	text->Clear();
	text2->Clear();
	leg->Clear();

	// 5.pp_pdg (hist8,9)
	treepp->Draw("Reco_QQ_ctau>>pp_pos_pdg", condition[0].c_str(),"e");
	treepp->Draw("Reco_QQ_ctau>>pp_neg_pdg", condition[1].c_str(),"esame");
	cout << "histogram entries =" << histCt[8]->GetEntries() <<endl;
	cout << "histogram entries =" << histCt[9]->GetEntries() <<endl;
	text->AddText("Trk-Trk");
	text->AddText("[2.6-3.5] GeV/c^{2}");
	text->AddText("6.5<p_{T}<30 GeV/c");
	text->AddText("HLT_PAL1DoubleMuOpen");
	text->Draw();	
	text2->AddText("Lifetime with");
	text2->AddText("J/#psi PDG mass");
	text2->Draw();
	leg->SetHeader("pp (5/pb)");
	leg -> AddEntry(histCt[8],"0 < y_{lab} < 2.4","lp");
	leg -> AddEntry(histCt[9],"-2.4 < y_{lab} < 0","lp");
	leg->Draw();
	c1->SaveAs("pp_pdg.pdf");
	c1->Clear();
	text->Clear();
	text2->Clear();
	leg->Clear();

	// 6.pp_inv (hist,10,11)
	treepp->Draw("(Reco_QQ_ctau*(Reco_QQ_4mom->M())/3.096916)>>pp_pos_inv", condition[0].c_str(),"e");
	treepp->Draw("(Reco_QQ_ctau*(Reco_QQ_4mom->M())/3.096916)>>pp_neg_inv", condition[1].c_str(),"esame");
	cout << "histogram entries =" << histCt[10]->GetEntries() <<endl;
	cout << "histogram entries =" << histCt[11]->GetEntries() <<endl;
	text->AddText("Trk-Trk");
	text->AddText("[2.6-3.5] GeV/c^{2}");
	text->AddText("6.5<p_{T}<30 GeV/c");
	text->AddText("HLT_PAL1DoubleMuOpen");
	text->Draw();	
	text2->AddText("Lifetime with");
	text2->AddText("dimuon invariant mass");
	text2->Draw();
	leg->SetHeader("pp (5/pb)");
	leg -> AddEntry(histCt[10],"0 < y_{lab} < 2.4","lp");
	leg -> AddEntry(histCt[11],"-2.4 < y_{lab} < 0","lp");
	leg->Draw();
	c1->SaveAs("pp_inv.pdf");
	c1->Clear();
	text->Clear();
	text2->Clear();
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
	l->SetFillStyle(4000); //transparent
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
}
