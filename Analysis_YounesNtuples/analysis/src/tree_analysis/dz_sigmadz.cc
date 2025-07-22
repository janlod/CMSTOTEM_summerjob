#include "tree_analysis/dz_sigmadz.h"

void dz_dist(TTree *tree, std::string filebasename){
	    Float_t trk_dz[1000], trk_dzerr[1000];
	    Int_t ntrk;

	    tree->SetBranchAddress("trk_dz", trk_dz);
	    tree->SetBranchAddress("trk_dzerr", trk_dzerr);
	    tree->SetBranchAddress("ntrk", &ntrk);
		
	    TCanvas *c1 = new TCanvas("Figure","Figure",1000,800);
	    TH1F* hist1d = new TH1F(("dz/dzerr from" + filebasename).c_str(), "dz/dzerr", 400, -4, 4);
	    hist1d->GetXaxis()->SetTitle("dz/dzerr");
	    //c1->SetLogy();

	    Long64_t nentries = tree->GetEntries();
	    Int_t counter4 = 0;
	    for (Int_t i = 0; i < nentries; i++) {
		tree->GetEntry(i);
		if(ntrk == 4){
		    for(Int_t i_trk = 0; i_trk < ntrk; i_trk++){
			//Choose what to plot
			hist1d->Fill(trk_dz[i_trk]/trk_dzerr[i_trk]);
			
		    }
		    
		    counter4++;
		}
	    }
	    //std::cout<< counter4 << std::endl;
	    TF1* gausFit = new TF1("gausFit", "gaus", -0.5, 0.5);
	    std::cout << "Fit for " << filebasename << ".root" <<std::endl;
	    hist1d->Fit(gausFit, "R");

	    gausFit->SetLineColor(kRed);
	    gausFit->SetLineWidth(2);

	    // Extract fit parameters
	    double amplitude = gausFit->GetParameter(0);
	    double mean      = gausFit->GetParameter(1);
	    double sigma     = gausFit->GetParameter(2);

	    // Create a TPaveText in NDC (normalized device coords, 0-1 range)
	    TPaveText* pave = new TPaveText(0.125, 0.7, 0.425, 0.88, "NDC"); 
	    pave->SetFillColor(0);     
	    pave->SetTextAlign(12);    
	    pave->SetTextSize(0.03);   
	    pave->AddText(Form("Gaussian Fit:"));
	    pave->AddText(Form("Mean =%f ", mean));
	    pave->AddText(Form("Sigma =%f ", sigma));
	    pave->AddText(Form("Amplitude =%f ", amplitude));
	    

	    hist1d->Draw("E1");   
	    gausFit->Draw("same");   
	    pave->Draw();          
	    c1->SaveAs(("plots/dz_dist/dz_" + filebasename + ".png").c_str());
	    delete hist1d;
	    delete c1;
}
