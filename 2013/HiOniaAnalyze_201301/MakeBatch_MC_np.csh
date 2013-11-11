#!/bin/sh -f
#############################################
#### bash shell script to make batch job ####
#### by Dongho Moon                      ####
#############################################
#### modified  by Hyunchul Kim           ####
#############################################
#### modified  by Songkyo Lee            ####
#############################################

#### Set up the paramters

echo Now processing !!!!
echo $nFile

curdir=$(pwd)

nFile=9 ## total number of files
pyname=hioniaanalyzer_MC_np_cfg
outputdir=/afs/cern.ch/user/k/kyolee/private/cms538HI/src/HiAnalysis/HiOnia/test/outTTree_MC_np ### output directory, don't end with "/"

inname=root://eoscms//eos/cms/store/group/phys_heavyions/dileptons/MC2013/5TeV/NonPromptJpsi/Skims/onia2MuMuPAT_MC_

outname=hioniaanalyzer_MC_np_ ## end with _
workpy=hioniaanalyzer_MC_np_cfg_bth_ ## end with _
job=job_hioniaanalyzer_MC_np_bth_ ## end with _
#outname=pythia6_BtoJpsitoMuMu_GEN_2.76TeV_bfiltered_evt10k_ ## end with _
#workpy=pythia6_BtoJpsitoMuMu_GEN_2.76TeV_bfiltered_evt10k_ ## end with _
#job=pythia6_BtoJpsitoMuMu_GEN_2.76TeV_bfiltered_evt10k_ ## end with _

echo Making cfg and csh file

#### Making the input bunchs ####

i=0

while [ $i -lt $nFile ]
do 
	awk -v p1=$inname$i.root -v p2=$outname$i.root '{gsub("_input_",p1); gsub("_output_",p2); print;}' $pyname.py > $workpy$i.py;
#	awk -v p1=$inname$i.root -v p2=$outname$i.root -v p3=False '{gsub("_input_",p1); gsub("_output_",p2); gsub("_prnp_",p3); print;}' $pyname.py > $workpy$i.py;
# p3=True for promt & False for nonpromt
	awk -v p1=$(pwd) -v p2=$workpy$i.py -v p3=$outname$i.root -v p4=$outputdir '{gsub("_in_dir_",p1); gsub("_input_py_",p2); gsub("_output_",p3); gsub("_out_dir_",p4); print;}' job.csh > $job$i.csh
	i=$(expr $i + 1);
done

#### Submitting ####

i=0

while [ $i -lt $nFile ]
do
	echo Job submitting $i
	bsub -R "pool>10000" -q 1nd -J $job$i < $job$i.csh
	i=$(expr $i + 1);
done

