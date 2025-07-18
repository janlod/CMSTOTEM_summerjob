#include "tree_analysis/dz_eta_correl.h"

void dz_eta_correl(TTree *tree, std::string filebasename){
	    Float_t trk_dz[1000], trk_eta[1000];
	    Int_t ntrk;

	    tree->SetBranchAddress("trk_dz", trk_dz);
	    tree->SetBranchAddress("trk_eta", trk_eta);
	    tree->SetBranchAddress("ntrk", &ntrk);
		
	    TCanvas *c1 = new TCanvas("Figure","Figure",1000,800);
	    TH2F* hist2d = new TH2F(("dz vs eta from " + filebasename).c_str(), "dz eta correl", 400, -0.5, 0.5, 400, -3.0, 3.0);
	    hist2d->GetXaxis()->SetTitle("dz");
	    hist2d->GetYaxis()->SetTitle("#eta");
	    //c1->SetLogy();

	    Long64_t nentries = tree->GetEntries();
	    Int_t counter4 = 0;
	    for (Int_t i = 0; i < nentries; i++) {
		tree->GetEntry(i);
		if(ntrk == 4){
		    for(Int_t i_trk = 0; i_trk < ntrk; i_trk++){
			hist2d->Fill(trk_dz[i_trk], trk_eta[i_trk]);
		    }
		    
		    counter4++;
		}
	    }
	    std::cout<< counter4 << std::endl;
	    hist2d->Draw();                
	    c1->SaveAs(("../../plots/dz_eta_correl/dz_eta_" + filebasename + ".png").c_str());
	    delete hist2d;
	    delete c1;
}
