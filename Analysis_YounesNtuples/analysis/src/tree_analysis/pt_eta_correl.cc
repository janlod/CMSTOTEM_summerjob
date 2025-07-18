void pt_eta_correl(TTree *tree, std::string filebasename){
	    Float_t trk_pt[1000], trk_eta[1000];
	    Int_t ntrk;

	    tree->SetBranchAddress("trk_pt", trk_pt);
	    tree->SetBranchAddress("trk_eta", trk_eta);
	    tree->SetBranchAddress("ntrk", &ntrk);
		
	    TCanvas *c1 = new TCanvas("Figure","Figure",1000,800);
	    TH2F* hist2d = new TH2F(("pt vs eta from " + filebasename).c_str(), "pt eta correl", 400, 0, 3.0, 400, 0, 3);
	    hist2d->GetXaxis()->SetTitle("pt");
	    hist2d->GetYaxis()->SetTitle("eta");
	    //c1->SetLogy();

	    Long64_t nentries = tree->GetEntries();
	    Int_t counter4 = 0;
	    for (Int_t i = 0; i < nentries; i++) {
		tree->GetEntry(i);
		if(ntrk == 4){
		    for(Int_t i_trk = 0; i_trk < ntrk; i_trk++){
			hist2d->Fill(trk_pt[i_trk], trk_eta[i_trk]);
		    }
		}
	    }
	    std::cout<< counter4 << std::endl;
	    hist2d->Draw();                
	    c1->SaveAs(("../plots/pt_dedx_correl/pt_eta_" + filebasename + ".png").c_str());
	    delete hist2d;
	    delete c1;
}
