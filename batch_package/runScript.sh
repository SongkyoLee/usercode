#!/bin/bash
pyname=skel

skel 

###nFile=300
ninit=70
skelpyname=runAnalysis_emu_skel
workpyname=batch_runAnalysisTT_emu_
batchskelname=bth_skel
batchname=batch_TT_emu_
outDir=Results
outputname=out_tree_TT_emu_

if [ ! -d "$(pwd)/$outDir" ]; then
	mkdir $(pwd)/$outDir
fi

### make inputfile list
#ls /cmsdas/scratch/jlee/SingleMuon/Run2015B-PromptReco-v1/MINIAOD/*.root >> inputlist.txt
#ls /cmsdas/scratch/jlee/MuonEG/Run2015B-PromptReco-v1/MINIAOD/*.root >> inputlist.txt
ls /cmsdas/scratch/jlee/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/MINIAODSIM/*.root >> inputlist.txt
#awk -v p=file:step3 '{gsub("step3",p); print;}' inputlist_raw.txt > inputlist.txt

### read in line by line to array
let nFile=0
while read line 
do 
	((nFile++))
	echo -e "$line"  
	array+=("$line")
done < inputlist.txt
###tmp
###let nFile=2
echo "*** Number of lines: $nFile"

### check the array (NB: starting from zero)
echo "*** Check the array"
for ((i=0; i < ${#array[*]}; i++))
do
	echo "${array[i]}"
done

### main
echo "*** Make $nFile python files and run!"
for (( i=$ninit; i<=$nFile; i++)) do
echo "------ "$i"th process ------"
### create python
awk -v p=${array[i-1]} -v p1=$outputname$i.root '{gsub("_inputfile_",p); gsub("_outputfile_",p1); print;}' $skelpyname.py > $workpyname$i.py;
### create batch.sh
awk -v p=$(pwd) -v p1=$workpyname$i.py -v p2=$outputname$i.root '{gsub("_indir_",p); gsub("_inputpy_",p1); gsub("_outputfile_",p2); print;}'  $batchskelname.sh> $batchname$i.sh;
chmod 777 $batchname$i.sh
### 1)) run batch
#bsub -R "pool>10000" -q 1nd -J $batchname$i < $batchname$i.sh
### 2)) locally ShllScript
#./$batchname$i.sh
### 4)) locally cmsRun without batch
#cmsRun $workpyname$i.py
#mv $outputname$i.root ./$outDir/$outputname$i.root
done
echo "*** Done!!"


