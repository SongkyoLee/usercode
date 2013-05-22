#!/bin/bash
eval `scramv1 runtime -sh`

#inputf=root://eoscms//eos/cms
#inputf=$inputf/store/group/phys_heavyions/dileptons/Data2013/pPb/Prompt/TTrees/Jpsi_Histos_Runs_210498-210837.root

#KYO : input data selection
# for Pbp
#inputf=/afs/cern.ch/user/k/kyolee/private/cms538HI/src/HiAnalysis/HiOnia/test/outTTree/Jpsi_Histos_Runs_210498-211256.root
# for pPb
#inputf=/afs/cern.ch/user/k/kyolee/private/cms538HI/src/HiAnalysis/HiOnia/test/outTTree/Jpsi_Histos_Runs_211313-211631.root
# for pp
inputf=/afs/cern.ch/user/k/kyolee/private/cms538HI/src/HiAnalysis/HiOnia/test/outTTree/Jpsi_v2.18_Histos_Runs_211739-211831.root

#KYO : output directory selection
# for Pbp
#outputf=outRooData_Pbp
# for pPb
#outputf=outRooData_pPb
# for pp
outputf=outRooData_pp

prefixarr=(mu4GeV_bit1 singleMuEtaAll_bit1 singleMuEtaAllMu4GeV_bit1 singleMuEtaBarrel_bit1 default_bit1)
#prefixarr=(default_bit1)

#KYO : Centrality Array 
# for Pbp or pPb
#labelarr=(305070 50 60 70 80 805 901235)
# for pp
labelarr=(1)

if [ ! -d $outputf ]; then #KYO
	mkdir $outputf
fi

for prefix in ${prefixarr[@]}; do
  if [ ! -d $outputf/$prefix ]; then
    mkdir $outputf/$prefix
    for label in ${labelarr[@]}; do
      mkdir $outputf/$prefix/cent$label
    done
  else
    echo " "
    echo "===== Target directory exists! Check is it okay to delete or not.";
    exit
  fi

#KYO : runType selection - you should change the number by yourself!
#for Pbp : 7, 8, 78, 9, 0
#for pPb : 7, 10, 710, 11, 0
#for pp : 7, 12, 712, 13, 0

  if [ "$prefix" == "${prefixarr[0]}" ]; then
    echo "runType == 7"
    for label in ${labelarr[@]}; do
      ./Tree2Datasets =t $label =or 7 =oc 0 =f $inputf $outputf/$prefix/cent$label >& $outputf/$prefix/log_cent$label &
    done
  elif [ "$prefix" == "${prefixarr[1]}" ]; then
    echo "runType == 12"
    for label in ${labelarr[@]}; do
      ./Tree2Datasets =t $label =or 12 =oc 0 =f $inputf $outputf/$prefix/cent$label >& $outputf/$prefix/log_cent$label &
    done
  elif [ "$prefix" == "${prefixarr[2]}" ]; then
    echo "runType == 712"
    for label in ${labelarr[@]}; do
      ./Tree2Datasets =t $label =or 712 =oc 0 =f $inputf $outputf/$prefix/cent$label >& $outputf/$prefix/log_cent$label &
    done
  elif [ "$prefix" == "${prefixarr[3]}" ]; then
    echo "runType == 13"
    for label in ${labelarr[@]}; do
      ./Tree2Datasets =t $label =or 13 =oc 0 =f $inputf $outputf/$prefix/cent$label >& $outputf/$prefix/log_cent$label &
    done
  elif [ "$prefix" == "${prefixarr[4]}" ]; then
    echo "runType == 0"
    for label in ${labelarr[@]}; do
      ./Tree2Datasets =t $label =or 0 =oc 0 =f $inputf $outputf/$prefix/cent$label >& $outputf/$prefix/log_cent$label &
    done
  fi

done

