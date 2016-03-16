# Auto generated configuration file
# using: 
# Revision: 1.232.2.6 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: Configuration/GenProduction/python/SingleJPsimumu_FlatPt0to20_cfi.py --scenario HeavyIons -s GEN:ProductionFilterSequence,SIM,DIGI,L1,DIGI2RAW,RAW2DIGI,RECO --conditions=FrontierCodnitions_GlobalTag,MC_311_V1::All --datatier GEN-SIM-RAW-RECO --eventcontent=FEVTDEBUG --processName SIGNAL -n 3000 --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('SIGNAL')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
##process.load('Configuration.StandardSequences.MixingNoPileUp_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
##process.load('Configuration.StandardSequences.VtxSmearedRealistic7TeVCollision_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic7TeV2011Collision_cfi')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
## for PbPb reconstrunction
##process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
##process.load('Configuration.EventContent.EventContentHeavyIons_cff')
## for pp reconstrunction
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.EventContent.EventContent_cff')

process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')

process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.2 $'),
    annotation = cms.untracked.string('Pythia Gun J/Psi -> mu mu'),
    name = cms.untracked.string('$Source: /afs/cern.ch/project/cvs/reps/CMSSW/UserCode/HCKim/HIOniaAccStudy/Generation/Attic/pythiagun_Jpsitomumu_GEN_SIM_DIGI_RECO_2.76TeV_evt1000_999.py,v $')
)
process.maxEvents = cms.untracked.PSet(
    #input = cms.untracked.int32(3000)
    #input = cms.untracked.int32(100)
    #output = cms.untracked.int32(10000)
    output = cms.untracked.int32(100) #output KYO
)

# Input source
process.source = cms.Source("EmptySource")
process.RandomNumberGeneratorService.generator.initialSeed = _N_ 
process.RandomNumberGeneratorService.VtxSmeared.initialSeed = _N_ 
process.RandomNumberGeneratorService.g4SimHits.initialSeed = _N_ 
process.RandomNumberGeneratorService.mix.initialSeed = _N_ 
process.RandomNumberGeneratorService.mixData.initialSeed = _N_ 
process.RandomNumberGeneratorService.simSiStripDigis.initialSeed = _N_ 
process.RandomNumberGeneratorService.simEcalUnsuppressedDigis.initialSeed = _N_ 
process.RandomNumberGeneratorService.simHcalUnsuppressedDigis.initialSeed = _N_ 
process.RandomNumberGeneratorService.simMuonDTDigis.initialSeed = _N_ 
process.RandomNumberGeneratorService.simMuonCSCDigis.initialSeed = _N_ 
process.RandomNumberGeneratorService.simMuonRPCDigis.initialSeed = _N_ 
process.RandomNumberGeneratorService.simCastorDigis.initialSeed = _N_ 
process.options = cms.untracked.PSet(

)

# Output definition

process.FEVTDEBUGoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    outputCommands = process.FEVTDEBUGEventContent.outputCommands,
    ##outputCommands = process.reRecoMuonAOD.outputCommands,

    fileName = cms.untracked.string(
        ##'pythiagun_Jpsitomumu_GEN_SIM_DIGI_RECO_2.76TeV_evt3k_999_20121204.root'
        ##'pythiagun_Jpsitomumu_GEN_SIM_DIGI_RECO_2.76TeV_evt100_999_20121206_camelia.root'
        #'SingleJPsimumu_FlatPt0to20_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO.root'
        '_output_file_'
#	'test_evt10k.root'
	),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('GEN-SIM-RAW-RECO')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    )
)
##process.FEVTDEBUGoutput.outputCommands.extend(process.reRecoMuonAOD.outputCommands)

# Additional output definition

# Other statements
#process.GlobalTag.globaltag = 'FrontierCodnitions_GlobalTag'
#process.GlobalTag.connect   = 'MC_311_V1::All'
#process.GlobalTag.connect   = 'START39_V4HI::All'
process.GlobalTag.globaltag = 'STARTHI53_V17::All'
process.generator = cms.EDProducer("Pythia6PtYDistGun",
    PGunParameters = cms.PSet(
        MaxY = cms.double(2.5),
        MinPt = cms.double(0.0),
        ParticleID = cms.vint32(443),
        MaxPhi = cms.double(3.14159265359),
        MaxPt = cms.double(20.0),
        MinY = cms.double(-2.5),
        YBinning = cms.int32(500),
        kinematicsFile = cms.FileInPath('GeneratorInterface/HiGenCommon/data/flatYPt.root'),
        MinPhi = cms.double(-3.14159265359),
        PtBinning = cms.int32(100000)
    ),
    PythiaParameters = cms.PSet(
        pythiaUESettings = cms.vstring('MSTJ(11)=3     ! Choice of the fragmentation function', 
            'MSTJ(22)=2     ! Decay those unstable particles', 
            'PARJ(71)=10 .  ! for which ctau  10 mm', 
            'MSTP(2)=1      ! which order running alphaS', 
            'MSTP(33)=0     ! no K factors in hard cross sections', 
            'MSTP(51)=10042 ! structure function chosen (external PDF CTEQ6L1)', 
            'MSTP(52)=2     ! work with LHAPDF', 
            'MSTP(81)=1     ! multiple parton interactions 1 is Pythia default', 
            'MSTP(82)=4     ! Defines the multi-parton model', 
            'MSTU(21)=1     ! Check on possible errors during program execution', 
            'PARP(82)=1.8387   ! pt cutoff for multiparton interactions', 
            'PARP(89)=1960. ! sqrts for which PARP82 is set', 
            'PARP(83)=0.5   ! Multiple interactions: matter distrbn parameter', 
            'PARP(84)=0.4   ! Multiple interactions: matter distribution parameter', 
            'PARP(90)=0.16  ! Multiple interactions: rescaling power', 
            'PARP(67)=2.5    ! amount of initial-state radiation', 
            'PARP(85)=1.0  ! gluon prod. mechanism in MI', 
            'PARP(86)=1.0  ! gluon prod. mechanism in MI', 
            'PARP(62)=1.25   ! ', 
            'PARP(64)=0.2    ! ', 
            'MSTP(91)=1      !', 
            'PARP(91)=2.1   ! kt distribution', 
            'PARP(93)=15.0  ! '),
        pythiaJpsiToMuons = cms.vstring('BRAT(858) = 0 ', 
            'BRAT(859) = 1 ', 
            'BRAT(860) = 0 ', 
            'MDME(858,1) = 0 ', 
            'MDME(859,1) = 1 ', 
            'MDME(860,1) = 0 '),
        parameterSets = cms.vstring('pythiaUESettings', 
            'pythiaJpsiToMuons')
    )
)

process.ProductionFilterSequence = cms.Sequence(process.generator)


# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen_hi)

process.simulation_step = cms.Path(process.psim)

process.digitisation_step = cms.Path(process.pdigi)

process.L1simulation_step = cms.Path(process.SimL1Emulator)

process.digi2raw_step = cms.Path(process.DigiToRaw)

process.raw2digi_step = cms.Path(process.RawToDigi)

##process.reconstruction_step = cms.Path(process.reconstructionHeavyIons) ##default
##process.reconstruction_step = cms.Path(process.reconstructionHeavyIons*process.reMuonRecoPbPb) ##for adding regit process
process.reconstruction_step = cms.Path(process.reconstruction) ##for pp reconstruction
##process.reconstruction_step = cms.Path(process.reMuonRecoPbPb)

process.endjob_step = cms.Path(process.endOfProcess)

##process.FEVTDEBUGoutput_step = cms.EndPath(process.FEVTDEBUGoutput)
process.FEVTDEBUGoutput_step = cms.EndPath(process.FEVTDEBUGoutput)



# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.simulation_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step,process.raw2digi_step,process.reconstruction_step,process.endjob_step,process.FEVTDEBUGoutput_step)

# special treatment in case of production filter sequence
for path in process.paths: 
    getattr(process,path)._seq = process.ProductionFilterSequence*getattr(process,path)._seq
