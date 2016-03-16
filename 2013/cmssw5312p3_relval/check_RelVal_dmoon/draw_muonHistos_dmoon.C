#include <Riostream.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TGraph.h>
#include <vector>
#include <TSystem.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TDirectory.h>
#include <TLegend.h>
#include <TPaveStats.h>
#include <TLatex.h>
#include "TStyle.h"
#include "TSystem.h"

#include <sstream>
#include <string>

void SetHistStyle(TH1* h, Int_t c, Int_t m);
void SetLegendStyle(TLegend* l);

void draw_muonHistos_dmoon(int fileCode=3){

	//gROOT->Macro("./JpsiStyle.c");
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.12);
  gStyle->SetPadLeftMargin(0.12);

	TFile* inFile;
	string samplename;
	Double_t massMin;
	Double_t massMax;
	Double_t ptMin;
	Double_t ptMax;
	Double_t diptMin;
	Double_t diptMax;
	const int nPtBin = 40;
	const int nEtaBin = 15;
	const int nPhiBin = 15;
	const int nMassBin = 40;

  //TFile *in = new TFile("HLTrgAna_RelVal_JpsitoMM_20131205.root","READ");

	if (fileCode ==0) {
	  inFile = TFile::Open("root://eoscms//eos/cms/store/user/dmoon/cms538HI/HLTrgAna/RelVal/HLTrgAna_RelVal_JpsitoMM_20131205.root","READ");
		samplename = "53X_Jpsi";
		massMin = 2.6; massMax = 3.5;
		ptMin = 0.0; ptMax = 20.0;
		diptMin = 0.0; diptMax = 20.0;
		
	} else if (fileCode ==1) {
	  inFile = TFile::Open("root://eoscms//eos/cms/store/user/dmoon/cms538HI/HLTrgAna/RelVal/HLTrgAna_RelVal_ZtoMM_20131205.root","READ");
		samplename = "53X_Z";
		massMin = 60; massMax = 120;
		ptMin = 0.0; ptMax =100.0;
		diptMin = 0.0; diptMax = 50.0;
	} else if (fileCode ==2) {
	  inFile = TFile::Open("root://eoscms//eos/cms/store/user/dmoon/cms538HI/HLTrgAna/442patch5/HLTrgAna_RelVal_JpsiMM_442patch5_20131210.root","READ");
		samplename = "44X_Jpsi";
		massMin = 2.6; massMax = 3.5;
		ptMin = 0.0; ptMax = 20.0;
		diptMin = 0.0; diptMax = 20.0;
	} else if (fileCode ==3) {
	  inFile = TFile::Open("root://eoscms//eos/cms/store/user/dmoon/cms538HI/HLTrgAna/442patch5/HLTrgAna_RelVal_ZMM_442patch5_20131210.root","READ");
		samplename = "44X_Z";
		massMin = 60; massMax = 120;
		ptMin = 0.0; ptMax =100.0;
		diptMin = 0.0; diptMax = 50.0;
	} else std::cout << "*** Error *** Specify the input file" << std::endl;

  TTree *Ana = (TTree*)inFile->Get("Ana");

  // single muon (muon, regitmuon -  glb, trk)
	//pt
  TH1F *hRecoMuPtGlb = new TH1F("hRecoMuPtGlb",";p_{T} (GeV/c);", nPtBin, ptMin, ptMax);
  TH1F *hRecoMuPtTrk = new TH1F("hRecoMuPtTrk",";p_{T} (GeV/c);", nPtBin, ptMin, ptMax);
  hRecoMuPtGlb->Sumw2();
  hRecoMuPtTrk->Sumw2();
  TH1F *hRegitMuPtGlb = new TH1F("hRegitMuPtGlb",";p_{T} (GeV/c);",nPtBin, ptMin, ptMax);
  TH1F *hRegitMuPtTrk = new TH1F("hRegitMuPtTrk",";p_{T} (GeV/c);",nPtBin, ptMin, ptMax);
  hRegitMuPtGlb->Sumw2();
  hRegitMuPtTrk->Sumw2();
	//eta
  TH1F *hRecoMuEtaGlb = new TH1F("hRecoMuEtaGlb",";#eta;",nEtaBin, -2.5, 2.5);
  TH1F *hRecoMuEtaTrk = new TH1F("hRecoMuEtaTrk",";#eta;",nEtaBin, -2.5, 2.5);
  hRecoMuEtaGlb->Sumw2();
  hRecoMuEtaTrk->Sumw2();
  TH1F *hRegitMuEtaGlb = new TH1F("hRegitMuEtaGlb",";#eta;",nEtaBin, -2.5, 2.5);
  TH1F *hRegitMuEtaTrk = new TH1F("hRegitMuEtaTrk",";#eta;",nEtaBin, -2.5, 2.5);
  hRegitMuEtaGlb->Sumw2();
  hRegitMuEtaTrk->Sumw2();
	//phi
  TH1F *hRecoMuPhiGlb = new TH1F("hRecoMuPhiGlb",";#phi;",nPhiBin, 0, 3.2);
  TH1F *hRecoMuPhiTrk = new TH1F("hRecoMuPhiTrk",";#phi;",nPhiBin, 0, 3.2);
  hRecoMuPhiGlb->Sumw2();
  hRecoMuPhiTrk->Sumw2();
  TH1F *hRegitMuPhiGlb = new TH1F("hRegitMuPhiGlb",";#phi;",nPhiBin, 0, 3.2);
  TH1F *hRegitMuPhiTrk = new TH1F("hRegitMuPhiTrk",";#phi;",nPhiBin, 0, 3.2);
  hRegitMuPhiGlb->Sumw2();
  hRegitMuPhiTrk->Sumw2();

	// dimuon (muon, regitmuon -  glb, trk)
	// pt
  TH1F *hRecoDiMuPt = new TH1F("hRecoDiMuPt",";p_{T} (GeV/c);",nPtBin, diptMin, diptMax);
  hRecoDiMuPt->Sumw2();
  TH1F *hRegitDiMuPt = new TH1F("hRegitDiMuPt",";p_{T} (GeV/c);",nPtBin, diptMin, diptMax);
  hRegitDiMuPt->Sumw2();
	// mass
  TH1F *hRecoDiMuMass = new TH1F("hRecoDiMuMass",";m_{#mu#mu} (GeV/c^{2});",nMassBin, massMin, massMax);
  hRecoDiMuMass->Sumw2();
  TH1F *hRegitDiMuMass = new TH1F("hRegitDiMuMass",";m_{#mu#mu} (GeV/c^{2});",nMassBin, massMin, massMax);
  hRegitDiMuMass->Sumw2();

	// single muon	
  Ana->Draw("recoMu_pt>>hRecoMuPtGlb","recoMu_Glb==1","E");
  Ana->Draw("recoMu_pt>>hRecoMuPtTrk","recoMu_Trk==1","E");
  Ana->Draw("regrecoMu_pt>>hRegitMuPtGlb","regrecoMu_Glb==1","E");
  Ana->Draw("regrecoMu_pt>>hRegitMuPtTrk","regrecoMu_Trk==1","E");
  Ana->Draw("recoMu_eta>>hRecoMuEtaGlb","recoMu_Glb==1","E");
  Ana->Draw("recoMu_eta>>hRecoMuEtaTrk","recoMu_Trk==1","E");
  Ana->Draw("regrecoMu_eta>>hRegitMuEtaGlb","regrecoMu_Glb==1","E");
  Ana->Draw("regrecoMu_eta>>hRegitMuEtaTrk","regrecoMu_Trk==1","E");
  Ana->Draw("recoMu_phi>>hRecoMuPhiGlb","recoMu_Glb==1","E");
  Ana->Draw("recoMu_phi>>hRecoMuPhiTrk","recoMu_Trk==1","E");
  Ana->Draw("regrecoMu_phi>>hRegitMuPhiGlb","regrecoMu_Glb==1","E");
  Ana->Draw("regrecoMu_phi>>hRegitMuPhiTrk","regrecoMu_Trk==1","E");

	// dimuon
  Ana->Draw("recoDimu_pt>>hRecoDiMuPt","","E");
  Ana->Draw("regrecoDimu_pt>>hRegitDiMuPt","","E");
  Ana->Draw("recoDimu_mass>>hRecoDiMuMass","","E");
  Ana->Draw("regrecoDimu_mass>>hRegitDiMuMass","","E");

	SetHistStyle(hRecoMuPtGlb, 1,0);
	SetHistStyle(hRegitMuPtGlb, 2,0);
	SetHistStyle(hRecoMuPtTrk, 1,0);
	SetHistStyle(hRegitMuPtTrk, 2,0);
	SetHistStyle(hRecoMuEtaGlb, 1,0);
	SetHistStyle(hRegitMuEtaGlb, 2,0);
	SetHistStyle(hRecoMuEtaTrk, 1,0);
	SetHistStyle(hRegitMuEtaTrk, 2,0);
	SetHistStyle(hRecoMuPhiGlb, 1,0);
	SetHistStyle(hRegitMuPhiGlb, 2,0);
	SetHistStyle(hRecoMuPhiTrk, 1,0);
	SetHistStyle(hRegitMuPhiTrk, 2,0);

	SetHistStyle(hRecoDiMuPt, 1,0);
	SetHistStyle(hRegitDiMuPt, 2,0);
	SetHistStyle(hRecoDiMuMass, 1,0);
	SetHistStyle(hRegitDiMuMass, 2,0);

  TLegend *legUR01 = new TLegend(0.68,0.60,0.87,0.77);
  TLegend *legUM = new TLegend(0.42,0.70,0.61,0.88);
  TLegend *legBR = new TLegend(0.64,0.15,0.84,0.33);
	SetLegendStyle(legUR01);
	SetLegendStyle(legUM);
	SetLegendStyle(legBR);

	//draw and save plots
  TCanvas *c1 = new TCanvas("c1","",600,600);
	//single muon
  hRegitMuPtTrk->SetMinimum(0);
  hRegitMuPtTrk->Draw();
  hRecoMuPtTrk->Draw("same");
  legUR01->SetHeader("Tracker Muons");
  legUR01->AddEntry(hRecoMuPtTrk,"reco muon","PL");
  legUR01->AddEntry(hRegitMuPtTrk,"regit muon","PL");
  legUR01->Draw("same");
  c1->SaveAs(Form("%s_MuPtTrk_reco_vs_regit.pdf",samplename.c_str()));
	legUR01->Clear();
	c1->Clear();

  hRegitMuPtGlb->SetMinimum(0);
  hRegitMuPtGlb->Draw();
  hRecoMuPtGlb->Draw("same");
  legUR01->SetHeader("Global Muons");
  legUR01->AddEntry(hRecoMuPtGlb,"reco muon","PL");
  legUR01->AddEntry(hRegitMuPtGlb,"regit muon","PL");
  legUR01->Draw("same");
  c1->SaveAs(Form("%s_MuPtGlb_reco_vs_regit.pdf",samplename.c_str()));
	legUR01->Clear();
	c1->Clear();

  hRegitMuEtaTrk->SetMinimum(0);
  hRegitMuEtaTrk->Draw();
  hRecoMuEtaTrk->Draw("same");
  legUM->SetHeader("Tracker Muons");
  legUM->AddEntry(hRecoMuEtaTrk,"reco muon","PL");
  legUM->AddEntry(hRegitMuEtaTrk,"regit muon","PL");
  legUM->Draw("same");
  c1->SaveAs(Form("%s_MuEtaTrk_reco_vs_regit.pdf",samplename.c_str()));
	legUM->Clear();
	c1->Clear();

  hRegitMuEtaGlb->SetMinimum(0);
  hRegitMuEtaGlb->Draw();
  hRecoMuEtaGlb->Draw("same");
  legUM->SetHeader("Global Muons");
  legUM->AddEntry(hRecoMuEtaGlb,"reco muon","PL");
  legUM->AddEntry(hRegitMuEtaGlb,"regit muon","PL");
  legUM->Draw("same");
  c1->SaveAs(Form("%s_MuEtaGlb_reco_vs_regit.pdf",samplename.c_str()));
	legUM->Clear();
	c1->Clear();

  hRegitMuPhiTrk->SetMinimum(0);
  hRegitMuPhiTrk->Draw();
  hRecoMuPhiTrk->Draw("same");
  legBR->SetHeader("Tracker Muons");
  legBR->AddEntry(hRecoMuPhiTrk,"reco muon","PL");
  legBR->AddEntry(hRegitMuPhiTrk,"regit muon","PL");
  legBR->Draw("same");
  c1->SaveAs(Form("%s_MuPhiTrk_reco_vs_regit.pdf",samplename.c_str()));
	legBR->Clear();
	c1->Clear();

  hRegitMuPhiGlb->SetMinimum(0);
  hRegitMuPhiGlb->Draw();
  hRecoMuPhiGlb->Draw("same");
  legBR->SetHeader("Global Muons");
  legBR->AddEntry(hRecoMuPhiGlb,"reco muon","PL");
  legBR->AddEntry(hRegitMuPhiGlb,"regit muon","PL");
  legBR->Draw("same");
  c1->SaveAs(Form("%s_MuPhiGlb_reco_vs_regit.pdf",samplename.c_str()));
	legBR->Clear();
	c1->Clear();

	//dimu
  hRegitDiMuPt->SetMinimum(0);
  hRegitDiMuPt->Draw();
  hRecoDiMuPt->Draw("same");
  legUR01->SetHeader("Dimuons");
  legUR01->AddEntry(hRecoDiMuPt,"reco muon","PL");
  legUR01->AddEntry(hRegitDiMuPt,"regit muon","PL");
  legUR01->Draw("same");
  c1->SaveAs(Form("%s_DiMuPt_reco_vs_regit.pdf",samplename.c_str()));
	legUR01->Clear();
	c1->Clear();

  hRegitDiMuMass->SetMinimum(0);
  hRegitDiMuMass->Draw();
  hRecoDiMuMass->Draw("same");
  legUR01->SetHeader("Dimuons");
  legUR01->AddEntry(hRecoDiMuMass,"reco muon","PL");
  legUR01->AddEntry(hRegitDiMuMass,"regit muon","PL");
  legUR01->Draw("same");
  c1->SaveAs(Form("%s_DiMuMass_reco_vs_regit.pdf",samplename.c_str()));
	legUR01->Clear();
	c1->Clear();

	return;

}

void SetHistStyle(TH1* h, Int_t c, Int_t m) {
	Int_t colorArr[] = { kGray+3, kRed-4, kBlue, kOrange+7, kGreen+3, kAzure+8, kViolet-4, kBlack };
	//Int_t colorArr[] = { kGray+3, kRed-4, kBlue, kOrange+1, kGreen-3, kAzure+8, kViolet-4, kBlack };
	Int_t markerArr[] = {kFullCircle, kOpenCircle, kFullTriangleUp, kOpenTriangleUp, kFullTriangleDown, kFullSquare};
	//Int_t markerFullArr[] = {kFullCircle, kFullTriangleUp, kFullTriangleDown, kFullSquare};
	//Int_t markerOpenArr[] = {kOpenCircle, kOpenTriangleUp, kOpenTriangleDown, kOpenSquare};
	h-> SetMarkerColor(colorArr[c]);
	h-> SetMarkerStyle(markerArr[m]);
	h-> SetMarkerSize(1.2);
	h-> SetLineColor(colorArr[c]);
	h-> SetLineWidth(1.8);
}

void SetLegendStyle(TLegend* l) {
	l->SetFillColor(0);
	l->SetFillStyle(4000);
	l->SetBorderSize(0);
	l->SetMargin(0.2);
	l->SetTextSize(0.040);
}
