#!/bin/bash
eval `scramv1 runtime -sh`

#prefixarr=(default_bit1 default_cowboy default_sailor)
#prefixarr=(default_bit1_mu4GeV)

#datasetarr=(datasets)
# for Pbp
#datasetarr=(/afs/cern.ch/user/k/kyolee/private/cms442/src/pAJpsi/outRooData_Pbp/)
# for pPb
#datasetarr=(/afs/cern.ch/user/k/kyolee/private/cms442/src/pAJpsi/outRooData_pPb/)
# for pp
datasetarr=(/afs/cern.ch/user/k/kyolee/private/cms442/src/pAJpsi/outRooData_pp/)

prefixarr=(mu4GeV_bit1 singleMuEtaAll_bit1 singleMuEtaAllMu4GeV_bit1 singleMuEtaBarrel_bit1 default_bit1)

#raparr=(-2.4-1.46 -2.4--0.47 -0.47-1.46 -2.4--1.757 -1.757--1.113 -1.113--0.47 -0.47-0.173 0.173-0.817 0.817-1.46 1.46-1.93 1.93-2.4 1.46-2.4 -1.47-1.46 -1.47-0.53)
# for Pbp (18.38/nb)
#raparr=(-2.4--1.47 -1.47--0.47 -0.47-0.53 0.53-1.47 1.47-2.4 -2.4--0.47 -0.47-1.47 -1.47-0.53)
# for pPb (12.55/nb)
#raparr=(-2.4--1.47 -1.47--0.53 -0.53-0.47 0.47-1.47 1.47-2.4 -1.47-0.47 0.47-2.4 -0.53-1.47)
# for pp 
raparr=(-1.93--1.00 -1.00-0.00 0.00-1.00 1.00-1.93 -1.93-0.00 0.00-1.93 -1.00-1.00 -1.93-1.93)


for dataset in ${datasetarr[@]}; do
  for prefix in ${prefixarr[@]}; do
    for rap in ${raparr[@]}; do
# for Pbp or pPb
#      awk -v p=$(pwd) -v p2=CTauErr -v p3=$prefix -v p4=$dataset -v p5=$rap -v p6=$prefix\_$rap.tgz '{gsub("_pwd_",p); gsub("_input_py_",p2); gsub("_prefix_",p3); gsub("_input_file_",p4); gsub("_rap_",p5); gsub("_prefixtar_",p6);  print;}' runCtauErrJob.sh > $prefix\_$rap.sh;
# for pp
      awk -v p=$(pwd) -v p2=CTauErrpp -v p3=$prefix -v p4=$dataset -v p5=$rap -v p6=$prefix\_$rap.tgz '{gsub("_pwd_",p); gsub("_input_py_",p2); gsub("_prefix_",p3); gsub("_input_file_",p4); gsub("_rap_",p5); gsub("_prefixtar_",p6);  print;}' runCtauErrJob.sh > $prefix\_$rap.sh;
#      awk -v p=$(pwd) -v p2=CTauErrdPhi -v p3=$prefix -v p4=$dataset -v p5=$rap -v p6=$prefix\_$rap.tgz '{gsub("_pwd_",p); gsub("_input_py_",p2); gsub("_prefix_",p3); gsub("_input_file_",p4); gsub("_rap_",p5); gsub("_prefixtar_",p6);  print;}' runCtauErrJob.sh > $prefix\_$rap.sh;
      echo $prefix\_$rap.sh 
      chmod +x $prefix\_$rap.sh 
      bsub -R "pool>10000" -u songkyo.lee@cern.c -q 1nd -J $prefix\_$rap.sh < $prefix\_$rap.sh
    done
  done
done

