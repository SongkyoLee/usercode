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

void draw_TH2D_oneRun()
{
  //Set style
  gROOT->Macro("/afs/cern.ch/user/k/kyolee/private/cms538HI_test/src/01_SimpleHist/styleTH2D.C"); 

  //Variables
  Int_t Run, Event;

 //----- open the root file 

 // PilotRun (as a reference)
 //TFile *openFile = TFile::Open("root://eoscms//eos/cms/store/caf/user/velicanu/PA2013_merged/PA2013_HiForest_Express_r0_pilot_minbias_v0.root");
 // Run210353 (date 180113) 
 //TFile *openFile = TFile::Open("root://eoscms//eos/cms/store/caf/user/velicanu/PA2013_merged/PA2013_HiForest_Express_r210498_stablebeams.root");
 TFile *openFile = TFile::Open("root://eoscms//eos/cms/store/caf/user/velicanu/PA2013_merged/PA2013_HiForest_Express_r210534_stablebeams_72bunch.root");

  TTree *tree = (TTree *) openFile -> Get("muonTree/HLTMuTree");
  tree -> SetBranchAddress("Run",&Run);
  tree -> SetBranchAddress("Event",&Event);
	tree->GetEntry(0);
  cout<< "Run = " <<Run << endl;

 //draw histograms
  //TCanvas *c1 = new TCanvas("c1", "canvas", 800, 600);
  TCanvas *c1 = new TCanvas("c1", "canvas", 600, 600);
  c1 -> cd();
 
  TH2D *h1 = new TH2D("h1", "Glb_nValMuHits vs Glb_pt;Global muon p_{T} [GeV/c];# of valid muon hits", 50, 0., 20., 55, 0., 55.);
  TH2D *h2 = new TH2D("h2", "Glb_nValMuHits vs Glb_eta;Global muon #eta;# of valid muon hits", 50, -2.5, 2.5, 55, 0., 55.);
  TH2D *h3 = new TH2D("h3", "Glb_nValMuHits vs Glb_phi;Global muon #phi [rad];# of valid muon hits", 50, -3.4, 3.4, 55, 0., 55.);
  TH2D *h4 = new TH2D("h4", "Glb_nValTrkHits vs Glb_pt;Global muon p_{T} [GeV/c];# of valid tracker hits", 50, 0., 20., 31, 0., 31);
  TH2D *h5 = new TH2D("h5", "Glb_nValTrkHits vs Glb_eta;Global muon #eta;# of valid tracker hits", 50, -2.5, 2.5, 31, 0., 31.);
  TH2D *h6 = new TH2D("h6", "Glb_nValTrkHits vs Glb_phi;Global muon #phi [rad];# of valid tracker hits", 50, -3.4, 3.4, 31, 0., 31.);
  TH2D *h7 = new TH2D("h7", "Glb_pixLayerWMeas vs Glb_pt;Global muon p_{T} [GeV/c];Pixel layer with measurement", 50, 0., 20., 5, 0., 5.);
  TH2D *h8 = new TH2D("h8", "Glb_pixLayerWMeas vs Glb_eta;Global muon #eta;Pixel layer with measurement", 50, -2.5, 2.5, 5, 0., 5.);
  TH2D *h9 = new TH2D("h9", "Glb_pixLayerWMeas vs Glb_phi;Global muon #phi [rad];Pixel layer with measurement", 50, -3.4, 3.4, 5, 0., 5.);
  TH2D *h10 = new TH2D("h10", "Glb_pt vs Glb_eta;Global muon #eta;Global muon p_{T} [GeV/c]", 50, -2.5, 2.5, 50, 0., 20.);
  TH2D *h11 = new TH2D("h11", "Glb_phi vs Glb_eta;Global muon #eta;Global muon #phi [rad]", 50, -2.5, 2.5, 50, -3.4, 3.4);
  TH2D *h12 = new TH2D("h12", "Sta_pt vs Sta_eta;Standalone muon #eta;Standalone muon p_{T} [GeV/c]", 50, -2.5, 2.5, 50, 0., 50.); 
  TH2D *h13 = new TH2D("h13", "Sta_phi vs Sta_eta;Standalone muon #eta;Standalone muon #phi [rad]", 50, -2.5, 2.5, 50, -3.4, 3.4);
/*
  // count HLTMuTree entries 
  Int_t NumTreeEntries = tree -> GetEntries();
	cout << "Tree Entries = " << NumTreeEntries << endl;
*/
	tree->Draw("Glb_nValMuHits:Glb_pt>>h1","","colz"); //Glb_nptl>0
  c1->SaveAs("TH2D_nValMuHits_vs_Glb_pt.pdf");
  c1->Clear();
	tree->Draw("Glb_nValMuHits:Glb_eta>>h2","","colz");
  c1->SaveAs("TH2D_nValMuHits_vs_Glb_eta.pdf");
  c1->Clear();
	tree->Draw("Glb_nValMuHits:Glb_phi>>h3","","colz");
  c1->SaveAs("TH2D_nValMuHits_vs_Glb_phi.pdf");
  c1->Clear();
	tree->Draw("Glb_nValTrkHits:Glb_pt>>h4","","colz");
  c1->SaveAs("TH2D_nValTrkHits_vs_Glb_pt.pdf");
  c1->Clear();
	tree->Draw("Glb_nValTrkHits:Glb_eta>>h5","","colz");
  c1->SaveAs("TH2D_nValTrkHits_vs_Glb_eta.pdf");
  c1->Clear();
	tree->Draw("Glb_nValTrkHits:Glb_phi>>h6","","colz");
  c1->SaveAs("TH2D_nValTrkHits_vs_Glb_phi.pdf");
  c1->Clear();
	tree->Draw("Glb_pixLayerWMeas:Glb_pt>>h7","","colz");
  c1->SaveAs("TH2D_pixLayerWMeas_vs_Glb_pt.pdf");
  c1->Clear();
	tree->Draw("Glb_pixLayerWMeas:Glb_eta>>h8","","colz");
  c1->SaveAs("TH2D_pixLayerWMeas_vs_Glb_eta.pdf");
  c1->Clear();
	tree->Draw("Glb_pixLayerWMeas:Glb_phi>>h9","","colz");
  c1->SaveAs("TH2D_pixLayerWMeas_vs_Glb_phi.pdf");
  c1->Clear();
	tree->Draw("Glb_pt:Glb_eta>>h10","","colz");
  c1->SaveAs("TH2D_Glb_pt_vs_Glb_eta.pdf");
  c1->Clear();
	tree->Draw("Glb_phi:Glb_eta>>h11","","colz");
  c1->SaveAs("TH2D_Glb_phi_vs_Glb_eta.pdf");
  c1->Clear();
	tree->Draw("Sta_pt:Sta_eta>>h12","","colz"); //Sta_nptl>0
  c1->SaveAs("TH2D_Sta_pt_vs_Sta_eta.pdf");
  c1->Clear();
	tree->Draw("Sta_phi:Sta_eta>>h13","","colz");
  c1->SaveAs("TH2D_Sta_phi_vs_Sta_eta.pdf");

	//delete c1;
  //delete tree;
  //openFile->Close();
  //delete openFile;
	//exit(0);
  return;
}
