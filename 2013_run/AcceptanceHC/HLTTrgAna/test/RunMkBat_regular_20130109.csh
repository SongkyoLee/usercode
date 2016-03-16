#!/bin/sh -f
#############################################
#### bash shell script to make batch job ####
#### by Dongho Moon                      ####
#############################################
### Modified by Hyunchul Kim 		 ####
#############################################

#### Set up the paramters
bunch=10   # the number of input files

inputdir=$(pwd)
#inputdir=/afs/cern.ch/work/h/hckim/MCsample_forAcc/btojpsipythiagun_cms445patch1_regit_evt20k_20130109
outputdir=$(pwd) ### output directory

##outname=pythiagun_regittest_HLTrgAna_evt20k_regular_
##jobname=pythiagun_regittest_HLTrgAna_evt20k_regular_
##job=pythiagun_regittest_HLTrgAna_evt20k_regular_
##outname=pythiagun_regittest_HLTrgAna_evt20k_regit_
##jobname=pythiagun_regittest_HLTrgAna_evt20k_regit_
##job=pythiagun_regittest_HLTrgAna_evt20k_regit_
jobname=pythiagunpromptUps1S_boosted_GENRECO_ppreco_HLTrgAna_evt5k_20130118_
skelpyname=pythiagunpromptUps1S_boosted_GENRECO_ppreco_HLTrgAna_totevt100k_20130117_skel_cfg

#
######################################################

frontpath='"rfio:$inputdir'

echo Now processing !!!!
#ls -pl pythiagun_GENRECO_regit_evt500_v2_*.root >& list
#cp list_20121221 list2
cp list_regit list2

###awk -v p='"rfio:'$inputdir '{print p$9"\","}' list > tmp.txt
###awk -v p='"file:'$inputdir/ '{print p$9"\","}' list > tmp.txt
##awk -v p='"file:' '{print p$9"\","}' list2 > tmp.txt
awk -v p='"file:'$inputdir/ '{print p$9"\","}' list2 > tmp.txt



file=list2 
curdir=$(pwd)
##rfmkdir $outputdir

echo Making cfg and csh file

#### Making the input bunchs ####

i=1
tmp=""

exec 4<&0
exec 7>&1

exec < tmp.txt
while read line
do
    exec >> conv
    tmp=$tmp$line;
    if [ $i -eq $(wc -l <$file) ]
    then
        echo $tmp;
        
    elif [ $(($i%$bunch)) -eq 0 ]
    then
        echo $tmp;
        tmp="";
    fi
    i=$(expr $i + 1);

done

#### Making the batchs #### 

i=1;
exec < conv

while read convline
do 
    cat $skelpyname.py | sed s/_output_file_/$jobname$i.root/g > test_$i.py
   ##cat HLTrgAna_20121208_pythiagunregit_regit_evt20k_skel_cfg.py | sed s/_output_file_/$jobname$i.root/g > test_$i.py
    awk -v p=$convline '{gsub("_input_",p); print}' test_$i.py > $jobname$i.py;
    awk -v p=$(pwd) -v p2=$jobname$i.py -v p3=$jobname$i.root -v p4=$outputdir '{gsub("_in_dir_",p); gsub("_input_py_",p2); gsub("_output_file_",p3); gsub("_out_dir_",p4); print;}' mjob_test.csh > $jobname$i.csh
    rm test_$i.py
    i=$(expr $i + 1);
done

cp conv conv2

#### Submitting ####

i=1
nc=$(wc -l <conv)

exec 0<&4 
exec 1>&7

while [ $i -le $nc ]
do
    echo Job submitting $i
    bsub -R "pool>10000" -q 1nh -J $jobname$i < $jobname$i.csh
    i=$(expr $i + 1);
done

rm -f tmp.txt conv conv2 list2
##rm -f list
