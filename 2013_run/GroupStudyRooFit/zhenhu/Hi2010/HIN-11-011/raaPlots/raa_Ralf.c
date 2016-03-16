{
	ifstream in_SBS1S, in_SBS2S;
	in_SBS1S.open("LHC-SBS-nabs0.0-2.0-1sRAA.dat");
	in_SBS2S.open("LHC-SBS-nabs0.0-2.0-2sRAA.dat");

	float N_part_1S[50], N_coll_1S[50], Absorp_l_1S[50], Primordial_l_1S[50], Total_l_1S[50], Absorp_h_1S[50], Primordial_h_1S[50], Total_h_1S[50];
	float N_part_Err[50], Absorp_1S[50], Primordial_1S[50], Total_1S[50], Absorp_1S_err[50], Primordial_1S_err[50], Total_1S_err[50];
	float regen_l_1S[50], regen_h_1S[50], regen_l_1S[50], regen_h_1S[50], regen_mean_1S[50], regen_err_1S[50];

	for (int i=0; i<28; i++) {
		in_SBS1S >> N_part_1S[i] >> N_coll_1S[i] >> Absorp_l_1S[i] >> Primordial_l_1S[i] >> Total_l_1S[i] >> Absorp_h_1S[i] >> Primordial_h_1S[i] >> Total_h_1S[i];
		cout << N_part_1S[i] << " " << N_coll_1S[i] << " " << Absorp_l_1S[i] << " " << Primordial_l_1S[i] << " " << Total_l_1S[i] << " " << Absorp_h_1S[i] << " " << Primordial_h_1S[i] << " " << Total_h_1S[i] << endl;
		Absorp_1S[i] = (Absorp_l_1S[i] + Absorp_h_1S[i])/2;
		Primordial_1S[i] = (Primordial_l_1S[i] + Primordial_h_1S[i])/2;
		Total_1S[i] = (Total_l_1S[i] + Total_h_1S[i])/2;
		Absorp_1S_err[i] = (Absorp_l_1S[i] - Absorp_h_1S[i])/2;
		Primordial_1S_err[i] = (Primordial_l_1S[i] - Primordial_h_1S[i])/2;
		Total_1S_err[i] = (Total_l_1S[i] - Total_h_1S[i])/2;
		regen_l_1S[i] = Total_l_1S[i] - Primordial_l_1S[i];
		regen_h_1S[i] = Total_h_1S[i] - Primordial_h_1S[i];
		regen_mean_1S[i] = (regen_l_1S[i] + regen_h_1S[i])/2;
		regen_err_1S[i] = (regen_l_1S[i] - regen_h_1S[i])/2;
		N_part_Err[i]=0;
	}

	TGraphErrors* SBS_Absorp_1S = new TGraphErrors(28, N_part_1S, Absorp_1S, N_part_Err, Absorp_1S_err);
	TGraphErrors* SBS_Primordial_1S = new TGraphErrors(28, N_part_1S, Primordial_1S, N_part_Err, Primordial_1S_err);
	TGraphErrors* SBS_Total_1S = new TGraphErrors(28, N_part_1S, Total_1S, N_part_Err, Total_1S_err);
	TGraph* SBS_regen_1S = new TGraph(28, N_part_1S, regen_mean_1S);


	SBS_Absorp_1S->SetFillColor(kOrange-4);
	SBS_Absorp_1S->SetLineColor(kOrange-4);

	SBS_Primordial_1S->SetFillColor(kRed-4);
	SBS_Primordial_1S->SetLineColor(kRed-4);

	SBS_Total_1S->SetFillColor(kBlue-4);
	//SBS_Total_1S->SetFillStyle(3144);
	SBS_Total_1S->SetLineColor(kBlue-4);

	SBS_regen_1S->SetLineColor(kBlack);


	float N_part_2S[50], N_coll_2S[50], Absorp_l_2S[50], Primordial_l_2S[50], Total_l_2S[50], Absorp_h_2S[50], Primordial_h_2S[50], Total_h_2S[50];
	float Absorp_2S[50], Primordial_2S[50], Total_2S[50], Absorp_2S_err[50], Primordial_2S_err[50], Total_2S_err[50];
	float regen_l_2S[50], regen_h_2S[50], regen_l_2S[50], regen_h_2S[50], regen_mean_2S[50], regen_err_2S[50];

	for (int i=0; i<28; i++) {
		in_SBS2S >> N_part_2S[i] >> N_coll_2S[i] >> Absorp_l_2S[i] >> Primordial_l_2S[i] >> Total_l_2S[i] >> Absorp_h_2S[i] >> Primordial_h_2S[i] >> Total_h_2S[i];
		cout << N_part_2S[i] << " " << N_coll_2S[i] << " " << Absorp_l_2S[i] << " " << Primordial_l_2S[i] << " " << Total_l_2S[i] << " " << Absorp_h_2S[i] << " " << Primordial_h_2S[i] << " " << Total_h_2S[i] << endl;
		Absorp_2S[i] = (Absorp_l_2S[i] + Absorp_h_2S[i])/2;
		Primordial_2S[i] = (Primordial_l_2S[i] + Primordial_h_2S[i])/2;
		Total_2S[i] = (Total_l_2S[i] + Total_h_2S[i])/2;
		Absorp_2S_err[i] = (Absorp_l_2S[i] - Absorp_h_2S[i])/2;
		Primordial_2S_err[i] = (Primordial_l_2S[i] - Primordial_h_2S[i])/2;
		Total_2S_err[i] = (Total_l_2S[i] - Total_h_2S[i])/2;
		regen_l_2S[i] = Total_l_2S[i] - Primordial_l_2S[i];
		regen_h_2S[i] = Total_h_2S[i] - Primordial_h_2S[i];
		regen_mean_2S[i] = (regen_l_2S[i] + regen_h_2S[i])/2;
		regen_err_2S[i] = (regen_l_2S[i] - regen_h_2S[i])/2;
	}

	TGraphErrors* SBS_Absorp_2S = new TGraphErrors(28, N_part_2S, Absorp_2S, N_part_Err, Absorp_2S_err);
	TGraphErrors* SBS_Primordial_2S = new TGraphErrors(28, N_part_2S, Primordial_2S, N_part_Err, Primordial_2S_err);
	TGraphErrors* SBS_Total_2S = new TGraphErrors(28, N_part_2S, Total_2S, N_part_Err, Total_2S_err);
	TGraph* SBS_regen_2S = new TGraph(28, N_part_2S, regen_mean_2S);

	//SBS_Absorp_2S->SetFillStyle(3244);
	//SBS_Absorp_2S->SetFillColor(kMagenta);

	SBS_Primordial_2S->SetFillColor(kMagenta);
	SBS_Primordial_2S->SetLineColor(kMagenta);

	SBS_Total_2S->SetFillColor(kRed+2);
	SBS_Total_2S->SetLineColor(kRed+2);
	//SBS_Total_2S->SetFillStyle(3144);

	SBS_regen_2S->SetLineStyle(kDashed);


	int bin = 7;
	int bin1 = 7;
	float cent[bin]={22.1, 86.3, 130.0, 187.1, 261.4, 329.4, 381.3};
	float cent1[8]={14.2, 53.5, 86.3, 130.0, 187.1, 261.4, 329.4, 381.3};
	float centErr[bin]={6,6,6,6,6,6,6};
	float centnoErr[bin]={0,0,0,0};

	//pt > 4 Raa
	float ratio1S[bin]={1.005,0.590,0.681,0.614,0.484,0.432,0.411};
	float ratio1SstatErr[bin]={0.121,0.096,0.069,0.053,0.040,0.048,0.043};
	float ratio1SsystErr[bin]={0.176,0.086,0.085,0.075,0.049,0.046,0.048};
	float ratio2S[bin]={0.300,0.251,0.237,0.260,0.068,0.044,0.111};
	float ratio2SstatErr[bin]={0.157,0.138,0.098,0.079,0.053,0.060,0.061};
	float ratio2SsystErr[bin]={0.069,0.050,0.039,0.043,0.022,0.019,0.020};

	float tot1SErr[bin];
	float tot2SErr[bin];
	for (int i=0; i<bin; i++){
		tot1SErr[i] = sqrt(ratio1SstatErr[i]*ratio1SstatErr[i]+ratio1SsystErr[i]*ratio1SsystErr[i]);
		cout<<i<<" "<<tot1SErr[i]<<endl;
	}
	for (int i=0; i<bin; i++){
		tot2SErr[i] = sqrt(ratio2SstatErr[i]*ratio2SstatErr[i]+ratio2SsystErr[i]*ratio2SsystErr[i]);
		cout<<i<<" "<<tot2SErr[i]<<endl;
	}

	TCanvas *c1 = new TCanvas("c1","c1");
	TF1 *f4 = new TF1("f4","1",0,400);
	f4->SetLineWidth(1);
	f4->GetXaxis()->SetTitle("N_{part}");
	f4->GetYaxis()->SetTitle("R_{AA}");
	f4->GetYaxis()->SetTitleOffset(1.0);
	f4->GetYaxis()->SetRangeUser(0,1.5);
	f4->GetXaxis()->CenterTitle(kTRUE);
	f4->Draw();

	SBS_Absorp_1S->Draw("3");
	SBS_Primordial_1S->Draw("same 3");
	SBS_Total_1S->Draw("same 3");
	SBS_regen_1S->Draw("same");   

	SBS_Primordial_2S->Draw("same 3");
	SBS_Total_2S->Draw("same 3");   
	SBS_regen_2S->Draw("same");   

	TGraphErrors *g = new TGraphErrors(bin1,cent,ratio1S,centnoErr,ratio1SstatErr);
	g->SetMarkerColor(kGreen+2);
	g->SetMarkerStyle(33);
	g->SetMarkerSize(2);

	TGraphErrors *g1Ssyst = new TGraphErrors(bin1,cent,ratio1S,centnoErr,ratio1SsystErr);
	g1Ssyst->SetLineColor(kGreen-9);
	g1Ssyst->SetLineWidth(25);
	g1Ssyst->SetMarkerSize(0);
	g1Ssyst->Draw("e");

	g->Draw("pe");

	TGraphErrors *g1circle = new TGraphErrors(bin,cent,ratio1S,centnoErr,ratio1SstatErr);
	g1circle->SetMarkerStyle(27);
	g1circle->SetMarkerSize(2);
	g1circle->SetLineColor(kBlack);
	g1circle->Draw("p");

	TGraphErrors *g2 = new TGraphErrors(bin,cent,ratio2S,centnoErr,ratio2SstatErr);
	g2->SetMarkerColor(kBlue+1);
	g2->SetMarkerStyle(20);
	g2->SetMarkerSize(1.2);

	TGraphErrors *g2Ssyst = new TGraphErrors(bin,cent,ratio2S,centnoErr,ratio2SsystErr);
	g2Ssyst->SetLineColor(kAzure-9);
	//g2Ssyst->SetFillStyle(0);
	g2Ssyst->SetLineWidth(25);
	g2Ssyst->SetMarkerSize(0);
	g2Ssyst->Draw("e");

	g2->Draw("pe");

	TGraphErrors *g2circle = new TGraphErrors(bin,cent,ratio2S,centnoErr,ratio2SstatErr);
	g2circle->SetMarkerStyle(24);
	g2circle->SetMarkerSize(1.2);
	g2circle->SetLineColor(kBlack);
	g2circle->Draw("p");

	//MB

	//pt > 4
	float centMB[1]={113.95};
	float cent_limit_err[1]={5};
	float raaMB1S[1]={0.564};
	float raaMB1SstatErr[1]={0.071};
	float raaMB1SsystErr[1]={0.060};
	float raaMB2S[1]={0.120};
	float raaMB2SstatErr[1]={0.040};
	float raaMB2SsystErr[1]={0.018};
	float raaMB3S[1]={0.033};
	float raaMB3SstatErr[1]={0.1};//{0.035};
	float raaMB3SsystErr[1]={0.006};
	float raaMB3Slimit[1]={0.1};

	float raaMB1StotErr[0]=sqrt(pow(raaMB1SstatErr[0],2)+pow(raaMB1SsystErr[0],2));
	float raaMB2StotErr[0]=sqrt(pow(raaMB2SstatErr[0],2)+pow(raaMB2SsystErr[0],2));
	float raaMB3StotErr[0]=sqrt(pow(raaMB3SstatErr[0],2)+pow(raaMB3SsystErr[0],2));

	// lumi sys

	float ppy[1]={1};
	float ppx[1]={377};
	float ppxEr[1]={0};
	float ppyErSystematic=sqrt(pow(0.06,2)+pow(0.023,2));
	cout<<"ppyErSystematic"<<ppyErSystematic<<endl;
	float ppyErSyst[1]={ppyErSystematic};
	float ppyErtotal=sqrt(pow(ppyErSystematic,2)+pow(0.12,2));
	float ppyErtol[1]={0};

	TBox *lumiY1S = new TBox(370.0,0.864,385.0,1.136);
	lumiY1S->SetFillColor(kGreen-9);
	lumiY1S->Draw("2");
	/*
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
	 */

	float Y2Sppx[1]={392};
	float Y2SppyErSystematic=sqrt(pow(0.06,2)+pow(0.033,2));
	float Y2SppyErSyst[1]={Y2SppyErSystematic};
	float Y2SppyErtotal=sqrt(pow(Y2SppyErSystematic,2)+pow(0.202,2));
	float Y2SppyErtol[1]={0};

	TBox *lumiY2S = new TBox(385.0,0.787,400.0,1.213);
	lumiY2S->SetFillColor(kAzure-9);
	//lumiY2S->SetFillStyle(0);
	//lumiY2S->SetLineWidth(2);
	//lumiY2S->SetLineColor(kGreen+2);
	lumiY2S->Draw("2");

	/*
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
	 */

	f4->Draw("same");
	gPad->RedrawAxis();

	TLatex *l1 = new TLatex(50,1.37,"CMS PbPb  #sqrt{s_{NN}} = 2.76 TeV");
	l1->SetTextFont(42);
	l1->SetTextSize(0.05);
	//TLatex *l1 = new TLatex(25,1.37,"CMS Preliminary, PbPb #sqrt{s_{NN}} = 2.76 TeV");
	//l1->SetTextSize(0.045);
	l1->Draw();

	TLatex *lumi = new TLatex(240,1.25,"L_{int} = 150 #mub^{-1}");
	//lumi->Draw();
	//lumi->DrawLatex(240,1.13,"L_{int}^{pp} = 230 nb^{-1}");

	TLatex *ly = new TLatex(240,1.15,"|y| < 2.4");
	//TLatex *ly = new TLatex(240,0.9,"|y| < 2.4");
	//TLatex *ly = new TLatex(240,1.03,"|y| < 2.4");
	//ly->Draw();

	TLatex *NucAbs = new TLatex(200,0.85,"Nuc. Abs.");
	NucAbs->Draw();

	TLatex *centrality = new TLatex(360,0.55,"0-5%");
	centrality->SetTextSize(0.03);
	//	centrality->Draw();
	//	centrality->DrawLatex(310,0.55,"5-10%");
	//	centrality->DrawLatex(240,0.6,"10-20%");
	//	centrality->DrawLatex(170,0.75,"20-30%");
	//	centrality->DrawLatex(110,0.85,"30-40%");
	//	centrality->DrawLatex(65,0.75,"40-50%");
	//	centrality->DrawLatex(10,0.65,"50-100%");

	TLegend *legend = new TLegend(0.23,0.69,0.45,0.87);
	//    TLegend *legend = new TLegend(0.2,0.69,0.5,0.87);
	legend->SetFillStyle(0);
	legend->SetFillColor(0);
	legend->SetMargin(0.25);
	legend->SetBorderSize(0);
	legend->SetTextSize(0.035);
	legend->SetTextFont(42);
	legend->SetHeader("#varUpsilon(1S)");
	//legend->AddEntry(g,"#varUpsilon(1S), stat. unc.","lpe");
	//legend->AddEntry(g1Ssyst, "#varUpsilon(1S), syst. unc.","l");
	//legend->AddEntry(g2, "#varUpsilon(2S), stat. unc.","lpe");
	//legend->AddEntry((TObject*)0, "#varUpsilon(2S), syst. unc.","");
	legend->AddEntry(g,"CMS data","p");
	//legend->AddEntry(SBS_Absorp_1S,"Nuc. Abs.","f");
	legend->AddEntry(SBS_Primordial_1S,"Primordial","f");
	legend->AddEntry(SBS_regen_1S,"Regenerated","l");
	legend->AddEntry(SBS_Total_1S,"Total","f");
	//legend->AddEntry(SBS_Absorp_1S,"Nuc. Abs.","f"); 
	legend->Draw();

	TLegend *legend2 = new TLegend(0.55,0.69,0.8,0.87);
	legend2->SetFillStyle(0);
	legend2->SetFillColor(0);
	legend2->SetMargin(0.25);
	legend2->SetBorderSize(0);
	legend2->SetTextSize(0.035);
	legend2->SetTextFont(42);
	legend2->SetHeader("#varUpsilon(2S)");
	legend2->AddEntry(g2,"CMS data","p");
	legend2->AddEntry(SBS_Primordial_2S,"Primordial","f");
	legend2->AddEntry(SBS_regen_2S,"Regenerated","l");	
	legend2->AddEntry(SBS_Total_2S,"Total","f");
	legend2->Draw();

	c1->SaveAs("Raa_SBS.gif");
	c1->SaveAs("Raa_SBS.pdf");
}
