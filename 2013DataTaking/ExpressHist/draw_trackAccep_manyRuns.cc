#include <Riostream.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <TDirectory.h>
#include <TChain.h>
#include <TMath.h>
 
#include <sstream>
#include <string>

using namespace std;

void draw_trackAccep_manyRuns()
{
	//Set style
	gROOT->Macro("/afs/cern.ch/user/k/kyolee/private/cms538HI_test/src/01_ExpressHist/styleTH2D.C"); 

	//Variables
//	Int_t Run, Event;

	//----- open the root file ----- 

	// -- PilotRun (as a reference)
	//TFile *openFile = new TFile("/afs/cern.ch/work/k/kyolee/private/HiForestRootFiles/pPb_hiForest2_1_15_test.root");
	//TFile *openFile = TFile::Open("root://eoscms//eos/cms/store/caf/user/velicanu/PA2013_merged/PA2013_HiForest_Express_r0_pilot_minbias_v0.root");
	// -- MC run1?
	// TFile* openFile = TFile::Open("root://eoscms//eos/cms/store/group/phys_heavyions/azsigmon/HiForest_pPb_Epos_336800.root");
	// -- Run210353 (date 180113) 

	TChain *tree = new TChain("ppTrack/trackTree");
	tree->Add("root://eoscms//eos/cms/store/group/phys_heavyions/velicanu/forest/PA2013_HiForest_Express_r210498_autoforest_v51.root");
	tree->Add("root://eoscms//eos/cms/store/group/phys_heavyions/velicanu/forest/PA2013_HiForest_Express_r210534_autoforest_v51.root");
	tree->Add("root://eoscms//eos/cms/store/group/phys_heavyions/velicanu/forest/PA2013_HiForest_Express_r210614_autoforest_v51.root");
	tree->Add("root://eoscms//eos/cms/store/group/phys_heavyions/velicanu/forest/PA2013_HiForest_Express_r210634_autoforest_v51.root");
	tree->Add("root://eoscms//eos/cms/store/group/phys_heavyions/velicanu/forest/PA2013_HiForest_Express_r210635_autoforest_v51.root");
	tree->Add("root://eoscms//eos/cms/store/group/phys_heavyions/velicanu/forest/PA2013_HiForest_Express_r210638_autoforest_v51.root");
	tree->Add("root://eoscms//eos/cms/store/group/phys_heavyions/velicanu/forest/PA2013_HiForest_Express_r210658_autoforest_v51.root");
	tree->Add("root://eoscms//eos/cms/store/group/phys_heavyions/velicanu/forest/PA2013_HiForest_Express_r210676_autoforest_v51.root");

	//tree = (TTree *) openFile -> Get("muonTree/HLTMuTree");
	//	tree -> SetBranchAddress("Run",&Run);
	//	tree -> SetBranchAddress("Event",&Event);
	//	tree -> GetEntry(0);

	//Draw histograms
	//TCanvas *c1 = new TCanvas();
	TCanvas *c1 = new TCanvas("c1", "canvas", 600, 600);
	c1->cd();

	TH2D *h1 = new TH2D("h1", "trkPt vs trkEta;tracks #eta;tracks p_{T} [GeV/c]", 100, -2.4, 2.4, 100, 0, 6.);
	TH2D *h2 = new TH2D("h2", "trkphi vs trkEta;trakcs #eta;tracks #phi [rad]", 100, -2.4, 2.4, 100, -3.14, 3.14);
	
	tree->Draw(
		"trkPt:trkEta>>h1",
		"nTrk>0 && TMath::Abs(trkEta)<2.4 && (TMath::Abs(trkEta)<1.3&&trkPt>=3.3) || (1.3<=TMath::Abs(trkEta)&&TMath::Abs(trkEta)<2.2&& trkPt*(TMath::CosH(trkEta))>=2.9) || (2.2<=TMath::Abs(trkEta)&&trkPt>=0.8)",
		"colz"); // muon acceptance cuts ( remember that|p|=pT*cosh(eta) )
	c1->SaveAs("TH2D_trkPt_vs_trkEta_manyRuns.pdf");
	c1->Clear();	
	tree->Draw("trkPhi:trkEta>>h2",
		"nTrk>0 && TMath::Abs(trkEta)<2.4 && (TMath::Abs(trkEta)<1.3&&trkPt>=3.3) || (1.3<=TMath::Abs(trkEta)&&TMath::Abs(trkEta)<2.2&& trkPt*(TMath::CosH(trkEta))>=2.9) || (2.2<=TMath::Abs(trkEta)&&trkPt>=0.8)",
		"colz");
	c1->SaveAs("TH2D_trkPhi_vs_trkEta_manyRuns.pdf");

	//save as a root file
	TFile *outFile = new TFile("TH2D_manyRuns.root", "recreate");
//	TFile *outFile = new TFile(Form("TH2D_run%d.root",Run),"recreate");
	outFile->cd();
	h1->Write();
	h2->Write();
	outFile->Close();

	//delete c1;
  //delete tree;
  //openFile->Close();
  //delete openFile;
	//exit(0);
	return;

}

