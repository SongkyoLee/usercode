#include <iostream>
#include <string>

#include <TROOT.h>
#include <TStyle.h>
#include <TApplication.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include <TH1D.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>

using namespace std;

void Error(string msg);
void SetHistStyle(TH1* h, int i) ;
void SetLegendStyle(TLegend* l);

int eff(void) {
  TFile *fin = new TFile("./Jpsi_Histos.root","read");
  if (!fin->IsOpen()) Error("Input file is not good");

  TTree *myTree = (TTree*)fin->Get("myTree");
  if (!myTree) Error("myTree doesn't exist");

  string trigPath[] = {
    "HLT_PAL1DoubleMu0_HighQ_v1",
    "HLT_PAL1DoubleMuOpen_v1",
    "HLT_PAMu1_Track1_Mgt2_v1",
    "HLT_PAMu3_Track1_Mgt2_v1",
    "HLT_PAL2DoubleMu3_v1",
    "HLT_PAL2Mu3_NHitQ_v1",
    "HLT_PAMu3_v1",
    "HLT_PAMu7_v1",
    "HLT_PAMu12_v1"
  };
  const int nTrig = sizeof(trigPath)/sizeof(string);
  int trigJpsi[nTrig] = {0};
  int trigAll=0;
  TH1D *trigPt[nTrig], *trigRap[nTrig], *allPt, *allRap, *allPtSingle, *allRapSingle;

  for (int i=0; i< nTrig; i++) {
    char name[512], title[512];
    sprintf(name,"%s p_{T}",trigPath[i].c_str());
    sprintf(title,";J/#psi p_{T} [GeV/c];Efficiency");
    trigPt[i] = new TH1D(name,title,15,0,15);
    sprintf(name,"%s rapidity",trigPath[i].c_str());
    sprintf(title,";J/#psi rapidity [rad];Efficiency");
    trigRap[i] = new TH1D(name,title,48,-2.4,2.4);
  }
  allPt = new TH1D("All Jpsi pt",";J/#psi p_{T} [GeV/c];Counts",15,0,15);
  allRap = new TH1D("All Jpsi rap",";J/#psi rapidity [rad];Counts",48,-2.4,2.4);
  allPtSingle = new TH1D("All single muon pt",";muon p_{T} [GeV/c];Counts",15,0,15);
  allRapSingle = new TH1D("All single muon rap",";muon rapidity [rad];Counts",48,-2.4,2.4);
  
  Int_t Reco_QQ_size;
  Int_t Reco_QQ_trig[20];
  Int_t HLTriggers;
  TClonesArray *Reco_QQ_4mom = 0;

  TBranch *b_Reco_QQ_size;
  TBranch *b_Reco_QQ_trig;
  TBranch *b_HLTriggers;
  TBranch *b_Reco_QQ_4mom;

  TLorentzVector *Jp = new TLorentzVector;

  myTree->SetBranchAddress("Reco_QQ_size", &Reco_QQ_size, &b_Reco_QQ_size);
  myTree->SetBranchAddress("Reco_QQ_trig", Reco_QQ_trig, &b_Reco_QQ_trig);
  myTree->SetBranchAddress("Reco_QQ_4mom", &Reco_QQ_4mom, &b_Reco_QQ_4mom);
  myTree->SetBranchAddress("HLTriggers", &HLTriggers, &b_HLTriggers);

  for (int i=0; i<myTree->GetEntries(); i++) {
    myTree->GetEntry(i);
    for (int jp=0; jp<Reco_QQ_size; jp++) {
      Jp = (TLorentzVector*) Reco_QQ_4mom->At(jp);
      allPt->Fill(Jp->Pt());
      allRap->Fill(Jp->Rapidity());
      allPtSingle->Fill();
      allRapSingle->Fill();
      
      if ( (HLTriggers&1)==1 && (Reco_QQ_trig[jp]&1)==1 ) {
        trigPt[0]->Fill(Jp->Pt());
        trigRap[0]->Fill(Jp->Rapidity());
      }
      if ( (HLTriggers&2)==2 && (Reco_QQ_trig[jp]&2)==2 ) {
        trigPt[1]->Fill(Jp->Pt());
        trigRap[1]->Fill(Jp->Rapidity());
      }
      if ( (HLTriggers&4)==4 && (Reco_QQ_trig[jp]&4)==4 ) {
        trigPt[2]->Fill(Jp->Pt());
        trigRap[2]->Fill(Jp->Rapidity());
      }
      if ( (HLTriggers&8)==8 && (Reco_QQ_trig[jp]&8)==8 ) {
        trigPt[3]->Fill(Jp->Pt());
        trigRap[3]->Fill(Jp->Rapidity());
      }
      if ( (HLTriggers&16)==16 && (Reco_QQ_trig[jp]&16)==16 ) {
        trigPt[4]->Fill(Jp->Pt());
        trigRap[4]->Fill(Jp->Rapidity());
      }
      if ( (HLTriggers&32)==32 && (Reco_QQ_trig[jp]&32)==32 ) {
        trigPt[5]->Fill(Jp->Pt());
        trigRap[5]->Fill(Jp->Rapidity());
      }
      if ( (HLTriggers&64)==64 && (Reco_QQ_trig[jp]&64)==64 ) {
        trigPt[6]->Fill(Jp->Pt());
        trigRap[6]->Fill(Jp->Rapidity());
      }
      if ( (HLTriggers&128)==128 && (Reco_QQ_trig[jp]&128)==128 ) {
        trigPt[7]->Fill(Jp->Pt());
        trigRap[7]->Fill(Jp->Rapidity());
      }
/*      if ( (HLTriggers&256)==256 && (Reco_QQ_trig[jp]&256)==256 ) {
        trigPt[8]->Fill(Jp->Pt());
        trigRap[8]->Fill(Jp->Rapidity());
      } */
    } // end of Reco_QQ_size loop

  }
  
  TLegend *leg_do = new TLegend(0.16,0.64,0.58,0.88);
  SetLegendStyle(leg_do);
  TLegend *leg_do_rap = new TLegend(0.35,0.64,0.8,0.88);
  SetLegendStyle(leg_do_rap);
  TLegend *leg_si = new TLegend(0.16,0.64,0.58,0.88);
  SetLegendStyle(leg_si);
  TLegend *leg_si_rap = new TLegend(0.35,0.64,0.8,0.88);
  SetLegendStyle(leg_si_rap);
  TLegend *leg_eff_pt_do = new TLegend(0.16,0.72,0.58,0.9);
  SetLegendStyle(leg_eff_pt_do);
  TLegend *leg_eff_pt_si = new TLegend(0.2,0.7,0.58,0.88);
  SetLegendStyle(leg_eff_pt_si);
  TLegend *leg_eff_rap_do = new TLegend(0.4,0.73,0.8,0.90);
  SetLegendStyle(leg_eff_rap_do);
  TLegend *leg_eff_rap_si = new TLegend(0.4,0.2,0.8,0.40);
  SetLegendStyle(leg_eff_rap_si);
  
  cout << "All: " << allPt->GetEntries() << " " << allRap->GetEntries() << endl;
  trigAll = allPt->GetEntries();

  allPt->SetLineColor(kBlack);
  allPt->SetLineWidth(2.4);
  allRap->SetLineColor(kBlack);
  allRap->SetLineWidth(2.4);
  leg_do->AddEntry(allPt,"All Jpsi","l");
  leg_do_rap->AddEntry(allPt,"All Jpsi","l");
  leg_si->AddEntry(allPt,"All Jpsi","l");
  leg_si_rap->AddEntry(allPt,"All Jpsi","l");

  for (int tr=0; tr < nTrig; tr++) {
    cout << trigPath[tr] << endl;
    SetHistStyle(trigPt[tr],tr);
    SetHistStyle(trigRap[tr],tr);
    if (tr >=5) {
      SetHistStyle(trigPt[tr],tr-5);
      SetHistStyle(trigRap[tr],tr-5);
    }
    cout << trigPt[tr]->GetEntries() << " " << trigRap[tr]->GetEntries() << endl;
    trigJpsi[tr] = trigPt[tr]->GetEntries();
    char title[512];
    sprintf(title,"%s (%.2f)",trigPath[tr].c_str(), (float)trigJpsi[tr]/(float)trigAll);
    
    if (tr < 5) {
      leg_do->AddEntry(trigPt[tr],title,"l");
      leg_do_rap->AddEntry(trigPt[tr],title,"l");
      leg_eff_rap_do->AddEntry(trigPt[tr],title,"l");
      leg_eff_pt_do->AddEntry(trigPt[tr],title,"l");
    }
    
    if (tr >= 5) {
      leg_si->AddEntry(trigPt[tr],title,"l");
      leg_si_rap->AddEntry(trigPt[tr],title,"l");
      leg_eff_rap_si->AddEntry(trigPt[tr],title,"l");
      leg_eff_pt_si->AddEntry(trigPt[tr],title,"l");
    }
  }

  gStyle->SetOptStat(0);
  gStyle->SetPadRightMargin(0.035);
  gStyle->SetPadLeftMargin(0.13);
  
  TCanvas *c = new TCanvas("c","c",600,600);
  c->Draw();

  allPt->Draw();
  allPt->GetYaxis()->SetTitleOffset(1.9);
  for (int tr=0; tr<nTrig; tr++) {
    if (tr < 5)
      trigPt[tr]->Draw("same");
  }
  leg_do->Draw();
  c->SaveAs("pt_double.pdf");
  c->Clear();
 
  allPt->Draw();
  allPt->GetYaxis()->SetTitleOffset(1.9);
  for (int tr=0; tr<nTrig; tr++) {
    if (tr >= 5) 
      trigPt[tr]->Draw("same");
  }
  leg_si->Draw();
  c->SaveAs("pt_single.pdf");
  c->Clear();

  allRap->Draw();
  allRap->GetYaxis()->SetTitleOffset(1.9);
  for (int tr=0; tr<nTrig; tr++) {
    if (tr < 5)
      trigRap[tr]->Draw("same");
  }
  leg_do_rap->Draw();
  c->SaveAs("rap_double.pdf"); 
  c->Clear();

  allRap->Draw();
  allRap->GetYaxis()->SetTitleOffset(1.9);
  for (int tr=0; tr<nTrig; tr++) {
    if (tr >= 5 ) 
      trigRap[tr]->Draw("same");
  }
  leg_si_rap->Draw();
  c->SaveAs("rap_single.pdf"); 
  c->Clear();

  TH1D *gpt = new TH1D("pt",";J/#psi p_{T} [GeV/c];Eff",15,0,15);
  TH1D *grap = new TH1D("rap",";J/#psi rapidity [rad];Eff",48,-2.4,2.4);

  gpt->GetYaxis()->SetTitleOffset(1.9);
  gpt->GetYaxis()->SetRangeUser(0,1.2);
  gpt->Draw();
  for (int tr=0; tr<nTrig; tr++) {
    if (tr < 5 ) {
      trigPt[tr]->Divide(allPt);
      trigPt[tr]->Draw("same");
    }
  }
  leg_eff_pt_do->Draw();
  c->SaveAs("pt_eff_double.pdf");
  c->Clear();

  gpt->GetYaxis()->SetTitleOffset(1.9);
  gpt->GetYaxis()->SetRangeUser(0,1.2);
  gpt->Draw();
  for (int tr=0; tr<nTrig; tr++) {
    if (tr >= 5) {
      trigPt[tr]->Divide(allPt);
      trigPt[tr]->Draw("same");
    }
  }
  leg_eff_pt_si->Draw();
  c->SaveAs("pt_eff_single.pdf");
  c->Clear();
  
  grap->GetYaxis()->SetTitleOffset(1.9);
  grap->GetYaxis()->SetRangeUser(0,1.2);
  grap->Draw();
  for (int tr=0; tr<nTrig; tr++) {
    if (tr < 5) {
      trigRap[tr]->Divide(allRap);
      trigRap[tr]->Draw("same");
    }
  }
 
  leg_eff_rap_do->Draw();
  c->SaveAs("rap_eff_double.pdf"); 
  c->Clear();

  grap->GetYaxis()->SetTitleOffset(1.9);
  grap->GetYaxis()->SetRangeUser(0,1.2);
  grap->Draw();
  for (int tr=0; tr<nTrig; tr++) {
    if (tr >= 5) {
      trigRap[tr]->Divide(allRap);
      trigRap[tr]->Draw("same");
    }
  }
 
  leg_eff_rap_si->Draw();
  c->SaveAs("rap_eff_single.pdf"); 
  c->Clear();


  return 0;
}

void Error(string msg) {
  std::cout << msg << std::endl;
  gApplication->Terminate(-1);
}

void SetHistStyle(TH1* h, int i) {
//  int colorArr[6] = {kBlack, kBlue, kRed, kGreen+2, kOrange, kMagenta+2};
//  int colorArr[] = {kGray+2, kBlack, kRed, kRed+2, kOrange+1, kOrange+8, kGreen+2, kGreen+4, kAzure+1, kAzure+3, kViolet+5, kViolet+3, kMagenta, kMagenta+2};
  int colorArr[] = {kRed+1, kOrange+1, kOrange-8, kGreen+2, kAzure+1, kBlue+2, kViolet+5, kViolet-4, kMagenta, kMagenta+2};
  int markerFullArr[6] = {kFullCircle, kFullSquare, kFullTriangleUp, kFullTriangleDown, kFullStar, kFullDiamond};
  int markerOpenArr[6] = {kOpenCircle, kOpenSquare, kOpenTriangleUp, kOpenTriangleDown, kOpenStar, kOpenDiamond};
  
  h->SetLineColor(colorArr[i]);
  h->SetLineWidth(2.4);
  h->SetMarkerColor(colorArr[i]);
  h->SetMarkerStyle(kOpenCircle);
//  if (i < 10)  h->SetMarkerStyle(markerFullArr[i]);
//  else h->SetMarkerStyle(markerOpenArr[i-10]);
  h->SetMarkerSize(1.5);

  return;
}

void SetLegendStyle(TLegend* l) {
  l->SetFillColor(0);
  l->SetFillStyle(4000);
  l->SetBorderSize(0);
  l->SetMargin(0.1);
}
