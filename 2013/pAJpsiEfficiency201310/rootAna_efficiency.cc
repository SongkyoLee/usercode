#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <TString.h>

#include <TROOT.h>
#include "TSystem.h"
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TNtuple.h>
#include <TMath.h>
#include <math.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include "TRandom3.h"
#include "TClonesArray.h"
#include <TAxis.h>
#include <cmath>
#include <TLorentzRotation.h>

#include <TCanvas.h>
#include <TStyle.h>
#include <TPaveStats.h>

// Basically our basic frame is collision frame, in this code all value means in collision frame.

const double convvar = -0.47; // conversion constant y=0(collision)==y=-0.47(LAB frame)  

bool kineCut(bool, double muPt, double muEta, double muP);
bool massCut1(double lv_dimu_mass);
bool massCut2(double lv_dimu_mass);

struct Condition {
	double theCentrality; 
  int theType, theSign, Reco_QQ_trig;
  double theMass, theRapidity, thePt, thePhi;
  double mupl_p, mumi_p, mupl_pt, mumi_pt, mupl_eta, mumi_eta;
} ;

void rootAna_efficiency(char *stringA = "m24_p147_pt_65300", bool isBoosted = true, int fileCode = 1, double rapbinmin=-2.4, double rapbinmax=1.47, double ptbinmin=0.0, double ptbinmax=30.0){

	// # of event range
	int initev =0;
	int nevt = -1; //all
	//int nevt = 5000;
		
//	gROOT->Macro("setStyle.C+");
	gROOT->Macro("rootlogon.C+");
	gStyle->SetCanvasDefW(800);

	TFile *f1;
	char* samplename;
	//double minylab;
	//double maxylab;

// read-in root file
//## fileCode : 0=PR, 1=NP, 2=test
	if (isBoosted) {
		//minylab=-2.4;
		//maxylab=1.47;
//		if (fileCode==0) {f1 = new TFile("/afs/cern.ch/work/k/kyolee/private/cms538HI/src/HiAnalysis/HiOnia/test/PRMC_ppboostedMC5023_20131113/res/merged_PRMC_eff_Histos.root");samplename="PRMC_boosted"; }
		if (fileCode==0) {f1 = new TFile("/home/songkyo/kyo/2013/08_EffTmp/PRMC_eff_rootFile/merged_PRMC_eff_Histos.root"); samplename="PRMC_boosted"; }
		else if (fileCode==1) {f1 = new TFile("/home/songkyo/kyo/2013/08_EffTmp/NPMC_eff_rootFile/merged_NPMC_eff_Histos.root"); samplename="NPMC_boosted"; }
	} else {
		//minylab=-2.4;
		//maxylab=2.4;
	}

	const char* datestring = Form("%s_%s",stringA,samplename);
	std::cout << "datestring: " << datestring << std::endl;

	//read-in tree
	TTree *mytree = (TTree*)f1->Get("myTree");

  UInt_t          eventNb;
  Int_t           Centrality;
  Int_t           Reco_QQ_size;
  Int_t           Reco_QQ_type[20];   //[Reco_QQ_size] : for Data GG, GT, TT?
  Int_t           Reco_QQ_sign[20];   //[Reco_QQ_size] : 0=+,- / 1=+/+, 2=-/-
  Int_t           Reco_QQ_trig[20];   //[Reco_QQ_size] : DoubleMuOpen ==1
  TClonesArray    *Reco_QQ_4mom;
  TClonesArray    *Reco_QQ_mupl_4mom;
  TClonesArray    *Reco_QQ_mumi_4mom;
  Int_t           Gen_QQ_size;
  Int_t           Gen_QQ_type[20];	//[Gen_QQ_size] : for MC PR=0 / NP=1
  TClonesArray    *Gen_QQ_4mom;
  TClonesArray    *Gen_QQ_mupl_4mom;
  TClonesArray    *Gen_QQ_mumi_4mom;

  TBranch        *b_eventNb;
  TBranch        *b_Centrality;   //!
  TBranch        *b_Reco_QQ_size;   //!
  TBranch        *b_Reco_QQ_type;   //!
  TBranch        *b_Reco_QQ_sign;   //!
  TBranch        *b_Reco_QQ_trig;   //!
  TBranch        *b_Reco_QQ_4mom;   //!
  TBranch        *b_Reco_QQ_mupl_4mom;   //!
  TBranch        *b_Reco_QQ_mumi_4mom;   //!
  TBranch        *b_Gen_QQ_size;   //!
  TBranch        *b_Gen_QQ_type;
  TBranch        *b_Gen_QQ_4mom;   //!
  TBranch        *b_Gen_QQ_mupl_4mom;   //!
  TBranch        *b_Gen_QQ_mumi_4mom;   //!

  TLorentzVector* JP_Reco = new TLorentzVector;
  TLorentzVector* m1P_Reco = new TLorentzVector;
  TLorentzVector* m2P_Reco = new TLorentzVector;
  TLorentzVector* JP_Gen = new TLorentzVector;
  TLorentzVector* m1P_Gen = new TLorentzVector;
  TLorentzVector* m2P_Gen = new TLorentzVector;

	Reco_QQ_4mom =0;
	Reco_QQ_mupl_4mom =0;
	Reco_QQ_mumi_4mom =0;
	Gen_QQ_4mom =0;
	Gen_QQ_mupl_4mom =0;
	Gen_QQ_mumi_4mom =0;

	// read-in branches
	mytree->SetBranchAddress("eventNb", &eventNb, &b_eventNb);
	mytree->SetBranchAddress("Centrality", &Centrality, &b_Centrality);
  mytree->SetBranchAddress("Reco_QQ_size", &Reco_QQ_size, &b_Reco_QQ_size);
  mytree->SetBranchAddress("Reco_QQ_type", Reco_QQ_type, &b_Reco_QQ_type);
  mytree->SetBranchAddress("Reco_QQ_sign", Reco_QQ_sign, &b_Reco_QQ_sign);
  mytree->SetBranchAddress("Reco_QQ_trig", Reco_QQ_trig, &b_Reco_QQ_trig);
  mytree->SetBranchAddress("Reco_QQ_4mom", &Reco_QQ_4mom, &b_Reco_QQ_4mom);
  mytree->SetBranchAddress("Reco_QQ_mupl_4mom", &Reco_QQ_mupl_4mom, &b_Reco_QQ_mupl_4mom);
  mytree->SetBranchAddress("Reco_QQ_mumi_4mom", &Reco_QQ_mumi_4mom, &b_Reco_QQ_mumi_4mom);
	mytree->SetBranchAddress("Gen_QQ_size", &Gen_QQ_size, &b_Gen_QQ_size);
	mytree->SetBranchAddress("Gen_QQ_type", Gen_QQ_type, &b_Gen_QQ_type);
  mytree->SetBranchAddress("Gen_QQ_4mom", &Gen_QQ_4mom, &b_Gen_QQ_4mom);
  mytree->SetBranchAddress("Gen_QQ_mupl_4mom", &Gen_QQ_mupl_4mom, &b_Gen_QQ_mupl_4mom);
  mytree->SetBranchAddress("Gen_QQ_mumi_4mom", &Gen_QQ_mumi_4mom, &b_Gen_QQ_mumi_4mom);


	using namespace std;

	// Definition of binning
	// binCode ==1
	// --- pt Bin
	Double_t ptBinsArr1[] = {6.5, 30.0}; //1bin
	Double_t ptBinsArr2[] = {6.5, 8.0, 10.0, 13.0, 30.0}; //4bin
	const Int_t nPtBins1 = sizeof(ptBinsArr1)/sizeof(double)-1;
	const Int_t nPtBins2 = sizeof(ptBinsArr2)/sizeof(double)-1;
	cout << "nPtBins1=" << nPtBins1 << endl;
	cout << "nPtBins2=" << nPtBins2 << endl;

	// --- y Bin
	Double_t yBinsArr1[] = {-2.4, -1.97, -1.72, -1.47, -1.22, -0.97, -0.72, -0.47, -0.22, 0.03, 0.28, 0.53, 0.78, 1.03, 1.47}; //14bin
	Double_t yBinsArr2[] = {-2.4, -0.47, 1.47}; //2bin
	const Int_t nYBins1 = sizeof(yBinsArr1)/sizeof(double)-1;
	const Int_t nYBins2 = sizeof(yBinsArr2)/sizeof(double)-1;
	cout << "nYBins1=" << nYBins1 << endl;
	cout << "nYBins2=" << nYBins2 << endl;

	std::cout << "datestring: " << datestring << std::endl;

	////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////
	// define 2D hist
	// fine binning
	TH2D *h2D_NoCut_Reco_pt_y = new TH2D(Form("h2D_NoCut_Reco_pt_y_%s",stringA),"",500,-2.5,2.5,300,0,30);
	TH2D *h2D_NoCut_Gen_pt_y = new TH2D(Form("h2D_NoCut_Gen_pt_y_%s",stringA),"",500,-2.5,2.5,300,0,30);
	TH2D *h2D_Den_pt_y = new TH2D(Form("h2D_Den_pt_y_%s",stringA),"",500,-2.5,2.5,300,0,30);
	TH2D *h2D_Num_pt_y = new TH2D(Form("h2D_Num_pt_y_%s",stringA),"",500,-2.5,2.5,300,0,30);
	TH2D *h2D_Eff_pt_y = new TH2D(Form("h2D_Eff_pt_y_%s",stringA),"",500,-2.5,2.5,300,0,30);
	// with defined binning 1 (y dependence)
	TH2D *h2D_NoCut_Reco_pt_y_bin1 = new TH2D(Form("h2D_NoCut_Reco_pt_y_bin1_%s",stringA),"",nYBins1,yBinsArr1,nPtBins1,ptBinsArr1);
	TH2D *h2D_NoCut_Gen_pt_y_bin1 = new TH2D(Form("h2D_NoCut_Gen_pt_y_bin1_%s",stringA),"",nYBins1,yBinsArr1,nPtBins1,ptBinsArr1);
	TH2D *h2D_Den_pt_y_bin1 = new TH2D(Form("h2D_Den_pt_y_bin1_%s",stringA),"",nYBins1,yBinsArr1,nPtBins1,ptBinsArr1);
	TH2D *h2D_Num_pt_y_bin1 = new TH2D(Form("h2D_Num_pt_y_bin1_%s",stringA),"",nYBins1,yBinsArr1,nPtBins1,ptBinsArr1);
	TH2D *h2D_Eff_pt_y_bin1 = new TH2D(Form("h2D_Eff_pt_y_bin1_%s",stringA),"",nYBins1,yBinsArr1,nPtBins1,ptBinsArr1);
	// with defined binning 2 (pt dependence)
	TH2D *h2D_NoCut_Reco_pt_y_bin2 = new TH2D(Form("h2D_NoCut_Reco_pt_y_bin2_%s",stringA),"",nYBins2,yBinsArr2,nPtBins2,ptBinsArr2);
	TH2D *h2D_NoCut_Gen_pt_y_bin2 = new TH2D(Form("h2D_NoCut_Gen_pt_y_bin2_%s",stringA),"",nYBins2,yBinsArr2,nPtBins2,ptBinsArr2);
	TH2D *h2D_Den_pt_y_bin2 = new TH2D(Form("h2D_Den_pt_y_bin2_%s",stringA),"",nYBins2,yBinsArr2,nPtBins2,ptBinsArr2);
	TH2D *h2D_Num_pt_y_bin2 = new TH2D(Form("h2D_Num_pt_y_bin2_%s",stringA),"",nYBins2,yBinsArr2,nPtBins2,ptBinsArr2);
	TH2D *h2D_Eff_pt_y_bin2 = new TH2D(Form("h2D_Eff_pt_y_bin2_%s",stringA),"",nYBins2,yBinsArr2,nPtBins2,ptBinsArr2);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// define 1D hist
	// fine binning
	TH1D *h1D_NoCut_Reco_y = new TH1D(Form("h1D_NoCut_Reco_y_%s",stringA),"",500,-2.5,2.5);
	TH1D *h1D_NoCut_Gen_y = new TH1D(Form("h1D_NoCut_Gen_y_%s",stringA),"",500,-2.5,2.5);
	TH1D *h1D_NoCut_Reco_pt = new TH1D(Form("h1D_NoCut_Reco_pt_%s",stringA),"",300,0,30);
	TH1D *h1D_NoCut_Gen_pt = new TH1D(Form("h1D_NoCut_Gen_pt_%s",stringA),"",300,0,30);
	TH1D *h1D_Den_y = new TH1D(Form("h1D_Den_y_%s",stringA),"",500,-2.5,2.5);
	TH1D *h1D_Den_pt = new TH1D(Form("h1D_Den_pt_%s",stringA),"",300,0,30);
	TH1D *h1D_Num_y = new TH1D(Form("h1D_Num_y_%s",stringA),"",500,-2.5,2.5);
	TH1D *h1D_Num_pt = new TH1D(Form("h1D_Num_pt_%s",stringA),"",300,0,30);
	TH1D *h1D_Eff_y = new TH1D(Form("h1D_Eff_y_%s",stringA),"",500,-2.5,2.5);
	TH1D *h1D_Eff_pt = new TH1D(Form("h1D_Eff_pt_%s",stringA),"",300,0,30);
	// with defined binning 1 (y dependence)
	TH1D *h1D_NoCut_Reco_y_bin1 = new TH1D(Form("h1D_NoCut_Reco_y_bin1_%s",stringA),"",nYBins1,yBinsArr1);
	TH1D *h1D_NoCut_Gen_y_bin1 = new TH1D(Form("h1D_NoCut_Gen_y_bin1_%s",stringA),"",nYBins1,yBinsArr1);
	TH1D *h1D_Den_y_bin1 = new TH1D(Form("h1D_Den_y_bin1_%s",stringA),"",nYBins1,yBinsArr1);
	TH1D *h1D_Num_y_bin1 = new TH1D(Form("h1D_Num_y_bin1_%s",stringA),"",nYBins1,yBinsArr1);
	TH1D *h1D_Eff_y_bin1 = new TH1D(Form("h1D_Eff_y_bin1_%s",stringA),"",nYBins1,yBinsArr1);
	// with defined binning 2 (pt dependence - FW)
	TH1D *h1D_NoCut_Reco_pt_bin2_FW = new TH1D(Form("h1D_NoCut_Reco_pt_bin2_FW_%s",stringA),"",nPtBins2,ptBinsArr2);
	TH1D *h1D_NoCut_Gen_pt_bin2_FW = new TH1D(Form("h1D_NoCut_Gen_pt_bin2_FW_%s",stringA),"",nPtBins2,ptBinsArr2);
	TH1D *h1D_Den_pt_bin2_FW = new TH1D(Form("h1D_Den_pt_bin2_FW_%s",stringA),"",nPtBins2,ptBinsArr2);
	TH1D *h1D_Num_pt_bin2_FW = new TH1D(Form("h1D_Num_pt_bin2_FW_%s",stringA),"",nPtBins2,ptBinsArr2);
	TH1D *h1D_Eff_pt_bin2_FW = new TH1D(Form("h1D_Eff_pt_bin2_FW_%s",stringA),"",nPtBins2,ptBinsArr2);
	// with defined binning 2 (pt dependence - BW)
	TH1D *h1D_NoCut_Reco_pt_bin2_BW = new TH1D(Form("h1D_NoCut_Reco_pt_bin2_BW_%s",stringA),"",nPtBins2,ptBinsArr2);
	TH1D *h1D_NoCut_Gen_pt_bin2_BW = new TH1D(Form("h1D_NoCut_Gen_pt_bin2_BW_%s",stringA),"",nPtBins2,ptBinsArr2);
	TH1D *h1D_Den_pt_bin2_BW = new TH1D(Form("h1D_Den_pt_bin2_BW_%s",stringA),"",nPtBins2,ptBinsArr2);
	TH1D *h1D_Num_pt_bin2_BW = new TH1D(Form("h1D_Num_pt_bin2_BW_%s",stringA),"",nPtBins2,ptBinsArr2);
	TH1D *h1D_Eff_pt_bin2_BW = new TH1D(Form("h1D_Eff_pt_bin2_BW_%s",stringA),"",nPtBins2,ptBinsArr2);

	std::cout << "TH1, TH2 definition, datestring: " << datestring << std::endl;

	// temp - mass check
	TH1D *h1D_Reco_M = new TH1D("h1D_Reco_M","h1D_Reco_M",100,2.6,3.5);
	TH1D *h1D_Num_M = new TH1D("h1D_Num_M","h1D_Num_M",100,2.6,3.5);
	TH1D *h1D_Gen_M = new TH1D("h1D_Gen_M","h1D_Gen_M",100,2.6,3.5);
	TH1D *h1D_Den_M = new TH1D("h1D_Den_M","h1D_Den_M",100,2.6,3.5);

	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	//2D hist
	h2D_Den_pt_y->Sumw2();
	h2D_Num_pt_y->Sumw2();
	h2D_Eff_pt_y->Sumw2();

	h2D_Den_pt_y_bin1->Sumw2();
	h2D_Num_pt_y_bin1->Sumw2();
	h2D_Eff_pt_y_bin1->Sumw2();

	h2D_Den_pt_y_bin2->Sumw2();
	h2D_Num_pt_y_bin2->Sumw2();
	h2D_Eff_pt_y_bin2->Sumw2();

	//1D hist
	h1D_Den_y->Sumw2();
	h1D_Num_y->Sumw2();
	h1D_Eff_y->Sumw2();
	h1D_Den_pt->Sumw2();
	h1D_Num_pt->Sumw2();
	h1D_Eff_pt->Sumw2();

	h1D_Den_y_bin1->Sumw2();
	h1D_Num_y_bin1->Sumw2();
	h1D_Eff_y_bin1->Sumw2();

	h1D_Den_pt_bin2_FW->Sumw2();
	h1D_Num_pt_bin2_FW->Sumw2();
	h1D_Eff_pt_bin2_FW->Sumw2();
	h1D_Den_pt_bin2_BW->Sumw2();
	h1D_Num_pt_bin2_BW->Sumw2();
	h1D_Eff_pt_bin2_BW->Sumw2();

	h1D_Reco_M->Sumw2();
	h1D_Num_M->Sumw2();
	h1D_Gen_M->Sumw2();
	h1D_Den_M->Sumw2();

	////////////////////////////////////////////////////////////////////////////////////////////////

	std::cout << "before check eff. datestring: " << datestring << std::endl;

	// event loop start
	if(nevt == -1) nevt = mytree->GetEntries();
	for(int iev=initev; iev<nevt; ++iev){
		if(iev%100000==0) cout << ">>>>> EVENT " << iev << " / " << mytree->GetEntries() <<  endl;

		mytree->GetEntry(iev);

		// Reco_QQ_size loop
		for (Int_t irqq=0; irqq<Reco_QQ_size; ++irqq) {
			struct Condition Jpsi_Reco; 
			JP_Reco = (TLorentzVector*) Reco_QQ_4mom->At(irqq);
			m1P_Reco = (TLorentzVector*) Reco_QQ_mupl_4mom->At(irqq);
			m2P_Reco = (TLorentzVector*) Reco_QQ_mumi_4mom->At(irqq);

			Jpsi_Reco.theCentrality = 97.5; // for pp!
			Jpsi_Reco.theType = Reco_QQ_type[irqq]; // GG, GT, TT
			Jpsi_Reco.theSign = Reco_QQ_sign[irqq];
			Jpsi_Reco.Reco_QQ_trig  = Reco_QQ_trig[irqq];

			Jpsi_Reco.theMass = JP_Reco->M();
			Jpsi_Reco.theRapidity = JP_Reco->Rapidity(); // boosted so that -2.4 < y_{lab} < 1.47	
			Jpsi_Reco.thePt = JP_Reco->Pt();
			Jpsi_Reco.thePhi = JP_Reco->Phi();

			Jpsi_Reco.mupl_p = sqrt( (m1P_Reco->Px())*(m1P_Reco->Px()) + (m1P_Reco->Py())*(m1P_Reco->Py()) + (m1P_Reco->Pz())*(m1P_Reco->Pz()) );
			Jpsi_Reco.mumi_p = sqrt( (m2P_Reco->Px())*(m2P_Reco->Px()) + (m2P_Reco->Py())*(m2P_Reco->Py()) + (m2P_Reco->Pz())*(m2P_Reco->Pz()) );
			Jpsi_Reco.mupl_pt = m1P_Reco->Pt();
			Jpsi_Reco.mumi_pt = m2P_Reco->Pt();
			Jpsi_Reco.mupl_eta = m1P_Reco->Eta();
			Jpsi_Reco.mumi_eta = m2P_Reco->Eta();

			// trigger check for - DoubleMuOpen_v1
			if ( ! (Jpsi_Reco.Reco_QQ_trig&1)==1 ) continue;

			// --- cut01 : RECO - No cut except for trigger
			h2D_NoCut_Reco_pt_y->Fill(Jpsi_Reco.theRapidity, Jpsi_Reco.thePt);
			h2D_NoCut_Reco_pt_y_bin1->Fill(Jpsi_Reco.theRapidity,Jpsi_Reco.thePt);
			h2D_NoCut_Reco_pt_y_bin2->Fill(Jpsi_Reco.theRapidity,Jpsi_Reco.thePt);
	
			h1D_NoCut_Reco_y->Fill(Jpsi_Reco.theRapidity);
			h1D_NoCut_Reco_pt->Fill(Jpsi_Reco.thePt);
			h1D_NoCut_Reco_y_bin1->Fill(Jpsi_Reco.theRapidity);
			h1D_NoCut_Reco_pt_bin2_FW->Fill(Jpsi_Reco.thePt);
			h1D_NoCut_Reco_pt_bin2_BW->Fill(Jpsi_Reco.thePt);
			h1D_Reco_M->Fill(Jpsi_Reco.theMass);

			// --- cut02 : RECO for numerator
			bool yn_reco = false;
			if ( Jpsi_Reco.theSign ==0 
				&& massCut1(Jpsi_Reco.theMass)
				&& kineCut(isBoosted, Jpsi_Reco.mupl_pt, Jpsi_Reco.mupl_eta, Jpsi_Reco.mupl_p) 
				&& kineCut(isBoosted, Jpsi_Reco.mumi_pt, Jpsi_Reco.mumi_eta, Jpsi_Reco.mumi_p) 
				&& ptbinmin<=Jpsi_Reco.thePt && Jpsi_Reco.thePt <ptbinmax 
				&& rapbinmin<=Jpsi_Reco.theRapidity && Jpsi_Reco.theRapidity <rapbinmax) {
					h1D_Num_M->Fill(Jpsi_Reco.theMass);
					if (massCut2(Jpsi_Reco.theMass)) yn_reco = true;
			}

			if (yn_reco == true){
				h2D_Num_pt_y->Fill(Jpsi_Reco.theRapidity,Jpsi_Reco.thePt);
				h2D_Num_pt_y_bin1->Fill(Jpsi_Reco.theRapidity,Jpsi_Reco.thePt);
				h2D_Num_pt_y_bin2->Fill(Jpsi_Reco.theRapidity,Jpsi_Reco.thePt);

				h1D_Num_y->Fill(Jpsi_Reco.theRapidity);
				h1D_Num_pt->Fill(Jpsi_Reco.thePt);
				// cut for 1D hist with binning
				if (6.5<=Jpsi_Reco.thePt)	{
					h1D_Num_y_bin1->Fill(Jpsi_Reco.theRapidity);
				}
				if (-2.4<=Jpsi_Reco.theRapidity && Jpsi_Reco.theRapidity<-0.47) {
					h1D_Num_pt_bin2_FW->Fill(Jpsi_Reco.thePt);
				}
				if (-0.47<=Jpsi_Reco.theRapidity && Jpsi_Reco.theRapidity<1.47) {
					h1D_Num_pt_bin2_BW->Fill(Jpsi_Reco.thePt);
				}
			} // end of yn_reco
		} //end of Reco_QQ_size loop

		// Gen_QQ_size loop
		for (Int_t igqq=0; igqq<Gen_QQ_size; ++igqq) {
			struct Condition Jpsi_Gen; 
			JP_Gen = (TLorentzVector*) Gen_QQ_4mom->At(igqq);
			m1P_Gen = (TLorentzVector*) Gen_QQ_mupl_4mom->At(igqq);
			m2P_Gen = (TLorentzVector*) Gen_QQ_mumi_4mom->At(igqq);

			// variables only used for Reco
			Jpsi_Gen.theMass = JP_Gen->M();
			Jpsi_Gen.Reco_QQ_trig  = 0;
			Jpsi_Gen.theSign = 0;
			
			Jpsi_Gen.theCentrality = 97.5; // for pp!
			Jpsi_Gen.theType = Gen_QQ_type[igqq]; // PR or NP

			Jpsi_Gen.theRapidity = JP_Gen->Rapidity(); // boosted so that -2.4 < y_{lab} < 1.47	
			Jpsi_Gen.thePt = JP_Gen->Pt();
			Jpsi_Gen.thePhi = JP_Gen->Phi();

			Jpsi_Gen.mupl_p = sqrt( (m1P_Gen->Px())*(m1P_Gen->Px()) + (m1P_Gen->Py())*(m1P_Gen->Py()) + (m1P_Gen->Pz())*(m1P_Gen->Pz()) );
			Jpsi_Gen.mumi_p = sqrt( (m2P_Gen->Px())*(m2P_Gen->Px()) + (m2P_Gen->Py())*(m2P_Gen->Py()) + (m2P_Gen->Pz())*(m2P_Gen->Pz()) );
			Jpsi_Gen.mupl_pt = m1P_Reco->Pt();
			Jpsi_Gen.mumi_pt = m2P_Reco->Pt();
			Jpsi_Gen.mupl_eta = m1P_Gen->Eta();
			Jpsi_Gen.mumi_eta = m2P_Gen->Eta();

			// --- cut01 : GEN - No cut
			h2D_NoCut_Gen_pt_y->Fill(Jpsi_Gen.theRapidity, Jpsi_Gen.thePt);
			h2D_NoCut_Gen_pt_y_bin1->Fill(Jpsi_Gen.theRapidity,Jpsi_Gen.thePt);
			h2D_NoCut_Gen_pt_y_bin2->Fill(Jpsi_Gen.theRapidity,Jpsi_Gen.thePt);
	
			h1D_NoCut_Gen_y->Fill(Jpsi_Gen.theRapidity);
			h1D_NoCut_Gen_pt->Fill(Jpsi_Gen.thePt);
			h1D_NoCut_Gen_y_bin1->Fill(Jpsi_Gen.theRapidity);
			h1D_NoCut_Gen_pt_bin2_FW->Fill(Jpsi_Gen.thePt);
			h1D_NoCut_Gen_pt_bin2_BW->Fill(Jpsi_Gen.thePt);
			h1D_Gen_M->Fill(Jpsi_Gen.theMass);

			// --- cut02 : GEN for denominator
			bool yn_gen = false;
			if ( massCut1(Jpsi_Gen.theMass)
				&& kineCut(isBoosted, Jpsi_Gen.mupl_pt, Jpsi_Gen.mupl_eta, Jpsi_Gen.mupl_p) 
				&& kineCut(isBoosted, Jpsi_Gen.mumi_pt, Jpsi_Gen.mumi_eta, Jpsi_Gen.mumi_p) 
				&& ptbinmin<=Jpsi_Gen.thePt && Jpsi_Gen.thePt <ptbinmax 
				&& rapbinmin<=Jpsi_Gen.theRapidity && Jpsi_Gen.theRapidity <rapbinmax) {
					yn_gen = true;
			}

			if (yn_gen == true){

				h1D_Den_M->Fill(Jpsi_Gen.theMass);
				h2D_Den_pt_y->Fill(Jpsi_Gen.theRapidity,Jpsi_Gen.thePt);
				h2D_Den_pt_y_bin1->Fill(Jpsi_Gen.theRapidity,Jpsi_Gen.thePt);
				h2D_Den_pt_y_bin2->Fill(Jpsi_Gen.theRapidity,Jpsi_Gen.thePt);

				h1D_Den_y->Fill(Jpsi_Gen.theRapidity);
				h1D_Den_pt->Fill(Jpsi_Gen.thePt);
				// cut for 1D hist with binning
				if (6.5<=Jpsi_Gen.thePt)	{
					h1D_Den_y_bin1->Fill(Jpsi_Gen.theRapidity);
				}
				if (-2.4<=Jpsi_Gen.theRapidity && Jpsi_Gen.theRapidity<-0.47) {
					h1D_Den_pt_bin2_FW->Fill(Jpsi_Gen.thePt);
				}
				if (-0.47<=Jpsi_Gen.theRapidity && Jpsi_Gen.theRapidity<1.47) {
					h1D_Den_pt_bin2_BW->Fill(Jpsi_Gen.thePt);
				}
			} // end of yn_gen
		} //end of Gen_QQ_size loop

	} //end of event loop

	// (Num/Den) to get efficiency (B : binomial error)
	h2D_Eff_pt_y->Divide(h2D_Num_pt_y,h2D_Den_pt_y,1,1,"B");
	h2D_Eff_pt_y_bin1->Divide(h2D_Num_pt_y_bin1,h2D_Den_pt_y_bin1,1,1,"B");
	h2D_Eff_pt_y_bin2->Divide(h2D_Num_pt_y_bin2,h2D_Den_pt_y_bin2,1,1,"B");

	h1D_Eff_y->Divide(h1D_Num_y,h1D_Den_y,1,1,"B");
	h1D_Eff_pt->Divide(h1D_Num_pt,h1D_Den_pt,1,1,"B");
	h1D_Eff_y_bin1->Divide(h1D_Num_y_bin1,h1D_Den_y_bin1,1,1,"B");
	h1D_Eff_pt_bin2_FW->Divide(h1D_Num_pt_bin2_FW,h1D_Den_pt_bin2_FW,1,1,"B");
	h1D_Eff_pt_bin2_BW->Divide(h1D_Num_pt_bin2_BW,h1D_Den_pt_bin2_BW,1,1,"B");

	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	// Save the data!

	// ---save01 : as a pdf file <- Removed


	// --- save02 : save the efficiency value as a ASCII
	// binning 1 y dependence
//	streamsize prec = cout.precision(); // for setprecision (like %.3f in C)
	std::ofstream outFile_yDep(Form("Eff_yDep_%s.out",datestring),std::ios::app);
	Double_t eff_yDep=0;
	Double_t effErr_yDep=0;
//	Int_t effBin_yDep = h1D_Eff_y_bin1->GetNbinsX();
	cout << "*** Get Efficiency value (yDep) ***" << endl;
//	cout << "nYBins1 = " << nYBins1 << ", effBin_yDep = "<< effBin_yDep <<" should be same!"<< endl;
	for (Int_t i=0; i< nYBins1; i++) {
		cout << "from y=" << yBinsArr1[i] << ", to y="<< yBinsArr1[i+1] <<endl;
//		cout << "from pt=" << ptBinsArr1[0] <<", to pt="<< ptBinsArr1[1]<<endl;
		eff_yDep = h1D_Eff_y_bin1->GetBinContent(i+1);
		effErr_yDep = h1D_Eff_y_bin1->GetBinError(i+1);
		cout << std::fixed; //// fix flating point notation for setprecision (like %.3f in C)
		cout << "eff= " << setprecision(3) <<eff_yDep << ", effErr = "<< setprecision(3)<<effErr_yDep<<endl;
		outFile_yDep << setprecision(3) <<  eff_yDep << "\t" << setprecision(3) << effErr_yDep << endl;
	}
	outFile_yDep.close();

	// binning 2 pt dependence
//	streamsize prec = cout.precision(); // for setprecision (like %.3f in C)
	std::ofstream outFile_ptDep(Form("Eff_ptDep_%s.out",datestring),std::ios::app);
	Double_t eff_ptDep=0;
	Double_t effErr_ptDep=0;
	cout << "*** Get Efficiency value (ptDep) ***" << endl;
	// FW
	for (Int_t i=0; i< nPtBins2; i++) {
		cout << "from pt=" << ptBinsArr2[i] <<", to pt="<< ptBinsArr2[i+1]<<endl;
		cout << "from y=" << yBinsArr2[0] << ", to y="<< yBinsArr2[1] <<endl;
		eff_ptDep = h1D_Eff_pt_bin2_FW->GetBinContent(i+1);
		effErr_ptDep = h1D_Eff_pt_bin2_FW->GetBinError(i+1);
		cout << std::fixed; //// fix flating point notation for setprecision (like %.3f in C)
		cout << "eff= " << setprecision(3) <<eff_ptDep << ", effErr = "<< setprecision(3)<<effErr_ptDep<<endl;
		outFile_ptDep << setprecision(3) <<  eff_ptDep << "\t" << setprecision(3) << effErr_ptDep << endl;
	}
	// BW
	for (Int_t i=0; i< nPtBins2; i++) {
		cout << "from pt=" << ptBinsArr2[i] <<", to pt="<< ptBinsArr2[i+1]<<endl;
		cout << "from y=" << yBinsArr2[1] << ", to y="<< yBinsArr2[2] <<endl;
		eff_ptDep = h1D_Eff_pt_bin2_BW->GetBinContent(i+1);
		effErr_ptDep = h1D_Eff_pt_bin2_BW->GetBinError(i+1);
		cout << std::fixed; //// fix flating point notation for setprecision (like %.3f in C)
		cout << "eff= " << setprecision(3) <<eff_ptDep << ", effErr = "<< setprecision(3)<<effErr_ptDep<<endl;
		outFile_ptDep << setprecision(3) << eff_ptDep << "\t" << setprecision(3) << effErr_ptDep << endl;
	}
	outFile_ptDep.close();

	// --- save03 : save as a root file

	TFile *outFile = new TFile(Form("EffAna_%s.root",datestring),"RECREATE");
	std::cout << "datestring: " << datestring << std::endl;
	outFile->cd();

	h2D_NoCut_Reco_pt_y->Write();
	h2D_NoCut_Gen_pt_y->Write();
	h2D_Den_pt_y->Write();
	h2D_Num_pt_y->Write();
	h2D_Eff_pt_y->Write();
	h2D_NoCut_Reco_pt_y_bin1->Write();
	h2D_NoCut_Gen_pt_y_bin1->Write();
	h2D_Den_pt_y_bin1->Write();
	h2D_Num_pt_y_bin1->Write();
	h2D_Eff_pt_y_bin1->Write();
	h2D_NoCut_Reco_pt_y_bin2->Write();
	h2D_NoCut_Gen_pt_y_bin2->Write();
	h2D_Den_pt_y_bin2->Write();
	h2D_Num_pt_y_bin2->Write();
	h2D_Eff_pt_y_bin2->Write();

	h1D_NoCut_Reco_y->Write();
	h1D_NoCut_Gen_y->Write();
	h1D_NoCut_Reco_pt->Write();
	h1D_NoCut_Gen_pt->Write();
	h1D_Den_y->Write();
	h1D_Den_pt->Write();
	h1D_Num_y->Write();
	h1D_Num_pt->Write();
	h1D_Eff_y->Write();
	h1D_Eff_pt->Write();

	h1D_NoCut_Reco_y_bin1->Write();
	h1D_NoCut_Gen_y_bin1->Write();
	h1D_Den_y_bin1->Write();
	h1D_Num_y_bin1->Write();
	h1D_Eff_y_bin1->Write();

	h1D_NoCut_Reco_pt_bin2_FW->Write();
	h1D_NoCut_Gen_pt_bin2_FW->Write();
	h1D_Den_pt_bin2_FW->Write();
	h1D_Num_pt_bin2_FW->Write();
	h1D_Eff_pt_bin2_FW->Write();

	h1D_NoCut_Reco_pt_bin2_BW->Write();
	h1D_NoCut_Gen_pt_bin2_BW->Write();
	h1D_Den_pt_bin2_BW->Write();
	h1D_Num_pt_bin2_BW->Write();
	h1D_Eff_pt_bin2_BW->Write();

	h1D_Reco_M->Write();
	h1D_Num_M->Write();
	h1D_Gen_M->Write();
	h1D_Den_M->Write();

	outFile->Close();

} // end of main func

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// sub-routines function 

bool kineCut(bool isBoosted, double muPt, double muEta, double muP) {

	if(muEta<-2.4 || muEta>=1.47)
	{return false;}
	else if(TMath::Abs(muEta)>=2.2 && TMath::Abs(muEta)<2.4 && muPt<=0.8)
	{return false;}
	else if(TMath::Abs(muEta)>=1.3 && TMath::Abs(muEta)<2.2 && muP<=2.9)
	{return false;}
	else if(TMath::Abs(muEta)<1.3 && muPt<=3.3)
	{return false;}

	else {return true;}

}

bool massCut1(double lv_dimu_mass) {
	if(lv_dimu_mass < 2.6 || lv_dimu_mass >= 3.5)
	{return false;}
	else {return true;}
}

bool massCut2(double lv_dimu_mass) {
	if(lv_dimu_mass < 2.95 || lv_dimu_mass >= 3.25)
	{return false;}
	else {return true;}
}

