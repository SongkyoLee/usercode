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
#include <TMath.h>
 
#include <sstream>
#include <string>

using namespace std;
void SetHistStyle(TH1* h, int i) ;
void SetLegendStyle(TLegend* l);

void draw_pT_trigger_ratio_cut()
{
	//Set style
	gROOT->Macro("/afs/cern.ch/user/k/kyolee/private/cms538HI_test/src/01_ExpressHist/styleTH1D.C"); 

	//----- open the root file ------
	TFile *openFile = TFile::Open("root://eoscms//eos/cms/store/group/phys_heavyions/velicanu/forest/PA2013_HiForest_Express_r210986_autoforest_v63.root");

	//Draw histograms
	string histName[] ={
		"All_Global_muons", 
		"HLT_PAMu3_v1", 
		"HLT_PAMu7_v1", 
		"HLT_PAMu12_v1", 
		"num_HLT_PAMu7_v1"
	};
	string histTitle = "Glb_pt;Global muon p_{T} [GeV/c];Counts";
	//const Int_t nBins = 60;
	//const Double_t xMin = 0.;
	//const Double_t xMax = 30.;
	Double_t binSet[] = {0,2,4,6,8,10,12,14,20,30};
	//Double_t binSet[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,18,22,30,50};
	const int nBins = (sizeof(binSet)/sizeof(string))-1;
	cout << "nBins = " << nBins << endl;

	const int nHist = sizeof(histName)/sizeof(string);
//	cout<< "nHist = " << nHist << endl;

	TH1D *hist1D[nHist];	
	for(Int_t i=0; i<nHist; i++) {
//		hist1D[i] = new TH1D(histName[i].c_str(),histTitle.c_str(),nBins,xMin,xMax);
		hist1D[i] = new TH1D(histName[i].c_str(),histTitle.c_str(),nBins,binSet);
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

	tree->Draw("HLTMuTree.Glb_pt>>All_Global_muons","HLTMuTree.Event==HltTree.Event && HLTMuTree.Glb_nptl>0 && HLTMuTree.Glb_nTrkFound>10 && HLTMuTree.Glb_glbChi2_ndof<20. && HLTMuTree.Glb_trkChi2_ndof<4. && HLTMuTree.Glb_pixLayerWMeas>0 && TMath::Abs(HLTMuTree.Glb_trkDxy)<3. && TMath::Abs(HLTMuTree.Glb_trkDz)<15.","e");
	tree->Draw("HLTMuTree.Glb_pt>>HLT_PAMu3_v1","HLTMuTree.Event==HltTree.Event && HLTMuTree.Glb_nptl>0 && HLTMuTree.Glb_nTrkFound>10 && HLTMuTree.Glb_glbChi2_ndof<20. && HLTMuTree.Glb_trkChi2_ndof<4. && HLTMuTree.Glb_pixLayerWMeas>0 && TMath::Abs(HLTMuTree.Glb_trkDxy)<3. && TMath::Abs(HLTMuTree.Glb_trkDz)<15. && HltTree.HLT_PAMu3_v1==1 ","pe same");
	tree->Draw("HLTMuTree.Glb_pt>>HLT_PAMu7_v1","HLTMuTree.Event==HltTree.Event && HLTMuTree.Glb_nptl>0 && HLTMuTree.Glb_nTrkFound>10 && HLTMuTree.Glb_glbChi2_ndof<20. && HLTMuTree.Glb_trkChi2_ndof<4. && HLTMuTree.Glb_pixLayerWMeas>0 && TMath::Abs(HLTMuTree.Glb_trkDxy)<3. && TMath::Abs(HLTMuTree.Glb_trkDz)<15. && HltTree.HLT_PAMu7_v1==1","pe same");
	tree->Draw("HLTMuTree.Glb_pt>>HLT_PAMu12_v1","HLTMuTree.Event==HltTree.Event && HLTMuTree.Glb_nptl>0 && HLTMuTree.Glb_nTrkFound>10 && HLTMuTree.Glb_glbChi2_ndof<20. && HLTMuTree.Glb_trkChi2_ndof<4. && HLTMuTree.Glb_pixLayerWMeas>0 && TMath::Abs(HLTMuTree.Glb_trkDxy)<3. && TMath::Abs(HLTMuTree.Glb_trkDz)<15. && HltTree.HLT_PAMu12_v1==1","pe same");
	//Mu7 as a numerator
	tree->Draw("HLTMuTree.Glb_pt>>num_HLT_PAMu7_v1","HLTMuTree.Event==HltTree.Event && HLTMuTree.Glb_nptl>0 && HLTMuTree.Glb_nTrkFound>10 && HLTMuTree.Glb_glbChi2_ndof<20. && HLTMuTree.Glb_trkChi2_ndof<4. && HLTMuTree.Glb_pixLayerWMeas>0 && TMath::Abs(HLTMuTree.Glb_trkDxy)<3. && TMath::Abs(HLTMuTree.Glb_trkDz)<15. && HltTree.HLT_PAMu7_v1==1","pe same");

	// Set the error as zero for denominators
	for(Int_t i=0; i<nBins; i++) {
		hist1D[2] ->SetBinError(i+1,0.);
		hist1D[3] ->SetBinError(i+1,0.);
	}

	c1->Clear();

	// draw the ratio of triggers
	string histRatioName[] = {"HLT_PA Mu3/Mu7", "HLT_PA Mu3/Mu12", "HLT_PA Mu7/Mu12"};
	const int nHistRatio = sizeof(histRatioName)/sizeof(string);
	cout << "nHistRatio = " << nHistRatio << endl; 
  
	TLegend *leg = new TLegend(0.45,0.70,0.93,0.91);
	SetLegendStyle(leg);

	TH1D* histRatio[nHistRatio];

	for(Int_t i=0; i<nHistRatio; i++) {
//		histRatio[i] = new TH1D(histRatioName[i].c_str(),histTitle.c_str(),nBins,xMin,xMax);
		histRatio[i] = new TH1D(histRatioName[i].c_str(),histTitle.c_str(),nBins,binSet);
		SetHistStyle(histRatio[i],i);
		histRatio[i]->Sumw2();
		leg->AddEntry(histRatio[i],histRatioName[i].c_str(),"lp");
	}

	//--- Mu3/Mu7
	histRatio[0]->Divide(hist1D[1],hist1D[2]);
//	for(Int_t i=0; i<nBins; i++) {
//		cout << i <<"th bin" <<endl; 
//		cout << "3: mu3 Contents " << hist1D[1]->GetBinContent(i+1) << endl;
//		cout << "3: mu7 Contents " << hist1D[2]->GetBinContent(i+1) << endl;
//		cout << "3: mu3/mu7 Contents " << histRatio[0]->GetBinContent(i+1) << endl;
//		cout << "3: mu3 error = " << hist1D[1]->GetBinError(i+1) << endl;
//		cout << "3: mu7 error = " << hist1D[2]->GetBinError(i+1) << endl;
//		cout << "hist_3_7 error = " << histRatio[0]->GetBinError(i+1) << endl;
//	}
	histRatio[0]->Draw("e");
	leg->Draw();
	histRatio[0]->SetTitle(Form("Run%d",Run));
	gPad->SetLogy(0); //linear scale
	//gPad->SetLogy(1);
	histRatio[0]->SetMinimum(0.4);
	histRatio[0]->SetMaximum(2.0);
	//histRatio[0]->SetMaximum(5000);

	//--- Mu3/Mu12
	histRatio[1]->Divide(hist1D[1],hist1D[3]);
	histRatio[1]->Draw("e same");
//	for(Int_t i=0; i<nBins; i++) {
//		cout << i <<"th bin" <<endl; 
//		cout << "3: mu3 Contents " << hist1D[1]->GetBinContent(i+1) << endl;
//		cout << "3: mu12 Contents " << hist1D[3]->GetBinContent(i+1) << endl;
//		cout << "3: mu3/mu12 Contents " << histRatio[1]->GetBinContent(i+1) << endl;
//		cout << "3: mu3 error = " << hist1D[1]->GetBinError(i+1) << endl;
//		cout << "3: mu12 error = " << hist1D[3]->GetBinError(i+1) << endl;
//		cout << "hist_3_12 error = " << histRatio[1]->GetBinError(i+1) << endl;
//	}

	//--- Mu7/Mu12
	histRatio[2]->Divide(hist1D[4],hist1D[3]);
	histRatio[2]->Draw("e same");
//	for(Int_t i=0; i<nBins; i++) {
//		cout << i <<"th bin" <<endl; 
//		cout << "3: mu7 Contents " << hist1D[4]->GetBinContent(i+1) << endl;
//		cout << "3: mu12 Contents " << hist1D[3]->GetBinContent(i+1) << endl;
//		cout << "3: mu7/mu12 Contents " << histRatio[2]->GetBinContent(i+1) << endl;
//		cout << "3: mu7 error = " << hist1D[4]->GetBinError(i+1) << endl;
//		cout << "3: mu12 error = " << hist1D[3]->GetBinError(i+1) << endl;
//		cout << "hist_7_12 error = " << histRatio[2]->GetBinError(i+1) << endl;
//	}

	// draw the reference graph y=1
	Double_t x[531];
	Double_t y[531];
	for(Int_t n=0; n<nBins; n++) {
		x[n]=binSet[0]+1.2*n*((binSet[nBins]-binSet[0])/nBins);
		//x[n]=xMin+1.2*n*((xMax-xMin)/nBins);
		//x[n]=xMin+n*((xMax-xMin)/nBins);
		y[n]=1;
	}
		
	TGraph* gr_ref = new TGraph(nBins, x+1, y);
	gr_ref->SetLineColor(kRed);
	gr_ref->Draw("L");
	
	c1->SaveAs(Form("trig_ratio_cut_run%d.pdf",Run));
		
	//save as a root file
	TFile *outFile = new TFile(Form("trig_ratio_cut_run%d.root",Run),"recreate");
	outFile->cd();
	for (Int_t i=0; i<nHistRatio; i++) {
		histRatio[i]->Write();
	}
	outFile->Close();

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
	//h->SetMarkerStyle(kFullCircle);
	h->SetMarkerStyle(markerFullArr[i]);
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
	l->SetMargin(0.11);
	l->SetTextSize(0.05);
}

