{
	int bin = 7;
	float cent[bin]={22.1, 86.3, 130.0, 187.1, 261.4, 329.4, 381.3};
	float centErr[bin]={};
	float centnoErr[bin]={0,0,0,0,0,0,0};
	//pt > 4 R23
	//float ratio[bin]={0.167,0.511,0.183,0.302,0.061,0.069,0.216};
	//float systErr[bin]={0.044,0.061,0.025,0.035,0.038,0.041,0.027};
	//float statErr[bin]={0.114,0.193,0.099,0.093,/*0.084,0.110,*/0.1358,0.0542,0.114};
	//pt > 4 R2
	float ratio[bin]={0.304,0.420,0.344,0.428,0.138,0.102,0.270};
	float systErr[bin]={0.040,0.048,0.027,0.039,0.041,0.042,0.031};
	float statErr[bin]={0.154,0.220,0.138,0.124,0.108,0.189,0.146};

	float totErr[bin];

	for (int i=0; i<7; i++){
		//ratio[i] = ratio[i]/0.90;//0.66;
		//ratioErr[i] = ratioErr[i]/0.90;///0.66;
		//ratio2[i] = ratio2[i]/0.87;///0.63;
		//ratioErr2[i] = ratioErr2[i]/0.87;///0.63;
		//sytErr[i] = fabs(ratio2[i]-ratio[i]);
		totErr[i] = sqrt(systErr[i]*systErr[i]+statErr[i]*statErr[i]);
	}

	TCanvas *c1 = new TCanvas("c1","c1");
	TGraphErrors *g = new TGraphErrors(7,cent,ratio,centnoErr,systErr);
	//TGraphErrors *g0 = new TGraphErrors(7,cent,ratio,centnoErr,ratioErr);
	TGraphErrors *gtot = new TGraphErrors(7,cent,ratio,centnoErr,statErr);

	g->GetYaxis()->SetRangeUser(0.,1.5);
	g->GetXaxis()->SetRangeUser(0,400);
	//g->GetYaxis()->SetTitle("[#varUpsilon(2S+3S)/#varUpsilon(1S)]_{PbPb} / [#varUpsilon(2S+3S)/#varUpsilon(1S)]_{pp}");
	g->GetYaxis()->SetTitle("[#varUpsilon(2S)/#varUpsilon(1S)]_{PbPb} / [#varUpsilon(2S)/#varUpsilon(1S)]_{pp}");
	g->GetYaxis()->SetTitleSize(0.04);
	g->GetYaxis()->SetTitleOffset(1.3);
	g->GetXaxis()->SetTitle("N_{part}");
	g->GetXaxis()->CenterTitle(kTRUE);
	g->SetMarkerSize(0);
	g->SetLineColor(38);
	g->SetLineWidth(16);
	g->Draw("ap");
	/*
	   g0->GetYaxis()->SetRangeUser(-0.2,1.2);
	   g0->GetXaxis()->SetRangeUser(0,500);
	//g0->GetYaxis()->SetTitle("[#Upsilon(2S+3S)/#Upsilon(1S)]_{PbPb} / [#Upsilon(2S+3S)/#Upsilon(1S)]_{pp}");
	g0->GetYaxis()->SetTitle("[#Upsilon(2S+3S)/#Upsilon(1S)]_{PbPb}");
	//g0->GetYaxis()->SetTitle("[#Upsilon(2S)/#Upsilon(1S)]_{PbPb}");
	g0->GetYaxis()->SetTitleSize(0.05);
	g0->GetYaxis()->SetTitleOffset(1);
	g0->GetXaxis()->SetTitle("Centrality %");
	g0->GetXaxis()->CenterTitle(kTRUE);
	g0->SetMarkerColor(kBlue);
	g0->SetMarkerStyle(20);
	g0->SetMarkerSize(1.5);
	g0->SetLineColor(kBlue);
	g0->SetLineWidth(2);
	//g0->Draw("ap");
	//g->Draw("psame");
	 */
	gtot->GetYaxis()->SetRangeUser(0.,1.5);
	gtot->GetXaxis()->SetRangeUser(0,400);
	gtot->GetYaxis()->SetTitle("[#Upsilon(2S+3S)/#Upsilon(1S)]_{PbPb} / [#Upsilon(2S+3S)/#Upsilon(1S)]_{pp}");
	//gtot->GetYaxis()->SetTitle("[#Upsilon(2S)/#Upsilon(1S)]_{PbPb} / [#Upsilon(2S)/#Upsilon(1S)]_{pp}");    
	gtot->GetYaxis()->SetTitleSize(0.04);
	gtot->GetYaxis()->SetTitleOffset(1.3);
	gtot->GetXaxis()->SetTitle("N_{part}");
	gtot->GetXaxis()->CenterTitle(kTRUE);
	gtot->SetMarkerSize(1.1);
	gtot->Draw("p");

	//MB
	/*
	//chi23,pt4
	float centMB[1]={113.95};
	float chi23MB[1]={0.176};
	float chi23statErr[1]={0.043};
	float chi23systErr[1]={0.014};
	float chi23totErr[1];
	 */
	/*
	//chi2,pt4
	float centMB[2]={64.2184,308.3853};//[1]={113.95};
	float chi23MB[2]={0.364,0.184};//[1]={0.254};
	float chi23statErr[2]={0.076,0.078};//[1]={0.054};
	float chi23systErr[2]={0,0};//[1]={0.015};
	float chi23totErr[2];//[1];

	chi23totErr[0]=sqrt(pow(chi23statErr[0],2)+pow(chi23systErr[0],2));
	chi23totErr[1]=sqrt(pow(chi23statErr[1],2)+pow(chi23systErr[1],2));


	TGraphErrors *gMB = new TGraphErrors(2,centMB,chi23MB,centnoErr,chi23systErr);
	TGraphErrors *gMBtot = new TGraphErrors(2,centMB,chi23MB,centnoErr,chi23totErr);
	gMBtot->SetMarkerStyle(24);
	gMBtot->Draw("pe");
	gMB->SetLineColor(38);
	gMB->SetLineWidth(6);
	gMB->Draw("e");
	 */
	float ppy[1]={1};
	float ppx[1]={394};
	float ppxEr[1]={0};

	//chi23
	//float ppy_err = sqrt(pow(0.17,2)+pow(0.023,2));
	//chi2
	float ppy_err = sqrt(pow(0.12,2)+pow(0.012,2));

	float ppyEr[1]={ppy_err};

	//TGraphErrors *gpp = new TGraphErrors(1,ppx,ppy,ppxEr,ppyEr);
	//gpp->SetMarkerSize(0);
	//gpp->SetLineColor(kGray);
	//gpp->SetLineWidth(18);
	//gpp->Draw("e");
	TBox *lumiY2S = new TBox(385.0,0.8794,400.0,1.1206);
	lumiY2S->SetFillColor(kBlue-7);
	lumiY2S->SetFillStyle(0);
	lumiY2S->SetLineWidth(2);
	lumiY2S->SetLineColor(kBlue+1);
	lumiY2S->Draw("2");

	TLine L1(0,1,400,1);
	L1.SetLineWidth(1);
	L1.Draw();
	gPad->RedrawAxis();

	TLatex *l1 = new TLatex(50,1.37,"CMS PbPb  #sqrt{s_{NN}} = 2.76 TeV");
	l1->SetTextFont(42);
	l1->SetTextSize(0.05);
	//TLatex *l1 = new TLatex(25,1.37,"CMS Preliminary, PbPb #sqrt{s_{NN}} = 2.76 TeV");
	//l1->SetTextSize(0.045);
	l1->Draw();
	TLatex *lumi = new TLatex(240,1.25,"L_{int} = 150 #mub^{-1}");
	lumi->Draw();

	TLatex *ly = new TLatex(240,1.15,"|y| < 2.4");
	ly->Draw();

	TLatex *mupt = new TLatex(240,1.05,"p_{T}^{#mu} > 4 GeV/c");
	mupt->Draw();

	TLatex *centrality = new TLatex(360,0.5,"0-5%");
	centrality->SetTextSize(0.03);
	centrality->Draw();
	centrality->DrawLatex(310,0.4,"5-10%");
	centrality->DrawLatex(240,0.4,"10-20%");
	centrality->DrawLatex(170,0.65,"20-30%");
	centrality->DrawLatex(110,0.57,"30-40%");
	centrality->DrawLatex(65,0.72,"40-50%");
	centrality->DrawLatex(8,0.54,"50-100%");


	TLegend *legend = new TLegend(.22,.6915,.52,.87);
	legend->SetTextSize(0.04);
	legend->AddEntry(gtot,"stat. unc.","lpe");
	legend->AddEntry(g, "syst. unc.","l");
	//legend->AddEntry(gMBtot,"minbias sample","p");
	legend->AddEntry((TObject*)0,"pp unc. ","");
	legend->Draw();

	TBox *legY2S = new TBox(55,1.05,80,1.09);
	legY2S->SetFillColor(kBlue-7);
	legY2S->SetFillStyle(0);
	legY2S->SetLineWidth(2);
	legY2S->SetLineColor(kBlue+1);
	legY2S->Draw("2");

	c1->SaveAs("chi2VsCent.pdf");
	c1->SaveAs("chi2VsCent.gif");
	//c1->SaveAs("chi2VsCent_prelim.gif");
	//c1->SaveAs("chi2VsCent_prelim.pdf");
}
