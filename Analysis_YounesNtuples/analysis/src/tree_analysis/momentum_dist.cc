void p_dist(TTree *tree, std::string filebasename){
	    Float_t trk_p[1000];
	    Int_t ntrk;

	    tree->SetBranchAddress("trk_p", trk_p);
	    tree->SetBranchAddress("ntrk", &ntrk);
		
	    TCanvas *c1 = new TCanvas("Figure","Figure",1000,800);
	    TH1F* hist1d = new TH1F(("#trk_momentum from" + filebasename).c_str(), "momentum", 400, 0, 4);
	    hist1d->GetXaxis()->SetTitle("p");
	    //c1->SetLogy();

	    Long64_t nentries = tree->GetEntries();
	    Int_t counter4 = 0;
	    for (Int_t i = 0; i < nentries; i++) {
		tree->GetEntry(i);
		if(ntrk == 4){
		    for(Int_t i_trk = 0; i_trk < ntrk; i_trk++){
			hist1d->Fill(trk_p[i_trk]);
		    }
		    
		    counter4++;
		}
	    }


	    hist1d->Draw("E1");  
	    c1->SaveAs(("../plots/p_dist/p_" + filebasename + ".png").c_str());
	    delete hist1d;
	    delete c1;
}
