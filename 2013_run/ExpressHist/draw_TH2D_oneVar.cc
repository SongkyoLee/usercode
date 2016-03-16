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

void draw_TH2D_oneVar(char* VarX,char* VarY, Int_t XBins, Double_t Xmin, Double_t Xmax, Int_t YBins, Double_t Ymin, Double_t Ymax)
{
  //
  // tree->Project(); may doesn't work well
  // please use draw_TH2D_oneRun.cc
  //

  //Set style
  gROOT->Macro("/afs/cern.ch/user/k/kyolee/private/cms538HI_test/src/JpsiStyle.C"); 
  //gROOT->Macro("./JpsiStyle.C");

  //variables
  Float_t Glb_pt, Glb_eta, Glb_phi, Glb_dxy, Glb_dz, ;
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

 //draw the histogram
  TCanvas *c1 = new TCanvas("c1", "canvas", 800, 600);
  c1 -> cd();
  TH2D *hist = new TH2D("hist", "", XBins, Xmin, Xmax, YBins, Ymin, Ymax);
 
  tree -> Project("hist", Form("%s:%s",VarY, VarX),"");

  hist -> GetXaxis() -> SetTitle(Form("%s",VarX));
  hist -> GetYaxis() -> SetTitle(Form("%s",VarY));
  hist -> Draw("colz");

  c1->Update();
  c1->SaveAs(Form("T2_%s_vs_%s.pdf",VarY, VarX));

  //delete hist;
	//delete c1;
  //delete tree;
  //openFile->Close();
  //delete openFile;
	//exit(0);
  return;

}

