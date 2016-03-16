// -*- C++ -*-
//
// Package:    HLTrgAna
// Class:      HLTrgAna
// 
/**\class HLTrgAna HLTrgAna.cc UserCode/HLTrgAna/src/HLTrgAna.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
*/
//
// Original Author:  Dong Ho Moon,588 R-012,+41227670285,
//         Created:  Tue Nov 15 23:36:54 CET 2011
// $Id: HLTrgAna.cc,v 1.23 2013/01/17 19:34:45 dmoon Exp $
//
//
// eddited at 20131203 for adding Regit Reco


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

#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtUtils.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"

#include "L1Trigger/CSCTrackFinder/interface/CSCSectorReceiverLUT.h"
#include "L1Trigger/CSCTrackFinder/interface/CSCTFPtLUT.h"
#include "L1Trigger/CSCTrackFinder/interface/CSCTrackFinderDataTypes.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include "DataFormats/Luminosity/interface/LumiSummary.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "DataFormats/HeavyIonEvent/interface/CentralityProvider.h"

#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "DataFormats/Candidate/interface/CompositeCandidateFwd.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/CompositeCandidate.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "PhysicsTools/HepMCCandAlgos/interface/GenParticlesHelper.h"

#include "TrackingTools/TrajectoryState/interface/TrajectoryStateTransform.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"


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
// class declaration
//

class HLTrgAna : public edm::EDAnalyzer {
    public:
        explicit HLTrgAna(const edm::ParameterSet&);
        ~HLTrgAna();

        static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
        const static int xNum = 10000;
        const static int yNum = 3;


    private:
        virtual void beginJob() ;
        virtual void analyze(const edm::Event&, const edm::EventSetup&);
        virtual void endJob() ;

        virtual void beginRun(edm::Run const&, edm::EventSetup const&);
        virtual void endRun(edm::Run const&, edm::EventSetup const&);
        virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
        virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

        // ----------member data ---------------------------
        std::string fOutputFile_;
        edm::InputTag L1MuCands_;
        edm::InputTag gtDigis_;
        edm::InputTag vertex_;
        edm::InputTag L2MuCands_;
        edm::InputTag L3MuCands_;
        edm::InputTag triggerResults_;
        edm::InputTag muons_;
        edm::InputTag BeamSpot_;
        edm::InputTag genSource_;

        int nHLT_HIL1DoubleMu0_HighQ_v1, nHLT_HIL2DoubleMu3_v1;
        int nHLT_HIL2Mu3_NHitQ_v1, nHLT_HIL2Mu7_v1;
        int nHLT_HIL2Mu15_v1, nHLT_HIL3DoubleMuOpen_v1;
        int nHLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v1;
        int nHLT_HIL3Mu3_v1;
        int nHLT_HIMinBiasBSC_v1, nHLT_HIMinBiasHF_v1, nHLT_HIMinBiasHfOrBSC_v1;
        int nHLT_HIActivityHF_Single3_v1, nHLT_HIActivityHF_Coincidence3_v1;
        int nHLT_HIClusterVertexCompatibility_v1;

        int nHLT_HIL1DoubleMuOpen_v5;
        int nHLT_HIL1DoubleMu0_HighQ_v5;
        int nHLT_HIL2DoubleMu0_v5;
        int nHLT_HIL2DoubleMu0_NHitQ_v5;
        int nHLT_HIL2DoubleMu0_L1HighQL2NHitQ_v5;
        int nHLT_HIL2DoubleMu3_v5;
        int nHLT_HIL3DoubleMuOpen_v7;
        int nHLT_HIL3DoubleMuOpen_Mgt2_v7;
        int nHLT_HIL3DoubleMuOpen_Mgt2_SS_v7;
        int nHLT_HIL3DoubleMuOpen_Mgt2_OS_v7;
        int nHLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v7;
        int nHLT_HIL2Mu3_v5;
        int nHLT_HIL2Mu3_NHitQ_v5;
        int nHLT_HIL2Mu7_v5;
        int nHLT_HIL2Mu15_v5;
        int nHLT_HIL3Mu3_v7;

        int nL1_DoubleMuOpen_BptxAND;
        int nL1_DoubleMu0;
        int nL1_SingleMu3;
        int nL1_SingleMu7;
        int nL1_SingleMu12;

        int nHLT_PAL1DoubleMu0_HighQ_v1;
        int nHLT_PAL1DoubleMuOpen_v1;
        int nHLT_PAMu1_Track1_Mgt2_v1;
        int nHLT_PAMu3_Track1_Mgt2_v1;
        int nHLT_PAL2DoubleMu3_v1;
        int nHLT_PAL2Mu3_NHitQ_v1;
        int nHLT_PAMu3_v1;
        int nHLT_PAMu7_v1;
        int nHLT_PAMu12_v1;
        int nHLT_PABTagMu_Jet20_Mu4_v1;
        int nHLT_PAMu3PFJet20_v1;
        int nHLT_PAMu3PFJet40_v1;
        int nHLT_PAMu7PFJet20_v1;

        int Run, Evt, Lumi;

        // Gen Info
        int nmom, nPar, ndau, p_Id[xNum];
        int nMom[xNum], nDau[xNum], m_Id[xNum][yNum], d_Id[xNum][yNum];
        double p_pt[xNum], p_eta[xNum], p_phi[xNum], p_st[xNum], p_mass[xNum], p_mtum[xNum], 
               p_vx[xNum], p_vy[xNum], p_vz[xNum], p_y[xNum];
        double m_pt[xNum][yNum], m_eta[xNum][yNum], m_phi[xNum][yNum], m_st[xNum][yNum], 
               m_mass[xNum][yNum], m_mtum[xNum][yNum], m_vx[xNum][yNum], m_vy[xNum][yNum], 
               m_vz[xNum][yNum], m_y[xNum][yNum];
        double d_pt[xNum][yNum], d_eta[xNum][yNum], d_phi[xNum][yNum], d_st[xNum][yNum], 
               d_mass[xNum][yNum], d_mtum[xNum][yNum], d_vx[xNum][yNum], d_vy[xNum][yNum], 
               d_vz[xNum][yNum], d_y[xNum][yNum]; 

        // Centrality Reco
        CentralityProvider * centrality_;

        double bmean, bsigma;
        double npartmean, npartsigma;
        double ncollmean, ncollsigma;
        double hf;
        int    c_bin;
        //double Cent;

        // Hi MC
        int nPart, nColl, nHard;
        double GenRpAng;
        double Imp;

        // L1/L2/L3 info
        double l1mu_p[xNum], l1mu_pt[xNum], l1mu_eta[xNum], l1mu_phi[xNum];
        int l1mu_ch[xNum], l1mu_qual[xNum], nL1Mu;
        double l2mu_p[xNum], l2mu_pt[xNum], l2mu_eta[xNum], l2mu_phi[xNum];
        double l2mu_nPixHits[xNum], l2mu_nHits[xNum], l2mu_nTrkHits[xNum];
        double l2mu_nStrHits[xNum], l2mu_dr[xNum], l2mu_dz[xNum];
        int l2mu_ch[xNum], nL2Mu;

        double l3mu_p[xNum], l3mu_pt[xNum], l3mu_eta[xNum], l3mu_phi[xNum];
        double l3mu_nPixHits[xNum], l3mu_nHits[xNum], l3mu_nTrkHits[xNum];
        double l3mu_nStrHits[xNum], l3mu_dr[xNum], l3mu_dz[xNum];
        int l3mu_ch[xNum], nL3Mu;

        // Reco Muons
        int nTMu, nRGMu, nRSMu, nRDMu;
        double recoGlb_pt[xNum], recoGlb_p[xNum], recoGlb_eta[xNum], recoGlb_phi[xNum], recoGlb_dxy[xNum];
        double recoGlb_sigmaDxy[xNum], recoGlb_dz[xNum], recoGlb_sigmaDz[xNum]; 
        int recoGlb_nhits[xNum];
        double recoSta_pt[xNum], recoSta_p[xNum], recoSta_eta[xNum], recoSta_phi[xNum], recoSta_dxy[xNum];
        double recoSta_sigmaDxy[xNum], recoSta_dz[xNum], recoSta_sigmaDz[xNum]; 
        int recoSta_nhits[xNum];
        double recoMu_pt[xNum], recoMu_p[xNum], recoMu_phi[xNum], recoMu_eta[xNum];
        int recoMu_Glb[xNum], recoMu_Sta[xNum], recoMu_Trk[xNum];

        // Regit Reco Muons
        int nRegTMu, nRegRGMu, nRegRSMu, nRegRDMu;
        double regrecoGlb_pt[xNum], regrecoGlb_p[xNum], regrecoGlb_eta[xNum], regrecoGlb_phi[xNum], regrecoGlb_dxy[xNum];
        double regrecoGlb_sigmaDxy[xNum], regrecoGlb_dz[xNum], regrecoGlb_sigmaDz[xNum]; 
        int regrecoGlb_nhits[xNum];
        double regrecoSta_pt[xNum], regrecoSta_p[xNum], regrecoSta_eta[xNum], regrecoSta_phi[xNum], regrecoSta_dxy[xNum];
        double regrecoSta_sigmaDxy[xNum], regrecoSta_dz[xNum], regrecoSta_sigmaDz[xNum]; 
        int regrecoSta_nhits[xNum];
        double regrecoMu_pt[xNum], regrecoMu_p[xNum], regrecoMu_phi[xNum], regrecoMu_eta[xNum];
        int regrecoMu_Glb[xNum], regrecoMu_Sta[xNum], regrecoMu_Trk[xNum];

        double recoDimu_pt[xNum], recoDimu_p[xNum], recoDimu_eta[xNum], recoDimu_phi[xNum], recoDimu_y[xNum], recoDimu_mass[xNum];
        int recoDimu_ch[xNum];

        double recoKids_pt[xNum][yNum], recoKids_p[xNum][yNum], recoKids_eta[xNum][yNum], recoKids_phi[xNum][yNum]; 
        double recoKids_dz[xNum][yNum], recoKids_dxy[xNum][yNum], recoKids_sigmaDxy[xNum][yNum], recoKids_sigmaDz[xNum][yNum], recoKids_htits[xNum][yNum];
        double recoKids_nhits[xNum][yNum];

        // Regit Reco DiMuon
        double regrecoDimu_pt[xNum], regrecoDimu_p[xNum], regrecoDimu_eta[xNum], regrecoDimu_phi[xNum], regrecoDimu_y[xNum], regrecoDimu_mass[xNum];
        int regrecoDimu_ch[xNum];

        double regrecoKids_pt[xNum][yNum], regrecoKids_p[xNum][yNum], regrecoKids_eta[xNum][yNum], regrecoKids_phi[xNum][yNum]; 
        double regrecoKids_dz[xNum][yNum], regrecoKids_dxy[xNum][yNum], regrecoKids_sigmaDxy[xNum][yNum], regrecoKids_sigmaDz[xNum][yNum], regrecoKids_htits[xNum][yNum];
        double regrecoKids_nhits[xNum][yNum];

        bool MC_, Central_, HiMC_, SIM_, HLT_, L1_BIT_, RECO_, REGIT_, L1_TRG_, L2_TRG_, L3_TRG_, PATMuons_, Cent_;
        int NoTrg_, TrgClass_;

        // Pat Muons
        int npMuons, patMuon_glb[xNum], patMuon_sta[xNum], patMuon_trk[xNum]; 
        int patMuonTrg_bit1[xNum], patMuonTrg_bit2[xNum], patMuonTrg_bit3[xNum], patMuonTrg_bit4[xNum], patMuonTrg_bit5[xNum], patMuonTrg_bit6[xNum];
        int patMuonTrgF_bit1[xNum], patMuonTrgF_bit2[xNum], patMuonTrgF_bit3[xNum], patMuonTrgF_bit4[xNum], patMuonTrgF_bit5[xNum], patMuonTrgF_bit6[xNum];
        double patMuon_eta[xNum], patMuon_phi[xNum], patMuon_pt[xNum], patMuon_p[xNum];
        int patMuon_nTrkHits[xNum], patMuon_arbitrated[xNum], patMuon_stationTight[xNum], patMuon_nTrkMeas[xNum], patMuon_nPixLays[xNum], patMuon_nMuValHits[xNum];
        double patMuon_nchi2In[xNum], patMuon_nchi2Gl[xNum], patMuon_dxy[xNum], patMuon_dz[xNum];

        const reco::VertexCollection *vertices;

        math::XYZPoint RefVtx;

        TFile *hOutputFile;
        TTree *rTree;

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
HLTrgAna::HLTrgAna(const edm::ParameterSet& iConfig)
{
    //now do what ever initialization is needed
    genSource_      = iConfig.getUntrackedParameter<edm::InputTag>("genSource");
    L1MuCands_      = iConfig.getUntrackedParameter<edm::InputTag>("L1MuCands");
    gtDigis_        = iConfig.getUntrackedParameter<edm::InputTag>("gtObjects");
    vertex_         = iConfig.getUntrackedParameter<edm::InputTag>("vertex");
    L2MuCands_      = iConfig.getUntrackedParameter<edm::InputTag>("L2MuCands");
    L3MuCands_      = iConfig.getUntrackedParameter<edm::InputTag>("L3MuCands");
    fOutputFile_    = iConfig.getUntrackedParameter<std::string>("hOutputFile");
    MC_             = iConfig.getParameter<bool>("doMC");
    Central_        = iConfig.getParameter<bool>("doCentrality");
    HiMC_           = iConfig.getParameter<bool>("doHiMC");
    L1_TRG_         = iConfig.getParameter<bool>("doL1");
    L2_TRG_         = iConfig.getParameter<bool>("doL2");
    L3_TRG_         = iConfig.getParameter<bool>("doL3");
    L1_BIT_         = iConfig.getParameter<bool>("doL1Bit");
    HLT_            = iConfig.getParameter<bool>("doHLT");
    RECO_           = iConfig.getParameter<bool>("doRECO");
    REGIT_          = iConfig.getParameter<bool>("doREGIT");
    PATMuons_       = iConfig.getParameter<bool>("doPAT");
    TrgClass_       = iConfig.getUntrackedParameter<int>("TrgClass");
    NoTrg_          = iConfig.getUntrackedParameter<int>("NoTrg");
    triggerResults_ = iConfig.getParameter<edm::InputTag>("TriggerResults");
    muons_          = iConfig.getUntrackedParameter<edm::InputTag>("muontag");
    BeamSpot_       = iConfig.getUntrackedParameter<edm::InputTag>("BeamSpot");
}


HLTrgAna::~HLTrgAna()
{

    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)



}


//
// member functions
//

// ------------ method called for each event  ------------
    void
HLTrgAna::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    /*
    // initialization
    for(int i = 0; i < xNum; i++){
        l1mu_p[i]=-999.0;l1mu_pt[i]=-999.0;l1mu_eta[i]=-999.0;l1mu_phi[i]=-999.0;
        l1mu_ch[i]=-999;l1mu_qual[i]=-999;
        l2mu_p[i]=-999.0;l2mu_pt[i]=-999.0;l2mu_eta[i]=-999.0;l2mu_phi[i]=-999.0;
        l2mu_nPixHits[i]=-999.0;l2mu_nHits[i]=-999.0;l2mu_nTrkHits[i]=-999.0;
        l2mu_nStrHits[i]=-999.0;l2mu_dr[i]=-999.0;l2mu_dz[i]=-999.0;
        l2mu_ch[i]=-999;
        l3mu_p[i]=-999.0;l3mu_pt[i]=-999.0;l3mu_eta[i]=-999.0;l3mu_phi[i]=-999.0;
        l3mu_nPixHits[i]=-999.0;l3mu_nHits[i]=-999.0;l3mu_nTrkHits[i]=-999.0;
        l3mu_nStrHits[i]=-999.0;l3mu_dr[i]=-999.0;l3mu_dz[i]=-999.0;
        l3mu_ch[i]=-999;
        recoGlb_pt[i]=-999.0;recoGlb_p[i]=-999.0;recoGlb_eta[i]=-999.0;recoGlb_phi[i]=-999.0;recoGlb_dxy[i]=-999.0;
        recoGlb_sigmaDxy[i]=-999.0;recoGlb_dz[i]=-999.0;recoGlb_sigmaDz[i]=-999.0;
        recoGlb_nhits[i]=-999;
        recoSta_pt[i]=-999.0;recoSta_p[i]=-999.0;recoSta_eta[i]=-999.0;recoSta_phi[i]=-999.0;recoSta_dxy[i]=-999.0;
        recoSta_sigmaDxy[i]=-999.0;recoSta_dz[i]=-999.0;recoSta_sigmaDz[i]=-999.0;
        recoSta_nhits[i]=-999;
        recoDimu_pt[i]=-999.0;recoDimu_p[i]=-999.0;recoDimu_eta[i]=-999.0;recoDimu_phi[i]=-999.0;recoDimu_y[i]=-999.0;recoDimu_mass[i]=-999.0;
        recoDimu_ch[i]=-999;
        for(int j = 0; j < yNum; j++){
            recoKids_pt[i][j]=-999.0;recoKids_p[i][j]=-999.0;recoKids_eta[i][j]=-999.0;recoKids_phi[i][j]=-999.0;
            recoKids_dz[i][j]=-999.0;recoKids_dxy[i][j]=-999.0;recoKids_sigmaDxy[i][j]=-999.0;recoKids_sigmaDz[i][j]=-999.0;recoKids_htits[i][j]=-999.0;
            recoKids_nhits[i][j]=-999.0;
        }


    }
    */
    using namespace edm;
    using namespace HepMC;

    const GenEvent* evt;

    Evt = 0; Run = 0; Lumi = 0;

    Evt = iEvent.id().event();
    Run = iEvent.id().run();
    Lumi = (int)iEvent.luminosityBlock();

    cout<<"Run : "<<Run<<", Evt : "<<Evt<<", Lumi : "<<Lumi<<endl;
    if(Central_){
        c_bin = 0;
        if(!centrality_) centrality_ = new CentralityProvider(iSetup);
        centrality_->newEvent(iEvent,iSetup); // make sure you do this first in every event
        c_bin = centrality_->getBin();
    }

    if(MC_){
        // MC Truth Analysis
        Handle<GenParticleCollection> mctruth; 
        iEvent.getByLabel(genSource_, mctruth);

        nPar = 0;

        for(size_t i = 0; i < mctruth->size(); ++ i) {

            const Candidate & p = (*mctruth)[i];
            if (! &p ) continue;
            int id = p.pdgId();
            //cout<<"particle Id : "<<id<<endl;

            if(abs(id) == 13  || abs(id) == 443 || abs(id) == 553 || abs(id) == 23 || abs(id) == 24){
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
                    //++nDau;
                }

                ++nPar;
            }


        }
    }



    if(L1_BIT_){
        // Trigger Analysis
        std::string L1_DoubleMuOpen_BptxAND = "L1_DoubleMuOpen_BptxAND";
        std::string L1_DoubleMu0 = "L1_DoubleMu0";
        std::string L1_SingleMu3 = "L1_SingleMu3";
        std::string L1_SingleMu7 = "L1_SingleMu7";
        std::string L1_SingleMu12 = "L1_SingleMu12";

        //m_l1GtUtils.retrieveL1EventSetup(eventSetup);
        edm::ESHandle<L1GtTriggerMenu> menuRcd;
        iSetup.get<L1GtTriggerMenuRcd>().get(menuRcd) ;
        const L1GtTriggerMenu* menu = menuRcd.product();

        Handle<L1GlobalTriggerReadoutRecord> L1GTRR;
        iEvent.getByLabel(gtDigis_,L1GTRR);

        DecisionWord gtDecisionWord = L1GTRR->decisionWord();
        string l1BitName;
        int l1Acc;
        int l1Acc0 = 0, l1Acc1 = 0, l1Acc2 = 0, l1Acc3 = 0, l1Acc4 = 0, l1Acc5 = 0, l1Acc6 = 0, l1Acc7 = 0;
        int l1Acc8 = 0, l1Acc9 = 0, l1Acc10 = 0, l1Acc11 = 0, l1Acc12 = 0, l1Acc13 = 0;
        for (CItAlgo algo = menu->gtAlgorithmMap().begin(); algo!=menu->gtAlgorithmMap().end(); ++algo) {
            //std::cout << "Name: " << (algo->second).algoName() << " Alias: " << (algo->second).algoAlias() << std::endl;
            int itrig = (algo->second).algoBitNumber();
            l1BitName = TString( (algo->second).algoName() );
            l1Acc = gtDecisionWord[itrig];
            //cout<<"%%% L1 Info : "<<l1BitName<<" %%%"<<endl;
            if(l1BitName == L1_DoubleMuOpen_BptxAND && l1Acc == 1) {cout<<"%%% L1 Info : "<<l1BitName<<" !!!"<<" Fired"<<endl;l1Acc0 = 1;}
            if(l1BitName == L1_DoubleMu0 && l1Acc == 1) {cout<<"%%% L1 Info : "<<l1BitName<<" !!!"<<" Fired"<<endl;l1Acc1 = 1;}
            if(l1BitName == L1_SingleMu3 && l1Acc == 1) {cout<<"%%% L1 Info : "<<l1BitName<<" !!!"<<" Fired"<<endl;l1Acc2 = 1;}
            if(l1BitName == L1_SingleMu7 && l1Acc == 1) {cout<<"%%% L1 Info : "<<l1BitName<<" !!!"<<" Fired"<<endl;l1Acc3 = 1;}
            if(l1BitName == L1_SingleMu12 && l1Acc == 1) {cout<<"%%% L1 Info : "<<l1BitName<<" !!!"<<" Fired"<<endl;l1Acc4 = 1;}
        }

        nL1_DoubleMuOpen_BptxAND = l1Acc0; 
        nL1_DoubleMu0 = l1Acc1; 
        nL1_SingleMu3 = l1Acc2; 
        nL1_SingleMu7 = l1Acc3; 
        nL1_SingleMu12 = l1Acc4; 
    }

    if(L1_TRG_){
        Handle< vector<l1extra::L1MuonParticle> > l1muons;
        //iEvent.getByLabel("l1extraParticles", l1muons);
        iEvent.getByLabel(L1MuCands_, l1muons);
        //iEvent.getByLabel("hltL1extraParticles", l1muons);
        if(!l1muons.isValid()){
            cout<<" No L1 Muon Candidates !!!!!"<<endl;
        }
        
        l1extra::L1MuonParticleCollection::const_iterator l1_it = l1muons->begin() ;
        l1extra::L1MuonParticleCollection::const_iterator muEnd = l1muons->end() ;
        int NL1Mu = 0;
        for( size_t i = 0 ; l1_it != muEnd ; ++l1_it, ++i )
        {
            const l1extra::L1MuonParticle & l1mu = (*l1muons)[i];

            l1mu_ch[NL1Mu]=l1mu.charge();
            l1mu_pt[NL1Mu]=l1mu.pt();
            l1mu_eta[NL1Mu]=l1mu.eta();
            l1mu_phi[NL1Mu]=l1mu.phi();
            l1mu_p[NL1Mu]=l1mu.p();
            l1mu_qual[NL1Mu] = l1_it->gmtMuonCand().quality();
            //cout<<"l1mu_qual : "<<l1_it->gmtMuonCand().quality()<<endl;

            NL1Mu++;
        }
        nL1Mu = NL1Mu;
        cout<<"number of L1 muons : "<<nL1Mu<<endl;

    }

    if(HLT_){
        Handle<TriggerResults> trigResults;
        iEvent.getByLabel(triggerResults_,trigResults);

        TriggerNames triggerNames_;

        /*
           std::string HLT_HIL1DoubleMu0_HighQ_v1   = "HLT_HIL1DoubleMu0_HighQ_v1";
           std::string HLT_HIL2DoubleMu3_v1   = "HLT_HIL2DoubleMu3_v1";
           std::string HLT_HIL3DoubleMuOpen_v1      = "HLT_HIL3DoubleMuOpen_v1";
           std::string HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v1      = "HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v1";
           std::string HLT_HIL2Mu3_NHitQ_v1      = "HLT_HIL2Mu3_NHitQ_v1";
           std::string HLT_HIL3Mu3_v1      = "HLT_HIL3Mu3_v1";
           std::string HLT_HIL2Mu7_v1     = "HLT_HIL2Mu7_v1";
           std::string HLT_HIL2Mu15_v1    = "HLT_HIL2Mu15_v1";

           std::string HLT_HIMinBiasBSC_v1       = "HLT_HIMinBiasBSC_V1";
           std::string HLT_HIMinBiasHF_v1        = "HLT_HIMinBiasHF_v1";
           std::string HLT_HIMinBiasHfOrBSC_v1   = "HLT_HIMinBiasHfOrBSC_v1"; // HF_or_BSC
           std::string HLT_HIActivityHF_Single3_v1 = "HLT_HIActivityHF_Single3_v1";
           std::string HLT_HIActivityHF_Coincidence3_v1 = "HLT_HIActivityHF_Coincidence3_v1";
           std::string HLT_HIClusterVertexCompatibility_v1 = "HLT_HIClusterVertexCompatibility_v1";
           */

        // TrgClass_ : 0 (PbPb), 1 (pPb)
        std::string TrgNames[30];
        if(TrgClass_ == 1){
                TrgNames[0] = "HLT_PAL1DoubleMu0_HighQ_v1";
                TrgNames[1] = "HLT_PAL1DoubleMuOpen_v1";
                TrgNames[2] = "HLT_PAL2DoubleMu3_v1";
                TrgNames[3] = "HLT_PAMu1_Track1_Mgt2_v1";
                TrgNames[4] = "HLT_PAMu3_Track1_Mgt2_v1";
                TrgNames[5] = "HLT_PAL2Mu3_NHitQ_v1";
                TrgNames[6] = "HLT_PAMu3_v1";
                TrgNames[7] = "HLT_PAMu7_v1";
                TrgNames[8] = "HLT_PAMu12_v1";
                TrgNames[9] = "HLT_PABTagMu_Jet20_Mu4_v1";
                TrgNames[10] = "HLT_PAMu3PFJet20_v1";
                TrgNames[11] = "HLT_PAMu3PFJet40_v1";
                TrgNames[12] = "HLT_PAMu7PFJet20_v1";
        }

        if(TrgClass_ == 0){
                TrgNames[0] = "HLT_HIL1DoubleMuOpen_v5";
                TrgNames[1] = "HLT_HIL1DoubleMu0_HighQ_v5";
                TrgNames[2] = "HLT_HIL2DoubleMu0_v5";
                TrgNames[3] = "HLT_HIL2DoubleMu0_NHitQ_v5";
                TrgNames[4] = "HLT_HIL2DoubleMu0_L1HighQL2NHitQ_v5";
                TrgNames[5] = "HLT_HIL2DoubleMu3_v5";
                TrgNames[6] = "HLT_HIL3DoubleMuOpen_v7";
                TrgNames[7] = "HLT_HIL3DoubleMuOpen_Mgt2_v7";
                TrgNames[8] = "HLT_HIL3DoubleMuOpen_Mgt2_SS_v7";
                TrgNames[9] = "HLT_HIL3DoubleMuOpen_Mgt2_OS_v7";
                TrgNames[10] = "HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v7";
                TrgNames[11] = "HLT_HIL2Mu3_v5";
                TrgNames[12] = "HLT_HIL2Mu3_NHitQ_v5";
                TrgNames[13] = "HLT_HIL2Mu7_v5";
                TrgNames[14] = "HLT_HIL2Mu15_v5";
                TrgNames[15] = "HLT_HIL3Mu3_v7";
        }



        // MinBias
        //int nHF = 0, nBSC = 0, nHForBSC = 0, nHFS3 = 0, nHFC3 = 0, nCVtxC = 0; // 6
        int nTrg[100] = {0};

        if (trigResults.isValid()) {
            int ntrigs = trigResults->size();
            if (ntrigs==0){std::cout << "%HLTInfo -- No trigger name given in TriggerResults of the input " << std::endl;}
            edm::TriggerNames const& triggerNames = iEvent.triggerNames(*trigResults);

            //std::cout << "Number of HLT paths: " << hltConfig_.size() << std::endl;
            //int presclSet = hltConfig_.prescaleSet(iEvent, eventSetup);
            //std::cout<<"\tPrescale set number: "<< presclSet <<std::endl;
            //cout<<"hlt is ok !!!!"<<endl;

            for (int itrig = 0; itrig != ntrigs; ++itrig){

                std::string trigName=triggerNames.triggerName(itrig);
                bool accept = trigResults->accept(itrig);
                //std::cout << "%HLTInfo --  Name of HLT Triggers: " << trigName << std::endl;

                if (accept) {
                    //cout<<"%HLTInfo -- "<<trigName<<" : accepted !!!!!"<<endl;

                    //std::cout << "%HLTInfo --  Number of HLT Triggers: " << ntrigs << std::endl;
                    //std::cout << "%HLTInfo --  HLTTrigger(" << itrig << "): " << trigName << " = " << accept << " fired !!!"<<std::endl;
                    // 2013
                    //cout<<"TrgNames[0] : "<<TrgNames[0]<<endl;
                    for(int NTrg = 0; NTrg < NoTrg_; NTrg++){
                        //cout<<"TrgNames["<<NTrg<<"] : "<<TrgNames[NTrg]<<", "<<trigName<<endl;
                        if(trigName == TrgNames[NTrg]){ cout<<"%HLTInfo : "<<trigName<<" is fired !!!!"<<endl; nTrg[NTrg] = 1;}
                    }
                }
            }
        }else{cout<<"HLT Info is not ok !!!!!"<<endl;}

        if(TrgClass_ == 0){
            // L1/L2/L3 bit fill up
            nHLT_HIL1DoubleMuOpen_v5 = nTrg[0];
            nHLT_HIL1DoubleMu0_HighQ_v5 = nTrg[1];
            nHLT_HIL2DoubleMu0_v5 = nTrg[2];
            nHLT_HIL2DoubleMu0_NHitQ_v5 = nTrg[3];
            nHLT_HIL2DoubleMu0_L1HighQL2NHitQ_v5 = nTrg[4];
            nHLT_HIL2DoubleMu3_v5 = nTrg[5];
            nHLT_HIL3DoubleMuOpen_v7 = nTrg[6];
            nHLT_HIL3DoubleMuOpen_Mgt2_v7 = nTrg[7];
            nHLT_HIL3DoubleMuOpen_Mgt2_SS_v7 = nTrg[8];
            nHLT_HIL3DoubleMuOpen_Mgt2_OS_v7 = nTrg[9];
            nHLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v7 = nTrg[10];
            nHLT_HIL2Mu3_v5 = nTrg[11];
            nHLT_HIL2Mu3_NHitQ_v5 = nTrg[12];
            nHLT_HIL2Mu7_v5 = nTrg[13];
            nHLT_HIL2Mu15_v5 = nTrg[14];
            nHLT_HIL3Mu3_v7 = nTrg[15];
        }else if(TrgClass_ == 1){
            nHLT_PAL1DoubleMu0_HighQ_v1 = nTrg[0];
            nHLT_PAL1DoubleMuOpen_v1 = nTrg[1];
            nHLT_PAL2DoubleMu3_v1 = nTrg[2];
            nHLT_PAMu1_Track1_Mgt2_v1 = nTrg[3];
            nHLT_PAMu3_Track1_Mgt2_v1 = nTrg[4];
            nHLT_PAL2Mu3_NHitQ_v1 = nTrg[5];
            nHLT_PAMu3_v1 = nTrg[6];
            nHLT_PAMu7_v1 = nTrg[7];
            nHLT_PAMu12_v1 = nTrg[8];
            nHLT_PABTagMu_Jet20_Mu4_v1 = nTrg[9];
            nHLT_PAMu3PFJet20_v1 = nTrg[10];
            nHLT_PAMu3PFJet40_v1 = nTrg[11];
            nHLT_PAMu7PFJet20_v1 = nTrg[12];
        }

    }

    /*
    edm::Handle<reco::VertexCollection> vertexCollection;
    iEvent.getByLabel(vertex_,vertexCollection);
    vertices = vertexCollection.product();
    const reco::Vertex *vtx = &(vertices->at(0));
    RefVtx = vtx->position();
    */

    if(RECO_){
        // Reco Muon Collection
        edm::Handle<edm::View<reco::Muon> >muons;
        iEvent.getByLabel("muons",muons);
        int NTMu = 0; int NgMu = 0; int NsMu = 0;
        for(unsigned int j = 0; j < muons->size(); ++j){
            edm::RefToBase<reco::Muon> muCandRef(muons, j);
            if ( muCandRef.isNull() ) continue;
            NTMu++;
            if(muCandRef->isGlobalMuon()){
                //cout<<"reco::Muon >> GlobalMuons !!!!!"<<endl;
                recoGlb_pt[NgMu]=muCandRef->globalTrack()->pt();
                recoGlb_p[NgMu]=muCandRef->globalTrack()->p();
                recoGlb_eta[NgMu]=muCandRef->globalTrack()->eta();
                recoGlb_phi[NgMu]=muCandRef->globalTrack()->phi();
                //recoGlb_dxy[NgMu] = muCandRef->globalTrack()->dxy(vtx->position());
                //recoGlb_sigmaDxy[NgMu] = sqrt(muCandRef->globalTrack()->dxyError()*muCandRef->globalTrack()->dxyError() + vtx->yError()*vtx->yError()+vtx->xError()*vtx->xError());
                //recoGlb_dz[NgMu] = muCandRef->globalTrack()->dz(vtx->position());
                //recoGlb_sigmaDz[NgMu] = sqrt(muCandRef->globalTrack()->dzError()*muCandRef->globalTrack()->dzError()+vtx->zError()*vtx->zError());
                //recoGlb_nhits[NgMu] = muCandRef->globalTrack()->numberOfValidHits();
                NgMu++;
            }
            if(muCandRef->isStandAloneMuon()){
                //cout<<"reco::Muon >> standAloneMuons !!!!!"<<endl;
                recoSta_pt[NsMu]=muCandRef->standAloneMuon()->pt();
                recoSta_p[NsMu]=muCandRef->standAloneMuon()->p();
                recoSta_eta[NsMu]=muCandRef->standAloneMuon()->eta();
                recoSta_phi[NsMu]=muCandRef->standAloneMuon()->phi();
                //recoSta_dxy[NsMu] = muCandRef->standAloneMuon()->dxy(vtx->position());
                //recoSta_sigmaDxy[NsMu] = sqrt(muCandRef->standAloneMuon()->dxyError()*muCandRef->standAloneMuon()->dxyError() + vtx->yError()*vtx->yError()+vtx->xError()*vtx->xError());
                //recoSta_dz[NsMu] = muCandRef->standAloneMuon()->dz(vtx->position());
                //recoSta_sigmaDz[NsMu] = sqrt(muCandRef->standAloneMuon()->dzError()*muCandRef->standAloneMuon()->dzError()+vtx->zError()*vtx->zError());
                //recoSta_nhits[NsMu] = muCandRef->standAloneMuon()->numberOfValidHits();
                NsMu++;
            }
            recoMu_Glb[NTMu] = 0;
            recoMu_Sta[NTMu] = 0;
            recoMu_Trk[NTMu] = 0;
            if(muCandRef->isGlobalMuon()) recoMu_Glb[NTMu] = 1;
            if(muCandRef->isStandAloneMuon()) recoMu_Sta[NTMu] = 1;
            if(muCandRef->isTrackerMuon()) recoMu_Trk[NTMu] = 1;
            recoMu_pt[NTMu] = muCandRef->pt();
            recoMu_p[NTMu] = muCandRef->p();
            recoMu_phi[NTMu] = muCandRef->phi();
            recoMu_eta[NTMu] = muCandRef->eta();
        }
        nTMu = NTMu; nRGMu = NgMu; nRSMu = NsMu;
        // DiMuon of reco::Muons
        int NrDMu = 0;
        cout<<"# of muons : "<<muons->size()<<endl;
        if(muons->size() > 1) {
            for(unsigned int j = 0; j < muons->size()-1; ++j){
                edm::RefToBase<reco::Muon> muCandRef1(muons, j);
                if ( muCandRef1.isNull() ) {
                    cout<<"null muons"<<endl;
                    continue;
                }
                if ( !muCandRef1->isGlobalMuon()) {
                    cout<<"this is not global muon"<<endl;
                    continue;
                }
                for(unsigned int k = j+1; k < muons->size(); ++k){
                    //cout<<"j : "<<j<<", k : "<<k<<endl;
                    edm::RefToBase<reco::Muon> muCandRef2(muons, k);
                    if ( muCandRef2.isNull() ) {
                        cout<<"null muons"<<endl;
                        continue;
                    }
                    if ( !muCandRef2->isGlobalMuon()) {
                        cout<<"this is not global muon"<<endl;
                        continue;
                    }
                    //cout<<"mu1 pt : "<<muCandRef1->globalTrack()->pt()<<", eta : "<<muCandRef1->globalTrack()->eta()<<endl;
                    //cout<<"mu2 pt : "<<muCandRef2->globalTrack()->pt()<<", eta : "<<muCandRef2->globalTrack()->eta()<<endl;
                    recoDimu_ch[NrDMu]=muCandRef1->globalTrack()->charge()*muCandRef2->globalTrack()->charge();
                    TLorentzVector kid1, kid2;
                    double en1 = sqrt(muCandRef1->globalTrack()->p()*muCandRef1->globalTrack()->p()+m_mu*m_mu);
                    double en2 = sqrt(muCandRef2->globalTrack()->p()*muCandRef2->globalTrack()->p()+m_mu*m_mu);

                    kid1.SetPxPyPzE(muCandRef1->globalTrack()->px(),muCandRef1->globalTrack()->py(),muCandRef1->globalTrack()->pz(),en1);
                    kid2.SetPxPyPzE(muCandRef2->globalTrack()->px(),muCandRef2->globalTrack()->py(),muCandRef2->globalTrack()->pz(),en2);

                    TLorentzVector dimuon;
                    dimuon = kid1 + kid2;
                    recoDimu_pt[NrDMu]=dimuon.Pt();recoDimu_p[NrDMu]=dimuon.P();recoDimu_eta[NrDMu]=dimuon.Eta();recoDimu_y[NrDMu]=dimuon.Rapidity();
                    recoDimu_phi[NrDMu]=dimuon.Phi();recoDimu_mass[NrDMu]=dimuon.M();
                    //cout<<"reco dimuon mass : "<<recoDimu_mass[NrDMu]<<endl;
                    //cout<<"reco dimuon mass 2 : "<<dimuon.M()<<endl;
                    //cout<<"reco dimuon y : "<<recoDimu_y[NrDMu]<<endl;
                    //cout<<"reco dimuon eta : "<<recoDimu_eta[NrDMu]<<endl;

                    if(muCandRef1->globalTrack()->charge() == -1){
                        recoKids_pt[NrDMu][0] = muCandRef1->globalTrack()->pt();recoKids_eta[NrDMu][0]=muCandRef1->globalTrack()->eta();
                        recoKids_phi[NrDMu][0]=muCandRef1->globalTrack()->phi();recoKids_p[NrDMu][0] = muCandRef1->globalTrack()->p();
                        recoKids_pt[NrDMu][1] = muCandRef2->globalTrack()->pt();recoKids_eta[NrDMu][1]=muCandRef2->globalTrack()->eta();
                        recoKids_phi[NrDMu][1]=muCandRef2->globalTrack()->phi();recoKids_p[NrDMu][1] = muCandRef2->globalTrack()->p();

                        //recoKids_dxy[NrDMu][0] = muCandRef1->globalTrack()->dxy(vtx->position());
                        //recoKids_sigmaDxy[NrDMu][0]=sqrt(muCandRef1->globalTrack()->dxyError()*muCandRef1->globalTrack()->dxyError() + vtx->yError()*vtx->yError()+vtx->xError()*vtx->xError());
                        //recoKids_dz[NrDMu][0] = muCandRef1->globalTrack()->dz(vtx->position());
                        //recoKids_sigmaDz[NrDMu][0] = sqrt(muCandRef1->globalTrack()->dzError()*muCandRef1->globalTrack()->dzError()+vtx->zError()*vtx->zError());
                        //recoKids_nhits[NrDMu][0] = muCandRef1->globalTrack()->numberOfValidHits();

                        //recoKids_dxy[NrDMu][1] = muCandRef2->globalTrack()->dxy(vtx->position());
                        //recoKids_sigmaDxy[NrDMu][1] = sqrt(muCandRef2->globalTrack()->dxyError()*muCandRef2->globalTrack()->dxyError() + vtx->yError()*vtx->yError()+vtx->xError()*vtx->xError());
                        //recoKids_dz[NrDMu][1] = muCandRef2->globalTrack()->dz(vtx->position());
                        //recoKids_sigmaDz[NrDMu][1] = sqrt(muCandRef2->globalTrack()->dzError()*muCandRef2->globalTrack()->dzError()+vtx->zError()*vtx->zError());
                        //recoKids_nhits[NrDMu][1] = muCandRef2->globalTrack()->numberOfValidHits();
                    }else{
                        recoKids_pt[NrDMu][0] = muCandRef2->globalTrack()->pt();recoKids_eta[NrDMu][0]=muCandRef2->globalTrack()->eta();
                        recoKids_phi[NrDMu][0]=muCandRef2->globalTrack()->phi();recoKids_p[NrDMu][0] = muCandRef2->globalTrack()->p();
                        //recoKids_dxy[NrDMu][0] = muCandRef2->globalTrack()->dxy(vtx->position());
                        //recoKids_sigmaDxy[NrDMu][0]=sqrt(muCandRef2->globalTrack()->dxyError()*muCandRef2->globalTrack()->dxyError() + vtx->yError()*vtx->yError()+vtx->xError()*vtx->xError());
                        //recoKids_dz[NrDMu][0] = muCandRef2->globalTrack()->dz(vtx->position());
                        //recoKids_sigmaDz[NrDMu][0] = sqrt(muCandRef2->globalTrack()->dzError()*muCandRef2->globalTrack()->dzError()+vtx->zError()*vtx->zError());
                        //recoKids_nhits[NrDMu][0] = muCandRef2->globalTrack()->numberOfValidHits();

                        recoKids_pt[NrDMu][1] = muCandRef1->globalTrack()->pt();recoKids_eta[NrDMu][1]=muCandRef1->globalTrack()->eta();
                        recoKids_phi[NrDMu][1]=muCandRef1->globalTrack()->phi();recoKids_p[NrDMu][1] = muCandRef1->globalTrack()->p();
                        //recoKids_dxy[NrDMu][1] = muCandRef1->globalTrack()->dxy(vtx->position());
                        //recoKids_sigmaDxy[NrDMu][1] = sqrt(muCandRef1->globalTrack()->dxyError()*muCandRef1->globalTrack()->dxyError() + vtx->yError()*vtx->yError()+vtx->xError()*vtx->xError());
                        //recoKids_dz[NrDMu][1] = muCandRef1->globalTrack()->dz(vtx->position());
                        //recoKids_sigmaDz[NrDMu][1] = sqrt(muCandRef1->globalTrack()->dzError()*muCandRef1->globalTrack()->dzError()+vtx->zError()*vtx->zError());
                        //recoKids_nhits[NrDMu][1] = muCandRef1->globalTrack()->numberOfValidHits();
                    }

                    NrDMu++;
                }
            }
            nRDMu = NrDMu;
            cout<<"number of dimuon : "<<nRDMu<<endl;
        }
    }

    if(REGIT_){
        cout<<"dmoon chk 2 !!!"<<endl;
        // Reco Muon Collection
        edm::Handle<edm::View<reco::Muon> >muons;
        iEvent.getByLabel("remuons",muons);
        int NTMu = 0; int NgMu = 0; int NsMu = 0;
        for(unsigned int j = 0; j < muons->size(); ++j){
            edm::RefToBase<reco::Muon> muCandRef(muons, j);
            if ( muCandRef.isNull() ) continue;
            NTMu++;
            if(muCandRef->isGlobalMuon()){
                //cout<<"reco::Muon >> GlobalMuons !!!!!"<<endl;
                regrecoGlb_pt[NgMu]=muCandRef->globalTrack()->pt();
                regrecoGlb_p[NgMu]=muCandRef->globalTrack()->p();
                regrecoGlb_eta[NgMu]=muCandRef->globalTrack()->eta();
                regrecoGlb_phi[NgMu]=muCandRef->globalTrack()->phi();
                //regrecoGlb_dxy[NgMu] = muCandRef->globalTrack()->dxy(vtx->position());
                //regrecoGlb_sigmaDxy[NgMu] = sqrt(muCandRef->globalTrack()->dxyError()*muCandRef->globalTrack()->dxyError() + vtx->yError()*vtx->yError()+vtx->xError()*vtx->xError());
                //regrecoGlb_dz[NgMu] = muCandRef->globalTrack()->dz(vtx->position());
                //regrecoGlb_sigmaDz[NgMu] = sqrt(muCandRef->globalTrack()->dzError()*muCandRef->globalTrack()->dzError()+vtx->zError()*vtx->zError());
                //regrecoGlb_nhits[NgMu] = muCandRef->globalTrack()->numberOfValidHits();
                NgMu++;
            }
            if(muCandRef->isStandAloneMuon()){
                //cout<<"regreco::Muon >> standAloneMuons !!!!!"<<endl;
                regrecoSta_pt[NsMu]=muCandRef->standAloneMuon()->pt();
                regrecoSta_p[NsMu]=muCandRef->standAloneMuon()->p();
                regrecoSta_eta[NsMu]=muCandRef->standAloneMuon()->eta();
                regrecoSta_phi[NsMu]=muCandRef->standAloneMuon()->phi();
                //regrecoSta_dxy[NsMu] = muCandRef->standAloneMuon()->dxy(vtx->position());
                //regrecoSta_sigmaDxy[NsMu] = sqrt(muCandRef->standAloneMuon()->dxyError()*muCandRef->standAloneMuon()->dxyError() + vtx->yError()*vtx->yError()+vtx->xError()*vtx->xError());
                //regrecoSta_dz[NsMu] = muCandRef->standAloneMuon()->dz(vtx->position());
                //regrecoSta_sigmaDz[NsMu] = sqrt(muCandRef->standAloneMuon()->dzError()*muCandRef->standAloneMuon()->dzError()+vtx->zError()*vtx->zError());
                //regrecoSta_nhits[NsMu] = muCandRef->standAloneMuon()->numberOfValidHits();
                NsMu++;
            }
            regrecoMu_Glb[NTMu] = 0;
            regrecoMu_Sta[NTMu] = 0;
            regrecoMu_Trk[NTMu] = 0;
            if(muCandRef->isGlobalMuon()) regrecoMu_Glb[NTMu] = 1;
            if(muCandRef->isStandAloneMuon()) regrecoMu_Sta[NTMu] = 1;
            if(muCandRef->isTrackerMuon()) regrecoMu_Trk[NTMu] = 1;
            regrecoMu_pt[NTMu] = muCandRef->pt();
            regrecoMu_p[NTMu] = muCandRef->p();
            regrecoMu_phi[NTMu] = muCandRef->phi();
            regrecoMu_eta[NTMu] = muCandRef->eta();
        }
        nRegTMu = NTMu; nRegRGMu = NgMu; nRegRSMu = NsMu;
        // DiMuon of regreco::Muons
        int NrDMu = 0;
        cout<<"# of muons : "<<muons->size()<<endl;
        if(muons->size() > 1) {
            for(unsigned int j = 0; j < muons->size()-1; ++j){
                edm::RefToBase<reco::Muon> muCandRef1(muons, j);
                if ( muCandRef1.isNull() ) {
                    cout<<"null muons"<<endl;
                    continue;
                }
                if ( !muCandRef1->isGlobalMuon()) {
                    cout<<"this is not global muon"<<endl;
                    continue;
                }
                for(unsigned int k = j+1; k < muons->size(); ++k){
                    //cout<<"j : "<<j<<", k : "<<k<<endl;
                    edm::RefToBase<reco::Muon> muCandRef2(muons, k);
                    if ( muCandRef2.isNull() ) {
                        cout<<"null muons"<<endl;
                        continue;
                    }
                    if ( !muCandRef2->isGlobalMuon()) {
                        cout<<"this is not global muon"<<endl;
                        continue;
                    }
                    //cout<<"mu1 pt : "<<muCandRef1->globalTrack()->pt()<<", eta : "<<muCandRef1->globalTrack()->eta()<<endl;
                    //cout<<"mu2 pt : "<<muCandRef2->globalTrack()->pt()<<", eta : "<<muCandRef2->globalTrack()->eta()<<endl;
                    regrecoDimu_ch[NrDMu]=muCandRef1->globalTrack()->charge()*muCandRef2->globalTrack()->charge();
                    TLorentzVector kid1, kid2;
                    double en1 = sqrt(muCandRef1->globalTrack()->p()*muCandRef1->globalTrack()->p()+m_mu*m_mu);
                    double en2 = sqrt(muCandRef2->globalTrack()->p()*muCandRef2->globalTrack()->p()+m_mu*m_mu);

                    kid1.SetPxPyPzE(muCandRef1->globalTrack()->px(),muCandRef1->globalTrack()->py(),muCandRef1->globalTrack()->pz(),en1);
                    kid2.SetPxPyPzE(muCandRef2->globalTrack()->px(),muCandRef2->globalTrack()->py(),muCandRef2->globalTrack()->pz(),en2);

                    TLorentzVector dimuon;
                    dimuon = kid1 + kid2;
                    regrecoDimu_pt[NrDMu]=dimuon.Pt();regrecoDimu_p[NrDMu]=dimuon.P();regrecoDimu_eta[NrDMu]=dimuon.Eta();regrecoDimu_y[NrDMu]=dimuon.Rapidity();
                    regrecoDimu_phi[NrDMu]=dimuon.Phi();regrecoDimu_mass[NrDMu]=dimuon.M();
                    //cout<<"regreco dimuon mass : "<<regrecoDimu_mass[NrDMu]<<endl;
                    //cout<<"regreco dimuon mass 2 : "<<dimuon.M()<<endl;
                    //cout<<"regreco dimuon y : "<<regrecoDimu_y[NrDMu]<<endl;
                    //cout<<"regreco dimuon eta : "<<regrecoDimu_eta[NrDMu]<<endl;

                    if(muCandRef1->globalTrack()->charge() == -1){
                        regrecoKids_pt[NrDMu][0] = muCandRef1->globalTrack()->pt();regrecoKids_eta[NrDMu][0]=muCandRef1->globalTrack()->eta();
                        regrecoKids_phi[NrDMu][0]=muCandRef1->globalTrack()->phi();regrecoKids_p[NrDMu][0] = muCandRef1->globalTrack()->p();
                        regrecoKids_pt[NrDMu][1] = muCandRef2->globalTrack()->pt();regrecoKids_eta[NrDMu][1]=muCandRef2->globalTrack()->eta();
                        regrecoKids_phi[NrDMu][1]=muCandRef2->globalTrack()->phi();regrecoKids_p[NrDMu][1] = muCandRef2->globalTrack()->p();

                        //regrecoKids_dxy[NrDMu][0] = muCandRef1->globalTrack()->dxy(vtx->position());
                        //regrecoKids_sigmaDxy[NrDMu][0]=sqrt(muCandRef1->globalTrack()->dxyError()*muCandRef1->globalTrack()->dxyError() + vtx->yError()*vtx->yError()+vtx->xError()*vtx->xError());
                        //regrecoKids_dz[NrDMu][0] = muCandRef1->globalTrack()->dz(vtx->position());
                        //regrecoKids_sigmaDz[NrDMu][0] = sqrt(muCandRef1->globalTrack()->dzError()*muCandRef1->globalTrack()->dzError()+vtx->zError()*vtx->zError());
                        //regrecoKids_nhits[NrDMu][0] = muCandRef1->globalTrack()->numberOfValidHits();

                        //regrecoKids_dxy[NrDMu][1] = muCandRef2->globalTrack()->dxy(vtx->position());
                        //regrecoKids_sigmaDxy[NrDMu][1] = sqrt(muCandRef2->globalTrack()->dxyError()*muCandRef2->globalTrack()->dxyError() + vtx->yError()*vtx->yError()+vtx->xError()*vtx->xError());
                        //regrecoKids_dz[NrDMu][1] = muCandRef2->globalTrack()->dz(vtx->position());
                        //regrecoKids_sigmaDz[NrDMu][1] = sqrt(muCandRef2->globalTrack()->dzError()*muCandRef2->globalTrack()->dzError()+vtx->zError()*vtx->zError());
                        //regrecoKids_nhits[NrDMu][1] = muCandRef2->globalTrack()->numberOfValidHits();
                    }else{
                        regrecoKids_pt[NrDMu][0] = muCandRef2->globalTrack()->pt();regrecoKids_eta[NrDMu][0]=muCandRef2->globalTrack()->eta();
                        regrecoKids_phi[NrDMu][0]=muCandRef2->globalTrack()->phi();regrecoKids_p[NrDMu][0] = muCandRef2->globalTrack()->p();
                        //regrecoKids_dxy[NrDMu][0] = muCandRef2->globalTrack()->dxy(vtx->position());
                        //regrecoKids_sigmaDxy[NrDMu][0]=sqrt(muCandRef2->globalTrack()->dxyError()*muCandRef2->globalTrack()->dxyError() + vtx->yError()*vtx->yError()+vtx->xError()*vtx->xError());
                        //regrecoKids_dz[NrDMu][0] = muCandRef2->globalTrack()->dz(vtx->position());
                        //regrecoKids_sigmaDz[NrDMu][0] = sqrt(muCandRef2->globalTrack()->dzError()*muCandRef2->globalTrack()->dzError()+vtx->zError()*vtx->zError());
                        //regrecoKids_nhits[NrDMu][0] = muCandRef2->globalTrack()->numberOfValidHits();

                        regrecoKids_pt[NrDMu][1] = muCandRef1->globalTrack()->pt();regrecoKids_eta[NrDMu][1]=muCandRef1->globalTrack()->eta();
                        regrecoKids_phi[NrDMu][1]=muCandRef1->globalTrack()->phi();regrecoKids_p[NrDMu][1] = muCandRef1->globalTrack()->p();
                        //regrecoKids_dxy[NrDMu][1] = muCandRef1->globalTrack()->dxy(vtx->position());
                        //regrecoKids_sigmaDxy[NrDMu][1] = sqrt(muCandRef1->globalTrack()->dxyError()*muCandRef1->globalTrack()->dxyError() + vtx->yError()*vtx->yError()+vtx->xError()*vtx->xError());
                        //regrecoKids_dz[NrDMu][1] = muCandRef1->globalTrack()->dz(vtx->position());
                        //regrecoKids_sigmaDz[NrDMu][1] = sqrt(muCandRef1->globalTrack()->dzError()*muCandRef1->globalTrack()->dzError()+vtx->zError()*vtx->zError());
                        //regrecoKids_nhits[NrDMu][1] = muCandRef1->globalTrack()->numberOfValidHits();
                    }

                    NrDMu++;
                }
            }
            nRegRDMu = NrDMu;
            cout<<"number of dimuon : "<<nRegRDMu<<endl;
        }
    }


    reco::BeamSpot beamSpot;
    edm::Handle<reco::BeamSpot> recoBeamSpotHandle;
    iEvent.getByLabel(BeamSpot_,recoBeamSpotHandle);
    if (!recoBeamSpotHandle.failedToGet())  beamSpot = *recoBeamSpotHandle;

    // L2 trigger info
    if(L2_TRG_){

        cout<<"dmoon chk 3 !!!"<<endl;
        edm::Handle<RecoChargedCandidateCollection> l2muons;
        iEvent.getByLabel(L2MuCands_, l2muons);
        if(!l2muons.isValid()){
            cout<<" No L2 Muon Candidates !!!!!"<<endl;
        }else{
            int L2Mu = 0;
            for(RecoChargedCandidateCollection::const_iterator cand=l2muons->begin(); cand!=l2muons->end(); cand++){
                TrackRef l2mu = cand->get<TrackRef>();
                l2mu_pt[L2Mu] = l2mu->pt(); l2mu_phi[L2Mu] = l2mu->phi(); l2mu_eta[L2Mu] = l2mu->eta();
                const reco::HitPattern& hitp = l2mu->hitPattern();
                l2mu_nPixHits[L2Mu] = hitp.numberOfValidPixelHits();
                l2mu_nHits[L2Mu] = hitp.numberOfHits();
                l2mu_nTrkHits[L2Mu] = hitp.numberOfValidTrackerHits();
                l2mu_nStrHits[L2Mu] = hitp.numberOfValidStripHits();
                l2mu_dr[L2Mu] = l2mu->dxy(beamSpot.position());
                l2mu_dz[L2Mu] = l2mu->dz(beamSpot.position());
                L2Mu++;
            }
            nL2Mu = L2Mu;
            cout<<" "<<L2Mu<<" L2 Muon Candidates found !!!!!"<<endl;
        }
    }

    // L3 trigger info
    if(L3_TRG_){

        cout<<"dmoon chk 4 !!!"<<endl;
        edm::Handle<RecoChargedCandidateCollection> l3muons;
        iEvent.getByLabel(L3MuCands_, l3muons);
        if(!l3muons.isValid()){
            cout<<" No L3 Muon Candidates !!!!!"<<endl;
        }else{
            int L3Mu = 0;
            for(RecoChargedCandidateCollection::const_iterator cand=l3muons->begin(); cand!=l3muons->end(); cand++){
                TrackRef l3mu = cand->get<TrackRef>();
                l3mu_pt[L3Mu] = l3mu->pt(); l3mu_phi[L3Mu] = l3mu->phi(); l3mu_eta[L3Mu] = l3mu->eta();
                const reco::HitPattern& hitp = l3mu->hitPattern();
                l3mu_nPixHits[L3Mu] = hitp.numberOfValidPixelHits();
                l3mu_nHits[L3Mu] = hitp.numberOfHits();
                l3mu_nTrkHits[L3Mu] = hitp.numberOfValidTrackerHits();
                l3mu_nStrHits[L3Mu] = hitp.numberOfValidStripHits();
                l3mu_dr[L3Mu] = l3mu->dxy(beamSpot.position());
                l3mu_dz[L3Mu] = l3mu->dz(beamSpot.position());
                L3Mu++;
            }
            nL3Mu = L3Mu;
            cout<<" "<<L3Mu<<" L3 Muon Candidates found !!!!!"<<endl;
        }
    }
    if(PATMuons_){
        edm::Handle<edm::View<pat::Muon> > pMuons;
        iEvent.getByLabel("patMuonsWithTrigger", pMuons);

        int nPMuons = 0;
        if(pMuons.isValid()){
            edm::View<pat::Muon> pMuonColl= *pMuons;
            int pMuonsize = pMuonColl.size();

            int npMuon=pMuonColl.size();

            if(npMuon < 1000)
            {  
                for ( int i=0 ; i < pMuonsize ; ++i ){
                    const pat::Muon& pmuon = (*pMuons)[i];

                    patMuon_eta[nPMuons] = pmuon.eta();
                    patMuon_pt[nPMuons] = pmuon.pt();
                    patMuon_phi[nPMuons] = pmuon.phi();
                    patMuon_p[nPMuons] = pmuon.p();
                    if(pmuon.isGlobalMuon()){patMuon_glb[nPMuons] = 1;}else{patMuon_glb[nPMuons] = 0;}
                    if(pmuon.isTrackerMuon()){patMuon_trk[nPMuons] = 1;}else{patMuon_trk[nPMuons] = 0;}
                    if(pmuon.isStandAloneMuon()){patMuon_sta[nPMuons] = 1;}else{patMuon_sta[nPMuons] = 0;}
                    if(!pmuon.triggerObjectMatchesByPath("HLT_PAL1DoubleMuOpen_v1").empty()){patMuonTrg_bit1[nPMuons]=1;}else{patMuonTrg_bit1[nPMuons]=0;}
                    if(!pmuon.triggerObjectMatchesByPath("HLT_PAL1DoubleMu0_HighQ_v1").empty()){patMuonTrg_bit2[nPMuons]=1;}else{patMuonTrg_bit2[nPMuons]=0;}
                    if(!pmuon.triggerObjectMatchesByPath("HLT_PAL2DoubleMu3_v1").empty()){patMuonTrg_bit3[nPMuons]=1;}else{patMuonTrg_bit3[nPMuons]=0;}
                    if(!pmuon.triggerObjectMatchesByPath("HLT_PAMu3_v1").empty()){patMuonTrg_bit4[nPMuons]=1;}else{patMuonTrg_bit4[nPMuons]=0;}
                    if(!pmuon.triggerObjectMatchesByPath("HLT_PAMu7_v1").empty()){patMuonTrg_bit5[nPMuons]=1;}else{patMuonTrg_bit5[nPMuons]=0;}
                    if(!pmuon.triggerObjectMatchesByPath("HLT_PAMu12_v1").empty()){patMuonTrg_bit6[nPMuons]=1;}else{patMuonTrg_bit6[nPMuons]=0;}

                    if(!pmuon.triggerObjectMatchesByFilter("hltL1fL1sPAL1DoubleMuOpenL1Filtered0").empty()){patMuonTrgF_bit1[nPMuons]=1;}else{patMuonTrgF_bit1[nPMuons]=0;}
                    if(!pmuon.triggerObjectMatchesByFilter("hltL1fL1sPAL1DoubleMu0HighQL1FilteredHighQ").empty()){patMuonTrgF_bit2[nPMuons]=1;}else{patMuonTrgF_bit2[nPMuons]=0;}
                    if(!pmuon.triggerObjectMatchesByFilter("hltL2fL1sPAL2DoubleMu3L2Filtered3").empty()){patMuonTrgF_bit3[nPMuons]=1;}else{patMuonTrgF_bit3[nPMuons]=0;}
                    if(!pmuon.triggerObjectMatchesByFilter("hltL3fL2sMu3L3Filtered3").empty()){patMuonTrgF_bit4[nPMuons]=1;}else{patMuonTrgF_bit4[nPMuons]=0;}
                    if(!pmuon.triggerObjectMatchesByFilter("hltL3fL2sMu7L3Filtered7").empty()){patMuonTrgF_bit5[nPMuons]=1;}else{patMuonTrgF_bit5[nPMuons]=0;}
                    if(!pmuon.triggerObjectMatchesByFilter("hltL3fL2sMu12L3Filtered12").empty()){patMuonTrgF_bit6[nPMuons]=1;}else{patMuonTrgF_bit6[nPMuons]=0;}

                    edm::Handle<reco::VertexCollection> vertexCollection;
                    iEvent.getByLabel(vertex_,vertexCollection);
                    vertices = vertexCollection.product();
                    const reco::Vertex *vtx = &(vertices->at(0));
                    RefVtx = vtx->position();

                    if(pmuon.isTrackerMuon() ){
                        TrackRef iTrack =pmuon.innerTrack();
                        const reco::HitPattern& p1=iTrack->hitPattern();
                        patMuon_nTrkHits[nPMuons]=iTrack->found();
                        patMuon_nchi2In[nPMuons]=iTrack->normalizedChi2();
                        patMuon_arbitrated[nPMuons]=pmuon.muonID("TrackerMuonArbitrated");
                        patMuon_stationTight[nPMuons]=pmuon.muonID("TMOneStationTight");
                        patMuon_nTrkMeas[nPMuons]=p1.trackerLayersWithMeasurement();
                        patMuon_nPixLays[nPMuons]=p1.pixelLayersWithMeasurement();
                        patMuon_dxy[nPMuons]=iTrack->dxy(RefVtx);
                        patMuon_dz[nPMuons]=iTrack->dz(RefVtx);
                        if(pmuon.isGlobalMuon())
                        {
                            TrackRef gTrack =pmuon.globalTrack();
                            const reco::HitPattern& q1=gTrack->hitPattern();
                            patMuon_nMuValHits[nPMuons]=q1.numberOfValidMuonHits();
                            patMuon_nchi2Gl[nPMuons]=gTrack->chi2()/gTrack->ndof();
                        }else{
                            patMuon_nMuValHits[nPMuons]=-999.9;
                            patMuon_nchi2Gl[nPMuons]=-999.9;
                        }
                    }else{
                        patMuon_nTrkHits[nPMuons]=-999.9;
                        patMuon_nchi2In[nPMuons]=-999.9;
                        patMuon_arbitrated[nPMuons]=-999.9;
                        patMuon_stationTight[nPMuons]=-999.9;
                        patMuon_nTrkMeas[nPMuons]=-999.9;
                        patMuon_nPixLays[nPMuons]=-999.9;
                        patMuon_dxy[nPMuons]=-999.9;
                        patMuon_dz[nPMuons]=-999.9;
                        patMuon_nMuValHits[nPMuons]=-999.9;
                        patMuon_nchi2Gl[nPMuons]=-999.9;
                    }
                    nPMuons++;
                }//muon loop
            }//gmuon <1000
            npMuons = nPMuons;
        }else{
            cout<<"No PAT Muons !!!"<<endl;
        }
    }

    rTree->Fill();

}


// ------------ method called once each job just before starting event loop  ------------
    void 
HLTrgAna::beginJob()
{
    hOutputFile   = new TFile( fOutputFile_.c_str(), "RECREATE" ) ;
    rTree = new TTree("Ana","Dilepton Analysis");

    
    rTree->Branch("Evt",                          &Evt,                           "Evt/I");
    rTree->Branch("Lumi",                         &Lumi,                          "Lumi/I");
    rTree->Branch("Run",                          &Run,                           "Run/I");
    

    if(L1_TRG_){
        rTree->Branch("nL1_SingleMu3",                &nL1_SingleMu3,                 "nL1_SingleMu3/I");
        rTree->Branch("nL1_SingleMu7",                &nL1_SingleMu7,                 "nL1_SingleMu7/I");
        rTree->Branch("nL1_SingleMu12",               &nL1_SingleMu12,                "nL1_SingleMu12/I");
        rTree->Branch("nL1_DoubleMuOpen_BptxAND",     &nL1_DoubleMuOpen_BptxAND,      "nL1_DoubleMuOpen_BptxAND/I");
        rTree->Branch("nL1_DoubleMu0",                &nL1_DoubleMu0,                 "nL1_DoubleMu0/I");
    }


    if(RECO_){
        //Reco DiMuon
        rTree->Branch("nRDMu",            &nRDMu,             "nRDMu/I");
        rTree->Branch("recoDimu_pt",      &recoDimu_pt,       "recoDimu_pt[nRDMu]/D");
        rTree->Branch("recoDimu_ch",      &recoDimu_ch,       "recoDimu_ch[nRDMu]/I");
        rTree->Branch("recoDimu_p",       &recoDimu_p,        "recoDimu_p[nRDMu]/D");
        rTree->Branch("recoDimu_y",       &recoDimu_y,        "recoDimu_y[nRDMu]/D");
        rTree->Branch("recoDimu_eta",     &recoDimu_eta,      "recoDimu_eta[nRDMu]/D");
        rTree->Branch("recoDimu_phi",     &recoDimu_phi,      "recoDimu_phi[nRDMu]/D");
        rTree->Branch("recoDimu_mass",    &recoDimu_mass,     "recoDimu_mass[nRDMu]/D");

        rTree->Branch("recoKids_pt",      &recoKids_pt,       "recoKids_pt[nRDMu][2]/D");
        rTree->Branch("recoKids_p",       &recoKids_p,        "recoKids_p[nRDMu][2]/D");
        rTree->Branch("recoKids_phi",     &recoKids_phi,      "recoKids_phi[nRDMu][2]/D");
        rTree->Branch("recoKids_eta",     &recoKids_eta,      "recoKids_eta[nRDMu][2]/D");

        rTree->Branch("recoKids_dxy",      &recoKids_dxy,       "recoKids_dxy[nRDMu][2]/D");
        rTree->Branch("recoKids_dz",       &recoKids_dz,        "recoKids_dz[nRDMu][2]/D");
        rTree->Branch("recoKids_sigmaDxy", &recoKids_sigmaDxy,  "recoKids_sigmaDxy[nRDMu][2]/D");
        rTree->Branch("recoKids_sigmaDz",  &recoKids_sigmaDz,   "recoKids_sigmaDz[nRDMu][2]/D");

        // reco::Muon
        rTree->Branch("nTMu",               &nTMu,               "nTMu/I");
        rTree->Branch("nRGMu",              &nRGMu,              "nRGMu/I");
        rTree->Branch("nRSMu",              &nRSMu,              "nRSMu/I");
        rTree->Branch("recoGlb_nhits",      &recoGlb_nhits,      "recoGlb_nhits[nRGMu]/I");
        rTree->Branch("recoGlb_pt",         &recoGlb_pt,         "recoGlb_pt[nRGMu]/D");
        rTree->Branch("recoGlb_p",          &recoGlb_p,          "recoGlb_p[nRGMu]/D");
        rTree->Branch("recoGlb_eta",        &recoGlb_eta,        "recoGlb_eta[nRGMu]/D");
        rTree->Branch("recoGlb_phi",        &recoGlb_phi,        "recoGlb_phi[nRGMu]/D");
        rTree->Branch("recoGlb_dxy",        &recoGlb_dxy,        "recoGlb_dxy[nRGMu]/D");
        rTree->Branch("recoGlb_dz",         &recoGlb_dz,         "recoGlb_dz[nRGMu]/D");
        rTree->Branch("recoGlb_sigmaDxy",   &recoGlb_sigmaDxy,   "recoGlb_sigmaDxy[nRGMu]/D");
        rTree->Branch("recoGlb_sigmaDz",    &recoGlb_sigmaDz,    "recoGlb_sigmaDz[nRGMu]/D");

        rTree->Branch("recoSta_nhits",      &recoSta_nhits,      "recoSta_nhits[nRSMu]/I");
        rTree->Branch("recoSta_pt",         &recoSta_pt,         "recoSta_pt[nRSMu]/D");
        rTree->Branch("recoSta_p",          &recoSta_p,          "recoSta_p[nRSMu]/D");
        rTree->Branch("recoSta_eta",        &recoSta_eta,        "recoSta_eta[nRSMu]/D");
        rTree->Branch("recoSta_phi",        &recoSta_phi,        "recoSta_phi[nRSMu]/D");
        rTree->Branch("recoSta_dxy",        &recoSta_dxy,        "recoSta_dxy[nRSMu]/D");
        rTree->Branch("recoSta_dz",         &recoSta_dz,         "recoSta_dz[nRSMu]/D");
        rTree->Branch("recoSta_sigmaDxy",   &recoSta_sigmaDxy,   "recoSta_sigmaDxy[nRSMu]/D");
        rTree->Branch("recoSta_sigmaDz",    &recoSta_sigmaDz,    "recoSta_sigmaDz[nRSMu]/D");

        rTree->Branch("recoMu_pt",         &recoMu_pt,         "recoMu_pt[nTMu]/D");
        rTree->Branch("recoMu_p",          &recoMu_p,          "recoMu_p[nTMu]/D");
        rTree->Branch("recoMu_eta",        &recoMu_eta,        "recoMu_eta[nTMu]/D");
        rTree->Branch("recoMu_phi",        &recoMu_phi,        "recoMu_phi[nTMu]/D");
        rTree->Branch("recoMu_Glb",        &recoMu_Glb,        "recoMu_Glb[nTMu]/I");
        rTree->Branch("recoMu_Sta",        &recoMu_Sta,        "recoMu_Sta[nTMu]/I");
        rTree->Branch("recoMu_Trk",        &recoMu_Trk,        "recoMu_Trk[nTMu]/I");

    }

    if(REGIT_){
        //Regit Reco DiMuon
        rTree->Branch("nRegRDMu",            &nRegRDMu,             "nRegRDMu/I");
        rTree->Branch("regrecoDimu_pt",      &regrecoDimu_pt,       "regrecoDimu_pt[nRegRDMu]/D");
        rTree->Branch("regrecoDimu_ch",      &regrecoDimu_ch,       "regrecoDimu_ch[nRegRDMu]/I");
        rTree->Branch("regrecoDimu_p",       &regrecoDimu_p,        "regrecoDimu_p[nRegRDMu]/D");
        rTree->Branch("regrecoDimu_y",       &regrecoDimu_y,        "regrecoDimu_y[nRegRDMu]/D");
        rTree->Branch("regrecoDimu_eta",     &regrecoDimu_eta,      "regrecoDimu_eta[nRegRDMu]/D");
        rTree->Branch("regrecoDimu_phi",     &regrecoDimu_phi,      "regrecoDimu_phi[nRegRDMu]/D");
        rTree->Branch("regrecoDimu_mass",    &regrecoDimu_mass,     "regrecoDimu_mass[nRegRDMu]/D");

        rTree->Branch("regrecoKids_pt",      &regrecoKids_pt,       "regrecoKids_pt[nRegRDMu][2]/D");
        rTree->Branch("regrecoKids_p",       &regrecoKids_p,        "regrecoKids_p[nRegRDMu][2]/D");
        rTree->Branch("regrecoKids_phi",     &regrecoKids_phi,      "regrecoKids_phi[nRegRDMu][2]/D");
        rTree->Branch("regrecoKids_eta",     &regrecoKids_eta,      "regrecoKids_eta[nRegRDMu][2]/D");

        rTree->Branch("regrecoKids_dxy",      &regrecoKids_dxy,       "regrecoKids_dxy[nRegRDMu][2]/D");
        rTree->Branch("regrecoKids_dz",       &regrecoKids_dz,        "regrecoKids_dz[nRegRDMu][2]/D");
        rTree->Branch("regrecoKids_sigmaDxy", &regrecoKids_sigmaDxy,  "regrecoKids_sigmaDxy[nRegRDMu][2]/D");
        rTree->Branch("regrecoKids_sigmaDz",  &regrecoKids_sigmaDz,   "regrecoKids_sigmaDz[nRegRDMu][2]/D");

        // rereco::Muon
        rTree->Branch("nRegTMu",               &nRegTMu,               "nRegTMu/I");
        rTree->Branch("nRegRGMu",              &nRegRGMu,              "nRegRGMu/I");
        rTree->Branch("nRegRSMu",              &nRegRSMu,              "nRegRSMu/I");
        rTree->Branch("regrecoGlb_nhits",      &regrecoGlb_nhits,      "regrecoGlb_nhits[nRegRGMu]/I");
        rTree->Branch("regrecoGlb_pt",         &regrecoGlb_pt,         "regrecoGlb_pt[nRegRGMu]/D");
        rTree->Branch("regrecoGlb_p",          &regrecoGlb_p,          "regrecoGlb_p[nRegRGMu]/D");
        rTree->Branch("regrecoGlb_eta",        &regrecoGlb_eta,        "regrecoGlb_eta[nRegRGMu]/D");
        rTree->Branch("regrecoGlb_phi",        &regrecoGlb_phi,        "regrecoGlb_phi[nRegRGMu]/D");
        rTree->Branch("regrecoGlb_dxy",        &regrecoGlb_dxy,        "regrecoGlb_dxy[nRegRGMu]/D");
        rTree->Branch("regrecoGlb_dz",         &regrecoGlb_dz,         "regrecoGlb_dz[nRegRGMu]/D");
        rTree->Branch("regrecoGlb_sigmaDxy",   &regrecoGlb_sigmaDxy,   "regrecoGlb_sigmaDxy[nRegRGMu]/D");
        rTree->Branch("regrecoGlb_sigmaDz",    &regrecoGlb_sigmaDz,    "regrecoGlb_sigmaDz[nRegRGMu]/D");

        rTree->Branch("regrecoSta_nhits",      &regrecoSta_nhits,      "regrecoSta_nhits[nRegRSMu]/I");
        rTree->Branch("regrecoSta_pt",         &regrecoSta_pt,         "regrecoSta_pt[nRegRSMu]/D");
        rTree->Branch("regrecoSta_p",          &regrecoSta_p,          "regrecoSta_p[nRegRSMu]/D");
        rTree->Branch("regrecoSta_eta",        &regrecoSta_eta,        "regrecoSta_eta[nRegRSMu]/D");
        rTree->Branch("regrecoSta_phi",        &regrecoSta_phi,        "regrecoSta_phi[nRegRSMu]/D");
        rTree->Branch("regrecoSta_dxy",        &regrecoSta_dxy,        "regrecoSta_dxy[nRegRSMu]/D");
        rTree->Branch("regrecoSta_dz",         &regrecoSta_dz,         "regrecoSta_dz[nRegRSMu]/D");
        rTree->Branch("regrecoSta_sigmaDxy",   &regrecoSta_sigmaDxy,   "regrecoSta_sigmaDxy[nRegRSMu]/D");
        rTree->Branch("regrecoSta_sigmaDz",    &regrecoSta_sigmaDz,    "regrecoSta_sigmaDz[nRegRSMu]/D");

        rTree->Branch("regrecoMu_pt",         &regrecoMu_pt,         "regrecoMu_pt[nTMu]/D");
        rTree->Branch("regrecoMu_p",          &regrecoMu_p,          "regrecoMu_p[nTMu]/D");
        rTree->Branch("regrecoMu_eta",        &regrecoMu_eta,        "regrecoMu_eta[nTMu]/D");
        rTree->Branch("regrecoMu_phi",        &regrecoMu_phi,        "regrecoMu_phi[nTMu]/D");
        rTree->Branch("regrecoMu_Glb",        &regrecoMu_Glb,        "regrecoMu_Glb[nTMu]/I");
        rTree->Branch("regrecoMu_Sta",        &regrecoMu_Sta,        "regrecoMu_Sta[nTMu]/I");
        rTree->Branch("regrecoMu_Trk",        &regrecoMu_Trk,        "regrecoMu_Trk[nTMu]/I");

    }


    /*
       rTree->Branch("nHLT_HIMinBiasBSC_v1",                 &nHLT_HIMinBiasBSC_v1,                 "nHLT_HIMinBiasBSC_v1/I");
       rTree->Branch("nHLT_HIMinBiasHF_v1",                  &nHLT_HIMinBiasHF_v1,                  "nHLT_HIMinBiasHF_v1/I");
       rTree->Branch("nHLT_HIMinBiasHfOrBSC_v1",             &nHLT_HIMinBiasHfOrBSC_v1,             "nHLT_HIMinBiasHfOrBSC_v1/I");
       rTree->Branch("nHLT_HIActivityHF_Single3_v1",         &nHLT_HIActivityHF_Single3_v1,         "nHLT_HIActivityHF_Single3_v1/I");
       rTree->Branch("nHLT_HIActivityHF_Coincidence3_v1",    &nHLT_HIActivityHF_Coincidence3_v1,    "nHLT_HIActivityHF_Coincidence3_v1/I");
       rTree->Branch("nHLT_HIClusterVertexCompatibility_v1", &nHLT_HIClusterVertexCompatibility_v1, "nHLT_HIClusterVertexCompatibility_v1/I");

       rTree->Branch("nHLT_HIL1DoubleMu0_HighQ_v1",               &nHLT_HIL1DoubleMu0_HighQ_v1,     "nHLT_HIL1DoubleMu0_HighQ_v1/I");
       rTree->Branch("nHLT_HIL2DoubleMu3_v1",                     &nHLT_HIL2DoubleMu3_v1,           "nHLT_HIL2DoubleMu3_v1/I");
       rTree->Branch("nHLT_HIL2Mu3_NHitQ_v1",                     &nHLT_HIL2Mu3_NHitQ_v1,           "nHLT_HIL2Mu3_NHitQ_v1/I");
       rTree->Branch("nHLT_HIL2Mu7_v1",                           &nHLT_HIL2Mu7_v1,                 "nHLT_HIL2Mu7_v1/I");
       rTree->Branch("nHLT_HIL2Mu15_v1",                          &nHLT_HIL2Mu15_v1,                "nHLT_HIL2Mu15_v1/I");
       rTree->Branch("nHLT_HIL3DoubleMuOpen_v1",                  &nHLT_HIL3DoubleMuOpen_v1,        "nHLT_HIL3DoubleMuOpen_v1/I");
       rTree->Branch("nHLT_HIL3Mu3_v1",                           &nHLT_HIL3Mu3_v1,                 "nHLT_HIL3Mu3_v1/I");
       rTree->Branch("nHLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v1", &nHLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v1, "nHLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v1/I");
       */

    if(HLT_){
        if(TrgClass_ == 0){
            rTree->Branch("nHLT_HIL1DoubleMuOpen_v5", &nHLT_HIL1DoubleMuOpen_v5, "nHLT_HIL1DoubleMuOpen_v5/I");
            rTree->Branch("nHLT_HIL1DoubleMu0_HighQ_v5", &nHLT_HIL1DoubleMu0_HighQ_v5, "nHLT_HIL1DoubleMu0_HighQ_v5/I");
            rTree->Branch("nHLT_HIL2DoubleMu0_v5", &nHLT_HIL2DoubleMu0_v5, "nHLT_HIL2DoubleMu0_v5/I");
            rTree->Branch("nHLT_HIL2DoubleMu0_NHitQ_v5", &nHLT_HIL2DoubleMu0_NHitQ_v5, "nHLT_HIL2DoubleMu0_NHitQ_v5/I");
            rTree->Branch("nHLT_HIL2DoubleMu0_L1HighQL2NHitQ_v5", &nHLT_HIL2DoubleMu0_L1HighQL2NHitQ_v5, "nHLT_HIL2DoubleMu0_L1HighQL2NHitQ_v5/I");
            rTree->Branch("nHLT_HIL2DoubleMu3_v5", &nHLT_HIL2DoubleMu3_v5, "nHLT_HIL2DoubleMu3_v5/I");
            rTree->Branch("nHLT_HIL3DoubleMuOpen_v7", &nHLT_HIL3DoubleMuOpen_v7, "nHLT_HIL3DoubleMuOpen_v7/I");
            rTree->Branch("nHLT_HIL3DoubleMuOpen_Mgt2_v7", &nHLT_HIL3DoubleMuOpen_Mgt2_v7, "nHLT_HIL3DoubleMuOpen_Mgt2_v7/I");
            rTree->Branch("nHLT_HIL3DoubleMuOpen_Mgt2_SS_v7", &nHLT_HIL3DoubleMuOpen_Mgt2_SS_v7, "nHLT_HIL3DoubleMuOpen_Mgt2_SS_v7/I");
            rTree->Branch("nHLT_HIL3DoubleMuOpen_Mgt2_OS_v7", &nHLT_HIL3DoubleMuOpen_Mgt2_OS_v7, "nHLT_HIL3DoubleMuOpen_Mgt2_OS_v7/I");
            rTree->Branch("nHLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v7", &nHLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v7, "nHLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v7/I");
            rTree->Branch("nHLT_HIL2Mu3_v5", &nHLT_HIL2Mu3_v5, "nHLT_HIL2Mu3_v5/I");
            rTree->Branch("nHLT_HIL2Mu3_NHitQ_v5", &nHLT_HIL2Mu3_NHitQ_v5, "nHLT_HIL2Mu3_NHitQ_v5/I");
            rTree->Branch("nHLT_HIL2Mu7_v5", &nHLT_HIL2Mu7_v5, "nHLT_HIL2Mu7_v5/I");
            rTree->Branch("nHLT_HIL2Mu15_v5", &nHLT_HIL2Mu15_v5, "nHLT_HIL2Mu15_v5/I");
            rTree->Branch("nHLT_HIL3Mu3_v7", &nHLT_HIL3Mu3_v7, "nHLT_HIL3Mu3_v7/I");
        }else if(TrgClass_ == 1){
            rTree->Branch("nHLT_PAL1DoubleMu0_HighQ_v1", &nHLT_PAL1DoubleMu0_HighQ_v1, "nHLT_PAL1DoubleMu0_HighQ_v1/I");
            rTree->Branch("nHLT_PAL1DoubleMuOpen_v1", &nHLT_PAL1DoubleMuOpen_v1, "nHLT_PAL1DoubleMuOpen_v1/I");
            rTree->Branch("nHLT_PAL2DoubleMu3_v1", &nHLT_PAL2DoubleMu3_v1, "nHLT_PAL2DoubleMu3_v1/I");
            rTree->Branch("nHLT_PAMu1_Track1_Mgt2_v1", &nHLT_PAMu1_Track1_Mgt2_v1, "nHLT_PAMu1_Track1_Mgt2_v1/I");
            rTree->Branch("nHLT_PAMu3_Track1_Mgt2_v1", &nHLT_PAMu3_Track1_Mgt2_v1, "nHLT_PAMu3_Track1_Mgt2_v1/I");
            rTree->Branch("nHLT_PAL2Mu3_NHitQ_v1", &nHLT_PAL2Mu3_NHitQ_v1, "nHLT_PAL2Mu3_NHitQ_v1/I");
            rTree->Branch("nHLT_PAMu3_v1", &nHLT_PAMu3_v1, "nHLT_PAMu3_v1/I");
            rTree->Branch("nHLT_PAMu7_v1", &nHLT_PAMu7_v1, "nHLT_PAMu7_v1/I");
            rTree->Branch("nHLT_PAMu12_v1", &nHLT_PAMu12_v1, "nHLT_PAMu12_v1/I");
            rTree->Branch("nHLT_PABTagMu_Jet20_Mu4_v1", &nHLT_PABTagMu_Jet20_Mu4_v1, "nHLT_PABTagMu_Jet20_Mu4_v1/I");
            rTree->Branch("nHLT_PAMu3PFJet20_v1", &nHLT_PAMu3PFJet20_v1, "nHLT_PAMu3PFJet20_v1/I");
            rTree->Branch("nHLT_PAMu3PFJet40_v1", &nHLT_PAMu3PFJet40_v1, "nHLT_PAMu3PFJet40_v1/I");
            rTree->Branch("nHLT_PAMu7PFJet20_v1", &nHLT_PAMu7PFJet20_v1, "nHLT_PAMu7PFJet20_v1/I");
        }
    }

    if(L1_TRG_){
        rTree->Branch("nL1Mu",        &nL1Mu,         "nL1Mu/I");
        rTree->Branch("l1mu_pt",      &l1mu_pt,       "l1mu_pt[nL1Mu]/D");
        rTree->Branch("l1mu_eta",     &l1mu_eta,      "l1mu_eta[nL1Mu]/D");
        rTree->Branch("l1mu_phi",     &l1mu_phi,      "l1mu_phi[nL1Mu]/D");
        rTree->Branch("l1mu_ch",      &l1mu_ch,       "l1mu_ch[nL1Mu]/I");
        rTree->Branch("l1mu_qual",    &l1mu_qual,     "l1mu_qual[nL1Mu]/I");
        rTree->Branch("l1mu_p",       &l1mu_p,        "l1mu_p[nL1Mu]/D");
    }

    if(L2_TRG_){
        // L2 Info
        rTree->Branch("nL2Mu",         &nL2Mu,          "nL2Mu/I");
        rTree->Branch("l2mu_pt",       &l2mu_pt,        "l2mu_pt[nL2Mu]/D");
        rTree->Branch("l2mu_p",        &l2mu_p,         "l2mu_p[nL2Mu]/D");
        rTree->Branch("l2mu_eta",      &l2mu_eta,       "l2mu_eta[nL2Mu]/D");
        rTree->Branch("l2mu_phi",      &l2mu_phi,       "l2mu_phi[nL2Mu]/D");
        rTree->Branch("l2mu_ch",       &l2mu_ch,        "l2mu_ch[nL2Mu]/I");
        rTree->Branch("l2mu_nPixHits", &l2mu_nPixHits,  "l2mu_nPixHits[nL2Mu]/I");
        rTree->Branch("l2mu_nHits",    &l2mu_nHits,     "l2mu_nHits[nL2Mu]/I");
        rTree->Branch("l2mu_nTrkHits", &l2mu_nTrkHits,  "l2mu_nTrkHits[nL2Mu]/I");
        rTree->Branch("l2mu_nStrHits", &l2mu_nStrHits,  "l2mu_nStrHits[nL2Mu]/I");
        rTree->Branch("l2mu_dr",       &l2mu_dr,        "l2mu_dr[nL2Mu]/I");
        rTree->Branch("l2mu_dz",       &l2mu_dz,        "l2mu_dz[nL2Mu]/I");
    }

    if(L3_TRG_){
        // L3 Info
        rTree->Branch("nL3Mu",         &nL3Mu,          "nL3Mu/I");
        rTree->Branch("l3mu_pt",       &l3mu_pt,        "l3mu_pt[nL3Mu]/D");
        rTree->Branch("l3mu_p",        &l3mu_p,         "l3mu_p[nL3Mu]/D");
        rTree->Branch("l3mu_eta",      &l3mu_eta,       "l3mu_eta[nL3Mu]/D");
        rTree->Branch("l3mu_phi",      &l3mu_phi,       "l3mu_phi[nL3Mu]/D");
        rTree->Branch("l3mu_ch",       &l3mu_ch,        "l3mu_ch[nL3Mu]/I");
        rTree->Branch("l3mu_nPixHits", &l3mu_nPixHits,  "l3mu_nPixHits[nL2Mu]/I");
        rTree->Branch("l3mu_nHits",    &l3mu_nHits,     "l3mu_nHits[nL2Mu]/I");
        rTree->Branch("l3mu_nTrkHits", &l3mu_nTrkHits,  "l3mu_nTrkHits[nL2Mu]/I");
        rTree->Branch("l3mu_nStrHits", &l3mu_nStrHits,  "l3mu_nStrHits[nL2Mu]/I");
        rTree->Branch("l3mu_dr",       &l3mu_dr,        "l3mu_dr[nL2Mu]/I");
        rTree->Branch("l3mu_dz",       &l3mu_dz,        "l3mu_dz[nL2Mu]/I");
    }

    if(MC_){
        rTree->Branch("nPar",         &nPar,          "nPar/I");
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
    }

    if(Central_) rTree->Branch("c_bin",        &c_bin,         "c_bin/I");
    if(HiMC_){
        rTree->Branch("Imp",          &Imp,           "Imp/D");
        rTree->Branch("nPart",        &nPart,         "nPart/I");
        rTree->Branch("nColl",        &nColl,         "nColl/I");
        rTree->Branch("nHard",        &nHard,         "nHard/I");
        rTree->Branch("GenRpAng",     &GenRpAng,      "GenRpAng/D");
    }
    if(PATMuons_){
        rTree->Branch("npMuons",            &npMuons,           "npMuons/I");
        rTree->Branch("patMuon_eta",        &patMuon_eta,       "patMuon_eta[npMuons]/D");
        rTree->Branch("patMuon_phi",        &patMuon_phi,       "patMuon_phi[npMuons]/D");
        rTree->Branch("patMuon_pt",         &patMuon_pt,        "patMuon_pt[npMuons]/D");
        rTree->Branch("patMuon_p",          &patMuon_p,         "patMuon_p[npMuons]/D");
        rTree->Branch("patMuon_p",          &patMuon_p,         "patMuon_p[npMuons]/D");
        rTree->Branch("patMuon_glb",        &patMuon_glb,       "patMuon_glb[npMuons]/I");
        rTree->Branch("patMuon_sta",        &patMuon_sta,       "patMuon_sta[npMuons]/I");
        rTree->Branch("patMuon_trk",        &patMuon_trk,       "patMuon_trk[npMuons]/I");
        rTree->Branch("patMuonTrg_bit1",    &patMuonTrg_bit1,   "patMuonTrg_bit1[npMuons]/I");
        rTree->Branch("patMuonTrg_bit2",    &patMuonTrg_bit2,   "patMuonTrg_bit2[npMuons]/I");
        rTree->Branch("patMuonTrg_bit3",    &patMuonTrg_bit3,   "patMuonTrg_bit3[npMuons]/I");
        rTree->Branch("patMuonTrg_bit4",    &patMuonTrg_bit4,   "patMuonTrg_bit4[npMuons]/I");
        rTree->Branch("patMuonTrg_bit5",    &patMuonTrg_bit5,   "patMuonTrg_bit5[npMuons]/I");
        rTree->Branch("patMuonTrg_bit6",    &patMuonTrg_bit6,   "patMuonTrg_bit6[npMuons]/I");
        rTree->Branch("patMuonTrgF_bit1",    &patMuonTrgF_bit1,   "patMuonTrgF_bit1[npMuons]/I");
        rTree->Branch("patMuonTrgF_bit2",    &patMuonTrgF_bit2,   "patMuonTrgF_bit2[npMuons]/I");
        rTree->Branch("patMuonTrgF_bit3",    &patMuonTrgF_bit3,   "patMuonTrgF_bit3[npMuons]/I");
        rTree->Branch("patMuonTrgF_bit4",    &patMuonTrgF_bit4,   "patMuonTrgF_bit4[npMuons]/I");
        rTree->Branch("patMuonTrgF_bit5",    &patMuonTrgF_bit5,   "patMuonTrgF_bit5[npMuons]/I");
        rTree->Branch("patMuonTrgF_bit6",    &patMuonTrgF_bit6,   "patMuonTrgF_bit6[npMuons]/I");
        rTree->Branch("patMuon_nTrkHits",   &patMuon_nTrkHits,  "patMuon_nTrkHits[npMuons]/I");
        rTree->Branch("patMuon_arbitrated",     &patMuon_arbitrated,    "patMuon_arbitrated[npMuons]/I");
        rTree->Branch("patMuon_stationTight",   &patMuon_stationTight,  "patMuon_stationTight[npMuons]/I");
        rTree->Branch("patMuon_nTrkMeas",       &patMuon_nTrkMeas,      "patMuon_nTrkMeas[npMuons]/I");
        rTree->Branch("patMuon_nPixLays",       &patMuon_nPixLays,      "patMuon_nPixLays[npMuons]/I");
        rTree->Branch("patMuon_nMuValHits",     &patMuon_nMuValHits,    "patMuon_nMuValHits[npMuons]/I");
        rTree->Branch("patMuon_nchi2In",        &patMuon_nchi2In,       "patMuon_nchi2In[npMuons]/D");
        rTree->Branch("patMuon_nchi2Gl",        &patMuon_nchi2Gl,       "patMuon_nchi2Gl[npMuons]/D");
        rTree->Branch("patMuon_dxy",            &patMuon_dxy,           "patMuon_dxy[npMuons]/D");
        rTree->Branch("patMuon_dz",             &patMuon_dz,            "patMuon_dz[npMuons]/D");
    }


}

// ------------ method called once each job just after ending the event loop  ------------
    void 
HLTrgAna::endJob() 
{

    hOutputFile->SetCompressionLevel(2);
    hOutputFile->cd();

    hOutputFile->Write();
    hOutputFile->Close();

}

// ------------ method called when starting to processes a run  ------------
    void 
HLTrgAna::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
    void 
HLTrgAna::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
    void 
HLTrgAna::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
    void 
HLTrgAna::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
HLTrgAna::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
    //The following says we do not know what parameters are allowed so do no validation
    // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(HLTrgAna);
