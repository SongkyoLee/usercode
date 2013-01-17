#include <Riostream.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TDirectory.h>
 
#include <sstream>
#include <string>

using namespace std;

void draw_TH1D_all()
{

  //Set style
  gROOT->Macro("/afs/cern.ch/user/k/kyolee/private/cms538HI_test/src/JpsiStyle.C"); 
  //gROOT->Macro("./JpsiStyle.C");

  //Variables
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

  TH1D *h1 = new TH1D("h1", "Global muon's pT", 100, 0., 13.);
  tree -> Project("h1","Glb_pt","");
  h1 -> GetXaxis() -> SetTitle("Glb_pt [GeV/c]");
  h1 -> GetYaxis() -> SetTitle("Counts");
  h1 -> Draw();
  c1->Update();
  c1->SaveAs("TH1D_Glb_pt.pdf");
	delete h1;

  TH1D *h2 = new TH1D("h2", "Global muon's eta", 100, -2.8, 2.8);
  tree -> Project("h2", "Glb_eta","");
  h2 -> GetXaxis() -> SetTitle("Glb_eta");
  h2 -> GetYaxis() -> SetTitle("Counts");
  h2 -> Draw();
  c1->Update();
  c1->SaveAs("TH1D_Glb_eta.pdf");
	delete h2;

  TH1D *h3 = new TH1D("h3", "Global muon's phi", 100, -3.4, 3.4);
  tree -> Project("h3", "Glb_phi","");
  h3 -> GetXaxis() -> SetTitle("Glb_phi [rad]");
  h3 -> GetYaxis() -> SetTitle("Counts");
  h3 -> Draw();
  c1->Update();
  c1->SaveAs("TH1D_Glb_phi.pdf");
	delete h3;

  TH1D *h4 = new TH1D("h4", "Global muon's dxy", 100, -1.5, 1.5);
  tree -> Project("h4", "Glb_dxy","");
  h4 -> GetXaxis() -> SetTitle("Glb_dxy [cm]");
  h4 -> GetYaxis() -> SetTitle("Counts");
  h4 -> Draw();
  c1->Update();
  c1->SaveAs("TH1D_Glb_dxy.pdf");
	delete h4;

  TH1D *h5 = new TH1D("h5", "Global muon's dz", 100, -8., 8.);
  tree -> Project("h5", "Glb_dz","");
  h5 -> GetXaxis() -> SetTitle("Glb_dz [cm]");
  h5 -> GetYaxis() -> SetTitle("Counts");
  h5 -> Draw();
  c1->Update();
  c1->SaveAs("TH1D_Glb_dz.pdf");
	delete h5;

  TH1D *h6 = new TH1D("h6", "number of valid muon hits", 12, 0., 12.);
  tree -> Project("h6", "Glb_nValMuHits","");
  h6 -> GetXaxis() -> SetTitle("Glb_nValMuHits");
  h6 -> GetYaxis() -> SetTitle("Counts");
  h6 -> Draw();
  c1->Update();
  c1->SaveAs("TH1D_Glb_nValMuHits.pdf");
	delete h6;

  TH1D *h7 = new TH1D("h7", "number of valid tracker hits", 31, 0., 31.);
  tree -> Project("h7", "Glb_nValTrkHits","");
  h7 -> GetXaxis() -> SetTitle("Glb_nValTrkHits");
  h7 -> GetYaxis() -> SetTitle("Counts");
  h7 -> Draw();
  c1->Update();
  c1->SaveAs("TH1D_Glb_Glb_nValTrkHits.pdf");
	delete h7;

  TH1D *h8 = new TH1D("h8", "number of tracks found", 31, 0., 31.);
  tree -> Project("h8", "Glb_nTrkFound","");
  h8 -> GetXaxis() -> SetTitle("Glb_nTrkFound");
  h8 -> GetYaxis() -> SetTitle("Counts");
  h8 -> Draw();
  c1->Update();
  c1->SaveAs("TH1D_Glb_nTrkFound.pdf");
	delete h8;

  TH1D *h9 = new TH1D("h9", "pixel layer with measurement", 6, 0., 6.);
  tree -> Project("h9", "Glb_pixLayerWMeas","");
  h9 -> GetXaxis() -> SetTitle("Glb_pixLayerWMeas");
  h9 -> GetYaxis() -> SetTitle("Counts");
  h9 -> Draw();
  c1->Update();
  c1->SaveAs("TH1D_Glb_pixLayerWMeas.pdf");
	delete h9;

  TH1D *h10 = new TH1D("h10", "global muon's chi2/ndof", 100, 0., 6.);
  tree -> Project("h10", "Glb_glbChi2_ndof","");
  h10 -> GetXaxis() -> SetTitle("Glb_glbChi2_ndof");
  h10 -> GetYaxis() -> SetTitle("Counts");
  h10 -> Draw();
  c1->Update();
  c1->SaveAs("TH1D_Glb_glbChi2_ndof.pdf");
	delete h10;

  TH1D *h11 = new TH1D("h11", "tracker muon's chi2/ndof", 50, 0., 3.);
  tree -> Project("h11", "Glb_trkChi2_ndof","");
  h11 -> GetXaxis() -> SetTitle("Glb_trkChi2_ndof");
  h11 -> GetYaxis() -> SetTitle("Counts");
  h11 -> Draw();
  c1->Update();
  c1->SaveAs("TH1D_Glb_trkChi2_ndof.pdf");
	delete h11;

  TH1D *h12 = new TH1D("h12", "dimuon's vertex probability", 100, 0., 1.);
  tree -> Project("h12", "Di_vProb","");
  h12 -> GetXaxis() -> SetTitle("Di_vProb");
  h12 -> GetYaxis() -> SetTitle("Counts");
  h12 -> Draw();
  c1->Update();
  c1->SaveAs("TH1D_Di_vProb.pdf");
	delete h12;

  TH1D *h13 = new TH1D("h13", "standalone muon's pT", 100, 0., 20.);
  tree -> Project("h13", "Sta_pt","");
  h13 -> GetXaxis() -> SetTitle("Sta_pt [GeV/c]");
  h13 -> GetYaxis() -> SetTitle("Counts");
  h13 -> Draw();
  c1->Update();
  c1->SaveAs("TH1D_Sta_pt.pdf");
	delete h13;

  TH1D *h14 = new TH1D("h14", "Standalone muon's eta", 100, -2.8, 2.8);
  tree -> Project("h14", "Sta_eta","");
  h14 -> GetXaxis() -> SetTitle("Sta_eta");
  h14 -> GetYaxis() -> SetTitle("Counts");
  h14 -> Draw();
  c1->Update();
  c1->SaveAs("TH1D_Sta_eta.pdf");
	delete h14;

  TH1D *h15 = new TH1D("h15", "Standalone muon's phi", 100, -3.4, 3.4);
  tree -> Project("h15", "Sta_phi","");
  h15 -> GetXaxis() -> SetTitle("Sta_phi [rad]");
  h15 -> GetYaxis() -> SetTitle("Counts");
  h15 -> Draw();
  c1->Update();
  c1->SaveAs("TH1D_Sta_phi.pdf");
	delete h15;

  TH1D *h16 = new TH1D("h16", "Standalone muon's dxy", 100, -0.1, 0.1);
  tree -> Project("h16", "Sta_dxy","");
  h16 -> GetXaxis() -> SetTitle("Sta_dxy [cm]");
  h16 -> GetYaxis() -> SetTitle("Counts");
  h16 -> Draw();
  c1->Update();
  c1->SaveAs("TH1D_Sta_dxy.pdf");
	delete h16;

  TH1D *h17 = new TH1D("h17", "Standalone muon's dz", 100, -30.0, 30.0);
  tree -> Project("h17", "Sta_dz","");
  h17 -> GetXaxis() -> SetTitle("Sta_dz [cm]");
  h17 -> GetYaxis() -> SetTitle("Counts");
  h17 -> Draw();
  c1->Update();
  c1->SaveAs("TH1D_Sta_dz.pdf");

  delete h17;
	delete c1;
  delete tree;
	openFile->Close();
	delete openFile;
  //exit(0);
  return;
}

