#!/bin/bash
eval `scramv1 runtime -sh`

#---input data
inputf=root://eoscms//eos/cms
#inputf=$inputf/store/user/miheejo/TREE/2011PbPb/RegIt/All_Histos_cmssw445p1_RegIt_v3_small.root
#inputfpbp=/afs/cern.ch/work/k/kyolee/private/cms442/src/pAJpsi/outTree/Jpsi_v2.24_muLessPV_Histos_Runs_210498-211256.root
#inputfppb=/afs/cern.ch/work/k/kyolee/private/cms442/src/pAJpsi/outTree/Jpsi_v2.24_muLessPV_Histos_Runs_211313-211631.root
#inputfpp=/afs/cern.ch/work/k/kyolee/private/cms442/src/pAJpsi/outTree/All_v2.24_Histos_Runs_211739-211831_woPileUpRej_muLessPV.root
inputfpbp=$inputf/store/user/miheejo/TREE/2013pPb/Jpsi_v2.24_muLessPV_Histos_Runs_210498-211256.root
inputfppb=$inputf/store/user/miheejo/TREE/2013pPb/Jpsi_v2.24_muLessPV_Histos_Runs_211313-211631.root
inputfpp=$inputf/store/group/phys_heavyions/dileptons/Data2013/pp/Prompt/TTrees/All_v2.24_Histos_Runs_211739-211831_woPileUpRej_muLessPV.root

#---input MC
#inputfpAPRMC=/afs/cern.ch/work/k/kyolee/private/cms442/src/pAJpsi/outTreeMC/PRMC_Histos.root
#inputfpANPMC=/afs/cern.ch/work/k/kyolee/private/cms442/src/pAJpsi/outTreeMC/NPMC_Histos.root
#inputfppPRMC=/afs/cern.ch/work/k/kyolee/private/cms442/src/pAJpsi/outTreeMC/PromptJpsi_pp2760_MCTemplate_cms538p3.root
#inputfppNPMC=/afs/cern.ch/work/k/kyolee/private/cms442/src/pAJpsi/outTreeMC/NonPromptJpsi_pp2760_MCTemplate_cms538p3.root
inputfpAPRMC=$inputf/store/user/miheejo/TREE/2013pPb/MC/PRMC_Histos.root
inputfpANPMC=$inputf/store/user/miheejo/TREE/2013pPb/MC/NPMC_Histos.root
inputfppPRMC=/afs/cern.ch/work/m/miheejo/public/TREE/PromptJpsi_pp2760_MCTemplate_cms538p3.root
inputfppNPMC=/afs/cern.ch/work/m/miheejo/public/TREE/NonPromptJpsi_pp2760_MCTemplate_cms538p3.root

cent=2  #0: centrality 40 bins(pbpb), 1: pp,MC(const=97.5), else:PbPb
#runtype=0
trigtype=3 #HLT_PAL1DoubleMuOpen_v1 
#datatype=0 #0: default 1: flip the rapidity signs
#  Caution : if Jpsi_Y sign is flipped, sglMu_eta sign also should be flipped
#  Therefore, runType should be filpped : (8,9,78,79) <=> (10,11,710,711)

function program {
  if [ ! -d $1 ]; then
    mkdir $1
  else
    echo " "
    echo "===== Target directory exists! Check is it okay to delete or not.";
  fi

  ./Tree2Datasets =c $2 =ot $3 =or $4 =f $5 $1 >& $1/log &
}

function programMC {
  if [ ! -d $1 ]; then
    mkdir $1
  else
    echo " "
    echo "===== Target directory exists! Check is it okay to delete or not.";
  fi

  ./Tree2DatasetsMC =c $2 =ot $3 =or $4 =od $5 =f $6 $1 >& $1/log &
}

# 1. Data
# run for Pbp
program outRoo_Pbp_sglMuEtaAll $cent $trigtype 8 $inputfpbp
# run for pPb
program outRoo_pPb_sglMuEtaAll $cent $trigtype 10 $inputfppb
# run for pp
program outRoo_pp_sglMuEtaAll 1 $trigtype 12 $inputfpp

# 2. MC
# run for Pbp -MC
programMC outRoo_PRMC_Pbp_sglMuEtaAll 1 $trigtype 8 0 $inputfpAPRMC 
programMC outRoo_NPMC_Pbp_sglMuEtaAll 1 $trigtype 8 0 $inputfpANPMC 
#run for pPb -MC
programMC outRoo_PRMC_pPb_sglMuEtaAll 1 $trigtype 8 1 $inputfpAPRMC
programMC outRoo_NPMC_pPb_sglMuEtaAll 1 $trigtype 8 1 $inputfpANPMC 
#run for pp -MC
programMC outRoo_PRMC_pp_sglMuEtaAll 1 $trigtype 12 0 $inputfppPRMC 
programMC outRoo_NPMC_pp_sglMuEtaAll 1 $trigtype 12 0 $inputfppNPMC 

