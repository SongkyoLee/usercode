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

	//----- open the root file ----- 

	// -- PilotRun (as a reference)
	//TFile *openFile = new TFile("/afs/cern.ch/work/k/kyolee/private/HiForestRootFiles/pPb_hiForest2_1_15_test.root");
	//TFile *openFile = TFile::Open("root://eoscms//eos/cms/store/caf/user/velicanu/PA2013_merged/PA2013_HiForest_Express_r0_pilot_minbias_v0.root");
	// -- MC run1?
 	//TFile* openFile = TFile::Open("root://eoscms//eos/cms/store/group/phys_heavyions/azsigmon/HiForest_pPb_Epos_336800.root");
	// -- Run210353 (date 180113) 
	//TFile *openFile = TFile::Open("root://eoscms//eos/cms/store/group/phys_heavyions/velicanu/forest/PA2013_HiForest_Express_r210658_autoforest_v51.root");
	TFile* openFile = TFile::Open("root://eoscms//eos/cms/store/group/phys_heavyions/velicanu/forest/PA2013_HiForest_Express_r210676_autoforest_v51.root");

	TTree *tree = (TTree *) openFile -> Get("muonTree/HLTMuTree");
	tree -> SetBranchAddress("Run",&Run);
	tree -> SetBranchAddress("Event",&Event);
	tree->GetEntry(0);
	cout<< "Run = " <<Run << endl;

	// Draw histograms
	TCanvas *c1 = new TCanvas("c1", "canvas", 600, 600);
	//TCanvas *c1 = new TCanvas("c1", "canvas", 800, 600);
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
	tree->Draw("Glb_nValMuHits:Glb_pt>>h1","Glb_nptl>0","colz"); //Glb_nptl>0
	c1->SaveAs("TH2D_nValMuHits_vs_Glb_pt.pdf");
	c1->Clear();
	tree->Draw("Glb_nValMuHits:Glb_eta>>h2","Glb_nptl>0","colz");
	c1->SaveAs("TH2D_nValMuHits_vs_Glb_eta.pdf");
	c1->Clear();
	tree->Draw("Glb_nValMuHits:Glb_phi>>h3","Glb_nptl>0","colz");
	c1->SaveAs("TH2D_nValMuHits_vs_Glb_phi.pdf");
	c1->Clear();
	tree->Draw("Glb_nValTrkHits:Glb_pt>>h4","Glb_nptl>0","colz");
	c1->SaveAs("TH2D_nValTrkHits_vs_Glb_pt.pdf");
	c1->Clear();
	tree->Draw("Glb_nValTrkHits:Glb_eta>>h5","Glb_nptl>0","colz");
	c1->SaveAs("TH2D_nValTrkHits_vs_Glb_eta.pdf");
	c1->Clear();
	tree->Draw("Glb_nValTrkHits:Glb_phi>>h6","Glb_nptl>0","colz");
	c1->SaveAs("TH2D_nValTrkHits_vs_Glb_phi.pdf");
	c1->Clear();
	tree->Draw("Glb_pixLayerWMeas:Glb_pt>>h7","Glb_nptl>0","colz");
	c1->SaveAs("TH2D_pixLayerWMeas_vs_Glb_pt.pdf");
	c1->Clear();
	tree->Draw("Glb_pixLayerWMeas:Glb_eta>>h8","Glb_nptl>0","colz");
	c1->SaveAs("TH2D_pixLayerWMeas_vs_Glb_eta.pdf");
	c1->Clear();
	tree->Draw("Glb_pixLayerWMeas:Glb_phi>>h9","Glb_nptl>0","colz");
	c1->SaveAs("TH2D_pixLayerWMeas_vs_Glb_phi.pdf");
	c1->Clear();
	tree->Draw("Glb_pt:Glb_eta>>h10","Glb_nptl>0","colz");
	c1->SaveAs("TH2D_Glb_pt_vs_Glb_eta.pdf");
	c1->Clear();
	tree->Draw("Glb_phi:Glb_eta>>h11","Glb_nptl>0","colz");
	c1->SaveAs("TH2D_Glb_phi_vs_Glb_eta.pdf");
	c1->Clear();
	tree->Draw("Sta_pt:Sta_eta>>h12","Sta_nptl>0","colz"); //Sta_nptl>0
	c1->SaveAs("TH2D_Sta_pt_vs_Sta_eta.pdf");
	c1->Clear();
	tree->Draw("Sta_phi:Sta_eta>>h13","Sta_nptl>0","colz");
	c1->SaveAs("TH2D_Sta_phi_vs_Sta_eta.pdf");

	//save as a root file
	TFile *outFile = new TFile(Form("TH2D_run%d.root",Run),"recreate");
	outFile->cd();
	for (Int_t i=0; i<13; i++) {
		h1->Write();
		h2->Write();
		h3->Write();
		h4->Write();
		h5->Write();
		h6->Write();
		h7->Write();
		h8->Write();
		h9->Write();
		h10->Write();
		h11->Write();
		h12->Write();
		h13->Write();
	}
	outFile->Close();

	//delete c1;
	//delete tree;
	//openFile->Close();
	//delete openFile;
	//exit(0);
	return;

}


