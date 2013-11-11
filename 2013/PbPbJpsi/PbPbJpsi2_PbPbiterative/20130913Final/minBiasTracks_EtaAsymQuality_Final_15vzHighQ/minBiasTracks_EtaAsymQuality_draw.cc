#include <Riostream.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TGraph.h>
#include <vector>
#include <TSystem.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TDirectory.h>
#include <TLegend.h>
#include <TPaveStats.h>
#include "TStyle.h"
#include "TSystem.h"
 
#include <sstream>
#include <string>

TH1D* divideHistosDiffBins(TH1D* h_Num, TH1D* h_Den);
TH1D* divideHistosSameBins(TH1D* h_Num, TH1D* h_Den);
TGraph* referenceLine(Double_t nBins, Double_t xMin, Double_t xMax);
void SetHistStyle(TH1* h, Int_t c, Int_t m);
void SetLegendStyle(TLegend* l);
void SetTextStyle(TPaveText* t);

void minBiasTracks_EtaAsymQuality_draw()
{
	gROOT->Macro("/afs/cern.ch/work/k/kyolee/private/cms442/src/JpsiStyle.C");

	TFile *refFile = new TFile("minBiasTracks_EtaAsymQuality_Final_15vzHighQ.root","READ");
	TH1D* relPt_FullTrack_plusEta = (TH1D*)refFile->Get("relPt_FullTrack_plusEta");
	TH1D* relDxy_FullTrack_plusEta = (TH1D*)refFile->Get("relDxy_FullTrack_plusEta");
	TH1D* relDz_FullTrack_plusEta = (TH1D*)refFile->Get("relDz_FullTrack_plusEta");
	TH1D* absRelDxy_FullTrack_plusEta = (TH1D*)refFile->Get("absRelDxy_FullTrack_plusEta");
	TH1D* absRelDz_FullTrack_plusEta = (TH1D*)refFile->Get("absRelDz_FullTrack_plusEta");
	TH1D* dxy_FullTrack_plusEta = (TH1D*)refFile->Get("dxy_FullTrack_plusEta");
	TH1D* dz_FullTrack_plusEta = (TH1D*)refFile->Get("dz_FullTrack_plusEta");
	TH1D* dxyErr_FullTrack_plusEta = (TH1D*)refFile->Get("dxyErr_FullTrack_plusEta");
	TH1D* dzErr_FullTrack_plusEta = (TH1D*)refFile->Get("dzErr_FullTrack_plusEta");
	TH1D* absEta_FullTrack_plusEta = (TH1D*)refFile->Get("absEta_FullTrack_plusEta");
	TH1D* phi_FullTrack_plusEta = (TH1D*)refFile->Get("phi_FullTrack_plusEta");

	TH1D* relPt_FullTrack_minusEta = (TH1D*)refFile->Get("relPt_FullTrack_minusEta");
	TH1D* relDxy_FullTrack_minusEta = (TH1D*)refFile->Get("relDxy_FullTrack_minusEta");
	TH1D* relDz_FullTrack_minusEta = (TH1D*)refFile->Get("relDz_FullTrack_minusEta");
	TH1D* absRelDxy_FullTrack_minusEta = (TH1D*)refFile->Get("absRelDxy_FullTrack_minusEta");
	TH1D* absRelDz_FullTrack_minusEta = (TH1D*)refFile->Get("absRelDz_FullTrack_minusEta");
	TH1D* dxy_FullTrack_minusEta = (TH1D*)refFile->Get("dxy_FullTrack_minusEta");
	TH1D* dz_FullTrack_minusEta = (TH1D*)refFile->Get("dz_FullTrack_minusEta");
	TH1D* dxyErr_FullTrack_minusEta = (TH1D*)refFile->Get("dxyErr_FullTrack_minusEta");
	TH1D* dzErr_FullTrack_minusEta = (TH1D*)refFile->Get("dzErr_FullTrack_minusEta");
	TH1D* absEta_FullTrack_minusEta = (TH1D*)refFile->Get("absEta_FullTrack_minusEta");
	TH1D* phi_FullTrack_minusEta = (TH1D*)refFile->Get("phi_FullTrack_minusEta");

	// Draw histograms
	TCanvas* c1 = new TCanvas("c1","canvas",600,600);
	c1->cd();
//	TLegend *legUR = new TLegend(0.55, 0.74, 0.80, 0.90); // upper right
	TLegend *legUR = new TLegend(0.60, 0.76, 0.83, 0.91); // upper right
	TLegend *legBR = new TLegend(0.60, 0.20, 0.83, 0.40); // bottom right
	TLegend *legUL = new TLegend(0.20, 0.74, 0.45, 0.90); // upper left
	TLegend *legBM = new TLegend(0.37, 0.20, 0.62, 0.35); // bottom middle
	SetLegendStyle(legUR);
	SetLegendStyle(legBR);
	SetLegendStyle(legUL);
	SetLegendStyle(legBM);

	//1. overlaying etaPlus and etaMinus
	gPad->SetLogy(1);
	SetHistStyle(relPt_FullTrack_plusEta,1,3);
	SetHistStyle(relPt_FullTrack_minusEta,2,0);
//	relPt_FullTrack_plusEta->Rebin(5);
//	relPt_FullTrack_minusEta->Rebin(5);
	relPt_FullTrack_plusEta->GetXaxis()->SetTitle("#deltap_{T}/p_{T}");
	relPt_FullTrack_plusEta->GetYaxis()->SetTitle("Tracks");
	cout << "relPt plusEta Entry = " << relPt_FullTrack_plusEta->GetEntries() << endl;
	cout << "relPt minusEta Entry = " << relPt_FullTrack_minusEta->GetEntries() << endl;
	relPt_FullTrack_plusEta->Draw("e");	
	relPt_FullTrack_minusEta->Draw("e same");	
	legUR->SetHeader("minBiasTracks");
	legUR -> AddEntry(relPt_FullTrack_plusEta,"0 < #eta_{lab} < 2.4","lp");
	legUR -> AddEntry(relPt_FullTrack_minusEta,"-2.4 < #eta_{lab} < 0","lp");
	legUR->Draw();
	c1->SaveAs("minBiasTracksQualityOverlay_relPt.png");
	c1->Clear();	
	legUR->Clear();

	gPad->SetLogy(1);
	SetHistStyle(relDxy_FullTrack_plusEta,1,3);
	SetHistStyle(relDxy_FullTrack_minusEta,2,0);
	cout << "relDxy plusEta Entry = " << relDxy_FullTrack_plusEta->GetEntries() << endl;
	cout << "relDxy minusEta Entry = " << relDxy_FullTrack_minusEta->GetEntries() << endl;
	relDxy_FullTrack_plusEta->GetXaxis()->SetTitle("dxy/#sigma_{dxy}");
	relDxy_FullTrack_plusEta->GetYaxis()->SetTitle("Tracks");
	relDxy_FullTrack_plusEta->Rebin(2);
	relDxy_FullTrack_minusEta->Rebin(2);
//	relDxy_FullTrack_plusEta->SetMinimum(100000);
//	relDxy_FullTrack_plusEta->SetMaximum(100000000);
	relDxy_FullTrack_plusEta->Draw("e");	
	relDxy_FullTrack_minusEta->Draw("e same");	
	legUR->SetHeader("minBiasTracks");
	legUR -> AddEntry(relDxy_FullTrack_plusEta,"0 < #eta_{lab} < 2.4","lp");
	legUR -> AddEntry(relDxy_FullTrack_minusEta,"-2.4 < #eta_{lab} < 0","lp");
	legUR->Draw();
	c1->SaveAs("minBiasTracksQualityOverlay_relDxy.png");
	c1->Clear();	
	legUR->Clear();

	gPad->SetLogy(1);
	SetHistStyle(relDz_FullTrack_plusEta,1,3);
	SetHistStyle(relDz_FullTrack_minusEta,2,0);
	cout << "relDz plusEta Entry = " << relDz_FullTrack_plusEta->GetEntries() << endl;
	cout << "relDz minusEta Entry = " << relDz_FullTrack_minusEta->GetEntries() << endl;
	relDz_FullTrack_plusEta->GetXaxis()->SetTitle("dz/#sigma_{dz}");
	relDz_FullTrack_plusEta->GetYaxis()->SetTitle("Tracks");
//	relDz_FullTrack_plusEta->SetMinimum(1000000);
//	relDz_FullTrack_plusEta->SetMinimum(50000);
	relDz_FullTrack_plusEta->Draw("e");	
	relDz_FullTrack_minusEta->Draw("e same");	
	legUR->SetHeader("minBiasTracks");
	legUR -> AddEntry(relDz_FullTrack_plusEta,"0 < #eta_{lab} < 2.4","lp");
	legUR -> AddEntry(relDz_FullTrack_minusEta,"-2.4 < #eta_{lab} < 0","lp");
	legUR->Draw();
	c1->SaveAs("minBiasTracksQualityOverlay_relDz.png");
	c1->Clear();	
	legUR->Clear();
/*
	gPad->SetLogy(1);
	SetHistStyle(absRelDxy_FullTrack_plusEta,1,3);
	SetHistStyle(absRelDxy_FullTrack_minusEta,2,0);
	cout << "absRelDxy plusEta Entry = " << absRelDxy_FullTrack_plusEta->GetEntries() << endl;
	cout << "absRelDxy minusEta Entry = " << absRelDxy_FullTrack_minusEta->GetEntries() << endl;
	absRelDxy_FullTrack_plusEta->GetXaxis()->SetTitle("|dxy/#sigma_{dxy}|");
	absRelDxy_FullTrack_plusEta->GetYaxis()->SetTitle("Tracks");
//	absRelDxy_FullTrack_plusEta->SetMinimum(100000);
//	absRelDxy_FullTrack_plusEta->SetMaximum(100000000);
	absRelDxy_FullTrack_plusEta->Draw("e");	
	absRelDxy_FullTrack_minusEta->Draw("e same");	
	legUR->SetHeader("minBiasTracks");
	legUR -> AddEntry(absRelDxy_FullTrack_plusEta,"0 < #eta_{lab} < 2.4","lp");
	legUR -> AddEntry(absRelDxy_FullTrack_minusEta,"-2.4 < #eta_{lab} < 0","lp");
	legUR->Draw();
	c1->SaveAs("minBiasTracksQualityOverlay_absRelDxy.png");
	c1->Clear();	
	legUR->Clear();

	gPad->SetLogy(1);
	SetHistStyle(absRelDz_FullTrack_plusEta,1,3);
	SetHistStyle(absRelDz_FullTrack_minusEta,2,0);
	cout << "absRelDz plusEta Entry = " << absRelDz_FullTrack_plusEta->GetEntries() << endl;
	cout << "absRelDz minusEta Entry = " << absRelDz_FullTrack_minusEta->GetEntries() << endl;
	absRelDz_FullTrack_plusEta->GetXaxis()->SetTitle("|dz/#sigma_{dz}|");
	absRelDz_FullTrack_plusEta->GetYaxis()->SetTitle("Tracks");
	absRelDz_FullTrack_plusEta->SetMinimum(1000000);
//	absRelDz_FullTrack_plusEta->SetMinimum(50000);
	absRelDz_FullTrack_plusEta->Draw("e");	
	absRelDz_FullTrack_minusEta->Draw("e same");	
	legUR->SetHeader("minBiasTracks");
	legUR -> AddEntry(absRelDz_FullTrack_plusEta,"0 < #eta_{lab} < 2.4","lp");
	legUR -> AddEntry(absRelDz_FullTrack_minusEta,"-2.4 < #eta_{lab} < 0","lp");
	legUR->Draw();
	c1->SaveAs("minBiasTracksQualityOverlay_absRelDz.png");
	c1->Clear();	
	legUR->Clear();

	gPad->SetLogy(1);
	SetHistStyle(dxy_FullTrack_plusEta,1,3);
	SetHistStyle(dxy_FullTrack_minusEta,2,0);
	cout << "dxy plusEta Entry = " << dxy_FullTrack_plusEta->GetEntries() << endl;
	cout << "dxy minusEta Entry = " << dxy_FullTrack_minusEta->GetEntries() << endl;
	dxy_FullTrack_plusEta->GetXaxis()->SetTitle("dxy");
	dxy_FullTrack_plusEta->GetYaxis()->SetTitle("Tracks");
//	dxy_FullTrack_plusEta->SetMinimum(100000);
//	dxy_FullTrack_plusEta->SetMaximum(100000000);
	dxy_FullTrack_plusEta->Draw("e");	
	dxy_FullTrack_minusEta->Draw("e same");	
	legUR->SetHeader("minBiasTracks");
	legUR -> AddEntry(dxy_FullTrack_plusEta,"0 < #eta_{lab} < 2.4","lp");
	legUR -> AddEntry(dxy_FullTrack_minusEta,"-2.4 < #eta_{lab} < 0","lp");
	legUR->Draw();
	c1->SaveAs("minBiasTracksQualityOverlay_dxy.png");
	c1->Clear();	
	legUR->Clear();

	gPad->SetLogy(1);
	SetHistStyle(dz_FullTrack_plusEta,1,3);
	SetHistStyle(dz_FullTrack_minusEta,2,0);
	dz_FullTrack_plusEta->Rebin(2);
	dz_FullTrack_minusEta->Rebin(2);
	cout << "dz plusEta Entry = " << dz_FullTrack_plusEta->GetEntries() << endl;
	cout << "dz minusEta Entry = " << dz_FullTrack_minusEta->GetEntries() << endl;
	dz_FullTrack_plusEta->GetXaxis()->SetTitle("dz");
	dz_FullTrack_plusEta->GetYaxis()->SetTitle("Tracks");
//	dz_FullTrack_plusEta->SetMinimum(50000);
	dz_FullTrack_plusEta->Draw("e");	
	dz_FullTrack_minusEta->Draw("e same");	
	legUR->SetHeader("minBiasTracks");
	legUR -> AddEntry(dz_FullTrack_plusEta,"0 < #eta_{lab} < 2.4","lp");
	legUR -> AddEntry(dz_FullTrack_minusEta,"-2.4 < #eta_{lab} < 0","lp");
	legUR->Draw();
	c1->SaveAs("minBiasTracksQualityOverlay_dz.png");
	c1->Clear();	
	legUR->Clear();

	gPad->SetLogy(1);
	SetHistStyle(dxyErr_FullTrack_plusEta,1,3);
	SetHistStyle(dxyErr_FullTrack_minusEta,2,0);
	cout << "dxyErr plusEta Entry = " << dxyErr_FullTrack_plusEta->GetEntries() << endl;
	cout << "dxyErr minusEta Entry = " << dxyErr_FullTrack_minusEta->GetEntries() << endl;
	dxyErr_FullTrack_plusEta->GetXaxis()->SetTitle("#sigma_{dxy}");
	dxyErr_FullTrack_plusEta->GetYaxis()->SetTitle("Tracks");
//	dxyErr_FullTrack_plusEta->SetMinimum(100000);
//	dxyErr_FullTrack_plusEta->SetMaximum(100000000);
	dxyErr_FullTrack_plusEta->Draw("e");	
	dxyErr_FullTrack_minusEta->Draw("e same");	
	legUR->SetHeader("minBiasTracks");
	legUR -> AddEntry(dxyErr_FullTrack_plusEta,"0 < #eta_{lab} < 2.4","lp");
	legUR -> AddEntry(dxyErr_FullTrack_minusEta,"-2.4 < #eta_{lab} < 0","lp");
	legUR->Draw();
	c1->SaveAs("minBiasTracksQualityOverlay_dxyErr.png");
	c1->Clear();	
	legUR->Clear();

	gPad->SetLogy(1);
	SetHistStyle(dzErr_FullTrack_plusEta,1,3);
	SetHistStyle(dzErr_FullTrack_minusEta,2,0);
	dzErr_FullTrack_plusEta->Rebin(2);
	dzErr_FullTrack_minusEta->Rebin(2);
	cout << "dzErr plusEta Entry = " << dzErr_FullTrack_plusEta->GetEntries() << endl;
	cout << "dzErr minusEta Entry = " << dzErr_FullTrack_minusEta->GetEntries() << endl;
	dzErr_FullTrack_plusEta->GetXaxis()->SetTitle("#sigma_{dz}");
	dzErr_FullTrack_plusEta->GetYaxis()->SetTitle("Tracks");
//	dzErr_FullTrack_plusEta->SetMinimum(1000000);
	dzErr_FullTrack_plusEta->Draw("e");	
	dzErr_FullTrack_minusEta->Draw("e same");	
	legUR->SetHeader("minBiasTracks");
	legUR -> AddEntry(dzErr_FullTrack_plusEta,"0 < #eta_{lab} < 2.4","lp");
	legUR -> AddEntry(dzErr_FullTrack_minusEta,"-2.4 < #eta_{lab} < 0","lp");
	legUR->Draw();
	c1->SaveAs("minBiasTracksQualityOverlay_dzErr.png");
	c1->Clear();	
	legUR->Clear();

	gPad->SetLogy(1);
	SetHistStyle(absEta_FullTrack_plusEta,1,3);
	SetHistStyle(absEta_FullTrack_minusEta,2,0);
	cout << "absEta plusEta Entry = " << absEta_FullTrack_plusEta->GetEntries() << endl;
	cout << "absEta minusEta Entry = " << absEta_FullTrack_minusEta->GetEntries() << endl;
	absEta_FullTrack_plusEta->GetXaxis()->SetTitle("|#eta|");
	absEta_FullTrack_plusEta->GetYaxis()->SetTitle("Tracks");
//	absEta_FullTrack_plusEta->SetMinimum(100000);
//	absEta_FullTrack_plusEta->SetMaximum(100000000);
	absEta_FullTrack_plusEta->Draw("e");	
	absEta_FullTrack_minusEta->Draw("e same");	
	legUR->SetHeader("minBiasTracks");
	legUR -> AddEntry(absEta_FullTrack_plusEta,"0 < #eta_{lab} < 2.4","lp");
	legUR -> AddEntry(absEta_FullTrack_minusEta,"-2.4 < #eta_{lab} < 0","lp");
	legUR->Draw();
	c1->SaveAs("minBiasTracksQualityOverlay_absEta.png");
	c1->Clear();	
	legUR->Clear();

	gPad->SetLogy(1);
	SetHistStyle(phi_FullTrack_plusEta,1,3);
	SetHistStyle(phi_FullTrack_minusEta,2,0);
	cout << "phi plusEta Entry = " << phi_FullTrack_plusEta->GetEntries() << endl;
	cout << "phi minusEta Entry = " << phi_FullTrack_minusEta->GetEntries() << endl;
	phi_FullTrack_plusEta->GetXaxis()->SetTitle("#phi");
	phi_FullTrack_plusEta->GetYaxis()->SetTitle("Tracks");
//	phi_FullTrack_plusEta->SetMinimum(1000000);
	phi_FullTrack_plusEta->Draw("e");	
	phi_FullTrack_minusEta->Draw("e same");	
	legUR->SetHeader("minBiasTracks");
	legUR -> AddEntry(phi_FullTrack_plusEta,"0 < #eta_{lab} < 2.4","lp");
	legUR -> AddEntry(phi_FullTrack_minusEta,"-2.4 < #eta_{lab} < 0","lp");
	legUR->Draw();
	c1->SaveAs("minBiasTracksQualityOverlay_phi.png");
	c1->Clear();	
	legUR->Clear();
*/

	//2. ratio etaPlus over etaMinus
	TGraph* gUnityLine = referenceLine(3, -100, 100);

	gPad->SetLogy(0);
	TH1D* relPtRatio = divideHistosDiffBins(relPt_FullTrack_plusEta, relPt_FullTrack_minusEta);
	SetHistStyle(relPtRatio,4,0);
	relPtRatio->GetXaxis()->SetTitle("#deltap_{T}/p_{T}");
	relPtRatio->GetYaxis()->SetTitle("Ratio");
	relPtRatio->SetMinimum(0.0);
	relPtRatio->SetMaximum(1.5);
	relPtRatio->Draw("e");
	gUnityLine->Draw("L same");
	legUR->SetHeader("minBiasTracks");
	legUR->AddEntry(relPtRatio,"(#eta>0)/(#eta<0)","lp");
	legUR->Draw();
	c1->SaveAs("minBiasTracksQualityRatio_relPt.png");
	c1->Clear();
	legUR->Clear();

	TH1D* relDxyRatio = divideHistosDiffBins(relDxy_FullTrack_plusEta, relDxy_FullTrack_minusEta);
	SetHistStyle(relDxyRatio,4,0);
	relDxyRatio->GetXaxis()->SetTitle("dxy/#sigma_{dxy}");
	relDxyRatio->GetXaxis()->CenterTitle();
	relDxyRatio->GetYaxis()->SetTitle("Ratio");
	relDxyRatio->SetMinimum(0.8);
	relDxyRatio->SetMaximum(1.2);
	relDxyRatio->Draw("e");
	gUnityLine->Draw("L same");
	legUR->SetHeader("minBiasTracks");
	legUR->AddEntry(relDxyRatio,"(#eta>0)/(#eta<0)","lp");
	legUR->Draw();
	c1->SaveAs("minBiasTracksQualityRatio_relDxy.png");
	c1->Clear();
	legUR->Clear();

	TH1D* relDzRatio = divideHistosDiffBins(relDz_FullTrack_plusEta, relDz_FullTrack_minusEta);
	SetHistStyle(relDzRatio,4,0);
	relDzRatio->GetXaxis()->SetTitle("dz/#sigma_{dz}");
	relDzRatio->GetXaxis()->CenterTitle();
	relDzRatio->GetYaxis()->SetTitle("Ratio");
	relDzRatio->SetMinimum(0.0);
	relDzRatio->SetMaximum(1.5);
	relDzRatio->Draw("e");
//	relDzRatio->GetXaxis()->SetRange(-15,15);
//	relDzRatio->GetYaxis()->SetRange(0.,1.5);
//	c1->Update();
	gUnityLine->Draw("L same");
	legBR->SetHeader("minBiasTracks");
	legBR->AddEntry(relDzRatio,"(#eta>0)/(#eta<0)","lp");
	legBR->Draw();
	c1->SaveAs("minBiasTracksQualityRatio_relDz.png");
	c1->Clear();
	legBM->Clear();
/*
	gPad->SetLogy(0);
	TH1D* absRelDxyRatio = divideHistosDiffBins(absRelDxy_FullTrack_plusEta, absRelDxy_FullTrack_minusEta);
	SetHistStyle(absRelDxyRatio,4,0);
	absRelDxyRatio->GetYaxis()->SetTitle("|dxy/#sigma_{dxy}|");
	absRelDxyRatio->GetYaxis()->SetTitle("Ratio");
	absRelDxyRatio->SetMinimum(0.8);
	absRelDxyRatio->SetMaximum(1.2);
	absRelDxyRatio->Draw("e");
	gUnityLine->Draw("L same");
	legUR->SetHeader("minBiasTracks");
	legUR->AddEntry(absRelDxyRatio,"(#eta>0)/(#eta<0)","lp");
	legUR->Draw();
	c1->SaveAs("minBiasTracksQualityRatio_absRelDxy.png");
	c1->Clear();
	legUR->Clear();

	TH1D* absRelDzRatio = divideHistosDiffBins(absRelDz_FullTrack_plusEta, absRelDz_FullTrack_minusEta);
	SetHistStyle(absRelDzRatio,4,0);
	absRelDzRatio->GetYaxis()->SetTitle("dz/#sigma_{dz}");
	absRelDzRatio->GetYaxis()->SetTitle("Ratio");
	absRelDzRatio->SetMinimum(0.0);
	absRelDzRatio->SetMaximum(1.5);
	absRelDzRatio->Draw("e");
	gUnityLine->Draw("L same");
	legUR->SetHeader("minBiasTracks");
	legUR->AddEntry(absRelDzRatio,"(#eta>0)/(#eta<0)","lp");
	legUR->Draw();
	c1->SaveAs("minBiasTracksQualityRatio_absRelDz.png");
	c1->Clear();
	legUR->Clear();

	gPad->SetLogy(0);
	TH1D* dxyRatio = divideHistosDiffBins(dxy_FullTrack_plusEta, dxy_FullTrack_minusEta);
	SetHistStyle(dxyRatio,4,0);
	dxyRatio->GetYaxis()->SetTitle("dxy");
	dxyRatio->GetYaxis()->SetTitle("Ratio");
	dxyRatio->SetMinimum(0.0);
	dxyRatio->SetMaximum(1.5);
	dxyRatio->Draw("e");
	gUnityLine->Draw("L same");
	legBM->SetHeader("minBiasTracks");
	legBM->AddEntry(dxyRatio,"(#eta>0)/(#eta<0)","lp");
	legBM->Draw();
	c1->SaveAs("minBiasTracksQualityRatio_dxy.png");
	c1->Clear();
	legBM->Clear();

	TH1D* dzRatio = divideHistosDiffBins(dz_FullTrack_plusEta, dz_FullTrack_minusEta);
	SetHistStyle(dzRatio,4,0);
	dzRatio->GetYaxis()->SetTitle("dz");
	dzRatio->GetYaxis()->SetTitle("Ratio");
	dzRatio->SetMinimum(0.0);
	dzRatio->SetMaximum(1.5);
	dzRatio->Draw("e");
	gUnityLine->Draw("L same");
	legBM->SetHeader("minBiasTracks");
	legBM->AddEntry(dzRatio,"(#eta>0)/(#eta<0)","lp");
	legBM->Draw();
	c1->SaveAs("minBiasTracksQualityRatio_dz.png");
	c1->Clear();
	legBM->Clear();

	gPad->SetLogy(0);
	TH1D* dxyErrRatio = divideHistosDiffBins(dxyErr_FullTrack_plusEta, dxyErr_FullTrack_minusEta);
	SetHistStyle(dxyErrRatio,4,0);
	dxyErrRatio->GetYaxis()->SetTitle("#sigma_{dxy}");
	dxyErrRatio->GetYaxis()->SetTitle("Ratio");
	dxyErrRatio->SetMinimum(0.0);
	dxyErrRatio->SetMaximum(1.5);
	dxyErrRatio->Draw("e");
	gUnityLine->Draw("L same");
	legBM->SetHeader("minBiasTracks");
	legBM->AddEntry(dxyErrRatio,"(#eta>0)/(#eta<0)","lp");
	legBM->Draw();
	c1->SaveAs("minBiasTracksQualityRatio_dxyErr.png");
	c1->Clear();
	legBM->Clear();

	TH1D* dzErrRatio = divideHistosDiffBins(dzErr_FullTrack_plusEta, dzErr_FullTrack_minusEta);
	SetHistStyle(dzErrRatio,4,0);
	dzErrRatio->GetYaxis()->SetTitle("#sigma_{dz}");
	dzErrRatio->GetYaxis()->SetTitle("Ratio");
	dzErrRatio->SetMinimum(0.0);
	dzErrRatio->SetMaximum(1.5);
	dzErrRatio->Draw("e");
	gUnityLine->Draw("L same");
	legUR->SetHeader("minBiasTracks");
	legUR->AddEntry(dzErrRatio,"(#eta>0)/(#eta<0)","lp");
	legUR->Draw();
	c1->SaveAs("minBiasTracksQualityRatio_dzErr.png");
	c1->Clear();
	legUR->Clear();

	gPad->SetLogy(0);
	TH1D* absEtaRatio = divideHistosDiffBins(absEta_FullTrack_plusEta, absEta_FullTrack_minusEta);
	SetHistStyle(absEtaRatio,4,0);
	absEtaRatio->GetYaxis()->SetTitle("|#eta|");
	absEtaRatio->GetYaxis()->SetTitle("Ratio");
	absEtaRatio->SetMinimum(0.0);
	absEtaRatio->SetMaximum(1.5);
	absEtaRatio->Draw("e");
	gUnityLine->Draw("L same");
	legUR->SetHeader("minBiasTracks");
	legUR->AddEntry(absEtaRatio,"(#eta>0)/(#eta<0)","lp");
	legUR->Draw();
	c1->SaveAs("minBiasTracksQualityRatio_absEta.png");
	c1->Clear();
	legUR->Clear();

	TH1D* phiRatio = divideHistosDiffBins(phi_FullTrack_plusEta, phi_FullTrack_minusEta);
	SetHistStyle(phiRatio,4,0);
	phiRatio->GetYaxis()->SetTitle("#phi");
	phiRatio->GetYaxis()->SetTitle("Ratio");
	phiRatio->SetMinimum(0.0);
	phiRatio->SetMaximum(1.5);
	phiRatio->Draw("e");
	gUnityLine->Draw("L same");
	legUR->SetHeader("minBiasTracks");
	legUR->AddEntry(phiRatio,"(#eta>0)/(#eta<0)","lp");
	legUR->Draw();
	c1->SaveAs("minBiasTracksQualityRatio_phi.png");
	c1->Clear();
	legUR->Clear();
*/
	std::cout << "Running Ended!" << std::endl;

}

// --- sub routines

TH1D* divideHistosDiffBins(TH1D* h_Num, TH1D* h_Den) {
	TH1D *h_ratio = (TH1D*)h_Num->Clone("h_ratio");
	h_ratio->Reset();
	for(int i = 1; i <= h_Num->GetNbinsX(); i++) {
		float content = h_Num->GetBinContent(i);
		float error = h_Num->GetBinError(i);
		float center = h_Num->GetBinCenter(i);
		int which_bin_in_h_Den = h_Den->FindBin(center);
		float content_h_Den = h_Den->GetBinContent(which_bin_in_h_Den);
		if(content_h_Den==0)
			continue;
		h_ratio->SetBinContent(i,content/content_h_Den);
		h_ratio->SetBinError(i,error/content_h_Den);
		}
	return h_ratio;
}

TH1D* divideHistosSameBins(TH1D* h_Num, TH1D* h_Den) {
	TH1D* h_ratio = (TH1D*)h_Num->Clone("h_ratio");
	h_ratio->Sumw2();
	h_ratio->Divide(h_Num,h_Den);
	return h_ratio;
}

TGraph* referenceLine(Double_t nBins, Double_t xMin, Double_t xMax) {
	Double_t x[531];
	Double_t y[531];
	for(Int_t n=0; n<nBins; n++) {
//	x[n]=binSet[0]+1.2*n*((binSet[nBins]-binSet[0])/nBins);
	x[n]=xMin+1.2*n*((xMax-xMin)/nBins);
	//x[n]=xMin+n*((xMax-xMin)/nBins);
	y[n]=1;
	}
	TGraph* gr_ref = new TGraph(nBins, x+1, y);
	gr_ref->SetLineColor(kRed);
//	gr_ref->Draw("L");
	return gr_ref;
}

void SetHistStyle(TH1* h, Int_t c, Int_t m) {
	Int_t colorArr[] = { kGray+3, kRed-4, kBlue, kOrange+7, kGreen+3, kAzure+8, kViolet-4, kBlack };
	//Int_t colorArr[] = { kGray+3, kRed-4, kBlue, kOrange+1, kGreen-3, kAzure+8, kViolet-4, kBlack };
	Int_t markerFullArr[] = {kFullCircle, kFullTriangleUp, kFullTriangleDown, kFullSquare};
	//Int_t markerOpenArr[] = {kOpenCircle, kOpenTriangleUp, kOpenTriangleDown, kOpenSquare};
	h-> SetMarkerColor(colorArr[c]);
	h-> SetMarkerStyle(markerFullArr[m]);
	h-> SetMarkerSize(1.2);
	h-> SetLineColor(colorArr[c]);
	h-> SetLineWidth(1.8);
}

void SetLegendStyle(TLegend* l) {
	l->SetFillColor(0);
	l->SetFillStyle(4000); //transparent
	l->SetBorderSize(0);
	l->SetMargin(0.2);
	l->SetTextSize(0.040);
}

void SetTextStyle(TPaveText* t) {
	t->SetFillColor(0);
	t->SetFillStyle(4000);
	t->SetBorderSize(0);
	t->SetMargin(0.2);
	t->SetTextSize(0.035);
}


