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

//void draw_TH2D_all()
void draw_TH2D_all()
{
  //Set style
  gROOT->Macro("/afs/cern.ch/user/k/kyolee/private/cms538HI_test/src/JpsiStyle.C"); 
  //gROOT->Macro("./JpsiStyle.C");

  //variables
  Float_t Glb_pt, Glb_eta, Glb_phi, Glb_dxy, Glb_dz;
  Int_t Glb_nValMuHits, Glb_nValTrkHits, Glb_nTrkFound, Glb_pixLayerWMeas; 
  Float_t Glb_glbChi2_ndof, Glb_trkChi2_ndof;
  Float_t Di_vProb; 
  Float_t Sta_pt, Sta_eta, Sta_phi, Sta_dxy, Sta_dz;

 //open the root file 
 //for eos files, = TFile::Open(root://eoscms//eos/cms/[filename])
  TFile *openFile = TFile::Open("root://eoscms//eos/cms/store/caf/user/velicanu/PA2013_merged_HiForest/pPb_hiForest2_1_15_test.root");
  TTree *tree = (TTree *) openFile -> Get("muonTree/HLTMuTree");

  tree -> SetBranchAddress("Glb_pt", &Glb_pt);
  tree -> SetBranchAddress("Glb_eta", &Glb_eta);
  tree -> SetBranchAddress("Glb_phi", &Glb_phi);
  tree -> SetBranchAddress("Glb_dxy", &Glb_dxy);
  tree -> SetBranchAddress("Glb_dz", &Glb_dz);
  tree -> SetBranchAddress("Glb_nValMuHits", &Glb_nValMuHits);
  tree -> SetBranchAddress("Glb_nValTrkHits", &Glb_nValTrkHits);
  tree -> SetBranchAddress("Glb_nTrkFound", &Glb_nTrkFound);
  tree -> SetBranchAddress("Glb_pixLayerWMeas", &Glb_pixLayerWMeas);
  tree -> SetBranchAddress("Glb_glbChi2_ndof", &Glb_glbChi2_ndof);
  tree -> SetBranchAddress("Glb_trkChi2_ndof", &Glb_trkChi2_ndof);
  tree -> SetBranchAddress("Di_vProb", &Di_vProb);
  tree -> SetBranchAddress("Sta_pt", &Sta_pt);
  tree -> SetBranchAddress("Sta_eta", &Sta_eta);
  tree -> SetBranchAddress("Sta_phi", &Sta_phi);
  tree -> SetBranchAddress("Sta_dxy", &Sta_dxy);
  tree -> SetBranchAddress("Sta_dz", &Sta_dz);

 //draw histograms
  TCanvas *c1 = new TCanvas("c1", "canvas", 800, 600);
  c1 -> cd();
 
  TH2D *h1 = new TH2D("h1", "", 50, -2.5, 2.5, 11, 0., 11.);
  tree -> Project("h1", "Glb_nValMuHits:Glb_eta","");
  h1 -> GetXaxis() -> SetTitle("Glb_eta");
  h1 -> GetYaxis() -> SetTitle("Glb_nValMuHits");
  h1 -> Draw("colz");
  c1->Update();
  c1->SaveAs("TH2D_Glb_nValMuHits_vs_Glb_eta.pdf");
  delete h1;

  TH2D *h2 = new TH2D("h2", "", 50, -3.4, 3.4, 31, 0, 31);
  tree -> Project("h2", "Glb_nValTrkHits:Glb_phi","");
  h2 -> GetXaxis() -> SetTitle("Glb_phi");
  h2 -> GetYaxis() -> SetTitle("Glb_nValTrkHits");
  h2 -> Draw("colz");
  c1->Update();
  c1->SaveAs("TH2D_Glb_nValTrkHits_vs_Glb_phi.pdf");
  delete h2;

  TH2D *h3 = new TH2D("h3", "", 50, 0., 15., 5, 0, 5);
  tree -> Project("h3", "Glb_pixLayerWMeas:Glb_pt","");
  h3 -> GetXaxis() -> SetTitle("Glb_pt");
  h3 -> GetYaxis() -> SetTitle("Glb_pixLayerWMeas");
  h3 -> Draw("colz");
  c1->Update();
  c1->SaveAs("TH2D_Glb_pixLayerWMeas_vs_Glb_pt.pdf");
  delete h3;

  TH2D *h4 = new TH2D("h4", "", 50, -2.5, 2.5, 50, 0, 14);
  tree -> Project("h4", "Glb_pt:Glb_eta","");
  h4 -> GetXaxis() -> SetTitle("Glb_eta");
  h4 -> GetYaxis() -> SetTitle("Glb_pt");
  h4 -> Draw("colz");
  c1->Update();
  c1->SaveAs("TH2D_Glb_pt_vs_Glb_eta.pdf");
  delete h4;

	delete c1;
  delete tree;
  openFile->Close();
  delete openFile;
	//exit(0);
  return;

}

