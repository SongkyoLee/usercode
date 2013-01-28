#include <Riostream.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <TDirectory.h>
 
#include <sstream>
#include <string>

using namespace std;

void draw_trackAccep_oneRun()
{
  //Set style
  gROOT->Macro("/afs/cern.ch/user/k/kyolee/private/cms538HI_test/src/01_ExpressHist/styleTH2D.C"); 

  //Variables
  Int_t Run, Event;

 //----- open the root file 

 // -- PilotRun (as a reference)
 //TFile *openFile = TFile::Open("root://eoscms//eos/cms/store/caf/user/velicanu/PA2013_merged/PA2013_HiForest_Express_r0_pilot_minbias_v0.root");
 //  -- MC run1?
 //TFile* openFile = TFile::Open("root://eoscms//eos/cms/store/caf/user/vzhukova/EPOS_RECO/epos_reco_fix_1000_1_Em3.root"); //this is RECO, not HiForest
  TFile* openFile = TFile::Open("root://eoscms//eos/cms/store/group/phys_heavyions/azsigmon/HiForest_pPb_Epos_336800.root");
 // -- Run210353 (date 180113) 
//  TFile* openFile = TFile::Open("root://eoscms//eos/cms/store/group/phys_heavyions/velicanu/forest/PA2013_HiForest_Express_r210676_autoforest_v51.root");

  TTree *tree = (TTree *) openFile -> Get("ppTrack/trackTree");
  tree -> SetBranchAddress("nRun",&Run);
  tree -> SetBranchAddress("nEv",&Event);
	tree->GetEntry(0);
	cout<< "Run = " <<Run << endl;

 //draw histograms
  TCanvas *c1 = new TCanvas("c1", "canvas", 600, 600);
  c1 -> cd();

	TH2D* hist2D[2];
  hist2D[0] = new TH2D("trkPt_trkEta_01", "ppTree : trkPt vs trkEta;tracks #eta;tracks p_{T} [GeV/c]", 100, -2.4, 2.4, 100, 0., 6.);
  hist2D[1] = new TH2D("trkPhi_trkEta_01", "ppTree : trkPhi vs trkEta;tracks #eta;tracks #phi [rad]", 100, -2.4, 2.4, 100, -3.14, 3.14);

	tree->Draw(
		"trkPt:trkEta>>trkPt_trkEta_01",
		"nTrk>0 && TMath::Abs(trkEta)<2.4 && (TMath::Abs(trkEta)<1.3&&trkPt>=3.3) || (1.3<=TMath::Abs(trkEta)&&TMath::Abs(trkEta)<2.2&& trkPt*(TMath::CosH(trkEta))>=2.9) || (2.2<=TMath::Abs(trkEta)&&trkPt>=0.8)",
		"colz");
  c1->SaveAs("TH2D_trkPt_vs_trkEta_MC.pdf");
  c1->Clear();

	tree->Draw("trkPhi:trkEta>>trkPhi_trkEta_01",
	"nTrk>0 && TMath::Abs(trkEta)<2.4 && (TMath::Abs(trkEta)<1.3&&trkPt>=3.3) || (1.3<=TMath::Abs(trkEta)&&TMath::Abs(trkEta)<2.2&& trkPt*(TMath::CosH(trkEta))>=2.9) || (2.2<=TMath::Abs(trkEta)&&trkPt>=0.8)",
	"colz");
  c1->SaveAs("TH2D_trkPhi_vs_trkEta_MC.pdf");

/*
  //save as a root file
	TFile *outFile = new TFile(Form("TH2D_MC_run%d.root",Run),"recreate");
	outFile->cd();
	for (Int_t i=0; i<13; i++) {
		h10->Write();
		h11->Write();
	}
	outFile->Close();
*/

	//delete c1;
  //delete tree;
  //openFile->Close();
  //delete openFile;
	//exit(0);
  return;

}


