#!/bin/bash
eval `scramv1 runtime -sh`

#prefixarr=(default_bit1_singleMuEtaAll default_bit1_singleMuEtaAllMu4GeV default_bit1_mu4GeV default_bit1_singleMuEtaBarrel)
prefixarr=(default_bit1 mu4GeV_bit1 singleMuEtaAllMu4GeV_bit1 singleMuEtaAll_bit1 singleMuEtaBarrel_bit1)
labelarr=(305070 50 60 70 80 805 901235)
#outputf=outRooData_Pbp
outputf=outRooData_pPb

for prefix in ${prefixarr[@]}; do
  for label in ${labelarr[@]}; do
    mv $outputf/$prefix/cent$label/* $outputf/$prefix/
    rmdir $outputf/$prefix/cent$label 
  done
done

