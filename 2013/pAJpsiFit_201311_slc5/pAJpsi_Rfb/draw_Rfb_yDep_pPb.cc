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

void draw_Rfb_yDep_pPb()
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
	string rapArr[] = {"-1.93--1.50", "-1.50--1.25", "-1.25--1.00", "-1.00--0.75", "-0.75--0.50", "-0.50--0.25", "-0.25-0.00", "0.00-0.25", "0.25-0.05", "0.05-0.75", "0.75-1.00", "1.00-1.25", "1.25-1.50", "1.50-1.93"}; // rapfiner3 - CM

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
	if (nRap%2 != 0) {
		cout << "warning :: # of rapidity bins should be symmetric, and therefore even numbers " << endl;
	}

	//Set x-axis for rapidity : should modify by hand (carefully)!!
	const Int_t nXaxis = nRap/2;
	cout << "nXaxis = " << nXaxis <<endl;
	Double_t xaxis[nXaxis];
	xaxis[0]= (1.50+1.93)/2;
	xaxis[1]= (1.25+1.50)/2;
	for (Int_t i=0+2; i<nXaxis; i++) {
		xaxis[i]=xaxis[i-1]-0.25;
	}
	for (Int_t i=0; i<nXaxis; i++) {
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
	// Rfb (array # nRap to nXaxis)
	Double_t rfbSig[nCent][nPt][nXaxis], rfbPr[nCent][nPt][nXaxis], rfbNp[nCent][nPt][nXaxis];
	Double_t rfbSigErr[nCent][nPt][nXaxis], rfbPrErr[nCent][nPt][nXaxis], rfbNpErr[nCent][nPt][nXaxis];

// merge Pbp & pPb data
for (Int_t ic=0; ic<nCent; ic++) {
	for (Int_t ip=0; ip<nPt; ip++) { 
		for (Int_t ir=0; ir<nRap; ir++) {
			inFilePbp >> nPbpSig[ic][ip][ir] >> nPbpSigErr[ic][ip][ir] >> nPbpPr[ic][ip][ir] >> nPbpPrErr[ic][ip][ir] >> nPbpNp[ic][ip][ir] >> nPbpNpErr[ic][ip][ir] ;
			inFilepPb >> npPbSig[ic][ip][ir] >> npPbSigErr[ic][ip][ir] >> npPbPr[ic][ip][ir] >> npPbPrErr[ic][ip][ir] >> npPbNp[ic][ip][ir] >> npPbNpErr[ic][ip][ir] ;
			nSig[ic][ip][ir] = npPbSig[ic][ip][ir];
			nSigErr[ic][ip][ir] = npPbSigErr[ic][ip][ir];
			nPr[ic][ip][ir] = npPbPr[ic][ip][ir];
			nPrErr[ic][ip][ir] = npPbPrErr[ic][ip][ir];
			nNp[ic][ip][ir] = npPbNp[ic][ip][ir];
			nNpErr[ic][ip][ir] = npPbNpErr[ic][ip][ir];
			cout << "cent : " << centArr[ic] << ", pT : " << ptArr[ip] << " , rap : " << rapArr[ir] << endl;
			cout << " Pbp Raw=" <<setw(10) << nPbpSig[ic][ip][ir] << setw(10) << nPbpSigErr[ic][ip][ir] << setw(10)<< nPbpPr[ic][ip][ir] << setw(10) << nPbpPrErr[ic][ip][ir] << setw(10) <<  nPbpNp[ic][ip][ir] << setw(10) << nPbpNpErr[ic][ip][ir] << endl;
			cout << " pPb Raw="<<setw(10) << npPbSig[ic][ip][ir] << setw(10) << npPbSigErr[ic][ip][ir] << setw(10)<< npPbPr[ic][ip][ir] << setw(10) << npPbPrErr[ic][ip][ir] << setw(10) << npPbNp[ic][ip][ir] << setw(10) << npPbNpErr[ic][ip][ir] << endl;
			cout << " Total Raw="<<setw(10) << nSig[ic][ip][ir] << setw(10) << nSigErr[ic][ip][ir] << setw(10)<< nPr[ic][ip][ir] << setw(10) << nPrErr[ic][ip][ir] << setw(10) <<  nNp[ic][ip][ir] << setw(10) << nNpErr[ic][ip][ir] << endl;
		}
	}
}
			
// calculate Fw/Bw = Rfb
for (Int_t ic=0; ic<nCent; ic++) {
	for (Int_t ip=0; ip<nPt; ip++) { 
		for (Int_t ir=0; ir<nXaxis; ir++) {
			rfbSig[ic][ip][ir] = nSig[ic][ip][ir]/nSig[ic][ip][nRap-1-ir]; // Fw/Bw
			rfbPr[ic][ip][ir] = nPr[ic][ip][ir]/nPr[ic][ip][nRap-1-ir];
			rfbNp[ic][ip][ir] = nNp[ic][ip][ir]/nNp[ic][ip][nRap-1-ir];
			rfbSigErr[ic][ip][ir]= rfbSig[ic][ip][ir]*TMath::Sqrt( TMath::Power(nSigErr[ic][ip][ir]/nSig[ic][ip][ir],2)+TMath::Power(nSigErr[ic][ip][nRap-1-ir]/nSig[ic][ip][nRap-1-ir],2) );
			rfbPrErr[ic][ip][ir]= rfbPr[ic][ip][ir]*TMath::Sqrt( TMath::Power(nPrErr[ic][ip][ir]/nPr[ic][ip][ir],2)+TMath::Power(nPrErr[ic][ip][nRap-1-ir]/nPr[ic][ip][nRap-1-ir],2) );
			rfbNpErr[ic][ip][ir]= rfbNp[ic][ip][ir]*TMath::Sqrt( TMath::Power(nNpErr[ic][ip][ir]/nNp[ic][ip][ir],2)+TMath::Power(nNpErr[ic][ip][nRap-1-ir]/nNp[ic][ip][nRap-1-ir],2) );
			cout << ir << "th rapbin : FW= " << rapArr[ir] << ", BW=" << rapArr[nRap-1-ir]<<endl;
			cout << "Rfb="<< setw(10) << rfbSig[ic][ip][ir] << setw(10) << rfbSigErr[ic][ip][ir] << setw(10)<< rfbPr[ic][ip][ir] << setw(10) << rfbPrErr[ic][ip][ir] << setw(10) <<  rfbNp[ic][ip][ir] << setw(10) << rfbNpErr[ic][ip][ir] << endl;
			cout << " " << endl;
		}
	}
} // end of calculation

	TCanvas *c1 = new TCanvas("c1","", 200, 10, 600, 600);

	//draw the reference graph y=1
	TGraph* gUnityLine = referenceLine(nXaxis, xaxis[7], xaxis[0]);

	//draw the Legend
//	Legend *legUR = new TLegend(0.55, 0.74, 0.80, 0.90); //upper right
//	TLegend *leg = new TLegend(0.20, 0.70, 0.50, 0.90); //upper left
	TLegend *leg = new TLegend(0.20, 0.15, 0.48, 0.33); //bottom left
	SetLegendStyle(leg);

	//draw test box for beam, rapidity, pT info
//	TPaveText *text = new TPaveText(0.20, 0.48, 0.50, 0.64, "NDC"); //upper left
	TPaveText *text = new TPaveText(0.55, 0.15, 0.85, 0.33, "NDC"); // bottom right
	SetTextStyle(text);

	//draw the TGraphError (Rfb)
	TGraphErrors *rfb_inclusive[nCent][nPt];
	TGraphErrors *rfb_prompt[nCent][nPt];
	TGraphErrors *rfb_nonprompt[nCent][nPt];

	for (Int_t ic=0; ic<nCent; ic++) {
		for (Int_t ip=0; ip<nPt; ip++) {
			rfb_inclusive[ic][ip] = new TGraphErrors(nXaxis, xaxis, rfbSig[ic][ip], 0, rfbSigErr[ic][ip]);
			SetGraphStyle(rfb_inclusive[ic][ip], 0, 0);
			rfb_inclusive[ic][ip]->SetTitle("");
			rfb_inclusive[ic][ip]->GetXaxis()->SetTitle("y_{cm}");
			rfb_inclusive[ic][ip]->GetYaxis()->SetTitle("raw yield R_{FB}");
//  		rfb_inclusive[ic][ip]->SetMinimum(0.0);
//	  	rfb_inclusive[ic][ip]->SetMaximum(1.2);
  		rfb_inclusive[ic][ip]->SetMinimum(0.5);
	  	rfb_inclusive[ic][ip]->SetMaximum(2.5);
			rfb_inclusive[ic][ip]->Draw("ALP");
			rfb_prompt[ic][ip] = new TGraphErrors(nXaxis, xaxis, rfbPr[ic][ip], 0, rfbPrErr[ic][ip]);
			SetGraphStyle(rfb_prompt[ic][ip], 1, 0);
			rfb_prompt[ic][ip]->Draw("LP");
			rfb_nonprompt[ic][ip] = new TGraphErrors(nXaxis, xaxis, rfbNp[ic][ip], 0, rfbNpErr[ic][ip]);
			SetGraphStyle(rfb_nonprompt[ic][ip], 2, 0);
			rfb_nonprompt[ic][ip]->Draw("LP");
			gUnityLine->Draw("L");
			leg -> AddEntry(rfb_inclusive[ic][ip],"Inclusive J/#psi","lp");
			leg -> AddEntry(rfb_prompt[ic][ip],"Prompt J/#psi","lp");
			leg -> AddEntry(rfb_nonprompt[ic][ip],"Nonprompt J/#psi","lp");
			leg->Draw();
//			text->AddText("pA (30/nb)");
//			text->AddText("Pbp (18/nb)");
			text->AddText("pPb (12/nb)");
//			text->AddText("pp (5.41/pb)");
//			text->AddText(Form("y_{cm} : %s",rapArr[ic].c_str()));
			text->AddText(Form("Cent : %s %% ",centArr[ic].c_str()));
			text->AddText(Form("p_{T} : %s GeV/c",ptArr[ip].c_str()));
			text->Draw();
			c1->Update();
//			c1->SaveAs(Form("Rfb_yDep_finer_%s_%s.pdf",centArr[ic].c_str(),ptArr[ip].c_str()));
			c1->SaveAs(Form("Rfb_yDep_pPb_finer2_%s_%s.png",centArr[ic].c_str(),ptArr[ip].c_str()));
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
