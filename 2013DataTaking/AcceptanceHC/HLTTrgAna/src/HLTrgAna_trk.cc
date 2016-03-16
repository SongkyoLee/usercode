// -*- C++ -*-
//
// Package:    HLTrgAna_trk
// Class:      HLTrgAna_trk
// 
/**\class HLTrgAna_trk HLTrgAna_trk.cc UserCode/HLTrgAna_trk/src/HLTrgAna_trk.cc

Description: <one line class summary>

Implementation:
<Notes on implementation>
*/
//
// Original Author:  Dong Ho Moon
//         Created:  Wed Sep 16 11:58:35 CEST 2009
// $Id: HLTrgAna_trk.cc,v 1.14 2010/11/04 14:24:22 dmoon Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include <string>
#include <functional>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/EDMException.h"

#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidateFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/TrajectorySeed/interface/TrajectorySeed.h"
#include "DataFormats/L1Trigger/interface/L1MuonParticle.h"
#include "L1Trigger/L1ExtraFromDigis/interface/L1ExtraParticlesProd.h"
#include "DataFormats/MuonSeed/interface/L2MuonTrajectorySeed.h"
#include "DataFormats/MuonSeed/interface/L2MuonTrajectorySeedCollection.h"
#include "DataFormats/MuonSeed/interface/L3MuonTrajectorySeed.h"
#include "DataFormats/MuonSeed/interface/L3MuonTrajectorySeedCollection.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMap.h"

#include "DataFormats/L1Trigger/interface/L1MuonParticleFwd.h"
#include "DataFormats/L1Trigger/interface/L1ParticleMap.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerRecord.h"
#include "RecoVertex/VertexPrimitives/interface/TransientVertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "L1Trigger/CSCTrackFinder/interface/CSCSectorReceiverLUT.h"
#include <L1Trigger/CSCTrackFinder/src/CSCTFDTReceiver.h>


#include "DataFormats/CSCDigi/interface/CSCCorrelatedLCTDigiCollection.h"
#include "DataFormats/L1CSCTrackFinder/interface/L1CSCTrackCollection.h"
#include "DataFormats/L1CSCTrackFinder/interface/CSCTriggerContainer.h"
#include "DataFormats/L1CSCTrackFinder/interface/TrackStub.h"

#include "HLTrigger/HLTfilters/interface/HLTHighLevel.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "HepMC/GenEvent.h"
#include "HepMC/HeavyIon.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticleFwd.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"

#include "CondFormats/L1TObjects/interface/L1MuTriggerScales.h"
#include "CondFormats/DataRecord/interface/L1MuTriggerScalesRcd.h"
#include "CondFormats/L1TObjects/interface/L1MuTriggerPtScale.h"
#include "CondFormats/DataRecord/interface/L1MuTriggerPtScaleRcd.h"

//#include "DQMServices/Core/interface/DQMStore.h"
//#include "DQMServices/Core/interface/MonitorElement.h"
#include "L1Trigger/CSCTrackFinder/interface/CSCSectorReceiverLUT.h"
#include <L1Trigger/CSCTrackFinder/interface/CSCTFPtLUT.h>
#include "L1Trigger/CSCTrackFinder/interface/CSCTrackFinderDataTypes.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include "DataFormats/Luminosity/interface/LumiSummary.h"


//
#include <TH1.h>
#include <TFile.h>
#include <TString.h>
#include <stdio.h>
#include <TH2F.h>

#include <TNtuple.h>
#include <TLorentzVector.h>

using namespace edm;
using namespace reco;
using namespace std;

const double m_mu = .105658;

//
// class decleration
//

class HLTrgAna_trk : public edm::EDAnalyzer {
    public:
        explicit HLTrgAna_trk(const edm::ParameterSet&);
        ~HLTrgAna_trk();
        const static int xNum = 10000;
        const static int yNum = 3;

    private:
        virtual void beginJob() ;
        virtual void analyze(const edm::Event&, const edm::EventSetup&);
        void endLuminosityBlock(const edm::LuminosityBlock &lumiBlock, const edm::EventSetup &iSetup);
        //virtual void endLuminosityBlock(const edm::LuminosityBlock &lumiBlock, const edm::EventSetup &iSetup);
        virtual void endJob() ;

        // ----------member data ---------------------------

        std::string fOutputFile_;

        edm::InputTag genSource_;
        edm::InputTag L2MuCands_;
        edm::InputTag triggerResults_,trackProducer;
        edm::InputTag muTrackTag_;
        edm::InputTag staMuons_;
	edm::InputTag _thePVs;

        std::vector<std::string> hltPaths_L1_;
        std::vector<std::string> hltPaths_L3_;

        int nPart, nColl, nHard;
        int nL1Acc, nL1SAcc, nL2Acc, nL2SAcc, nPVAcc, nL3Acc, nL2Acc3, nL2Acc5, nL2Acc7, nL2Acc10, nL2Acc12;
        int nL1Acc0, nL1Acc1, nL1Acc2, nL1Acc3, nL1Acc4,nL1Acc_DoubleMuOpenQual4,nL1Acc_DoubleMu3Qual4;
        int nL1Acc5, nL1Acc6, nL1Acc7;
        int nL1Mu, nGMu, nSMu;
        int nHLT_HIL2DoubleMu0, nHLT_HIL2DoubleMu0_Core, nHLT_HIL2Mu3, nHLT_HIL2Mu3_Core;
        int nHLT_HIL2Mu5, nHLT_HIL2Mu5_Core, nHLT_HIL2Mu7, nHLT_HIL2Mu7_Core;
        int nHLT_HIL1DoubleMuOpen, nHLT_HIL1SingleMuOpen, nHLT_HIL1SingleMu0, nHLT_HIL1SingleMu3;
        int nHLT_HIL1SingleMu5, nHLT_HIL1SingleMu7, nHLT_HIL1SingleMu10;
        int nHLT_HIMinBiasBSC, nHLT_HIMinBiasHF;

        int nHLT_HIL1DoubleMu3, nHLT_HIL2DoubleMu3;
        int nHLT_HIL2Mu5Tight, nHLT_HIL2Mu9;
        int nHLT_HIL2Mu11, nHLT_HIL2Mu15, nHLT_HIL2Mu20;
        int nHLT_HIL2Mu11Central, nHLT_HIL2Mu11Tight;

        double Imp;
        double nFRate, nFRateSim;

        int Run, Evt, Lumi, nmom, nPar, ndau, p_Id[xNum]; 
        int nMom[xNum], nDau[xNum], m_Id[xNum][yNum], d_Id[xNum][yNum];
        int p_ch[xNum], m_ch[xNum][yNum], d_ch[xNum][yNum];

        double p_pt[xNum], p_eta[xNum], p_phi[xNum], p_st[xNum], p_mass[xNum], p_mtum[xNum], 
               p_vx[xNum], p_vy[xNum], p_vz[xNum], p_y[xNum], p_p[xNum];
        double m_pt[xNum][yNum], m_eta[xNum][yNum], m_phi[xNum][yNum], m_st[xNum][yNum], 
               m_mass[xNum][yNum], m_mtum[xNum][yNum], m_vx[xNum][yNum], m_vy[xNum][yNum], 
               m_vz[xNum][yNum], m_y[xNum][yNum], m_p[xNum][yNum];
        double d_pt[xNum][yNum], d_eta[xNum][yNum], d_phi[xNum][yNum], d_st[xNum][yNum], 
               d_mass[xNum][yNum], d_mtum[xNum][yNum], d_vx[xNum][yNum], d_vy[xNum][yNum], 
               d_vz[xNum][yNum], d_y[xNum][yNum], d_p[xNum][yNum]; 
        double l1mu_p, l1mu_pt, l1mu_eta, l1mu_phi;
        int l1mu_ch;
        int modeP[xNum],etaP[xNum];
        int l1mu_qual;
        double s_pt[xNum], s_eta[xNum], s_phi[xNum], s_p[xNum];
        int s_ch[xNum], s_Id[xNum], s_st[xNum];

        int gmu_Id[xNum], gmu_ch[xNum], ngMu;
        double gmu_pt[xNum], gmu_eta[xNum], gmu_phi[xNum], gmu_st[xNum], gmu_mass[xNum], gmu_mtum[xNum], 
               gmu_vx[xNum], gmu_vy[xNum], gmu_vz[xNum], gmu_y[xNum], gmu_p[xNum],
               gmu_px[xNum], gmu_py[xNum], gmu_pz[xNum];

        int ngdimu, gdimu_ch[xNum];
        double gdimu_pt[xNum], gdimu_p[xNum], gdimu_eta[xNum], gdimu_phi[xNum], gdimu_mass[xNum], gdimu_y[xNum];
        double gdkid_pt[xNum][2], gdkid_phi[xNum][2], gdkid_eta[xNum][2], gdkid_p[xNum][2], gdkid_y[xNum][2];


        // Reco Ana
        // Single muons and Dimuons
        int nRDMu, nSDMu, nTDMu, nSTA, nGLB, nTRK;
        double sta_pt[xNum], sta_eta[xNum], sta_phi[xNum], sta_p[xNum], sta_y[xNum];

        double glb_pt[xNum], glb_eta[xNum], glb_phi[xNum], glb_p[xNum], glb_y[xNum];
        double glb_dxy[xNum], glb_dz[xNum];
	int glb_numberOfValidTrackerHits[xNum];
	double glb_normalizedChi2[xNum];


        double trk_pt[xNum], trk_eta[xNum], trk_phi[xNum], trk_p[xNum], trk_y[xNum];
        double trk_dxy[xNum], trk_dz[xNum];

        double rdmu_pt[xNum], rdmu_p[xNum], rdmu_eta[xNum], rdmu_phi[xNum], rdmu_mass[xNum], rdmu_y[xNum];
        double rkids_pt[xNum][2], rkids_phi[xNum][2], rkids_eta[xNum][2], rkids_p[xNum][2], rkids_y[xNum][2];
        double sdmu_pt[xNum], sdmu_p[xNum], sdmu_eta[xNum], sdmu_phi[xNum], sdmu_mass[xNum], sdmu_y[xNum];
        double skids_pt[xNum][2], skids_phi[xNum][2], skids_eta[xNum][2], skids_p[xNum][2], skids_y[xNum][2];
        double tdmu_pt[xNum], tdmu_p[xNum], tdmu_eta[xNum], tdmu_phi[xNum], tdmu_mass[xNum], tdmu_y[xNum];
        double tkids_pt[xNum][2], tkids_phi[xNum][2], tkids_eta[xNum][2], tkids_p[xNum][2], tkids_y[xNum][2];
 

        int rdmu_ch[xNum], sdmu_ch[xNum], tdmu_ch[xNum];

        bool MC_, HiMC_, SIM_, L1_TRG_, HLT_, RECO_;

        TFile *hOutputFile;
        TTree *rTree;

	math::XYZPoint RefVtx;
	float zVtx;
	float nPV;

	// number of primary vertices
	TH1F* hPileUp;

	// z vertex distribution
	TH1F* hZVtx;

        double Getrapidity(double p, double pz, double mass);

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
HLTrgAna_trk::HLTrgAna_trk(const edm::ParameterSet& iConfig):
    trackProducer (iConfig.getUntrackedParameter<edm::InputTag>("trackProducer",edm::InputTag("csctfunpacker")))
{
    //now do what ever initialization is neededi
    genSource_      = iConfig.getUntrackedParameter<edm::InputTag>("genSource");
    L2MuCands_      = iConfig.getUntrackedParameter<edm::InputTag>("L2MuCands");
    fOutputFile_    = iConfig.getUntrackedParameter<std::string>("hOutputFile");
    MC_             = iConfig.getParameter<bool>("doMC");
    HiMC_           = iConfig.getParameter<bool>("doHiMC");
    SIM_            = iConfig.getParameter<bool>("doSIM");
    L1_TRG_         = iConfig.getParameter<bool>("doL1");
    HLT_            = iConfig.getParameter<bool>("doHLT");
    RECO_           = iConfig.getParameter<bool>("doRECO");
    triggerResults_ = iConfig.getParameter<edm::InputTag>("TriggerResults");
    muTrackTag_     = iConfig.getParameter<edm::InputTag>("muTrackTag");
    staMuons_       = iConfig.getParameter<edm::InputTag>("staMuonsTag");
    _thePVs	    = iConfig.getParameter<edm::InputTag>("primaryVertexTag");

}


HLTrgAna_trk::~HLTrgAna_trk()
{

    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)

}

    void 
HLTrgAna_trk::beginJob()
{
    hOutputFile   = new TFile( fOutputFile_.c_str(), "RECREATE" ) ;
    rTree = new TTree("Ana","Dilepton Analysis");

    rTree->Branch("zVtx",   	  &zVtx,          "zVtx/F");
    rTree->Branch("nPar",         &nPar,          "nPar/I");
    rTree->Branch("nGMu",         &nGMu,          "nGMu/I");
    rTree->Branch("nSMu",         &nSMu,          "nSMu/I");
    rTree->Branch("Evt",          &Evt,           "Evt/I");
    rTree->Branch("Lumi",         &Lumi,          "Lumi/I");
    rTree->Branch("Run",          &Run,           "Run/I");
    rTree->Branch("Imp",          &Imp,           "Imp/D");
    rTree->Branch("nPart",        &nPart,         "nPart/I");
    rTree->Branch("nColl",        &nColl,         "nColl/I");
    rTree->Branch("nHard",        &nHard,         "nHard/I");

    rTree->Branch("nFRate",       &nFRate,        "nFRate/D");
    rTree->Branch("nFRateSim",    &nFRateSim,     "nFRateSim/D");
    rTree->Branch("nL1Mu",        &nL1Mu,         "nL1Mu/I");
    rTree->Branch("nL1Acc",       &nL1Acc,        "nL1Acc/I");
    rTree->Branch("nL1Acc0",      &nL1Acc0,       "nL1Acc0/I");
    rTree->Branch("nL1Acc1",      &nL1Acc1,       "nL1Acc1/I");
    rTree->Branch("nL1Acc2",      &nL1Acc2,       "nL1Acc2/I");
    rTree->Branch("nL1Acc3",      &nL1Acc3,       "nL1Acc3/I");
    rTree->Branch("nL1Acc4",      &nL1Acc4,       "nL1Acc4/I");
    rTree->Branch("nL1Acc5",      &nL1Acc5,       "nL1Acc5/I");
    rTree->Branch("nL1Acc6",      &nL1Acc6,       "nL1Acc6/I");
    rTree->Branch("nL1Acc7",      &nL1Acc7,       "nL1Acc7/I");
    rTree->Branch("nL1SAcc",      &nL1SAcc,       "nL1SAcc/I");

    rTree->Branch("nL1Acc_DoubleMuOpenQual4",      &nL1Acc_DoubleMuOpenQual4,       "nL1Acc_DoubleMuOpenQual4/I");
    rTree->Branch("nL1Acc_DoubleMu3Qual4",      &nL1Acc_DoubleMu3Qual4,       "nL1Acc_DoubleMu3Qual4/I");

    rTree->Branch("nL2Acc",       &nL2Acc,        "nL2Acc/I");
    rTree->Branch("nL2Acc3",      &nL2Acc3,       "nL2Acc3/I");
    rTree->Branch("nL2Acc5",      &nL2Acc5,       "nL2Acc5/I");
    rTree->Branch("nL2Acc7",      &nL2Acc7,       "nL2Acc7/I");
    rTree->Branch("nL2Acc10",     &nL2Acc10,      "nL2Acc10/I");
    rTree->Branch("nL2Acc12",     &nL2Acc12,      "nL2Acc12/I");
    rTree->Branch("nL2SAcc",      &nL2SAcc,       "nL2SAcc/I");
    rTree->Branch("nPVAcc",       &nPVAcc,        "nPVAcc/I");
    rTree->Branch("nL3Acc",       &nL3Acc,        "nL3Acc/I");

    rTree->Branch("p_Id",         &p_Id,          "p_Id[nPar]/I");
    rTree->Branch("p_pt",         &p_pt,          "p_pt[nPar]/D");
    rTree->Branch("p_y",          &p_y,           "p_y[nPar]/D");
    rTree->Branch("p_eta",        &p_eta,         "p_eta[nPar]/D");
    rTree->Branch("p_phi",        &p_phi,         "p_phi[nPar]/D");
    rTree->Branch("p_st",         &p_st,          "p_st[nPar]/D");
    rTree->Branch("p_mass",       &p_mass,        "p_mass[nPar]/D");
    rTree->Branch("p_vx",         &p_vx,          "p_vx[nPar]/D");
    rTree->Branch("p_vy",         &p_vy,          "p_vy[nPar]/D");
    rTree->Branch("p_vz",         &p_vz,          "p_vz[nPar]/D");
    rTree->Branch("p_p",          &p_p,           "p_p[nPar]/D");
    rTree->Branch("p_ch",         &p_ch,          "p_ch[nPar]/I");

    rTree->Branch("nMom",         &nMom,          "nMom[nPar]/I");
    rTree->Branch("m_Id",         &m_Id,          "m_Id[nPar][3]/I");
    rTree->Branch("m_pt",         &m_pt,          "m_pt[nPar][3]/D");
    rTree->Branch("m_y",          &m_y,           "m_y[nPar][3]/D");
    rTree->Branch("m_eta",        &m_eta,         "m_eta[nPar][3]/D");
    rTree->Branch("m_phi",        &m_phi,         "m_phi[nPar][3]/D");
    rTree->Branch("m_st",         &m_st,          "m_st[nPar][3]/D");
    rTree->Branch("m_mass",       &m_mass,        "m_mass[nPar][3]/D");
    rTree->Branch("m_vx",         &m_vx,          "m_vx[nPar][3]/D");
    rTree->Branch("m_vy",         &m_vy,          "m_vy[nPar][3]/D");
    rTree->Branch("m_vz",         &m_vz,          "m_vz[nPar][3]/D");
    rTree->Branch("m_p",          &m_p,           "m_p[nPar][3]/D");
    rTree->Branch("m_ch",         &m_ch,          "m_ch[nPar][3]/I");

    rTree->Branch("nDau",         &nDau,          "nDau[nPar]/I");
    rTree->Branch("d_Id",         &d_Id,          "d_Id[nPar][3]/I");
    rTree->Branch("d_pt",         &d_pt,          "d_pt[nPar][3]/D");
    rTree->Branch("d_y",          &d_y,           "d_y[nPar][3]/D");
    rTree->Branch("d_eta",        &d_eta,         "d_eta[nPar][3]/D");
    rTree->Branch("d_phi",        &d_phi,         "d_phi[nPar][3]/D");
    rTree->Branch("d_st",         &d_st,          "d_st[nPar][3]/D");
    rTree->Branch("d_mass",       &d_mass,        "d_mass[nPar][3]/D");
    rTree->Branch("d_vx",         &p_vx,          "d_vx[nPar][3]/D");
    rTree->Branch("d_vy",         &p_vy,          "d_vy[nPar][3]/D");
    rTree->Branch("d_vz",         &p_vz,          "d_vz[nPar][3]/D");
    rTree->Branch("d_p",          &d_p,           "d_p[nPar][3]/D");
    rTree->Branch("d_ch",         &d_ch,          "d_ch[nPar][3]/I");

    rTree->Branch("ngMu",         &ngMu,          "ngMu/I");
    rTree->Branch("gmu_Id",         &gmu_Id,          "gmu_Id[ngMu]/I");
    rTree->Branch("gmu_pt",         &gmu_pt,          "gmu_pt[ngMu]/D");
    rTree->Branch("gmu_y",          &gmu_y,           "gmu_y[ngMu]/D");
    rTree->Branch("gmu_eta",        &gmu_eta,         "gmu_eta[ngMu]/D");
    rTree->Branch("gmu_phi",        &gmu_phi,         "gmu_phi[ngMu]/D");
    rTree->Branch("gmu_st",         &gmu_st,          "gmu_st[ngMu]/D");
    rTree->Branch("gmu_mass",       &gmu_mass,        "gmu_mass[ngMu]/D");
    rTree->Branch("gmu_vx",         &gmu_vx,          "gmu_vx[ngMu]/D");
    rTree->Branch("gmu_vy",         &gmu_vy,          "gmu_vy[ngMu]/D");
    rTree->Branch("gmu_vz",         &gmu_vz,          "gmu_vz[ngMu]/D");
    rTree->Branch("gmu_p",          &gmu_p,           "gmu_p[ngMu]/D");
    rTree->Branch("gmu_px",         &gmu_px,          "gmu_px[ngMu]/D");
    rTree->Branch("gmu_py",         &gmu_py,          "gmu_py[ngMu]/D");
    rTree->Branch("gmu_pz",         &gmu_pz,          "gmu_pz[ngMu]/D");
    rTree->Branch("gmu_ch",      &gmu_ch,       "gmu_ch[ngMu]/I");

    rTree->Branch("ngdimu",        &ngdimu,         "ngdimu/I");
    rTree->Branch("gdimu_pt",      &gdimu_pt,       "gdimu_pt[ngdimu]/D");
    rTree->Branch("gdimu_ch",      &gdimu_ch,       "gdimu_ch[ngdimu]/I");
    rTree->Branch("gdimu_p",       &gdimu_p,        "gdimu_p[ngdimu]/D");
    rTree->Branch("gdimu_eta",     &gdimu_eta,      "gdimu_eta[ngdimu]/D");
    rTree->Branch("gdimu_phi",     &gdimu_phi,      "gdimu_phi[ngdimu]/D");
    rTree->Branch("gdimu_mass",    &gdimu_mass,     "gdimu_mass[ngdimu]/D");
    rTree->Branch("gdimu_y",     &gdimu_y,      "gdimu_y[ngdimu]/D");

    rTree->Branch("gdkid_pt",     &gdkid_pt,      "gdkid_pt[ngdimu][2]/D");
    rTree->Branch("gdkid_phi",    &gdkid_phi,     "gdkid_phi[ngdimu][2]/D");
    rTree->Branch("gdkid_eta",    &gdkid_eta,     "gdkid_eta[ngdimu][2]/D");
    rTree->Branch("gdkid_p",      &gdkid_p,       "gdkid_p[ngdimu][2]/D");
    rTree->Branch("gdkid_y",    &gdkid_y,     "gdkid_y[ngdimu][2]/D");



    rTree->Branch("l1mu_pt",      &l1mu_pt,       "l1mu_pt/D");
    rTree->Branch("l1mu_eta",     &l1mu_eta,      "l1mu_eta/D");
    rTree->Branch("l1mu_phi",     &l1mu_phi,      "l1mu_phi/D");
    rTree->Branch("l1mu_ch",      &l1mu_ch,       "l1mu_ch/I");
    rTree->Branch("l1mu_qual",    &l1mu_qual,     "l1mu_qual/I");
    rTree->Branch("l1mu_p",       &l1mu_p,        "l1mu_p/D");

    rTree->Branch("s_pt",         &s_pt,          "s_pt[nSMu]/D");
    rTree->Branch("s_p",          &s_p,           "s_p[nSMu]/D");
    rTree->Branch("s_eta",        &s_eta,         "s_eta[nSMu]/D");
    rTree->Branch("s_phi",        &s_phi,         "s_phi[nSMu]/D");
    rTree->Branch("s_ch",         &s_ch,          "s_ch[nSMu]/I");
    rTree->Branch("s_Id",         &s_Id,          "s_Id[nSMu]/I");
    rTree->Branch("s_st",         &s_st,          "s_st[nSMu]/I");

    //Reco DiMuon
    rTree->Branch("nRDMu",        &nRDMu,         "nRDMu/I");
    rTree->Branch("rdmu_pt",      &rdmu_pt,       "rdmu_pt[nRDMu]/D");
    rTree->Branch("rdmu_ch",      &rdmu_ch,       "rdmu_ch[nRDMu]/I");
    rTree->Branch("rdmu_p",       &rdmu_p,        "rdmu_p[nRDMu]/D");
    rTree->Branch("rdmu_eta",     &rdmu_eta,      "rdmu_eta[nRDMu]/D");
    rTree->Branch("rdmu_phi",     &rdmu_phi,      "rdmu_phi[nRDMu]/D");
    rTree->Branch("rdmu_mass",    &rdmu_mass,     "rdmu_mass[nRDMu]/D");
    rTree->Branch("rdmu_y",    &rdmu_y,     "rdmu_y[nRDMu]/D");


    rTree->Branch("rkids_pt",     &rkids_pt,      "rkids_pt[nRDMu][2]/D");
    rTree->Branch("rkids_phi",    &rkids_phi,     "rkids_phi[nRDMu][2]/D");
    rTree->Branch("rkids_eta",    &rkids_eta,     "rkids_eta[nRDMu][2]/D");
    rTree->Branch("rkids_p",      &rkids_p,       "rkids_p[nRDMu][2]/D");
    rTree->Branch("rkids_y",      &rkids_y,       "rkids_y[nRDMu][2]/D");


    rTree->Branch("nSDMu",        &nSDMu,         "nSDMu/I");
    rTree->Branch("sdmu_pt",      &sdmu_pt,       "sdmu_pt[nSDMu]/D");
    rTree->Branch("sdmu_ch",      &sdmu_ch,       "sdmu_ch[nSDMu]/I");
    rTree->Branch("sdmu_p",       &sdmu_p,        "sdmu_p[nSDMu]/D");
    rTree->Branch("sdmu_eta",     &sdmu_eta,      "sdmu_eta[nSDMu]/D");
    rTree->Branch("sdmu_phi",     &sdmu_phi,      "sdmu_phi[nSDMu]/D");
    rTree->Branch("sdmu_mass",    &sdmu_mass,     "sdmu_mass[nSDMu]/D");
    rTree->Branch("sdmu_y",    &sdmu_y,     "sdmu_y[nSDMu]/D");


    rTree->Branch("skids_pt",     &skids_pt,      "skids_pt[nSDMu][2]/D");
    rTree->Branch("skids_phi",    &skids_phi,     "skids_phi[nSDMu][2]/D");
    rTree->Branch("skids_eta",    &skids_eta,     "skids_eta[nSDMu][2]/D");
    rTree->Branch("skids_p",      &skids_p,       "skids_p[nSDMu][2]/D");
    rTree->Branch("skids_p",      &skids_p,       "skids_p[nSDMu][2]/D");

    rTree->Branch("nTDMu",        &nTDMu,         "nTDMu/I");
    rTree->Branch("tdmu_pt",      &tdmu_pt,       "tdmu_pt[nTDMu]/D");
    rTree->Branch("tdmu_ch",      &tdmu_ch,       "tdmu_ch[nTDMu]/I");
    rTree->Branch("tdmu_p",       &tdmu_p,        "tdmu_p[nTDMu]/D");
    rTree->Branch("tdmu_eta",     &tdmu_eta,      "tdmu_eta[nTDMu]/D");
    rTree->Branch("tdmu_phi",     &tdmu_phi,      "tdmu_phi[nTDMu]/D");
    rTree->Branch("tdmu_mass",    &tdmu_mass,     "tdmu_mass[nTDMu]/D");
    rTree->Branch("tdmu_y",    &tdmu_y,     "tdmu_y[nTDMu]/D");


    rTree->Branch("tkids_pt",     &tkids_pt,      "tkids_pt[nTDMu][2]/D");
    rTree->Branch("tkids_phi",    &tkids_phi,     "tkids_phi[nTDMu][2]/D");
    rTree->Branch("tkids_eta",    &tkids_eta,     "tkids_eta[nTDMu][2]/D");
    rTree->Branch("tkids_p",      &tkids_p,       "tkids_p[nTDMu][2]/D");
    rTree->Branch("tkids_y",      &tkids_y,       "tkids_y[nTDMu][2]/D");


    //Reco Single muon
    rTree->Branch("nSTA",         &nSTA,          "nSTA/I");
    rTree->Branch("sta_pt",       &sta_pt,        "sta_pt[nSTA]/D");
    rTree->Branch("sta_p",        &sta_p,         "sta_p[nSTA]/D");
    rTree->Branch("sta_eta",      &sta_eta,       "sta_eta[nSTA]/D");
    rTree->Branch("sta_phi",      &sta_phi,       "sta_phi[nSTA]/D");
    rTree->Branch("sta_y",      &sta_y,       "sta_y[nSTA]/D");


    rTree->Branch("nGLB",         &nGLB,          "nGLB/I");
    rTree->Branch("glb_pt",       &glb_pt,        "glb_pt[nGLB]/D");
    rTree->Branch("glb_p",        &glb_p,         "glb_p[nGLB]/D");
    rTree->Branch("glb_eta",      &glb_eta,       "glb_eta[nGLB]/D");
    rTree->Branch("glb_phi",      &glb_phi,       "glb_phi[nGLB]/D");
    rTree->Branch("glb_y",      &glb_y,       "glb_y[nGLB]/D");


    rTree->Branch("glb_dxy",      &glb_dxy,       "glb_dxy[nGLB]/D");
    rTree->Branch("glb_dz",       &glb_dz,        "glb_dz[nGLB]/D");

    rTree->Branch("glb_numberOfValidTrackerHits",       &glb_numberOfValidTrackerHits,        "glb_numberOfValidTrackerHits[nGLB]/I");
    rTree->Branch("glb_normalizedChi2",       		&glb_normalizedChi2,        	      "glb_normalizedChi2[nGLB]/D");

    rTree->Branch("nTRK",         &nTRK,          "nTRK/I");
    rTree->Branch("trk_pt",       &trk_pt,        "trk_pt[nTRK]/D");
    rTree->Branch("trk_p",        &trk_p,         "trk_p[nTRK]/D");
    rTree->Branch("trk_eta",      &trk_eta,       "trk_eta[nTRK]/D");
    rTree->Branch("trk_phi",      &trk_phi,       "trk_phi[nTRK]/D");
    rTree->Branch("trk_y",      &trk_y,       "trk_y[nTRK]/D");


    rTree->Branch("trk_dxy",      &trk_dxy,       "trk_dxy[nTRK]/D");
    rTree->Branch("trk_dz",       &trk_dz,        "trk_dz[nTRK]/D");


    rTree->Branch("nHLT_HIL2DoubleMu0",      &nHLT_HIL2DoubleMu0,      "nHLT_HIL2DoubleMu0/I");
    rTree->Branch("nHLT_HIL2DoubleMu0_Core", &nHLT_HIL2DoubleMu0_Core, "nHLT_HIL2DoubleMu0_Core/I");
    rTree->Branch("nHLT_HIL2Mu3",            &nHLT_HIL2Mu3,            "nHLT_HIL2Mu3/I");
    rTree->Branch("nHLT_HIL2Mu3_Core",       &nHLT_HIL2Mu3_Core,       "nHLT_HIL2Mu3_Core/I");
    rTree->Branch("nHLT_HIL2Mu5",            &nHLT_HIL2Mu5,            "nHLT_HIL2Mu5/I");
    rTree->Branch("nHLT_HIL2Mu5_Core",       &nHLT_HIL2Mu5_Core,       "nHLT_HIL2Mu5_Core/I");
    rTree->Branch("nHLT_HIL2Mu7",            &nHLT_HIL2Mu7,            "nHLT_HIL2Mu7/I");
    rTree->Branch("nHLT_HIL2Mu7_Core",       &nHLT_HIL2Mu7_Core,       "nHLT_HIL2Mu7_Core/I");

    rTree->Branch("nHLT_HIL1DoubleMuOpen",   &nHLT_HIL1DoubleMuOpen,   "nHLT_HIL1DoubleMuOpen/I");
    rTree->Branch("nHLT_HIL1SingleMuOpen",   &nHLT_HIL1SingleMuOpen,   "nHLT_HIL1SingleMuOpen/I");
    rTree->Branch("nHLT_HIL1SingleMu0",      &nHLT_HIL1SingleMu0,      "nHLT_HIL1SingleMu0/I");
    rTree->Branch("nHLT_HIL1SingleMu3",      &nHLT_HIL1SingleMu3,      "nHLT_HIL1SingleMu3/I");
    rTree->Branch("nHLT_HIL1SingleMu5",      &nHLT_HIL1SingleMu5,      "nHLT_HIL1SingleMu5/I");
    rTree->Branch("nHLT_HIL1SingleMu7",      &nHLT_HIL1SingleMu7,      "nHLT_HIL1SingleMu7/I");
    rTree->Branch("nHLT_HIL1SingleMu10",     &nHLT_HIL1SingleMu10,     "nHLT_HIL1SingleMu10/I");
    rTree->Branch("nHLT_HIMinBiasBSC",       &nHLT_HIMinBiasBSC,       "nHLT_HIMinBiasBSC/I");
    rTree->Branch("nHLT_HIMinBiasHF",        &nHLT_HIMinBiasHF,        "nHLT_HIMinBiasHF/I");

    rTree->Branch("nHLT_HIL1DoubleMu3",      &nHLT_HIL1DoubleMu3,      "nHLT_HIL1DoubleMu3/I");
    rTree->Branch("nHLT_HIL2DoubleMu0",      &nHLT_HIL2DoubleMu0,      "nHLT_HIL2DoubleMu0/I");
    rTree->Branch("nHLT_HIL2DoubleMu3",      &nHLT_HIL2DoubleMu3,      "nHLT_HIL2DoubleMu3/I");
    rTree->Branch("nHLT_HIL2Mu3",            &nHLT_HIL2Mu3,            "nHLT_HIL2Mu3/I");
    rTree->Branch("nHLT_HIL2Mu5",            &nHLT_HIL2Mu5,            "nHLT_HIL2Mu5/I");
    rTree->Branch("nHLT_HIL2Mu5Tight",       &nHLT_HIL2Mu5Tight,       "nHLT_HIL2Mu5Tight/I");
    rTree->Branch("nHLT_HIL2Mu7",            &nHLT_HIL2Mu7,            "nHLT_HIL2Mu7/I");
    rTree->Branch("nHLT_HIL2Mu9",            &nHLT_HIL2Mu9,            "nHLT_HIL2Mu9/I");
    rTree->Branch("nHLT_HIL2Mu11",           &nHLT_HIL2Mu11,           "nHLT_HIL2Mu11/I");
    rTree->Branch("nHLT_HIL2Mu11Central",    &nHLT_HIL2Mu11Central,    "nHLT_HIL2Mu11Central/I");
    rTree->Branch("nHLT_HIL2Mu11Tight",      &nHLT_HIL2Mu11Tight,      "nHLT_HIL2Mu11Tight/I");
    rTree->Branch("nHLT_HIL2Mu15",           &nHLT_HIL2Mu15,           "nHLT_HIL2Mu15/I");
    rTree->Branch("nHLT_HIL2Mu20",           &nHLT_HIL2Mu20,           "nHLT_HIL2Mu20/I");

    hPileUp = new TH1F("hPileUp","Number of Primary Vertices;n_{PV};counts", 50, 0, 50);
    hPileUp->Sumw2();

    hZVtx = new TH1F("hZVtx","Primary z-vertex distribution;z_{vtx} [cm];counts", 120, -30, 30);
    hZVtx->Sumw2();
}

//
// member functions
//

// ------------ method called to for each event  ------------
    void
HLTrgAna_trk::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace HepMC;

    const GenEvent* evt;

    // initialization

    l1mu_pt=-999;
    l1mu_phi=-999;
    l1mu_eta=-999;
    l1mu_ch=-999;
    l1mu_p=-999;
    l1mu_qual=-999;


    for (Int_t i=0; i<xNum; ++i) {

        p_Id[i]=-999;p_pt[i]=-999;p_y[i]=-999;p_eta[i]=-999;p_phi[i]=-999;p_st[i]=-999;p_mass[i]=-999;

        p_ch[i]=-999;
        p_vx[i]=-999;p_vy[i]=-999;p_vz[i]=-999;nMom[i]=-999;nDau[i]=-999;p_p[i]=-999;
        s_pt[i]=-999;s_p[i]=-999;
        s_phi[i]=-999;s_eta[i]=-999;s_ch[i]=-999;s_Id[i]=-999;s_st[i]=-999;
        glb_pt[i]=-999;glb_eta[i]=-999;glb_phi[i]=-999;glb_p[i]=-999;
        sta_pt[i]=-999;sta_eta[i]=-999;sta_phi[i]=-999;sta_p[i]=-999;
        rdmu_pt[i]=-999;rdmu_eta[i]=-999;rdmu_phi[i]=-999;rdmu_p[i]=-999;rdmu_mass[i]=-999;rdmu_y[i]=-999;
        sdmu_pt[i]=-999;sdmu_eta[i]=-999;sdmu_phi[i]=-999;sdmu_p[i]=-999;sdmu_mass[i]=-999;sdmu_y[i]=-999;
        rkids_pt[i][0]=-999;rkids_eta[i][0]=-999;rkids_phi[i][0]=-999;rkids_p[i][0]=-999;rkids_y[i][0]=-999;
        rkids_pt[i][1]=-999;rkids_eta[i][1]=-999;rkids_phi[i][1]=-999;rkids_p[i][1]=-999;rkids_y[i][1]=-999;
        skids_pt[i][0]=-999;skids_eta[i][0]=-999;skids_phi[i][0]=-999;skids_p[i][0]=-999;skids_y[i][0]=-999;
        skids_pt[i][1]=-999;skids_eta[i][1]=-999;skids_phi[i][1]=-999;skids_p[i][1]=-999;skids_y[i][1]=-999;
        gmu_Id[i]=-999;gmu_pt[i]=-999;gmu_y[i]=-999;gmu_eta[i]=-999;gmu_phi[i]=-999;gmu_st[i]=-999;gmu_mass[i]=-999;
        gmu_vx[i]=-999;gmu_vy[i]=-999;gmu_vz[i]=-999;nMom[i]=-999;nDau[i]=-999;gmu_p[i]=-999;gmu_ch[i]=-999;
        gmu_px[i]=-999;gmu_py[i]=-999;gmu_pz[i]=-999;

	glb_dxy[i]=-999;glb_dz[i]=-999;

        trk_pt[i]=-999;trk_eta[i]=-999;trk_phi[i]=-999;trk_p[i]=-999;trk_y[i]=-999;
	trk_dxy[i]=-999;trk_dz[i]=-999;


        for(Int_t j=0; j<yNum; ++j) {
            m_Id[i][j]=-999;m_pt[i][j]=-999;m_y[i][j]=-999;m_eta[i][j]=-999;m_phi[i][j]=-999;
            m_st[i][j]=-999;m_mass[i][j]=-999;m_vx[i][j]=-999;m_vy[i][j]=-999;m_vz[i][j]=-999;

            d_Id[i][j]=-999;d_pt[i][j]=-999;d_y[i][j]=-999;d_eta[i][j]=-999;d_phi[i][j]=-999;
            d_st[i][j]=-999;d_mass[i][j]=-999;d_vx[i][j]=-999;d_vy[i][j]=-999;d_vz[i][j]=-999;
            
            m_ch[i][j]=-999;d_ch[i][j]=-999;
        }

    }

// for primary vertex
	edm::Handle<reco::VertexCollection> privtxs;
	iEvent.getByLabel(_thePVs, privtxs);
	reco::VertexCollection::const_iterator privtx;

	nPV = privtxs->size();

	if ( privtxs->begin() != privtxs->end() ) {
 		privtx=privtxs->begin();
 		RefVtx = privtx->position();
	} else {
 		RefVtx.SetXYZ(0.,0.,0.);
 	}

	zVtx = RefVtx.Z();
	hZVtx->Fill(zVtx);

    if(MC_){
        // MC Truth Analysis
        Handle<GenParticleCollection> mctruth; 
        iEvent.getByLabel(genSource_, mctruth);

        nPar = 0;

        ngMu = 0;

        for(size_t i = 0; i < mctruth->size(); ++ i) {

            const Candidate & p = (*mctruth)[i];
            if (! &p ) continue;
            int id = p.pdgId();
            //cout<<"particle Id : "<<id<<endl;

            if(abs(id) == 13  || abs(id) == 443 || abs(id) == 553 || abs(id) == 23){

                // cout<<"I am the muon !!!!"<<endl;
                p_Id[nPar] = id;
                p_pt[nPar] = p.pt();
                p_y[nPar] = p.rapidity();
                p_eta[nPar]= p.eta();
                p_phi[nPar] = p.phi();
                p_mass[nPar] = p.mass();
                p_st[nPar] = p.status();
                p_vx[nPar] = p.vx();
                p_vy[nPar] = p.vy();
                p_vz[nPar] = p.vz();
                p_p[nPar] = p.p();
                p_ch[nPar] = p.charge();
                nmom = p.numberOfMothers();
                nMom[nPar] = nmom;

                nmom = p.numberOfMothers();

                for(int j=0; j<nmom;++j){
                    const Candidate * mom = p.mother(j);
                    if (!mom) continue;
                    m_Id[nPar][j] = mom->pdgId();
                    m_pt[nPar][j] = mom->pt();
                    m_y[nPar][j] = mom->rapidity();
                    m_eta[nPar][j] = mom->eta();
                    m_phi[nPar][j] = mom->phi();
                    m_st[nPar][j] = mom->status();
                    m_mass[nPar][j] = mom->mass();
                    m_vx[nPar][j] = mom->vx();
                    m_vy[nPar][j] = mom->vy();
                    m_vz[nPar][j] = mom->vz();
                    m_ch[nPar][j] = mom->charge();
                    //++nMom;

                }

                ndau = p.numberOfDaughters();

                nDau[nPar] = ndau;

                for(int l=0; l<ndau;l++){
                    const Candidate * dau = p.daughter(l);
                    d_Id[nPar][l] = dau->pdgId();
                    d_pt[nPar][l] = dau->pt();
                    d_y[nPar][l] = dau->rapidity();
                    d_eta[nPar][l]=dau->eta();
                    d_phi[nPar][l] = dau->phi();
                    d_st[nPar][l] = dau->status();
                    d_vx[nPar][l] = dau->vx();
                    d_vy[nPar][l] = dau->vy();
                    d_vz[nPar][l] = dau->vz();
                    d_ch[nPar][l] = dau->charge();
                    //++nDau;
                }
                // muon
                if (abs(id) == 13) {
                    gmu_Id[ngMu] = id;
                    gmu_pt[ngMu] = p.pt();
                    gmu_y[ngMu] = p.rapidity();
                    gmu_eta[ngMu]= p.eta();
                    gmu_phi[ngMu] = p.phi();
                    gmu_mass[ngMu] = p.mass();
                    gmu_st[ngMu] = p.status();
                    gmu_vx[ngMu] = p.vx();
                    gmu_vy[ngMu] = p.vy();
                    gmu_vz[ngMu] = p.vz();
                    gmu_p[ngMu] = p.p();
                    gmu_ch[ngMu] = p.charge();
                    gmu_px[ngMu] = p.px();
                    gmu_py[ngMu] = p.py();
                    gmu_pz[ngMu] = p.pz();
                    //gmu_npar[ngMu] = nPar;
                    ++ngMu;
                }

                ++nPar;

            }


        }
        ngdimu=0;

        for (int mu1=0;mu1<ngMu-1;++mu1){
            for (int mu2=mu1+1;mu2<ngMu;++mu2){
                if (gmu_ch[mu1]*gmu_ch[mu2]>0) continue;

                cout << "mu1: " << mu1 << "mu2: " << mu2 << endl;
                cout << "gmu_p[mu1]: " << gmu_p[mu1] << "gmu_p[mu2]: " << gmu_p[mu2] << endl;

                double gdimu_en1 = sqrt(gmu_p[mu1]*gmu_p[mu1]+m_mu*m_mu);
                double gdimu_en2 = sqrt(gmu_p[mu2]*gmu_p[mu2]+m_mu*m_mu);

                TLorentzVector gdkidv1, gdkidv2;

                gdkidv1.SetPxPyPzE(gmu_px[mu1],gmu_py[mu1],gmu_pz[mu1],gdimu_en1);
                gdkidv2.SetPxPyPzE(gmu_px[mu2],gmu_py[mu2],gmu_pz[mu2],gdimu_en2);

                TLorentzVector gdimuon;
                gdimuon = gdkidv1 + gdkidv2;
                
                cout << "gdimuon.Pt(): " << gdimuon.Pt() << endl;
                gdimu_pt[ngdimu]=gdimuon.Pt();gdimu_p[ngdimu]=gdimuon.P();gdimu_eta[ngdimu]=gdimuon.Eta();gdimu_y[ngdimu]=gdimuon.Rapidity();
                gdimu_phi[ngdimu]=gdimuon.Phi();gdimu_mass[ngdimu]=gdimuon.M();

                gdkid_pt[ngdimu][0]=gmu_pt[mu1];gdkid_eta[ngdimu][0]=gmu_eta[mu1];gdkid_phi[ngdimu][0]=gmu_phi[mu1];gdkid_p[ngdimu][0]=gmu_p[mu1];gdkid_y[ngdimu][0]=gmu_y[mu1];
                gdkid_pt[ngdimu][1]=gmu_pt[mu2];gdkid_eta[ngdimu][1]=gmu_eta[mu2];gdkid_phi[ngdimu][1]=gmu_phi[mu2];gdkid_p[ngdimu][1]=gmu_p[mu2];gdkid_y[ngdimu][1]=gmu_y[mu2];
                ngdimu++;

            }

        }

    }

    if(SIM_){
        // Simulation Analysis
        TrackingParticleCollection trackingParticles;
        edm::Handle<TrackingParticleCollection> SimMuons;
        iEvent.getByLabel("mergedtruth","MergedTrackTruth",SimMuons);
        int nSimMu = 0;

        if(SimMuons.isValid()){
            const TrackingParticleCollection trackingParticles = *(SimMuons.product());
            for(TrackingParticleCollection::const_iterator t = trackingParticles.begin(), tEnd = trackingParticles.end(); t != tEnd; ++t){
                //cout<<"sim id : "<<(*t).pdgId()<<endl;
                if(abs( (*t).pdgId() ) == 13 && abs((*t).eta()) < 2.5 ) { 
                    //cout<<"I am sim muon !!!!!"<<endl; 
                    nSimMu++;
                    //cout<<nSimMu<<". sim id : "<<(*t).pdgId()<<", status : "<<(*t).status()<<endl;
                    s_Id[nSimMu] = (*t).pdgId();s_pt[nSimMu] = (*t).pt();s_ch[nSimMu] = (*t).charge();s_p[nSimMu] = (*t).p();
                    s_eta[nSimMu] = (*t).eta();s_phi[nSimMu] = (*t).phi();s_st[nSimMu] = (*t).status();
                }   

            }   


        }

        nSMu = nSimMu;
        nGMu = nPar;
        //cout<<"nGMu : "<<nGMu<<", nPar : "<<nPar<<", nSMu : "<<nSMu<<endl;
        if(nGMu == 0) nGMu = -1;
        if(nSMu == 0) nSMu = -1;
    }

    if(HiMC_){
        // General Run info
        Imp = -1.0;
        Handle<HepMCProduct> mc;
        iEvent.getByLabel("generator",mc);

        evt = mc->GetEvent();
        const HeavyIon* hi = evt->heavy_ion();

        if(hi){
            Imp = hi->impact_parameter();
            nPart = hi->Npart_proj()+hi->Npart_targ();
            nColl = hi->Ncoll();
            nHard = hi->Ncoll_hard();
            //cout<<"Impact parameter : "<<nImp<<endl;

        }
    }

    Evt = iEvent.id().event();
    Run = iEvent.id().run();

    if(L1_TRG_){
        // Trigger Analysis
        std::string L1Path0, L1Path1, L1Path2, L1Path3, L1Path4, L1Path5, L1Path6, L1Path7;
        L1Path0 = "L1_DoubleMuOpen";
        L1Path1 = "L1_DoubleMu3";
        L1Path2 = "L1_SingleMuOpen";
        L1Path3 = "L1_SingleMu0";
        L1Path4 = "L1_SingleMu3";
        L1Path5 = "L1_SingleMu5";
        L1Path6 = "L1_SingleMu7";
        L1Path7 = "L1_SingleMu10";

        Handle<L1GlobalTriggerReadoutRecord> L1GTRR;
        iEvent.getByLabel("hltGtDigis",L1GTRR);

        Handle<L1GlobalTriggerObjectMapRecord> L1GTOMRec;
        iEvent.getByLabel("hltL1GtObjectMap",L1GTOMRec);

        DecisionWord gtDecisionWord = L1GTRR->decisionWord();
        string l1BitName;
        int l1Acc;
        int l1Acc0 = 0, l1Acc1 = 0, l1Acc2 = 0, l1Acc3 = 0, l1Acc4 = 0, l1Acc5 = 0, l1Acc6 = 0, l1Acc7 = 0;

        // get ObjectMaps from ObjectMapRecord
        const vector<L1GlobalTriggerObjectMap>& objMapVec =  L1GTOMRec->gtObjectMap();
        for (vector<L1GlobalTriggerObjectMap>::const_iterator itMap = objMapVec.begin();itMap != objMapVec.end(); ++itMap) {
            int iBit = (*itMap).algoBitNumber();
            l1BitName = string( (*itMap).algoName() );
            l1Acc = gtDecisionWord[iBit];
            if(l1BitName == L1Path0 && l1Acc == 1) {cout<<"This is "<<l1BitName<<" !!!"<<" Fired"<<endl;l1Acc0 = 1;}
            if(l1BitName == L1Path1 && l1Acc == 1) {cout<<"This is "<<l1BitName<<" !!!"<<" Fired"<<endl;l1Acc1 = 1;}
            if(l1BitName == L1Path2 && l1Acc == 1) {cout<<"This is "<<l1BitName<<" !!!"<<" Fired"<<endl;l1Acc2 = 1;}
            if(l1BitName == L1Path3 && l1Acc == 1) {cout<<"This is "<<l1BitName<<" !!!"<<" Fired"<<endl;l1Acc3 = 1;}
            if(l1BitName == L1Path4 && l1Acc == 1) {cout<<"This is "<<l1BitName<<" !!!"<<" Fired"<<endl;l1Acc4 = 1;}
            if(l1BitName == L1Path5 && l1Acc == 1) {cout<<"This is "<<l1BitName<<" !!!"<<" Fired"<<endl;l1Acc5 = 1;}
            if(l1BitName == L1Path6 && l1Acc == 1) {cout<<"This is "<<l1BitName<<" !!!"<<" Fired"<<endl;l1Acc6 = 1;}
            if(l1BitName == L1Path7 && l1Acc == 1) {cout<<"This is "<<l1BitName<<" !!!"<<" Fired"<<endl;l1Acc7 = 1;}
        }
        nL1Acc0 = l1Acc0; nL1Acc1 = l1Acc1; nL1Acc2 = l1Acc2; nL1Acc3 = l1Acc3; nL1Acc4 = l1Acc4; nL1Acc5 = l1Acc5; nL1Acc6 = l1Acc6; nL1Acc7 = l1Acc7;

        Handle< vector<l1extra::L1MuonParticle> > l1muons;
        iEvent.getByLabel("hltL1extraParticles", l1muons);
        l1extra::L1MuonParticleCollection::const_iterator l1_it = l1muons->begin() ;
        l1extra::L1MuonParticleCollection::const_iterator muEnd = l1muons->end() ;


        nL1Mu = l1muons->size();
        for( size_t i = 0 ; l1_it != muEnd ; ++l1_it, ++i )
        {
            const l1extra::L1MuonParticle & l1mu = (*l1muons)[i];

            l1mu_ch=l1mu.charge(); 
            l1mu_pt=l1mu.pt();
            l1mu_eta=l1mu.eta();
            l1mu_phi=l1mu.phi(); 
            l1mu_p=l1mu.p();
            l1mu_qual = l1_it->gmtMuonCand().quality();

            if(nL1Mu>= 2){
                if((*l1_it).pt()>0 && abs((*l1_it).eta())<2.5){
                    unsigned int qual = l1_it->gmtMuonCand().quality() ;
                    if( qual ==2 || qual == 4 || qual == 5 || qual == 6 ||
                            qual == 7 )
                    {
                        nL1Acc_DoubleMuOpenQual4=1;
                    }

                    if(qual == 4 || qual == 5 || qual == 6 || qual == 7 ){
                        if((*l1_it).pt()>=3){
                            nL1Acc_DoubleMu3Qual4=1;
                        }
                    }
                }
            }
            // Fake rate Analysis
            nFRate = (double)nL1Mu/nGMu;
            nFRateSim = (double)nL1Mu/nSMu;

        }
    }
    if(HLT_){
        Handle<TriggerResults> trigResults;
        iEvent.getByLabel(triggerResults_,trigResults);

        TriggerNames triggerNames_;

        std::string HLT_HIDoubleMuOpen     = "HLT_HIDoubleMuOpen";

        std::string HLT_HIL1DoubleMuOpen   = "HLT_HIL1DoubleMuOpen";
        std::string HLT_HIL1SingleMuOpen   = "HLT_HIL1SingleMuOpen";
        std::string HLT_HIL1SingleMu0      = "HLT_HIL1SingleMu0";
        std::string HLT_HIL1SingleMu3      = "HLT_HIL1SingleMu3";
        std::string HLT_HIL1SingleMu5      = "HLT_HIL1SingleMu5";
        std::string HLT_HIL1SingleMu7      = "HLT_HIL1SingleMu7";
        std::string HLT_HIL1SingleMu10     = "HLT_HIL1SingleMu10";

        std::string HLT_HIMinBiasBSC       = "HLT_HIMinBiasBSC";
        std::string HLT_HIMinBiasHF        = "HLT_HIMinBiasHF";

        // L1 DoubleMu3 and L2 Path
        std::string HLT_HIL1DoubleMu3      = "HLT_HIL1DoubleMu3";
        std::string HLT_HIL2DoubleMu0      = "HLT_HIL2DoubleMu0";
        std::string HLT_HIL2DoubleMu3      = "HLT_HIL2DoubleMu3";
        std::string HLT_HIL2Mu3            = "HLT_HIL2Mu3";
        std::string HLT_HIL2Mu5            = "HLT_HIL2Mu5";
        std::string HLT_HIL2Mu5Tight       = "HLT_HIL2Mu5Tight";
        std::string HLT_HIL2Mu7            = "HLT_HIL2Mu7";
        std::string HLT_HIL2Mu9            = "HLT_HIL2Mu9";
        std::string HLT_HIL2Mu11           = "HLT_HIL2Mu11";
        std::string HLT_HIL2Mu11Central    = "HLT_HIL2Mu11Central";
        std::string HLT_HIL2Mu11Tight      = "HLT_HIL2Mu11Tight";
        std::string HLT_HIL2Mu15           = "HLT_HIL2Mu15";
        std::string HLT_HIL2Mu20           = "HLT_HIL2Mu20";

        int nH1 = 0, nH2 = 0, nH3 = 0, nH4 = 0, nH5 = 0; 
        int nH6 = 0, nH7 = 0, nH8 = 0, nH9 = 0, nH10 = 0, nH11 = 0, nH12 = 0;

        int nL1D3 = 0, nL2D0 = 0, nL2D3 = 0, nL2S3 = 0, nL2S5 = 0, nL2S5T = 0;
        int nL2S7 = 0, nL2S9 = 0, nL2S11 = 0, nL2S15 = 0, nL2S20 = 0;
        int nL2S11T = 0, nL2S11C = 0;

        if (trigResults.isValid()) {
            int ntrigs = trigResults->size();
            if (ntrigs==0){std::cout << "%HLTInfo -- No trigger name given in TriggerResults of the input " << std::endl;}

            edm::TriggerNames const& triggerNames = iEvent.triggerNames(*trigResults);

            //std::cout << "Number of prescale sets: " << hltConfig_.prescaleSize() << std::endl;
            //std::cout << "Number of HLT paths: " << hltConfig_.size() << std::endl;
            //int presclSet = hltConfig_.prescaleSet(iEvent, eventSetup);
            //std::cout<<"\tPrescale set number: "<< presclSet <<std::endl; 
            //cout<<"hlt is ok !!!!"<<endl;

            for (int itrig = 0; itrig != ntrigs; ++itrig){

                std::string trigName=triggerNames.triggerName(itrig);
                bool accept = trigResults->accept(itrig);
                //std::cout << "%HLTInfo --  Name of HLT Triggers: " << trigName << std::endl;

                if (accept) {
                    //                    cout<<"%HLTInfo -- "<<trigName<<" : accepted !!!!!"<<endl;

                    //std::cout << "%HLTInfo --  Number of HLT Triggers: " << ntrigs << std::endl;
                    //std::cout << "%HLTInfo --  HLTTrigger(" << itrig << "): " << trigName << " = " << accept << std::endl;
                    if(trigName == HLT_HIL2DoubleMu0){ cout<<"%HLTInfo : "<<trigName<<" is fired !!!!"<<endl; nH1 = 1;}
                    if(trigName == HLT_HIL2Mu3){ cout<<"%HLTInfo : "<<trigName<<" is fired !!!!"<<endl; nH2 = 1;}
                    if(trigName == HLT_HIL2Mu5){ cout<<"%HLTInfo : "<<trigName<<" is fired !!!!"<<endl; nH3 = 1;}
                    if(trigName == HLT_HIL2Mu7){ cout<<"%HLTInfo : "<<trigName<<" is fired !!!!"<<endl; nH4 = 1;}
                    if(trigName == HLT_HIL1DoubleMuOpen){ cout<<"%HLTInfo : "<<trigName<<" is fired !!!!"<<endl; nH5 = 1;}
                    if(trigName == HLT_HIL1SingleMuOpen){ cout<<"%HLTInfo : "<<trigName<<" is fired !!!!"<<endl; nH6 = 1;}
                    if(trigName == HLT_HIL1SingleMu3){ cout<<"%HLTInfo : "<<trigName<<" is fired !!!!"<<endl; nH7 = 1;}
                    if(trigName == HLT_HIL1SingleMu5){ cout<<"%HLTInfo : "<<trigName<<" is fired !!!!"<<endl; nH8 = 1;}
                    if(trigName == HLT_HIL1SingleMu7){ cout<<"%HLTInfo : "<<trigName<<" is fired !!!!"<<endl; nH9 = 1;}
                    if(trigName == HLT_HIL1SingleMu10){ cout<<"%HLTInfo : "<<trigName<<" is fired !!!!"<<endl; nH10 = 1;}
                    if(trigName == HLT_HIMinBiasHF){ cout<<"%HLTInfo : "<<trigName<<" is fired !!!!"<<endl; nH11 = 1;}
                    if(trigName == HLT_HIMinBiasBSC){ cout<<"%HLTInfo : "<<trigName<<" is fired !!!!"<<endl; nH12 = 1;}
                    // L1 DoubleMu3, L2 Path
                    if(trigName == HLT_HIL1DoubleMu3){ cout<<"%HLTInfo : "<<trigName<<" is fired !!!!"<<endl; nL1D3 = 1;}
                    if(trigName == HLT_HIL2DoubleMu0){ cout<<"%HLTInfo : "<<trigName<<" is fired !!!!"<<endl; nL2D0 = 1;}
                    if(trigName == HLT_HIL2DoubleMu3){ cout<<"%HLTInfo : "<<trigName<<" is fired !!!!"<<endl; nL2D3 = 1;}
                    if(trigName == HLT_HIL2Mu3){ cout<<"%HLTInfo : "<<trigName<<" is fired !!!!"<<endl; nL2S3 = 1;}
                    if(trigName == HLT_HIL2Mu5){ cout<<"%HLTInfo : "<<trigName<<" is fired !!!!"<<endl; nL2S5 = 1;}
                    if(trigName == HLT_HIL2Mu5Tight){ cout<<"%HLTInfo : "<<trigName<<" is fired !!!!"<<endl; nL2S5T = 1;}
                    if(trigName == HLT_HIL2Mu7){ cout<<"%HLTInfo : "<<trigName<<" is fired !!!!"<<endl; nL2S7 = 1;}
                    if(trigName == HLT_HIL2Mu9){ cout<<"%HLTInfo : "<<trigName<<" is fired !!!!"<<endl; nL2S9 = 1;}
                    if(trigName == HLT_HIL2Mu11){ cout<<"%HLTInfo : "<<trigName<<" is fired !!!!"<<endl; nL2S11 = 1;}
                    if(trigName == HLT_HIL2Mu11Central){ cout<<"%HLTInfo : "<<trigName<<" is fired !!!!"<<endl; nL2S11C = 1;}
                    if(trigName == HLT_HIL2Mu11Tight){ cout<<"%HLTInfo : "<<trigName<<" is fired !!!!"<<endl; nL2S11T = 1;}
                    if(trigName == HLT_HIL2Mu15){ cout<<"%HLTInfo : "<<trigName<<" is fired !!!!"<<endl; nL2S15 = 1;}
                    if(trigName == HLT_HIL2Mu20){ cout<<"%HLTInfo : "<<trigName<<" is fired !!!!"<<endl; nL2S20 = 1;}
                }
            }
        }else{cout<<"HLT Info is not ok !!!!!"<<endl;}

        nHLT_HIL2DoubleMu0 = nH1; nHLT_HIL2Mu3 = nH2; 
        nHLT_HIL2Mu5 = nH3; nHLT_HIL2Mu7 = nH4;  
        nHLT_HIL1SingleMuOpen = nH6; nHLT_HIL1SingleMu3 = nH7; nHLT_HIL1SingleMu5 = nH8;
        nHLT_HIL1SingleMu7 = nH9; nHLT_HIL1SingleMu10 = nH10; nHLT_HIL1DoubleMuOpen = nH5;
        nHLT_HIMinBiasHF = nH11; nHLT_HIMinBiasBSC = nH12;
        nHLT_HIL1DoubleMu3 = nL1D3; nHLT_HIL2DoubleMu0 = nL2D0; nHLT_HIL2DoubleMu3 = nL2D3;
        nHLT_HIL2Mu3 = nL2S3; nHLT_HIL2Mu5 = nL2S5; nHLT_HIL2Mu5Tight = nL2S5T; nHLT_HIL2Mu7 = nL2S7;
        nHLT_HIL2Mu9 = nL2S9; nHLT_HIL2Mu11 = nL2S11; nHLT_HIL2Mu15 = nL2S15; nHLT_HIL2Mu20 = nL2S20;
        nHLT_HIL2Mu11Central = nL2S11C; nHLT_HIL2Mu11Tight = nL2S11T;
    }

    if(RECO_){
        // Reco analysis
        // Reco Single Muon Ana
        edm::Handle<edm::View<reco::Track> >STAmuons;
        iEvent.getByLabel(staMuons_,STAmuons);
        //iEvent.getByLabel("standAloneMuons",STAmuons);
        //iEvent.getByLabel("standAloneMuons","","UpdatedAtVtx",STAmuons);

        int rDMu = 0, rSDMu = 0, rTDMu=0, rGLB = 0, rSTA = 0, rTRK = 0;
        //       if(STAmuons.isValid() && STAmuons.product()->size() >1 ){
        if(STAmuons.isValid() && STAmuons.product()->size() >0 ){
            for(edm::View<reco::Track> ::size_type i=0; i < STAmuons.product()->size(); i++){
                edm::RefToBase<reco::Track> STAmu(STAmuons, i);
                if(STAmu.isNull()) continue;
                sta_pt[rSTA]=STAmu->pt();sta_phi[rSTA]=STAmu->phi();sta_p[rSTA]=STAmu->p();sta_eta[rSTA]=STAmu->eta();
		sta_y[rSTA]=Getrapidity(STAmu->p(),STAmu->pz(),m_mu);
                rSTA++;
            }
        }
        //nSTA = rSTA;
        nSTA = STAmuons.product()->size();

        edm::Handle<edm::View<reco::Track> >muonCollection;
        iEvent.getByLabel(muTrackTag_,muonCollection);
        cout<<"Reco muon size : "<<muonCollection->size()<<endl;

        //        if(muonCollection.isValid() && muonCollection.product()->size() >1 ){
        if(muonCollection.isValid() && muonCollection.product()->size() >0 ){
            for(edm::View<reco::Track> ::size_type i=0; i < muonCollection.product()->size(); i++){
                edm::RefToBase<reco::Track> GLBmu(muonCollection, i);
                if ( GLBmu.isNull() ) continue;
		//reco::TrackRef iTrack = GLBmu->innerTrack();
		//const edm::RefToBase<reco::Track>& trkRef;
		const reco::HitPattern& hp = GLBmu.get()->hitPattern();
		//if ( GLBmu.isGlobalMuon() ) {
                  glb_pt[rGLB]=GLBmu->pt();glb_phi[rGLB]=GLBmu->phi();glb_p[rGLB]=GLBmu->p();glb_eta[rGLB]=GLBmu->eta();
		  glb_y[rGLB]=Getrapidity(GLBmu->p(),GLBmu->pz(),m_mu);

    		  glb_dxy[rGLB]=GLBmu->dxy(RefVtx);glb_dz[rGLB]=GLBmu->dz(RefVtx);

		  glb_numberOfValidTrackerHits[rGLB]=hp.numberOfValidTrackerHits();
		  glb_normalizedChi2[rGLB]=GLBmu->normalizedChi2();

                  rGLB++;
		//}
/*
*/
            }

        }
        nGLB = rGLB;
        //nGLB = muonCollection.product()->size();

//////////////////
	edm::Handle<edm::View<reco::Muon> > muons;
	iEvent.getByLabel("muons",muons);
 	for (unsigned int j=0; j<muons->size(); ++j)
	{
		edm::RefToBase<reco::Muon> muCandRef(muons,j);
		if (muCandRef.isNull()) continue;
		if (muCandRef->isStandAloneMuon()) 
			std::cout << "* I am StandAloneMuon ***" << std::endl;
		if (muCandRef->isGlobalMuon()) 
			std::cout << "*** I am GlobalMuon ***" << std::endl;
		if (muCandRef->isTrackerMuon()) {
			std::cout << "***** I am TrackerMuon ***" << std::endl;
                	trk_pt[rTRK]=muCandRef->innerTrack()->pt();trk_phi[rTRK]=muCandRef->innerTrack()->phi();trk_p[rTRK]=muCandRef->innerTrack()->p();
			trk_eta[rTRK]=muCandRef->innerTrack()->eta();
			trk_y[rTRK]=Getrapidity(muCandRef->innerTrack()->p(),muCandRef->innerTrack()->pz(),m_mu);    		  	
			trk_dxy[rTRK]=muCandRef->innerTrack()->dxy(RefVtx);trk_dz[rTRK]=muCandRef->innerTrack()->dz(RefVtx);
                  	rTRK++;
		}
}
	nTRK = rTRK;

//////////////
        // Reco Dimuon Ana
        // Dimuon from STA
        if(STAmuons.isValid() && STAmuons.product()->size() >1 )
        {
            //cout<<"Reco muon size : "<<STAmuons.product()->size()<<endl;
            for(edm::View<reco::Track> ::size_type i=0; i < STAmuons.product()->size()-1; i++)
            {
                edm::RefToBase<reco::Track> STAmu1(STAmuons, i);
                if ( STAmu1.isNull() ) continue;

                for(edm::View<reco::Track> ::size_type j=i+1; j < STAmuons.product()->size(); j++)
                {
                    edm::RefToBase<reco::Track> STAmu2(STAmuons, j);
                    if ( STAmu2.isNull() ) continue;

                    // only opposite sign dimuons
                    if(STAmu1->charge() * STAmu2->charge()>0) continue;
                    sdmu_ch[rSDMu]=STAmu1->charge() * STAmu2->charge();

                    TLorentzVector kid1, kid2;
                    double en1 = sqrt(STAmu1->p()*STAmu1->p()+m_mu*m_mu);
                    double en2 = sqrt(STAmu2->p()*STAmu2->p()+m_mu*m_mu);

                    kid1.SetPxPyPzE(STAmu1->px(),STAmu1->py(),STAmu1->pz(),en1);
                    kid2.SetPxPyPzE(STAmu2->px(),STAmu2->py(),STAmu2->pz(),en2);

                    TLorentzVector dimuon;
                    dimuon = kid1 + kid2;
                    sdmu_pt[rSDMu]=dimuon.Pt();sdmu_p[rSDMu]=dimuon.P();sdmu_eta[rSDMu]=dimuon.Eta();
                    sdmu_phi[rSDMu]=dimuon.Phi();sdmu_mass[rSDMu]=dimuon.M();sdmu_y[rSDMu]=dimuon.Rapidity(); 
                    skids_pt[rSDMu][0]=STAmu1->pt();skids_eta[rSDMu][0]=STAmu1->eta();skids_phi[rSDMu][0]=STAmu1->phi();skids_p[rSDMu][0]=STAmu1->p();
		    skids_y[rSDMu][0]=Getrapidity(STAmu1->p(),STAmu1->pz(),m_mu);
                    skids_pt[rSDMu][1]=STAmu2->pt();skids_eta[rSDMu][1]=STAmu2->eta();skids_phi[rSDMu][1]=STAmu2->phi();skids_p[rSDMu][0]=STAmu1->p();
		    skids_y[rSDMu][1]=Getrapidity(STAmu2->p(),STAmu2->pz(),m_mu);

                    cout<<"STA DiMuon Mass : "<<sdmu_mass[rSDMu]<<endl;
                    cout<<"STA skids 1 pt : "<<skids_pt[rSDMu][0]<<endl;
                    cout<<"STA skids 2 pt : "<<skids_pt[rSDMu][1]<<endl;

                    rSDMu++;

                }//2nd muon loop
            }// 1st muon loop
        }// muonCollectino is valid and has more than 2 muons reconstructed
        nSDMu = rSDMu;
//////////////////////////////////////////
	// Dimuon from TRK
	if(muons.isValid() && muons.product()->size()>1)
	{
	    for(edm::View<reco::Muon> ::size_type i=0; i < muons.product()->size()-1; i++)
	    {
                edm::RefToBase<reco::Muon> trkmu1(muons, i);
                if ( trkmu1.isNull() || !(trkmu1->isTrackerMuon())) continue;
                for(edm::View<reco::Muon> ::size_type j=i+1; j < muons.product()->size(); j++)
                {
                    edm::RefToBase<reco::Muon> trkmu2(muons, j);
                    if ( trkmu2.isNull() || !(trkmu2->isTrackerMuon())) continue;

                    // only opposite sign dimuons
                    if(trkmu1->innerTrack()->charge() * trkmu2->innerTrack()->charge()>0) continue;
                    tdmu_ch[rTDMu]=trkmu1->innerTrack()->charge() * trkmu2->innerTrack()->charge();

                    TLorentzVector tkid1, tkid2;
                    double ent1 = sqrt(trkmu1->innerTrack()->p()*trkmu1->innerTrack()->p()+m_mu*m_mu);
                    double ent2 = sqrt(trkmu2->innerTrack()->p()*trkmu2->innerTrack()->p()+m_mu*m_mu);

                    tkid1.SetPxPyPzE(trkmu1->innerTrack()->px(),trkmu1->innerTrack()->py(),trkmu1->innerTrack()->pz(),ent1);
                    tkid2.SetPxPyPzE(trkmu2->innerTrack()->px(),trkmu2->innerTrack()->py(),trkmu2->innerTrack()->pz(),ent2);

                    TLorentzVector dimuontrk;
                    dimuontrk = tkid1 + tkid2;
                    tdmu_pt[rTDMu]=dimuontrk.Pt();tdmu_p[rTDMu]=dimuontrk.P();tdmu_eta[rTDMu]=dimuontrk.Eta();
                    tdmu_phi[rTDMu]=dimuontrk.Phi();tdmu_mass[rTDMu]=dimuontrk.M();tdmu_y[rTDMu]=dimuontrk.Rapidity(); 
                    tkids_pt[rTDMu][0]=trkmu1->innerTrack()->pt();tkids_eta[rTDMu][0]=trkmu1->innerTrack()->eta();tkids_phi[rTDMu][0]=trkmu1->innerTrack()->phi();tkids_p[rTDMu][0]=trkmu1->innerTrack()->p();
		    tkids_y[rTDMu][0]=Getrapidity(trkmu1->innerTrack()->p(), trkmu1->innerTrack()->pz(), m_mu);
                    tkids_pt[rTDMu][1]=trkmu2->innerTrack()->pt();tkids_eta[rTDMu][1]=trkmu2->innerTrack()->eta();tkids_phi[rTDMu][1]=trkmu2->innerTrack()->phi();tkids_p[rTDMu][1]=trkmu2->innerTrack()->p();
		    tkids_y[rTDMu][1]=Getrapidity(trkmu2->innerTrack()->p(), trkmu2->innerTrack()->pz(), m_mu);


                    cout<<"TRK DiMuon Mass : "<<tdmu_mass[rTDMu]<<endl;
                    cout<<"TRK rkids 1 pt : "<<tkids_pt[rTDMu][0]<<endl;
                    cout<<"TRK rkids 2 pt : "<<tkids_pt[rTDMu][1]<<endl;

                    rTDMu++;

                }//2nd muon loop
             }// 1st muon loop
        }// muonCollection is valid and has more than 2 muons reconstructed
        nTDMu = rTDMu;
///////////////////////////////////////
        // Dimuon from GLB
        if(muonCollection.isValid() && muonCollection.product()->size() >1 )
        {
            //cout<<"Reco muon size : "<<muonCollection.product()->size()<<endl;
            for(edm::View<reco::Track> ::size_type i=0; i < muonCollection.product()->size()-1; i++)
            {
                edm::RefToBase<reco::Track> muTrack1(muonCollection, i);
                if ( muTrack1.isNull() ) continue;

                for(edm::View<reco::Track> ::size_type j=i+1; j < muonCollection.product()->size(); j++)
                {
                    edm::RefToBase<reco::Track> muTrack2(muonCollection, j);
                    if ( muTrack2.isNull() ) continue;

                    // only opposite sign dimuons
                    if(muTrack1->charge() * muTrack2->charge()>0) continue;
                    rdmu_ch[rDMu]=muTrack1->charge() * muTrack2->charge();

                    TLorentzVector kid1, kid2;
                    double en1 = sqrt(muTrack1->p()*muTrack1->p()+m_mu*m_mu);
                    double en2 = sqrt(muTrack2->p()*muTrack2->p()+m_mu*m_mu);

                    kid1.SetPxPyPzE(muTrack1->px(),muTrack1->py(),muTrack1->pz(),en1);
                    kid2.SetPxPyPzE(muTrack2->px(),muTrack2->py(),muTrack2->pz(),en2);

                    TLorentzVector dimuon;
                    dimuon = kid1 + kid2;
                    rdmu_pt[rDMu]=dimuon.Pt();rdmu_p[rDMu]=dimuon.P();rdmu_eta[rDMu]=dimuon.Eta();
                    rdmu_phi[rDMu]=dimuon.Phi();rdmu_mass[rDMu]=dimuon.M();rdmu_y[rDMu]=dimuon.Rapidity(); 
                    rkids_pt[rDMu][0]=muTrack1->pt();rkids_eta[rDMu][0]=muTrack1->eta();rkids_phi[rDMu][0]=muTrack1->phi();rkids_p[rDMu][0]=muTrack1->p();
		    rkids_y[rDMu][0]=Getrapidity(muTrack1->p(), muTrack1->pz(), m_mu);
                    rkids_pt[rDMu][1]=muTrack2->pt();rkids_eta[rDMu][1]=muTrack2->eta();rkids_phi[rDMu][1]=muTrack2->phi();rkids_p[rDMu][1]=muTrack2->p();
		    rkids_y[rDMu][1]=Getrapidity(muTrack2->p(), muTrack2->pz(), m_mu);


                    cout<<"GLB DiMuon Mass : "<<rdmu_mass[rDMu]<<endl;
                    cout<<"GLB rkids 1 pt : "<<rkids_pt[rDMu][0]<<endl;
                    cout<<"GLB rkids 2 pt : "<<rkids_pt[rDMu][1]<<endl;

                    rDMu++;

                }//2nd muon loop
            }// 1st muon loop
        }// muonCollectino is valid and has more than 2 muons reconstructed
        nRDMu = rDMu;
        cout<<"N of GlobalMuons : "<<nGLB<<", N of StandAlone Muons : "<<nSTA<<", N of Track Muons : "<<nTRK<<endl;
    }
    rTree->Fill();

    }

    double HLTrgAna_trk::Getrapidity(double p, double pz, double mass) {
	double energyreco = sqrt(p*p+mass*mass);
	double rapidityreco = 0.5*log((energyreco+pz)/(energyreco-pz));
	return rapidityreco;
}

    void HLTrgAna_trk::endLuminosityBlock(const edm::LuminosityBlock &lumiBlock, const edm::EventSetup &iSetup){

        edm::Handle<LumiSummary> lumiSummary;
        lumiBlock.getByLabel("lumiProducer",lumiSummary);

        Lumi = lumiBlock.id().luminosityBlock();
    }

    // ------------ method called once each job just after ending the event loop  ------------
    void 
        HLTrgAna_trk::endJob() {

            hOutputFile->SetCompressionLevel(2);
            hOutputFile->cd();
	    hZVtx->Write();
            hOutputFile->Write();
            hOutputFile->Close();

        }

    //define this as a plug-in
    DEFINE_FWK_MODULE(HLTrgAna_trk);

