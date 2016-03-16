#!/bin/bash
if [ $# -ne 3 ]; then
  echo "Usage: $0 [Executable] [Input root File] [Prefix] "
  exit;
fi

executable=$(pwd)/$1
datasets=$2
prefix=$3

################################################################ 
########## Script parameter setting
################################################################ 
# Storage for batch jobs (should be under /afs)
storage=$(pwd)/Results/$prefix
scripts=$(pwd)/Scripts
if [ ! -d "$(pwd)/Results" ]; then
  mkdir $(pwd)/Results
fi
if [ ! -d "$storage" ]; then
  mkdir $storage
fi
if [ ! -d "$scripts" ]; then
  mkdir $scripts
fi

ctaurange=1.5-3.0
fracfree=0
ispbpb=3 # 0:pp, 1:PbPb, 2:Pbp, 3:pPb
is2Widths=1
isPEE=1
usedPhi=0 # 0: RAA, 1: v2 (this determines whether dphi angles will be presented on the plots or not)

# Non-prompt MC
#mc1=/afs/cern.ch/work/k/kyolee/private/cms442/src/pAJpsi/outRoo_NPMC_pPb_sglMuEtaAll/outRoo_NPMC_pPb_sglMuEtaAll.root
mc1=$(pwd)/outRoo_NPMC_pPb_sglMuEtaAll/outRoo_NPMC_pPb_sglMuEtaAll.root
# Prompt MC
#mc2=/afs/cern.ch/work/k/kyolee/private/cms442/src/pAJpsi/outRoo_PRMC_pPb_sglMuEtaAll/outRoo_PRMC_pPb_sglMuEtaAll.root
mc2=$(pwd)/outRoo_PRMC_pPb_sglMuEtaAll/outRoo_PRMC_pPb_sglMuEtaAll.root

mSigF="sigCB2WNG1" # Mass signal function name (options: sigCB2WNG1 (default), signalCB3WN)
mBkgF="expFunct" # Mass background function name (options: expFunct (default), polFunct)

weight=0  #0: Do NOT weight, 1: Do weight
eventplane="etHFm" # Name of eventplane (etHFp, etHFm, etHF(default))
runOpt=4 # Inclusive mass fit (options: 4(default), 3(Constrained fit), 5(_mb in 2010 analysis))
anaBct=1 #0: do b-fit(not-analytic fit for b-lifetime), 1: do b-fit(analytic fit for b-lifetime), 2: do NOT b-fit
#0: 2 Resolution functions & fit on data, 1: 1 Resolution function & fit on data,
#2: 2 Resolution functions & fit on PRMC, 3: 1 Resolution function & fit on PRMC
resOpt=2
ctauBkg=0 #0: 1 ctau bkg, 1: 2 ctau bkg with signal region fitting, 2: 2 ctau bkg with step function

########## Except dphibins, rap, pt, centrality bins doesn't need "integrated range" bins in the array.
########## Ex ) DO NOT USE rapbins=(0.0-2.4) or ptbins=(6.5-30.0) or centbins=(0.0-100.0)
########## dphibins always needs "0.000-1.571" both for Raa and v2. Add other dphibins if you need
dphibins=(0.000-1.571) #0.000-0.393 0.393-0.785 0.785-1.178 1.178-1.571)
#rapfiner=(0.0-0.3 0.3-0.6 0.6-0.9 0.9-1.2 1.2-1.6 1.6-1.9 1.9-2.1 2.1-2.4)
#rapcoarser2=(0.0-0.6 0.6-1.2 1.2-1.8 1.8-2.4)
#rapcoarser4=(0.0-0.9 0.9-1.6 1.6-2.4)
#for pPb(12/nb)
#rapbins=(-2.4--1.47 -1.47--0.47 -0.47-0.53 0.53-1.47 1.47-2.4 -2.4--0.47 -0.47-1.47 -1.47-0.53)
rapbins=(-1.47--0.53 -0.53-0.47 0.47-1.47 1.47-2.4 -1.47-0.47 0.47-2.4 -0.53-1.47)
rapfiner=(-1.47--1.03 -1.03--0.53 -0.53--0.03 -0.03-0.47 0.47-0.97 0.97-1.47 1.47-1.97 1.97-2.4)
rapfiner2=(-1.47--1.03 -1.03--0.78 -0.78--0.53 -0.53--0.28 -0.28--0.03 -0.03-0.22 0.22-0.47 0.47-0.72 0.72-0.97 0.97-1.22 1.22-1.47 1.47-1.72 1.72-1.97 1.97-2.4)
rapcoarser=(-1.47-0.47 0.47-2.4)
rapside=(-1.47--1.03 1.97-2.4)
#centfiner=(0.0-5.0 5.0-10.0 10.0-15.0 15.0-20.0 20.0-25.0 25.0-30.0 30.0-35.0 35.0-40.0 40.0-45.0 45.0-50.0 50.0-55.0 55.0-60.0 60.0-70.0 70.0-100.0)
#centcoarser2=(0.0-10.0 10.0-20.0 20.0-30.0 30.0-40.0 40.0-50.0 50.0-60.0 60.0-100.0)
#centcoarser4=(0.0-15.0 15.0-30.0 30.0-50.0 50.0-100.0)
centMin=(0.0-100.0)
pt1624=(3.0-4.5 4.5-6.5)
ptfiner=(6.5-7.5 7.5-8.5 8.5-9.5 9.5-10.5 10.5-11.5 11.5-12.5 12.5-14.5 14.5-16.5 16.5-20.0 20.0-30.0)
ptcoarser2=(6.5-8.0 8.0-10.0 10.0-13.0 13.0-30.0)
ptlower=(0.0-2.0 2.0 4.0 0.0-4.0 4.0-6.5 0.0-3.0 3.0-4.5 4.5-6.5 0.0-6.5 6.5-8.0 8.0-10.0 10.0-13.0 13.0-30.0)
ptlower2=(3.0-6.5)
ptcoarser4=(6.5-10.0 10.0-30.0)
pthigher=(40.0-100.0)

################################################################ 
########## Information print out
################################################################ 
txtrst=$(tput sgr0)
txtred=$(tput setaf 2)  #1 Red, 2 Green, 3 Yellow, 4 Blue, 5 Purple, 6 Cyan, 7 White
txtbld=$(tput bold)     #dim (Half-bright mode), bold (Bold characters)

echo "Run fits with ${txtbld}${txtred}$executable${txtrst} on ${txtbld}${txtred}$datasets${txtrst}."
if [ "$storage" != "" ]; then
  echo "Results will be placed on ${txtbld}${txtred}$storage${txtrst}."
fi

################################################################ 
########## Function for progream running
################################################################ 
function program {
  ### Arguments
  rap=$1
  pt=$2
  shift; shift;
  centarr=(${@})

  for cent in ${centarr[@]}; do
    for dphi in ${dphibins[@]}; do
      work=$prefix"_rap"$rap"_pT"$pt"_cent"$cent"_dPhi"$dphi; # Output file name has this prefix
      workMB=$prefix"_rap"$rap"_pT"$pt"_cent0.0-100.0_dPhi0.000-1.571"; 
      workPHI=$prefix"_rap"$rap"_pT"$pt"_cent"$cent"_dPhi0.000-1.571"; 

      echo "Processing: "$work
      printf "#!/bin/csh\n" > $scripts/$work.csh
#      printf "source /afs/cern.ch/sw/lcg/external/gcc/4.3.2/x86_64-slc5/setup.csh; source /afs/cern.ch/user/m/miheejo/thisroot.csh\n" >> $scripts/$work.csh
      printf "cd %s\n" $(pwd) >> $scripts/$work.csh
      printf "eval \`scramv1 runtime -csh\`\n" >> $scripts/$work.csh
      printf "cd -\n" >> $scripts/$work.csh
      printf "cp %s/%s.csh %s/fit2DData.h %s/fit2DData_all.cpp .\n" $scripts $work $(pwd) $(pwd) >> $scripts/$work.csh

      if [ "$cent" == "0.0-100.0" ]; then
        if [ "$dphi" == "0.000-1.571" ]; then
          script="$executable -f $datasets $weight -m $mc1 $mc2 -v $mSigF $mBkgF -d $prefix -r $eventplane $usedPhi -u $resOpt -a $anaBct $ctauBkg -b $ispbpb $isPEE $is2Widths -p $pt -y $rap -t $cent -s $dphi -l $ctaurange -x $runOpt -z $fracfree >& $work.log;"
          echo $script >> $scripts/$work.csh
        elif [ "$dphi" != "0.000-1.571" ]; then
          script="$executable -f $datasets $weight -m $mc1 $mc2 -v $mSigF $mBkgF -d $prefix -r $eventplane $usedPhi -u $resOpt -a 2 $ctauBkg -b $ispbpb $isPEE $is2Widths -p $pt -y $rap -t $cent -s 0.000-1.571 -l $ctaurange -x $runOpt -z $fracfree >& $workPHI.log;"
          echo $script >> $scripts/$work.csh
          script="$executable -f $datasets $weight -m $mc1 $mc2 -v $mSigF $mBkgF -d $prefix -r $eventplane $usedPhi -u $resOpt -a $anaBct $ctauBkg -b $ispbpb $isPEE $is2Widths -p $pt -y $rap -t $cent -s $dphi -l $ctaurange -x $runOpt -z $fracfree >& $work.log;"
          echo $script >> $scripts/$work.csh
        fi
      elif [ "$cent" != "0.0-100.0" ]; then
        if [ "$dphi" == "0.000-1.571" ]; then
          script="$executable -f $datasets $weight -m $mc1 $mc2 -v $mSigF $mBkgF -d $prefix -r $eventplane $usedPhi -u $resOpt -a 2 $ctauBkg -b $ispbpb $isPEE $is2Widths -p $pt -y $rap -t 0.0-100.0 -s 0.000-1.571 -l $ctaurange -x $runOpt -z $fracfree >& $workMB.log;"
          echo $script >> $scripts/$work.csh
          script="$executable -f $datasets $weight -m $mc1 $mc2 -v $mSigF $mBkgF -d $prefix -r $eventplane $usedPhi -u $resOpt -a $anaBct $ctauBkg -b $ispbpb $isPEE $is2Widths -p $pt -y $rap -t $cent -s $dphi -l $ctaurange -x $runOpt -z $fracfree >& $work.log;"
          echo $script >> $scripts/$work.csh
        elif [ "$dphi" != "0.000-1.571" ]; then
          script="$executable -f $datasets $weight -m $mc1 $mc2 -v $mSigF $mBkgF -d $prefix -r $eventplane $usedPhi -u $resOpt -a 2 $ctauBkg -b $ispbpb $isPEE $is2Widths -p $pt -y $rap -t 0.0-100.0 -s 0.000-1.571 -l $ctaurange -x $runOpt -z $fracfree >& $workMB.log;"
          echo $script >> $scripts/$work.csh
          script="$executable -f $datasets $weight -m $mc1 $mc2 -v $mSigF $mBkgF -d $prefix -r $eventplane $usedPhi -u $resOpt -a 2 $ctauBkg -b $ispbpb $isPEE $is2Widths -p $pt -y $rap -t $cent -s 0.000-1.571 -l $ctaurange -x $runOpt -z $fracfree >& $workPHI.log;"
          echo $script >> $scripts/$work.csh
          script="$executable -f $datasets $weight -m $mc1 $mc2 -v $mSigF $mBkgF -d $prefix -r $eventplane $usedPhi -u $resOpt -a $anaBct $ctauBkg -b $ispbpb $isPEE $is2Widths -p $pt -y $rap -t $cent -s $dphi -l $ctaurange -x $runOpt -z $fracfree >& $work.log;"
          echo $script >> $scripts/$work.csh
        fi
      fi

      printf "tar zcvf %s.tgz %s* fit2DData.h fit2DData_all.cpp\n" $work $work >> $scripts/$work.csh
      printf "cp %s.tgz %s\n" $work $storage >> $scripts/$work.csh
      bsub -R "pool>10000" -u songkyo.lee@cer.c -q 1nd -J $work < $scripts/$work.csh
    done
  done
}

################################################################ 
########## Running script with pre-defined binnings
################################################################ 

#program 0.0-2.4 6.5-30.0 0.0-100.0
#program 0.0-2.4 6.5-30.0 ${centfiner[@]}
#program -1.47-2.4 6.5-30.0 0.0-100.0

## for sglMuEtaFiner2
for rap in ${rapfiner2[@]}; do
  program $rap 6.5-30.0 0.0-100.0 #sglMuEtaFiner2 - original analysis
#  program $rap 40.0-100.0 0.0-100.0 # for sglMuEtaHigher
#  for pt in ${ptlower[@]}; do #for slgMuEtaLower
#    program $rap $pt 0.0-100.0
#  done
done

## 2D differential binnings # y-inclusive FW/BW
for rap in ${rapcoarser[@]}; do # for sglMuEtaFiner2
#  for pt in ${pthigher[@]}; do # for sglMuEtaHigher
  for pt in ${ptcoarser2[@]}; do # for sglMuEtaHigher
    program $rap $pt 0.0-100.0
  done
#  for pt in ${ptlower[@]}; do #for slgMuEtaLower
#    program $rap $pt 0.0-100.0
#  done
done

## sglMuEtaLower2 
#for rap in ${rapside[@]}; do
#	program $rap 3.0-6.5 0.0-100.0
#done

