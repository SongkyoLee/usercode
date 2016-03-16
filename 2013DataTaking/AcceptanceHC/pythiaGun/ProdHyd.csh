#!/bin/sh -f
#############################################
#### bash shell script to make batch job ####
#### by Dongho Moon                      ####
#############################################
#### modified  by Hyunchul Kim           ####
#############################################

#### Set up the paramters

echo Now processing !!!!
echo $nFile

curdir=$(pwd)


# for BtoJ/Psi sample
#nFile=100 ## total number of files
nFile=10 ## total number of files
skelpyname=generator_skel_pythiagun_GENRECO_ppreco_20121218
outputdir=/afs/cern.ch/user/k/kyolee/private/cms538HI/src/UserCode/03_UpsilonAcceptance/01_pythiaGun/outPutData ### output directory, don't end with "/"
outname=test_ ## end with _
workpy=test_ ## end with _
job=test_ ## end with _
#outname=pythia6_BtoJpsitoMuMu_GEN_2.76TeV_bfiltered_evt10k_ ## end with _
#workpy=pythia6_BtoJpsitoMuMu_GEN_2.76TeV_bfiltered_evt10k_ ## end with _
#job=pythia6_BtoJpsitoMuMu_GEN_2.76TeV_bfiltered_evt10k_ ## end with _

# for prompt J/Psi sample
#nFile=1000 ## total number of files
#skelpyname = generator_skel_promptjpsi
#outputdir=/castor/cern.ch/user/h/hckim/cms392/pythia6_PromptJpsitoMuMu_GEN_2.76TeV_totevt10M ### output directory, don't end with "/"
#outname=pythia6_PromptJpsitoMuMu_GEN_2.76TeV_evt10k_ ## end with _
#workpy=pythia6_PromptJpsitoMuMu_GEN_2.76TeV_evt10k_ ## end with _
#job=pythia6_PromptJpsitoMuMu_GEN_2.76TeV_evt10k_ ## end with _

echo Making cfg and csh file

#### Making the input bunchs ####

i=1

while [ $i -le $nFile ]
do 
	awk -v p=$outname$i.root -v p1=$i '{gsub("_output_file_",p); gsub("_N_",p1); print;}' $skelpyname.py > $workpy$i.py;
	awk -v p=$(pwd) -v p2=$workpy$i.py -v p3=$outname$i.root -v p4=$outputdir '{gsub("_in_dir_",p); gsub("_input_py_",p2); gsub("_output_file_",p3); gsub("_out_dir_",p4); print;}' mjob_test.csh > $job$i.csh
	i=$(expr $i + 1);
done

#### Submitting ####

i=1

while [ $i -le $nFile ]
do
	echo Job submitting $i
	bsub -R "pool>10000" -q 1nd -J $job$i < $job$i.csh
	i=$(expr $i + 1);
done

