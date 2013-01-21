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
  // Run 
	//TFile *openFile = TFile::Open("root://eoscms//eos/cms/store/caf/user/velicanu/PA2013_merged/PA2013_HiForest_Express_r210498_firstlook_stablebeam.root");

  TTree *tree = (TTree *) openFile -> Get("muonTree/HLTMuTree");
  tree -> SetBranchAddress("Run", &Run);
  tree -> SetBranchAddress("Event", &Event);
	tree->GetEntry(0);
  cout<< "Run = " <<Run << endl;
/*
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
*/

  //draw histograms
	string histName[] ={"Glb_pt","Glb_eta","Glb_phi","Glb_dxy","Glb_dz","Glb_nValMuHits", "Glb_nValTrkHits", "Glb_nTrkFound", "Glb_pixLayerWMeas", "Glb_glbChi2_ndof", "Glb_trkChi2_ndof", "Di_vProb", "Sta_pt", "Sta_eta", "Sta_phi", "Sta_dxy", "Sta_dz"};
	string histTitle[] = {"Glb_pt;Global muon p_{T};Counts (normalized by # of entries)", "Glb_eta;Global muon #eta;Counts (normalized by # of entries)", "Glb_phi;Global muon #phi;Counts (normalized by # of entries)", "Glb_dxy;Global muon dxy;Counts (normalized by # of entries)", "Glb_dz;Global muon dz;Counts (normalized by # of entries)", "Glb_nValMuHits;# of valid muon hits;Counts (normalized by # of entries)", "Glb_nValTrkHits;# of valid tracker hits;Counts (normalized by # of entries)", "Glb_nTrkFound;# of tracks found;Counts (normalized by # of entries)", "Glb_pixLayerWMeas;Pixel layer with measurement;Counts (normalized by # of entries)", "Glb_glbChi2_ndof;Global muon chi2/ndof;Counts (normalized by # of entries)", "Glb_trkChi2_ndof;Tracker muon chi2/ndof;Counts (normalized by # of entries)", "Di_vProb;Dimuon's vertex probability;Counts (normalized by # of entries)", "Sta_pt;Standalone muon p_{T};Counts (normalized by # of entries)", "Sta_eta;Standalone muon #eta;Counts (normalized by # of entries)", "Sta_phi;Standalone muon #phi;Counts (normalized by # of entries)", "Sta_dxy;Standalone muon dxy;Counts (normalized by # of entries)", "Sta_dz;Standalone muon dz;Counts (normalized by # of entries)"}; 
	int nbins[] ={50, 50, 50, 50, 50, 55, 31, 31, 6, 50, 50, 50, 50, 50, 50, 50, 50};
	double xmin[] ={0., -2.5, -3.4, -15.0, -80., 0., 0., 0., 0., 0., 0., 0., 0., -2.5,-3.4, -10., -400. };
	double xmax[] ={20., 2.5, 3.4, 15.0, 80., 50., 31., 31., 6., 5., 3., 1., 50., 2.5, 3.4, 10., 400. };

	const int nHist = sizeof(histName)/sizeof(string);
//  cout<< "nHist = " << nHist << endl;

	TH1D *hist1D[nHist];
  Int_t histEntries[nHist];
	Double_t histMax[nHist];
	for (Int_t i=0; i<nHist; i++) {
		hist1D[i] = new TH1D(histName[i].c_str(),histTitle[i].c_str(),nbins[i],xmin[i],xmax[i]);
		hist1D[i]->Sumw2(); //sum of squares of weights
	}

  TCanvas c1;
	c1.cd(); 

  tree->Draw("Glb_pt>>Glb_pt","Glb_nptl>0","e");
	histEntries[0] = hist1D[0]->GetEntries();
  cout << "histEntries = " << histEntries[0] <<endl;
	hist1D[0]->Scale(1./histEntries[0]);
	histMax[0]=hist1D[0]->GetMaximum();
  hist1D[0]->SetMaximum(histMax[0]*10.); 
	gPad->SetLogy(1);
	c1.SaveAs(Form("TH1D_%d_Glb_pt.pdf",Run));
	
  
  tree->Draw("Glb_eta>>Glb_eta","Glb_nptl>0","e");
	histEntries[1] = hist1D[1]->GetEntries();
  cout << "histEntries = " << histEntries[1] <<endl;
	hist1D[1]->Scale(1./histEntries[1]);
	histMax[1]=hist1D[1]->GetMaximum();
  hist1D[1]->SetMaximum(histMax[1]*1.2); 
  gPad->SetLogy(0);
	c1.SaveAs(Form("TH1D_%d_Glb_eta.pdf",Run));

  tree->Draw("Glb_phi>>Glb_phi","Glb_nptl>0","e");
	histEntries[2] = hist1D[2]->GetEntries();
  cout << "histEntries = " << histEntries[2] <<endl;
  hist1D[2]->Scale(1./histEntries[2]);
	histMax[2]=hist1D[2]->GetMaximum();
  hist1D[2]->SetMaximum(histMax[2]*1.2); 
  gPad->SetLogy(0);
	c1.SaveAs(Form("TH1D_%d_Glb_phi.pdf",Run));

  tree->Draw("Glb_dxy>>Glb_dxy","Glb_nptl>0","e");
	histEntries[3] = hist1D[3]->GetEntries();
  cout << "histEntries = " << histEntries[3] <<endl;
	hist1D[3]->Scale(1./histEntries[3]);
	histMax[3]=hist1D[3]->GetMaximum();
  hist1D[3]->SetMaximum(histMax[3]*10.); 
  gPad->SetLogy(1);
	c1.SaveAs(Form("TH1D_%d_Glb_dxy.pdf",Run));

  tree->Draw("Glb_dz>>Glb_dz","Glb_nptl>0","e");
	histEntries[4] = hist1D[4]->GetEntries();
  cout << "histEntries = " << histEntries[4] <<endl;
	hist1D[4]->Scale(1./histEntries[4]);
	histMax[4]=hist1D[4]->GetMaximum();
  hist1D[4]->SetMaximum(histMax[4]*10.); 
  gPad->SetLogy(1);
	c1.SaveAs(Form("TH1D_%d_Glb_dz.pdf",Run));

  tree->Draw("Glb_nValMuHits>>Glb_nValMuHits","Glb_nptl>0","e");
	histEntries[5] = hist1D[5]->GetEntries();
  cout << "histEntries = " << histEntries[5] <<endl;
	hist1D[5]->Scale(1./histEntries[5]);
	histMax[5]=hist1D[5]->GetMaximum();
  hist1D[5]->SetMaximum(histMax[5]*1.2); 
  gPad->SetLogy(0);
	c1.SaveAs(Form("TH1D_%d_Glb_nValMuHits.pdf",Run));

  tree->Draw("Glb_nValTrkHits>>Glb_nValTrkHits","Glb_nptl>0","e");
	histEntries[6] = hist1D[6]->GetEntries();
  cout << "histEntries = " << histEntries[6] <<endl;
	hist1D[6]->Scale(1./histEntries[6]);
	histMax[6]=hist1D[6]->GetMaximum();
  hist1D[6]->SetMaximum(histMax[6]*1.2); 
  gPad->SetLogy(0);
	c1.SaveAs(Form("TH1D_%d_Glb_nValTrkHits.pdf",Run));

  tree->Draw("Glb_nTrkFound>>Glb_nTrkFound","Glb_nptl>0","e");
	histEntries[7] = hist1D[7]->GetEntries();
  cout << "histEntries = " << histEntries[7] <<endl;
	hist1D[7]->Scale(1./histEntries[7]);
	histMax[7]=hist1D[7]->GetMaximum();
  hist1D[7]->SetMaximum(histMax[7]*1.2); 
  gPad->SetLogy(0);
	c1.SaveAs(Form("TH1D_%d_Glb_nTrkFound.pdf",Run));

  tree->Draw("Glb_pixLayerWMeas>>Glb_pixLayerWMeas","Glb_nptl>0","e");
	histEntries[8] = hist1D[8]->GetEntries();
  cout << "histEntries = " << histEntries[8] <<endl;
	hist1D[8]->Scale(1./histEntries[8]);
	histMax[8]=hist1D[8]->GetMaximum();
  hist1D[8]->SetMaximum(histMax[8]*1.2); 
  gPad->SetLogy(0);
	c1.SaveAs(Form("TH1D_%d_Glb_pixLayerWMeas.pdf",Run));

  tree->Draw("Glb_glbChi2_ndof>>Glb_glbChi2_ndof","Glb_nptl>0","e");
	histEntries[9] = hist1D[9]->GetEntries();
  cout << "histEntries = " << histEntries[9] <<endl;
	hist1D[9]->Scale(1./histEntries[9]);
	histMax[9]=hist1D[9]->GetMaximum();
  hist1D[9]->SetMaximum(histMax[9]*1.2); 
  gPad->SetLogy(0);
	c1.SaveAs(Form("TH1D_%d_Glb_glbChi2_ndof.pdf",Run));

  tree->Draw("Glb_trkChi2_ndof>>Glb_trkChi2_ndof","Glb_nptl>0","e");
	histEntries[10] = hist1D[10]->GetEntries();
  cout << "histEntries = " << histEntries[10] <<endl;
	hist1D[10]->Scale(1./histEntries[10]);
	histMax[10]=hist1D[10]->GetMaximum();
  hist1D[10]->SetMaximum(histMax[10]*1.2); 
  gPad->SetLogy(0);
	c1.SaveAs(Form("TH1D_%d_Glb_trkChi2_ndof.pdf",Run));

  tree->Draw("Di_vProb>>Di_vProb","Di_npair>0","e");
	histEntries[11] = hist1D[11]->GetEntries();
  cout << "histEntries = " << histEntries[11] <<endl;
	hist1D[11]->Scale(1./histEntries[11]);
	histMax[11]=hist1D[11]->GetMaximum();
  hist1D[11]->SetMaximum(histMax[11]*10.); 
  gPad->SetLogy(1);
	c1.SaveAs(Form("TH1D_%d_Di_vProb.pdf",Run));

  tree->Draw("Sta_pt>>Sta_pt","Sta_nptl>0","e");
	histEntries[12] = hist1D[12]->GetEntries();
  cout << "histEntries = " << histEntries[12] <<endl;
	hist1D[12]->Scale(1./histEntries[12]);
	histMax[12]=hist1D[12]->GetMaximum();
  hist1D[12]->SetMaximum(histMax[12]*10.); 
	hist1D[12]->GetYaxis()->SetTitle("Counts (normalized by # of entries)");
  gPad->SetLogy(1);
	c1.SaveAs(Form("TH1D_%d_Sta_pt.pdf",Run));

  tree->Draw("Sta_eta>>Sta_eta","Sta_nptl>0","e");
	histEntries[13] = hist1D[13]->GetEntries();
  cout << "histEntries = " << histEntries[13] <<endl;
	hist1D[13]->Scale(1./histEntries[13]);
	histMax[13]=hist1D[13]->GetMaximum();
  hist1D[13]->SetMaximum(histMax[13]*1.2); 
  gPad->SetLogy(0);
	c1.SaveAs(Form("TH1D_%d_Sta_eta.pdf",Run));

  tree->Draw("Sta_phi>>Sta_phi","Sta_nptl>0","e");
	histEntries[14] = hist1D[14]->GetEntries();
  cout << "histEntries = " << histEntries[14] <<endl;
	hist1D[14]->Scale(1./histEntries[14]);
	histMax[14]=hist1D[14]->GetMaximum();
  hist1D[14]->SetMaximum(histMax[14]*1.2); 
  gPad->SetLogy(0);
	c1.SaveAs(Form("TH1D_%d_Sta_phi.pdf",Run));

  tree->Draw("Sta_dxy>>Sta_dxy","Sta_nptl>0","e");
	histEntries[15] = hist1D[15]->GetEntries();
  cout << "histEntries = " << histEntries[15] <<endl;
	hist1D[15]->Scale(1./histEntries[15]);
	histMax[15]=hist1D[15]->GetMaximum();
  hist1D[15]->SetMaximum(histMax[15]*10.); 
  gPad->SetLogy(1);
	c1.SaveAs(Form("TH1D_%d_Sta_dxy.pdf",Run));

  tree->Draw("Sta_dz>>Sta_dz","Sta_nptl>0","e");
	histEntries[16] = hist1D[16]->GetEntries();
  cout << "histEntries = " << histEntries[16] <<endl;
	hist1D[16]->Scale(1./histEntries[16]);
	histMax[16]=hist1D[16]->GetMaximum();
  hist1D[16]->SetMaximum(histMax[16]*10.); 
  gPad->SetLogy(1);
	c1.SaveAs(Form("TH1D_%d_Sta_dz.pdf",Run));

  //save as a root file
	TFile *outFile = new TFile(Form("TH1D_run%d.root",Run),"recreate");
	outFile->cd();
	for (Int_t i=0; i<nHist; i++) {
		hist1D[i]->Write();
	}
	outFile->Close();

 return;

}

