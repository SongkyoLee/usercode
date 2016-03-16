#include "TFile.h"
#include <TROOT.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TH1.h>
#include <TLegend.h>
#include <TMath.h>
#include <TPaveText.h>
#include <TText.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

//#include <vector>
//#include <list>
//#include <algorithm>
//#include <stdlib.h>

using namespace std;
TGraph* referenceLine(Double_t nBins, Double_t xMin, Double_t xMax);
void SetGraphStyle(TGraph* gr, Int_t c, Int_t m);
void SetLegendStyle(TLegend* l);
void SetTextStyle(TPaveText* t);

void draw_rawYield_yDep_Pbp()
{
	//set style
//	gROOT->Macro("/home/songkyo/kyo/2013/03_Jpsi/JpsiStyle.C");
	gROOT->Macro("/afs/cern.ch/work/k/kyolee/private/cms442/src/JpsiStyle.C");

	//read the fit_table ASCII file
	std::ifstream inFilePbp("fit_table_Pbp_yDep",std::ios::in);
	std::ifstream inFilepPb("fit_table_pPb_yDep",std::ios::in);

	//define the arrays
	// --- rap
	cout<<"NOTICE:: Rap direction and bins should be tuned by [ReadContents.cpp] already! (bw to fw)"<<endl;
//	string rapArr[] = {"-1.93-0.00", "0.00-1.93"}; // FwBw - CM
//	string rapArr[] = {"-2.4--0.47", "-0.47-1.47"}; // FwBw - Pbp
//	string rapArr[] = {"-2.4--0.47", "-0.47-1.47"}; // FwBw - Pbp
//	string rapArr[] = {"-1.93--1.75", "-1.75--1.50", "-1.50--1.25", "-1.25--1.00", "-1.00--0.75", "-0.75--0.50", "-0.50--0.25", "-0.25-0.00", "0.00-0.25", "0.25-0.05", "0.05-0.75", "0.75-1.00", "1.00-1.25", "1.25-1.50", "1.50-1.75", "1.75-1.93"}; // rapfiner2 - CM
//	string rapArr[] = {"-1.93--1.50", "-1.50--1.25", "-1.25--1.00", "-1.00--0.75", "-0.75--0.50", "-0.50--0.25", "-0.25-0.00", "0.00-0.25", "0.25-0.05", "0.05-0.75", "0.75-1.00", "1.00-1.25", "1.25-1.50", "1.50-1.93"}; // rapfiner3 - CM
	string rapArr[] = {"1.93-1.50", "1.50-1.25", "1.25-1.00", "1.00-0.75", "0.75-0.50", "0.50-0.25", "0.25-0.00", "0.00--0.25", "-0.25--0.05", "-0.05--0.75", "-0.75--1.00", "-1.00--1.25", "-1.25--1.50", "-1.50--1.93"}; // rapfiner3 - CM FwBw

	// --- pt
	string ptArr[] = {"6.5-30.0"};
//	string ptArr[]={"6.5-7.5", "7.5-8.5", "8.5-9.5", "9.5-10.5", "10.5-11.5", "11.5-12.5", "12.5-14.5", "14.5-16.5", "16.5-20.0", "20.0-30.0"};// ptfiner

	// ---cent
//	string centArr[] = {"70-100", "60-70", "50-60", "40-50", "30-40", "20-30", "10-20", "0-10"};
	string centArr[] = {"0.0-100.0"};

	const Int_t nRap = sizeof(rapArr)/sizeof(string);
	const Int_t nPt = sizeof(ptArr)/sizeof(string);
	const Int_t nCent = sizeof(centArr)/sizeof(string);
	cout << "nRap = " << nRap << endl;
	cout << "nPt = " << nPt << endl;
	cout << "nCent = " << nCent << endl;

	//warning messages
//	if (nRap%2 != 0) {
//		cout << "warning :: # of rapidity bins should be symmetric, and therefore even numbers " << endl;
//	}

	//Set x-axis for rapidity : should modify by hand (carefully)!!
	Double_t xaxis[nRap];
	xaxis[0]= (1.93+1.50)/2;
	xaxis[1]= (1.50+1.25)/2;
	xaxis[nRap-1]= (-1.93-1.50)/2;
	for (Int_t i=0+2; i<nRap-1; i++) {
		xaxis[i]=xaxis[i-1]-0.25;
	}
	for (Int_t i=0; i<nRap; i++) {
		cout << "xaxis["<<i<<"] = "<< xaxis[i] <<endl;
	}
	//warning messages
//	if (sizeof(axis)/sizeof(double) != nRap/2) {
//		cout << "warning :: #of x-axis should be half with # of rapidity bins " << endl;
//	}

	// get raw yield & error : Pbp run (Inclusive, prompt, non-prompt)
	Double_t nPbpSig[nCent][nPt][nRap], nPbpPr[nCent][nPt][nRap], nPbpNp[nCent][nPt][nRap];
	Double_t nPbpSigErr[nCent][nPt][nRap], nPbpPrErr[nCent][nPt][nRap], nPbpNpErr[nCent][nPt][nRap];
	// get raw yield & error : pPb run
	Double_t npPbSig[nCent][nPt][nRap], npPbPr[nCent][nPt][nRap], npPbNp[nCent][nPt][nRap];
	Double_t npPbSigErr[nCent][nPt][nRap], npPbPrErr[nCent][nPt][nRap], npPbNpErr[nCent][nPt][nRap];
	// ger raw yield $ error : Pbp+pPb
	Double_t nSig[nCent][nPt][nRap], nPr[nCent][nPt][nRap], nNp[nCent][nPt][nRap];
	Double_t nSigErr[nCent][nPt][nRap], nPrErr[nCent][nPt][nRap], nNpErr[nCent][nPt][nRap];

// merge Pbp & pPb data
for (Int_t ic=0; ic<nCent; ic++) {
	for (Int_t ip=0; ip<nPt; ip++) { 
		for (Int_t ir=0; ir<nRap; ir++) {
			inFilePbp >> nPbpSig[ic][ip][ir] >> nPbpSigErr[ic][ip][ir] >> nPbpPr[ic][ip][ir] >> nPbpPrErr[ic][ip][ir] >> nPbpNp[ic][ip][ir] >> nPbpNpErr[ic][ip][ir] ;
			inFilepPb >> npPbSig[ic][ip][ir] >> npPbSigErr[ic][ip][ir] >> npPbPr[ic][ip][ir] >> npPbPrErr[ic][ip][ir] >> npPbNp[ic][ip][ir] >> npPbNpErr[ic][ip][ir] ;
			nSig[ic][ip][ir] = nPbpSig[ic][ip][ir];
			nSigErr[ic][ip][ir] = nPbpSigErr[ic][ip][ir];
			nPr[ic][ip][ir] = nPbpPr[ic][ip][ir];
			nPrErr[ic][ip][ir] = nPbpPrErr[ic][ip][ir];
			nNp[ic][ip][ir] = nPbpNp[ic][ip][ir];
			nNpErr[ic][ip][ir] = nPbpNpErr[ic][ip][ir];
			cout << "cent : " << centArr[ic] << ", pT : " << ptArr[ip] << " , rap : " << rapArr[ir] << endl;
			cout << " Pbp Raw=" <<setw(10) << nPbpSig[ic][ip][ir] << setw(10) << nPbpSigErr[ic][ip][ir] << setw(10)<< nPbpPr[ic][ip][ir] << setw(10) << nPbpPrErr[ic][ip][ir] << setw(10) <<  nPbpNp[ic][ip][ir] << setw(10) << nPbpNpErr[ic][ip][ir] << endl;
			cout << " pPb Raw="<<setw(10) << npPbSig[ic][ip][ir] << setw(10) << npPbSigErr[ic][ip][ir] << setw(10)<< npPbPr[ic][ip][ir] << setw(10) << npPbPrErr[ic][ip][ir] << setw(10) << npPbNp[ic][ip][ir] << setw(10) << npPbNpErr[ic][ip][ir] << endl;
			cout << " Total Raw="<<setw(10) << nSig[ic][ip][ir] << setw(10) << nSigErr[ic][ip][ir] << setw(10)<< nPr[ic][ip][ir] << setw(10) << nPrErr[ic][ip][ir] << setw(10) <<  nNp[ic][ip][ir] << setw(10) << nNpErr[ic][ip][ir] << endl;
		}
	}
}
			

	TCanvas *c1 = new TCanvas("c1","", 200, 10, 800, 600);

	//draw the reference graph y=1
//	TGraph* gUnityLine = referenceLine(nRap, xaxis[7], xaxis[0]);

	//draw the Legend
//	TLegend *leg = new TLegend(0.68, 0.74, 0.85, 0.90); //upper right
	TLegend *leg = new TLegend(0.20, 0.75, 0.40, 0.90); //upper left
//	TLegend *leg = new TLegend(0.20, 0.15, 0.48, 0.33); //bottom left
	SetLegendStyle(leg);

	//draw test box for beam, rapidity, pT info
//	TPaveText *text = new TPaveText(0.20, 0.48, 0.50, 0.64, "NDC"); //upper left
//	TPaveText *text = new TPaveText(0.55, 0.15, 0.85, 0.33, "NDC"); // bottom right
//	TPaveText *text = new TPaveText(0.68, 0.58, 0.85, 0.72, "NDC"); //middle right
	TPaveText *text = new TPaveText(0.20, 0.58, 0.40, 0.72, "NDC"); //middle left
	SetTextStyle(text);

	//draw the TGraphError (rawYield)
	TGraphErrors *raw_inclusive[nCent][nPt];
	TGraphErrors *raw_prompt[nCent][nPt];
	TGraphErrors *raw_nonprompt[nCent][nPt];

	for (Int_t ic=0; ic<nCent; ic++) {
		for (Int_t ip=0; ip<nPt; ip++) {
			raw_inclusive[ic][ip] = new TGraphErrors(nRap, xaxis, nSig[ic][ip], 0, nSigErr[ic][ip]);
			SetGraphStyle(raw_inclusive[ic][ip], 0, 0);
			raw_inclusive[ic][ip]->SetTitle("");
			raw_inclusive[ic][ip]->GetXaxis()->SetTitle("y_{cm}");
			raw_inclusive[ic][ip]->GetXaxis()->SetRangeUser(-2.0,2.0);
			raw_inclusive[ic][ip]->GetYaxis()->SetTitle("raw yield");
//  		raw_inclusive[ic][ip]->SetMinimum(0.0);
//	  	raw_inclusive[ic][ip]->SetMaximum(1.2);
  		raw_inclusive[ic][ip]->SetMinimum(400);
	  	raw_inclusive[ic][ip]->SetMaximum(5600);
			raw_inclusive[ic][ip]->Draw("ALP");
			raw_prompt[ic][ip] = new TGraphErrors(nRap, xaxis, nPr[ic][ip], 0, nPrErr[ic][ip]);
			SetGraphStyle(raw_prompt[ic][ip], 1, 0);
			raw_prompt[ic][ip]->Draw("LP");
			raw_nonprompt[ic][ip] = new TGraphErrors(nRap, xaxis, nNp[ic][ip], 0, nNpErr[ic][ip]);
			SetGraphStyle(raw_nonprompt[ic][ip], 2, 0);
			raw_nonprompt[ic][ip]->Draw("LP");
//			gUnityLine->Draw("L");
			leg -> AddEntry(raw_inclusive[ic][ip],"Inclusive J/#psi","lp");
			leg -> AddEntry(raw_prompt[ic][ip],"Prompt J/#psi","lp");
			leg -> AddEntry(raw_nonprompt[ic][ip],"Nonprompt J/#psi","lp");
			leg->Draw();
//			text->AddText("pA (30/nb)");
			text->AddText("Pbp (18/nb)");
//			text->AddText("pPb (12/nb)");
//			text->AddText("pp (5.41/pb)");
//			text->AddText(Form("y_{cm} : %s",rapArr[ic].c_str()));
			text->AddText(Form("Cent : %s %% ",centArr[ic].c_str()));
			text->AddText(Form("p_{T} : %s GeV/c",ptArr[ip].c_str()));
			text->Draw();
			c1->Update();
			c1->SaveAs(Form("rawYield_yDep_Pbp_finer2_%s_%s.png",centArr[ic].c_str(),ptArr[ip].c_str()));
			leg->Clear();
			text->Clear();
			c1->Clear();
		}
	}
	return;
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
	return gr_ref;
}

void SetGraphStyle(TGraph* gr, Int_t c, Int_t m) {
	Int_t colorArr[] = { kGray+3, kRed-4, kBlue, kViolet-4, kAzure+8, kBlack };
	Int_t markerFullArr[] = {kFullCircle, kFullTriangleUp, kFullTriangleDown, kFullSquare};
	//Int_t markerFullArr[] = {kFullCircle, kFullTriangleUp, kFullTriangleDown, kFullSquare, kFullStar, kFullDiamond};
	//Int_t markerOpenArr[] = {kOpenCircle, kOpenTriangleUp, kOpenTriangleDown, kOpenSquare, kOpenStar, kOpenDiamond};

	gr-> SetMarkerColor(colorArr[c]);
	gr-> SetMarkerStyle(markerFullArr[m]);
	gr-> SetMarkerSize(1.2);
	gr-> SetLineColor(colorArr[c]);
	gr-> SetLineWidth(0.8);
}

void SetLegendStyle(TLegend* l) {
	l->SetFillColor(0);
	l->SetFillStyle(4000);
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
