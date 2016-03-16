void AnaExample(){
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.12);
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetMarkerSize(1.2);

  TFile *in = new TFile("HLTrgAna_RelVal_JpsitoMM_20131205.root","READ");
  TTree *Ana = (TTree*)in->Get("Ana");

  // Reco muon information
  TH1F *hRecoMuPtGlb = new TH1F("hRecoMuPtGlb",";p_{T} (GeV/c);",40, 0, 20);
  TH1F *hRecoMuPtTrk = new TH1F("hRecoMuPtTrk",";p_{T} (GeV/c);",40, 0, 20);
  hRecoMuPtGlb->Sumw2();
  hRecoMuPtTrk->Sumw2();
  TH1F *hRegitMuPtGlb = new TH1F("hRegitMuPtGlb",";p_{T} (GeV/c);",40, 0, 20);
  TH1F *hRegitMuPtTrk = new TH1F("hRegitMuPtTrk",";p_{T} (GeV/c);",40, 0, 20);
  hRegitMuPtGlb->Sumw2();
  hRegitMuPtTrk->Sumw2();

  Ana->Draw("recoMu_pt>>hRecoMuPtGlb","recoMu_Glb==1","E");
  Ana->Draw("recoMu_pt>>hRecoMuPtTrk","recoMu_Trk==1","E");
  Ana->Draw("regrecoMu_pt>>hRegitMuPtGlb","regrecoMu_Glb==1","E");
  Ana->Draw("regrecoMu_pt>>hRegitMuPtTrk","regrecoMu_Trk==1","E");

  hRecoMuPtGlb->SetMarkerStyle(20);
  hRecoMuPtTrk->SetMarkerStyle(20);
  hRecoMuPtGlb->SetMarkerColor(kBlue+1);
  hRecoMuPtTrk->SetMarkerColor(kBlue+1);
  hRegitMuPtGlb->SetMarkerStyle(24);
  hRegitMuPtTrk->SetMarkerStyle(24);
  hRegitMuPtGlb->SetMarkerColor(kRed+1);
  hRegitMuPtTrk->SetMarkerColor(kRed+1);

  TLegend *leg = new TLegend(0.56,0.53,0.78,0.70);
  leg->SetFillStyle(0);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetHeader("Global Muons");
  leg->SetTextSize(0.04);
  leg->AddEntry(hRecoMuPtGlb,"reco muon","PL");
  leg->AddEntry(hRegitMuPtGlb,"regit muon","PL");

  TLegend *leg1 = new TLegend(0.56,0.53,0.78,0.70);
  leg1->SetFillStyle(0);
  leg1->SetFillColor(0);
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.04);
  leg1->SetHeader("Tracker Muons");
  leg1->AddEntry(hRecoMuPtTrk,"reco muon","PL");
  leg1->AddEntry(hRegitMuPtTrk,"regit muon","PL");


  TCanvas *c1 = new TCanvas("c1","",550,500);
  hRegitMuPtTrk->Draw();
  hRecoMuPtTrk->Draw("same");
  leg->Draw("same");

  c1->SaveAs("comp_glb_reco_vs_regit.png");

  hRegitMuPtTrk->Draw();
  hRecoMuPtTrk->Draw("same");

  leg1->Draw("same");

  c1->SaveAs("comp_trk_reco_vs_regit.png");

  // Reco muon information Trigger (For example: HLT_HIL1DoubleMu0_HighQ_v5):
  TH1F *hHLTRecoMuPtGlb = new TH1F("hHLTRecoMuPtGlb",";p_{T} (GeV/c);",40, 0, 20);
  TH1F *hHLTRecoMuPtTrk = new TH1F("hHLTRecoMuPtTrk",";p_{T} (GeV/c);",40, 0, 20);
  hHLTRecoMuPtGlb->Sumw2();
  hHLTRecoMuPtTrk->Sumw2();
  TH1F *hHLTRegitMuPtGlb = new TH1F("hHLTRegitMuPtGlb",";p_{T} (GeV/c);",40, 0, 20);
  TH1F *hHLTRegitMuPtTrk = new TH1F("hHLTRegitMuPtTrk",";p_{T} (GeV/c);",40, 0, 20);
  hHLTRegitMuPtGlb->Sumw2();
  hHLTRegitMuPtTrk->Sumw2();

  Ana->Draw("recoMu_pt>>hHLTRecoMuPtGlb","recoMu_Glb==1 && nHLT_HIL1DoubleMu0_HighQ_v5 == 1","E");
  Ana->Draw("recoMu_pt>>hHLTRecoMuPtTrk","recoMu_Trk==1 && nHLT_HIL1DoubleMu0_HighQ_v5 == 1","E");
  Ana->Draw("regrecoMu_pt>>hHLTRegitMuPtGlb","regrecoMu_Glb==1 && nHLT_HIL1DoubleMu0_HighQ_v5 == 1","E");
  Ana->Draw("regrecoMu_pt>>hHLTRegitMuPtTrk","regrecoMu_Trk==1 && nHLT_HIL1DoubleMu0_HighQ_v5 == 1","E");

  hHLTRecoMuPtGlb->SetMarkerStyle(20);
  hHLTRecoMuPtTrk->SetMarkerStyle(20);
  hHLTRecoMuPtGlb->SetMarkerColor(kBlue+1);
  hHLTRecoMuPtTrk->SetMarkerColor(kBlue+1);
  hHLTRegitMuPtGlb->SetMarkerStyle(24);
  hHLTRegitMuPtTrk->SetMarkerStyle(24);
  hHLTRegitMuPtGlb->SetMarkerColor(kRed+1);
  hHLTRegitMuPtTrk->SetMarkerColor(kRed+1);

  TLegend *leg = new TLegend(0.56,0.53,0.78,0.70);
  leg->SetFillStyle(0);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetHeader("Global Muons");
  leg->SetTextSize(0.04);
  leg->AddEntry(hHLTRecoMuPtGlb,"reco muon","PL");
  leg->AddEntry(hHLTRegitMuPtGlb,"regit muon","PL");

  TLegend *leg1 = new TLegend(0.56,0.53,0.78,0.70);
  leg1->SetFillStyle(0);
  leg1->SetFillColor(0);
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.04);
  leg1->SetHeader("Tracker Muons");
  leg1->AddEntry(hHLTRecoMuPtTrk,"reco muon","PL");
  leg1->AddEntry(hHLTRegitMuPtTrk,"regit muon","PL");

  TLatex *lt1 = new TLatex();
  lt1->SetNDC();
  lt1->SetTextSize(0.035);

  TCanvas *c1 = new TCanvas("c1","",550,500);
  hHLTRegitMuPtTrk->Draw();
  hHLTRecoMuPtTrk->Draw("same");
  leg->Draw("same");
  lt1->DrawLatex(0.55,0.90,"HLT_HIL1DoubleMu0_HighQ");

  c1->SaveAs("comp_glb_reco_vs_regit_HLT.png");

  hHLTRegitMuPtTrk->Draw();
  hHLTRecoMuPtTrk->Draw("same");

  leg1->Draw("same");
  lt1->DrawLatex(0.55,0.90,"HLT_HIL1DoubleMu0_HighQ");

  c1->SaveAs("comp_trk_reco_vs_regit_HLT.png");

  hRegitMuPtTrk->SetMarkerStyle(20);
  hRegitMuPtTrk->SetMarkerColor(kBlue+1);
  hRegitMuPtTrk->Draw();
  hHLTRegitMuPtTrk->Draw("same");

  TLegend *leg2 = new TLegend(0.43,0.53,0.65,0.70);
  leg2->SetFillStyle(0);
  leg2->SetFillColor(0);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.035);
  leg2->SetHeader("Regit Tracker Muons");
  leg2->AddEntry(hRegitMuPtTrk,"w/o HLT_HIL1DoubleMu0_HighQ","PL");
  leg2->AddEntry(hHLTRegitMuPtTrk,"with HLT_HIL1DoubleMu0_HighQ","PL");
  leg2->Draw();

  c1->SaveAs("comp_trk_regit_HLT.png");

  TH1F *hHLTRegitMuPtTrk2 = (TH1F*)hHLTRegitMuPtTrk->Clone();
  hHLTRegitMuPtTrk2->Divide(hRegitMuPtTrk);

  hHLTRegitMuPtTrk2->SetMaximum(1.05);
  hHLTRegitMuPtTrk2->SetMinimum(0.0);
  hHLTRegitMuPtTrk2->SetMarkerStyle(20);
  hHLTRegitMuPtTrk2->SetMarkerColor(kBlack);
  hHLTRegitMuPtTrk2->GetYaxis()->SetTitle("Efficiency");
  hHLTRegitMuPtTrk2->Draw();
  lt1->DrawLatex(0.55,0.90,"HLT_HIL1DoubleMu0_HighQ");

  c1->SaveAs("eff_trk_regit_HLT.png");

  // Reco muon information Trigger (For example: HLT_HIL2Mu3_v5):
  TH1F *hHLT2RecoMuPtGlb = new TH1F("hHLT2RecoMuPtGlb",";p_{T} (GeV/c);",40, 0, 20);
  TH1F *hHLT2RecoMuPtTrk = new TH1F("hHLT2RecoMuPtTrk",";p_{T} (GeV/c);",40, 0, 20);
  hHLT2RecoMuPtGlb->Sumw2();
  hHLT2RecoMuPtTrk->Sumw2();
  TH1F *hHLT2RegitMuPtGlb = new TH1F("hHLT2RegitMuPtGlb",";p_{T} (GeV/c);",40, 0, 20);
  TH1F *hHLT2RegitMuPtTrk = new TH1F("hHLT2RegitMuPtTrk",";p_{T} (GeV/c);",40, 0, 20);
  hHLT2RegitMuPtGlb->Sumw2();
  hHLT2RegitMuPtTrk->Sumw2();

  Ana->Draw("recoMu_pt>>hHLT2RecoMuPtGlb","recoMu_Glb==1 && nHLT_HIL2Mu3_v5 == 1","E");
  Ana->Draw("recoMu_pt>>hHLT2RecoMuPtTrk","recoMu_Trk==1 && nHLT_HIL2Mu3_v5 == 1","E");
  Ana->Draw("regrecoMu_pt>>hHLT2RegitMuPtGlb","regrecoMu_Glb==1 && nHLT_HIL2Mu3_v5 == 1","E");
  Ana->Draw("regrecoMu_pt>>hHLT2RegitMuPtTrk","regrecoMu_Trk==1 && nHLT_HIL2Mu3_v5 == 1","E");

  hHLT2RecoMuPtGlb->SetMarkerStyle(20);
  hHLT2RecoMuPtTrk->SetMarkerStyle(20);
  hHLT2RecoMuPtGlb->SetMarkerColor(kBlue+1);
  hHLT2RecoMuPtTrk->SetMarkerColor(kBlue+1);
  hHLT2RegitMuPtGlb->SetMarkerStyle(24);
  hHLT2RegitMuPtTrk->SetMarkerStyle(24);
  hHLT2RegitMuPtGlb->SetMarkerColor(kRed+1);
  hHLT2RegitMuPtTrk->SetMarkerColor(kRed+1);

  TLegend *leg = new TLegend(0.56,0.53,0.78,0.70);
  leg->SetFillStyle(0);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetHeader("Global Muons");
  leg->SetTextSize(0.04);
  leg->AddEntry(hHLT2RecoMuPtGlb,"reco muon","PL");
  leg->AddEntry(hHLT2RegitMuPtGlb,"regit muon","PL");

  TLegend *leg1 = new TLegend(0.56,0.53,0.78,0.70);
  leg1->SetFillStyle(0);
  leg1->SetFillColor(0);
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.04);
  leg1->SetHeader("Tracker Muons");
  leg1->AddEntry(hHLT2RecoMuPtTrk,"reco muon","PL");
  leg1->AddEntry(hHLT2RegitMuPtTrk,"regit muon","PL");

  TLatex *lt1 = new TLatex();
  lt1->SetNDC();
  lt1->SetTextSize(0.035);

  TCanvas *c1 = new TCanvas("c1","",550,500);
  hHLT2RegitMuPtTrk->Draw();
  hHLT2RecoMuPtTrk->Draw("same");
  leg->Draw("same");
  lt1->DrawLatex(0.55,0.90,"HLT_HIL2Mu3");

  c1->SaveAs("comp_glb_reco_vs_regit_HLT2.png");

  hHLT2RegitMuPtTrk->Draw();
  hHLT2RecoMuPtTrk->Draw("same");

  leg1->Draw("same");
  lt1->DrawLatex(0.55,0.90,"HLT_HIL2Mu3");

  c1->SaveAs("comp_trk_reco_vs_regit_HLT2.png");

  hRegitMuPtTrk->SetMarkerStyle(20);
  hRegitMuPtTrk->SetMarkerColor(kBlue+1);
  hRegitMuPtTrk->Draw();
  hHLT2RegitMuPtTrk->Draw("same");

  TLegend *leg2 = new TLegend(0.43,0.53,0.65,0.70);
  leg2->SetFillStyle(0);
  leg2->SetFillColor(0);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.035);
  leg2->SetHeader("Regit Tracker Muons");
  leg2->AddEntry(hRegitMuPtTrk,"w/o HLT_HIL2Mu3","PL");
  leg2->AddEntry(hHLT2RegitMuPtTrk,"with HLT_HIL2Mu3","PL");
  leg2->Draw();

  c1->SaveAs("comp_trk_regit_HLT2.png");

  TH1F *hHLT2RegitMuPtTrk2 = (TH1F*)hHLT2RegitMuPtTrk->Clone();
  hRegitMuPtTrk->Rebin(2);
  hHLT2RegitMuPtTrk2->Rebin(2);
  hHLT2RegitMuPtTrk2->Divide(hRegitMuPtTrk);

  hHLT2RegitMuPtTrk2->SetMaximum(1.05);
  hHLT2RegitMuPtTrk2->SetMinimum(0.0);
  hHLT2RegitMuPtTrk2->SetMarkerStyle(20);
  hHLT2RegitMuPtTrk2->SetMarkerColor(kBlack);
  hHLT2RegitMuPtTrk2->GetYaxis()->SetTitle("Efficiency");
  hHLT2RegitMuPtTrk2->Draw();
  lt1->DrawLatex(0.73,0.90,"HLT_HIL2Mu3");

  c1->SaveAs("eff_trk_regit_HLT2.png");


}
