import FWCore.ParameterSet.Config as cms

process = cms.Process("kyoEmuAnalyzer")
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.options.allowUnscheduled = cms.untracked.bool(True)
process.load("FWCore.MessageService.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(50) )

process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring())
#process.source.fileNames.append('file:/cmsdas/scratch/jlee/ZprimeToMuMu_M-5000_TuneCUETP8M1_13TeV-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM/FAFCC1F1-CA34-E511-8F18-0002C92DB418.root')
process.source.fileNames.append('file:_inputfile_')

process.tree = cms.EDAnalyzer("kyoEmuAnalyzer",
    vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
    muons = cms.InputTag("slimmedMuons"),
    elecs = cms.InputTag("slimmedElectrons"),
    jets = cms.InputTag("slimmedJets"),
    mets = cms.InputTag("slimmedMETs"),
    mcLabel = cms.InputTag("prunedGenParticles"),
)

process.TFileService = cms.Service("TFileService",
#    fileName = cms.string("out_tree_RD_mumu.root"
    fileName = cms.string("_outputfile_"
))

process.p = cms.Path(process.tree)
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

