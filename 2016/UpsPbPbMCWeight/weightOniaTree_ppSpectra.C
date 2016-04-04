////////////////////////////////////////////////////////////////////////////////////
//// filterEff (NOT used): https://twiki.cern.ch/twiki/bin/view/CMS/DileptonEmbeddingRequest#Onia_2015
//// In this code, each of the PbPb MCs are normalized so as to fit the pT spectra of pp MC.
//// filterEff are not used and weight factors are calculated within this code.
//// For 3S, uncomment "for_3S" part and comment out "for_1S" and "for_2S" (should be modified by hand..)
////////////////////////////////////////////////////////////////////////////////////
#include "commonUtility.h"
#include <THStack.h>

int k1S = 1; 
int k2S = 2; 
int k3S = 3; 

int nbin = 100;
double binmin = 0;
double binmax = 30;
double pTbin[] = {0., 3., 6., 9., 12., 15., 30}; // "for_1S" & "for_2S"
//double pTbin[] = {0., 3., 6., 9., 30}; // "for_3S"
const Int_t numTree = sizeof(pTbin)/sizeof(double)-1;

TCanvas* ctmp = new TCanvas("ctmp","ctmp",300,300);

TString szFile1SPP = {"OniaTree_Ups1SMM_5p02TeV_TuneCUETP8M1_HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1"};
TString szFile2SPP = {"OniaTree_Ups2SMM_5p02TeV_TuneCUETP8M1_HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1"};
TString szFile3SPP = {"OniaTree_Ups3SMM_5p02TeV_TuneCUETP8M1_HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1"};

TString szFile1S[] = {
  "OniaTree_Pythia8_Ups1SMM_ptUps_00_03_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1",
  "OniaTree_Pythia8_Ups1SMM_ptUps_03_06_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1",
  "OniaTree_Pythia8_Ups1SMM_ptUps_06_09_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1",
  "OniaTree_Pythia8_Ups1SMM_ptUps_09_12_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1",
  "OniaTree_Pythia8_Ups1SMM_ptUps_12_15_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1",
  "OniaTree_Pythia8_Ups1SMM_ptUps_15_30_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1"
};
TString szFile2S[] = {
  "OniaTree_Pythia8_Ups2SMM_ptUps2S_00_03_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1",
  "OniaTree_Pythia8_Ups2SMM_ptUps2S_03_06_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1",
  "OniaTree_Pythia8_Ups2SMM_ptUps2S_06_09_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1",
  "OniaTree_Pythia8_Ups2SMM_ptUps2S_09_12_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1",
  "OniaTree_Pythia8_Ups2SMM_ptUps2S_12_15_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1",
  "OniaTree_Pythia8_Ups2SMM_ptUps2S_15_inf_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1"
};
TString szFile3S[] = {
  "OniaTree_Pythia8_Ups3SMM_ptUps3S_00_03_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1",
  "OniaTree_Pythia8_Ups3SMM_ptUps3S_03_06_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1",
  "OniaTree_Pythia8_Ups3SMM_ptUps3S_06_09_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1",
  "OniaTree_Pythia8_Ups3SMM_ptUps3S_09_inf_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1"
};

double* getWeight(int state = k1S, bool isLog=false);

////////////////////////////////////////////////////////////////////////
//// main function
void weightOniaTree_ppSpectra(bool isLog=false){

  gROOT->Macro("./Style.C");
  if (isLog) gPad->SetLogy(1);
  TH1::SetDefaultSumw2();

  cout << endl<< "numTree = " << numTree << endl;
  
  //// "for_1S"
  double *pTmp1S=getWeight(k1S,isLog);
  double wfactor1S[numTree]; // weighting to each sample
  cout << " *************** Final Weight Factor 1S *************** " << endl;
  for (int it=0; it<numTree; it++){
    wfactor1S[it] = *(pTmp1S + it);
    cout << " * "<< it <<"th pt range, weight factor of 1S = " << wfactor1S[it] << endl;
  }
  cout << " ****************************************************** " << endl;
  
  //// "for_2S"
  double *pTmp2S=getWeight(k2S,isLog);
  double wfactor2S[numTree]; // weighting to each sample
  cout << " *************** Final Weight Factor 3S *************** " << endl;
  for (int it=0; it<numTree; it++){
    wfactor2S[it] = *(pTmp2S + it);
    cout << " * "<< it <<"th pt range, weight factor of 2S = " << wfactor2S[it] << endl;
  }
  cout << " ****************************************************** " << endl;
  
  /*
  //// "for_3S"
  double *pTmp3S=getWeight(k3S,isLog);
  double wfactor3S[numTree]; // weighting to each sample
  cout << " *************** Final Weight Factor 3S *************** " << endl;
  for (int it=0; it<numTree; it++){
    wfactor3S[it] = *(pTmp3S + it);
    cout << " * "<< it <<"th pt range, weight factor of 3S = " << wfactor3S[it] << endl;
  }
  cout << " ****************************************************** " << endl;
  */
} // end of main function

////////////////////////////////////////////////////////////////////////
//// sub-function

double* getWeight(int state, bool isLog){

  gROOT->Macro("./Style.C");
  if (isLog) gPad->SetLogy(1);
  TH1::SetDefaultSumw2();

  ////for pp
  TFile* fInPP;
  TTree* myTreeInPP;
  TH1D* hGenPP;
  int genEntriesPP;
  double genIntegPP[numTree];
  //// for AA
  TFile* fInAA[numTree];
  TTree* myTreeInAA[numTree];
  TH1D* hGenBefore[numTree];
  TH1D* hGenAfter[numTree];
  int genEntriesAA[numTree];
  double genIntegAA[numTree];
  double weightOrig[numTree];
  
  static double wfactor[numTree]; // weighting to each sample

  //// read in files
  if (state==k1S) {
    cout << endl << " *************** Start 1S *************** " << endl;
    fInPP = new TFile(Form("/storage/OniaTree/Onia5TeV/ppOfficialMC/%s.root",szFile1SPP.Data()),"READ");
    for (int it=0; it<numTree; it++){ 
      fInAA[it] = new TFile(Form("/storage/OniaTree/Onia5TeV/PbPbOfficialMC/%s.root",szFile1S[it].Data()),"READ");
    }
  }else if (state==k2S) {
    cout << endl << " *************** Start 2S *************** " << endl;
    fInPP = new TFile(Form("/storage/OniaTree/Onia5TeV/ppOfficialMC/%s.root",szFile2SPP.Data()),"READ");
    for (int it=0; it<numTree; it++){ 
      fInAA[it] = new TFile(Form("/storage/OniaTree/Onia5TeV/PbPbOfficialMC/%s.root",szFile2S[it].Data()),"READ");
    }
  }else if (state==k3S) {
    cout << endl << " *************** Start 3S *************** " << endl;
    fInPP = new TFile(Form("/storage/OniaTree/Onia5TeV/ppOfficialMC/%s.root",szFile3SPP.Data()),"READ");
    for (int it=0; it<numTree; it++){ 
      fInAA[it] = new TFile(Form("/storage/OniaTree/Onia5TeV/PbPbOfficialMC/%s.root",szFile3S[it].Data()),"READ");
    }
  }  
 
  // check input 
  if (fInPP->IsZombie()) { cout << "*** CANNOT open input files"<<endl;}
  for (int it=0; it<numTree; it++){ 
    if (fInAA[it]->IsZombie()) { cout << "*** CANNOT open input files"<<endl;}
  }  
  
  //////////////////////////////////////////////////
  ctmp->cd();
  ////////////// get pp dist.
  myTreeInPP = (TTree*)fInPP->Get("hionia/myTree");
  if ( myTreeInPP == 0 ){ myTreeInPP = (TTree*)fInPP->Get("myTree");}
  genEntriesPP = myTreeInPP->GetEntries();
  cout << " *** genEntriesPP = " << genEntriesPP << endl; //only for checking
  hGenPP = new TH1D("hGenPP",";Gen p_{T} (GeV); Entries",nbin,binmin,binmax); 
  myTreeInPP->Draw(Form("Gen_QQ_4mom.Pt()>>%s",hGenPP->GetName())); 
  handsomeTH1(hGenPP,1);
  hGenPP->SetLineWidth(2);
  for (int it=0; it<numTree;it++){
    genIntegPP[it]=hGenPP->Integral(pTbin[it]*(nbin/binmax)+1,pTbin[it+1]*(nbin/binmax));
    cout << it << "th pTrange genIntegPP = " << genIntegPP[it] << endl;
  }
  ////////////// get PbPb dist. 
  for (int it=0; it<numTree; it++){
    myTreeInAA[it] = (TTree*)fInAA[it]->Get("hionia/myTree");
    if ( myTreeInAA[it] == 0 ){ myTreeInAA[it] = (TTree*)fInAA[it]->Get("myTree");}
    //// fill pT dist. before weight
    hGenBefore[it] = new TH1D(Form("hGenBefore_%d",it),";Gen p_{T} (GeV); Entries before weight",nbin,binmin,binmax); 
    myTreeInAA[it]->Draw(Form("Gen_QQ_4mom.Pt()>>%s",hGenBefore[it]->GetName())); 
    handsomeTH1(hGenBefore[it],it+2);
  }
  
  TCanvas* c1 = new TCanvas("c1","before weight",600,600);
  if (isLog) gPad->SetLogy(1);
  c1->cd(1);
  hGenPP->Draw("hist");
  for (int it=0; it<numTree; it++){
    hGenBefore[it]->Draw("hist same");  
  }
  c1->SaveAs(Form("plotsWeight/beforeWeight_state%d_log%d.pdf",state,(int)isLog));
  
  ////////////////////////////////////////////////////////////////////////////////  
  //// calculate wfactor && check distributions after weight
  
  ctmp->cd();
  for (int it=0; it<numTree; it++){
    weightOrig[it] = myTreeInAA[it]->GetWeight(); 
    genEntriesAA[it] = myTreeInAA[it]->GetEntries();
    genIntegAA[it]=hGenBefore[it]->Integral(pTbin[it]*(nbin/binmax)+1,pTbin[it+1]*(nbin/binmax)); // only for check
    cout << it << "th pTrange weightOrig  = " << weightOrig[it] << endl;
    cout << it << "th pTrange genEntriesAA  = " << genEntriesAA[it] << endl;
    
    wfactor[it] = genIntegPP[it]/(genEntriesAA[it]*weightOrig[it]);
    //wfactor[it] = genIntegPP[it]/(genEntriesAA[it]);
    
    hGenAfter[it] = (TH1D*)hGenBefore[it]->Clone(Form("hGenAfter_%d",it));
    hGenAfter[it]->Scale(wfactor[it]);
    handsomeTH1(hGenAfter[it],it+2);
  }
    
  TCanvas* c2 = new TCanvas("c2","after weight",600,600);
  if (isLog) gPad->SetLogy(1);
  c2->cd(1);
  hGenPP->Draw("hist");
  for (int it=0; it<numTree; it++){
    hGenAfter[it]->Draw("hist same"); 
  }
  c2->SaveAs(Form("plotsWeight/afterWeight_state%d_log%d.pdf",state,(int)isLog));
    
  ////////////////////////////////////////////////////////////////////////////////  
  //// check Stack
  THStack* hsGen = new THStack("hsGen","");
  TH1D* hGenTmp[numTree];
  for (int it=0; it<numTree; it++){
    hGenTmp[it]=(TH1D*)hGenAfter[it]->Clone(Form("hGenTmp_%d",it));
    handsomeTH1(hGenTmp[it],it+2);
    hGenTmp[it]->SetFillColor(it+2);
    hGenTmp[it]->SetFillStyle(3001);
    hsGen->Add(hGenTmp[it]);
  }
  
  TCanvas* c3 = new TCanvas("c3","stack",600,600);
  if (isLog) gPad->SetLogy(1);
  c3->cd(1);
  hsGen->Draw("hist");  
  hGenPP->Draw("hist same");
  c3->SaveAs(Form("plotsWeight/stack_state%d_log%d.pdf",state,(int)isLog));
  
  return wfactor;
}

