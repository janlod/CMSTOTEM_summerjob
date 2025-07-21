#include "tree_analysis/dxy_phi_correl.h"

TH1D* CropHistogram(TH1D* h_original, double x_min, double x_max) {
	    // Get bin range corresponding to x_min and x_max
	    int bin_min = h_original->FindBin(x_min);
	    int bin_max = h_original->FindBin(x_max);
	    int new_nbins = bin_max - bin_min + 1;
	    double new_xmin = h_original->GetBinLowEdge(bin_min);
	    double new_xmax = h_original->GetBinLowEdge(bin_max + 1); // upper edge
	    // Create cropped histogram
	    TH1D* h_cropped = new TH1D("h_cropped", "Cropped Histogram;X;Entries", new_nbins, new_xmin, new_xmax);
	    for (int i = 1; i <= new_nbins; ++i) {
		int original_bin = bin_min + i - 1;
		double content = h_original->GetBinContent(original_bin);
		double error = h_original->GetBinError(original_bin);
		h_cropped->SetBinContent(i, content);
		h_cropped->SetBinError(i, error);
	    }
    	    return h_cropped;
}


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
	    //c1->SaveAs(("../../plots/dxy_phi_correl/dxy_phi_" + filebasename + ".png").c_str());
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
	    c1->SaveAs("../../plots/test.png");
	    delete hist2d;
	    delete c1;
}
