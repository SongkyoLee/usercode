
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

void draw_RfbAccep_ptDep()
{
	//set style
	gROOT->Macro("/afs/cern.ch/work/k/kyolee/private/cms442/src/JpsiStyle.C");

	//read the fit_table ASCII file
	std::ifstream inFilePbp("fit_table_Pbp_ptDep",std::ios::in);
	std::ifstream inFilepPb("fit_table_pPb_ptDep",std::ios::in);
	std::ifstream inFileAcc("acceptance_ptDep",std::ios::in);

	//define the arrays
	// --- rap
	cout<<"NOTICE:: Rap direction and bins should be tuned by [ReadContents.cpp] already! (FW to BW)"<<endl;
	string rapArr[] = {"-1.93-0.00", "0.00-1.93"}; // FwBw - CM
//	string rapArr[] = {"-1.93--1.75", "-1.75--1.50", "-1.50--1.25", "-1.25--1.00", "-1.00--0.75", "-0.75--0.50", "-0.50--0.25", "-0.25-0.00", "0.00-0.25", "0.25-0.05", "0.05-0.75", "0.75-1.00", "1.00-1.25", "1.25-1.50", "1.50-1.75", "1.75-1.93"}; // rapfiner2 - CM

	// --- pt
//	string ptArr[] = {"6.5-30.0"};
//	string ptArr[]={"6.5-7.5", "7.5-8.5", "8.5-9.5", "9.5-10.5", "10.5-11.5", "11.5-12.5", "12.5-14.5", "14.5-16.5", "16.5-20.0", "20.0-30.0"};// ptfiner
	string ptArr[]={"6.5-8.0", "8.0-10.0", "10.0-13.0", "13.0-30.0"}; //ptcoarser2

	// ---cent
//	string centArr[] = {"70-100", "60-70", "50-60", "40-50", "30-40", "20-30", "10-20", "0-10"};
	string centArr[] = {"0.0-100.0"};

	const Int_t nRap = sizeof(rapArr)/sizeof(string);
	const Int_t nPt = sizeof(ptArr)/sizeof(string);
	const Int_t nCent = sizeof(centArr)/sizeof(string);
	cout << "nRap = " << nRap << endl;
	cout << "nPt = " << nPt << endl;
	cout << "nCent = " << nCent << endl;


	//Set x-axis for pt : should modify by hand (carefully)!!
	Double_t xaxis[nPt];
	xaxis[0]= (6.5+8.0)/2;
	xaxis[1]= (8.0+10.0)/2;
	xaxis[2]= (10.+13.0)/2;
	xaxis[3]= (13.0+30.0)/2;
	for (Int_t i=0; i<nPt; i++) {
		cout << "xaxis["<<i<<"] = "<< xaxis[i] <<endl;
	}

	const Int_t nRapHalf = nRap/2;
	// define arrays
	// get raw yield & error : Pbp run (Inclusive, prompt, non-prompt)
	Double_t nPbpSig[nCent][nRap][nPt], nPbpPr[nCent][nRap][nPt], nPbpNp[nCent][nRap][nPt];
	Double_t nPbpSigErr[nCent][nRap][nPt], nPbpPrErr[nCent][nRap][nPt], nPbpNpErr[nCent][nRap][nPt];
	// get raw yield & error : pPb run
	Double_t npPbSig[nCent][nRap][nPt], npPbPr[nCent][nRap][nPt], npPbNp[nCent][nRap][nPt];
	Double_t npPbSigErr[nCent][nRap][nPt], npPbPrErr[nCent][nRap][nPt], npPbNpErr[nCent][nRap][nPt];
	// get raw yield $ error : Pbp+pPb
	Double_t nSig[nCent][nRap][nPt], nPr[nCent][nRap][nPt], nNp[nCent][nRap][nPt];
	Double_t nSigErr[nCent][nRap][nPt], nPrErr[nCent][nRap][nPt], nNpErr[nCent][nRap][nPt];
  // get acceptance
  Double_t nAcc[nCent][nRap][nPt];
	Double_t nAccErr[nCent][nRap][nPt];
	// corrected yield 1 = raw yield / Acceptance
	Double_t nSigCorr1[nCent][nRap][nPt], nPrCorr1[nCent][nRap][nPt], nNpCorr1[nCent][nRap][nPt];
	Double_t nSigCorr1Err[nCent][nRap][nPt], nPrCorr1Err[nCent][nRap][nPt], nNpCorr1Err[nCent][nRap][nPt];
	// Rfb
	// (NOTICE : numOfarray not 'nRap' but 'nXaxis')
	Double_t rfbSig[nCent][nRapHalf][nPt], rfbPr[nCent][nRapHalf][nPt], rfbNp[nCent][nRapHalf][nPt];
	Double_t rfbSigErr[nCent][nRapHalf][nPt], rfbPrErr[nCent][nRapHalf][nPt], rfbNpErr[nCent][nRapHalf][nPt];

// arrange data
for (Int_t ic=0; ic<nCent; ic++) {
	for (Int_t ir=0; ir<nRap; ir++) {
		for (Int_t ip=0; ip<nPt; ip++) { 
			// read-in the dat
			inFilePbp >> nPbpSig[ic][ir][ip] >> nPbpSigErr[ic][ir][ip] >> nPbpPr[ic][ir][ip] >> nPbpPrErr[ic][ir][ip] >> nPbpNp[ic][ir][ip] >> nPbpNpErr[ic][ir][ip] ;
			inFilepPb >> npPbSig[ic][ir][ip] >> npPbSigErr[ic][ir][ip] >> npPbPr[ic][ir][ip] >> npPbPrErr[ic][ir][ip] >> npPbNp[ic][ir][ip] >> npPbNpErr[ic][ir][ip] ;
			inFileAcc >> nAcc[ic][ir][ip] >> nAccErr[ic][ir][ip];
			// merge Pbp & pPb data
			nSig[ic][ir][ip] = nPbpSig[ic][ir][ip]+ npPbSig[ic][ir][ip];
			nSigErr[ic][ir][ip] = nPbpSigErr[ic][ir][ip]+ npPbSigErr[ic][ir][ip];
			nPr[ic][ir][ip] = nPbpPr[ic][ir][ip]+ npPbPr[ic][ir][ip];
			nPrErr[ic][ir][ip] = nPbpPrErr[ic][ir][ip]+ npPbPrErr[ic][ir][ip];
			nNp[ic][ir][ip] = nPbpNp[ic][ir][ip]+ npPbNp[ic][ir][ip];
			nNpErr[ic][ir][ip] = nPbpNpErr[ic][ir][ip]+ npPbNpErr[ic][ir][ip];
			cout << "ic : " << ic << ", ir : " << ir << " , ip : " << ip << endl;
			cout <<"cent : "<<centArr[ic]<<" , rap : "<<rapArr[ir]<<", pT : "<<ptArr[ip] << endl;
//			cout << " Pbp Raw=" <<setw(10) << nPbpSig[ic][ir][ip] << setw(10) << nPbpSigErr[ic][ir][ip] << setw(10)<< nPbpPr[ic][ir][ip] << setw(10) << nPbpPrErr[ic][ir][ip] << setw(10) <<  nPbpNp[ic][ir][ip] << setw(10) << nPbpNpErr[ic][ir][ip] << endl;
//			cout << " pPb Raw="<<setw(10) << npPbSig[ic][ir][ip] << setw(10) << npPbSigErr[ic][ir][ip] << setw(10)<< npPbPr[ic][ir][ip] << setw(10) << npPbPrErr[ic][ir][ip] << setw(10) << npPbNp[ic][ir][ip] << setw(10) << npPbNpErr[ic][ir][ip] << endl;
			cout << " Total Raw="<<setw(10) << nSig[ic][ir][ip] << setw(10) << nSigErr[ic][ir][ip] << setw(10)<< nPr[ic][ir][ip] << setw(10) << nPrErr[ic][ir][ip] << setw(10) <<  nNp[ic][ir][ip] << setw(10) << nNpErr[ic][ir][ip] << setw(10) << nAcc[ic][ir][ip] << setw(10) << nAccErr[ic][ir][ip] << endl;
			// yield correction 1
			nSigCorr1[ic][ir][ip] = nSig[ic][ir][ip]/nAcc[ic][ir][ip];
			nPrCorr1[ic][ir][ip] = nPr[ic][ir][ip]/nAcc[ic][ir][ip];
			nNpCorr1[ic][ir][ip] = nNp[ic][ir][ip]/nAcc[ic][ir][ip];
			nSigCorr1Err[ic][ir][ip]= nSigCorr1[ic][ir][ip]*TMath::Sqrt( TMath::Power(nSigErr[ic][ir][ip]/nSig[ic][ir][ip],2)+TMath::Power(nAccErr[ic][ir][ip]/nAcc[ic][ir][ip],2) );
			nPrCorr1Err[ic][ir][ip]= nPrCorr1[ic][ir][ip]*TMath::Sqrt( TMath::Power(nPrErr[ic][ir][ip]/nPr[ic][ir][ip],2)+TMath::Power(nAccErr[ic][ir][ip]/nAcc[ic][ir][ip],2) );
			nNpCorr1Err[ic][ir][ip]= nNpCorr1[ic][ir][ip]*TMath::Sqrt( TMath::Power(nNpErr[ic][ir][ip]/nNp[ic][ir][ip],2)+TMath::Power(nAccErr[ic][ir][ip]/nAcc[ic][ir][ip],2) );
			cout << " N_{J/#psi}/A = " <<setw(10) << nSigCorr1[ic][ir][ip] << setw(10) << nSigCorr1Err[ic][ir][ip]     << setw(10)<< nPrCorr1[ic][ir][ip] << setw(10) << nPrCorr1Err[ic][ir][ip] << setw(10) << nNpCorr1[ic][ir][ip] << setw(10) << nNpCorr1Err[ic][ir][ip] << setw(10) << endl;
		}
	}
}
			
// calculate Fw/Bw = Rfb
for (Int_t ic=0; ic<nCent; ic++) {
	for (Int_t ir=0; ir<nRapHalf; ir++) {
		for (Int_t ip=0; ip<nPt; ip++) { 
			rfbSig[ic][ir][ip] = nSigCorr1[ic][ir][ip]/nSigCorr1[ic][ir+1][ip]; // Fw/Bw
			rfbPr[ic][ir][ip] = nPrCorr1[ic][ir][ip]/nPrCorr1[ic][ir+1][ip];
			rfbNp[ic][ir][ip] = nNpCorr1[ic][ir][ip]/nNpCorr1[ic][ir+1][ip];
			rfbSigErr[ic][ir][ip]= rfbSig[ic][ir][ip]*TMath::Sqrt( TMath::Power(nSigCorr1Err[ic][ir][ip]/nSigCorr1[ic][ir][ip],2)+TMath::Power(nSigCorr1Err[ic][ir+1][ip]/nSigCorr1[ic][ir+1][ip],2) );
			rfbPrErr[ic][ir][ip]= rfbPr[ic][ir][ip]*TMath::Sqrt( TMath::Power(nPrCorr1Err[ic][ir][ip]/nPrCorr1[ic][ir][ip],2)+TMath::Power(nPrCorr1Err[ic][ir+1][ip]/nPrCorr1[ic][ir+1][ip],2) );
			rfbNpErr[ic][ir][ip]= rfbNp[ic][ir][ip]*TMath::Sqrt( TMath::Power(nNpCorr1Err[ic][ir][ip]/nNpCorr1[ic][ir][ip],2)+TMath::Power(nNpCorr1Err[ic][ir+1][ip]/nNpCorr1[ic][ir+1][ip],2) );
//			cout << ir << "th rapbin " << endl;
			cout << ip << "th ptbin = " << ptArr[ip]<<endl;
			cout << "Rfb="<< setw(10) << rfbSig[ic][ir][ip] << setw(10) << rfbSigErr[ic][ir][ip] << setw(10)<< rfbPr[ic][ir][ip] << setw(10) << rfbPrErr[ic][ir][ip] << setw(10) <<  rfbNp[ic][ir][ip] << setw(10) << rfbNpErr[ic][ir][ip] << endl;
			cout << " " << endl;
		}
	}
} // end of calcultation

	TCanvas *c1 = new TCanvas("c1","", 200, 10, 600, 600);

	//draw the reference graph y=1
//	TGraph* gUnityLine = referenceLine(nPt, xaxis[0], xaxis[nPt-1]);
	TGraph* gUnityLine = referenceLine(nPt, 0, 30);

	//draw the Legend
//	TLegend *leg = new TLegend(0.55, 0.74, 0.80, 0.90); //upper right
//	TLegend *leg = new TLegend(0.20, 0.70, 0.50, 0.90); //upper left
//	TLegend *leg = new TLegend(0.20, 0.15, 0.48, 0.35); //bottom left
//	TLegend *leg = new TLegend(0.53, 0.38, 0.85, 0.57); //middle right
	TLegend *leg = new TLegend(0.20, 0.15, 0.48, 0.33); //bottom left
	SetLegendStyle(leg);

	//draw test box for beam, rapidity, pT info
//	TPaveText *text = new TPaveText(0.20, 0.48, 0.50, 0.64, "NDC"); //upper left
//	TPaveText *text = new TPaveText(0.55, 0.15, 0.85, 0.35, "NDC"); // bottom right
//	TPaveText *text = new TPaveText(0.55, 0.52, 0.85, 0.70, "NDC"); //middle right
	TPaveText *text = new TPaveText(0.55, 0.15, 0.85, 0.33, "NDC"); // bottom right
	SetTextStyle(text);

	//draw the TGraphError (Rfb)
	TGraphErrors *rfb_inclusive[nCent][nRapHalf];
	TGraphErrors *rfb_prompt[nCent][nRapHalf];
	TGraphErrors *rfb_nonprompt[nCent][nRapHalf];

	for (Int_t ic=0; ic<nCent; ic++) {
		for (Int_t ir=0; ir<nRapHalf; ir++) {
			rfb_inclusive[ic][ir] = new TGraphErrors(nPt, xaxis, rfbSig[ic][ir], 0, rfbSigErr[ic][ir]);
			SetGraphStyle(rfb_inclusive[ic][ir], 7, 0);
			rfb_inclusive[ic][ir]->SetTitle("");
			rfb_inclusive[ic][ir]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
			rfb_inclusive[ic][ir]->GetXaxis()->CenterTitle();
			rfb_inclusive[ic][ir]->GetYaxis()->SetTitle("R_{FB} (A corr)");
			rfb_inclusive[ic][ir]->GetXaxis()->SetRangeUser(0., 30.);
  		rfb_inclusive[ic][ir]->SetMinimum(0.0);
	  	rfb_inclusive[ic][ir]->SetMaximum(1.2);
			rfb_inclusive[ic][ir]->Draw("ALP");
			rfb_prompt[ic][ir] = new TGraphErrors(nPt, xaxis, rfbPr[ic][ir], 0, rfbPrErr[ic][ir]);
			SetGraphStyle(rfb_prompt[ic][ir], 0, 0);
			rfb_prompt[ic][ir]->Draw("LP");
			rfb_nonprompt[ic][ir] = new TGraphErrors(nPt, xaxis, rfbNp[ic][ir], 0, rfbNpErr[ic][ir]);
			SetGraphStyle(rfb_nonprompt[ic][ir], 1, 0);
			rfb_nonprompt[ic][ir]->Draw("LP");
			gUnityLine->Draw("L same");
			leg -> AddEntry(rfb_inclusive[ic][ir],"Inclusive J/#psi","lp");
			leg -> AddEntry(rfb_prompt[ic][ir],"Prompt J/#psi","lp");
			leg -> AddEntry(rfb_nonprompt[ic][ir],"Nonprompt J/#psi","lp");
			leg->Draw();
			text->AddText("pA (30/nb)");
//			text->AddText("Pbp (18/nb)");
//			text->AddText("pPb (12/nb)");
//			text->AddText("pp (5.41/pb)");
//			text->AddText(Form("y_{cm} : %s",rapArr[ic].c_str()));
			text->AddText(Form("Cent : %s %% ",centArr[ic].c_str()));
//			text->AddText(Form("p_{T} : %s GeV/c",ptArr[ir].c_str()));
			text->AddText("0<|y_{cm}|<1.93 ");
			text->Draw();
			c1->Update();
//			c1->SaveAs(Form("Rfb_yDep_finer_%s_%s.pdf",centArr[ic].c_str(),ptArr[ip].c_str()));
			c1->SaveAs(Form("RfbAccep_ptDep_finer_%s.pdf",centArr[ic].c_str()));
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
	x[n]=xMin+1.9*n*((xMax-xMin)/nBins);
	//x[n]=xMin+n*((xMax-xMin)/nBins);
	y[n]=1;
	}
	TGraph* gr_ref = new TGraph(nBins, x+1, y);
	gr_ref->SetLineColor(kRed);
	gr_ref->SetLineWidth(1.2);
	return gr_ref;
}

void SetGraphStyle(TGraph* gr, Int_t c, Int_t m) {
	Int_t colorArr[] = { kGray+3, kRed-4, kBlue, kOrange+7, kGreen+3, kViolet-4, kAzure+8, kGreen+1, kBlack };
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
