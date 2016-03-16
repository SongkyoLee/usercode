#!/bin/bash

ninit=1
nFile=100
skelpyname=runAnalysis_emu_skel
workpyname=batch_runAnalysisTT_emu_
batchskelname=bth_skel
batchname=batch_TT_emu_
outDir=Results
outputname=out_tree_TT_emu_

for (( i=$ninit; i<=$nFile; i++)) do
echo "------ "$i"th process ------"
### 1)) run batch
#bsub -R "pool>10000" -q 1nd -J $batchname$i < $batchname$i.sh
### 2)) locally ShllScript
#./$batchname$i.sh
### 4)) locally cmsRun without batch
cmsRun $workpyname$i.py
mv $outputname$i.root ./$outDir/$outputname$i.root
done
echo "*** Done!!"


