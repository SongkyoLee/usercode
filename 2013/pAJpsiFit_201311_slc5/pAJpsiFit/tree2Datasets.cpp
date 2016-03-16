#include <iostream>
#include <math.h>
#include <fstream>

#include <TROOT.h>
#include "TSystem.h"
#include <TFile.h>
#include <TGraphErrors.h>
#include <TVector3.h>
#include "TH2.h"
#include "TH3.h"
#include "TLorentzVector.h"
#include "TRandom3.h"
#include "TClonesArray.h"
#include "TChain.h"

#include "RooFit.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooCategory.h"
#include "RooPlot.h"

#include <TCanvas.h>
#include "TStyle.h"
#include <TPaveStats.h>


//-1: etHFp+etHFm combined without auto-correlation
//-2: etHFp+etHFm combined with enhanced auto-correlation
//-3: *NOT* flattening + etHFp+etHFm combined without auto-correlation
//otherwise, indicates event plane method
static int RPNUM = -1;

//0: Nominal (one of the mu trig), 1: bit1 & Cowboy, 2: bit1 & Sailor, 3: bit1, 4: bit2, 5: random generation & bit1
//6: one of the single mu trig, 7: (one of the single mu trig) & cowboy, 8: (one of the single mu trig) & sailor
//9: (one of the single mu trig) && (one of the double mu trig)
//10: bit1,2,4 (HLT_HIL1DoubleMu0_NHitQ || HLT_HIL2DoubleMu3 || HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy)
static int trigType = 3;
static bool randChoice = true; //Only valid trigType == 5, true: randx > 0.5, false: randx < 0.5

//runType can be combined with trigType
//0: Don't use this option (default!!) 
//1: nMuValHits > 12, 2: select J/psi with |single mu_eta| < 1.2, 3: |zVtx| < 10 cm
//4: numOfMatch > 1 with a J/psi mass closest dimuon per event
//5: numOfMatch > 2 with a J/psi mass closest dimuon per event
//6: various single muon cuts for both single muons
//7: both single mu pT > 4
//8: -2.4 < both single mu eta < 1.47 // KYO for Pbp
//9: -1.47 < both single mu eta < 0.53 -mid rap
//10: -1.47 < both single mu eta < 2.4 // KYO for pPb
//11: -0.53 < both single mu eta < 1.47 - mid rap
//12: -1.93 < both single mu eta < 1.93 // KYO for pp
//13: -1.00 < both single mu eta < 1.00 - mid rap

static int runType = 0;

//0 : DO NOT weight, 1: Apply weight
static bool doWeighting = false;

//0: don't care about RPAng, 1: Pick events with RPAng != -10
static bool checkRPNUM = false;

static const double Jpsi_MassMin=2.6;
static const double Jpsi_MassMax=3.5;
static const double Jpsi_PtMin=0.0;
static const double Jpsi_PtMax=100;
static const double Jpsi_YMin=0;
static const double Jpsi_YMax=2.4;
static const double Jpsi_CtMin = -3.0;
static const double Jpsi_CtMax = 5.0;
static const double Jpsi_CtErrMin = 0.0;
static const double Jpsi_CtErrMax = 1.0;
static const double Jpsi_PhiMin=-3.14159265359;
static const double Jpsi_PhiMax=3.14159265359;
static const double Jpsi_dPhiMin=Jpsi_PhiMin*2;
static const double Jpsi_dPhiMax=Jpsi_PhiMax*2;

using namespace RooFit;
using namespace std;

static const double PDGJpsiM = 3.096916;

// Variables for a dimuon
struct Condition {
  double theMass, theRapidity, thePt, theCentrality;
  double thePhi, thedPhi, thedPhi22, thedPhi23;
  double vprob, theCt, theCtErr, zVtx, theEff;
  int HLTriggers, Reco_QQ_trig, theCat,Jq;
  int mupl_nMuValHits, mumi_nMuValHits;
  int mupl_numOfMatch, mumi_numOfMatch;
  int mupl_nTrkHits, mumi_nTrkHits;
  int mupl_nTrkWMea, mumi_nTrkWMea;
  double mupl_norChi2_inner, mumi_norChi2_inner, mupl_norChi2_global, mumi_norChi2_global;
  double theCtTrue, genType;
} ;

bool checkTriggers(const struct Condition Jpsi, bool cowboy, bool sailor, double var);
bool checkRunType(const struct Condition Jpsi, const TLorentzVector* m1P, const TLorentzVector* m2P);
bool isAccept(const TLorentzVector* aMuon);
double reducedPhi(double thedPhi);

int main(int argc, char* argv[]) {
  bool Centrality40Bins=false, Centralitypp=false;
  string fileName, outputDir;
  int initev = 0;
  int nevt = -1;

  if (argc == 1) {
    cout << "====================================================================\n";
    cout << "Use the program with this commend:" << endl;
    cout << "./Tree2Datasets =op [RP number] =ot [trigType] =or [runType] =w [Weighting] =f [input TTree file] [output directory]" << endl;
    cout << "./Tree2Datasets =op -1 =ot 3 =or 0 =w 0 =f /tmp/miheejo/mini_Jpsi_Histos_may202012_m25gev.root ." << endl;
    cout << "====================================================================\n";
    return 0;
  }
  
  for (int i=1; i<argc; i++) {
    char *tmpargv = argv[i];
    switch (tmpargv[0]) {
      case '=':{
        switch (tmpargv[1]) {
          case 'c':
            if (0 == atoi(argv[i+1])) Centrality40Bins = true;
            else if (1 == atoi(argv[i+1])) Centralitypp = true;
            break;
          case 'f':
            fileName = argv[i+1];
            outputDir = argv[i+2];
            break;
          case 'o':
            switch (tmpargv[2]) {
              case 'p':
                RPNUM = atoi(argv[i+1]);
                break;
              case 't':
                trigType = atoi(argv[i+1]);
                break;
              case 'r':
                runType = atoi(argv[i+1]);
                break;
              case 'c':
                if (0 == atoi(argv[i+1])) checkRPNUM = false;
                else checkRPNUM = true;
                break;
            }
            break;
          case 'w':
            if (atoi(argv[i+1]) == 0) doWeighting = false;
            else doWeighting =true;
            break;
          case 'e':
            initev = atoi(argv[i+1]);
            nevt = atoi(argv[i+2]);
            break;
        }
      }
    } // end of checking switch loop
  } // end of checking options

  cout << "fileName: " << fileName << endl;
  cout << "output directory: " << outputDir << endl;
  cout << "trigType: "<< trigType << endl;
  cout << "runType: " << runType << endl;
  cout << "checkRPNUM: " << checkRPNUM << endl;
  cout << "RPNUM: " << RPNUM << endl;
  cout << "start event #: " << initev << endl;
  cout << "end event #: " << nevt << endl;


  TFile *file=TFile::Open(fileName.c_str());
  TTree *Tree=(TTree*)file->Get("myTree");

/*  // 4D efficiency files
  string dirPath = "/afs/cern.ch/user/d/dmoon/public/ForJpsiV2/4DEff/0512/";
  char effHistname[1000];
  unsigned int nCentEff = 0;
  int centEff5[] = {0, 4, 8, 12, 24, 40};  //0 10 20 30 60 100
  int centEff2060[] = {0, 4, 8, 24};
  int centEff1060[] = {0, 4, 24};
  vector<int>centEff;

  if (centInput == 2060) {
    for (int i=0; i<4; i++) centEff.push_back(centEff2060[i]);
  } else if (centInput == 1060) {
    for (int i=0; i<3; i++) centEff.push_back(centEff1060[i]);
  } else {
    for (int i=0; i<6; i++) centEff.push_back(centEff5[i]);
  }
  nCentEff = centEff.size()-1;
  cout << "centInput: " <<centInput << " nCentEff: " << nCentEff << endl;

  TFile *effFileNominal[nCentEff], *effFileNominal_LowPt[nCentEff];
  TFile *effFileCowboy[nCentEff], *effFileCowboy_LowPt[nCentEff];
  TFile *effFileSailor[nCentEff], *effFileSailor_LowPt[nCentEff];
  for (int idx=0; idx <nCentEff ; idx++) {
    if (trigType == 3) {
      if (centEff[idx] == 0) {
        sprintf(effHistname,"%s/PrJpsi_PtRapdPhi_Cent00%.0f_default.root",dirPath.c_str(),centEff[idx+1]);
      } else {
        sprintf(effHistname,"%s/PrJpsi_PtRapdPhi_Cent%.0f%.0f_default.root",dirPath.c_str(),centEff[idx],centEff[idx+1]);
      }
      cout << effHistname << endl;
      effFileNominal[idx] = new TFile(effHistname);

      if (centEff[idx] == 0) {
        sprintf(effHistname,"%s/PrJpsi_PtRapdPhi_Cent00%.0f_LowPt_default.root",dirPath.c_str(),centEff[idx+1]);
      } else {
        sprintf(effHistname,"%s/PrJpsi_PtRapdPhi_Cent%.0f%.0f_LowPt_default.root",dirPath.c_str(),centEff[idx],centEff[idx+1]);
      }
      cout << effHistname << endl;
      effFileNominal_LowPt[idx] = new TFile(effHistname);

    } else if (trigType == 1) {
      if (centEff[idx] == 0) {
        sprintf(effHistname,"%s/PrJpsi_PtRapdPhi_Cent00%.0f_cowboy.root",dirPath.c_str(),centEff[idx+1]);
      } else {
        sprintf(effHistname,"%s/PrJpsi_PtRapdPhi_Cent%.0f%.0f_cowboy.root",dirPath.c_str(),centEff[idx],centEff[idx+1]);
      }
      cout << effHistname << endl;
      effFileCowboy[idx] = new TFile(effHistname);

      if (centEff[idx] == 0) {
        sprintf(effHistname,"%s/PrJpsi_PtRapdPhi_Cent00%.0f_LowPt_cowboy.root",dirPath.c_str(),centEff[idx+1]);
      } else {
        sprintf(effHistname,"%s/PrJpsi_PtRapdPhi_Cent%.0f%.0f_LowPt_cowboy.root",dirPath.c_str(),centEff[idx],centEff[idx+1]);
      }
      cout << effHistname << endl;
      effFileCowboy_LowPt[idx] = new TFile(effHistname);

    } else if (trigType == 2) {
      if (centEff[idx] == 0) {
        sprintf(effHistname,"%s/PrJpsi_PtRapdPhi_Cent00%.0f_sailor.root",dirPath.c_str(),centEff[idx+1]);
      } else {
        sprintf(effHistname,"%s/PrJpsi_PtRapdPhi_Cent%.0f%.0f_sailor.root",dirPath.c_str(),centEff[idx],centEff[idx+1]);
      }
      cout << effHistname << endl;
      effFileSailor[idx] = new TFile(effHistname);

      if (centEff[idx] == 0) {
        sprintf(effHistname,"%s/PrJpsi_PtRapdPhi_Cent00%.0f_LowPt_sailor.root",dirPath.c_str(),centEff[idx+1]);
      } else {
        sprintf(effHistname,"%s/PrJpsi_PtRapdPhi_Cent%.0f%.0f_LowPt_sailor.root",dirPath.c_str(),centEff[idx],centEff[idx+1]);
      }
      cout << effHistname << endl;
      effFileSailor_LowPt[idx] = new TFile(effHistname);
    }
  }

  TH3D *heffCentNom[nCentEff], *heffCentNom_LowPt[nCentEff];
  TH3D *heffCentCow[nCentEff], *heffCentCow_LowPt[nCentEff];
  TH3D *heffCentSai[nCentEff], *heffCentSai_LowPt[nCentEff];
  for (int idx=0; idx<nCentEff; idx++) {
    if (trigType == 3) {
      heffCentNom[idx] = (TH3D*)effFileNominal[idx]->Get("eff_default");
      heffCentNom_LowPt[idx] = (TH3D*)effFileNominal_LowPt[idx]->Get("eff_default");
    } else if (trigType == 1) {
      heffCentCow[idx] = (TH3D*)effFileCowboy[idx]->Get("eff_cowboy");
      heffCentCow_LowPt[idx] = (TH3D*)effFileCowboy_LowPt[idx]->Get("eff_cowboy");
    } else if (trigType == 2) {
      heffCentSai[idx] = (TH3D*)effFileSailor[idx]->Get("eff_sailor");
      heffCentSai_LowPt[idx] = (TH3D*)effFileSailor_LowPt[idx]->Get("eff_sailor");
    }
  }
*/

  if (doWeighting &&  (trigType != 3 && trigType != 1 && trigType != 2)) {
    cout << "##########################################################\n";
    cout << "You chose trigType " << trigType << endl;
    cout << "This trigType do NOT work with efficiency weighting.\n";
    cout << "Efficiency weighting will NOT be applied!\n";
    cout << "##########################################################\n";
    doWeighting = false;
  }

  UInt_t          eventNb;
  Int_t           Centrality;
  Int_t           Reco_QQ_size;
  Int_t           Reco_QQ_type[20];   //[Reco_QQ_size]
  Int_t           Reco_QQ_sign[20];   //[Reco_QQ_size]
  Int_t           Reco_QQ_trig[20];   //[Reco_QQ_size]
  Int_t           Reco_QQ_mupl_nMuValHits[20];
  Int_t           Reco_QQ_mumi_nMuValHits[20];
  Int_t           Reco_QQ_mupl_nTrkHits[20];  // track hits plus global muons
  Int_t           Reco_QQ_mumi_nTrkHits[20];  // track hits minus global muons
  Int_t           Reco_QQ_mupl_nTrkWMea[20];  // tracker layers with measurement for plus inner track muons
  Int_t           Reco_QQ_mumi_nTrkWMea[20];  // tracker layers with measurement for minus inner track muons
  Int_t           Reco_QQ_mupl_numOfMatch[20];  // number of matched segments for plus inner track muons
  Int_t           Reco_QQ_mumi_numOfMatch[20];  // number of matched segments for minus inner track muons
  Float_t         Reco_QQ_mupl_norChi2_inner[20];  // chi2/ndof for plus inner track muons
  Float_t         Reco_QQ_mumi_norChi2_inner[20];  // chi2/ndof for minus inner track muons
  Float_t         Reco_QQ_mupl_norChi2_global[20];  // chi2/ndof for plus global muons
  Float_t         Reco_QQ_mumi_norChi2_global[20];  // chi2/ndof for minus global muons
  TClonesArray    *Reco_QQ_4mom;
  TClonesArray    *Reco_QQ_mupl_4mom;
  TClonesArray    *Reco_QQ_mumi_4mom;
  Float_t         Reco_QQ_ctau[20];   //[Reco_QQ_size]
  Float_t         Reco_QQ_ctauErr[20];   //[Reco_QQ_size]
  Float_t         Reco_QQ_VtxProb[20];   //[Reco_QQ_size]
  Float_t         rpAng[38];   //[Reco_QQ_size]
  Float_t         zVtx;         //Primary vertex position
  int             HLTriggers; 
//  Int_t           Gen_QQ_size;
//  Int_t           Gen_QQ_type[20];
//  Float_t         Reco_QQ_ctauTrue[20];   //[Reco_QQ_size]

  TBranch        *b_eventNb;
  TBranch        *b_Centrality;   //!
  TBranch        *b_Reco_QQ_size;   //!
  TBranch        *b_Reco_QQ_type;   //!
  TBranch        *b_Reco_QQ_sign;   //!
  TBranch        *b_Reco_QQ_mupl_nMuValHits;   //!
  TBranch        *b_Reco_QQ_mumi_nMuValHits;   //!
  TBranch        *b_Reco_QQ_mupl_nTrkHits;
  TBranch        *b_Reco_QQ_mumi_nTrkHits;
  TBranch        *b_Reco_QQ_mupl_nTrkWMea;
  TBranch        *b_Reco_QQ_mumi_nTrkWMea;
  TBranch        *b_Reco_QQ_mupl_norChi2_inner;
  TBranch        *b_Reco_QQ_mumi_norChi2_inner;
  TBranch        *b_Reco_QQ_mupl_norChi2_global;
  TBranch        *b_Reco_QQ_mumi_norChi2_global;
  TBranch        *b_Reco_QQ_mupl_numOfMatch;   //!
  TBranch        *b_Reco_QQ_mumi_numOfMatch;   //!
  TBranch        *b_HLTriggers;   //!
  TBranch        *b_Reco_QQ_trig;   //!
  TBranch        *b_Reco_QQ_4mom;   //!
  TBranch        *b_Reco_QQ_mupl_4mom;   //!
  TBranch        *b_Reco_QQ_mumi_4mom;   //!
  TBranch        *b_Reco_QQ_ctau;   //!
  TBranch        *b_Reco_QQ_ctauErr;   //!
  TBranch        *b_Reco_QQ_VtxProb;   //!
  TBranch        *b_rpAng;   //!
  TBranch        *b_zVtx;
//  TBranch        *b_Gen_QQ_size;   //!
//  TBranch        *b_Gen_QQ_type;
//  TBranch        *b_Reco_QQ_ctauTrue;   //!

  TLorentzVector* JP= new TLorentzVector;
  TLorentzVector* m1P= new TLorentzVector;
  TLorentzVector* m2P= new TLorentzVector;


  TH1I *PassingEvent;
  // Normal datasets
  RooDataSet* dataJpsi;
  RooDataSet* dataJpsiSame;
  RooDataSet* dataPsip;
  // Have efficiency for every events
  RooDataSet* dataJpsiW;
  RooDataSet* dataJpsiSameW;
  RooDataSet* dataPsipW;
  // Efficiencies are applied to datasets as a weight
  RooDataSet* dataJpsiWeight;
  RooDataSet* dataJpsiSameWeight;
  RooDataSet* dataPsipWeight;
  
  RooRealVar* Jpsi_Mass;
  RooRealVar* Psip_Mass;      
  RooRealVar* Jpsi_Pt;
  RooRealVar* Jpsi_Ct;
  RooRealVar* Jpsi_CtErr;
  RooRealVar* Jpsi_Y;
  RooRealVar* Jpsi_Phi;
  RooRealVar* Jpsi_dPhi;
  RooRealVar* Jpsi_Cent;
  RooCategory* Jpsi_Type;
  RooCategory* Jpsi_Sign;
  RooRealVar* Jpsi_3DEff; //3D efficiency
//  RooRealVar* Jpsi_CtTrue;
//  RooCategory* MCType;

  Jpsi_Mass = new RooRealVar("Jpsi_Mass","J/#psi mass",Jpsi_MassMin,Jpsi_MassMax,"GeV/c^{2}");
  Psip_Mass = new RooRealVar("Psip_Mass","#psi' mass",3.3,Jpsi_MassMax,"GeV/c^{2}");
  Jpsi_Pt = new RooRealVar("Jpsi_Pt","J/#psi pt",Jpsi_PtMin,Jpsi_PtMax,"GeV/c");
  Jpsi_Y = new RooRealVar("Jpsi_Y","J/#psi y",-Jpsi_YMax,Jpsi_YMax);
  Jpsi_Phi = new RooRealVar("Jpsi_Phi","J/#psi phi",Jpsi_PhiMin,Jpsi_PhiMax,"rad");
  Jpsi_dPhi = new RooRealVar("Jpsi_dPhi","J/#psi phi - rpAng",Jpsi_dPhiMin,Jpsi_dPhiMax,"rad");
  Jpsi_Type = new RooCategory("Jpsi_Type","Category of Jpsi_");
  Jpsi_Sign = new RooCategory("Jpsi_Sign","Charge combination of Jpsi_");
  Jpsi_Ct = new RooRealVar("Jpsi_Ct","J/#psi c#tau",Jpsi_CtMin,Jpsi_CtMax,"mm");
  Jpsi_CtErr = new RooRealVar("Jpsi_CtErr","J/#psi c#tau error",Jpsi_CtErrMin,Jpsi_CtErrMax,"mm");
  Jpsi_3DEff = new RooRealVar("Jpsi_3DEff","J/#psi efficiency weight",1.,100.);
  Jpsi_Cent = new RooRealVar("Centrality","Centrality of the event",0,100);
//  MCType = new RooCategory("MCType","Type of generated Jpsi_");
//  Jpsi_CtTrue = new RooRealVar("Jpsi_CtTrue","J/#psi c#tau true",Jpsi_CtMin,Jpsi_CtMax,"mm");

  Jpsi_Type->defineType("GG",0);
  Jpsi_Type->defineType("GT",1);
  Jpsi_Type->defineType("TT",2);

  Jpsi_Sign->defineType("OS",0);
  Jpsi_Sign->defineType("PP",1);
  Jpsi_Sign->defineType("MM",2);

//  MCType->defineType("PR",0);
//  MCType->defineType("NP",1);

  Reco_QQ_4mom = 0;
  Reco_QQ_mupl_4mom = 0;
  Reco_QQ_mumi_4mom = 0;

  Tree->SetBranchAddress("eventNb", &eventNb, &b_eventNb);
  Tree->SetBranchAddress("Centrality", &Centrality, &b_Centrality);
  if (RPNUM == -3) {  //Not-flatten
    Tree->SetBranchAddress("NfRpAng", rpAng, &b_rpAng);
  } else {  //Flatten reaction plane
    Tree->SetBranchAddress("rpAng", rpAng, &b_rpAng);
  }
  Tree->SetBranchAddress("Reco_QQ_size", &Reco_QQ_size, &b_Reco_QQ_size);
  Tree->SetBranchAddress("HLTriggers", &HLTriggers, &b_HLTriggers);
  Tree->SetBranchAddress("Reco_QQ_trig", Reco_QQ_trig, &b_Reco_QQ_trig);
  Tree->SetBranchAddress("Reco_QQ_type", Reco_QQ_type, &b_Reco_QQ_type);
  Tree->SetBranchAddress("Reco_QQ_sign", Reco_QQ_sign, &b_Reco_QQ_sign);
  Tree->SetBranchAddress("Reco_QQ_mupl_nMuValHits", Reco_QQ_mupl_nMuValHits, &b_Reco_QQ_mupl_nMuValHits);
  Tree->SetBranchAddress("Reco_QQ_mumi_nMuValHits", Reco_QQ_mumi_nMuValHits, &b_Reco_QQ_mumi_nMuValHits);
  Tree->SetBranchAddress("Reco_QQ_mupl_numOfMatch", Reco_QQ_mupl_numOfMatch, &b_Reco_QQ_mupl_numOfMatch);
  Tree->SetBranchAddress("Reco_QQ_mumi_numOfMatch", Reco_QQ_mumi_numOfMatch, &b_Reco_QQ_mumi_numOfMatch);
  Tree->SetBranchAddress("Reco_QQ_mupl_nTrkHits", Reco_QQ_mupl_nTrkHits, &b_Reco_QQ_mupl_nTrkHits);
  Tree->SetBranchAddress("Reco_QQ_mumi_nTrkHits", Reco_QQ_mumi_nTrkHits, &b_Reco_QQ_mumi_nTrkHits);
  Tree->SetBranchAddress("Reco_QQ_mupl_nTrkWMea", Reco_QQ_mupl_nTrkWMea, &b_Reco_QQ_mupl_nTrkWMea);
  Tree->SetBranchAddress("Reco_QQ_mumi_nTrkWMea", Reco_QQ_mumi_nTrkWMea, &b_Reco_QQ_mumi_nTrkWMea);
  Tree->SetBranchAddress("Reco_QQ_mupl_norChi2_inner", Reco_QQ_mupl_norChi2_inner, &b_Reco_QQ_mupl_norChi2_inner);
  Tree->SetBranchAddress("Reco_QQ_mumi_norChi2_inner", Reco_QQ_mumi_norChi2_inner, &b_Reco_QQ_mumi_norChi2_inner);
  Tree->SetBranchAddress("Reco_QQ_mupl_norChi2_global", Reco_QQ_mupl_norChi2_global, &b_Reco_QQ_mupl_norChi2_global);
  Tree->SetBranchAddress("Reco_QQ_mumi_norChi2_global", Reco_QQ_mumi_norChi2_global, &b_Reco_QQ_mumi_norChi2_global);
  Tree->SetBranchAddress("Reco_QQ_4mom", &Reco_QQ_4mom, &b_Reco_QQ_4mom);
  Tree->SetBranchAddress("Reco_QQ_mupl_4mom", &Reco_QQ_mupl_4mom, &b_Reco_QQ_mupl_4mom);
  Tree->SetBranchAddress("Reco_QQ_mumi_4mom", &Reco_QQ_mumi_4mom, &b_Reco_QQ_mumi_4mom);
  Tree->SetBranchAddress("Reco_QQ_ctau", Reco_QQ_ctau, &b_Reco_QQ_ctau);
  Tree->SetBranchAddress("Reco_QQ_ctauErr", Reco_QQ_ctauErr, &b_Reco_QQ_ctauErr);
  Tree->SetBranchAddress("Reco_QQ_VtxProb", Reco_QQ_VtxProb, &b_Reco_QQ_VtxProb);
  Tree->SetBranchAddress("zVtx",&zVtx,&b_zVtx);
//  Tree->SetBranchAddress("Gen_QQ_size", &Gen_QQ_size, &b_Gen_QQ_size);
//  Tree->SetBranchAddress("Gen_QQ_type", Gen_QQ_type, &b_Gen_QQ_type);
//  Tree->SetBranchAddress("Reco_QQ_ctauTrue", Reco_QQ_ctauTrue, &b_Reco_QQ_ctauTrue);

  // Without weighting
  RooArgList varlist(*Jpsi_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_dPhi,*Jpsi_Cent,*Jpsi_Ct,*Jpsi_CtErr);
  RooArgList varlistSame(*Jpsi_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_dPhi,*Jpsi_Cent,*Jpsi_Ct,*Jpsi_CtErr);
  RooArgList varlist2(*Psip_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_dPhi,*Jpsi_Cent,*Jpsi_Ct,*Jpsi_CtErr);
  // With weighting
  RooArgList varlistW(*Jpsi_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_dPhi,*Jpsi_Cent,*Jpsi_3DEff,*Jpsi_Ct,*Jpsi_CtErr);
  RooArgList varlistSameW(*Jpsi_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_dPhi,*Jpsi_Cent,*Jpsi_3DEff,*Jpsi_Ct,*Jpsi_CtErr);
  RooArgList varlist2W(*Psip_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_dPhi,*Jpsi_Cent,*Jpsi_3DEff,*Jpsi_Ct,*Jpsi_CtErr);
/*  RooArgList varlist(*Jpsi_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_Type,*Jpsi_Sign,*Jpsi_Ct,*Jpsi_CtErr);
  RooArgList varlistSame(*Jpsi_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_Type,*Jpsi_Sign,*Jpsi_Ct,*Jpsi_CtErr);
  RooArgList varlist2(*Psip_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_Type,*Jpsi_Sign,*Jpsi_Ct,*Jpsi_CtErr);
*/
/*  RooArgList varlist(*Jpsi_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_Type,*Jpsi_Sign,*MCType,*Jpsi_Ct,*Jpsi_CtErr,*Jpsi_CtTrue);
  RooArgList varlistSame(*Jpsi_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_Type,*Jpsi_Sign,*MCType,*Jpsi_Ct,*Jpsi_CtErr,*Jpsi_CtTrue);
  RooArgList varlist2(*Psip_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_Type,*Jpsi_Sign,*MCType,*Jpsi_Ct,*Jpsi_CtErr,*Jpsi_CtTrue);
*/

  PassingEvent = new TH1I("NumPassingEvent",";;total number of events",1,1,2);
  dataJpsi = new RooDataSet("dataJpsi","A sample",varlist);
  dataJpsiSame = new RooDataSet("dataJpsiSame","A sample",varlistSame);
  dataPsip = new RooDataSet("dataPsip","A sample",varlist2);
  if (doWeighting) {
    dataJpsiW = new RooDataSet("dataJpsiW","A sample",varlistW);
    dataJpsiSameW = new RooDataSet("dataJpsiSameW","A sample",varlistSameW);
    dataPsipW = new RooDataSet("dataPsipW","A sample",varlist2W);
  }

  TH1D *JpsiPt = new TH1D("JpsiPt","JpsiPt",35,0,140);

  ifstream input("../randomNumbers");
  if (trigType == 5) {
    if (!input.is_open()) { cout << "cannot open randomNumbers. exit\n"; return -1; }
  } else {
    input.close();
  }

  if (nevt == -1) nevt = Tree->GetEntries();
  for (int ev=initev; ev<nevt; ++ev) {
    if (ev%100000==0) cout << ">>>>> EVENT " << ev << " / " << Tree->GetEntries() <<  endl;

    Tree->GetEntry(ev);
    
    float theRPAng=0, theRPAng22=0, theRPAng23=0;

    // Normal HI event plane setting
    if (RPNUM >= 0) theRPAng = rpAng[RPNUM];
    else theRPAng = rpAng[22];  //will not be used, put arbitary number

    theRPAng22 = rpAng[22]; //etHFp
    theRPAng23 = rpAng[23]; //etHFm


    //Loop over all dimuons in this event and find the most J/psi mass closest dimuon (runType == 4)
    double diffMass = 1.0;
    bool passMostJpsi = false;
    struct Condition mostJpsi; //Contains all condition variables for the most possible J/psi, used for runType == 4

    for (int i=0; i<Reco_QQ_size; ++i) {
      struct Condition Jpsi; //Contains all condition variables

      JP = (TLorentzVector*) Reco_QQ_4mom->At(i);
      m1P = (TLorentzVector*) Reco_QQ_mupl_4mom->At(i);
      m2P = (TLorentzVector*) Reco_QQ_mumi_4mom->At(i);
      if (Centrality40Bins) Jpsi.theCentrality = Centrality * 2.5;
      else if (Centralitypp) Jpsi.theCentrality = 97.5;
      else Jpsi.theCentrality = Centrality;
      Jpsi.vprob = Reco_QQ_VtxProb[i];
      Jpsi.theCat = Reco_QQ_type[i];
      Jpsi.Jq = Reco_QQ_sign[i];
      Jpsi.theCt = Reco_QQ_ctau[i];
      Jpsi.theCtErr = Reco_QQ_ctauErr[i];
      Jpsi.mupl_nMuValHits = Reco_QQ_mupl_nMuValHits[i];      
      Jpsi.mumi_nMuValHits = Reco_QQ_mumi_nMuValHits[i];      
      Jpsi.mupl_numOfMatch = Reco_QQ_mupl_numOfMatch[i];
      Jpsi.mumi_numOfMatch = Reco_QQ_mumi_numOfMatch[i];
      Jpsi.mupl_nTrkHits = Reco_QQ_mupl_nTrkHits[i];
      Jpsi.mumi_nTrkHits = Reco_QQ_mumi_nTrkHits[i];
      Jpsi.mupl_nTrkWMea = Reco_QQ_mupl_nTrkWMea[i];
      Jpsi.mumi_nTrkWMea = Reco_QQ_mumi_nTrkWMea[i];
      Jpsi.mupl_norChi2_inner = Reco_QQ_mupl_norChi2_inner[i];
      Jpsi.mumi_norChi2_inner = Reco_QQ_mumi_norChi2_inner[i];
      Jpsi.mupl_norChi2_global = Reco_QQ_mupl_norChi2_global[i];
      Jpsi.mumi_norChi2_global = Reco_QQ_mumi_norChi2_global[i];
//      Jpsi.genType = Gen_QQ_type[i];
//      Jpsi.theCtTrue = Reco_QQ_ctauTrue[i];

      Jpsi.theMass =JP->M();
      Jpsi.theRapidity=JP->Rapidity();
      Jpsi.thePt=JP->Pt();
      Jpsi.thePhi = JP->Phi();

      Jpsi.HLTriggers = HLTriggers;
      Jpsi.Reco_QQ_trig = Reco_QQ_trig[i];
      Jpsi.zVtx = zVtx;

      if (checkRPNUM) {
        if (theRPAng > -9) Jpsi.thedPhi=JP->Phi()-theRPAng;
        Jpsi.thedPhi = TMath::Abs(reducedPhi(Jpsi.thedPhi));
        if (theRPAng22 > -9) Jpsi.thedPhi22=JP->Phi()-theRPAng22;
        Jpsi.thedPhi22 = TMath::Abs(reducedPhi(Jpsi.thedPhi22));
        if (theRPAng23 > -9) Jpsi.thedPhi23=JP->Phi()-theRPAng23;
        Jpsi.thedPhi23 = TMath::Abs(reducedPhi(Jpsi.thedPhi23));
   
        if (RPNUM == -1 || RPNUM == -3) {
          if (JP->Eta() < 0) Jpsi.thedPhi = Jpsi.thedPhi22;
          else Jpsi.thedPhi = Jpsi.thedPhi23;
        } else if (RPNUM == -2) {
          if (JP->Eta() < 0) Jpsi.thedPhi = Jpsi.thedPhi23;
          else Jpsi.thedPhi = Jpsi.thedPhi22;
        }

      } else {
        theRPAng = 0;
        theRPAng22 = 0;
        theRPAng23 = 0;
        Jpsi.thedPhi = TMath::Abs(reducedPhi(JP->Phi()));
        Jpsi.thedPhi22 = Jpsi.thedPhi;
        Jpsi.thedPhi23 = Jpsi.thedPhi;
      }

      // get delta Phi between 2 muons to cut out cowboys
      double dPhi2mu = m1P->Phi() - m2P->Phi();
      while (dPhi2mu > TMath::Pi()) dPhi2mu -= 2*TMath::Pi();
      while (dPhi2mu <= -TMath::Pi()) dPhi2mu += 2*TMath::Pi();

      bool cowboy = false, sailor = false;
      if ( 1*dPhi2mu > 0. ) cowboy = true;
      else sailor = true;

      // Check trigger conditions
      double var=0;
      if (trigType == 5)  input >> var; //Read a random number for trigType == 5
      bool triggerCondition = checkTriggers(Jpsi, cowboy, sailor, var);

      bool isAcceptedEP = false;
      if (checkRPNUM) { // for Jpsi v2
        if (RPNUM < 0) {  //combined etHFp+etHFm datasets
          if (RPNUM == -1 || RPNUM == -3) {
            if ((JP->Eta()<0 && theRPAng22 != -10) || (JP->Eta()>=0 && theRPAng23 != -10)) isAcceptedEP = true;
            else isAcceptedEP = false;
          } else if (RPNUM == -2) {
            if ((JP->Eta()<=0 && theRPAng23 != -10) || (JP->Eta()>0 && theRPAng22 != -10)) isAcceptedEP = true;
            else isAcceptedEP = false;
          } else {
            cout << "Wrong RPNUM!\n" << endl;
            return -1;
          }

        } else {  //indivisual event plane datasets
          if ( (theRPAng != -10) && ((RPNUM==22 && JP->Eta()<0) || (RPNUM==23 && JP->Eta()>= 0)) ) isAcceptedEP = true;   //auto-correlation removed
          else if (theRPAng != -10 && RPNUM != 22 && RPNUM !=23) isAcceptedEP = true;
          else isAcceptedEP = false;
        }

      } else {  // for Jpsi raa
        isAcceptedEP = true;
      }

      bool passRunType = checkRunType(Jpsi,m1P,m2P);
      double theEff = 0;

      if (Jpsi.theMass > Jpsi_MassMin && Jpsi.theMass < Jpsi_MassMax && 
          Jpsi.thePt > Jpsi_PtMin && Jpsi.thePt < Jpsi_PtMax && 
          Jpsi.theCt > Jpsi_CtMin && Jpsi.theCt < Jpsi_CtMax && 
          Jpsi.theCtErr > Jpsi_CtErrMin && Jpsi.theCtErr < Jpsi_CtErrMax && 
//          fabs(theRapidity) > Jpsi_YMin && fabs(theRapidity) < Jpsi_YMax &&
          passRunType &&
          triggerCondition &&
          isAcceptedEP &&
          Jpsi.vprob > 0.001
          ) {

        if (doWeighting) {
          double tmpPt = Jpsi.thePt;
          if (tmpPt >= 40.0) tmpPt = 39.9;

          // 4D efficiency
/*          int tmpCent = -1;
          for (int centidx =0; centidx < nCentEff; centidx++){
            if ((Jpsi.theCentrality >= centEff[centidx]) && (Jpsi.theCentrality < centEff[centidx+1])) {
              tmpCent = centidx;
              cout << "theCentrality: " << Jpsi.theCentrality << endl;
              cout << "tmpCent: " << tmpCent << " centidx " << centidx << endl;
            }
          }
          if (tmpCent == -1) {
            theEff = 1.0;
          } else {
            int bin;
            if (trigType == 3){  //bit 1 case
              if (tmpPt < 6.5) {
                bin = heffCentNom_LowPt[tmpCent]->FindBin(Jpsi.thedPhi,tmpPt,fabs(Jpsi.theRapidity));
                theEff = heffCentNom_LowPt[tmpCent]->GetBinContent(bin);
                cout << "low pt" << endl;
              } else {
                bin = heffCentNom[tmpCent]->FindBin(Jpsi.thedPhi,tmpPt,fabs(Jpsi.theRapidity));
                theEff = heffCentNom[tmpCent]->GetBinContent(bin);
              }
            } else if (trigType == 1 && cowboy) { //cowboy
              if (tmpPt < 6.5) {
                bin = heffCentCow_LowPt[tmpCent]->FindBin(Jpsi.thedPhi,tmpPt,fabs(Jpsi.theRapidity));
                theEff = heffCentCow_LowPt[tmpCent]->GetBinContent(bin);
                cout << "low pt" << endl;
              } else {
                bin = heffCentCow[tmpCent]->FindBin(Jpsi.thedPhi,tmpPt,fabs(Jpsi.theRapidity));
                theEff = heffCentCow[tmpCent]->GetBinContent(bin);
              }
            } else if (trigType == 2 && sailor) {  //sailor
              if (tmpPt < 6.5) {
                bin = heffCentSai_LowPt[tmpCent]->FindBin(Jpsi.thedPhi,tmpPt,fabs(Jpsi.theRapidity));
                theEff = heffCentSai_LowPt[tmpCent]->GetBinContent(bin);
                cout << "low pt" << endl;
              } else {
                bin = heffCentSai[tmpCent]->FindBin(Jpsi.thedPhi,tmpPt,fabs(Jpsi.theRapidity));
                theEff = heffCentSai[tmpCent]->GetBinContent(bin);
              }
            }
            cout << "thedPhi: " << Jpsi.thedPhi << " thePt: " << tmpPt << " theRapidity: " << Jpsi.theRapidity << endl;
            cout << "bin: " << bin << " theEff: " << theEff << endl;
          }
*/
        } else { theEff = 1.0; }  // end of the weighting condition
        Jpsi.theEff = 1.0/theEff;

        double tmpDiff = TMath::Abs(PDGJpsiM - Jpsi.theMass);
        if (runType == 4) {
          if (Jpsi.mupl_numOfMatch > 1 && Jpsi.mumi_numOfMatch > 1 && diffMass > tmpDiff) {
            diffMass = tmpDiff;
            mostJpsi = Jpsi;
            passMostJpsi = true;
          }
        } else if (runType == 5) {
          if (Jpsi.mupl_numOfMatch > 2 && Jpsi.mumi_numOfMatch > 2 && diffMass > tmpDiff) {
            diffMass = tmpDiff;
            mostJpsi = Jpsi;
            passMostJpsi = true;
          }
        } else {
          JpsiPt->Fill(Jpsi.thePt);
          Jpsi_Pt->setVal(Jpsi.thePt); 
          Jpsi_Y->setVal(Jpsi.theRapidity); 
          Jpsi_Phi->setVal(Jpsi.thePhi);
          Jpsi_dPhi->setVal(Jpsi.thedPhi);
          Jpsi_Mass->setVal(Jpsi.theMass);
          Psip_Mass->setVal(Jpsi.theMass);
          Jpsi_Ct->setVal(Jpsi.theCt);
          Jpsi_CtErr->setVal(Jpsi.theCtErr);
          Jpsi_3DEff->setVal(Jpsi.theEff);
          Jpsi_Type->setIndex(Jpsi.theCat,kTRUE);
          Jpsi_Cent->setVal(Jpsi.theCentrality);
          if (Jpsi.Jq == 0){ Jpsi_Sign->setIndex(Jpsi.Jq,kTRUE); }
          else { Jpsi_Sign->setIndex(Jpsi.Jq,kTRUE); }
  //        Jpsi_CtTrue->setVal(Jpsi.theCtTrue);
  //        MCType->setIndex(Jpsi.genType,kTRUE);

  //        RooArgList varlist_tmp(*Jpsi_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_Type,*Jpsi_Sign,*MCType,*Jpsi_Ct,*Jpsi_CtErr,*Jpsi_CtTrue);
  //        RooArgList varlist2_tmp(*Psip_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_Type,*Jpsi_Sign,*MCType,*Jpsi_Ct,*Jpsi_CtErr,*Jpsi_CtTrue);
  /*        RooArgList varlist_tmp(*Jpsi_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_Type,*Jpsi_Sign,*Jpsi_Ct,*Jpsi_CtErr);
          RooArgList varlist2_tmp(*Psip_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_Type,*Jpsi_Sign,*Jpsi_Ct,*Jpsi_CtErr);*/
          // Without weighting
          RooArgList varlist_tmp(*Jpsi_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_dPhi,*Jpsi_Cent,*Jpsi_Ct,*Jpsi_CtErr);
          RooArgList varlistSame_tmp(*Jpsi_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_dPhi,*Jpsi_Cent,*Jpsi_Ct,*Jpsi_CtErr);
          RooArgList varlist2_tmp(*Psip_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_dPhi,*Jpsi_Cent,*Jpsi_Ct,*Jpsi_CtErr);
          // With weighting
          RooArgList varlistW_tmp(*Jpsi_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_dPhi,*Jpsi_Cent,*Jpsi_3DEff,*Jpsi_Ct,*Jpsi_CtErr);
          RooArgList varlistSameW_tmp(*Jpsi_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_dPhi,*Jpsi_Cent,*Jpsi_3DEff,*Jpsi_Ct,*Jpsi_CtErr);
          RooArgList varlist2W_tmp(*Psip_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_dPhi,*Jpsi_Cent,*Jpsi_3DEff,*Jpsi_Ct,*Jpsi_CtErr);


          if (Jpsi.Jq == 0) {
            if (Jpsi.theMass < 3.5) {
              dataJpsi->add(varlist_tmp);
              if (doWeighting) dataJpsiW->add(varlistW_tmp);
              PassingEvent->Fill(1);
            }
            if (Jpsi.theMass > 3.3) {
              dataPsip->add(varlist2_tmp);
              if (doWeighting) dataPsipW->add(varlist2W_tmp);
            }
          } else {
            if (Jpsi.theMass < 3.5) {
              dataJpsiSame->add(varlist_tmp);
              if (doWeighting) dataJpsiSameW->add(varlistW_tmp);
            }
          }

        } // runType == 4 or 5 condition
      } // End of if() statement for cuts

    } // End of Reco_QQ_size loop

    // Fill up the most J/psi mass closest dimuon per event
    if ((runType == 4 || runType == 5) && passMostJpsi) {
      Jpsi_Pt->setVal(mostJpsi.thePt); 
      Jpsi_Y->setVal(mostJpsi.theRapidity); 
      Jpsi_Phi->setVal(mostJpsi.thePhi);
      Jpsi_Mass->setVal(mostJpsi.theMass);
      Psip_Mass->setVal(mostJpsi.theMass);
      Jpsi_Ct->setVal(mostJpsi.theCt);
      Jpsi_CtErr->setVal(mostJpsi.theCtErr);
      Jpsi_dPhi->setVal(mostJpsi.thedPhi);
      Jpsi_3DEff->setVal(mostJpsi.theEff);
      Jpsi_Type->setIndex(mostJpsi.theCat,kTRUE);
      Jpsi_Cent->setVal(mostJpsi.theCentrality);
      if (mostJpsi.Jq == 0){ Jpsi_Sign->setIndex(mostJpsi.Jq,kTRUE); }
      else { Jpsi_Sign->setIndex(mostJpsi.Jq,kTRUE); }

      // Without weighting
      RooArgList varlist_tmp(*Jpsi_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_dPhi,*Jpsi_Cent,*Jpsi_Ct,*Jpsi_CtErr);
      RooArgList varlistSame_tmp(*Jpsi_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_dPhi,*Jpsi_Cent,*Jpsi_Ct,*Jpsi_CtErr);
      RooArgList varlist2_tmp(*Psip_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_dPhi,*Jpsi_Cent,*Jpsi_Ct,*Jpsi_CtErr);
      // With weighting
      RooArgList varlistW_tmp(*Jpsi_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_dPhi,*Jpsi_Cent,*Jpsi_3DEff,*Jpsi_Ct,*Jpsi_CtErr);
      RooArgList varlistSameW_tmp(*Jpsi_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_dPhi,*Jpsi_Cent,*Jpsi_3DEff,*Jpsi_Ct,*Jpsi_CtErr);
      RooArgList varlist2W_tmp(*Psip_Mass,*Jpsi_Pt,*Jpsi_Y,*Jpsi_dPhi,*Jpsi_Cent,*Jpsi_3DEff,*Jpsi_Ct,*Jpsi_CtErr);

      if (mostJpsi.Jq == 0) {
        if (mostJpsi.theMass < 3.5) {
          dataJpsi->add(varlist_tmp);
          if (doWeighting) dataJpsiW->add(varlistW_tmp);
          PassingEvent->Fill(1);
        }
        if (mostJpsi.theMass > 3.3) {
          dataPsip->add(varlist2_tmp);
          if (doWeighting) dataPsipW->add(varlist2W_tmp);
        }
      } else {
        if (mostJpsi.theMass < 3.5) {
          dataJpsiSame->add(varlist_tmp);
          if (doWeighting) dataJpsiSameW->add(varlistW_tmp);
        }
      }
      
    } // End of runType == 4 or 5
    passMostJpsi = false;
  } // End of tree event loop

  char namefile[200];
  TCanvas *canv = new TCanvas("canv","canv",800,600);
  canv->cd();
  JpsiPt->Draw("text");
  sprintf(namefile,"%s/JpsiPt.pdf",outputDir.c_str());
  canv->SaveAs(namefile);
  delete canv;

  if (doWeighting) {
    dataJpsiWeight = new RooDataSet("dataJpsiWeight","A sample",*dataJpsiW->get(),Import(*dataJpsiW),WeightVar(*Jpsi_3DEff));
    dataJpsiSameWeight = new RooDataSet("dataJpsiSameWeight","A sample",*dataJpsiSameW->get(),Import(*dataJpsiSameW),WeightVar(*Jpsi_3DEff));
    dataPsipWeight = new RooDataSet("dataPsipWeight","A sample",*dataPsipW->get(),Import(*dataPsipW),WeightVar(*Jpsi_3DEff));
  }

  /// *** Fill TFiles with RooDataSet
  TFile* Out;
  sprintf(namefile,"%s/%s.root",outputDir.c_str(),outputDir.c_str());
  Out = new TFile(namefile,"RECREATE");
  Out->cd();
  dataJpsi->Write();
  dataJpsiSame->Write();
  dataPsip->Write();
  if (doWeighting) {
    dataJpsiW->Write();
    dataJpsiSameW->Write();
    dataPsipW->Write();
    dataJpsiWeight->Write();
    dataJpsiSameWeight->Write();
    dataPsipWeight->Write();
  }
  Out->Close();

  cout << "PassingEvent: " << PassingEvent->GetEntries() << endl;
  delete PassingEvent;

  if (trigType == 5) input.close();

  return 0;

}




////////// sub-routines
double reducedPhi(double thedPhi) {
  if(thedPhi < -TMath::Pi()) thedPhi += 2.*TMath::Pi();
  if(thedPhi > TMath::Pi()) thedPhi -= 2.*TMath::Pi();
  if(thedPhi < -TMath::Pi()/2) thedPhi +=TMath::Pi();
  if(thedPhi > TMath::Pi()/2) thedPhi -=TMath::Pi();

  return thedPhi;
}

bool isAccept(const TLorentzVector* aMuon) {
  if (fabs(aMuon->Eta()) < 1.2) return true;
  else return false;
}

bool checkRunType(const struct Condition Jpsi, const TLorentzVector* m1P, const TLorentzVector* m2P) {
  if (runType == 1) {
    if (Jpsi.mupl_nMuValHits > 12 && Jpsi.mumi_nMuValHits > 12) return true;
    else return false;
  }
  else if (runType == 2) {
    if (isAccept(m1P) && isAccept(m2P)) return true;
    else return false;
  }
  else if (runType == 3) {
    if (fabs(Jpsi.zVtx) < 10.0) return true;
    else return false;
  }
  else if (runType == 4) {
    if (m1P->Pt() > 7.5 && m2P->Pt() > 7.5) return true;
    else return false;
  }
  else if (runType == 5) {
    if (m1P->Pt() > 5.0 && m2P->Pt() > 5.0) return true;
    else return false;
  }
  else if (runType == 6) {
    bool Matches      = Jpsi.mupl_numOfMatch > 1 && Jpsi.mumi_numOfMatch > 1;
    bool InnerChiMeas = (Jpsi.mupl_norChi2_inner/Jpsi.mupl_nTrkWMea < 0.15) &&
                        (Jpsi.mumi_norChi2_inner/Jpsi.mumi_nTrkWMea < 0.15);
    bool MuHits       = Jpsi.mupl_nMuValHits > 12 && Jpsi.mumi_nMuValHits > 12; 
    bool TrkHits      = Jpsi.mupl_nTrkHits > 12 && Jpsi.mumi_nTrkHits > 12;
    bool GlobalChi    = (Jpsi.mupl_norChi2_global/(Jpsi.mupl_nMuValHits+Jpsi.mupl_nTrkHits) < 0.15) &&
                        (Jpsi.mumi_norChi2_global/(Jpsi.mumi_nMuValHits+Jpsi.mumi_nTrkHits) < 0.15);

    if (TrkHits && Matches && InnerChiMeas && MuHits && GlobalChi) return true;
    else return false;
  }
  else if (runType == 7) {
    if (m1P->Pt() > 4.0 && m2P->Pt() > 4.0) return true;
    else return false;
  }
  // For Pbp (first run period)
  else if (runType == 8) {
    if (m1P->Eta() > -2.4 && m2P->Eta() > -2.4 && m1P->Eta() < 1.47 && m2P->Eta() < 1.47) return true;
    else return false;
  }
  else if (runType == 9) {
    if (m1P->Eta() > -1.47 && m2P->Eta() > -1.47 && m1P->Eta() < 0.53 && m2P->Eta() < 0.53) return true;
    else return false;
  }
  else if (runType == 78) {
    if ((m1P->Eta() > -2.4 && m2P->Eta() > -2.4 && m1P->Eta() < 1.47 && m2P->Eta() < 1.47) && (m1P->Pt() > 4.0 && m2P->Pt() > 4.0)) return true;
    else return false;
  }
  else if (runType == 79) {
    if ((m1P->Eta() > -1.47 && m2P->Eta() > -1.47 && m1P->Eta() < 0.53 && m2P->Eta() < 0.53) && (m1P->Pt() > 4.0 && m2P->Pt() > 4.0)) return true;
    else return false;
  }
  // For pPb (second run period)
  else if (runType == 10) {
    if (m1P->Eta() > -1.47 && m2P->Eta() > -1.47 && m1P->Eta() < 2.4 && m2P->Eta() < 2.4) return true;
    else return false;
  }
  else if (runType == 11) {
    if (m1P->Eta() > -0.53 && m2P->Eta() > -0.53 && m1P->Eta() < 1.47 && m2P->Eta() < 1.47) return true;
    else return false;
  }
  else if (runType == 710) {
    if ((m1P->Eta() > -1.47 && m2P->Eta() > -1.47 && m1P->Eta() < 2.4 && m2P->Eta() < 2.4) && (m1P->Pt() > 4.0 && m2P->Pt() > 4.0)) return true;
    else return false;
  }
  else if (runType == 711) {
    if ((m1P->Eta() > -0.53 && m2P->Eta() > -0.53 && m1P->Eta() < 1.47 && m2P->Eta() < 1.47) && (m1P->Pt() > 4.0 && m2P->Pt() > 4.0)) return true;
    else return false;
  }
  // For pp
	else if (runType == 12) {
		if (m1P->Eta() > -1.93 && m2P->Eta() > -1.93 && m1P->Eta() < 1.93 && m2P->Eta() < 1.93) return true;
		else return false;
	}
	else if (runType == 13) {
		if (m1P->Eta() > -1.00 && m2P->Eta() > -1.00 && m1P->Eta() < 1.00 && m2P->Eta() < 1.00) return true;
		else return false;
	}
	else if (runType == 712) {
		if ((m1P->Eta() > -1.93 && m2P->Eta() > -1.93 && m1P->Eta() < 1.93 && m2P->Eta() < 1.93) && (m1P->Pt()> 4.0 && m2P->Pt() > 4.0)) return true;
		 else return false;
	}
	else if (runType == 713) {
		if ((m1P->Eta() > -1.00 && m2P->Eta() > -1.00 && m1P->Eta() < 1.00 && m2P->Eta() < 1.00) && (m1P->Pt()> 4.0 && m2P->Pt() > 4.0)) return true;
		 else return false;
	}
  return true;
}

bool checkTriggers(const struct Condition Jpsi, bool cowboy, bool sailor, double var) {
  bool singleMu = false, doubleMu = false;
  bool triggerCondition = false;
  if ( ( (Jpsi.HLTriggers&1)==1 && (Jpsi.Reco_QQ_trig&1)==1 ) ||
       ( (Jpsi.HLTriggers&2)==2 && (Jpsi.Reco_QQ_trig&2)==2 ) ||
       ( (Jpsi.HLTriggers&4)==4 && (Jpsi.Reco_QQ_trig&4)==4 ) ||
       ( (Jpsi.HLTriggers&8)==8 && (Jpsi.Reco_QQ_trig&8)==8 ) ) {
    doubleMu = true;
  } else { doubleMu = false; }

  if ( ( (Jpsi.HLTriggers&16)==16 && (Jpsi.Reco_QQ_trig&16)==16 ) ||
       ( (Jpsi.HLTriggers&32)==32 && (Jpsi.Reco_QQ_trig&32)==32 ) ||
       ( (Jpsi.HLTriggers&64)==64 && (Jpsi.Reco_QQ_trig&64)==64 ) ||
       ( (Jpsi.HLTriggers&128)==128 && (Jpsi.Reco_QQ_trig&128)==128 ) ) {
    singleMu = true;
  } else { singleMu = false; } //HLTriggers should be removed before using

  if (trigType == 0) { //nominal case // should de modified!
    if ( singleMu || doubleMu ) { triggerCondition = true; }
    else { triggerCondition = false; }

  } else if (trigType ==1) { //HLT_PAL1DoubleMuOpen_v1, cowboy
//    if ( (Jpsi.HLTriggers&1)==1 && (Jpsi.Reco_QQ_trig&1)==1 && cowboy) { triggerCondition = true; }
    if ( (Jpsi.Reco_QQ_trig&1)==1 && cowboy) { triggerCondition = true; }
    else { triggerCondition = false; }

  } else if (trigType ==2) {  //HLT_PAL1DoubleMuOpen_v1, sailor
    if ( (Jpsi.Reco_QQ_trig&1)==1 && sailor ) { triggerCondition = true; }
    else { triggerCondition = false; }

  } else if (trigType ==3) {  //HLT_PAL1DoubleMuOpen_v1
    if ( (Jpsi.Reco_QQ_trig&1)==1 ) { triggerCondition = true; }
    else { triggerCondition = false; }

  } else if (trigType ==4) {  //HLT_HIL2DoubleMu3
    if ( (Jpsi.Reco_QQ_trig&2)==2 ) { triggerCondition = true; }
    else { triggerCondition = false; }

  } else if ( trigType ==5 ) { // HLT_PAL1DoubleMuOpen_v1 && Random selection for cowboy, sailor
    if ( (Jpsi.HLTriggers&1)==1 && (Jpsi.Reco_QQ_trig&1)==1 ) {
      if ( (randChoice && (0.5 > var)) || (!randChoice && (0.5 < var)) ) { triggerCondition = true; }
      else { triggerCondition = false; }

    } else {
      triggerCondition = false;
    }

  } else if (trigType ==6) {  //Single muon triggers only
    if ( singleMu ) { triggerCondition = true; }
    else { triggerCondition = false; }

  } else if (trigType ==7) {  //Single muon triggers only & cowboy
    if ( singleMu && cowboy ) { triggerCondition = true; }
    else { triggerCondition = false; }

  } else if (trigType ==8) {  //Single muon triggers only & sailor
    if ( singleMu && sailor ) { triggerCondition = true; }
    else { triggerCondition = false; }

  } else if (trigType ==9) {  //one of the single muon trig && one of the double muon trig
    if (singleMu && doubleMu ) { triggerCondition = true; }
    else { triggerCondition = false; }

  } else if (trigType ==10) {  // HLT_HIL1DoubleMu0_NHitQ || HLT_HIL2DoubleMu3 || HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy
    if ( ( (Jpsi.HLTriggers&1)==1 && (Jpsi.Reco_QQ_trig&1)==1 ) ||
         ( (Jpsi.HLTriggers&2)==2 && (Jpsi.Reco_QQ_trig&2)==2 ) ||
         ( (Jpsi.HLTriggers&8)==8 && (Jpsi.Reco_QQ_trig&8)==8 ) ) {
      triggerCondition = true; }
    else { triggerCondition = false; }

  } else if (trigType ==11) {  // HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy
    if ( (Jpsi.HLTriggers&8)==8 && (Jpsi.Reco_QQ_trig&8)==8 ) {
      triggerCondition = true; }
    else { triggerCondition = false; }

  } else {
    cout << "Not valid trigType!\n";
    triggerCondition = false;
  }

  return triggerCondition;
}
