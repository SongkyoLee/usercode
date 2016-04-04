# PbPbMCWeight
- [Style.C]  and [commonUtility.h] are basic macros
- [weightOniaTree_ppSpectra.C] : calculate weight factors and check normalized pT distributions
    - First, make directory [plotsWeight] to save figures
    - option "isLog" : y-axis with a log scale or not
    - Default : 1S and 2S will be calculated
      - For 3S, uncomment "for_3S" part and comment out "for_1S" and "for_2S" (should be modified by hand..)
