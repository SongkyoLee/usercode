#!/bin/bash
eval `scramv1 runtime -sh`

#prefixarr=(default_bit1 default_bit1_mu4GeV)
prefixarr=(mu4GeV_bit1 singleMuEtaAll_bit1 singleMuEtaAllMu4GeV_bit1 singleMuEtaBarrel_bit1 default_bit1)
#raparr=(-2.4-1.46 -2.4--0.47 -0.47-1.46 -2.4--2.014 -2.014--1.628 -1.628--1.242 -1.242--0.856 -0.856--0.47 -0.47--0.084 -0.084-0.302 0.302-0.688 0.688-1.074 1.074-1.46 1.46-1.93 1.93-2.4 1.46-2.4 -1.47-1.46 -1.47-0.53 -2.4--1.757 -1.757--1.113 -1.113--0.47 -0.47-0.173 0.173-0.817 0.817-1.46)

# pPb
#raparr=(-2.4-1.46 -2.4--0.47 -0.47-1.46 -1.47-1.46 -1.47-0.53 -2.4--1.757 -1.757--1.113 -1.113--0.47 -0.47-0.173 0.173-0.817 0.817-1.46 1.46-2.4)

# Pbp
#raparr=(-1.46--0.817 -0.817--0.173 -0.173-0.47 0.47-1.113 1.113-1.757 1.757-2.4 -1.46-1.47 -0.53-1.47 -2.4--1.46)
#raparr=(-1.46-2.4 0.47-2.4 -1.46-0.47 -1.46--0.817 -0.817--0.173 -0.173-0.47 0.47-1.113 1.113-1.757 1.757-2.4 -2.4--1.46 -2.4--1.93 -1.93--1.46 -1.46--1.47 -0.53-1.47)
raparr=(-2.4--1.47 -1.47--0.47 -0.47-0.53 0.53-1.47 1.47-2.4 -2.4--0.47 -0.47-1.47 -1.47-0.53)

outputf=outCTauErr_Pbp
#outputf=outCTauErr_pPb

#raparr=$(ls | grep ".*tgz" | awk 'BEGIN{FS="_"}; {print $NF}' | awk 'BEGIN{FS=".tgz"}; {print $1}')
#echo $raparr

if [ ! -d $outputf ]; then
	mkdir $outputf
fi

cd $outputf
for prefix in ${prefixarr[@]}; do
  rm -f "ctauErrRange_"$prefix".txt"
  for rap in ${raparr[@]}; do
		mv ../$prefix\_$rap.sh .
		mv ../$prefix\_$rap.tgz .
    tar zxf $prefix\_$rap.tgz
  done
  for rap in ${raparr[@]}; do
    cat "ctauErrRange_"$prefix\_$rap".txt" >> "ctauErrRange_"$prefix".txt"
  done
done

rm -f *out
