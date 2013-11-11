#!/bin/bash

# for Pbp
#./Pbp_nRaps4.sh Fit2DDataPbp datasets/Pbp18.38nb/default_bit1                 Pbp_default_bit1 >& log_Pbp_default_bit1 &
#./Pbp_mu4GeV.sh Fit2DDataPbp datasets/Pbp18.38nb/default_bit1_mu4GeV          Pbp_default_mu4GeV >& log_Pbp_default_mu4GeV &
#./Pbp_nRaps4_etaAll.sh Fit2DDataPbp datasets/Pbp18.38nb/default_bit1_singleMuEtaAll  Pbp_default_singleMuEtaAll >& log_Pbp_default_singleMuEtaAll &
# KYO
#./Pbp_nRaps4_etaAll.sh Fit2DDataPbp outRooData_Pbp/singleMuEtaAll_bit1 Pbp_singleMuEtaAll_bit1 >& log_Pbp_singleMuEtaAll_bit1 &

# for pPb
#./pPb_nRaps4.sh Fit2DDatapPb datasets/pPb12.55nb/default_bit1                 pPb_default_bit1 >& log_pPb_default_bit1 &
#./pPb_mu4GeV.sh Fit2DDatapPb datasets/pPb12.55nb/default_bit1_mu4GeV          pPb_default_mu4GeV >& log_pPb_default_mu4GeV &
#./pPb_nRaps4_etaAll.sh Fit2DDatapPb datasets/pPb12.55nb/default_bit1_singleMuEtaAll  pPb_default_singleMuEtaAll >& log_pPb_default_singleMuEtaAll &
# KYO
#./pPb_nRaps4_etaAll.sh Fit2DDatapPb outRooData_pPb/singleMuEtaAll_bit1 pPb_singleMuEtaAll_bit1 >& log_pPb_singleMuEtaAll_bit1 &

# for pp
#KYO
./pp_nRaps4_etaAll.sh Fit2DDatapp outRooData_pp/singleMuEtaAll_bit1 pp_singleMuEtaAll_bit1 >& log_pp_singleMuEtaAll_bit1 &
