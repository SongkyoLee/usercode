import FWCore.ParameterSet.Config as cms


### genjet cleaning for improved matching in HI environment

from RecoHI.HiJetAlgos.HiGenCleaner_cff import *

iterativeCone5HiCleanedGenJets = heavyIonCleanedGenJets.clone( src = cms.InputTag('iterativeCone5HiGenJets'))
iterativeCone7HiCleanedGenJets = heavyIonCleanedGenJets.clone( src = cms.InputTag('iterativeCone7HiGenJets'))
ak3HiCleanedGenJets = heavyIonCleanedGenJets.clone( src = cms.InputTag('ak3HiGenJets'))
ak5HiCleanedGenJets = heavyIonCleanedGenJets.clone( src = cms.InputTag('ak5HiGenJets'))
ak7HiCleanedGenJets = heavyIonCleanedGenJets.clone( src = cms.InputTag('ak7HiGenJets'))

#from JetMETCorrections.Configuration.JetCorrectionsRecord_cfi import *
#from RecoJets.Configuration.RecoJetAssociations_cff import *

process = cms.Process("hiJETVALIDATION")

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.Geometry.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('RecoJets.Configuration.GenJetParticles_cff')
process.load('RecoHI.HiJetAlgos.HiGenJets_cff')
process.load('RecoHI.HiJetAlgos.HiRecoJets_cff')
process.load('RecoHI.HiJetAlgos.HiRecoPFJets_cff')


process.GlobalTag.globaltag = 'STARTHI53_V28::All'
#process.GlobalTag.globaltag = 'auto:starthi_HIon'

#process.load("Configuration.StandardSequences.Services_cff")
#process.load("Configuration.StandardSequences.Simulation_cff")
#process.load("Configuration.StandardSequences.MixingNoPileUp_cff")
#process.load("Configuration.StandardSequences.VtxSmearedGauss_cff")
#process.load("Configuration.StandardSequences.Geometry_cff")
#process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("FWCore.MessageLogger.MessageLogger_cfi")

#from JetMETCorrections.Configuration.JetCorrectionServicesAllAlgos_cff import *
#
#
# DQM
#
process.load("DQMServices.Core.DQM_cfg")

# check # of bins
#process.load("DQMServices.Components.DQMStoreStats_cfi")

#process.load("JetMETCorrections.Configuration.JetPlusTrackCorrections_cff")
#process.load("JetMETCorrections.Configuration.ZSPJetCorrections332_cff")
#process.load("JetMETCorrections.Configuration.DefaultJEC_cff")
#process.ak5L1JPTOffset.era = 'Jec11V0'
#process.ak5L1JPTOffset.useCondDB = False

#process.ak5L1JPTOffset.offsetService = cms.string('')

process.load('RecoJets.Configuration.RecoPFJets_cff')
#process.kt6PFJets.doRhoFastjet = True
#process.ak5PFJets.doAreaFastjet = True


# Validation module
process.load("Validation.RecoHI.JetValidationHeavyIons_cff")
process.load("Validation.RecoJets.JetValidation_cff")


process.maxEvents = cms.untracked.PSet(
       input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
#    debugFlag = cms.untracked.bool(True),
#    debugVebosity = cms.untracked.uint32(0),

    fileNames = cms.untracked.vstring(
      '/store/user/yilmaz/hydjetTuneDrum_QuenchedMB_53X_GEN-SIM_v2/Hydjet_Drum_53X_RECO_test16/16a66057d6b9b6b77f83d561b8cd7aea/step3_RAW2DIGI_L1Reco_RECO_VALIDATION_DQM_82_1_Jtp.root',
      '/store/user/yilmaz/hydjetTuneDrum_QuenchedMB_53X_GEN-SIM_v2/Hydjet_Drum_53X_RECO_test16/16a66057d6b9b6b77f83d561b8cd7aea/step3_RAW2DIGI_L1Reco_RECO_VALIDATION_DQM_83_1_9cJ.root',
      '/store/user/yilmaz/hydjetTuneDrum_QuenchedMB_53X_GEN-SIM_v2/Hydjet_Drum_53X_RECO_test16/16a66057d6b9b6b77f83d561b8cd7aea/step3_RAW2DIGI_L1Reco_RECO_VALIDATION_DQM_84_1_Xgg.root',
      '/store/user/yilmaz/hydjetTuneDrum_QuenchedMB_53X_GEN-SIM_v2/Hydjet_Drum_53X_RECO_test16/16a66057d6b9b6b77f83d561b8cd7aea/step3_RAW2DIGI_L1Reco_RECO_VALIDATION_DQM_85_1_Atc.root',
      '/store/user/yilmaz/hydjetTuneDrum_QuenchedMB_53X_GEN-SIM_v2/Hydjet_Drum_53X_RECO_test16/16a66057d6b9b6b77f83d561b8cd7aea/step3_RAW2DIGI_L1Reco_RECO_VALIDATION_DQM_86_1_5Hy.root',
      '/store/user/yilmaz/hydjetTuneDrum_QuenchedMB_53X_GEN-SIM_v2/Hydjet_Drum_53X_RECO_test16/16a66057d6b9b6b77f83d561b8cd7aea/step3_RAW2DIGI_L1Reco_RECO_VALIDATION_DQM_87_1_v07.root',
      '/store/user/yilmaz/hydjetTuneDrum_QuenchedMB_53X_GEN-SIM_v2/Hydjet_Drum_53X_RECO_test16/16a66057d6b9b6b77f83d561b8cd7aea/step3_RAW2DIGI_L1Reco_RECO_VALIDATION_DQM_88_1_uJe.root',
      '/store/user/yilmaz/hydjetTuneDrum_QuenchedMB_53X_GEN-SIM_v2/Hydjet_Drum_53X_RECO_test16/16a66057d6b9b6b77f83d561b8cd7aea/step3_RAW2DIGI_L1Reco_RECO_VALIDATION_DQM_89_1_IzC.root',
      '/store/user/yilmaz/hydjetTuneDrum_QuenchedMB_53X_GEN-SIM_v2/Hydjet_Drum_53X_RECO_test16/16a66057d6b9b6b77f83d561b8cd7aea/step3_RAW2DIGI_L1Reco_RECO_VALIDATION_DQM_90_1_njx.root',
      '/store/user/yilmaz/hydjetTuneDrum_QuenchedMB_53X_GEN-SIM_v2/Hydjet_Drum_53X_RECO_test16/16a66057d6b9b6b77f83d561b8cd7aea/step3_RAW2DIGI_L1Reco_RECO_VALIDATION_DQM_91_2_5dE.root',
      '/store/user/yilmaz/hydjetTuneDrum_QuenchedMB_53X_GEN-SIM_v2/Hydjet_Drum_53X_RECO_test16/16a66057d6b9b6b77f83d561b8cd7aea/step3_RAW2DIGI_L1Reco_RECO_VALIDATION_DQM_9_1_pQl.root',
      '/store/user/yilmaz/hydjetTuneDrum_QuenchedMB_53X_GEN-SIM_v2/Hydjet_Drum_53X_RECO_test16/16a66057d6b9b6b77f83d561b8cd7aea/step3_RAW2DIGI_L1Reco_RECO_VALIDATION_DQM_92_1_jtS.root',
      '/store/user/yilmaz/hydjetTuneDrum_QuenchedMB_53X_GEN-SIM_v2/Hydjet_Drum_53X_RECO_test16/16a66057d6b9b6b77f83d561b8cd7aea/step3_RAW2DIGI_L1Reco_RECO_VALIDATION_DQM_93_1_PUO.root',
      '/store/user/yilmaz/hydjetTuneDrum_QuenchedMB_53X_GEN-SIM_v2/Hydjet_Drum_53X_RECO_test16/16a66057d6b9b6b77f83d561b8cd7aea/step3_RAW2DIGI_L1Reco_RECO_VALIDATION_DQM_94_1_S4X.root',
      '/store/user/yilmaz/hydjetTuneDrum_QuenchedMB_53X_GEN-SIM_v2/Hydjet_Drum_53X_RECO_test16/16a66057d6b9b6b77f83d561b8cd7aea/step3_RAW2DIGI_L1Reco_RECO_VALIDATION_DQM_95_1_v9t.root',
      '/store/user/yilmaz/hydjetTuneDrum_QuenchedMB_53X_GEN-SIM_v2/Hydjet_Drum_53X_RECO_test16/16a66057d6b9b6b77f83d561b8cd7aea/step3_RAW2DIGI_L1Reco_RECO_VALIDATION_DQM_96_1_JCv.root',
      '/store/user/yilmaz/hydjetTuneDrum_QuenchedMB_53X_GEN-SIM_v2/Hydjet_Drum_53X_RECO_test16/16a66057d6b9b6b77f83d561b8cd7aea/step3_RAW2DIGI_L1Reco_RECO_VALIDATION_DQM_97_1_TZO.root',
      '/store/user/yilmaz/hydjetTuneDrum_QuenchedMB_53X_GEN-SIM_v2/Hydjet_Drum_53X_RECO_test16/16a66057d6b9b6b77f83d561b8cd7aea/step3_RAW2DIGI_L1Reco_RECO_VALIDATION_DQM_98_1_pnA.root',
      '/store/user/yilmaz/hydjetTuneDrum_QuenchedMB_53X_GEN-SIM_v2/Hydjet_Drum_53X_RECO_test16/16a66057d6b9b6b77f83d561b8cd7aea/step3_RAW2DIGI_L1Reco_RECO_VALIDATION_DQM_99_1_07m.root'

    )

)

process.fileSaver = cms.EDAnalyzer("JetFileSaver",
                        OutputFile = cms.untracked.string('histo.root')
)



# IC5 Calo jets
process.JetAnalyzerICPU5Calo = cms.EDAnalyzer("CaloJetTesterUnCorr",
    src = cms.InputTag("iterativeConePu5CaloJets"),
    srcGen = cms.InputTag("iterativeCone5HiCleanedGenJets"),
    srcRho = cms.InputTag("iterativeConePu5CaloJets","rho"),
    genEnergyFractionThreshold = cms.double(0.05),
    genPtThreshold = cms.double(1.0),
    RThreshold = cms.double(0.3),
    reverseEnergyFractionThreshold = cms.double(0.5)
)

#process.JetAnalyzerICPU7Calo = cms.EDAnalyzer("CaloJetTesterUnCorr",
 #   src = cms.InputTag("iterativeConePu7CaloJets"),
  #  srcGen = cms.InputTag("iterativeCone7HiCleanedGenJets"),
   # srcRho = cms.InputTag("iterativeConePu7CaloJets","rho"),
   # genEnergyFractionThreshold = cms.double(0.05),
    #genPtThreshold = cms.double(1.0),
    #RThreshold = cms.double(0.3),
    #reverseEnergyFractionThreshold = cms.double(0.5)
#)

process.JetAnalyzerAkPU3Calo = cms.EDAnalyzer("CaloJetTesterUnCorr",
    src = cms.InputTag("akPu3CaloJets"),
    srcGen = cms.InputTag("ak3HiCleanedGenJets"),
    srcRho = cms.InputTag("akPu3CaloJets","rho"),
    genEnergyFractionThreshold = cms.double(0.05),
    genPtThreshold = cms.double(1.0),
    RThreshold = cms.double(0.3),
    reverseEnergyFractionThreshold = cms.double(0.5)
)

#process.JetAnalyzerAkPU5Calo = cms.EDAnalyzer("CaloJetTesterUnCorr",
   # src = cms.InputTag("akPu5CaloJets"),
    #srcGen = cms.InputTag("ak5HiCleanedGenJets"),
    #srcRho = cms.InputTag("akPu5CaloJets","rho"),
    #genEnergyFractionThreshold = cms.double(0.05),
   # genPtThreshold = cms.double(1.0),
  #  RThreshold = cms.double(0.3),
 #   reverseEnergyFractionThreshold = cms.double(0.5)
#)

process.JetAnalyzerAkPU3PF = cms.EDAnalyzer("PFJetTesterUnCorr",
    src = cms.InputTag("akPu3PFJets"),
    srcGen = cms.InputTag("ak3HiCleanedGenJets"),
    srcRho = cms.InputTag("akPu3PFJets","rho"),
    genEnergyFractionThreshold = cms.double(0.05),
    genPtThreshold = cms.double(1.0),
    RThreshold = cms.double(0.3),
    reverseEnergyFractionThreshold = cms.double(0.5)
)


process.JetAnalyzerAkPU5PF = cms.EDAnalyzer("PFJetTesterUnCorr",
    src = cms.InputTag("akPu5PFJets"),
    srcGen = cms.InputTag("ak5HiCleanedGenJets"),
    srcRho = cms.InputTag("akPu5PFJets","rho"),
    genEnergyFractionThreshold = cms.double(0.05),
    genPtThreshold = cms.double(1.0),
    RThreshold = cms.double(0.3),
    reverseEnergyFractionThreshold = cms.double(0.5)
)


process.JetAnalyzerAkVs3Calo = cms.EDAnalyzer("CaloJetTesterUnCorr",
    src = cms.InputTag("akVs3CaloJets"),
    srcGen = cms.InputTag("ak3HiCleanedGenJets"),
    srcRho = cms.InputTag("akVs3CaloJets","rho"),
    genEnergyFractionThreshold = cms.double(0.05),
    genPtThreshold = cms.double(1.0),
    RThreshold = cms.double(0.3),
    reverseEnergyFractionThreshold = cms.double(0.5)
)

process.DQMoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    outputCommands = process.DQMEventContent.outputCommands,
    fileName = cms.untracked.string('step3_RAW2DIGI_L1Reco_RECO_VALIDATION_DQM_inDQM.root'),
    dataset = cms.untracked.PSet(
      filterName = cms.untracked.string(''),
      dataTier = cms.untracked.string('DQM')
      )
)


process.p1 = cms.Path(process.fileSaver
#                       *process.JetAnalyzerICPU5Calo
                      # *process.JetAnalyzerICPU7Calo
#		       *process.JetAnalyzerAkPU3Calo
		     #  *process.JetAnalyzerAkPU5Calo
 #                      *process.JetAnalyzerAkPU3PF
#		       *process.JetAnalyzerAkPU5PF
 #                      *process.JetAnalyzerAkVs3Calo
#                     *process.JetAnalyzerIC5Calo
	             # *process.kt6PFJets 
                     # * process.ak5PFJets 
                      #--- Non-Standard sequence (that involve Producers)
                      #*process.ak5CaloJetsL2L3
 #                     *process.ZSPJetCorrectionsIcone5
 #                     *process.ZSPJetCorrectionsAntiKt5
 #                     *process.JetPlusTrackCorrectionsIcone5
 #                     *process.JetPlusTrackCorrectionsAntiKt5
#                      *process.JetAnalyzerAK5Cor
#                      *process.JetAnalyzerIC5JPT
#                      *process.JetAnalyzerAk5JPT
                      #--- Standard sequence
                      *process.hiJetValidation
                      *process.DQMoutput
                      #--- DQM stats module
#                      *process.dqmStoreStats
)
process.DQM.collectorHost = ''

