#include "./KrisztiansHiForest/hiForest.h"
#include "./KrisztiansHiForest/utilities.h"
#include <TROOT.h>
#include <TStyle.h>
#include <TFile.h>
#include <TH1D.h>
#include <TNtuple.h>
#include <iostream>
#include <TLegend.h>
#include <TLatex.h>

void normalizeByBinWidth(TH1D *histo);
//------------------------

void minBiasTracks_EtaAsymQuality_Final_15vz_makeroot()
{
// ---- 1D ----
// PtErr/Pt
// dxy/dxyErr
// dz/dzErr
// abs(dz/dzErr)
// abs(dxy/dxyErr)
// dxy
// dxyErr
// dz
// dzErr
// abs(eta) : for _plusEta and _minusEta, not for _all 
// phi

	gROOT->Reset();
	gROOT->ProcessLine(".x rootlogonChristof.C");
	gROOT->ForceStyle();
	gStyle->SetPalette(1);
	gStyle->SetTitleYOffset(1.30);
	gStyle->SetPadRightMargin(0.16);

	TFile * f_output = new TFile("minBiasTracks_EtaAsymQuality_Final_15vz.root","recreate");

	// --- Define the input file and HiForest
	// 1. Data (@eos)
//	char *infName_FullTrackTrigger_Track20 = "root://eoscms//eos/cms/store/group/phys_heavyions/icali/MinBias_Merged.root";
	char *infName_FullTrackTrigger_Track20 = "root://eoscms//eos/cms/store/user/miheejo/TREE/2011PbPb/HiForest/pbpbMB_v3_part.root";
	// 2. MC (@knu)
//	char *infName_FullTrackTrigger_Track20 = "/u/user/kyolee/public/HydjetDrum03_HiForest_v05_merged_test02.root";

	HiForest *c_FullTrackTrigger_Track20 = new HiForest(infName_FullTrackTrigger_Track20,"",cPbPb);

	// --- Binning!
	const Double_t small = 1e-3;

	// binning for PtErr/Pt (relPt)
	std::vector<Double_t> relPtBins;
	Double_t relPt;
	for(relPt=0.0; relPt<0.2-small; relPt+=0.025) { relPtBins.push_back(relPt); }
	for(relPt=0.2; relPt<0.4-small; relPt+=0.04) { relPtBins.push_back(relPt); }
	for(relPt=0.4; relPt<1.0-small; relPt+=0.1) { relPtBins.push_back(relPt); }
	relPtBins.push_back(1.0);
	std::cerr<<" relPtBins.size()-1: " << relPtBins.size()-1 << std::endl;

	// binnig for dxy/dxyError (relDxy)
	std::vector<Double_t> relDxyBins;
	Double_t relDxy;
	for(relDxy=-8.; relDxy<-4.-small; relDxy+=1.) {relDxyBins.push_back(relDxy);}
	for(relDxy=-4.; relDxy<-2.-small; relDxy+=0.5) {relDxyBins.push_back(relDxy);}
	for(relDxy=-2.; relDxy<-0.5-small; relDxy+=0.25) {relDxyBins.push_back(relDxy);}
	for(relDxy=-0.5; relDxy<0.5-small; relDxy+=0.1) {relDxyBins.push_back(relDxy);}
	for(relDxy=0.5; relDxy<2.-small; relDxy+=0.25) {relDxyBins.push_back(relDxy);}
	for(relDxy=2.; relDxy<4.-small; relDxy+=0.5) {relDxyBins.push_back(relDxy);}
	for(relDxy=4.; relDxy<8.-small; relDxy+=1.) {relDxyBins.push_back(relDxy);}
	relDxyBins.push_back(8.);
	std::cerr<<" relDxyBins.size()-1: " << relDxyBins.size()-1 << std::endl;

	// binnig for dz/dzError (relDz)
	std::vector<Double_t> relDzBins;
	Double_t relDz;
	for(relDz=-17.; relDz<17.-small; relDz+=0.5) {relDzBins.push_back(relDz);}
	relDzBins.push_back(17.);
	std::cerr<<" relDzBins.size()-1: " << relDzBins.size()-1 << std::endl;

	// binnig for abs(dxy/dxyError) (absRelDxy)
	std::vector<Double_t> absRelDxyBins;
	Double_t absRelDxy;
	for(absRelDxy=0.0; absRelDxy<0.5-small; absRelDxy+=0.1) {absRelDxyBins.push_back(absRelDxy);}
	for(absRelDxy=0.5; absRelDxy<2.-small; absRelDxy+=0.25) {absRelDxyBins.push_back(absRelDxy);}
	for(absRelDxy=2.; absRelDxy<4.-small; absRelDxy+=0.5) {absRelDxyBins.push_back(absRelDxy);}
	for(absRelDxy=4.; absRelDxy<8.-small; absRelDxy+=1.) {absRelDxyBins.push_back(absRelDxy);}
	absRelDxyBins.push_back(8.);
	std::cerr<<" absRelDxyBins.size()-1: " << absRelDxyBins.size()-1 << std::endl;

	//binning for abs(dz/dzErr) (absRelDz)
	std::vector<Double_t> absRelDzBins;
	Double_t absRelDz;
	for(absRelDz=-0.; absRelDz<17.-small; absRelDz+=0.5) {absRelDzBins.push_back(absRelDz);}
	absRelDzBins.push_back(17.);
	std::cerr<<" absRelDzBins.size()-1: " << absRelDzBins.size()-1 << std::endl;

// binning for dxy
	std::vector<Double_t> dxyBins;
	Double_t dxy;
	for(dxy=-0.35; dxy<-0.15-small; dxy+=0.20) {dxyBins.push_back(dxy);}
	for(dxy=-0.15; dxy<-0.1-small; dxy+=0.05) {dxyBins.push_back(dxy);}
	for(dxy=-0.1; dxy<0.1-small; dxy+=0.020) {dxyBins.push_back(dxy);} //0.025
	for(dxy=0.1; dxy<0.15-small; dxy+=0.05) {dxyBins.push_back(dxy);}
	for(dxy=0.15; dxy<0.35-small; dxy+=0.20) {dxyBins.push_back(dxy);}
	dxyBins.push_back(0.35);
	std::cerr<<" dxyBins.size()-1: " << dxyBins.size()-1 << std::endl;

	// binning for dz
	std::vector<Double_t> dzBins;
	Double_t dz;
	for(dz=-2.0; dz<-1.0-small; dz+=1.0) {dzBins.push_back(dz);}
	for(dz=-1.0; dz<-0.5-small; dz+=0.25) {dzBins.push_back(dz);}
	for(dz=-0.5; dz<0.5-small; dz+=0.05) {dzBins.push_back(dz);} //0.1
	for(dz=0.5; dz<1.0-small; dz+=0.25) {dzBins.push_back(dz);}
	for(dz=1.0; dz<2.0-small; dz+=1.0) {dzBins.push_back(dz);}
	dzBins.push_back(2.0);
	std::cerr<<" dzBins.size()-1: " << dzBins.size()-1 << std::endl;

	// binning for dxyErr
	std::vector<Double_t> dxyErrBins;
	Double_t dxyErr;
	for(dxyErr=0.0; dxyErr<0.1-small; dxyErr+=0.002) {dxyErrBins.push_back(dxyErr);} //0.001
	for(dxyErr=0.1; dxyErr<0.15-small; dxyErr+=0.01) {dxyErrBins.push_back(dxyErr);}
	for(dxyErr=0.5; dxyErr<0.175-small; dxyErr+=0.025) {dxyErrBins.push_back(dxyErr);}
	dxyErrBins.push_back(0.175);
	std::cerr<<" dxyErrBins.size()-1: " << dxyErrBins.size()-1 << std::endl;

	// binning for dzErr
	std::vector<Double_t> dzErrBins;
	Double_t dzErr;
	for(dzErr=0.0; dzErr<0.3-small; dzErr+=0.01) {dzErrBins.push_back(dzErr);}
	for(dzErr=0.3; dzErr<0.45-small; dzErr+=0.05) {dzErrBins.push_back(dzErr);}
	for(dzErr=0.45; dzErr<0.6-small; dzErr+=0.15) {dzErrBins.push_back(dzErr);}
	dzErrBins.push_back(0.6);
	std::cerr<<" dzErrBins.size()-1: " << dzErrBins.size()-1 << std::endl;

	//binning for eta
	std::vector<Double_t> etaBins;
	Double_t eta;
	for(eta=-2.4; eta<2.4-small; eta+=0.2) {etaBins.push_back(eta);}
	etaBins.push_back(2.4);
	std::cerr<<" etaBins.size()-1: " << etaBins.size()-1 << std::endl;

	//binning for absEta
	std::vector<Double_t> absEtaBins;
	Double_t absEta;
	for(absEta=0.0; absEta<2.4-small; absEta+=0.2) {absEtaBins.push_back(absEta);}
	absEtaBins.push_back(2.4);
	std::cerr<<" absEtaBins.size()-1: " << absEtaBins.size()-1 << std::endl;

	//binning for phi
	std::vector<Double_t> phiBins;
	Double_t phi;
	for(phi=-3.2; phi<3.2-small; phi+=0.2) {phiBins.push_back(phi);}
	phiBins.push_back(3.2);
	std::cerr<<" phiBins.size()-1: " << phiBins.size()-1 << std::endl;

	// binning for pt
	std::vector<Double_t> ptBins;
	Double_t pt;
	for(pt = 0.0; pt < 4.0-small; pt += 0.4 ) { ptBins.push_back(pt); std::cerr<<" pt: " << pt << std::endl; }
	for(pt = 4.0; pt < 8.0-small; pt += 0.8 ) { ptBins.push_back(pt); std::cerr<<" pt: " << pt << std::endl; }
	for(pt = 8.0; pt < 14.0-small; pt += 1.2 ) { ptBins.push_back(pt); std::cerr<<" pt: " << pt << std::endl; }
	for(pt = 14.0; pt < 22.0-small; pt += 1.6 ) { ptBins.push_back(pt); std::cerr<<" pt: " << pt << std::endl; }
	for(pt = 22.0; pt < 30.0-small; pt += 2.0 ) { ptBins.push_back(pt); std::cerr<<" pt: " << pt << std::endl; }
	ptBins.push_back(30.0);
	std::cerr<<" ptBins.size()-1: " << ptBins.size()-1 << std::endl;


	TTree * t = new TTree("t","whatever");

	//For All eta range
	TH1D * relPt_FullTrack_all = new TH1D("relPt_FullTrack_all","relPt_FullTrack_all",relPtBins.size()-1,&relPtBins[0]);
	TH1D * relDxy_FullTrack_all = new TH1D("relDxy_FullTrack_all","relDxy_FullTrack_all",relDxyBins.size()-1,&relDxyBins[0]);
	TH1D * relDz_FullTrack_all = new TH1D("relDz_FullTrack_all","relDz_FullTrack_all",relDzBins.size()-1,&relDzBins[0]);
	TH1D * absRelDxy_FullTrack_all = new TH1D("absRelDxy_FullTrack_all","absRelDxy_FullTrack_all",absRelDxyBins.size()-1,&absRelDxyBins[0]);
	TH1D * absRelDz_FullTrack_all = new TH1D("absRelDz_FullTrack_all","absRelDz_FullTrack_all",absRelDzBins.size()-1,&absRelDzBins[0]);
	TH1D * dxy_FullTrack_all = new TH1D("dxy_FullTrack_all","dxy_FullTrack_all",dxyBins.size()-1,&dxyBins[0]);
	TH1D * dz_FullTrack_all = new TH1D("dz_FullTrack_all","dz_FullTrack_all",dzBins.size()-1,&dzBins[0]);
	TH1D * dxyErr_FullTrack_all = new TH1D("dxyErr_FullTrack_all","dxyErr_FullTrack_all",dxyErrBins.size()-1,&dxyErrBins[0]);
	TH1D * dzErr_FullTrack_all = new TH1D("dzErr_FullTrack_all","dzErr_FullTrack_all",dzErrBins.size()-1,&dzErrBins[0]);
	TH1D * absEta_FullTrack_all = new TH1D("absEta_FullTrack_all","absEta_FullTrack_all",etaBins.size()-1,&etaBins[0]); //not absolute!! etaBins instead of absEtaBins
	TH1D * phi_FullTrack_all = new TH1D("phi_FullTrack_all","phi_FullTrack_all",phiBins.size()-1,&phiBins[0]);

	//For plus eta range
	TH1D * relPt_FullTrack_plusEta = new TH1D("relPt_FullTrack_plusEta","relPt_FullTrack_plusEta",relPtBins.size()-1,&relPtBins[0]);
	TH1D * relDxy_FullTrack_plusEta = new TH1D("relDxy_FullTrack_plusEta","relDxy_FullTrack_plusEta",relDxyBins.size()-1,&relDxyBins[0]);
	TH1D * relDz_FullTrack_plusEta = new TH1D("relDz_FullTrack_plusEta","relDz_FullTrack_plusEta",relDzBins.size()-1,&relDzBins[0]);
	TH1D * absRelDxy_FullTrack_plusEta = new TH1D("absRelDxy_FullTrack_plusEta","absRelDxy_FullTrack_plusEta",absRelDxyBins.size()-1,&absRelDxyBins[0]);
	TH1D * absRelDz_FullTrack_plusEta = new TH1D("absRelDz_FullTrack_plusEta","absRelDz_FullTrack_plusEta",absRelDzBins.size()-1,&absRelDzBins[0]);
	TH1D * dxy_FullTrack_plusEta = new TH1D("dxy_FullTrack_plusEta","dxy_FullTrack_plusEta",dxyBins.size()-1,&dxyBins[0]);
	TH1D * dz_FullTrack_plusEta = new TH1D("dz_FullTrack_plusEta","dz_FullTrack_plusEta",dzBins.size()-1,&dzBins[0]);
	TH1D * dxyErr_FullTrack_plusEta = new TH1D("dxyErr_FullTrack_plusEta","dxyErr_FullTrack_plusEta",dxyErrBins.size()-1,&dxyErrBins[0]);
	TH1D * dzErr_FullTrack_plusEta = new TH1D("dzErr_FullTrack_plusEta","dzErr_FullTrack_plusEta",dzErrBins.size()-1,&dzErrBins[0]);
	TH1D * absEta_FullTrack_plusEta = new TH1D("absEta_FullTrack_plusEta","absEta_FullTrack_plusEta",absEtaBins.size()-1,&absEtaBins[0]);
	TH1D * phi_FullTrack_plusEta = new TH1D("phi_FullTrack_plusEta","phi_FullTrack_plusEta",phiBins.size()-1,&phiBins[0]);

	//For minus eta range
	TH1D * relPt_FullTrack_minusEta = new TH1D("relPt_FullTrack_minusEta","relPt_FullTrack_minusEta",relPtBins.size()-1,&relPtBins[0]);
	TH1D * relDxy_FullTrack_minusEta = new TH1D("relDxy_FullTrack_minusEta","relDxy_FullTrack_minusEta",relDxyBins.size()-1,&relDxyBins[0]);
	TH1D * relDz_FullTrack_minusEta = new TH1D("relDz_FullTrack_minusEta","relDz_FullTrack_minusEta",relDzBins.size()-1,&relDzBins[0]);
	TH1D * absRelDxy_FullTrack_minusEta = new TH1D("absRelDxy_FullTrack_minusEta","absRelDxy_FullTrack_minusEta",absRelDxyBins.size()-1,&absRelDxyBins[0]);
	TH1D * absRelDz_FullTrack_minusEta = new TH1D("absRelDz_FullTrack_minusEta","absRelDz_FullTrack_minusEta",absRelDzBins.size()-1,&absRelDzBins[0]);
	TH1D * dxy_FullTrack_minusEta = new TH1D("dxy_FullTrack_minusEta","dxy_FullTrack_minusEta",dxyBins.size()-1,&dxyBins[0]);
	TH1D * dz_FullTrack_minusEta = new TH1D("dz_FullTrack_minusEta","dz_FullTrack_minusEta",dzBins.size()-1,&dzBins[0]);
	TH1D * dxyErr_FullTrack_minusEta = new TH1D("dxyErr_FullTrack_minusEta","dxyErr_FullTrack_minusEta",dxyErrBins.size()-1,&dxyErrBins[0]);
	TH1D * dzErr_FullTrack_minusEta = new TH1D("dzErr_FullTrack_minusEta","dzErr_FullTrack_minusEta",dzErrBins.size()-1,&dzErrBins[0]);
	TH1D * absEta_FullTrack_minusEta = new TH1D("absEta_FullTrack_minusEta","absEta_FullTrack_minusEta",absEtaBins.size()-1,&absEtaBins[0]);
	TH1D * phi_FullTrack_minusEta = new TH1D("phi_FullTrack_minusEta","phi_FullTrack_minusEta",phiBins.size()-1,&phiBins[0]);

	relPt_FullTrack_all->Sumw2();
	relDxy_FullTrack_all->Sumw2();
	relDz_FullTrack_all->Sumw2();
	absRelDxy_FullTrack_all->Sumw2();
	absRelDz_FullTrack_all->Sumw2();
	dxy_FullTrack_all->Sumw2();
	dz_FullTrack_all->Sumw2();
	dxyErr_FullTrack_all->Sumw2();
	dzErr_FullTrack_all->Sumw2();
	absEta_FullTrack_all->Sumw2();
	phi_FullTrack_all->Sumw2();

	relPt_FullTrack_plusEta->Sumw2();
	relDxy_FullTrack_plusEta->Sumw2();
	relDz_FullTrack_plusEta->Sumw2();
	absRelDxy_FullTrack_plusEta->Sumw2();
	absRelDz_FullTrack_plusEta->Sumw2();
	dxy_FullTrack_plusEta->Sumw2();
	dz_FullTrack_plusEta->Sumw2();
	dxyErr_FullTrack_plusEta->Sumw2();
	dzErr_FullTrack_plusEta->Sumw2();
	absEta_FullTrack_plusEta->Sumw2();

	relPt_FullTrack_minusEta->Sumw2();
	relDxy_FullTrack_minusEta->Sumw2();
	relDz_FullTrack_minusEta->Sumw2();
	absRelDxy_FullTrack_minusEta->Sumw2();
	absRelDz_FullTrack_minusEta->Sumw2();
	dxy_FullTrack_minusEta->Sumw2();
	dz_FullTrack_minusEta->Sumw2();
	dxyErr_FullTrack_minusEta->Sumw2();
	dzErr_FullTrack_minusEta->Sumw2();
	absEta_FullTrack_minusEta->Sumw2();
		
// --- loop		 
	for (int i=0;i<c_FullTrackTrigger_Track20->GetEntries();i++) {
//	for (int i=0;i<5000;i++) {

		c_FullTrackTrigger_Track20->GetEntry(i);
		if (i % 2000 == 0) cout <<i<<" / "<<c_FullTrackTrigger_Track20->GetEntries()<<endl;
//		if (i % 2000 == 0) cout <<i<<" / "<<5000<<endl;

		//Event Selection
		bool event_accepted = true;
		if(!(TMath::Abs(c_FullTrackTrigger_Track20->evt.vz)<15.)) event_accepted = false;
		if(event_accepted == false) {
//			std::cout<< i <<"th vz = "<< c_FullTrackTrigger_Track20->evt.vz <<std::endl; 
				 continue;
		}

		//Tracks (Fill the histogram)
		for(int j=0;j<c_FullTrackTrigger_Track20->track.nTrk;j++) {

			if(!( (c_FullTrackTrigger_Track20->track.trkEta[j]<1.0)
				 && (c_FullTrackTrigger_Track20->track.trkEta[j]>-1.0)
				 && (c_FullTrackTrigger_Track20->track.trkPt[j]>3.4)
			  ))
				continue;

			relPt_FullTrack_all->Fill( c_FullTrackTrigger_Track20->track.trkPtError[j]/c_FullTrackTrigger_Track20->track.trkPt[j] );
			relDxy_FullTrack_all->Fill( c_FullTrackTrigger_Track20->track.trkDxy1[j]/c_FullTrackTrigger_Track20->track.trkDxyError1[j] );
			relDz_FullTrack_all->Fill( c_FullTrackTrigger_Track20->track.trkDz1[j]/c_FullTrackTrigger_Track20->track.trkDzError1[j] );
			absRelDxy_FullTrack_all->Fill( fabs(c_FullTrackTrigger_Track20->track.trkDxy1[j]/c_FullTrackTrigger_Track20->track.trkDxyError1[j]) );
			absRelDz_FullTrack_all->Fill( fabs(c_FullTrackTrigger_Track20->track.trkDz1[j]/c_FullTrackTrigger_Track20->track.trkDzError1[j]) );
			dxy_FullTrack_all->Fill( c_FullTrackTrigger_Track20->track.trkDxy1[j] );
			dz_FullTrack_all->Fill( c_FullTrackTrigger_Track20->track.trkDz1[j] );
			dxyErr_FullTrack_all->Fill( c_FullTrackTrigger_Track20->track.trkDxyError1[j] );
			dzErr_FullTrack_all->Fill( c_FullTrackTrigger_Track20->track.trkDzError1[j] );
			absEta_FullTrack_all->Fill( c_FullTrackTrigger_Track20->track.trkEta[j] );
			phi_FullTrack_all->Fill( c_FullTrackTrigger_Track20->track.trkPhi[j] );

			if ( (c_FullTrackTrigger_Track20->track.trkEta[j]<1.0) 
				&& (c_FullTrackTrigger_Track20->track.trkEta[j]>0.) ){
				relPt_FullTrack_plusEta->Fill( c_FullTrackTrigger_Track20->track.trkPtError[j]/c_FullTrackTrigger_Track20->track.trkPt[j] );
				relDxy_FullTrack_plusEta->Fill( c_FullTrackTrigger_Track20->track.trkDxy1[j]/c_FullTrackTrigger_Track20->track.trkDxyError1[j] );
				relDz_FullTrack_plusEta->Fill( c_FullTrackTrigger_Track20->track.trkDz1[j]/c_FullTrackTrigger_Track20->track.trkDzError1[j] );
				absRelDxy_FullTrack_plusEta->Fill( fabs(c_FullTrackTrigger_Track20->track.trkDxy1[j]/c_FullTrackTrigger_Track20->track.trkDxyError1[j]) );
				absRelDz_FullTrack_plusEta->Fill( fabs(c_FullTrackTrigger_Track20->track.trkDz1[j]/c_FullTrackTrigger_Track20->track.trkDzError1[j]) );
				dxy_FullTrack_plusEta->Fill( c_FullTrackTrigger_Track20->track.trkDxy1[j] );
				dz_FullTrack_plusEta->Fill( c_FullTrackTrigger_Track20->track.trkDz1[j] );
				dxyErr_FullTrack_plusEta->Fill( c_FullTrackTrigger_Track20->track.trkDxyError1[j] );
				dzErr_FullTrack_plusEta->Fill( c_FullTrackTrigger_Track20->track.trkDzError1[j] );
				absEta_FullTrack_plusEta->Fill( fabs(c_FullTrackTrigger_Track20->track.trkEta[j]) );
				phi_FullTrack_plusEta->Fill( c_FullTrackTrigger_Track20->track.trkPhi[j] );
			}
			else if ( (c_FullTrackTrigger_Track20->track.trkEta[j]<0.) 
				&& (c_FullTrackTrigger_Track20->track.trkEta[j]>-1.0) ){
				relPt_FullTrack_minusEta->Fill( c_FullTrackTrigger_Track20->track.trkPtError[j]/c_FullTrackTrigger_Track20->track.trkPt[j] );
				relDxy_FullTrack_minusEta->Fill( c_FullTrackTrigger_Track20->track.trkDxy1[j]/c_FullTrackTrigger_Track20->track.trkDxyError1[j] );
				relDz_FullTrack_minusEta->Fill( c_FullTrackTrigger_Track20->track.trkDz1[j]/c_FullTrackTrigger_Track20->track.trkDzError1[j] );
				absRelDxy_FullTrack_minusEta->Fill( fabs(c_FullTrackTrigger_Track20->track.trkDxy1[j]/c_FullTrackTrigger_Track20->track.trkDxyError1[j]) );
				absRelDz_FullTrack_minusEta->Fill( fabs(c_FullTrackTrigger_Track20->track.trkDz1[j]/c_FullTrackTrigger_Track20->track.trkDzError1[j]) );
				dxy_FullTrack_minusEta->Fill( c_FullTrackTrigger_Track20->track.trkDxy1[j] );
				dz_FullTrack_minusEta->Fill( c_FullTrackTrigger_Track20->track.trkDz1[j] );
				dxyErr_FullTrack_minusEta->Fill( c_FullTrackTrigger_Track20->track.trkDxyError1[j] );
				dzErr_FullTrack_minusEta->Fill( c_FullTrackTrigger_Track20->track.trkDzError1[j] );
				absEta_FullTrack_minusEta->Fill( fabs(c_FullTrackTrigger_Track20->track.trkEta[j]) );
				phi_FullTrack_minusEta->Fill( c_FullTrackTrigger_Track20->track.trkPhi[j] );
			}
		} //Track forLoop end
 
	}//event forLoop end

	normalizeByBinWidth(relPt_FullTrack_all);
	normalizeByBinWidth(relDxy_FullTrack_all);
	normalizeByBinWidth(relDz_FullTrack_all);
	normalizeByBinWidth(absRelDxy_FullTrack_all);
	normalizeByBinWidth(absRelDz_FullTrack_all);
	normalizeByBinWidth(dxy_FullTrack_all);
	normalizeByBinWidth(dz_FullTrack_all);
	normalizeByBinWidth(dxyErr_FullTrack_all);
	normalizeByBinWidth(dzErr_FullTrack_all);
	normalizeByBinWidth(absEta_FullTrack_all);
	normalizeByBinWidth(phi_FullTrack_all);

	normalizeByBinWidth(relPt_FullTrack_plusEta);
	normalizeByBinWidth(relDxy_FullTrack_plusEta);
	normalizeByBinWidth(relDz_FullTrack_plusEta);
	normalizeByBinWidth(absRelDxy_FullTrack_plusEta);
	normalizeByBinWidth(absRelDz_FullTrack_plusEta);
	normalizeByBinWidth(dxy_FullTrack_plusEta);
	normalizeByBinWidth(dz_FullTrack_plusEta);
	normalizeByBinWidth(dxyErr_FullTrack_plusEta);
	normalizeByBinWidth(dzErr_FullTrack_plusEta);
	normalizeByBinWidth(absEta_FullTrack_plusEta);
	normalizeByBinWidth(phi_FullTrack_plusEta);

	normalizeByBinWidth(relPt_FullTrack_minusEta);
	normalizeByBinWidth(relDxy_FullTrack_minusEta);
	normalizeByBinWidth(relDz_FullTrack_minusEta);
	normalizeByBinWidth(absRelDxy_FullTrack_minusEta);
	normalizeByBinWidth(absRelDz_FullTrack_minusEta);
	normalizeByBinWidth(dxy_FullTrack_minusEta);
	normalizeByBinWidth(dz_FullTrack_minusEta);
	normalizeByBinWidth(dxyErr_FullTrack_minusEta);
	normalizeByBinWidth(dzErr_FullTrack_minusEta);
	normalizeByBinWidth(absEta_FullTrack_minusEta);
	normalizeByBinWidth(phi_FullTrack_minusEta);

	f_output->cd();
	relPt_FullTrack_all->Write();
	relDxy_FullTrack_all->Write();
	relDz_FullTrack_all->Write();
	absRelDxy_FullTrack_all->Write();
	absRelDz_FullTrack_all->Write();
	dxy_FullTrack_all->Write();
	dz_FullTrack_all->Write();
	dxyErr_FullTrack_all->Write();
	dzErr_FullTrack_all->Write();
	absEta_FullTrack_all->Write();
	phi_FullTrack_all->Write();

	relPt_FullTrack_plusEta->Write();
	relDxy_FullTrack_plusEta->Write();
	relDz_FullTrack_plusEta->Write();
	absRelDxy_FullTrack_plusEta->Write();
	absRelDz_FullTrack_plusEta->Write();
	dxy_FullTrack_plusEta->Write();
	dz_FullTrack_plusEta->Write();
	dxyErr_FullTrack_plusEta->Write();
	dzErr_FullTrack_plusEta->Write();
	absEta_FullTrack_plusEta->Write();
	phi_FullTrack_plusEta->Write();

	relPt_FullTrack_minusEta->Write();
	relDxy_FullTrack_minusEta->Write();
	relDz_FullTrack_minusEta->Write();
	absRelDxy_FullTrack_minusEta->Write();
	absRelDz_FullTrack_minusEta->Write();
	dxy_FullTrack_minusEta->Write();
	dz_FullTrack_minusEta->Write();
	dxyErr_FullTrack_minusEta->Write();
	dzErr_FullTrack_minusEta->Write();
	absEta_FullTrack_minusEta->Write();
	phi_FullTrack_minusEta->Write();

	f_output->Close();
	std::cout << "Running ended!" <<std::endl;

}

void normalizeByBinWidth(TH1D *histo) {
	for(int i = 1; i <= histo->GetNbinsX(); i++) {
		float content = histo->GetBinContent(i);
		float error = histo->GetBinError(i);
		histo->SetBinContent(i,content/histo->GetBinWidth(i));
		histo->SetBinError(i,error/histo->GetBinWidth(i));
	}
}
