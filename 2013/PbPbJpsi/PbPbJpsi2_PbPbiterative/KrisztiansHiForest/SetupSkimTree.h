//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Sep 20 18:20:28 2012 by ROOT version 5.32/00
// from TTree HltTree/
// found on file: ../../../PAPhysics-test.root
//////////////////////////////////////////////////////////
#include "commonSetup.h"
#include <iostream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>

class Skims {
public :
   Skims(){};
   ~Skims(){};

   // Declaration of leaf types
   Int_t           reco_extra;
   Int_t           reco_extra_jet;
   Int_t           pat_step;
   Int_t           extrapatstep;
   Int_t           ana_step;
   Int_t           phltJetHI;
   Int_t           pcollisionEventSelection;
   Int_t           pBeamScrapingFilter;
   Int_t           pVertexFilterCutGplus;
   Int_t           pHBHENoiseFilter;
   Int_t           phiEcalRecHitSpikeFilter;
   Int_t           phfPosFilter1;
   Int_t           phfPosFilter2;
   Int_t           phfPosFilter3;
   Int_t           phfNegFilter1;
   Int_t           phfNegFilter2;
   Int_t           phfNegFilter3;
   Int_t           phltPixelClusterShapeFilter;
   Int_t           pprimaryvertexFilter;
   Int_t           phfCoincFilter;
   Int_t           ppurityFractionFilter;

   // List of branches
   TBranch        *b_reco_extra;   //!
   TBranch        *b_reco_extra_jet;   //!
   TBranch        *b_pat_step;   //!
   TBranch        *b_extrapatstep;   //!
   TBranch        *b_ana_step;   //!
   TBranch        *b_phltJetHI;   //!
   TBranch        *b_pcollisionEventSelection;   //!
   TBranch        *b_pBeamScrapingFilter;   //!
   TBranch        *b_pVertexFilterCutGplus;   //!
   TBranch        *b_pHBHENoiseFilter;   //!
   TBranch        *b_phiEcalRecHitSpikeFilter;   //!
   TBranch        *b_phfPosFilter1;   //!
   TBranch        *b_phfPosFilter2;   //!
   TBranch        *b_phfPosFilter3;   //!
   TBranch        *b_phfNegFilter1;   //!
   TBranch        *b_phfNegFilter2;   //!
   TBranch        *b_phfNegFilter3;   //!
   TBranch        *b_phltPixelClusterShapeFilter;   //!
   TBranch        *b_pprimaryvertexFilter;   //!
   TBranch        *b_phfCoincFilter;   //!
   TBranch        *b_ppurityFractionFilter;   //!

};


void setupSkimTree(TTree *t,Skims &tSkims,bool doCheck = 0)
{
   // Set branch addresses and branch pointers
   t->SetBranchAddress("reco_extra", &tSkims.reco_extra, &tSkims.b_reco_extra);
   t->SetBranchAddress("reco_extra_jet", &tSkims.reco_extra_jet, &tSkims.b_reco_extra_jet);
   t->SetBranchAddress("pat_step", &tSkims.pat_step, &tSkims.b_pat_step);
   t->SetBranchAddress("extrapatstep", &tSkims.extrapatstep, &tSkims.b_extrapatstep);
   t->SetBranchAddress("ana_step", &tSkims.ana_step, &tSkims.b_ana_step);
   t->SetBranchAddress("phltJetHI", &tSkims.phltJetHI, &tSkims.b_phltJetHI);
   t->SetBranchAddress("pcollisionEventSelection", &tSkims.pcollisionEventSelection, &tSkims.b_pcollisionEventSelection);
   t->SetBranchAddress("pBeamScrapingFilter", &tSkims.pBeamScrapingFilter, &tSkims.b_pBeamScrapingFilter);
   t->SetBranchAddress("pVertexFilterCutGplus", &tSkims.pVertexFilterCutGplus, &tSkims.b_pVertexFilterCutGplus);
   t->SetBranchAddress("pHBHENoiseFilter", &tSkims.pHBHENoiseFilter, &tSkims.b_pHBHENoiseFilter);
   t->SetBranchAddress("phiEcalRecHitSpikeFilter", &tSkims.phiEcalRecHitSpikeFilter, &tSkims.b_phiEcalRecHitSpikeFilter);
   t->SetBranchAddress("phfPosFilter1", &tSkims.phfPosFilter1, &tSkims.b_phfPosFilter1);
   t->SetBranchAddress("phfPosFilter2", &tSkims.phfPosFilter2, &tSkims.b_phfPosFilter2);
   t->SetBranchAddress("phfPosFilter3", &tSkims.phfPosFilter3, &tSkims.b_phfPosFilter3);
   t->SetBranchAddress("phfNegFilter1", &tSkims.phfNegFilter1, &tSkims.b_phfNegFilter1);
   t->SetBranchAddress("phfNegFilter2", &tSkims.phfNegFilter2, &tSkims.b_phfNegFilter2);
   t->SetBranchAddress("phfNegFilter3", &tSkims.phfNegFilter3, &tSkims.b_phfNegFilter3);
   t->SetBranchAddress("phltPixelClusterShapeFilter", &tSkims.phltPixelClusterShapeFilter, &tSkims.b_phltPixelClusterShapeFilter);
   t->SetBranchAddress("pprimaryvertexFilter", &tSkims.pprimaryvertexFilter, &tSkims.b_pprimaryvertexFilter);
   t->SetBranchAddress("phfCoincFilter", &tSkims.phfCoincFilter, &tSkims.b_phfCoincFilter);
   t->SetBranchAddress("ppurityFractionFilter", &tSkims.ppurityFractionFilter, &tSkims.b_ppurityFractionFilter);
   if (doCheck) {
   }
}

