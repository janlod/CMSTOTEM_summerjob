#include "tree_analysis/plot_chi2.h"

void plot_chi2(std::string branchname, std::string treename, std::string filepath, std::string outfilename, int nbins, float minbin, float maxbin){
	ROOT::RDataFrame df(treename.c_str(), filepath.c_str());
	
	auto hist = df.Histo1D({"chi2", "chi2", nbins, minbin, maxbin}, branchname.c_str());
	hist->GetXaxis()->SetTitle(branchname.c_str());
	
	TCanvas* c1 = new TCanvas("Fig", "Fig", 1200, 1000);
	TFile* outfile = new TFile((outfilename + ".root").c_str(), "RECREATE");
 	
	c1->SetLogy();	
	hist->Draw();
	c1->Write();
	outfile->Close();
}
