#include <Riostream.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TDirectory.h>
#include <TLegend.h>
#include <TGraph.h>
 
#include <sstream>
#include <string>

using namespace std;
void SetHistStyle(TH1* h, int i) ;
void SetLegendStyle(TLegend* l);

void draw_pT_trigger_ratio()
{
  //Set style
  gROOT->Macro("/afs/cern.ch/user/k/kyolee/private/cms538HI_test/src/01_SimpleHist/styleTH1D.C"); 

  //----- open the root file ------
  // reference file (created from pilot run 202792)
  //TFile *openFile = TFile::Open("root://eoscms//eos/cms/store/caf/user/velicanu/PA2013_merged/PA2013_HiForest_Express_r0_pilot_minbias_v0.root");
  // run root file 
  //TFile *openFile = TFile::Open("root://eoscms//eos/cms/store/caf/user/velicanu/PA2013_merged/PA2013_HiForest_Express_r210498_stablebeams.root");
	//TFile *openFile = TFile::Open("root://eoscms//eos/cms/store/caf/user/velicanu/PA2013_merged/PA2013_HiForest_Express_r210534_stablebeams_72bunch.root");
  //TFile *openFile = TFile::Open("root://eoscms//eos/cms/store/caf/user/velicanu/PA2013_merged/PA2013_HiForest_Express_r210614_autoforest.root"); 
  TFile * openFile = TFile::Open("root://eoscms//eos/cms/store/caf/user/velicanu/PA2013_merged/PA2013_HiForest_Express_r210634_autoforest_v2.root"); 

  //draw histograms
	string histName[] ={"All_Global_muons", "HLT_PAMu3_v1", "HLT_PAMu7_v1", "HLT_PAMu12_v1"};
	string histTitle[] = {"Glb_pt;Global muon p_{T} [GeV/c];Counts", "Glb_pt;Global muon p_{T} [GeV/c];Counts", "Glb_pt;Global muon p_{T} [GeV/c];Counts", "Glb_pt;Global muon p_{T} [GeV/c];Counts"};
	const int nbins = 60;
	const double xmin = 0.;
	const double xmax = 30.;

	const int nHist = sizeof(histName)/sizeof(string);
  cout<< "nHist = " << nHist << endl;

	TH1D *hist1D[nHist];	
	for(Int_t i=0; i<nHist; i++)
	{
		hist1D[i] = new TH1D(histName[i].c_str(),histTitle[i].c_str(),60,0,30);
		hist1D[i]->Sumw2();
	}

	//read the tree
  TTree *tree = new TTree();
	tree->AddFriend("hltanalysis/HltTree",openFile);
	tree->AddFriend("muonTree/HLTMuTree",openFile);

	//get the run number	
  Int_t Run;
  TTree *temptree = (TTree *) openFile -> Get("muonTree/HLTMuTree");
	temptree->SetBranchAddress("Run", &Run);
	temptree->GetEntry(0);


  TCanvas *c1 =new TCanvas();
	c1->cd(); 

  tree->Draw("HLTMuTree.Glb_pt>>All_Global_muons","HLTMuTree.Event==HltTree.Event && HLTMuTree.Glb_nptl>0","e");
	tree->Draw("HLTMuTree.Glb_pt>>HLT_PAMu3_v1","HLTMuTree.Event==HltTree.Event && HLTMuTree.Glb_nptl>0 && HltTree.HLT_PAMu3_v1==1 ","pe same");
	tree->Draw("HLTMuTree.Glb_pt>>HLT_PAMu7_v1","HLTMuTree.Event==HltTree.Event && HLTMuTree.Glb_nptl>0 && HltTree.HLT_PAMu7_v1==1","pe same");
	tree->Draw("HLTMuTree.Glb_pt>>HLT_PAMu12_v1","HLTMuTree.Event==HltTree.Event && HLTMuTree.Glb_nptl>0 && HltTree.HLT_PAMu12_v1==1","pe same");

 	c1->Clear();

	// draw the ratio of triggers
 string histRatioName[] ={"HLT_PA Mu3/Mu7", "HLT_PA Mu3/Mu12", "HLT_PA Mu7/Mu12"};
 const int nHistRatio = sizeof(histRatioName)/sizeof(string);
 cout << "nHistRatio = " << nHistRatio << endl; 
  
	TLegend *leg = new TLegend(0.45,0.65,0.93,0.91);
	SetLegendStyle(leg);

	TH1D* histRatio[nHistRatio];

	for(Int_t i=0; i<nHistRatio; i++)
	{
  	histRatio[i] = new TH1D(histRatioName[i].c_str(),histTitle[i].c_str(),nbins,xmin,xmax);
		SetHistStyle(histRatio[i],i);
		histRatio[i]->Sumw2();
		leg->AddEntry(histRatio[i],histRatioName[i].c_str(),"lp");
	}

  	histRatio[0]->Divide(hist1D[1],hist1D[2]);
		histRatio[0]->Draw("e");
		leg->Draw();
		histRatio[0]->SetTitle(Form("Run%d",Run));
		gPad->SetLogy(1);
		histRatio[0]->SetMinimum(0.4);
 		histRatio[0]->SetMaximum(5000);

  	histRatio[1]->Divide(hist1D[1],hist1D[3]);
		histRatio[1]->Draw("e same");

  	histRatio[2]->Divide(hist1D[2],hist1D[3]);
		histRatio[2]->Draw("e same");

		// draw the reference graph y=1
		Double_t x[531];
		Double_t y[531];
		for(Int_t n=0; n<nbins; n++)
		{
			x[n]=xmin+1.2*n*((xmax-xmin)/nbins);
			//x[n]=xmin+n*((xmax-xmin)/nbins);
			y[n]=1;
		}
		
		TGraph* gr_ref = new TGraph(nbins, x+1, y);
	  gr_ref->SetLineColor(kRed);
		gr_ref->Draw("L");
	
		c1->SaveAs(Form("trig_ratio_run%d.pdf",Run));
		
		return;

}

void SetHistStyle(TH1* h, int i) {
	//  int colorArr[6] = {kBlack, kBlue, kRed, kGreen+2, kOrange, kMagenta+2};
	//  int colorArr[] = {kGray+2, kBlack, kRed, kRed+2, kOrange+1, kOrange+8, kGreen+2, kGreen+4, kAzure+1, kAzure+3, kViolet+5, kViolet+3, kMagenta, kMagenta+2};
//int colorArr[] = { kBlack, kRed+1, kOrange+1, kOrange-8, kGreen+2, kAzure+1, kBlue+2, kViolet+5, kViolet-4, kMagenta, kMagenta+2};
int colorArr[] = { kBlack, kOrange+1, kGreen+1, kBlue+2};
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
	l->SetFillStyle(4100);
//	l->SetFillStyle(4000); //transparent
//	l->SetBorderSize(1);
	l->SetBorderSize(0);
	l->SetMargin(0.11);
	l->SetTextSize(0.05);
}

