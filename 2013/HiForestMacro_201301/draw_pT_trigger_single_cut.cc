#include <Riostream.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TDirectory.h>
#include <TLegend.h>
 
#include <sstream>
#include <string>

using namespace std;
void SetHistStyle(TH1* h, int i) ;
void SetLegendStyle(TLegend* l);

void draw_pT_trigger_single_cut()
{
	//Set style
	gROOT->Macro("/afs/cern.ch/user/k/kyolee/private/cms538HI_test/src/01_ExpressHist/styleTH1D.C"); 

	//----- open the root file ------
	TFile *openFile = TFile::Open("root://eoscms//eos/cms/store/group/phys_heavyions/velicanu/forest/PA2013_HiForest_Express_r210986_autoforest_v63.root");

	//draw histograms
	string histName[] ={
		"All_Global_muons", 
		"HLT_PAMu3_v1", 
		"HLT_PAMu7_v1", 
		"HLT_PAMu12_v1"
	};
	string histTitle = "Glb_pt;Global muon p_{T} [GeV/c];Counts";
	const Int_t nBins = 60;
	const Double_t xMin = 0.;
	const Double_t xMax = 30.;

	const int nHist = sizeof(histName)/sizeof(string);
	cout<< "nHist = " << nHist << endl;

	TH1D *hist1D[nHist];	
	Double_t histMin[nHist];
	Double_t histMax[nHist];

	for(Int_t i=0; i<nHist; i++) {
		hist1D[i] = new TH1D(histName[i].c_str(),histTitle.c_str(),nBins,xMin,xMax);
		SetHistStyle(hist1D[i],i);
		hist1D[i]->Sumw2();
	}

	Int_t Run;
	TTree *tree = new TTree();
	tree->AddFriend("hltanalysis/HltTree",openFile);
	tree->AddFriend("muonTree/HLTMuTree",openFile);
	
	TTree *temptree = (TTree *) openFile -> Get("muonTree/HLTMuTree");
	temptree->SetBranchAddress("Run", &Run);
	temptree->GetEntry(0);

	//make Legend
	TLegend *leg = new TLegend(0.48,0.59,0.93,0.91);
	SetLegendStyle(leg);
	for (Int_t i=0; i<nHist; i++) {
		leg->AddEntry(hist1D[i],histName[i].c_str(),"lp");
	}

	TCanvas *c1 =new TCanvas();
	c1->cd(); 

	tree->Draw("HLTMuTree.Glb_pt>>All_Global_muons","HLTMuTree.Event==HltTree.Event && HLTMuTree.Glb_nptl>0 && HLTMuTree.Glb_nTrkFound>10 && HLTMuTree.Glb_glbChi2_ndof<20. && HLTMuTree.Glb_trkChi2_ndof<4. && HLTMuTree.Glb_pixLayerWMeas>0 && TMath::Abs(HLTMuTree.Glb_trkDxy)<3. && TMath::Abs(HLTMuTree.Glb_trkDz)<15. ","e");
	leg->Draw();
	hist1D[0]->SetTitle(Form("Run%d",Run));
	gPad->SetLogy(1);
	histMin[0]=hist1D[0]->GetMinimum();
	histMax[0]=hist1D[0]->GetMaximum();
	if (hist1D[0]->GetMinimum() == 0)	{	hist1D[0]->SetMinimum(0.5); }
	else { hist1D[0]->SetMinimum(histMin[0]*0.1);}
	//hist1D[0]->SetMaximum(histMax[0]*1);
	hist1D[0]->SetMaximum(histMax[0]*10);

	tree->Draw("HLTMuTree.Glb_pt>>HLT_PAMu3_v1","HLTMuTree.Event==HltTree.Event && HLTMuTree.Glb_nptl>0 && HLTMuTree.Glb_nTrkFound>10 && HLTMuTree.Glb_glbChi2_ndof<20. && HLTMuTree.Glb_trkChi2_ndof<4. && HLTMuTree.Glb_pixLayerWMeas>0 && TMath::Abs(HLTMuTree.Glb_trkDxy)<3. && TMath::Abs(HLTMuTree.Glb_trkDz)<15. && HltTree.HLT_PAMu3_v1==1 ","pe same");
	tree->Draw("HLTMuTree.Glb_pt>>HLT_PAMu7_v1","HLTMuTree.Event==HltTree.Event && HLTMuTree.Glb_nptl>0 && HLTMuTree.Glb_nTrkFound>10 && HLTMuTree.Glb_glbChi2_ndof<20. && HLTMuTree.Glb_trkChi2_ndof<4. && HLTMuTree.Glb_pixLayerWMeas>0 && TMath::Abs(HLTMuTree.Glb_trkDxy)<3. && TMath::Abs(HLTMuTree.Glb_trkDz)<15. && HltTree.HLT_PAMu7_v1==1","pe same");
	tree->Draw("HLTMuTree.Glb_pt>>HLT_PAMu12_v1","HLTMuTree.Event==HltTree.Event && HLTMuTree.Glb_nptl>0 && HLTMuTree.Glb_nTrkFound>10 && HLTMuTree.Glb_glbChi2_ndof<20. && HLTMuTree.Glb_trkChi2_ndof<4. && HLTMuTree.Glb_pixLayerWMeas>0 && TMath::Abs(HLTMuTree.Glb_trkDxy)<3. && TMath::Abs(HLTMuTree.Glb_trkDz)<15. && HltTree.HLT_PAMu12_v1==1","pe same");

	c1->SaveAs(Form("trig_single_cut_run%d.pdf",Run));

	//save as a root file
	TFile *outFile = new TFile(Form("trig_single_cut_run%d.root",Run),"recreate");
	outFile->cd();
	for (Int_t i=0; i<nHist; i++) {
		hist1D[i]->Write();
	}
	outFile->Close();

	return;

}

void SetHistStyle(TH1* h, int i) {
	//  int colorArr[6] = {kBlack, kBlue, kRed, kGreen+2, kOrange, kMagenta+2};
	//  int colorArr[] = {kGray+2, kBlack, kRed, kRed+2, kOrange+1, kOrange+8, kGreen+2, kGreen+4, kAzure+1, kAzure+3, kViolet+5, kViolet+3, kMagenta, kMagenta+2};
//int colorArr[] = { kBlack, kRed+1, kOrange+1, kOrange-8, kGreen+2, kAzure+1, kBlue+2, kViolet+5, kViolet-4, kMagenta, kMagenta+2};
	int colorArr[] = { kBlack, kRed+1, kOrange+1, kBlue+2};
	int markerFullArr[6] = {kFullCircle, kFullSquare, kFullTriangleUp, kFullTriangleDown, kFullStar, kFullDiamond};
	int markerOpenArr[6] = {kOpenCircle, kOpenSquare, kOpenTriangleUp, kOpenTriangleDown, kOpenStar, kOpenDiamond};
				  
	h->SetLineColor(colorArr[i]);
	//h->SetLineWidth(2.4);
	h->SetMarkerColor(colorArr[i]);
	h->SetMarkerStyle(kFullCircle);
	//  if (i < 10)  h->SetMarkerStyle(markerFullArr[i]);
	//  else h->SetMarkerStyle(markerOpenArr[i-10]);
	h->SetMarkerSize(1.1);

	return;
}

void SetLegendStyle(TLegend* l) {
 	l->SetFillColor(0);
	l->SetFillStyle(4000); //transparent
//	l->SetBorderSize(1);
	l->SetBorderSize(0);
	l->SetMargin(0.12);
	l->SetTextSize(0.05);
}

