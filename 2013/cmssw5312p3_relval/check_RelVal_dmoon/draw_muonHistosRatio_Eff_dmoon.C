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
void normalizeByGenEntries(TH1F *histo, TH1F* Genhisto);
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

	// gen muon
  TH1F *hGenMuPt_53X = new TH1F("hGenMuPt_53X",";p_{T} (GeV/c);", nPtBin, ptMin, ptMax);
  hGenMuPt_53X->Sumw2();
  TH1F *hGenMuEta_53X = new TH1F("hGenMuEta_53X",";#eta;",nEtaBin, -2.5, 2.5);
  hGenMuEta_53X->Sumw2();
  TH1F *hGenMuPhi_53X = new TH1F("hGenMuPhi_53X",";#phi;",nPhiBin, 0, 3.2);
  hGenMuPhi_53X->Sumw2();
  TH1F *hGenDiMuPt_53X = new TH1F("hGenDiMuPt_53X",";p_{T} (GeV/c);",nPtBin, diptMin, diptMax);
  hGenDiMuPt_53X ->Sumw2();
  TH1F *hGenDiMuMass_53X = new TH1F("hGenDiMuMass_53X",";m_{#mu#mu} (GeV/c^{2});",nMassBin, massMin, massMax);
  hGenDiMuMass_53X->Sumw2();

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
	if (fileCode=0) {
		Ana53X->Draw("recoDimu_pt>>hRecoDiMuPt_53X","recoDimu_mass>3.0 && recoDimu_mass<3.2 && recoDimu_ch<0","E");
		Ana53X->Draw("regrecoDimu_pt>>hRegitDiMuPt_53X","regrecoDimu_mass>3.0 && regrecoDimu_mass<3.2 && regrecoDimu_ch<0","E");
	} else if (fileCode=1) {
	}
  Ana53X->Draw("recoDimu_mass>>hRecoDiMuMass_53X","recoDimu_mass>80. && recoDimu_mass<100. && recoDimu_ch<0","E");
  Ana53X->Draw("regrecoDimu_mass>>hRegitDiMuMass_53X","regrecoDimu_mass>80. && regrecoDimu_mass<100. && regrecoDimu_ch<0","E");

	// gen muon
  Ana53X->Draw("p_pt>>hGenMuPt_53X","","E");
  Ana53X->Draw("m_pt>>+hGenMuPt_53X","","E");
  Ana53X->Draw("p_eta>>hGenMuEta_53X","","E");
  Ana53X->Draw("m_eta>>+hGenMuEta_53X","","E");
  Ana53X->Draw("p_phi>>hGenMuPhi_53X","","E");
  Ana53X->Draw("m_phi>>+hGenMuPhi_53X","","E");
  Ana53X->Draw("d_pt>>hGenDiMuPt_53X","","E");
  Ana53X->Draw("d_mass>>hGenDiMuMass_53X","","E");

	std::cout << "total entries of recoMuPtGlb : " << hRecoMuPtGlb->GetEntries() << std::endl;
	std::cout << "total entries of recoMuPtGlb : " << hRecoMuPtGlb->GetEntries() << std::endl;
	std::cout << "total entries of recoMuPtGlb : " << hRecoMuPtGlb->GetEntries() << std::endl;
	std::cout << "total entries of recoMuPtGlb : " << hRecoMuPtGlb->GetEntries() << std::endl;
	std::cout << "total entries of recoMuPtGlb : " << hRecoMuPtGlb->GetEntries() << std::endl;
	std::cout << "total entries of recoMuPtGlb : " << hRecoMuPtGlb->GetEntries() << std::endl;
	std::cout << "total entries of recoMuPtGlb : " << hRecoMuPtGlb->GetEntries() << std::endl;
	std::cout << "total entries of recoMuPtGlb : " << hRecoMuPtGlb->GetEntries() << std::endl;
	std::cout << "total entries of recoMuPtGlb : " << hRecoMuPtGlb->GetEntries() << std::endl;
	std::cout << "total entries of recoMuPtGlb : " << hRecoMuPtGlb->GetEntries() << std::endl;
	std::cout << "total entries of recoMuPtGlb : " << hRecoMuPtGlb->GetEntries() << std::endl;
	std::cout << "total entries of recoMuPtGlb : " << hRecoMuPtGlb->GetEntries() << std::endl;
	std::cout << "total entries of recoMuPtGlb : " << hRecoMuPtGlb->GetEntries() << std::endl;
	std::cout << "total entries of recoMuPtGlb : " << hRecoMuPtGlb->GetEntries() << std::endl;
	std::cout << "total entries of recoMuPtGlb : " << hRecoMuPtGlb->GetEntries() << std::endl;
	std::cout << "total entries of recoMuPtGlb : " << hRecoMuPtGlb->GetEntries() << std::endl;
	std::cout << "total entries of recoMuPtGlb : " << hRecoMuPtGlb->GetEntries() << std::endl;
	std::cout << "total entries of recoMuPtGlb : " << hRecoMuPtGlb->GetEntries() << std::endl;
	std::cout << "total entries of recoMuPtGlb : " << hRecoMuPtGlb->GetEntries() << std::endl;
	std::cout << "total entries of recoMuPtGlb : " << hRecoMuPtGlb->GetEntries() << std::endl;
	std::cout << "total entries of recoMuPtGlb : " << hRecoMuPtGlb->GetEntries() << std::endl;
	std::cout << "total entries of recoMuPtGlb : " << hRecoMuPtGlb->GetEntries() << std::endl;


	normalizeByGenEntries(hRecoMuPtGlb_53X, hGenMuPt_53X);
	normalizeByGenEntries(hRegitMuPtGlb_53X, hGenMuPt_53X);
	normalizeByGenEntries(hRecoMuPtTrk_53X, hGenMuPt_53X);
	normalizeByGenEntries(hRegitMuPtTrk_53X, hGenMuPt_53X);
	normalizeByGenEntries(hRecoMuEtaGlb_53X, hGenMuEta_53X);
	normalizeByGenEntries(hRegitMuEtaGlb_53X, hGenMuEta_53X);
	normalizeByGenEntries(hRecoMuEtaTrk_53X, hGenMuEta_53X);
	normalizeByGenEntries(hRegitMuEtaTrk_53X, hGenMuEta_53X);
	normalizeByGenEntries(hRecoMuPhiGlb_53X, hGenMuPhi_53X);
	normalizeByGenEntries(hRegitMuPhiGlb_53X, hGenMuPhi_53X);
	normalizeByGenEntries(hRecoMuPhiTrk_53X, hGenMuPhi_53X);
	normalizeByGenEntries(hRegitMuPhiTrk_53X, hGenMuPhi_53X);

	normalizeByGenEntries(hRecoDiMuPt_53X, hGenDiMuPt_53X);
	normalizeByGenEntries(hRegitDiMuPt_53X, hGenDiMuPt_53X);
	normalizeByGenEntries(hRecoDiMuMass_53X, hGenDiMuMass_53X);
	normalizeByGenEntries(hRegitDiMuMass_53X, hGenDiMuMass_53X);


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

	// gen muon
  TH1F *hGenMuPt_44X = new TH1F("hGenMuPt_44X",";p_{T} (GeV/c);", nPtBin, ptMin, ptMax);
  hGenMuPt_44X->Sumw2();
  TH1F *hGenMuEta_44X = new TH1F("hGenMuEta_44X",";#eta;",nEtaBin, -2.5, 2.5);
  hGenMuEta_44X->Sumw2();
  TH1F *hGenMuPhi_44X = new TH1F("hGenMuPhi_44X",";#phi;",nPhiBin, 0, 3.2);
  hGenMuPhi_44X->Sumw2();
  TH1F *hGenDiMuPt_44X = new TH1F("hGenDiMuPt_44X",";p_{T} (GeV/c);",nPtBin, diptMin, diptMax);
  hGenDiMuPt_44X ->Sumw2();
  TH1F *hGenDiMuMass_44X = new TH1F("hGenDiMuMass_44X",";m_{#mu#mu} (GeV/c^{2});",nMassBin, massMin, massMax);
  hGenDiMuMass_44X->Sumw2();

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

	// gen muon
  Ana44X->Draw("p_pt>>hGenMuPt_44X","","E");
  Ana44X->Draw("m_pt>>+hGenMuPt_44X","","E");
  Ana44X->Draw("p_eta>>hGenMuEta_44X","","E");
  Ana44X->Draw("m_eta>>+hGenMuEta_44X","","E");
  Ana44X->Draw("p_phi>>hGenMuPhi_44X","","E");
  Ana44X->Draw("m_phi>>+hGenMuPhi_44X","","E");
  Ana44X->Draw("d_pt>>hGenDiMuPt_44X","","E");
  Ana44X->Draw("d_mass>>hGenDiMuMass_44X","","E");

	normalizeByGenEntries(hRecoMuPtGlb_44X, hGenMuPt_44X);
	normalizeByGenEntries(hRegitMuPtGlb_44X, hGenMuPt_44X);
	normalizeByGenEntries(hRecoMuPtTrk_44X, hGenMuPt_44X);
	normalizeByGenEntries(hRegitMuPtTrk_44X, hGenMuPt_44X);
	normalizeByGenEntries(hRecoMuEtaGlb_44X, hGenMuEta_44X);
	normalizeByGenEntries(hRegitMuEtaGlb_44X, hGenMuEta_44X);
	normalizeByGenEntries(hRecoMuEtaTrk_44X, hGenMuEta_44X);
	normalizeByGenEntries(hRegitMuEtaTrk_44X, hGenMuEta_44X);
	normalizeByGenEntries(hRecoMuPhiGlb_44X, hGenMuPhi_44X);
	normalizeByGenEntries(hRegitMuPhiGlb_44X, hGenMuPhi_44X);
	normalizeByGenEntries(hRecoMuPhiTrk_44X, hGenMuPhi_44X);
	normalizeByGenEntries(hRegitMuPhiTrk_44X, hGenMuPhi_44X);

	normalizeByGenEntries(hRecoDiMuPt_44X, hGenDiMuPt_44X);
	normalizeByGenEntries(hRegitDiMuPt_44X, hGenDiMuPt_44X);
	normalizeByGenEntries(hRecoDiMuMass_44X, hGenDiMuMass_44X);
	normalizeByGenEntries(hRegitDiMuMass_44X, hGenDiMuMass_44X);


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


	//////// draw and save plots
  TLegend *legUR01 = new TLegend(0.68,0.60,0.87,0.77);
  TLegend *legUR02 = new TLegend(0.68,0.70,0.87,0.87);
  TLegend *legUM = new TLegend(0.42,0.70,0.61,0.88);
  TLegend *legBR = new TLegend(0.64,0.15,0.84,0.33);
  TLegend *legBL = new TLegend(0.24,0.15,0.44,0.33);
	SetLegendStyle(legUR01);
	SetLegendStyle(legUR02);
	SetLegendStyle(legUM);
	SetLegendStyle(legBR);
	SetLegendStyle(legBL);

	TGraph* gr_unity = referenceLine(200, -200, 200);

  TCanvas *c1 = new TCanvas("c1","",600,600);

	//////// 1. draw distribution

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

	///// 2. Ratio

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

	//dimu
  hRegitDiMuPt_RATIO->SetMinimum(0);
  hRegitDiMuPt_RATIO->SetMaximum(1.5);
  hRegitDiMuPt_RATIO->GetYaxis()->SetTitle("53X/44X");
  hRegitDiMuPt_RATIO->Draw();
  hRecoDiMuPt_RATIO->Draw("same");
	gr_unity->Draw("L");
 	if (fileCode==0) { 
		legUR02->SetHeader("Dimuons");
 		legUR02->AddEntry(hRecoDiMuMass_RATIO,"reco muon","PL");
 		legUR02->AddEntry(hRegitDiMuMass_RATIO,"regit muon","PL");
 		legUR02->Draw("same");
	} else if (fileCode==1) {
		legBL->SetHeader("Dimuons");
 		legBL->AddEntry(hRecoDiMuMass_RATIO,"reco muon","PL");
 		legBL->AddEntry(hRegitDiMuMass_RATIO,"regit muon","PL");
 		legBL->Draw("same");
	}	
  c1->SaveAs(Form("%s_DiMuPt_RATIO_reco_vs_regit.pdf",samplename.c_str()));
	legUR02->Clear();
	legBL->Clear();
	c1->Clear();

  hRegitDiMuMass_RATIO->SetMinimum(0);
  hRegitDiMuMass_RATIO->SetMaximum(1.5);
  hRegitDiMuMass_RATIO->GetYaxis()->SetTitle("53X/44X");
  hRegitDiMuMass_RATIO->Draw();
  hRecoDiMuMass_RATIO->Draw("same");
	gr_unity->Draw("L");
 	if (fileCode==0) { 
		legUR02->SetHeader("Dimuons");
 		legUR02->AddEntry(hRecoDiMuMass_RATIO,"reco muon","PL");
 		legUR02->AddEntry(hRegitDiMuMass_RATIO,"regit muon","PL");
 		legUR02->Draw("same");
	} else if (fileCode==1) {
		legBL->SetHeader("Dimuons");
 		legBL->AddEntry(hRecoDiMuMass_RATIO,"reco muon","PL");
 		legBL->AddEntry(hRegitDiMuMass_RATIO,"regit muon","PL");
 		legBL->Draw("same");
	}	
  c1->SaveAs(Form("%s_DiMuMass_RATIO_reco_vs_regit.pdf",samplename.c_str()));
	legUR02->Clear();
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

void normalizeByGenEntries(TH1F *histo, TH1F *Genhisto) {
	//Int_t eventNum = histo->GetEntries();
	for (Int_t i=0; i<histo->GetNbinsX(); i++) {
		float content = histo->GetBinContent(i);
		float error = histo->GetBinError(i);
		histo->SetBinContent(i,content/Genhisto->GetEntries());
		histo->SetBinError(i,error/Genhisto->GetEntries());
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
