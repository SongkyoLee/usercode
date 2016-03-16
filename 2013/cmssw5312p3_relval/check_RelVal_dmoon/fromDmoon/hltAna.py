# Auto generated configuration file
# using: 
# Revision: 1.207 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: l1test -s DIGI,L1,DIGI2RAW,HLT:HIon --conditions auto:mc --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('HLT2')

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'STARTHI53_V28::All'
process.load("Configuration.StandardSequences.Reconstruction_cff")
#process.load("HLTrigger.Configuration.HLT_PIon_cff")

from HeavyIonsAnalysis.Configuration.CommonFunctions_cff import *
overrideCentrality(process)

process.HeavyIonGlobalParameters = cms.PSet(
        centralityVariable = cms.string("HFtowersPlusTrunc"),
        nonDefaultGlauberModel = cms.string(""),
        centralitySrc = cms.InputTag("pACentrality")
)

process.load('RecoHI.HiCentralityAlgos.HiCentrality_cfi')

process.options = cms.untracked.PSet(
    wantSummary=cms.untracked.bool(True),
    SkipEvent = cms.untracked.vstring('ProductNotFound')
)

process.load("MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff")

from MuonAnalysis.MuonAssociators.muonL1Match_cfi import *
muonL1Match.matched = cms.InputTag("hltL1extraParticles")

from MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff import *
useL1MatchingWindowForSinglets(process)
changeTriggerProcessName(process, "HLT") # DATA Mix
patMuonsWithoutTrigger.pvSrc = cms.InputTag("hiSelectedVertex") # Heavy Ion vertex collection

# HLT dimuon trigger
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltZMMHI = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
#process.hltZMMHI.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT2") # signal
process.hltZMMHI.TriggerResultsTag = cms.InputTag("TriggerResults","","DATAMIX") # DATA Mix
process.hltZMMHI.HLTPaths = ["HLT_HIL2Mu20"]
process.hltZMMHI.throw = False
process.hltZMMHI.andOr = True

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

# Input source
process.source = cms.Source("PoolSource",
    #skipEvents = cms.untracked.uint32(0), 
    duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
    fileNames = cms.untracked.vstring(
        "/store/user/dmoon/cms538HI/WMuNu_MC_5.02TeV/Onia2MuMu_2ndL1/WMuNu_MC_5.02TeV_Onia2MuMu_1.root",
        "/store/user/dmoon/cms538HI/WMuNu_MC_5.02TeV/Onia2MuMu_2ndL1/WMuNu_MC_5.02TeV_Onia2MuMu_2.root",
        "/store/user/dmoon/cms538HI/WMuNu_MC_5.02TeV/Onia2MuMu_2ndL1/WMuNu_MC_5.02TeV_Onia2MuMu_3.root",
        "/store/user/dmoon/cms538HI/WMuNu_MC_5.02TeV/Onia2MuMu_2ndL1/WMuNu_MC_5.02TeV_Onia2MuMu_4.root",
        "/store/user/dmoon/cms538HI/WMuNu_MC_5.02TeV/Onia2MuMu_2ndL1/WMuNu_MC_5.02TeV_Onia2MuMu_5.root",
        "/store/user/dmoon/cms538HI/WMuNu_MC_5.02TeV/Onia2MuMu_2ndL1/WMuNu_MC_5.02TeV_Onia2MuMu_6.root",
        "/store/user/dmoon/cms538HI/WMuNu_MC_5.02TeV/Onia2MuMu_2ndL1/WMuNu_MC_5.02TeV_Onia2MuMu_7.root",
        "/store/user/dmoon/cms538HI/WMuNu_MC_5.02TeV/Onia2MuMu_2ndL1/WMuNu_MC_5.02TeV_Onia2MuMu_8.root",
        "/store/user/dmoon/cms538HI/WMuNu_MC_5.02TeV/Onia2MuMu_2ndL1/WMuNu_MC_5.02TeV_Onia2MuMu_9.root",
        "/store/user/dmoon/cms538HI/WMuNu_MC_5.02TeV/Onia2MuMu_2ndL1/WMuNu_MC_5.02TeV_Onia2MuMu_10.root",
        "/store/user/dmoon/cms538HI/WMuNu_MC_5.02TeV/Onia2MuMu_2ndL1/WMuNu_MC_5.02TeV_Onia2MuMu_11.root",
        "/store/user/dmoon/cms538HI/WMuNu_MC_5.02TeV/Onia2MuMu_2ndL1/WMuNu_MC_5.02TeV_Onia2MuMu_12.root",
        "/store/user/dmoon/cms538HI/WMuNu_MC_5.02TeV/Onia2MuMu_2ndL1/WMuNu_MC_5.02TeV_Onia2MuMu_13.root",
        "/store/user/dmoon/cms538HI/WMuNu_MC_5.02TeV/Onia2MuMu_2ndL1/WMuNu_MC_5.02TeV_Onia2MuMu_14.root",
        "/store/user/dmoon/cms538HI/WMuNu_MC_5.02TeV/Onia2MuMu_2ndL1/WMuNu_MC_5.02TeV_Onia2MuMu_15.root",
        "/store/user/dmoon/cms538HI/WMuNu_MC_5.02TeV/Onia2MuMu_2ndL1/WMuNu_MC_5.02TeV_Onia2MuMu_16.root",
        "/store/user/dmoon/cms538HI/WMuNu_MC_5.02TeV/Onia2MuMu_2ndL1/WMuNu_MC_5.02TeV_Onia2MuMu_17.root",
        "/store/user/dmoon/cms538HI/WMuNu_MC_5.02TeV/Onia2MuMu_2ndL1/WMuNu_MC_5.02TeV_Onia2MuMu_18.root",
        "/store/user/dmoon/cms538HI/WMuNu_MC_5.02TeV/Onia2MuMu_2ndL1/WMuNu_MC_5.02TeV_Onia2MuMu_19.root",
        "/store/user/dmoon/cms538HI/WMuNu_MC_5.02TeV/Onia2MuMu_2ndL1/WMuNu_MC_5.02TeV_Onia2MuMu_20.root",
        "/store/user/dmoon/cms538HI/WMuNu_MC_5.02TeV/Onia2MuMu_2ndL1/WMuNu_MC_5.02TeV_Onia2MuMu_21.root",
        "/store/user/dmoon/cms538HI/WMuNu_MC_5.02TeV/Onia2MuMu_2ndL1/WMuNu_MC_5.02TeV_Onia2MuMu_22.root",
        "/store/user/dmoon/cms538HI/WMuNu_MC_5.02TeV/Onia2MuMu_2ndL1/WMuNu_MC_5.02TeV_Onia2MuMu_23.root",
        "/store/user/dmoon/cms538HI/WMuNu_MC_5.02TeV/Onia2MuMu_2ndL1/WMuNu_MC_5.02TeV_Onia2MuMu_24.root",
        "/store/user/dmoon/cms538HI/WMuNu_MC_5.02TeV/Onia2MuMu_2ndL1/WMuNu_MC_5.02TeV_Onia2MuMu_25.root",
    ),
)

process.analyzer = cms.EDAnalyzer('HLTrgAna',
        genSource = cms.untracked.InputTag("hiGenParticles"),
        L1MuCands = cms.untracked.InputTag("l1extraParticles"),
        #L1MuCands = cms.untracked.InputTag("hltL1extraParticles"),
        L2MuCands = cms.untracked.InputTag("hltL2MuonCandidates"),
        L3MuCands = cms.untracked.InputTag("hltL3MuonCandidates"),
        gtObjects = cms.untracked.InputTag("gtDigis"),
        #gtObjects = cms.untracked.InputTag("hltGtDigis"),
        vertex = cms.untracked.InputTag("offlinePrimaryVertices"),
        #vertex = cms.untracked.InputTag("hltPixelVertices"),
        BeamSpot = cms.untracked.InputTag("BeamSpot"),
        TriggerResults = cms.InputTag("TriggerResults","","HLT"),
        #TriggerResults = cms.InputTag("TriggerResults","","HLT1"),
        #TriggerResults = cms.InputTag("TriggerResults","","DATAMIX"),
        muTrackTag = cms.InputTag("globalMuons"),
        muontag = cms.untracked.InputTag("muons"),
        staMuonsTag = cms.InputTag("standAloneMuons","UpdatedAtVtx"),
        patMuonsTag = cms.InputTag("patMuonsWithTrigger"),
        hOutputFile = cms.untracked.string("HLTrgAna_RelVal_JpsiMM.root"),
        doMC = cms.bool(True),
        doHiMC = cms.bool(False),
        doSIM = cms.bool(False),
        doL1Bit = cms.bool(True),
        doL1 = cms.bool(True),
        doL2 = cms.bool(True),
        doL3 = cms.bool(True),
        doHLT = cms.bool(True),
        doRECO = cms.bool(True),
        doREGIT = cms.bool(True),
        TrgClass = cms.untracked.int32(0), # 0 : PbPb, 1 : pPb
        NoTrg = cms.untracked.int32(16), # No of Trg
        doCentrality = cms.bool(False),
        doPAT = cms.bool(False),
)

process.totalAnalyzer = cms.Path(process.analyzer)

