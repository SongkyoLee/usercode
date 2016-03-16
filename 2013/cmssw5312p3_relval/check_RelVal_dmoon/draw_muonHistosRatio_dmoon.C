#include <Riostream.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TGraph.h>
#include <vector>
#include <TSystem.h>
#include <TCanvas.h>
#include <TH1.h>
//#include <TH1D.h>
//#include <TH2D.h>
#include <TDirectory.h>
#include <TLegend.h>
#include <TPaveStats.h>
#include <TLatex.h>
#include "TStyle.h"
#include "TSystem.h"

#include <sstream>
#include <string>

void normalizeByEvent(TH1F *histo);
TH1F* divideHistosSameBins(TH1F* h_Num, TH1F* h_Den);
TGraph* referenceLine(Double_t nBins, Double_t xMin, Double_t xMax);
void SetHistStyle(TH1* h, Int_t c, Int_t m);
void SetLegendStyle(TLegend* l);

void draw_muonHistosRatio_dmoon(int fileCode=1){

	//gROOT->Macro("./JpsiStyle.c");
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.12);
  gStyle->SetPadLeftMargin(0.12);

	TFile* inFile53X;
	TFile* inFile44X;
	string samplename;
	Double_t massMin;
	Double_t massMax;
	Double_t ptMin;
	Double_t ptMax;
	Double_t diptMin;
	Double_t diptMax;
	//const int nPtBin = 40;
	//const int nEtaBin = 15;
	//const int nPhiBin = 15;
	//const int nMassBin = 40;
	const int nPtBin = 20;
	const int nEtaBin = 10;
	const int nPhiBin = 10;
	const int nMassBin = 20;

  //TFile *in = new TFile("HLTrgAna_RelVal_JpsitoMM_20131205.root","READ");

	if (fileCode ==0) {
	  inFile53X = TFile::Open("root://eoscms//eos/cms/store/user/dmoon/cms538HI/HLTrgAna/RelVal/HLTrgAna_RelVal_JpsitoMM_20131205.root","READ");
	  inFile44X = TFile::Open("root://eoscms//eos/cms/store/user/dmoon/cms538HI/HLTrgAna/442patch5/HLTrgAna_RelVal_JpsiMM_442patch5_20131210.root","READ");
		//samplename = "53X_Jpsi";
		samplename = "53X_44X_Jpsi";
		massMin = 2.6; massMax = 3.5;
		ptMin = 0.0; ptMax = 20.0;
		diptMin = 0.0; diptMax = 20.0;
		
	} else if (fileCode ==1) {
	  inFile53X = TFile::Open("root://eoscms//eos/cms/store/user/dmoon/cms538HI/HLTrgAna/RelVal/HLTrgAna_RelVal_ZtoMM_20131205.root","READ");
	  inFile44X = TFile::Open("root://eoscms//eos/cms/store/user/dmoon/cms538HI/HLTrgAna/442patch5/HLTrgAna_RelVal_ZMM_442patch5_20131210.root","READ");
		samplename = "53X_44X_Z";
		massMin = 60; massMax = 120;
		ptMin = 0.0; ptMax =100.0;
		diptMin = 0.0; diptMax = 50.0;
	} else std::cout << "*** Error *** Specify the input file" << std::endl;

  TTree *Ana53X = (TTree*)inFile53X->Get("Ana");
  TTree *Ana44X = (TTree*)inFile44X->Get("Ana");


	////// for 53X
  // single muon (muon, regitmuon -  glb, trk)
	//pt
  TH1F *hRecoMuPtGlb_53X = new TH1F("hRecoMuPtGlb_53X",";p_{T} (GeV/c);", nPtBin, ptMin, ptMax);
  TH1F *hRecoMuPtTrk_53X = new TH1F("hRecoMuPtTrk_53X",";p_{T} (GeV/c);", nPtBin, ptMin, ptMax);
  hRecoMuPtGlb_53X->Sumw2();
  hRecoMuPtTrk_53X->Sumw2();
  TH1F *hRegitMuPtGlb_53X = new TH1F("hRegitMuPtGlb_53X",";p_{T} (GeV/c);",nPtBin, ptMin, ptMax);
  TH1F *hRegitMuPtTrk_53X = new TH1F("hRegitMuPtTrk_53X",";p_{T} (GeV/c);",nPtBin, ptMin, ptMax);
  hRegitMuPtGlb_53X->Sumw2();
  hRegitMuPtTrk_53X->Sumw2();
	//eta
  TH1F *hRecoMuEtaGlb_53X = new TH1F("hRecoMuEtaGlb_53X",";#eta;",nEtaBin, -2.5, 2.5);
  TH1F *hRecoMuEtaTrk_53X = new TH1F("hRecoMuEtaTrk_53X",";#eta;",nEtaBin, -2.5, 2.5);
  hRecoMuEtaGlb_53X->Sumw2();
  hRecoMuEtaTrk_53X->Sumw2();
  TH1F *hRegitMuEtaGlb_53X = new TH1F("hRegitMuEtaGlb_53X",";#eta;",nEtaBin, -2.5, 2.5);
  TH1F *hRegitMuEtaTrk_53X = new TH1F("hRegitMuEtaTrk_53X",";#eta;",nEtaBin, -2.5, 2.5);
  hRegitMuEtaGlb_53X->Sumw2();
  hRegitMuEtaTrk_53X->Sumw2();
	//phi
  TH1F *hRecoMuPhiGlb_53X = new TH1F("hRecoMuPhiGlb_53X",";#phi;",nPhiBin, 0, 3.2);
  TH1F *hRecoMuPhiTrk_53X = new TH1F("hRecoMuPhiTrk_53X",";#phi;",nPhiBin, 0, 3.2);
  hRecoMuPhiGlb_53X->Sumw2();
  hRecoMuPhiTrk_53X->Sumw2();
  TH1F *hRegitMuPhiGlb_53X = new TH1F("hRegitMuPhiGlb_53X",";#phi;",nPhiBin, 0, 3.2);
  TH1F *hRegitMuPhiTrk_53X = new TH1F("hRegitMuPhiTrk_53X",";#phi;",nPhiBin, 0, 3.2);
  hRegitMuPhiGlb_53X->Sumw2();
  hRegitMuPhiTrk_53X->Sumw2();

	// dimuon (muon, regitmuon -  glb, trk)
	// pt
  TH1F *hRecoDiMuPt_53X = new TH1F("hRecoDiMuPt_53X",";p_{T} (GeV/c);",nPtBin, diptMin, diptMax);
  hRecoDiMuPt_53X ->Sumw2();
  TH1F *hRegitDiMuPt_53X = new TH1F("hRegitDiMuPt_53X",";p_{T} (GeV/c);",nPtBin, diptMin, diptMax);
  hRegitDiMuPt_53X->Sumw2();
	// mass
  TH1F *hRecoDiMuMass_53X = new TH1F("hRecoDiMuMass_53X",";m_{#mu#mu} (GeV/c^{2});",nMassBin, massMin, massMax);
  hRecoDiMuMass_53X->Sumw2();
  TH1F *hRegitDiMuMass_53X = new TH1F("hRegitDiMuMass_53X",";m_{#mu#mu} (GeV/c^{2});",nMassBin, massMin, massMax);
  hRegitDiMuMass_53X->Sumw2();

	// single muon	
  Ana53X->Draw("recoMu_pt>>hRecoMuPtGlb_53X","recoMu_Glb==1","E");
  Ana53X->Draw("recoMu_pt>>hRecoMuPtTrk_53X","recoMu_Trk==1","E");
  Ana53X->Draw("regrecoMu_pt>>hRegitMuPtGlb_53X","regrecoMu_Glb==1","E");
  Ana53X->Draw("regrecoMu_pt>>hRegitMuPtTrk_53X","regrecoMu_Trk==1","E");
  Ana53X->Draw("recoMu_eta>>hRecoMuEtaGlb_53X","recoMu_Glb==1","E");
  Ana53X->Draw("recoMu_eta>>hRecoMuEtaTrk_53X","recoMu_Trk==1","E");
  Ana53X->Draw("regrecoMu_eta>>hRegitMuEtaGlb_53X","regrecoMu_Glb==1","E");
  Ana53X->Draw("regrecoMu_eta>>hRegitMuEtaTrk_53X","regrecoMu_Trk==1","E");
  Ana53X->Draw("recoMu_phi>>hRecoMuPhiGlb_53X","recoMu_Glb==1","E");
  Ana53X->Draw("recoMu_phi>>hRecoMuPhiTrk_53X","recoMu_Trk==1","E");
  Ana53X->Draw("regrecoMu_phi>>hRegitMuPhiGlb_53X","regrecoMu_Glb==1","E");
  Ana53X->Draw("regrecoMu_phi>>hRegitMuPhiTrk_53X","regrecoMu_Trk==1","E");

	// dimuon
  Ana53X->Draw("recoDimu_pt>>hRecoDiMuPt_53X","","E");
  Ana53X->Draw("regrecoDimu_pt>>hRegitDiMuPt_53X","","E");
  Ana53X->Draw("recoDimu_mass>>hRecoDiMuMass_53X","","E");
  Ana53X->Draw("regrecoDimu_mass>>hRegitDiMuMass_53X","","E");

	normalizeByEvent(hRecoMuPtGlb_53X);
	normalizeByEvent(hRegitMuPtGlb_53X);
	normalizeByEvent(hRecoMuPtTrk_53X);
	normalizeByEvent(hRegitMuPtTrk_53X);
	normalizeByEvent(hRecoMuEtaGlb_53X);
	normalizeByEvent(hRegitMuEtaGlb_53X);
	normalizeByEvent(hRecoMuEtaTrk_53X);
	normalizeByEvent(hRegitMuEtaTrk_53X);
	normalizeByEvent(hRecoMuPhiGlb_53X);
	normalizeByEvent(hRegitMuPhiGlb_53X);
	normalizeByEvent(hRecoMuPhiTrk_53X);
	normalizeByEvent(hRegitMuPhiTrk_53X);

	normalizeByEvent(hRecoDiMuPt_53X);
	normalizeByEvent(hRegitDiMuPt_53X);
	normalizeByEvent(hRecoDiMuMass_53X);
	normalizeByEvent(hRegitDiMuMass_53X);


	////// for 44X
  // single muon (muon, regitmuon -  glb, trk)
	//pt
  TH1F *hRecoMuPtGlb_44X = new TH1F("hRecoMuPtGlb_44X",";p_{T} (GeV/c);", nPtBin, ptMin, ptMax);
  TH1F *hRecoMuPtTrk_44X = new TH1F("hRecoMuPtTrk_44X",";p_{T} (GeV/c);", nPtBin, ptMin, ptMax);
  hRecoMuPtGlb_44X->Sumw2();
  hRecoMuPtTrk_44X->Sumw2();
  TH1F *hRegitMuPtGlb_44X = new TH1F("hRegitMuPtGlb_44X",";p_{T} (GeV/c);",nPtBin, ptMin, ptMax);
  TH1F *hRegitMuPtTrk_44X = new TH1F("hRegitMuPtTrk_44X",";p_{T} (GeV/c);",nPtBin, ptMin, ptMax);
  hRegitMuPtGlb_44X->Sumw2();
  hRegitMuPtTrk_44X->Sumw2();
	//eta
  TH1F *hRecoMuEtaGlb_44X = new TH1F("hRecoMuEtaGlb_44X",";#eta;",nEtaBin, -2.5, 2.5);
  TH1F *hRecoMuEtaTrk_44X = new TH1F("hRecoMuEtaTrk_44X",";#eta;",nEtaBin, -2.5, 2.5);
  hRecoMuEtaGlb_44X->Sumw2();
  hRecoMuEtaTrk_44X->Sumw2();
  TH1F *hRegitMuEtaGlb_44X = new TH1F("hRegitMuEtaGlb_44X",";#eta;",nEtaBin, -2.5, 2.5);
  TH1F *hRegitMuEtaTrk_44X = new TH1F("hRegitMuEtaTrk_44X",";#eta;",nEtaBin, -2.5, 2.5);
  hRegitMuEtaGlb_44X->Sumw2();
  hRegitMuEtaTrk_44X->Sumw2();
	//phi
  TH1F *hRecoMuPhiGlb_44X = new TH1F("hRecoMuPhiGlb_44X",";#phi;",nPhiBin, 0, 3.2);
  TH1F *hRecoMuPhiTrk_44X = new TH1F("hRecoMuPhiTrk_44X",";#phi;",nPhiBin, 0, 3.2);
  hRecoMuPhiGlb_44X->Sumw2();
  hRecoMuPhiTrk_44X->Sumw2();
  TH1F *hRegitMuPhiGlb_44X = new TH1F("hRegitMuPhiGlb_44X",";#phi;",nPhiBin, 0, 3.2);
  TH1F *hRegitMuPhiTrk_44X = new TH1F("hRegitMuPhiTrk_44X",";#phi;",nPhiBin, 0, 3.2);
  hRegitMuPhiGlb_44X->Sumw2();
  hRegitMuPhiTrk_44X->Sumw2();

	// dimuon (muon, regitmuon -  glb, trk)
	// pt
  TH1F *hRecoDiMuPt_44X = new TH1F("hRecoDiMuPt_44X",";p_{T} (GeV/c);",nPtBin, diptMin, diptMax);
  hRecoDiMuPt_44X ->Sumw2();
  TH1F *hRegitDiMuPt_44X = new TH1F("hRegitDiMuPt_44X",";p_{T} (GeV/c);",nPtBin, diptMin, diptMax);
  hRegitDiMuPt_44X->Sumw2();
	// mass
  TH1F *hRecoDiMuMass_44X = new TH1F("hRecoDiMuMass_44X",";m_{#mu#mu} (GeV/c^{2});",nMassBin, massMin, massMax);
  hRecoDiMuMass_44X->Sumw2();
  TH1F *hRegitDiMuMass_44X = new TH1F("hRegitDiMuMass_44X",";m_{#mu#mu} (GeV/c^{2});",nMassBin, massMin, massMax);
  hRegitDiMuMass_44X->Sumw2();

	// single muon	
  Ana44X->Draw("recoMu_pt>>hRecoMuPtGlb_44X","recoMu_Glb==1","E");
  Ana44X->Draw("recoMu_pt>>hRecoMuPtTrk_44X","recoMu_Trk==1","E");
  Ana44X->Draw("regrecoMu_pt>>hRegitMuPtGlb_44X","regrecoMu_Glb==1","E");
  Ana44X->Draw("regrecoMu_pt>>hRegitMuPtTrk_44X","regrecoMu_Trk==1","E");
  Ana44X->Draw("recoMu_eta>>hRecoMuEtaGlb_44X","recoMu_Glb==1","E");
  Ana44X->Draw("recoMu_eta>>hRecoMuEtaTrk_44X","recoMu_Trk==1","E");
  Ana44X->Draw("regrecoMu_eta>>hRegitMuEtaGlb_44X","regrecoMu_Glb==1","E");
  Ana44X->Draw("regrecoMu_eta>>hRegitMuEtaTrk_44X","regrecoMu_Trk==1","E");
  Ana44X->Draw("recoMu_phi>>hRecoMuPhiGlb_44X","recoMu_Glb==1","E");
  Ana44X->Draw("recoMu_phi>>hRecoMuPhiTrk_44X","recoMu_Trk==1","E");
  Ana44X->Draw("regrecoMu_phi>>hRegitMuPhiGlb_44X","regrecoMu_Glb==1","E");
  Ana44X->Draw("regrecoMu_phi>>hRegitMuPhiTrk_44X","regrecoMu_Trk==1","E");

	// dimuon
  Ana44X->Draw("recoDimu_pt>>hRecoDiMuPt_44X","","E");
  Ana44X->Draw("regrecoDimu_pt>>hRegitDiMuPt_44X","","E");
  Ana44X->Draw("recoDimu_mass>>hRecoDiMuMass_44X","","E");
  Ana44X->Draw("regrecoDimu_mass>>hRegitDiMuMass_44X","","E");
/*
	SetHistStyle(hRecoMuPtGlb_44X, 1,0);
	SetHistStyle(hRegitMuPtGlb_44X, 2,0);
	SetHistStyle(hRecoMuPtTrk_44X, 1,0);
	SetHistStyle(hRegitMuPtTrk_44X, 2,0);
	SetHistStyle(hRecoMuEtaGlb_44X, 1,0);
	SetHistStyle(hRegitMuEtaGlb_44X, 2,0);
	SetHistStyle(hRecoMuEtaTrk_44X, 1,0);
	SetHistStyle(hRegitMuEtaTrk_44X, 2,0);
	SetHistStyle(hRecoMuPhiGlb_44X, 1,0);
	SetHistStyle(hRegitMuPhiGlb_44X, 2,0);
	SetHistStyle(hRecoMuPhiTrk_44X, 1,0);
	SetHistStyle(hRegitMuPhiTrk_44X, 2,0);

	SetHistStyle(hRecoDiMuPt_44X, 1,0);
	SetHistStyle(hRegitDiMuPt_44X, 2,0);
	SetHistStyle(hRecoDiMuMass_44X, 1,0);
	SetHistStyle(hRegitDiMuMass_44X, 2,0);
*/
	normalizeByEvent(hRecoMuPtGlb_44X);
	normalizeByEvent(hRegitMuPtGlb_44X);
	normalizeByEvent(hRecoMuPtTrk_44X);
	normalizeByEvent(hRegitMuPtTrk_44X);
	normalizeByEvent(hRecoMuEtaGlb_44X);
	normalizeByEvent(hRegitMuEtaGlb_44X);
	normalizeByEvent(hRecoMuEtaTrk_44X);
	normalizeByEvent(hRegitMuEtaTrk_44X);
	normalizeByEvent(hRecoMuPhiGlb_44X);
	normalizeByEvent(hRegitMuPhiGlb_44X);
	normalizeByEvent(hRecoMuPhiTrk_44X);
	normalizeByEvent(hRegitMuPhiTrk_44X);

	normalizeByEvent(hRecoDiMuPt_44X);
	normalizeByEvent(hRegitDiMuPt_44X);
	normalizeByEvent(hRecoDiMuMass_44X);
	normalizeByEvent(hRegitDiMuMass_44X);


	////// ratio histo
  // single muon (muon, regitmuon -  glb, trk)
	//pt
  TH1F *hRecoMuPtGlb_RATIO = divideHistosSameBins(hRecoMuPtGlb_53X,hRecoMuPtGlb_44X);
  TH1F *hRecoMuPtTrk_RATIO = divideHistosSameBins(hRecoMuPtTrk_53X,hRecoMuPtTrk_44X);
  TH1F *hRegitMuPtGlb_RATIO = divideHistosSameBins(hRegitMuPtGlb_53X,hRegitMuPtGlb_44X);
  TH1F *hRegitMuPtTrk_RATIO = divideHistosSameBins(hRegitMuPtTrk_53X,hRegitMuPtTrk_44X);
	//eta
  TH1F *hRecoMuEtaGlb_RATIO = divideHistosSameBins(hRecoMuEtaGlb_53X,hRecoMuEtaGlb_44X);
  TH1F *hRecoMuEtaTrk_RATIO = divideHistosSameBins(hRecoMuEtaTrk_53X,hRecoMuEtaTrk_44X);
  TH1F *hRegitMuEtaGlb_RATIO = divideHistosSameBins(hRegitMuEtaGlb_53X,hRegitMuEtaGlb_44X);
  TH1F *hRegitMuEtaTrk_RATIO = divideHistosSameBins(hRegitMuEtaTrk_53X,hRegitMuEtaTrk_44X);
	//phi
  TH1F *hRecoMuPhiGlb_RATIO = divideHistosSameBins(hRecoMuPhiGlb_53X,hRecoMuPhiGlb_44X);
  TH1F *hRecoMuPhiTrk_RATIO = divideHistosSameBins(hRecoMuPhiTrk_53X,hRecoMuPhiTrk_44X);
  TH1F *hRegitMuPhiGlb_RATIO = divideHistosSameBins(hRegitMuPhiGlb_53X,hRegitMuPhiGlb_44X);
  TH1F *hRegitMuPhiTrk_RATIO = divideHistosSameBins(hRegitMuPhiTrk_53X,hRegitMuPhiTrk_44X);

	// dimuon (muon, regitmuon -  glb, trk)
	// pt
  TH1F *hRecoDiMuPt_RATIO = divideHistosSameBins(hRecoDiMuPt_53X,hRecoDiMuPt_44X);
  TH1F *hRegitDiMuPt_RATIO = divideHistosSameBins(hRegitDiMuPt_53X,hRegitDiMuPt_44X);
	// mass
  TH1F *hRecoDiMuMass_RATIO = divideHistosSameBins(hRecoDiMuMass_53X,hRecoDiMuMass_44X);
  TH1F *hRegitDiMuMass_RATIO = divideHistosSameBins(hRegitDiMuMass_53X,hRegitDiMuMass_44X);

	SetHistStyle(hRecoMuPtGlb_RATIO, 1,0);
	SetHistStyle(hRegitMuPtGlb_RATIO, 2,0);
	SetHistStyle(hRecoMuPtTrk_RATIO, 1,0);
	SetHistStyle(hRegitMuPtTrk_RATIO, 2,0);
	SetHistStyle(hRecoMuEtaGlb_RATIO, 1,0);
	SetHistStyle(hRegitMuEtaGlb_RATIO, 2,0);
	SetHistStyle(hRecoMuEtaTrk_RATIO, 1,0);
	SetHistStyle(hRegitMuEtaTrk_RATIO, 2,0);
	SetHistStyle(hRecoMuPhiGlb_RATIO, 1,0);
	SetHistStyle(hRegitMuPhiGlb_RATIO, 2,0);
	SetHistStyle(hRecoMuPhiTrk_RATIO, 1,0);
	SetHistStyle(hRegitMuPhiTrk_RATIO, 2,0);

	SetHistStyle(hRecoDiMuPt_RATIO, 1,0);
	SetHistStyle(hRegitDiMuPt_RATIO, 2,0);
	SetHistStyle(hRecoDiMuMass_RATIO, 1,0);
	SetHistStyle(hRegitDiMuMass_RATIO, 2,0);


	// draw and save plots
//  TLegend *legUR = new TLegend(0.68,0.60,0.87,0.77);
  TLegend *legUR = new TLegend(0.68,0.70,0.87,0.87);
  TLegend *legUM = new TLegend(0.42,0.70,0.61,0.88);
  TLegend *legBR = new TLegend(0.64,0.15,0.84,0.33);
  TLegend *legBL = new TLegend(0.24,0.15,0.44,0.33);
	SetLegendStyle(legUR);
	SetLegendStyle(legUM);
	SetLegendStyle(legBR);
	SetLegendStyle(legBL);

	TGraph* gr_unity = referenceLine(200, -200, 200);

  TCanvas *c1 = new TCanvas("c1","",600,600);
/*
	//single muon
  hRegitMuPtTrk_RATIO->SetMinimum(0);
  hRegitMuPtTrk_RATIO->SetMaximum(1.5);
  hRegitMuPtTrk_RATIO->GetYaxis()->SetTitle("53X/44X");
  hRegitMuPtTrk_RATIO->Draw();
  hRecoMuPtTrk_RATIO->Draw("same");
	gr_unity->Draw("L");
  legBR->SetHeader("Tracker Muons");
  legBR->AddEntry(hRecoMuPtTrk_RATIO,"reco muon","PL");
  legBR->AddEntry(hRegitMuPtTrk_RATIO,"regit muon","PL");
  legBR->Draw("same");
  c1->SaveAs(Form("%s_MuPtTrk_RATIO_reco_vs_regit.pdf",samplename.c_str()));
	legBR->Clear();
	c1->Clear();

  hRegitMuPtGlb_RATIO->SetMinimum(0);
  hRegitMuPtGlb_RATIO->SetMaximum(1.5);
  hRegitMuPtGlb_RATIO->GetYaxis()->SetTitle("53X/44X");
  hRegitMuPtGlb_RATIO->Draw();
  hRecoMuPtGlb_RATIO->Draw("same");
	gr_unity->Draw("L");
  legBR->SetHeader("Global Muons");
  legBR->AddEntry(hRecoMuPtGlb_RATIO,"reco muon","PL");
  legBR->AddEntry(hRegitMuPtGlb_RATIO,"regit muon","PL");
  legBR->Draw("same");
  c1->SaveAs(Form("%s_MuPtGlb_RATIO_reco_vs_regit.pdf",samplename.c_str()));
	legBR->Clear();
	c1->Clear();

  hRegitMuEtaTrk_RATIO->SetMinimum(0);
  hRegitMuEtaTrk_RATIO->SetMaximum(1.5);
  hRegitMuEtaTrk_RATIO->GetYaxis()->SetTitle("53X/44X");
  hRegitMuEtaTrk_RATIO->Draw();
  hRecoMuEtaTrk_RATIO->Draw("same");
	gr_unity->Draw("L");
  legBR->SetHeader("Tracker Muons");
  legBR->AddEntry(hRecoMuEtaTrk_RATIO,"reco muon","PL");
  legBR->AddEntry(hRegitMuEtaTrk_RATIO,"regit muon","PL");
  legBR->Draw("same");
  c1->SaveAs(Form("%s_MuEtaTrk_RATIO_reco_vs_regit.pdf",samplename.c_str()));
	legBR->Clear();
	c1->Clear();

  hRegitMuEtaGlb_RATIO->SetMinimum(0);
  hRegitMuEtaGlb_RATIO->SetMaximum(1.5);
  hRegitMuEtaGlb_RATIO->GetYaxis()->SetTitle("53X/44X");
  hRegitMuEtaGlb_RATIO->Draw();
  hRecoMuEtaGlb_RATIO->Draw("same");
	gr_unity->Draw("L");
  legBR->SetHeader("Global Muons");
  legBR->AddEntry(hRecoMuEtaGlb_RATIO,"reco muon","PL");
  legBR->AddEntry(hRegitMuEtaGlb_RATIO,"regit muon","PL");
  legBR->Draw("same");
  c1->SaveAs(Form("%s_MuEtaGlb_RATIO_reco_vs_regit.pdf",samplename.c_str()));
	legBR->Clear();
	c1->Clear();

  hRegitMuPhiTrk_RATIO->SetMinimum(0);
  hRegitMuPhiTrk_RATIO->SetMaximum(1.5);
  hRegitMuPhiTrk_RATIO->GetYaxis()->SetTitle("53X/44X");
  hRegitMuPhiTrk_RATIO->Draw();
  hRecoMuPhiTrk_RATIO->Draw("same");
	gr_unity->Draw("L");
  legBR->SetHeader("Tracker Muons");
  legBR->AddEntry(hRecoMuPhiTrk_RATIO,"reco muon","PL");
  legBR->AddEntry(hRegitMuPhiTrk_RATIO,"regit muon","PL");
  legBR->Draw("same");
  c1->SaveAs(Form("%s_MuPhiTrk_RATIO_reco_vs_regit.pdf",samplename.c_str()));
	legBR->Clear();
	c1->Clear();

  hRegitMuPhiGlb_RATIO->SetMinimum(0);
  hRegitMuPhiGlb_RATIO->SetMaximum(1.5);
  hRegitMuPhiGlb_RATIO->GetYaxis()->SetTitle("53X/44X");
  hRegitMuPhiGlb_RATIO->Draw();
  hRecoMuPhiGlb_RATIO->Draw("same");
	gr_unity->Draw("L");
  legBR->SetHeader("Global Muons");
  legBR->AddEntry(hRecoMuPhiGlb_RATIO,"reco muon","PL");
  legBR->AddEntry(hRegitMuPhiGlb_RATIO,"regit muon","PL");
  legBR->Draw("same");
  c1->SaveAs(Form("%s_MuPhiGlb_RATIO_reco_vs_regit.pdf",samplename.c_str()));
	legBR->Clear();
	c1->Clear();
*/
	//dimu
  hRegitDiMuPt_RATIO->SetMinimum(0);
  hRegitDiMuPt_RATIO->SetMaximum(1.5);
  hRegitDiMuPt_RATIO->GetYaxis()->SetTitle("53X/44X");
  hRegitDiMuPt_RATIO->Draw();
  hRecoDiMuPt_RATIO->Draw("same");
	gr_unity->Draw("L");
 	if (fileCode==0) { 
		legUR->SetHeader("Dimuons");
 		legUR->AddEntry(hRecoDiMuMass_RATIO,"reco muon","PL");
 		legUR->AddEntry(hRegitDiMuMass_RATIO,"regit muon","PL");
 		legUR->Draw("same");
	} else if (fileCode==1) {
		legBL->SetHeader("Dimuons");
 		legBL->AddEntry(hRecoDiMuMass_RATIO,"reco muon","PL");
 		legBL->AddEntry(hRegitDiMuMass_RATIO,"regit muon","PL");
 		legBL->Draw("same");
	}	
  c1->SaveAs(Form("%s_DiMuPt_RATIO_reco_vs_regit.pdf",samplename.c_str()));
	legUR->Clear();
	legBL->Clear();
	c1->Clear();

  hRegitDiMuMass_RATIO->SetMinimum(0);
  hRegitDiMuMass_RATIO->SetMaximum(1.5);
  hRegitDiMuMass_RATIO->GetYaxis()->SetTitle("53X/44X");
  hRegitDiMuMass_RATIO->Draw();
  hRecoDiMuMass_RATIO->Draw("same");
	gr_unity->Draw("L");
 	if (fileCode==0) { 
		legUR->SetHeader("Dimuons");
 		legUR->AddEntry(hRecoDiMuMass_RATIO,"reco muon","PL");
 		legUR->AddEntry(hRegitDiMuMass_RATIO,"regit muon","PL");
 		legUR->Draw("same");
	} else if (fileCode==1) {
		legBL->SetHeader("Dimuons");
 		legBL->AddEntry(hRecoDiMuMass_RATIO,"reco muon","PL");
 		legBL->AddEntry(hRegitDiMuMass_RATIO,"regit muon","PL");
 		legBL->Draw("same");
	}	
  c1->SaveAs(Form("%s_DiMuMass_RATIO_reco_vs_regit.pdf",samplename.c_str()));
	legUR->Clear();
	legBL->Clear();
	c1->Clear();

	return;

}

void normalizeByEvent(TH1F *histo) {
	//Int_t eventNum = histo->GetEntries();
	for (Int_t i=0; i<histo->GetNbinsX(); i++) {
		float content = histo->GetBinContent(i);
		float error = histo->GetBinError(i);
		histo->SetBinContent(i,content/histo->GetEntries());
		histo->SetBinError(i,error/histo->GetEntries());
	}
}

TH1F* divideHistosSameBins(TH1F* h_Num, TH1F* h_Den) {
	TH1F* h_ratio = (TH1F*)h_Num->Clone("h_ratio");
	h_ratio->Sumw2();
	h_ratio->Divide(h_Num,h_Den);
	return h_ratio;
}

TGraph* referenceLine(Double_t nBins, Double_t xMin, Double_t xMax) {
	Double_t x[531];
	Double_t y[531];
	for(Int_t n=0; n<nBins; n++) {
		x[n]=xMin+1.9*n*((xMax-xMin)/nBins);
		y[n]=1;
	}
	TGraph* gr_ref = new TGraph(nBins, x+1, y);
	//gr_ref->SetLineColor(kRed);
	gr_ref->SetLineStyle(3);
	return gr_ref;
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
