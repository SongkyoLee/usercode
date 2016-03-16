#!/bin/bash

eval `scram runtime -sh`

cvs co -r V08-00-02 MuonAnalysis/TagAndProbe
cvs co -r V01-06-05 RecoVertex/PrimaryVertexProducer
cvs co -r pPbProd_v04 DataFormats/HeavyIonEvent
cvs co -r pPbProd_v05 HeavyIonsAnalysis/Configuration
cvs co -r pPbProd_v05 RecoHI/HiCentralityAlgos
cvs co -r branch_pA -d HiSkim/HiOnia2MuMu UserCode/tdahms/HiSkim/HiOnia2MuMu
cvs co -r branch_pA -d HiAnalysis/HiOnia UserCode/tdahms/HiAnalysis/HiOnia

scram b
