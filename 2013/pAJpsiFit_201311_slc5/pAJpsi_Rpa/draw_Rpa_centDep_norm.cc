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

void Rpa_cent_norm()
{
	//set style
//	gROOT->Macro("/home/songkyo/kyo/2013/03_Jpsi/JpsiStyle.C");
	gROOT->Macro("/afs/cern.ch/user/k/kyolee/private/cms442/src/JpsiStyle.C"); //temporary

	//read the fit_table ASCII file
	std::ifstream inFilePbp("fit_table_Pbp_4rap2pt4cent",std::ios::in);
	std::ifstream inFilepp("fit_table_pp_4rap2pt4cent",std::ios::in);

	// define the arrays
//	string rapArr[] = {"-2.4--1.47", "-1.47--0.47","-0.47-0.53", "0.53-1.47"};
	string rapArr[] = {"-1.93--1.00", "-1.00-0.00","0.00-1.00", "1.00-1.93"};
//	string ptArr[] = {"0.0-6.5", "6.5-30.0"};
	string ptArr[] = {"6.5-10.0", "10.0-30.0"};
//	string centArr[] = {"70-100", "60-70", "50-60", "40-50", "30-40", "20-30", "10-20", "0-10"};
//	string centArr[] = {"50-100", "40-50", "30-40", "20-30", "10-20", "0-10"};
//	string centArr[] = {"70-100", "50-70", "30-50", "10-30", "0-10"};
	string centArr[] = {"50-100", "30-50", "10-30", "0-10"};

//	Double_t nCollArr[] = { 2.97, 5.57, 7.34, 8.89, 10.08, 11.15, 12.14, 13.66 }; //2.97? 3.03?
//	Double_t nCollArr[] = {4.366, 8.89, 10.08, 11.15, 12.14, 13.66 };
//	Double_t nCollArr[] = {2.97, 6.46, 9.485, 11.645, 13.66 };
	Double_t nCollArr[] = {4.366, 9.485, 11.645, 13.66 };

//	Double_t nCollErrArr[] = {0.165, 0.79, 1.02, 0.95, 0.74, 0.67, 0.84, 1.22};
//	Double_t nCollErrArr[] = {0.276, 0.95, 0.74, 0.67, 0.84, 1.22};
//	Double_t nCollErrArr[] = {0.165, 0.645, 0.602, 0.537, 1.22};
	Double_t nCollErrArr[] = {0.276, 0.602, 0.537, 1.22};

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

  //get raw yield & error from pA run (Inclusivs, prompt, non-prompt)
	Double_t nPbpSig[nRap][nPt][nCent], nPbpPr[nRap][nPt][nCent], nPbpNp[nRap][nPt][nCent];
	Double_t nPbpSigErr[nRap][nPt][nCent], nPbpPrErr[nRap][nPt][nCent], nPbpNpErr[nRap][nPt][nCent];
  //get raw yield & error from pp run (Inclusivs, prompt, non-prompt)
	Double_t nppSig[nRap][nPt], nppPr[nRap][nPt], nppNp[nRap][nPt];
	Double_t nppSigErr[nRap][nPt], nppPrErr[nRap][nPt], nppNpErr[nRap][nPt];
	//RpA raw
	Double_t rpaSig[nRap][nPt][nCent], rpaPr[nRap][nPt][nCent], rpaNp[nRap][nPt][nCent];
	Double_t rpaSigErr[nRap][nPt][nCent], rpaPrErr[nRap][nPt][nCent], rpaNpErr[nRap][nPt][nCent];
	//RpA normalized
	Double_t rpaNormSig[nRap][nPt][nCent], rpaNormPr[nRap][nPt][nCent], rpaNormNp[nRap][nPt][nCent];
	Double_t rpaNormSigErr[nRap][nPt][nCent], rpaNormPrErr[nRap][nPt][nCent], rpaNormNpErr[nRap][nPt][nCent];

// loop for Calculating Rpa 
for (Int_t k=0; k<nRap; k++) { 
	for (Int_t j=0; j<nPt; j++) {
		inFilepp >> nppSig[k][j] >> nppSigErr[k][j] >> nppPr[k][j] >> nppPrErr[k][j] >> nppNp[k][j] >> nppNpErr[k][j] ;
		for (Int_t i=0; i<nCent; i++) {
			//Read the data from file
			inFilePbp >> nPbpSig[k][j][i] >> nPbpSigErr[k][j][i] >> nPbpPr[k][j][i] >> nPbpPrErr[k][j][i] >> nPbpNp[k][j][i] >> nPbpNpErr[k][j][i] ;
//			cout << "rap : " << rapArr[k] << ", pT : " << ptArr[j] << " , cent : " << centArr[i] << endl;
//			cout << setw(10) << nPbpSig[k][j][i] << setw(10) << nPbpSigErr[k][j][i] << setw(10)<< nPbpPr[k][j][i] << setw(10) << nPbpPrErr[k][j][i] << setw(10) <<  nPbpNp[k][j][i] << setw(10) << nPbpNpErr[k][j][i] << endl;
//			cout << setw(10) << nppSig[k][j] << setw(10) << nppSigErr[k][j] << setw(10)<< nppPr[k][j] << setw(10) << nppPrErr[k][j] << setw(10) <<  nppNp[k][j] << setw(10) << nppNpErr[k][j] << endl;

			//Rcp raw yield
			rpaSig[k][j][i]= nPbpSig[k][j][i]/nppSig[k][j];
			rpaPr[k][j][i]= nPbpPr[k][j][i]/nppPr[k][j];
			rpaNp[k][j][i]= nPbpNp[k][j][i]/nppNp[k][j];
			//Rcp normalized by Ncoll
			rpaNormSig[k][j][i]= rpaSig[k][j][i]/nCollArr[i];
			rpaNormPr[k][j][i]= rpaPr[k][j][i]/nCollArr[i];
			rpaNormNp[k][j][i]= rpaNp[k][j][i]/nCollArr[i];

//			cout << "nColl = " << nCollArr[i] << endl;
//			cout << "rpaSig = " << rpaSig[k][j][i] << ", rpaPr = " << rpaPr[k][j][i] << ", rpaNp = "<< rpaNp[k][j][i] << endl;
//			cout << "rpaNormSig = " << rpaNormSig[k][j][i] << ", rpaNormPr = " << rpaNormPr[k][j][i] << ", rpaNormNp = "<< rpaNormNp[k][j][i] << endl;
//			cout << "          " << endl;

			// error propagation for rpaRaw
			rpaSigErr[k][j][i]=rpaSig[k][j][i]*TMath::Sqrt( TMath::Power(nPbpSigErr[k][j][i]/nPbpSig[k][j][i],2)+TMath::Power(nppSigErr[k][j]/nppSig[k][j],2) );
			rpaPrErr[k][j][i]=rpaPr[k][j][i]*TMath::Sqrt( TMath::Power(nPbpPrErr[k][j][i]/nPbpPr[k][j][i],2)+TMath::Power(nppPrErr[k][j]/nppPr[k][j],2) );
			rpaNpErr[k][j][i]=rpaNp[k][j][i]*TMath::Sqrt( TMath::Power(nPbpNpErr[k][j][i]/nPbpNp[k][j][i],2)+TMath::Power(nppNpErr[k][j]/nppNp[k][j],2) );

			// error propagation for RpaNorm
			rpaNormSigErr[k][j][i]=rpaNormSig[k][j][i]*TMath::Sqrt( TMath::Power(nCollErrArr[i]/nCollArr[i],2)+TMath::Power(rpaSigErr[k][j][i]/rpaSig[k][j][i],2) );
			rpaNormPrErr[k][j][i]=rpaNormPr[k][j][i]*TMath::Sqrt( TMath::Power(nCollErrArr[i]/nCollArr[i],2)+TMath::Power(rpaPrErr[k][j][i]/rpaPr[k][j][i],2) );
			rpaNormNpErr[k][j][i]=rpaNormNp[k][j][i]*TMath::Sqrt( TMath::Power(nCollErrArr[i]/nCollArr[i],2)+TMath::Power(rpaNpErr[k][j][i]/rpaNp[k][j][i],2) );

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
//	TLegend *leg = new TLegend(0.50, 0.75, 0.80, 0.90); //upper right
	TLegend *leg = new TLegend(0.50, 0.17, 0.80, 0.33); //bottom right
	SetLegendStyle(leg);

	//draw test box for beam, rapidity, pT info
//	TPaveText *text = new TPaveText(0.20, 0.48, 0.50, 0.64, "NDC");
//	TPaveText *text = new TPaveText(0.55, 0.55, 0.85, 0.70, "NDC");
///	TPaveText *text = new TPaveText(0.20, 0.75, 0.50, 0.90, "NDC"); //upper left
	TPaveText *text = new TPaveText(0.20, 0.17, 0.50, 0.33, "NDC"); //bottom left
	SetTextStyle(text);

	//draw the TGraphError
	TGraphErrors *rpa_inclusive[nRap][nPt];
	TGraphErrors *rpa_prompt[nRap][nPt];
	TGraphErrors *rpa_nonprompt[nRap][nPt];

	for (Int_t k=0; k<nRap; k++) {
		for (Int_t j=0; j<nPt; j++) {
			// Inclusive J/psi Graph
			rpa_inclusive[k][j] = new TGraphErrors(nCent, xaxis, rpaNormSig[k][j], 0, rpaNormSigErr[k][j]); //temp Err
			SetGraphStyle(rpa_inclusive[k][j], 0, 0);
			rpa_inclusive[k][j]->SetTitle("");
			rpa_inclusive[k][j]->GetXaxis()->SetTitle("centrality");
			rpa_inclusive[k][j]->GetYaxis()->SetTitle("R_{pA} (normalized by N_{coll})");
	  	rpa_inclusive[k][j]->SetMinimum(0.0);
//	 	 	rpa_inclusive[k][j]->SetMaximum(1.5);
			rpa_inclusive[k][j]->Draw("ALP");
			// prompt J/psi Graph
			rpa_prompt[k][j] = new TGraphErrors(nCent, xaxis, rpaNormPr[k][j], 0, rpaNormPrErr[k][j]); //temp Err
			SetGraphStyle(rpa_prompt[k][j], 1, 0);
			rpa_prompt[k][j]->Draw("LP");
			//non-prompt J/psi Graph
			rpa_nonprompt[k][j] = new TGraphErrors(nCent, xaxis, rpaNormNp[k][j], 0, rpaNormNpErr[k][j]); //temp Err
			SetGraphStyle(rpa_nonprompt[k][j], 2, 0);
			rpa_nonprompt[k][j]->Draw("LP");
			gr_ref->Draw("L");
			leg -> AddEntry(rpa_inclusive[k][j],"Inclusive J/#psi","lp");
			leg -> AddEntry(rpa_prompt[k][j],"Prompt J/#psi","lp");
			leg -> AddEntry(rpa_nonprompt[k][j],"Nonprompt J/#psi","lp");
			leg->Draw();
			text->AddText("Pbp (18.4/nb)");
//			text->AddText("pPb (12.6/nb)");
//			text->AddText("pp (5.41/pb)");
			text->AddText(Form("y_{cm} : %s",rapArr[k].c_str()));
			text->AddText(Form("p_{T} : %s GeV/c",ptArr[j].c_str()));
			text->Draw();
			for(Int_t i=0; i<nCent; i++) {
					char xLabel[531];
					sprintf(xLabel,"%s%%",centArr[i].c_str());
					rpa_inclusive[k][j]->GetXaxis()->Set(nCent,0,100);
					rpa_inclusive[k][j]->GetXaxis()->SetBinLabel(i+1,xLabel);
			}
			c1->Update();
			c1->SaveAs(Form("Rpa_norm_Pbp_4rap2pt4cent_%s_%s.pdf",rapArr[k].c_str(),ptArr[j].c_str()));
			leg->Clear();
			text->Clear();
			c1->Clear();
		}
	}
}

void SetGraphStyle(TGraph* gr, Int_t c, Int_t m) {
	Int_t colorArr[] = { kGray+3, kRed-4, kBlue, kViolet-4, kAzure+8, kBlack };
	Int_t markerFullArr[] = {kFullCircle, kFullTriangleUp, kFullTriangleDown, kFullSquare};
//	Int_t markerFullArr[] = {kFullCircle, kFullTriangleUp, kFullTriangleDown, kFullSquare, kFullStar, kFullDiamond};
//	Int_t markerOpenArr[] = {kOpenCircle, kOpenTriangleUp, kOpenTriangleDown, kOpenSquare, kOpenStar, kOpenDiamond};

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
