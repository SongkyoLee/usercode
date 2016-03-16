//////////////////////////////////////////////////////////////////////////
//
// 'BASIC FUNCTIONALITY' RooFit tutorial macro #101
// 
// Fitting, plotting, toy data generation on one-dimensional p.d.f
//
// pdf = gauss(x,m,s) 
//
//
// 07/2008 - Wouter Verkerke 
// 
/////////////////////////////////////////////////////////////////////////

#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"

#include "TFile.h"
#include "TTree.h"

using namespace RooFit ;


void test01()
{
  // S e t u p   m o d e l 
  // ---------------------

	TFile *openFile = new TFile("/tmp/kyolee/dimuonTree_upsiMiniTree_pA5tev_14nb_Run210498-210909_trigBit1_allTriggers0_pt4.root");
	TTree* tree = (TTree*)openFile->Get("UpsilonTree");	

  // Declare variables with associated name, title, initial value and allowed range
  RooRealVar mass("invariantMass","M_{#mu#mu} [GeV/c]",9.4,7,14) ;
  RooRealVar muPlusPt("muPlusPt","muPlusPt",0,40) ;
  RooRealVar muMinusPt("muMinusPt","muMinusPt",0,40) ;
  RooRealVar mean("mean","mean of gaussian",9.4,8,11) ;
  RooRealVar sigma("sigma","width of gaussian",1,0.1,10) ;

	RooDataSet* data = new RooDataSet("data", "data", RooArgSet(mass,muPlusPt,muMinusPt), Import(*tree), Cut("muPlusPt>4 && muMinusPt>4"));

 	data->Print();

  // Build gaussian p.d.f in terms of x,mean and sigma
  RooGaussian gauss("gauss","gaussian PDF",mass,mean,sigma) ;  

  // Construct plot frame in 'x'
  RooPlot* xframe = mass.frame(Title("Gaussian p.d.f.")) ;

	data->plotOn(xframe);

	/*
  // P l o t   m o d e l   a n d   c h a n g e   p a r a m e t e r   v a l u e s
  // ---------------------------------------------------------------------------

  // Plot gauss in frame (i.e. in x) 
  gauss.plotOn(xframe) ;

  // Change the value of sigma to 3
  sigma.setVal(3) ;

  // Plot gauss in frame (i.e. in x) and draw frame on canvas
  gauss.plotOn(xframe,LineColor(kRed)) ;
*/  

  // F i t   m o d e l   t o   d a t a
  // -----------------------------

  // Fit pdf to data
  gauss.fitTo(*data,Range(9,10)) ;
  gauss.plotOn(xframe) ;

  // Print values of mean and sigma (that now reflect fitted values and errors)
  mean.Print() ;
  sigma.Print() ;


  // Draw all frames on a canvas
  TCanvas* c = new TCanvas("rf101_basics","rf101_basics",800,400) ;
  c->cd(1) ; gPad->SetLeftMargin(0.15) ; xframe->GetYaxis()->SetTitleOffset(1.6) ; xframe->Draw() ;
 
}
