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

void ctau_sideband()
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
	
	// hist name : 1.beamType(Pbp/pPb) 2.rapidityRange(y>0/y<0) 
	//3.sideband region(low=2.6-2.9/high=3.3-3.5 MeV/c^2) 4.mass(JpsiPDGValue/DiMuonInvariantMass)
	string histName[]={
		"pbp_pos_low_pdg", "pbp_pos_high_pdg", "pbp_neg_low_pdg", "pbp_neg_high_pdg",
		"pbp_pos_low_inv", "pbp_pos_high_inv", "pbp_neg_low_inv", "pbp_neg_high_inv",
		"ppb_pos_low_pdg", "ppb_pos_high_pdg", "ppb_neg_low_pdg", "ppb_neg_high_pdg", 
		"ppb_pos_low_inv", "ppb_pos_high_inv", "ppb_neg_low_inv", "ppb_neg_high_inv",
		"pp_pos_low_pdg", "pp_pos_high_pdg", "pp_neg_low_pdg", "pp_neg_high_pdg", 
		"pp_pos_low_inv", "pp_pos_high_inv", "pp_neg_low_inv", "pp_neg_high_inv"
	};
	string histTitle[]={
		"Pbp l_{J/#psi} y>0 w/ J/#psi PDG mass in [2.6,2.9] MeV/c^{2};l_{J/#psi} [mm];Events (0.1125 mm)", 
		"Pbp l_{J/#psi} y>0 w/ J/#psi PDG mass in [3.3,3.5] MeV/c^{2};l_{J/#psi} [mm];Events (0.1125 mm)", 
		"Pbp_l_{J/#psi} y<0 w/ J/#psi PDG mass in [2.6,2.9] MeV/c^{2};l_{J/#psi} [mm];Events (0.1125 mm)",
		"Pbp_l_{J/#psi} y<0 w/ J/#psi PDG mass in [3.3,3.5] MeV/c^{2};l_{J/#psi} [mm];Events (0.1125 mm)",
		"Pbp l_{J/#psi} y>0 w/ dimuon Invariant mass in [2.6,2.9] MeV/c^{2};l_{J/#psi} [mm];Events (0.1125 mm)", 
		"Pbp l_{J/#psi} y>0 w/ dimuon Invariant mass in [3.3,3.5] MeV/c^{2};l_{J/#psi} [mm];Events (0.1125 mm)", 
		"Pbp_l_{J/#psi} y<0 w/ dimuon Invariant mass in [2.6,2.9] MeV/c^{2};l_{J/#psi} [mm];Events (0.1125 mm)",
		"Pbp_l_{J/#psi} y<0 w/ dimuon Invariant mass in [3.3,3.5] MeV/c^{2};l_{J/#psi} [mm];Events (0.1125 mm)",
		"pPb l_{J/#psi} y>0 w/ J/#psi PDG mass in [2.6,2.9] MeV/c^{2};l_{J/#psi} [mm];Events (0.1125 mm)", 
		"pPb l_{J/#psi} y>0 w/ J/#psi PDG mass in [3.3,3.5] MeV/c^{2};l_{J/#psi} [mm];Events (0.1125 mm)", 
		"pPb l_{J/#psi} y<0 w/ J/#psi PDG mass in [2.6,2.9] MeV/c^{2};l_{J/#psi} [mm];Events (0.1125 mm)", 
		"pPb l_{J/#psi} y<0 w/ J/#psi PDG mass in [3.3,3.5] MeV/c^{2};l_{J/#psi} [mm];Events (0.1125 mm)", 
		"pPb l_{J/#psi} y>0 w/ dimuon Invariant mass in [2.6,2.9] MeV/c^{2};l_{J/#psi} [mm];Events (0.1125 mm)", 
		"pPb l_{J/#psi} y>0 w/ dimuon Invariant mass in [3.3,3.5] MeV/c^{2};l_{J/#psi} [mm];Events (0.1125 mm)", 
		"pPb l_{J/#psi} y<0 w/ dimuon Invariant mass in [2.6,2.9] MeV/c^{2};l_{J/#psi} [mm];Events (0.1125 mm)", 
		"pPb l_{J/#psi} y<0 w/ dimuon Invariant mass in [3.3,3.5] MeV/c^{2};l_{J/#psi} [mm];Events (0.1125 mm)",
		"pp l_{J/#psi} y>0 w/ J/#psi PDG mass in [2.6,2.9] MeV/c^{2};l_{J/#psi} [mm];Events (0.1125 mm)", 
		"pp l_{J/#psi} y>0 w/ J/#psi PDG mass in [3.3,3.5] MeV/c^{2};l_{J/#psi} [mm];Events (0.1125 mm)", 
		"pp l_{J/#psi} y<0 w/ J/#psi PDG mass in [2.6,2.9] MeV/c^{2};l_{J/#psi} [mm];Events (0.1125 mm)", 
		"pp l_{J/#psi} y<0 w/ J/#psi PDG mass in [3.3,3.5] MeV/c^{2};l_{J/#psi} [mm];Events (0.1125 mm)", 
		"pp l_{J/#psi} y>0 w/ dimuon Invariant mass in [2.6,2.9] MeV/c^{2};l_{J/#psi} [mm];Events (0.1125 mm)", 
		"pp l_{J/#psi} y>0 w/ dimuon Invariant mass in [3.3,3.5] MeV/c^{2};l_{J/#psi} [mm];Events (0.1125 mm)", 
		"pp l_{J/#psi} y<0 w/ dimuon Invariant mass in [2.6,2.9] MeV/c^{2};l_{J/#psi} [mm];Events (0.1125 mm)", 
		"pp l_{J/#psi} y<0 w/ dimuon Invariant mass in [3.3,3.5] MeV/c^{2};l_{J/#psi} [mm];Events (0.1125 mm)" 
	};
	// CUT : sglMu eta, trigSelection, dblMu oppositSign, dblMu Mass, dlbMu Ct, dblMu pT, dblMu y
	// [0] : dbleMu y>0 && [2.6,2.9] MeV/c^{2}
	// [1] : dbleMu y>0 && [3.3,3.5] MeV/c^{2}
	// [2] : dbleMu y<0 && [2.6,2.9] MeV/c^{2}
	// [3] : dbleMu y<0 && [3.3,3.5] MeV/c^{2}
	string condition[]= {
		"Reco_QQ_mupl_4mom->Eta()>-2.4 && Reco_QQ_mupl_4mom->Eta()<2.4 && Reco_QQ_mumi_4mom->Eta()>-2.4 && Reco_QQ_mumi_4mom->Eta()<2.4 && (Reco_QQ_trig&1)==1 && Reco_QQ_sign==0 && Reco_QQ_4mom->M()>2.6 && Reco_QQ_4mom->M()<2.9 && Reco_QQ_ctau>-1.5 && Reco_QQ_ctau<3.0 && Reco_QQ_4mom->Pt()>6.5 && Reco_QQ_4mom->Pt()<30.0 && Reco_QQ_4mom->Rapidity()>0.0 && Reco_QQ_4mom->Rapidity()<2.4",
		"Reco_QQ_mupl_4mom->Eta()>-2.4 && Reco_QQ_mupl_4mom->Eta()<2.4 && Reco_QQ_mumi_4mom->Eta()>-2.4 && Reco_QQ_mumi_4mom->Eta()<2.4 && (Reco_QQ_trig&1)==1 && Reco_QQ_sign==0 && Reco_QQ_4mom->M()>3.3 && Reco_QQ_4mom->M()<3.5 && Reco_QQ_ctau>-1.5 && Reco_QQ_ctau<3.0 && Reco_QQ_4mom->Pt()>6.5 && Reco_QQ_4mom->Pt()<30.0 && Reco_QQ_4mom->Rapidity()>0.0 && Reco_QQ_4mom->Rapidity()<2.4",
		"Reco_QQ_mupl_4mom->Eta()>-2.4 && Reco_QQ_mupl_4mom->Eta()<2.4 && Reco_QQ_mumi_4mom->Eta()>-2.4 && Reco_QQ_mumi_4mom->Eta()<2.4 && (Reco_QQ_trig&1)==1 && Reco_QQ_sign==0 && Reco_QQ_4mom->M()>2.6 && Reco_QQ_4mom->M()<2.9 && Reco_QQ_ctau>-1.5 && Reco_QQ_ctau<3.0 && Reco_QQ_4mom->Pt()>6.5 && Reco_QQ_4mom->Pt()<30.0 && Reco_QQ_4mom->Rapidity()>-2.4 && Reco_QQ_4mom->Rapidity()<0.0",
		"Reco_QQ_mupl_4mom->Eta()>-2.4 && Reco_QQ_mupl_4mom->Eta()<2.4 && Reco_QQ_mumi_4mom->Eta()>-2.4 && Reco_QQ_mumi_4mom->Eta()<2.4 && (Reco_QQ_trig&1)==1 && Reco_QQ_sign==0 && Reco_QQ_4mom->M()>3.3 && Reco_QQ_4mom->M()<3.5 && Reco_QQ_ctau>-1.5 && Reco_QQ_ctau<3.0 && Reco_QQ_4mom->Pt()>6.5 && Reco_QQ_4mom->Pt()<30.0 && Reco_QQ_4mom->Rapidity()>-2.4 && Reco_QQ_4mom->Rapidity()<0.0"
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
		if (i%2==0) {colorIndex=3;} else {colorIndex=4;}
		cout << i<<"th colorIndex=" << colorIndex << endl;
		SetHistStyle(histCt[i],colorIndex,0);
	}

	// --- Draw Ct distribution
	//TCanvas c1; c1.cd();
	TCanvas* c1 = new TCanvas("c1","canvas",600,600);
	c1->cd();
	gPad->SetLogy(1);

	//draw the Text
	//TPaveText *text = new TPaveText(0.41, 0.15, 0.50, 0.30, "NDC"); // bottom middle small
	TPaveText *text = new TPaveText(0.35, 0.15, 0.50, 0.35, "NDC"); // bottom middle
	SetTextStyle(text);
	//TPaveText *text2 = new TPaveText(0.35, 0.01, 0.70, 0.15, "NDC"); // most bottom
	TPaveText *text2 = new TPaveText(0.58, 0.64, 0.80, 0.73, "NDC"); // most bottom
	text2->SetFillColor(0);
	text2->SetFillStyle(4000);
	text2->SetBorderSize(0);
	text2->SetMargin(0.2);	
	text2->SetTextSize(0.040);
	text2->SetTextColor(kRed);

	//draw the Legends
	//TLegend *leg = new TLegend(0.50, 0.74, 0.80, 0.90); // upper right
	TLegend *leg = new TLegend(0.52, 0.74, 0.79, 0.90); // upper right
	SetLegendStyle(leg);

	// 1.pbp_pos_pdg (hist0,1)
	treePbp->Draw("Reco_QQ_ctau>>pbp_pos_low_pdg", condition[0].c_str(),"e");
	treePbp->Draw("Reco_QQ_ctau>>pbp_pos_high_pdg", condition[1].c_str(),"esame");
	cout << "histogram entries =" << histCt[0]->GetEntries() <<endl;
	cout << "histogram entries =" << histCt[1]->GetEntries() <<endl;
	text->AddText("Trk-Trk");
	text->AddText("0 < y_{lab} < 2.4");
	text->AddText("6.5<p_{T}<30 GeV/c");
	text->AddText("HLT_PAL1DoubleMuOpen");
	text->Draw();
	text2->AddText("Lifetime with");
	text2->AddText("J/#psi PDG mass");
	text2->Draw();	
	leg->SetHeader("Pbp (18/nb)");
	leg -> AddEntry(histCt[0],"[2.6-2.9] GeV/c^{2}","lp");
	leg -> AddEntry(histCt[1],"[3.3-3.5] GeV/c^{2}","lp");
	leg->Draw();
	//c1->SaveAs(Form("%s.png",histName[0].c_str()));
	c1->SaveAs("pbp_pos_pdg.png");
	c1->Clear();
	text->Clear();
	text2->Clear();
	leg->Clear();

	// 2.pbp_neg_pdg (hist2,3)
	treePbp->Draw("Reco_QQ_ctau>>pbp_neg_low_pdg", condition[2].c_str(),"e");
	treePbp->Draw("Reco_QQ_ctau>>pbp_neg_high_pdg", condition[3].c_str(),"esame");
	cout << "histogram entries =" << histCt[2]->GetEntries() <<endl;
	cout << "histogram entries =" << histCt[3]->GetEntries() <<endl;
	text->AddText("Trk-Trk");
	text->AddText("-2.4 < y_{lab} < 0");
	text->AddText("6.5<p_{T}<30 GeV/c");
	text->AddText("HLT_PAL1DoubleMuOpen");
	text->Draw();	
	text2->AddText("Lifetime with");
	text2->AddText("J/#psi PDG mass");
	text2->Draw();	
	leg -> SetHeader("Pbp (18/nb)");
	leg -> AddEntry(histCt[2],"[2.6-2.9] GeV/c^{2}","lp");
	leg -> AddEntry(histCt[3],"[3.3-3.5] GeV/c^{2}","lp");
	leg->Draw();
	c1->SaveAs("pbp_neg_pdg.png");
	c1->Clear();
	text->Clear();
	text2->Clear();
	leg->Clear();

	// 3.pbp_pos_inv (hist4,5)
	treePbp->Draw("(Reco_QQ_ctau*(Reco_QQ_4mom->M())/3.096916)>>pbp_pos_low_inv", condition[0].c_str(),"e");
	treePbp->Draw("(Reco_QQ_ctau*(Reco_QQ_4mom->M())/3.096916)>>pbp_pos_high_inv", condition[1].c_str(),"esame");
	cout << "histogram entries =" << histCt[4]->GetEntries() <<endl;
	cout << "histogram entries =" << histCt[5]->GetEntries() <<endl;
	text->AddText("Trk-Trk");
	text->AddText("0 < y_{lab} < 2.4");
	text->AddText("6.5<p_{T}<30 GeV/c");
	text->AddText("HLT_PAL1DoubleMuOpen");
	text->Draw();	
	text2->AddText("Lifetime with");
	text2->AddText("dimuon invariant mass");
	text2->Draw();	
	leg -> SetHeader("Pbp (18/nb)");
	leg -> AddEntry(histCt[4],"[2.6-2.9] GeV/c^{2}","lp");
	leg -> AddEntry(histCt[5],"[3.3-3.5] GeV/c^{2}","lp");
	leg->Draw();
	c1->SaveAs("pbp_pos_inv.png");
	c1->Clear();
	text->Clear();
	text2->Clear();
	leg->Clear();

	// 4.pbp_neg_inv (hist6,7)
	treePbp->Draw("(Reco_QQ_ctau*(Reco_QQ_4mom->M())/3.096916)>>pbp_neg_low_inv", condition[2].c_str(),"e");
	treePbp->Draw("(Reco_QQ_ctau*(Reco_QQ_4mom->M())/3.096916)>>pbp_neg_high_inv", condition[3].c_str(),"esame");
	cout << "histogram entries =" << histCt[6]->GetEntries() <<endl;
	cout << "histogram entries =" << histCt[7]->GetEntries() <<endl;
	text->AddText("Trk-Trk");
	text->AddText("-2.4 < y_{lab} < 0");
	text->AddText("6.5<p_{T}<30 GeV/c");
	text->AddText("HLT_PAL1DoubleMuOpen");
	text->Draw();	
	text2->AddText("Lifetime with");
	text2->AddText("dimuon invariant mass");
	text2->Draw();	
	leg -> SetHeader("Pbp (18/nb)");
	leg -> AddEntry(histCt[6],"[2.6-2.9] GeV/c^{2}","lp");
	leg -> AddEntry(histCt[7],"[3.3-3.5] GeV/c^{2}","lp");
	leg->Draw();
	c1->SaveAs("pbp_neg_inv.png");
	c1->Clear();
	text->Clear();
	text2->Clear();
	leg->Clear();

	// 5.ppb_pos_pdg (hist8,9)
	treepPb->Draw("Reco_QQ_ctau>>ppb_pos_low_pdg", condition[0].c_str(),"e");
	treepPb->Draw("Reco_QQ_ctau>>ppb_pos_high_pdg", condition[1].c_str(),"esame");
	cout << "histogram entries =" << histCt[8]->GetEntries() <<endl;
	cout << "histogram entries =" << histCt[9]->GetEntries() <<endl;
	text->AddText("Trk-Trk");
	text->AddText("0 < y_{lab} < 2.4");
	text->AddText("6.5<p_{T}<30 GeV/c");
	text->AddText("HLT_PAL1DoubleMuOpen");
	text->Draw();	
	text2->AddText("Lifetime with");
	text2->AddText("J/#psi PDG mass");
	text2->Draw();	
	leg -> SetHeader("pPb (12/nb)");
	leg -> AddEntry(histCt[8],"[2.6-2.9] GeV/c^{2}","lp");
	leg -> AddEntry(histCt[9],"[3.3-3.5] GeV/c^{2}","lp");
	leg->Draw();
	c1->SaveAs("ppb_pos_pdg.png");
	c1->Clear();
	text->Clear();
	text2->Clear();
	leg->Clear();

	// 6.ppb_neg_pdg (hist10,11)
	treepPb->Draw("Reco_QQ_ctau>>ppb_neg_low_pdg", condition[2].c_str(),"e");
	treepPb->Draw("Reco_QQ_ctau>>ppb_neg_high_pdg", condition[3].c_str(),"esame");
	cout << "histogram entries =" << histCt[10]->GetEntries() <<endl;
	cout << "histogram entries =" << histCt[11]->GetEntries() <<endl;
	text->AddText("Trk-Trk");
	text->AddText("-2.4 < y_{lab} < 0");
	text->AddText("6.5<p_{T}<30 GeV/c");
	text->AddText("HLT_PAL1DoubleMuOpen");
	text->Draw();	
	text2->AddText("Lifetime with");
	text2->AddText("J/#psi PDG mass");
	text2->Draw();	
	leg -> SetHeader("pPb (12/nb)");
	leg -> AddEntry(histCt[10],"[2.6-2.9] GeV/c^{2}","lp");
	leg -> AddEntry(histCt[11],"[3.3-3.5] GeV/c^{2}","lp");
	leg->Draw();
	c1->SaveAs("ppb_neg_pdg.png");
	c1->Clear();
	text->Clear();
	text2->Clear();
	leg->Clear();

	// 7.ppb_pos_inv (hist12,13)
	treepPb->Draw("(Reco_QQ_ctau*(Reco_QQ_4mom->M())/3.096916)>>ppb_pos_low_inv", condition[0].c_str(),"e");
	treepPb->Draw("(Reco_QQ_ctau*(Reco_QQ_4mom->M())/3.096916)>>ppb_pos_high_inv", condition[1].c_str(),"esame");
	cout << "histogram entries =" << histCt[12]->GetEntries() <<endl;
	cout << "histogram entries =" << histCt[13]->GetEntries() <<endl;
	text->AddText("Trk-Trk");
	text->AddText("0 < y_{lab} < 2.4");
	text->AddText("6.5<p_{T}<30 GeV/c");
	text->AddText("HLT_PAL1DoubleMuOpen");
	text->Draw();	
	text2->AddText("Lifetime with");
	text2->AddText("dimuon invariant mass");
	text2->Draw();	
	leg -> SetHeader("pPb (12/nb)");
	leg -> AddEntry(histCt[12],"[2.6-2.9] GeV/c^{2}","lp");
	leg -> AddEntry(histCt[13],"[3.3-3.5] GeV/c^{2}","lp");
	leg->Draw();
	c1->SaveAs("ppb_pos_inv.png");
	c1->Clear();
	text->Clear();
	text2->Clear();
	leg->Clear();

	// 8.ppb_neg_inv (hist14,15)
	treepPb->Draw("(Reco_QQ_ctau*(Reco_QQ_4mom->M())/3.096916)>>ppb_neg_low_inv", condition[2].c_str(),"e");
	treepPb->Draw("(Reco_QQ_ctau*(Reco_QQ_4mom->M())/3.096916)>>ppb_neg_high_inv", condition[3].c_str(),"esame");
	cout << "histogram entries =" << histCt[14]->GetEntries() <<endl;
	cout << "histogram entries =" << histCt[15]->GetEntries() <<endl;
	text->AddText("Trk-Trk");
	text->AddText("-2.4 < y_{lab} < 0");
	text->AddText("6.5<p_{T}<30 GeV/c");
	text->AddText("HLT_PAL1DoubleMuOpen");
	text->Draw();	
	text2->AddText("Lifetime with");
	text2->AddText("dimuon invariant mass");
	text2->Draw();	
	leg -> SetHeader("pPb (12/nb)");
	leg -> AddEntry(histCt[14],"[2.6-2.9] GeV/c^{2}","lp");
	leg -> AddEntry(histCt[15],"[3.3-3.5] GeV/c^{2}","lp");
	leg->Draw();
	c1->SaveAs("ppb_neg_inv.png");
	c1->Clear();
	text->Clear();
	text2->Clear();
	leg->Clear();

	// 9.pp_pos_pdg (hist16,17)
	treepp->Draw("Reco_QQ_ctau>>pp_pos_low_pdg", condition[0].c_str(),"e");
	treepp->Draw("Reco_QQ_ctau>>pp_pos_high_pdg", condition[1].c_str(),"esame");
	cout << "histogram entries =" << histCt[16]->GetEntries() <<endl;
	cout << "histogram entries =" << histCt[17]->GetEntries() <<endl;
	text->AddText("Trk-Trk");
	text->AddText("0 < y_{lab} < 2.4");
	text->AddText("6.5<p_{T}<30 GeV/c");
	text->AddText("HLT_PAL1DoubleMuOpen");
	text->Draw();	
	text2->AddText("Lifetime with");
	text2->AddText("J/#psi PDG mass");
	text2->Draw();	
	leg -> SetHeader("pp (5/pb)");
	leg -> AddEntry(histCt[16],"[2.6-2.9] GeV/c^{2}","lp");
	leg -> AddEntry(histCt[17],"[3.3-3.5] GeV/c^{2}","lp");
	leg->Draw();
	c1->SaveAs("pp_pos_pdg.png");
	c1->Clear();
	text->Clear();
	text2->Clear();
	leg->Clear();

	// 10.pp_neg_pdg (hist18,19)
	treepp->Draw("Reco_QQ_ctau>>pp_neg_low_pdg", condition[2].c_str(),"e");
	treepp->Draw("Reco_QQ_ctau>>pp_neg_high_pdg", condition[3].c_str(),"esame");
	cout << "histogram entries =" << histCt[18]->GetEntries() <<endl;
	cout << "histogram entries =" << histCt[19]->GetEntries() <<endl;
	text->AddText("Trk-Trk");
	text->AddText("-2.4 < y_{lab} < 0");
	text->AddText("6.5<p_{T}<30 GeV/c");
	text->AddText("HLT_PAL1DoubleMuOpen");
	text->Draw();	
	text2->AddText("Lifetime with");
	text2->AddText("J/#psi PDG mass");
	text2->Draw();	
	leg -> SetHeader("pp (5/pb)");
	leg -> AddEntry(histCt[18],"[2.6-2.9] GeV/c^{2}","lp");
	leg -> AddEntry(histCt[19],"[3.3-3.5] GeV/c^{2}","lp");
	leg->Draw();
	c1->SaveAs("pp_neg_pdg.png");
	c1->Clear();
	text->Clear();
	text2->Clear();
	leg->Clear();

	// 11.pp_pos_inv (hist20,21)
	treepp->Draw("(Reco_QQ_ctau*(Reco_QQ_4mom->M())/3.096916)>>pp_pos_low_inv", condition[0].c_str(),"e");
	treepp->Draw("(Reco_QQ_ctau*(Reco_QQ_4mom->M())/3.096916)>>pp_pos_high_inv", condition[1].c_str(),"esame");
	cout << "histogram entries =" << histCt[20]->GetEntries() <<endl;
	cout << "histogram entries =" << histCt[21]->GetEntries() <<endl;
	text->AddText("Trk-Trk");
	text->AddText("0 < y_{lab} < 2.4");
	text->AddText("6.5<p_{T}<30 GeV/c");
	text->AddText("HLT_PAL1DoubleMuOpen");
	text->Draw();	
	text2->AddText("Lifetime with");
	text2->AddText("dimuon invariant mass");
	text2->Draw();	
	leg -> SetHeader("pp (5/pb)");
	leg -> AddEntry(histCt[20],"[2.6-2.9] GeV/c^{2}","lp");
	leg -> AddEntry(histCt[21],"[3.3-3.5] GeV/c^{2}","lp");
	leg->Draw();
	c1->SaveAs("pp_pos_inv.png");
	c1->Clear();
	text->Clear();
	text2->Clear();
	leg->Clear();

	// 12.pp_neg_inv (hist22,23)
	treepp->Draw("(Reco_QQ_ctau*(Reco_QQ_4mom->M())/3.096916)>>pp_neg_low_inv", condition[2].c_str(),"e");
	treepp->Draw("(Reco_QQ_ctau*(Reco_QQ_4mom->M())/3.096916)>>pp_neg_high_inv", condition[3].c_str(),"esame");
	cout << "histogram entries =" << histCt[22]->GetEntries() <<endl;
	cout << "histogram entries =" << histCt[23]->GetEntries() <<endl;
	text->AddText("Trk-Trk");
	text->AddText("-2.4 < y_{lab} < 0");
	text->AddText("6.5<p_{T}<30 GeV/c");
	text->AddText("HLT_PAL1DoubleMuOpen");
	text->Draw();	
	text2->AddText("Lifetime with");
	text2->AddText("dimuon invariant mass");
	text2->Draw();	
	leg -> SetHeader("pp (5/pb)");
	leg -> AddEntry(histCt[22],"[2.6-2.9] GeV/c^{2}","lp");
	leg -> AddEntry(histCt[23],"[3.3-3.5] GeV/c^{2}","lp");
	leg->Draw();
	c1->SaveAs("pp_neg_inv.png");
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
	//t->SetTextSize(0.035);
	t->SetTextSize(0.026);
}
