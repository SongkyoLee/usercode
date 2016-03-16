void draw_pT_y()
{
	// Open RooDataFile
	TFile fInData("/afs/cern.ch/work/k/kyolee/private/cms442/src/pAJpsi/outRoo_Pbp_sglMuEtaAll/outRoo_Pbp_sglMuEtaAll.root");
	if (fInData.IsZombie()) { cout << "CANNOT open data root file\n"; return 1; }
	fInData.cd();
	RooDataSet *data;
		data = (RooDataSet*)fInData.Get("dataJpsi");  //Unweighted
		cout << "## UN-WEIGHTED dataset is used!\n";
		data->SetName("data");

	// Create work space
	RooWorkspace *ws = new RooWorkspace("workspace");
	ws->import(*data);

	//print var and num of events in data
	data->Print();

	// construct plot frame
	RooPlot *ptFrame = ws->var("Jpsi_Pt")->frame();
	RooPlot *yFrame = ws->var("Jpsi_Y")->frame();
	ws->data("data")->plotOn(ptFrame);
	ws->data("data")->plotOn(yFrame);
/*
  // Draw all frames on a canvas
  TCanvas* c = new TCanvas("pt&y","pt&y",800,400) ;
  c->Divide(2) ;
  c->cd(1) ;
	//gPad->SetLeftMargin(0.15) ; 
	ptFrame->Draw() ;
  c->cd(2) ; 
	//gPad->SetLeftMargin(0.15) ; 
	yFrame->Draw() ;
*/
	// Draw 2D
  TCanvas* c2 = new TCanvas("pt&y","pt&y",600,600) ;
	TH2F* hist;
	hist = ws->data("data")->createHistogram( "Jpsi_Y", "Jpsi_Pt", 100, 100);
	c2->cd()
	hist->Draw();
	
	 
}
