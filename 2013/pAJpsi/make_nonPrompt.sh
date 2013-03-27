#!/bin/bash
eval `scramv1 runtime -sh`

#input=/afs/cern.ch/work/m/miheejo/private/TREE/pA/NPMC_Histos.root
#input=/afs/cern.ch/user/k/kyolee/private/cms538HI/src/HiAnalysis/HiOnia/test/outTTree_MC_np/hioniaanalyzer_MC_np_merged.root
input=/afs/cern.ch/user/k/kyolee/private/cms538HI/src/HiAnalysis/HiOnia/test/outTTree_MC_np/NPMC_Histos.root

# KYO
outputf=outRooData_MC

prefixarr=(nonPrompt_mu4GeV_bit1 nonPrompt_singleMuEtaAll_bit1 nonPrompt_singleMuEtaAllMu4GeV_bit1 nonPrompt_singleMuEtaBarrel_bit1 nonPrompt_default_bit1)

if [ ! -d $outputf ]; then # KYO
	mkdir $outputf
fi

for prefix in ${prefixarr[@]}; do
  if [ ! -d $outputf/Pbp -o ! -d $outputf/pPb ]; then
    mkdir $outputf/Pbp $outputf/pPb
  fi
#  if [ ! -d $prefix ]; then
  if [ ! -d $outputf/Pbp/$prefix -o ! -d $outputf/pPf/$prefix ]; then
    mkdir $outputf/Pbp/$prefix $outputf/pPb/$prefix
  else
    echo " "
    echo "===== Target directory exists! Check is it okay to delete or not.";
    exit
  fi
done

for prefix in ${prefixarr[@]}; do
  if [ "$prefix" == "${prefixarr[0]}" ]; then
    ./Tree2DatasetspPb =t 40100 =or 7 =f $input $outputf/pPb/$prefix >& $outputf/pPb/$prefix/log_cent40100 &
    ./Tree2DatasetsPbp =t 40100 =or 7 =f $input $outputf/Pbp/$prefix >& $outputf/Pbp/$prefix/log_cent40100 &
  elif [ "$prefix" == "${prefixarr[1]}" ]; then
    ./Tree2DatasetspPb =t 40100 =or 10 =f $input $outputf/pPb/$prefix >& $outputf/pPb/$prefix/log_cent40100 &
    ./Tree2DatasetsPbp =t 40100 =or 8 =f $input $outputf/Pbp/$prefix >& $outputf/Pbp/$prefix/log_cent40100 &
  elif [ "$prefix" == "${prefixarr[2]}" ]; then
    ./Tree2DatasetspPb =t 40100 =or 710 =f $input $outputf/pPb/$prefix >& $outputf/pPb/$prefix/log_cent40100 &
    ./Tree2DatasetsPbp =t 40100 =or 78 =f $input $outputf/Pbp/$prefix >& $outputf/Pbp/$prefix/log_cent40100 &
  elif [ "$prefix" == "${prefixarr[3]}" ]; then
    ./Tree2DatasetspPb =t 40100 =or 11 =f $input $outputf/pPb/$prefix >& $outputf/pPb/$prefix/log_cent40100 &
    ./Tree2DatasetsPbp =t 40100 =or 9 =f $input $outputf/Pbp/$prefix >& $outputf/Pbp/$prefix/log_cent40100 &
  elif [ "$prefix" == "${prefixarr[4]}" ]; then
    ./Tree2DatasetspPb =t 40100 =or 0 =f $input $outputf/pPb/$prefix >& $outputf/pPb/$prefix/log_cent40100 &
    ./Tree2DatasetsPbp =t 40100 =or 0 =f $input $outputf/Pbp/$prefix >& $outputf/Pbp/$prefix/log_cent40100 &
  fi

done
