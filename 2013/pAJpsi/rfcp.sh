#!/bin/bash -f

########## Directory where the job submittion performed
submitdir="$(pwd)/Scripts/"
########## Castor directory that contains results
indir_="$(pwd)/Results/"
########## Directory where python & root scripts are located
workdir="/afs/cern.ch/user/k/kyolee/private/cms442/src/pAJpsi/"
########## Prefix of jobs
prefixarr=(pPb_singleMuEtaAll_bit1 Pbp_singleMuEtaAll_bit1)

############################################################
eval `scramv1 runtime -csh`

############################################################
########## Copy files from castor and extract it. Run python & root scripts over all files
for prefix in ${prefixarr[@]}; do
  mkdir /tmp/kyolee/$prefix
  cd /tmp/kyolee/$prefix
#  mkdir $indir/$prefix
#  cd $indir/$prefix

  indir=$indir_/$prefix
  echo "indir: "$indir
  list=$(ls $indir | grep tgz)

  for file in $list; do   # Get files from castor using prefix
    if echo $file | grep -q $prefix; then 
      echo $file
      cp $indir/$file .
      tar zxvf ./$file
      rm -f ./$file
#      rm -rf summary
    fi
  done

  # Run python & root script for 1 prefix
  python2.6 $workdir/extract.py $prefix .
#  root -l $workdir/savehisto.cpp

  # Summarize results
  mkdir /tmp/kyolee/$prefix/summary
#  mv fit_cppnumbers fit_parameters fit_table saved_histo.root $indir/$prefix/summary
#  mv fit_* /tmp/kyolee/$prefix/summary
	mv fit_cppnumbers fit_parameters fit_table /tmp/kyolee/$prefix/summary


  ls $submitdir | grep $prefix | awk 'BEGIN{FS=".csh"}; {print $1}' > $submitdir/$prefix\_submit
  ls /tmp/kyolee/$prefix | grep txt | awk 'BEGIN{FS=".txt"}; {print $1}' > $submitdir/$prefix\_txt
  diff $submitdir/$prefix\_submit $submitdir/$prefix\_txt > $submitdir/diff_$prefix

  tar zcvf $indir_/$prefix.tgz /tmp/kyolee/$prefix
done
