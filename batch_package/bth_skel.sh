#!/bin/bash
cd _indir_
#cms environment
export SCRAM_ARCH=slc6_amd64_gcc491
source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scramv1 runtime -sh`
cd -
cmsRun _indir_/_inputpy_
cp _outputfile_ _indir_/Results/
#cp _output_file_ _in_dir_
