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
void SetGraphStyle(TGraph* gr, Int_t c, Int_t m);
void SetLegendStyle(TLegend* l);
void SetTextStyle(TPaveText* t);

void draw_Rcp_centDep()
{
	//set style
	gROOT->Macro("/home/songkyo/kyo/2013/03_Jpsi/JpsiStyle.C");

	//read the fit_table ASCII file
	std::ifstream inFile("fit_table_coarser",std::ios::in);

	string rapArr[] = {"-2.4--0.47", "-0.47-1.47"};
	string ptArr[] = {"0.0-6.5", "6.5-30.0"};
//	string centArr[] = {"70-100", "60-70", "50-60", "40-50", "30-40", "20-30", "10-20", "0-10"};
//	string centArr[] = {"50-100", "30-50", "10-30", "0-10"};
	string centArr[] = {"50-100", "40-50", "30-40", "20-30", "10-20", "0-10"};

	const Int_t nRap = sizeof(rapArr)/sizeof(string);
	const Int_t nPt = sizeof(ptArr)/sizeof(string);
	const Int_t nCent = sizeof(centArr)/sizeof(string);
	cout << "nRap = " << nRap << endl;
	cout << "nPt = " << nPt << endl;
	cout << "nCent = " << nCent << endl;

	Double_t xaxis[nCent];
	for (Int_t i=0; i<nCent; i++) {
		xaxis[i]=(0.5+i)*(0+100)/nCent;
	}

	Double_t nSig[nRap][nPt][nCent], nPr[nRap][nPt][nCent], nNp[nRap][nPt][nCent];
	Double_t nSigErr[nRap][nPt][nCent], nPrErr[nRap][nPt][nCent], nNpErr[nRap][nPt][nCent];
	Double_t rcpSig[nRap][nPt][nCent], rcpPr[nRap][nPt][nCent], rcpNp[nRap][nPt][nCent];
	Double_t rcpSigErr[nRap][nPt][nCent], rcpPrErr[nRap][nPt][nCent], rcpNpErr[nRap][nPt][nCent];

for (Int_t k=0; k<nRap; k++) { 
	for (Int_t j=0; j<nPt; j++) {
		for (Int_t i=0; i<nCent; i++) {
			inFile >> nSig[k][j][i] >> nSigErr[k][j][i] >> nPr[k][j][i] >> nPrErr[k][j][i] >> nNp[k][j][i] >> nNpErr[k][j][i] ;
			cout << "rap : " << rapArr[k] << ", pT : " << ptArr[j] << " , cent : " << centArr[i] << endl;
			cout << setw(10) << nSig[k][j][i] << setw(10) << nSigErr[k][j][i] << setw(10)<< nPr[k][j][i] << setw(10) << nPrErr[k][j][i] << setw(10) <<  nNp[k][j][i] << setw(10) << nNpErr[k][j][i] << endl;
			rcpSig[k][j][i]= nSig[k][j][i]/nSig[k][j][0];
			rcpPr[k][j][i]=nPr[k][j][i]/nPr[k][j][0];
			rcpNp[k][j][i]=nNp[k][j][i]/nNp[k][j][0];
			rcpSigErr[k][j][i]=rcpSig[k][j][i]*TMath::Sqrt( TMath::Power(nSigErr[k][j][i]/nSig[k][j][i],2)+TMath::Power(nSigErr[k][j][0]/nSig[k][j][0],2) );
			rcpPrErr[k][j][i]=rcpPr[k][j][i]*TMath::Sqrt( TMath::Power(nPrErr[k][j][i]/nPr[k][j][i],2)+TMath::Power(nPrErr[k][j][0]/nPr[k][j][0],2) );
			rcpNpErr[k][j][i]=rcpNp[k][j][i]*TMath::Sqrt( TMath::Power(nNpErr[k][j][i]/nNp[k][j][i],2)+TMath::Power(nNpErr[k][j][0]/nNp[k][j][0],2) );
		}
	}
}

	TCanvas *c1 = new TCanvas("c1","", 200, 10, 600, 600);

	//draw the reference graph y=1
	Double_t x[]={0., 100.};
	Double_t y[]={1., 1.};
//	Double_t y[nCent];
//	for (Int_t i=0; i<nCent; i++) {
//		y[i]=1.;
//	}
  const Int_t n = sizeof(x)/sizeof(double);
	TGraph* gr_ref = new TGraph(n, x, y);
//	TGraph* gr_ref = new TGraph(nCent, xaxis, y);
	gr_ref->SetLineColor(kBlack);

	//draw the Legend
	TLegend *leg = new TLegend(0.20, 0.70, 0.50, 0.90);
	SetLegendStyle(leg);

	//draw test box for beam, rapidity, pT info
	TPaveText *text = new TPaveText(0.20, 0.48, 0.50, 0.64, "NDC");
	SetTextStyle(text);

	//draw the TGraphError
	TGraphErrors *rcp_inclusive[nRap][nPt];
	TGraphErrors *rcp_prompt[nRap][nPt];
	TGraphErrors *rcp_nonprompt[nRap][nPt];

	for (Int_t k=0; k<nRap; k++) {
		for (Int_t j=0; j<nPt; j++) {
			rcp_inclusive[k][j] = new TGraphErrors(nCent, xaxis, rcpSig[k][j], 0, rcpSigErr[k][j]); //temp Err
			SetGraphStyle(rcp_inclusive[k][j], 0, 0);
			rcp_inclusive[k][j]->SetTitle("");
			rcp_inclusive[k][j]->GetXaxis()->SetTitle("centrality");
			rcp_inclusive[k][j]->GetYaxis()->SetTitle("raw yield R_{cp}");
//  	rcp_inclusive[k][j]->SetMinimum(0.0);
//  	rcp_inclusive[k][j]->SetMaximum(25.);
			rcp_inclusive[k][j]->Draw("ALP");
			rcp_prompt[k][j] = new TGraphErrors(nCent, xaxis, rcpPr[k][j], 0, rcpPrErr[k][j]); //temp Err
			SetGraphStyle(rcp_prompt[k][j], 1, 0);
			rcp_prompt[k][j]->Draw("LP");
			rcp_nonprompt[k][j] = new TGraphErrors(nCent, xaxis, rcpNp[k][j], 0, rcpNpErr[k][j]); //temp Err
			SetGraphStyle(rcp_nonprompt[k][j], 2, 0);
			rcp_nonprompt[k][j]->Draw("LP");
			gr_ref->Draw("L");
			leg -> AddEntry(rcp_inclusive[k][j],"Inclusive J/#psi","lp");
			leg -> AddEntry(rcp_prompt[k][j],"Prompt J/#psi","lp");
			leg -> AddEntry(rcp_nonprompt[k][j],"Nonprompt J/#psi","lp");
			leg->Draw();
			text->AddText("Pbp (18.4/nb)");
//			text->AddText("pPb (12.6/nb)");
			text->AddText(Form("y : %s",rapArr[k].c_str()));
			text->AddText(Form("p_{T} : %s GeV/c",ptArr[j].c_str()));
			text->Draw();
			for(Int_t i=0; i<nCent; i++) {
					char xLabel[531];
					sprintf(xLabel,"%s%%",centArr[i].c_str());
					rcp_inclusive[k][j]->GetXaxis()->Set(nCent,0,100);
					rcp_inclusive[k][j]->GetXaxis()->SetBinLabel(i+1,xLabel);
			}
			c1->Update();
			c1->SaveAs(Form("Rcp_cent_coarser_%s_%s.pdf",rapArr[k].c_str(),ptArr[j].c_str()));
			leg->Clear();
			text->Clear();
			c1->Clear();
		}
	}
}

void SetGraphStyle(TGraph* gr, Int_t c, Int_t m) {
	Int_t colorArr[] = { kGray+3, kRed-4, kBlue, kViolet-4, kAzure+8, kBlack };
	Int_t markerFullArr[] = {kFullCircle, kFullTriangleUp, kFullTriangleDown, kFullSquare, kFullStar, kFullDiamond};
	Int_t markerOpenArr[] = {kOpenCircle, kOpenTriangleUp, kOpenTriangleDown, kOpenSquare, kOpenStar, kOpenDiamond};

	gr-> SetMarkerColor(colorArr[c]);
	gr-> SetMarkerStyle(markerFullArr[m]);
	gr-> SetMarkerSize(1.0);
	gr-> SetLineColor(colorArr[c]);
	gr-> SetLineWidth(0.5);
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
