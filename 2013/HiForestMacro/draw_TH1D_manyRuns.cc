#include <Riostream.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TDirectory.h>
#include <TLegend.h>
 
#include <sstream>
#include <string>

using namespace std;
void SetHistStyle(TH1* h, int i) ;
void SetLegendStyle(TLegend* l);

void draw_TH1D_manyRuns()
{
  //Set style
  gROOT->Macro("/afs/cern.ch/user/k/kyolee/private/cms538HI_test/src/01_SimpleHist/styleTH1D.C"); 

  //----- open the root file ------
  // 1.open reference file (created from pilot run 202792)

  TFile *refFile = new TFile("/afs/cern.ch/user/k/kyolee/private/cms538HI_test/src/01_SimpleHist/stableBeam/pilotRun/TH1D/TH1D_run202792.root","READ");
  // 2.open run root file 
  Int_t nRun = 1; //num of run root files
  TFile *openFile[nRun];
	openFile[0] = TFile::Open("root://eoscms//eos/cms/store/caf/user/velicanu/PA2013_merged/pPb_hiForest2_r210353_notracker_v1.root");
	openFile[0] = TFile::Open("root://eoscms//eos/cms/store/caf/user/velicanu/PA2013_merged/PA2013_HiForest_Express_r210498_stablebeams.root");

  //draw histograms
	string histName[] ={"Glb_pt","Glb_eta","Glb_phi","Glb_dxy","Glb_dz","Glb_nValMuHits", "Glb_nValTrkHits", "Glb_nTrkFound", "Glb_pixLayerWMeas", "Glb_glbChi2_ndof", "Glb_trkChi2_ndof", "Di_vProb", "Sta_pt", "Sta_eta", "Sta_phi", "Sta_dxy", "Sta_dz"};
	string histTitle[] = {"Glb_pt;Global muon p_{T};Counts (normalized by # of entries)", "Glb_eta;Global muon #eta;Counts (normalized by # of entries)", "Glb_phi;Global muon #phi;Counts (normalized by # of entries)", "Glb_dxy;Global muon dxy;Counts (normalized by # of entries)", "Glb_dz;Global muon dz;Counts (normalized by # of entries)", "Glb_nValMuHits;# of valid muon hits;Counts (normalized by # of entries)", "Glb_nValTrkHits;# of valid tracker hits;Counts (normalized by # of entries)", "Glb_nTrkFound;# of tracks found;Counts (normalized by # of entries)", "Glb_pixLayerWMeas;Pixel layer with measurement;Counts (normalized by # of entries)", "Glb_glbChi2_ndof;Global muon chi2/ndof;Counts (normalized by # of entries)", "Glb_trkChi2_ndof;Tracker muon chi2/ndof;Counts (normalized by # of entries)", "Di_vProb;Dimuon's vertex probability;Counts (normalized by # of entries)", "Sta_pt;Standalone muon p_{T};Counts (normalized by # of entries)", "Sta_eta;Standalone muon #eta;Counts (normalized by # of entries)", "Sta_phi;Standalone muon #phi;Counts (normalized by # of entries)", "Sta_dxy;Standalone muon dxy;Counts (normalized by # of entries)", "Sta_dz;Standalone muon dz;Counts (normalized by # of entries)"}; 
	int nbins[] ={50, 50, 50, 50, 50, 55, 31, 31, 6, 50, 50, 50, 50, 50, 50, 50, 50};
	double xmin[] ={0., -2.5, -3.4, -15.0, -80., 0., 0., 0., 0., 0., 0., 0., 0., -2.5,-3.4, -10., -400. };
	double xmax[] ={20., 2.5, 3.4, 15.0, 80., 50., 31., 31., 6., 5., 3., 1., 50., 2.5, 3.4, 10., 400. };

	const int nHist = sizeof(histName)/sizeof(string);
  cout<< "nHist = " << nHist << endl;

  Int_t RunNum[nRun];
  TTree *tree[nRun];
	//Int_t NumTreeEntries[nRun];
	//Int_t NumEventEntries[nRun];
  TH1D * histRef[nHist];
	TH1D *hist1D[nRun][nHist];
  Int_t histEntries[nRun][nHist];
	Double_t histMin[nHist];
	Double_t histMax[nHist];
	//Int_t LineCol[nRun];
	stringstream hist1Dname[nRun][nHist];

for (Int_t k=0; k<nRun; k++)
{
  tree[k] = (TTree *) openFile[k] -> Get("muonTree/HLTMuTree");
  tree[k] -> SetBranchAddress("Run", &RunNum[k]); //temporary
  //tree[k] -> SetBranchAddress("Event", &Event);
	tree[k] -> GetEntry(0);
	cout << k <<"th RunNum = " << RunNum[k] << endl;

	for (Int_t i=0; i<nHist; i++) {
	  histRef[i] = (TH1D*)refFile-> Get(histName[i].c_str());
		//histRef[i]->SetMarkerSize(1.2); //temporary
		//histRef[i]->SetLineWidth(2.0);
		hist1Dname[k][i] << k << "_" << histName[i].c_str() ;
	  //cout << k <<" : "<< histName[i].c_str()<<" : "<<hist1Dname[k][i].str().c_str() << endl;
		hist1D[k][i] = new TH1D(hist1Dname[k][i].str().c_str(),histTitle[i].c_str(),nbins[i],xmin[i],xmax[i]);
		SetHistStyle(hist1D[k][i],k);
		if(k>=5) { SetHistStyle(hist1D[k][i],k-5); }

	}
}

TLegend *leg = new TLegend(0.69,0.74,0.88,0.88);
//TLegend *leg = new TLegend(0.16,0.64,0.58,0.88);
SetLegendStyle(leg);
//TLegend *leg_do_rap = new TLegend(0.35,0.64,0.8,0.88);
//SetLegendStyle(leg_do_rap);

	leg->AddEntry(histRef[0],"pilotRun","lp");
	for (Int_t k; k<nRun; k++) {
	leg->AddEntry(hist1D[k][0],Form("Run%d",RunNum[nRun-1]),"lp");
  }

  TCanvas c1;
	c1.cd(); 
/*
 for(Int_t k=0; k<nRun; k++)
 {
	 for(Int_t i=0; i<nHist; i++)
	 {
		 hist1D[k][i]->SetLineColor(k+2); 
		 hist1D[k][i]->SetMarkerColor(k+2); 
   }
 }
 */	

  //Glb_pt
  histRef[0]->Draw("pe");
	leg->Draw();
  histMin[0]=histRef[0]->GetMinimum();
  histMax[0]=histRef[0]->GetMaximum();
	if (histRef[0]->GetMinimum() == 0)	{	histRef[0]->SetMinimum(0.001); }
	else { histRef[0]->SetMinimum(histMin[0]*0.01);}
	histRef[0]->SetMaximum(histMax[0]*1);
  gPad->SetLogy(1);
  for(Int_t k=0; k<nRun; k++)
	{
		char temp0_1[531];
		sprintf(temp0_1,"%s>>%s",histName[0].c_str(),hist1Dname[k][0].str().c_str());
		tree[k]->Draw(temp0_1,"Glb_nptl>0","pe same");
	//  leg_do_rap->AddEntry(hist1D[k][0],Form("Run%d",RunNum),"l");
		histEntries[k][0]=hist1D[k][0]->GetEntries();
	  hist1D[k][0]->Scale(1./histEntries[k][0]);
  }
	char temp0_2[531];
	sprintf(temp0_2,"runsTill_%d_%s.pdf",RunNum[nRun-1],histName[0].c_str());
	c1.SaveAs(temp0_2);

//Glb_eta
  histRef[1]->Draw("pe");
	leg->Draw();
  histMin[1]=histRef[1]->GetMinimum();
  histMax[1]=histRef[1]->GetMaximum();
	if (histRef[1]->GetMinimum() == 0)	{	histRef[1]->SetMinimum(0.001); }
	else { histRef[1]->SetMinimum(histMin[1]*0.01) ;}
	histRef[1]->SetMaximum(histMax[1]*1.2);
    gPad->SetLogy(0);
  for(Int_t k=0; k<nRun; k++)
	{
		char temp1_1[531];
		sprintf(temp1_1,"%s>>%s",histName[1].c_str(),hist1Dname[k][1].str().c_str());
		tree[k]->Draw(temp1_1,"Glb_nptl>0","pe same");
		histEntries[k][1]=hist1D[k][1]->GetEntries();
	  hist1D[k][1]->Scale(1./histEntries[k][1]);
  }
	char temp1_2[531];
	sprintf(temp1_2,"runsTill_%d_%s.pdf",RunNum[nRun-1],histName[1].c_str());
	c1.SaveAs(temp1_2);

//Glb_phi
  histRef[2]->Draw("pe");
	leg->Draw();
  histMin[2]=histRef[2]->GetMinimum();
  histMax[2]=histRef[2]->GetMaximum();
	if (histRef[2]->GetMinimum() == 0)	{	histRef[2]->SetMinimum(0.001); }
	else { histRef[2]->SetMinimum(histMin[2]*0.01) ;}
	histRef[2]->SetMaximum(histMax[2]*1.2);
    gPad->SetLogy(0);
  for(Int_t k=0; k<nRun; k++)
	{
		char temp2_1[531];
		sprintf(temp2_1,"%s>>%s",histName[2].c_str(),hist1Dname[k][2].str().c_str());
		tree[k]->Draw(temp2_1,"Glb_nptl>0","pe same");
		histEntries[k][2]=hist1D[k][2]->GetEntries();
	  hist1D[k][2]->Scale(1./histEntries[k][2]);
  }
	char temp2_2[531];
	sprintf(temp2_2,"runsTill_%d_%s.pdf",RunNum[nRun-1],histName[2].c_str());
	c1.SaveAs(temp2_2);

//Glb_dxy
  histRef[3]->Draw("pe");
	leg->Draw();
  histMin[3]=histRef[3]->GetMinimum();
  histMax[3]=histRef[3]->GetMaximum();
	if (histRef[3]->GetMinimum() == 0)	{	histRef[3]->SetMinimum(0.001); }
	else { histRef[3]->SetMinimum(histMin[3]*0.01) ;}
	histRef[3]->SetMaximum(histMax[3]*10);
    gPad->SetLogy(1);
  for(Int_t k=0; k<nRun; k++)
	{
		char temp3_1[531];
		sprintf(temp3_1,"%s>>%s",histName[3].c_str(),hist1Dname[k][3].str().c_str());
		tree[k]->Draw(temp3_1,"Glb_nptl>0","pe same");
		histEntries[k][3]=hist1D[k][3]->GetEntries();
	  hist1D[k][3]->Scale(1./histEntries[k][3]);
  }
	char temp3_2[531];
	sprintf(temp3_2,"runsTill_%d_%s.pdf",RunNum[nRun-1],histName[3].c_str());
	c1.SaveAs(temp3_2);

//Glb_dz
  histRef[4]->Draw("pe");
	leg->Draw();
  histMin[4]=histRef[4]->GetMinimum();
  histMax[4]=histRef[4]->GetMaximum();
	if (histRef[4]->GetMinimum() == 0)	{	histRef[4]->SetMinimum(0.001); }
	else { histRef[4]->SetMinimum(histMin[4]*0.01) ;}
	histRef[4]->SetMaximum(histMax[4]*10);
    gPad->SetLogy(1);
  for(Int_t k=0; k<nRun; k++)
	{
		char temp4_1[531];
		sprintf(temp4_1,"%s>>%s",histName[4].c_str(),hist1Dname[k][4].str().c_str());
		tree[k]->Draw(temp4_1,"Glb_nptl>0","pe same");
		histEntries[k][4]=hist1D[k][4]->GetEntries();
	  hist1D[k][4]->Scale(1./histEntries[k][4]);
  }
	char temp4_2[531];
	sprintf(temp4_2,"runsTill_%d_%s.pdf",RunNum[nRun-1],histName[4].c_str());
	c1.SaveAs(temp4_2);

//Glb_nValMuHits;
  histRef[5]->Draw("pe");
	leg->Draw();
  histMin[5]=histRef[5]->GetMinimum();
  histMax[5]=histRef[5]->GetMaximum();
	if (histRef[5]->GetMinimum() == 0)	{	histRef[5]->SetMinimum(0.001); }
	else { histRef[5]->SetMinimum(histMin[5]*0.01) ;}
	histRef[5]->SetMaximum(histMax[5]*1.2);
    gPad->SetLogy(0);
  for(Int_t k=0; k<nRun; k++)
	{
		char temp5_1[531];
		sprintf(temp5_1,"%s>>%s",histName[5].c_str(),hist1Dname[k][5].str().c_str());
		tree[k]->Draw(temp5_1,"Glb_nptl>0","pe same");
		histEntries[k][5]=hist1D[k][5]->GetEntries();
	  hist1D[k][5]->Scale(1./histEntries[k][5]);
  }
	char temp5_2[531];
	sprintf(temp5_2,"runsTill_%d_%s.pdf",RunNum[nRun-1],histName[5].c_str());
	c1.SaveAs(temp5_2);

//Glb_nValTrkHits;
  histRef[6]->Draw("pe");
	leg->Draw();
  histMin[6]=histRef[6]->GetMinimum();
  histMax[6]=histRef[6]->GetMaximum();
	if (histRef[6]->GetMinimum() == 0)	{	histRef[6]->SetMinimum(0.001); }
	else { histRef[6]->SetMinimum(histMin[6]*0.01) ;}
	histRef[6]->SetMaximum(histMax[6]*1.2);
    gPad->SetLogy(0);
  for(Int_t k=0; k<nRun; k++)
	{
		char temp6_1[531];
		sprintf(temp6_1,"%s>>%s",histName[6].c_str(),hist1Dname[k][6].str().c_str());
		tree[k]->Draw(temp6_1,"Glb_nptl>0","pe same");
		histEntries[k][6]=hist1D[k][6]->GetEntries();
	  hist1D[k][6]->Scale(1./histEntries[k][6]);
  }
	char temp6_2[531];
	sprintf(temp6_2,"runsTill_%d_%s.pdf",RunNum[nRun-1],histName[6].c_str());
	c1.SaveAs(temp6_2);

//Glb_nTrkFound
  histRef[7]->Draw("pe");
	leg->Draw();
  histMin[7]=histRef[7]->GetMinimum();
  histMax[7]=histRef[7]->GetMaximum();
	if (histRef[7]->GetMinimum() == 0)	{	histRef[7]->SetMinimum(0.001); }
	else { histRef[7]->SetMinimum(histMin[7]*0.01) ;}
	histRef[7]->SetMaximum(histMax[7]*1.2);
    gPad->SetLogy(0);
  for(Int_t k=0; k<nRun; k++)
	{
		char temp7_1[531];
		sprintf(temp7_1,"%s>>%s",histName[7].c_str(),hist1Dname[k][7].str().c_str());
		tree[k]->Draw(temp7_1,"Glb_nptl>0","pe same");
		histEntries[k][7]=hist1D[k][7]->GetEntries();
	  hist1D[k][7]->Scale(1./histEntries[k][7]);
  }
	char temp7_2[531];
	sprintf(temp7_2,"runsTill_%d_%s.pdf",RunNum[nRun-1],histName[7].c_str());
	c1.SaveAs(temp7_2);

//Glb_pixLayerWMeas;
  histRef[8]->Draw("pe");
	leg->Draw();
  histMin[8]=histRef[8]->GetMinimum();
  histMax[8]=histRef[8]->GetMaximum();
	if (histRef[8]->GetMinimum() == 0)	{	histRef[8]->SetMinimum(0.001); }
	else { histRef[8]->SetMinimum(histMin[8]*0.01) ;}
	histRef[8]->SetMaximum(histMax[8]*1.2);
    gPad->SetLogy(0);
  for(Int_t k=0; k<nRun; k++)
	{
		char temp8_1[531];
		sprintf(temp8_1,"%s>>%s",histName[8].c_str(),hist1Dname[k][8].str().c_str());
		tree[k]->Draw(temp8_1,"Glb_nptl>0","pe same");
		histEntries[k][8]=hist1D[k][8]->GetEntries();
	  hist1D[k][8]->Scale(1./histEntries[k][8]);
  }
	char temp8_2[531];
	sprintf(temp8_2,"runsTill_%d_%s.pdf",RunNum[nRun-1],histName[8].c_str());
	c1.SaveAs(temp8_2);

//Glb_glbChi2_ndof
  histRef[9]->Draw("pe");
	leg->Draw();
  histMin[9]=histRef[9]->GetMinimum();
  histMax[9]=histRef[9]->GetMaximum();
	if (histRef[9]->GetMinimum() == 0)	{	histRef[9]->SetMinimum(0.001); }
	else { histRef[9]->SetMinimum(histMin[9]*0.01) ;}
	histRef[9]->SetMaximum(histMax[9]*1.2);
    gPad->SetLogy(0);
  for(Int_t k=0; k<nRun; k++)
	{
		char temp9_1[531];
		sprintf(temp9_1,"%s>>%s",histName[9].c_str(),hist1Dname[k][9].str().c_str());
		tree[k]->Draw(temp9_1,"Glb_nptl>0","pe same");
		histEntries[k][9]=hist1D[k][9]->GetEntries();
	  hist1D[k][9]->Scale(1./histEntries[k][9]);
  }
	char temp9_2[531];
	sprintf(temp9_2,"runsTill_%d_%s.pdf",RunNum[nRun-1],histName[9].c_str());
	c1.SaveAs(temp9_2);

//Glb_trkChi2_ndof
  histRef[10]->Draw("pe");
	leg->Draw();
  histMin[10]=histRef[10]->GetMinimum();
  histMax[10]=histRef[10]->GetMaximum();
	if (histRef[10]->GetMinimum() == 0)	{	histRef[10]->SetMinimum(0.001); }
	else { histRef[10]->SetMinimum(histMin[10]*0.01) ;}
	histRef[10]->SetMaximum(histMax[10]*1.2);
    gPad->SetLogy(0);
  for(Int_t k=0; k<nRun; k++)
	{
		char temp10_1[531];
		sprintf(temp10_1,"%s>>%s",histName[10].c_str(),hist1Dname[k][10].str().c_str());
		tree[k]->Draw(temp10_1,"Glb_nptl>0","pe same");
		histEntries[k][10]=hist1D[k][10]->GetEntries();
	  hist1D[k][10]->Scale(1./histEntries[k][10]);
  }
	char temp10_2[531];
	sprintf(temp10_2,"runsTill_%d_%s.pdf",RunNum[nRun-1],histName[10].c_str());
	c1.SaveAs(temp10_2);

//Di_vProb
  histRef[11]->Draw("pe");
	leg->Draw();
  histMin[11]=histRef[11]->GetMinimum();
  histMax[11]=histRef[11]->GetMaximum();
	if (histRef[11]->GetMinimum() == 0)	{	histRef[11]->SetMinimum(0.001); }
	else { histRef[11]->SetMinimum(histMin[11]*0.01) ;}
//	histRef[11]->SetMaximum(histMax[11]*10);
	histRef[11]->SetMaximum();
    gPad->SetLogy(1);
  for(Int_t k=0; k<nRun; k++)
	{
		char temp11_1[531];
		sprintf(temp11_1,"%s>>%s",histName[11].c_str(),hist1Dname[k][11].str().c_str());
		tree[k]->Draw(temp11_1,"Di_npair>0","pe same");
		histEntries[k][11]=hist1D[k][11]->GetEntries();
	  hist1D[k][11]->Scale(1./histEntries[k][11]);
  }
	char temp11_2[531];
	sprintf(temp11_2,"runsTill_%d_%s.pdf",RunNum[nRun-1],histName[11].c_str());
	c1.SaveAs(temp11_2);

//Sta_pt
  histRef[12]->Draw("pe");
	leg->Draw();
  histMin[12]=histRef[12]->GetMinimum();
  histMax[12]=histRef[12]->GetMaximum();
	if (histRef[12]->GetMinimum() == 0)	{	histRef[12]->SetMinimum(0.001); }
	else { histRef[12]->SetMinimum(histMin[12]*0.01) ;}
	histRef[12]->SetMaximum(histMax[12]*10);
    gPad->SetLogy(1);
  for(Int_t k=0; k<nRun; k++)
	{
		char temp12_1[531];
		sprintf(temp12_1,"%s>>%s",histName[12].c_str(),hist1Dname[k][12].str().c_str());
		tree[k]->Draw(temp12_1,"Sta_nptl>0","pe same");
		histEntries[k][12]=hist1D[k][12]->GetEntries();
	  hist1D[k][12]->Scale(1./histEntries[k][12]);
  }
	char temp12_2[531];
	sprintf(temp12_2,"runsTill_%d_%s.pdf",RunNum[nRun-1],histName[12].c_str());
	c1.SaveAs(temp12_2);

 //Sta_eta
  histRef[13]->Draw("pe");
	leg->Draw();
  histMin[13]=histRef[13]->GetMinimum();
  histMax[13]=histRef[13]->GetMaximum();
	if (histRef[13]->GetMinimum() == 0)	{	histRef[13]->SetMinimum(0.001); }
	else { histRef[13]->SetMinimum(histMin[13]*0.01) ;}
	histRef[13]->SetMaximum(histMax[13]*1.2);
  gPad->SetLogy(0);
  for(Int_t k=0; k<nRun; k++)
	{
		char temp13_1[531];
		sprintf(temp13_1,"%s>>%s",histName[13].c_str(),hist1Dname[k][13].str().c_str());
		tree[k]->Draw(temp13_1,"","pe same");
		histEntries[k][13]=hist1D[k][13]->GetEntries();
	  hist1D[k][13]->Scale(1./histEntries[k][13]);
  }
	char temp13_2[531];
	sprintf(temp13_2,"runsTill_%d_%s.pdf",RunNum[nRun-1],histName[13].c_str());
	c1.SaveAs(temp13_2);

  //Sta_phi
  histRef[14]->Draw("pe");
	leg->Draw();
  histMin[14]=histRef[14]->GetMinimum();
  histMax[14]=histRef[14]->GetMaximum();
	if (histRef[14]->GetMinimum() == 0)	{	histRef[14]->SetMinimum(0.001); }
	else { histRef[14]->SetMinimum(histMin[14]*0.01) ;}
	histRef[14]->SetMaximum(histMax[14]*1.2);
  gPad->SetLogy(0);
  for(Int_t k=0; k<nRun; k++)
	{
		char temp14_1[531];
		sprintf(temp14_1,"%s>>%s",histName[14].c_str(),hist1Dname[k][14].str().c_str());
		tree[k]->Draw(temp14_1,"","pe same");
		histEntries[k][14]=hist1D[k][14]->GetEntries();
	  hist1D[k][14]->Scale(1./histEntries[k][14]);
  }
	char temp14_2[531];
	sprintf(temp14_2,"runsTill_%d_%s.pdf",RunNum[nRun-1],histName[14].c_str());
	c1.SaveAs(temp14_2);

 //Sta_dxy
  histRef[15]->Draw("pe");
	leg->Draw();
  histMin[15]=histRef[15]->GetMinimum();
  histMax[15]=histRef[15]->GetMaximum();
	if (histRef[15]->GetMinimum() == 0)	{	histRef[15]->SetMinimum(0.001); }
	else { histRef[15]->SetMinimum(histMin[15]*0.01) ;}
	histRef[15]->SetMaximum(histMax[15]*1.2);
  gPad->SetLogy(1);
  for(Int_t k=0; k<nRun; k++)
	{
		char temp15_1[531];
		sprintf(temp15_1,"%s>>%s",histName[15].c_str(),hist1Dname[k][15].str().c_str());
		tree[k]->Draw(temp15_1,"","pe same");
		histEntries[k][15]=hist1D[k][15]->GetEntries();
	  hist1D[k][15]->Scale(1./histEntries[k][15]);
  }
	char temp15_2[531];
	sprintf(temp15_2,"runsTill_%d_%s.pdf",RunNum[nRun-1],histName[15].c_str());
	c1.SaveAs(temp15_2);

  //Sta_dz
  histRef[16]->Draw("pe");
	leg->Draw();
  histMin[16]=histRef[16]->GetMinimum();
  histMax[16]=histRef[16]->GetMaximum();
	if (histRef[16]->GetMinimum() == 0)	{	histRef[16]->SetMinimum(0.001); }
	else { histRef[16]->SetMinimum(histMin[16]*0.01) ;}
	histRef[16]->SetMaximum(histMax[16]*1.2);
  gPad->SetLogy(1);
  for(Int_t k=0; k<nRun; k++)
	{
		char temp16_1[531];
		sprintf(temp16_1,"%s>>%s",histName[16].c_str(),hist1Dname[k][16].str().c_str());
		tree[k]->Draw(temp16_1,"","pe same");
		histEntries[k][16]=hist1D[k][16]->GetEntries();
	  hist1D[k][16]->Scale(1./histEntries[k][16]);
  }
	char temp16_2[500];
	sprintf(temp16_2,"runsTill_%d_%s.pdf",RunNum[nRun-1],histName[16].c_str());
	c1.SaveAs(temp16_2);

	return;

}

void SetHistStyle(TH1* h, int i) {
	//  int colorArr[6] = {kBlack, kBlue, kRed, kGreen+2, kOrange, kMagenta+2};
	//  int colorArr[] = {kGray+2, kBlack, kRed, kRed+2, kOrange+1, kOrange+8, kGreen+2, kGreen+4, kAzure+1, kAzure+3, kViolet+5, kViolet+3, kMagenta, kMagenta+2};
int colorArr[] = {kRed+1, kOrange+1, kOrange-8, kGreen+2, kAzure+1, kBlue+2, kViolet+5, kViolet-4, kMagenta, kMagenta+2};
int markerFullArr[6] = {kFullCircle, kFullSquare, kFullTriangleUp, kFullTriangleDown, kFullStar, kFullDiamond};
int markerOpenArr[6] = {kOpenCircle, kOpenSquare, kOpenTriangleUp, kOpenTriangleDown, kOpenStar, kOpenDiamond};
				  
h->SetLineColor(colorArr[i]);
//h->SetLineWidth(2.4);
h->SetMarkerColor(colorArr[i]);
//h->SetMarkerStyle(kOpenCircle);
  if (i < 10)  h->SetMarkerStyle(markerFullArr[i]);
  else h->SetMarkerStyle(markerOpenArr[i-10]);
//h->SetMarkerSize(1.5);

return;
}

void SetLegendStyle(TLegend* l) {
 	l->SetFillColor(0);
	l->SetFillStyle(4100);
//	l->SetFillStyle(4000); //transparent
//	l->SetBorderSize(1);
	l->SetBorderSize(0);
	l->SetMargin(0.1);
}

