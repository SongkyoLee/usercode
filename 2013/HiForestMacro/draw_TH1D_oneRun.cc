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

void draw_TH1D_oneRun()
{
  //Set style
  gROOT->Macro("/afs/cern.ch/user/k/kyolee/private/cms538HI_test/src/01_SimpleHist/styleTH1D.C"); 

  //Variables
  Int_t Run, Event;

  //----- open the root file 

  // PilotRun (as a reference)
  TFile *openFile = TFile::Open("root://eoscms//eos/cms/store/caf/user/velicanu/PA2013_merged/PA2013_HiForest_Express_r0_pilot_minbias_v0.root");
	// Run210353 (date 180113) 
	//TFile *openFile = TFile::Open("root://eoscms//eos/cms/store/caf/user/velicanu/PA2013_merged/pPb_hiForest2_r210353_notracker_v1.root");

  TTree *tree = (TTree *) openFile -> Get("muonTree/HLTMuTree");
  tree -> SetBranchAddress("Run", &Run);
  tree -> SetBranchAddress("Event", &Event);

  // Count HLTMuTree entries 
  Int_t NumTreeEntries = tree -> GetEntries();
	cout << "Tree Entries = " << NumTreeEntries << endl;

  // Count "Event" brach entries
	Int_t NumEventEntries=0;
	for(Int_t i=0; i<NumTreeEntries; i++)
	{
		tree->GetEntry(i);
		if(Event!=0) { NumEventEntries++; }
	}
	cout << "\"Event\" Entries = " << NumEventEntries << endl;

  //draw histograms
	string histName[] ={"Glb_pt","Glb_eta","Glb_phi","Glb_dxy","Glb_dz","Glb_nValMuHits", "Glb_nValTrkHits", "Glb_nTrkFound", "Glb_pixLayerWMeas", "Glb_glbChi2_ndof", "Glb_trkChi2_ndof", "Di_vProb", "Sta_pt", "Sta_eta", "Sta_phi", "Sta_dxy", "Sta_dz"};
	string histTitle[] = {"Glb_pt;Global muon p_{T};Counts", "Glb_eta;Global muon #eta;Counts", "Glb_phi;Global muon #phi;Counts", "Glb_dxy;Global muon dxy;Counts", "Glb_dz;Global muon dz;Counts", "Glb_nValMuHits;# of valid muon hits;Counts", "Glb_nValTrkHits;# of valid tracker hits;Counts", "Glb_nTrkFound;# of tracks found;Counts", "Glb_pixLayerWMeas;Pixel layer with measurement;Counts", "Glb_glbChi2_ndof;Global muon chi2/ndof;Counts", "Glb_trkChi2_ndof;Tracker muon chi2/ndof;Counts", "Di_vProb;Dimuon's vertex probability;Counts", "Sta_pt;Standalone muon p_{T};Counts", "Sta_eta;Standalone muon #eta;Counts", "Sta_phi;Standalone muon #phi;Counts", "Sta_dxy;Standalone muon dxy;Counts", "Sta_dz;Standalone muon dz;Counts"}; 
	int nbins[] ={100, 50, 50, 50, 50, 55, 31, 31, 6, 50, 50, 50, 100, 50, 50, 50, 50};
	double xmin[] ={0., -2.5, -3.4, -15.0, -50., 0., 0., 0., 0., 0., 0., 0., 0., -2.5,-3.4, -10., -90. };
	double xmax[] ={40., 2.5, 3.4, 15.0, 50., 55., 31., 31., 6., 5., 3., 1., 80., 2.5, 3.4, 10., 90. };

	const int nHist = sizeof(histName)/sizeof(string);
  cout<< "nHist = " << nHist << endl;

	TH1D *hist1D[nHist];
	for (Int_t i=0; i<nHist; i++) {
		hist1D[i] = new TH1D(histName[i].c_str(),histTitle[i].c_str(),nbins[i],xmin[i],xmax[i]);
	}

  TCanvas c1;
	c1.cd(); 

  tree->Draw("Glb_pt>>Glb_pt");
  hist1D[0]->Scale(1./NumEventEntries);
  gPad->SetLogy(1);
	c1.SaveAs("TH1D_Glb_pt.pdf");
	c1.Clear();

  tree->Draw("Glb_eta>>Glb_eta");
  hist1D[1]->Scale(1./NumEventEntries);
  gPad->SetLogy(0);
	c1.SaveAs("TH1D_Glb_eta.pdf");
	c1.Clear();

  tree->Draw("Glb_phi>>Glb_phi");
  hist1D[2]->Scale(1./NumEventEntries);
  gPad->SetLogy(0);
	c1.SaveAs("TH1D_Glb_phi.pdf");
	c1.Clear();

  tree->Draw("Glb_dxy>>Glb_dxy");
  hist1D[3]->Scale(1./NumEventEntries);
  gPad->SetLogy(1);
	c1.SaveAs("TH1D_Glb_dxy.pdf");
	c1.Clear();

  tree->Draw("Glb_dz>>Glb_dz");
  hist1D[4]->Scale(1./NumEventEntries);
  gPad->SetLogy(1);
	c1.SaveAs("TH1D_Glb_dz.pdf");
	c1.Clear();

  tree->Draw("Glb_nValMuHits>>Glb_nValMuHits");
  hist1D[5]->Scale(1./NumEventEntries);
  gPad->SetLogy(0);
	c1.SaveAs("TH1D_Glb_nValMuHits.pdf");
	c1.Clear();

  tree->Draw("Glb_nValTrkHits>>Glb_nValTrkHits");
  hist1D[6]->Scale(1./NumEventEntries);
  gPad->SetLogy(0);
	c1.SaveAs("TH1D_Glb_nValTrkHits.pdf");
	c1.Clear();

  tree->Draw("Glb_nTrkFound>>Glb_nTrkFound");
  hist1D[7]->Scale(1./NumEventEntries);
  gPad->SetLogy(0);
	c1.SaveAs("TH1D_Glb_nTrkFound.pdf");
	c1.Clear();

  tree->Draw("Glb_pixLayerWMeas>>Glb_pixLayerWMeas");
  hist1D[8]->Scale(1./NumEventEntries);
  gPad->SetLogy(0);
	c1.SaveAs("TH1D_Glb_pixLayerWMeas.pdf");
	c1.Clear();

  tree->Draw("Glb_glbChi2_ndof>>Glb_glbChi2_ndof");
  hist1D[9]->Scale(1./NumEventEntries);
  gPad->SetLogy(0);
	c1.SaveAs("TH1D_Glb_glbChi2_ndof.pdf");
	c1.Clear();

  tree->Draw("Glb_trkChi2_ndof>>Glb_trkChi2_ndof");
  hist1D[10]->Scale(1./NumEventEntries);
  gPad->SetLogy(0);
	c1.SaveAs("TH1D_Glb_trkChi2_ndof.pdf");
	c1.Clear();

  tree->Draw("Di_vProb>>Di_vProb");
  hist1D[11]->Scale(1./NumEventEntries);
  gPad->SetLogy(1);
	c1.SaveAs("TH1D_Di_vProb.pdf");
	c1.Clear();

  tree->Draw("Sta_pt>>Sta_pt");
  hist1D[12]->Scale(1./NumEventEntries);
  gPad->SetLogy(1);
	c1.SaveAs("TH1D_Sta_pt.pdf");
	c1.Clear();

  tree->Draw("Sta_eta>>Sta_eta");
  hist1D[13]->Scale(1./NumEventEntries);
  gPad->SetLogy(0);
	c1.SaveAs("TH1D_Sta_eta.pdf");
	c1.Clear();

  tree->Draw("Sta_phi>>Sta_phi");
  hist1D[14]->Scale(1./NumEventEntries);
  gPad->SetLogy(0);
	c1.SaveAs("TH1D_Sta_phi.pdf");
	c1.Clear();

  tree->Draw("Sta_dxy>>Sta_dxy");
  hist1D[15]->Scale(1./NumEventEntries);
  gPad->SetLogy(1);
	c1.SaveAs("TH1D_Sta_dxy.pdf");
	c1.Clear();

  tree->Draw("Sta_dz>>Sta_dz");
  hist1D[16]->Scale(1./NumEventEntries);
  gPad->SetLogy(1);
	c1.SaveAs("TH1D_Sta_dz.pdf");

  //save as a root file
	TFile *outFile = new TFile(Form("TH1D_run%d.root",Run),"recreate");
	outFile->cd();
	for (Int_t i=0; i<nHist; i++) {
		hist1D[i]->Write();
	}
	outFile->Close();

 return;
}

