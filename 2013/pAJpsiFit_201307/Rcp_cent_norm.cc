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

void Rcp_cent_norm()
{
	//set style
	gROOT->Macro("/home/songkyo/kyo/2013/03_Jpsi/JpsiStyle.C");

	//read the fit_table ASCII file
	std::ifstream inFile("fit_table_test02",std::ios::in);

	// define the arrays
//	string rapArr[] = {"-2.4--0.47", "-0.47-1.47"};
	string rapArr[] = {"-2.4--1.47", "-1.47--0.47","-0.47-0.53", "0.53-1.47"};
//	string ptArr[] = {"0.0-6.5", "6.5-30.0"};
	string ptArr[] = {"6.5-10.0", "10.0-30.0"};
	string centArr[] = {"70-100", "60-70", "50-60", "40-50", "30-40", "20-30", "10-20", "0-10"};
//	string centArr[] = {"50-100", "40-50", "30-40", "20-30", "10-20", "0-10"};
//	string centArr[] = {"70-100", "50-70", "30-50", "10-30", "0-10"};
//	string centArr[] = {"50-100", "30-50", "10-30", "0-10"};

	Double_t nCollArr[] = { 2.97, 5.57, 7.34, 8.89, 10.08, 11.15, 12.14, 13.66 }; //2.97? 3.03?
//	Double_t nCollArr[] = {4.366, 8.89, 10.08, 11.15, 12.14, 13.66 };
//	Double_t nCollArr[] = {2.97, 6.46, 9.485, 11.645, 13.66 };
//	Double_t nCollArr[] = {4.366, 9.485, 11.645, 13.66 };

	Double_t nCollErrArr[] = {0.165, 0.79, 1.02, 0.95, 0.74, 0.67, 0.84, 1.22};
//	Double_t nCollErrArr[] = {0.276, 0.95, 0.74, 0.67, 0.84, 1.22};
//	Double_t nCollErrArr[] = {0.165, 0.645, 0.602, 0.537, 1.22};
//	Double_t nCollErrArr[] = {0.276, 0.602, 0.537, 1.22};

	const Int_t nRap = sizeof(rapArr)/sizeof(string);
	const Int_t nPt = sizeof(ptArr)/sizeof(string);
	const Int_t nCent = sizeof(centArr)/sizeof(string);
	cout << "nRap = " << nRap << endl;
	cout << "nPt = " << nPt << endl;
	cout << "nCent = " << nCent << endl;

	// Warning messages
	if (nCent != sizeof(nCollArr)/sizeof(double)) {
		cout << "warning : # of nColl bins should match with # of centrality bins!!" << endl;
	}
	if ( sizeof(nCollArr)/sizeof(double) != sizeof(nCollArr)/sizeof(double)) {
		cout << "warning : # of nColl bins and # of nCollErr bins doesn't match!!" << endl;
	}

	//Set x-axis for centrality
	Double_t xaxis[nCent];
	for (Int_t i=0; i<nCent; i++) {
		xaxis[i]=(0.5+i)*(0+100)/nCent;
	}

	Double_t nSig[nRap][nPt][nCent], nPr[nRap][nPt][nCent], nNp[nRap][nPt][nCent];
	Double_t nSigErr[nRap][nPt][nCent], nPrErr[nRap][nPt][nCent], nNpErr[nRap][nPt][nCent];
	Double_t rcpSig[nRap][nPt][nCent], rcpPr[nRap][nPt][nCent], rcpNp[nRap][nPt][nCent];
	Double_t rcpSigErr[nRap][nPt][nCent], rcpPrErr[nRap][nPt][nCent], rcpNpErr[nRap][nPt][nCent];
	Double_t nFactor[nCent];
	Double_t nFactorErr[nCent];
	Double_t rcpNormSig[nRap][nPt][nCent], rcpNormPr[nRap][nPt][nCent], rcpNormNp[nRap][nPt][nCent];
	Double_t rcpNormSigErr[nRap][nPt][nCent], rcpNormPrErr[nRap][nPt][nCent], rcpNormNpErr[nRap][nPt][nCent];

// Calculate the normalization factor first (from Ncoll)
for (Int_t i=0; i<nCent; i++) {
	nFactor[i] = nCollArr[0]/nCollArr[i];
	nFactorErr[i] = nFactor[i]*TMath::Sqrt( TMath::Power(nCollErrArr[0]/nCollArr[0],2)+TMath::Power(nCollErrArr[i]/nCollArr[i],2) );
	cout << "nColl[i] = " << nCollArr[i] << ", nColl[0] = " << nCollArr[0] << endl;
	cout << "nFactor[i] =" << nFactor[i] << endl;
	cout << "nFactorErr[i] =" << nFactorErr[i] << endl;
}

// loop for Calculating Rcp 
for (Int_t k=0; k<nRap; k++) { 
	for (Int_t j=0; j<nPt; j++) {
		for (Int_t i=0; i<nCent; i++) {
			//Read the data from file
			inFile >> nSig[k][j][i] >> nSigErr[k][j][i] >> nPr[k][j][i] >> nPrErr[k][j][i] >> nNp[k][j][i] >> nNpErr[k][j][i] ;
			cout << "rap : " << rapArr[k] << ", pT : " << ptArr[j] << " , cent : " << centArr[i] << endl;
			cout << setw(10) << nSig[k][j][i] << setw(10) << nSigErr[k][j][i] << setw(10)<< nPr[k][j][i] << setw(10) << nPrErr[k][j][i] << setw(10) <<  nNp[k][j][i] << setw(10) << nNpErr[k][j][i] << endl;

			//Rcp raw yield
			rcpSig[k][j][i]= nSig[k][j][i]/nSig[k][j][0];
			rcpPr[k][j][i]= nPr[k][j][i]/nPr[k][j][0];
			rcpNp[k][j][i]= nNp[k][j][i]/nNp[k][j][0];
			//Rcp normalized
			rcpNormSig[k][j][i]= nFactor[i]*(nSig[k][j][i]/nSig[k][j][0]);
			rcpNormPr[k][j][i]= nFactor[i]*(nPr[k][j][i]/nPr[k][j][0]);
			rcpNormNp[k][j][i]= nFactor[i]*(nNp[k][j][i]/nNp[k][j][0]);

			cout << "nFactor = " << nFactor[i] << endl;
			cout << "rcpSig = " << rcpSig[k][j][i] << ", rcpPr = " << rcpPr[k][j][i] << ", rcpNp = "<< rcpNp[k][j][i] << endl;
			cout << "rcpNormSig = " << rcpNormSig[k][j][i] << ", rcpNormPr = " << rcpNormPr[k][j][i] << ", rcpNormNp = "<< rcpNormNp[k][j][i] << endl;
//			cout << "          " << endl;

			// error propagation for rcp_raw=NCent/NPeri
			rcpSigErr[k][j][i]=rcpSig[k][j][i]*TMath::Sqrt( TMath::Power(nSigErr[k][j][i]/nSig[k][j][i],2)+TMath::Power(nSigErr[k][j][0]/nSig[k][j][0],2) );
			rcpPrErr[k][j][i]=rcpPr[k][j][i]*TMath::Sqrt( TMath::Power(nPrErr[k][j][i]/nPr[k][j][i],2)+TMath::Power(nPrErr[k][j][0]/nPr[k][j][0],2) );
			rcpNpErr[k][j][i]=rcpNp[k][j][i]*TMath::Sqrt( TMath::Power(nNpErr[k][j][i]/nNp[k][j][i],2)+TMath::Power(nNpErr[k][j][0]/nNp[k][j][0],2) );

			// error propagation for Rcp=N*rcp_raw
			rcpNormSigErr[k][j][i]=rcpNormSig[k][j][i]*TMath::Sqrt( TMath::Power(nFactorErr[i]/nFactor[i],2)+TMath::Power(rcpSigErr[k][j][i]/rcpSig[k][j][i],2) );
			rcpNormPrErr[k][j][i]=rcpNormPr[k][j][i]*TMath::Sqrt( TMath::Power(nFactorErr[i]/nFactor[i],2)+TMath::Power(rcpPrErr[k][j][i]/rcpPr[k][j][i],2) );
			rcpNormNpErr[k][j][i]=rcpNormNp[k][j][i]*TMath::Sqrt( TMath::Power(nFactorErr[i]/nFactor[i],2)+TMath::Power(rcpNpErr[k][j][i]/rcpNp[k][j][i],2) );

		}
	}
}

	TCanvas *c1 = new TCanvas("c1","", 200, 10, 600, 600);

	//draw the reference graph y=1
	Double_t x[]={0., 100.};
	Double_t y[]={1., 1.};
  const Int_t n = sizeof(x)/sizeof(double);
	TGraph* gr_ref = new TGraph(n, x, y);
	gr_ref->SetLineColor(kBlack);

	//draw the Legend
//	TLegend *leg = new TLegend(0.20, 0.70, 0.50, 0.90);
	TLegend *leg = new TLegend(0.50, 0.75, 0.80, 0.90);
	SetLegendStyle(leg);

	//draw test box for beam, rapidity, pT info
//	TPaveText *text = new TPaveText(0.20, 0.48, 0.50, 0.64, "NDC");
//	TPaveText *text = new TPaveText(0.55, 0.55, 0.85, 0.70, "NDC");
	TPaveText *text = new TPaveText(0.20, 0.75, 0.50, 0.90, "NDC");
	SetTextStyle(text);

	//draw the TGraphError
	TGraphErrors *rcp_inclusive[nRap][nPt];
	TGraphErrors *rcp_prompt[nRap][nPt];
	TGraphErrors *rcp_nonprompt[nRap][nPt];

	for (Int_t k=0; k<nRap; k++) {
		for (Int_t j=0; j<nPt; j++) {
			// Inclusive J/psi Graph
			rcp_inclusive[k][j] = new TGraphErrors(nCent, xaxis, rcpNormSig[k][j], 0, rcpNormSigErr[k][j]); //temp Err
			SetGraphStyle(rcp_inclusive[k][j], 0, 0);
			rcp_inclusive[k][j]->SetTitle("");
			rcp_inclusive[k][j]->GetXaxis()->SetTitle("centrality");
			rcp_inclusive[k][j]->GetYaxis()->SetTitle("R_{cp} (normalized by N_{coll})");
	  	rcp_inclusive[k][j]->SetMinimum(0.0);
	 	 	rcp_inclusive[k][j]->SetMaximum(2.4);
			rcp_inclusive[k][j]->Draw("ALP");
			// prompt J/psi Graph
			rcp_prompt[k][j] = new TGraphErrors(nCent, xaxis, rcpNormPr[k][j], 0, rcpNormPrErr[k][j]); //temp Err
			SetGraphStyle(rcp_prompt[k][j], 1, 0);
			rcp_prompt[k][j]->Draw("LP");
			//non-prompt J/psi Graph
			rcp_nonprompt[k][j] = new TGraphErrors(nCent, xaxis, rcpNormNp[k][j], 0, rcpNormNpErr[k][j]); //temp Err
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
			c1->SaveAs(Form("Rcp_cent_norm_test02_%s_%s.pdf",rapArr[k].c_str(),ptArr[j].c_str()));
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
