# Auto generated configuration file
# using: 
# Revision: 1.207 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: l1test -s DIGI,L1,DIGI2RAW,HLT:HIon --conditions auto:mc --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('HLTAna')

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#process.load('CmsHi.Analysis2010.CommonFunctions_cff')

#process.GlobalTag.globaltag = 'GR10_P_V12::All'
##process.GlobalTag.globaltag = 'START39_V4HI::All'
process.GlobalTag.globaltag = 'STARTHI53_V17::All'


'''
process.HeavyIonGlobalParameters = cms.PSet(
    centralitySrc = cms.InputTag("hiCentrality"),
    centralityVariable = cms.string("HFhits"),
    nonDefaultGlauberModel = cms.string("")
)

process.makeCentralityTableTFile = cms.EDAnalyzer('CentralityTableProducer',
    isMC = cms.untracked.bool(False),
    makeDBFromTFile = cms.untracked.bool(False),
    makeTFileFromDB = cms.untracked.bool(True)
)
from CmsHi.Analysis2010.CommonFunctions_cff import *
overrideCentrality(process)
'''
process.options = cms.untracked.PSet(wantSummary=cms.untracked.bool(True))

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

# Input source
process.source = cms.Source("PoolSource",
#    skipEvents = cms.untracked.uint32(0), 
    duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
    fileNames = cms.untracked.vstring(
      _input_
      #'rfio:',
	###'root://eoscms.cern.ch//eos/cms/store/group/phys_heavyions/dileptons/mironov/ppMcTemplate_regit/ppTempRegit_200.root',
	###'file:pythiagun_Jpsitomumu_GEN_SIM_DIGI_RECO_2.76TeV_evt3k_999_20121204.root'
    )
)

process.muonSelector = cms.EDFilter("MuonSelector",
    src = cms.InputTag("muons"),
    cut = cms.string("(isStandAloneMuon || isGlobalMuon) && pt > 1."),
    filter = cms.bool(True)
)
process.muonFilter = cms.EDFilter("MuonCountFilter",
    src = cms.InputTag("muonSelector"),
    minNumber = cms.uint32(1)
)

process.analyzer = cms.EDAnalyzer('HLTrgAna_trk',
        genSource = cms.untracked.InputTag("hiGenParticles"),
        L2MuCands = cms.untracked.InputTag("hltL2MuonCandidates"),
        TriggerResults = cms.InputTag("TriggerResults","","HLT"),
        muTrackTag = cms.InputTag("globalMuons"), ##regular
        ##muTrackTag = cms.InputTag("reglobalMuons"), ##regit
        staMuonsTag = cms.InputTag("standAloneMuons","UpdatedAtVtx"),
        hOutputFile = cms.untracked.string("_output_file_"),
        ##hOutputFile = cms.untracked.string("pythiagun_hin10006_3000evttest_20121204.root"),
        doMC = cms.bool(True),
        doHiMC = cms.bool(False),
        doSIM = cms.bool(False),
        doL1 = cms.bool(False),
        doL2 = cms.bool(False),
        doRECO = cms.bool(True),
        doHLT = cms.bool(False),
        doCentrality = cms.bool(False),
	##primaryVertexTag = cms.InputTag("hiSelectedVertex"),
	primaryVertexTag = cms.InputTag("offlinePrimaryVertices")
)

#process.anlzr = cms.Path(process.muonSelector + process.muonFilter + process.analyzer)
process.anlzr = cms.Path(process.analyzer)

process.ana = cms.Schedule(
    process.anlzr
)

process.schedule = cms.Schedule()
process.schedule.extend(process.ana)


