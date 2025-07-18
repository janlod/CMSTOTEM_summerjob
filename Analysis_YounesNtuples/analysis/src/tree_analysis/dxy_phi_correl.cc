void dxy_phi_correl(TTree *tree, std::string filebasename, bool cut){
	    Float_t trk_dxy[1000], trk_phi[1000];
	    Int_t ntrk;

	    tree->SetBranchAddress("trk_dxy", trk_dxy);
	    tree->SetBranchAddress("trk_phi", trk_phi);
	    tree->SetBranchAddress("ntrk", &ntrk);
		
	    TCanvas *c1 = new TCanvas("Figure","Figure",1000,800);
	    TH2F* hist2d = new TH2F(("dxy vs phi from " + filebasename).c_str(), "dxy phi correl", 400, -0.3, 0.3, 400, -3.14, 3.14);
	    hist2d->GetXaxis()->SetTitle("dxy");
	    hist2d->GetYaxis()->SetTitle("#phi");

	    TF1* gausFit = new TF1("gausFit", "gaus", -0.02, 0.02);
	    

	    //c1->SetLogy();

	    Long64_t nentries = tree->GetEntries();
	    Int_t counter4 = 0;
	    for (Int_t i = 0; i < nentries; i++) {
		tree->GetEntry(i);
		if(ntrk == 4){
		    for(Int_t i_trk = 0; i_trk < ntrk; i_trk++){
			hist2d->Fill(trk_dxy[i_trk], trk_phi[i_trk]);
		    }
		    counter4++;
		}
	    }
	    std::cout<< counter4 << std::endl;
	    //hist2d->Draw();              
	    //c1->SaveAs(("../plots/dxy_phi_correl/dxy_phi_" + filebasename + ".png").c_str());
	     if(cut){
		    TH1D *histslice = hist2d->ProjectionX("slice");
		    histslice->Fit(gausFit, "R");
		   
		    double mean      = gausFit->GetParameter(1);
		    double sigma     = gausFit->GetParameter(2);
		    TH1D *cuttedHisto = CropHistogram(histslice, mean-3*sigma, mean +3*sigma);
		    gausFit->SetLineColor(kRed);
		    gausFit->SetLineWidth(2);

		    // cuttedHisto->Draw();
		    // gausFit->Draw("same");
		    //histslice->Draw();
		    cuttedHisto->Draw();

		}
	    c1->SaveAs("../plots/test.png");
	    delete hist2d;
	    delete c1;
}
