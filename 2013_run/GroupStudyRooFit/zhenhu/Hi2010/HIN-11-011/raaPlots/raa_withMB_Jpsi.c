{
	int bin = 7;
	int bin1 = 7;
	float cent[bin]={22.1, 86.3, 130.0, 187.1, 261.4, 329.4, 381.3};
	float cent1[8]={14.2, 53.5, 86.3, 130.0, 187.1, 261.4, 329.4, 381.3};
	float cent2[6]={22.1, 86.3, 130.0, 187.1, 261.4, 355.4};
	float centErr[bin]={6,6,6,6,6,6,6};
	float centnoErr[bin]={0,0,0,0};

	//pt > 4 Raa
	float ratio1S[bin1]={/*1.047,0.981,*/1.005,0.590,0.681,0.614,0.484,0.432,0.411};
	float ratio1SstatErr[bin1]={/*0.202,0.166,*/0.121,0.096,0.069,0.053,0.040,0.048,0.043};
	float ratio1SsystErr[bin1]={/*0.186,0.167,*/0.176,0.086,0.085,0.075,0.049,0.046,0.048};
	float ratio2S[bin]={0.300,0.251,0.237,0.260,0.068,0.044,0.111};
	float ratio2SstatErr[bin]={0.157,0.138,0.098,0.079,0.053,0.060,0.061};
	float ratio2SsystErr[bin]={0.069,0.050,0.039,0.043,0.022,0.019,0.020};

	float ratioJpsi[bin]={0.610, 0.661, 0.506, 0.372, 0.220, 0.202};
	float ratioJpsistatErr[bin]={0.122, 0.131, 0.085, 0.058, 0.037, 0.030};
	float ratioJpsisystErr[bin]={0.097, 0.077, 0.048, 0.029, 0.016, 0.014};

	float tot1SErr[bin];
	float tot2SErr[bin];
	for (int i=0; i<bin1; i++){
		tot1SErr[i] = sqrt(ratio1SstatErr[i]*ratio1SstatErr[i]+ratio1SsystErr[i]*ratio1SsystErr[i]);
		cout<<i<<" "<<tot1SErr[i]<<endl;
	}
	for (int i=0; i<bin; i++){
		tot2SErr[i] = sqrt(ratio2SstatErr[i]*ratio2SstatErr[i]+ratio2SsystErr[i]*ratio2SsystErr[i]);
		cout<<i<<" "<<tot2SErr[i]<<endl;
	}

	TCanvas *c1 = new TCanvas("c1","c1");

	c1->cd();
	TPad *p1 = new TPad("p1","p1",0.0,0.0,0.9,1.0);
	p1->SetBottomMargin(0.12);
	p1->SetTopMargin(0.03);
	p1->SetRightMargin(0.03);
	p1->SetLeftMargin(0.11);
	p1->Draw();
	p1->cd();

	TF1 *f4 = new TF1("f4","1",0,400);
	f4->SetLineWidth(1);
	f4->GetXaxis()->SetTitle("N_{part}");
	f4->GetYaxis()->SetTitle("R_{AA}");
	f4->GetYaxis()->SetTitleOffset(1.0);
	f4->GetYaxis()->SetRangeUser(0,1.5);
	f4->GetXaxis()->CenterTitle(kTRUE);
	f4->Draw();

	TGraphErrors *g = new TGraphErrors(bin1,cent,ratio1S,centnoErr,ratio1SstatErr);
	g->SetMarkerColor(kRed+2);
	g->SetMarkerStyle(21);
	g->SetMarkerSize(1.1);

	TGraphErrors *g1Ssyst = new TGraphErrors(bin1,cent,ratio1S,centnoErr,ratio1SsystErr);
	g1Ssyst->SetLineColor(kRed-9);
	g1Ssyst->SetLineWidth(18);
	g1Ssyst->SetMarkerSize(0);
	g1Ssyst->Draw("e");

	g->Draw("pe");

	TGraphErrors *g2 = new TGraphErrors(bin,cent,ratio2S,centnoErr,ratio2SstatErr);
	g2->SetMarkerColor(kGreen+2);
	g2->SetMarkerStyle(20);
	g2->SetMarkerSize(1.1);

	TGraphErrors *g2Ssyst = new TGraphErrors(bin,cent,ratio2S,centErr,ratio2SsystErr);
	g2Ssyst->SetLineColor(kGreen+2);
	g2Ssyst->SetFillStyle(0);
	g2Ssyst->SetLineWidth(2);
	g2Ssyst->SetMarkerSize(0);
	g2Ssyst->Draw("2");

	g2->Draw("pe");


	TGraphErrors *Jpsi = new TGraphErrors(6,cent2,ratioJpsi,centnoErr,ratioJpsistatErr);
	Jpsi->SetMarkerColor(kBlue+2);
	Jpsi->SetMarkerStyle(33);
	Jpsi->SetMarkerSize(1.5);

	TGraphErrors *Jpsisyst = new TGraphErrors(6,cent2,ratioJpsi,centErr,ratioJpsisystErr);
	Jpsisyst->SetLineColor(kBlue+2);
	Jpsisyst->SetFillColor(kBlue-7);
	Jpsisyst->SetFillStyle(3244);
	Jpsisyst->SetLineWidth(1);
	Jpsisyst->SetMarkerSize(0);

	Jpsisyst->Draw("2");

	TGraphErrors *Jpsisyst_ = new TGraphErrors(6,cent2,ratioJpsi,centErr,ratioJpsisystErr);
	Jpsisyst_->SetLineColor(kBlue+2);
	Jpsisyst_->SetFillColor(kBlue-7);
	Jpsisyst_->SetFillStyle(0);
	Jpsisyst_->SetLineWidth(1);
	Jpsisyst_->SetMarkerSize(0);
	Jpsisyst_->Draw("2");

	Jpsi->Draw("pe");


	float ppy[1]={1};
	float ppx[1]={377};
	float ppxEr[1]={0};
	float ppyErSystematic=sqrt(pow(0.06,2)+pow(0.023,2));
	cout<<"ppyErSystematic"<<ppyErSystematic<<endl;
	float ppyErSyst[1]={ppyErSystematic};
	float ppyErtotal=sqrt(pow(ppyErSystematic,2)+pow(0.12,2));
	float ppyErtol[1]={0};
	TBox *lumiY1S = new TBox(370.0,0.864,385.0,1.136);
	lumiY1S->SetFillColor(kRed-9);
	lumiY1S->Draw("2");
	TGraphErrors *gpp = new TGraphErrors(1,ppx,ppy,ppxEr,ppyErSyst);
	gpp->SetMarkerSize(0);
	gpp->SetLineColor(kGray);
	gpp->SetLineWidth(10);
	//gpp->Draw("e");
	TGraphErrors *gpptol = new TGraphErrors(1,ppx,ppy,ppxEr,ppyErtol);
	gpptol->SetLineWidth(0);
	gpptol->SetLineColor(kGray);
	gpptol->SetMarkerColor(kRed);
	gpptol->SetMarkerStyle(21);
	gpptol->SetMarkerSize(1.1);
	//gpptol->Draw("p");

	float Y2Sppx[1]={392};
	float Y2SppyErSystematic=sqrt(pow(0.06,2)+pow(0.033,2));
	float Y2SppyErSyst[1]={Y2SppyErSystematic};
	float Y2SppyErtotal=sqrt(pow(Y2SppyErSystematic,2)+pow(0.202,2));
	float Y2SppyErtol[1]={0};
	TBox *lumiY2S = new TBox(385.0,0.787,399.0,1.213);
	lumiY2S->SetFillColor(kGreen-7);
	lumiY2S->SetFillStyle(0);
	lumiY2S->SetLineWidth(2);
	lumiY2S->SetLineColor(kGreen+2);
	lumiY2S->Draw("2");
	TGraphErrors *Y2Sgpp = new TGraphErrors(1,Y2Sppx,ppy,ppxEr,Y2SppyErSyst);
	Y2Sgpp->SetMarkerSize(0);
	Y2Sgpp->SetLineColor(kGray);
	Y2Sgpp->SetLineWidth(10);
	//Y2Sgpp->Draw("e");
	TGraphErrors *Y2Sgpptol = new TGraphErrors(1,Y2Sppx,ppy,ppxEr,Y2SppyErtol);
	Y2Sgpptol->SetLineWidth(0);
	Y2Sgpptol->SetLineColor(kGray);
	Y2Sgpptol->SetMarkerColor(kGreen+2);
	Y2Sgpptol->SetMarkerStyle(20);
	Y2Sgpptol->SetMarkerSize(1.1);
	//Y2Sgpptol->Draw("p");

	TBox *lumiJpsi = new TBox(355.0,0.94,370.0,1.06);
	lumiJpsi->SetFillColor(kBlue-7);
	lumiJpsi->SetFillStyle(3244);
	lumiJpsi->SetLineWidth(2);
	lumiJpsi->SetLineColor(kBlue+2);
	lumiJpsi->Draw("2");

	TBox *lumiJpsi_ = new TBox(355.0,0.94,370.0,1.06);
	lumiJpsi_->SetFillStyle(0);
	lumiJpsi_->SetLineWidth(1);
	lumiJpsi_->SetLineColor(kBlue+2);
	lumiJpsi_->Draw("2");

	f4->Draw("same");
	gPad->RedrawAxis();

	TLatex *l1 = new TLatex(50,1.37,"CMS PbPb  #sqrt{s_{NN}} = 2.76 TeV");
	l1->SetTextFont(42);
	l1->SetTextSize(0.05);
	//TLatex *l1 = new TLatex(25,1.37,"CMS Preliminary, PbPb #sqrt{s_{NN}} = 2.76 TeV");
	//l1->SetTextSize(0.045);
	l1->Draw();

	//TLatex *lumi = new TLatex(240,1.24,"L_{int}^{PbPb} = 150 #mub^{-1}");
	//lumi->Draw();
	//lumi->DrawLatex(240,1.12,"L_{int}^{pp} = 230 nb^{-1}");

	//TLatex *ly = new TLatex(240,1.15,"|y| < 2.4");
	TLatex *ly = new TLatex(240,0.9,"|y| < 2.4");
	//ly->Draw();

	//	TLatex *mupt = new TLatex(240,1.05,"p_{T}^{#mu} > 4 GeV/c");
	//	mupt->Draw();

	TLatex *centrality = new TLatex(360,0.55,"0-5%");
	centrality->SetTextSize(0.03);
	centrality->Draw();
	centrality->DrawLatex(310,0.55,"5-10%");
	centrality->DrawLatex(240,0.6,"10-20%");
	centrality->DrawLatex(170,0.75,"20-30%");
	centrality->DrawLatex(110,0.85,"30-40%");
	centrality->DrawLatex(65,0.8,"40-50%");
	centrality->DrawLatex(10,0.75,"50-100%");
	centrality->DrawLatex(335,0.26,"0-10%");

	//	TLegend *legend = new TLegend(0.25,0.69,0.52,0.87);
	TLegend *legend = new TLegend(0.2,0.69,0.5,0.87);
	legend->SetFillStyle(0);
	legend->SetFillColor(0);
	legend->SetMargin(0.2);
	legend->SetBorderSize(0);
	legend->SetTextSize(0.035);
	legend->SetTextFont(42);
	//	legend->AddEntry(g,"#varUpsilon(1S), stat. unc.","lpe");
	//	legend->AddEntry(g1Ssyst, "#varUpsilon(1S), syst. unc.","l");
	//	legend->AddEntry(g2, "#varUpsilon(2S), stat. unc.","lpe");
	//	legend->AddEntry((TObject*)0, "#varUpsilon(2S), syst. unc.","");
	legend->AddEntry(Jpsi, "prompt J/#psi","P");
	legend->AddEntry(g,"#varUpsilon(1S)","P");
	legend->AddEntry(g2, "#varUpsilon(2S)","P");
	legend->AddEntry((TObject*)0, "#varUpsilon(3S), 95\% upper limit","");
	legend->Draw();

	TLine *g3Slegend = new TLine(51,1.09,61,1.09);
	g3Slegend->SetLineWidth(2);
	g3Slegend->Draw();
	TArrow *g3SlegendArrow = new TArrow(56,1.09,56,1.02,0.015,"|>");
	g3SlegendArrow->SetLineWidth(2);
	g3SlegendArrow->Draw();



	c1->cd();
	TPad *p2 = new TPad("p2","p2",0.9,0.0,1.0,1.0);
	p2->SetBottomMargin(0.12);
	p2->SetTopMargin(0.03);
	p2->SetRightMargin(0.2);
	p2->SetLeftMargin(0.01);
	p2->SetTickx(0);
	p2->SetTicky(0);
	p2->Draw();
	p2->cd();

	//MB

	//pt > 4
	float centMB[1]={0.5};
	float centMB2S[1]={0.3};
	float centMB3S[1]={0.7};
	float cent_limit_err[1]={0.1};
	float raaMB1S[1]={0.564};
	float raaMB1SstatErr[1]={0.077};
	float raaMB1SsystErr[1]={0.071};
	float raaMB2S[1]={0.120};
	float raaMB2SstatErr[1]={0.038};
	float raaMB2SsystErr[1]={0.020};
	float raaMB3S[1]={0.033};
	float raaMB3SstatErr[1]={0.035};//{0.035};
	float raaMB3SsystErr[1]={0.006};
	float raaMB3Slimit[1]={0.1};
	float raaMBJpsi[1]={0.304};
	float raaMBJpsistatErr[1]={0.025};
	float raaMBJpsisystErr[1]={0.022};

	float raaMB1StotErr[0]=sqrt(pow(raaMB1SstatErr[0],2)+pow(raaMB1SsystErr[0],2));
	float raaMB2StotErr[0]=sqrt(pow(raaMB2SstatErr[0],2)+pow(raaMB2SsystErr[0],2));
	float raaMB3StotErr[0]=sqrt(pow(raaMB3SstatErr[0],2)+pow(raaMB3SsystErr[0],2));


	TF1 *f5 = new TF1("f4","1",0,1);
	f5->GetXaxis()->SetNdivisions(2);
	f5->SetLineWidth(1);
	f5->GetXaxis()->SetTitle("");
	f5->GetXaxis()->SetLabelColor(kWhite);
	f5->GetXaxis()->SetRangeUser(0,1);
	f5->GetYaxis()->SetTitle("R_{AA}");
	f5->GetYaxis()->SetTitleOffset(1.0);
	f5->GetYaxis()->SetRangeUser(0,1.5);
	f5->GetXaxis()->CenterTitle(kTRUE);
	f5->Draw();

	TGraphErrors *g1SMB = new TGraphErrors(1,centMB,raaMB1S,centnoErr,raaMB1SsystErr);
	TGraphErrors *g1SMBtot = new TGraphErrors(1,centMB,raaMB1S,centnoErr,raaMB1SstatErr);

	g1SMBtot->SetMarkerStyle(21);
	g1SMBtot->SetMarkerColor(kRed+2);
	g1SMBtot->SetMarkerSize(1.1);
	g1SMB->SetLineColor(kRed-9);
	g1SMB->SetLineWidth(18);
	g1SMB->SetMarkerSize(0);
	g1SMB->Draw("e");
	g1SMBtot->Draw("pe");

	float centMBErr[1]={0.15};
	TGraphErrors *g2SMB = new TGraphErrors(1,centMB2S,raaMB2S,centMBErr,raaMB2SsystErr);
	TGraphErrors *g2SMBtot = new TGraphErrors(1,centMB2S,raaMB2S,centnoErr,raaMB2SstatErr);
	g2SMBtot->SetMarkerStyle(20);
	g2SMBtot->SetMarkerColor(kGreen+2);
	g2SMBtot->SetMarkerSize(1.1);
	g2SMB->SetLineColor(kGreen+2);
	g2SMB->SetFillStyle(0);
	g2SMB->SetLineWidth(2);
	g2SMB->SetMarkerSize(0);
	g2SMB->Draw("2");
	g2SMBtot->Draw("pe");

	TGraphErrors *gJpsiMB = new TGraphErrors(1,centMB,raaMBJpsi,centMBErr,raaMBJpsisystErr);
	TGraphErrors *gJpsiMBtot = new TGraphErrors(1,centMB,raaMBJpsi,centnoErr,raaMBJpsistatErr);
	gJpsiMBtot->SetMarkerStyle(33);
	gJpsiMBtot->SetMarkerColor(kBlue+2);
	gJpsiMBtot->SetMarkerSize(1.5);
	gJpsiMB->SetFillStyle(3244);
	gJpsiMB->SetFillColor(kBlue-7);
	gJpsiMB->SetLineWidth(18);
	gJpsiMB->SetMarkerSize(0);
	gJpsiMB->Draw("2");

	TGraphErrors *gJpsiMB_ = new TGraphErrors(1,centMB,raaMBJpsi,centMBErr,raaMBJpsisystErr);
	gJpsiMB_->SetFillStyle(0);
	gJpsiMB_->SetLineColor(kBlue+1);
	gJpsiMB_->SetLineWidth(1);
	gJpsiMB_->SetMarkerSize(0);
	gJpsiMB_->Draw("2");

	gJpsiMBtot->Draw("pe");


	TGraphErrors *g3SMB = new TGraphErrors(1,centMB3S,raaMB3S,centnoErr,raaMB3SsystErr);
	TGraphErrors *g3SMBtot = new TGraphErrors(1,centMB3S,raaMB3S,centnoErr,raaMB3SstatErr);
	g3SMBtot->SetMarkerStyle(33);
	g3SMBtot->SetMarkerColor(kBlue+2);
	g3SMBtot->SetMarkerSize(1.8);
	TGraphErrors *glimits = new TGraphErrors(1,centMB3S,raaMB3Slimit,cent_limit_err,centnoErr);
	glimits->SetMarkerSize(0);
	glimits->SetLineWidth(2);
	glimits->Draw("D");
	TArrow *g3SMBlimit = new TArrow(centMB3S[0],raaMB3Slimit[0],centMB3S[0],0,0.015,"|>");
	g3SMBlimit->SetLineWidth(2);
	g3SMBlimit->Draw();

	TLatex *MBcentrality = new TLatex(0.05,0.71,"0-100%");
	MBcentrality->SetTextSize(0.23);
	MBcentrality->Draw();

	p2->Update();
	p1->Update();
	c1->SaveAs("Raa_JpsiY1SY2S_withMB.gif");
	c1->SaveAs("Raa_JpsiY1SY2S_withMB.pdf");
}
