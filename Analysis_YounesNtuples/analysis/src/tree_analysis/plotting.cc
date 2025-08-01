#include "tree_analysis/plotting.h"

void plot2D_correl_eventvar(std::string filepath, std::string outpath, std::string xbranch, std::string ybranch, int xnbins, int ynbins, float xmin, float ymin, float xmax, float ymax, bool logscale){
	TH2F* hist = new TH2F("2d correl", (xbranch + " vs. " + ybranch).c_str(), xnbins, xmin, xmax, ynbins, ymin, ymax);
	TCanvas* c1 = new TCanvas("fig", "fig", 1200, 1000);
	if(logscale){c1->SetLogz(); }
	hist->GetXaxis()->SetTitle(xbranch.c_str());
	hist->GetYaxis()->SetTitle(ybranch.c_str());

	ROOT::RDataFrame df("tree", filepath);
	auto fill2D = [=](float value1, float value2){ hist->Fill(value1, value2); };
	
	df.Foreach(fill2D, {xbranch.c_str(), ybranch.c_str()});
	TFile* outfile = new TFile(outpath.c_str(), "RECREATE");
	hist->Draw("COLZ");
	c1->Write();
	outfile->Close();
}


void plot1D_eventvar(std::string filepath, std::string outpath, std::string branch, int nbins, float min, float max, bool logscale){
	auto fp = filepath.c_str();
	auto op = outpath.c_str();
	auto bname = branch.c_str();
	TH1F* hist = new TH1F("1d histo", bname, nbins, min, max);
	TCanvas* c1 = new TCanvas("Fig", "Fig", 1200, 1000);
	if(logscale){ c1->SetLogy(); }
	hist->GetXaxis()->SetTitle(bname);
	hist->GetYaxis()->SetTitle("events");
	
	ROOT::RDataFrame df("tree", fp);
	auto fill1D = [=](float value){ hist->Fill(value); };

	df.Foreach(fill1D, {bname});
	TFile* outfile = new TFile(op, "RECREATE");
	hist->Draw();
	c1->Write();
	outfile->Close();
}
