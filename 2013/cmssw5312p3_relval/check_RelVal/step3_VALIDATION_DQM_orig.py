# Auto generated configuration file
# using: 
# Revision: 1.381.2.28 
# Source: /local/reps/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: step3 --conditions STARTHI53_V28 -s VALIDATION,DQM --scenario HeavyIons --datatier GEN-SIM-RECO,DQM --eventcontent RECOSIM,DQM -n 100 --filein file:/tmp/miheejo/jpsigun_RECO_100_1_DMl.root --fileout file:step3.root
import FWCore.ParameterSet.Config as cms

process = cms.Process('DQM')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.ValidationHeavyIons_cff')
process.load('DQMOffline.Configuration.DQMOfflineHeavyIonsMC_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
#    fileNames = cms.untracked.vstring('file:/tmp/miheejo/jpsigun_RECO_100_1_DMl.root')
    fileNames = cms.untracked.vstring('file:/afs/cern.ch/work/k/kyolee/private/cms5312p3/src/RelVal_test/jpsigun_RECO_100_1_DMl.root')
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.381.2.28 $'),
    annotation = cms.untracked.string('step3 nevts:100'),
    name = cms.untracked.string('PyReleaseValidation')
)

# Output definition

process.RECOSIMoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = process.RECOSIMEventContent.outputCommands,
    fileName = cms.untracked.string('file:step3.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('GEN-SIM-RECO')
    )
)

process.DQMoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    outputCommands = process.DQMEventContent.outputCommands,
    fileName = cms.untracked.string('file:step3_inDQM.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('DQM')
    )
)

# Additional output definition

# Other statements
process.mix.playback = True
#process.RandomNumberGeneratorService.restoreStateLabel=cms.untracked.string("randomEngineStateProducer")
#from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'STARTHI53_V28', '')
process.GlobalTag.globaltag = 'STARTHI53_V28::All'

# Path and EndPath definitions
process.prevalidation_step = cms.Path(process.prevalidation)
process.dqmoffline_step = cms.Path(process.DQMOfflineHeavyIons)
process.validation_step = cms.EndPath(process.validation)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RECOSIMoutput_step = cms.EndPath(process.RECOSIMoutput)
process.DQMoutput_step = cms.EndPath(process.DQMoutput)

from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
massSearchReplaceAnyInputTag(process.prevalidation_step, 'hiSelectedTracks','hiGeneralTracks')
massSearchReplaceAnyInputTag(process.dqmoffline_step, 'hiSelectedTracks','hiGeneralTracks')
massSearchReplaceAnyInputTag(process.validation_step, 'hiSelectedTracks','hiGeneralTracks')
process.dqmoffline_step.remove(process.ecalBarrelOccupancyTask);
process.dqmoffline_step.remove(process.ecalEndcapOccupancyTask);
process.dqmoffline_step.remove(process.hcalNoiseMonitor);

# Schedule definition
#process.schedule = cms.Schedule(process.prevalidation_step,process.validation_step,process.dqmoffline_step,process.endjob_step,process.RECOSIMoutput_step,process.DQMoutput_step)
process.schedule = cms.Schedule(process.dqmoffline_step,process.endjob_step,process.DQMoutput_step)

