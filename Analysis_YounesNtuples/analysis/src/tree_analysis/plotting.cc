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


void plot2D_masspairs(bool correct, std::string filepath, std::string outpath, int nbins, float min, float max, bool logscale){
	TH2F* hist = new TH2F("2d correl", "Reconstructed invariant mass", nbins, min, max, nbins, min, max);
	TCanvas* c1 = new TCanvas("fig", "fig", 1200, 1000);
	if(logscale){c1->SetLogz(); }
	hist->GetXaxis()->SetTitle("mass [MeV]");
	hist->GetYaxis()->SetTitle("mass [MeV]");

	ROOT::RDataFrame df("tree", filepath);
	auto fill2D = [=](RVecF pair){ hist->Fill(pair.at(0)*1e3, pair.at(1)*1e3); };
	
	if(correct){
		df.Foreach(fill2D, {"correct_massPair"});
	}else{
		df.Foreach(fill2D, {"wrong_massPair"});
	}
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

void plot2D_correl_trkp_prp(std::string filepath, std::string outpath, std::string direction, int xnbins, int ynbins, float xmin, float ymin, float xmax, float ymax, bool logscale){
	TH2F* hist = new TH2F(("2d correl "+direction+"-direction").c_str(), "Proton momentum  vs. trk momentum ", xnbins, xmin, xmax, ynbins, ymin, ymax);
	TCanvas* c1 = new TCanvas("fig", "fig", 1200, 1000);
	if(logscale){c1->SetLogz(); }
	hist->GetYaxis()->SetTitle(("#sum_{trks}p_{"+direction+"}").c_str());
	hist->GetXaxis()->SetTitle(("#sum pr_p"+direction).c_str());

	ROOT::RDataFrame df("tree", filepath);
	auto fill2D = [=](RVecF trk_pt, RVecF trk_phi, RVecF trk_eta, Double_t pr_pa, Double_t pr_pb, Int_t ntrk){
		if(ntrk==4){ 
			Double_t pr_p = pr_pa + pr_pb;
			Float_t trk_p = 0.0;
			if(direction=="x"){
				for(int itrk=0; itrk<ntrk; itrk++){
					trk_p += trk_pt.at(itrk)*cos(trk_phi.at(itrk));
				} 
			}else if(direction=="y"){
				for(int itrk=0; itrk<ntrk; itrk++){
					trk_p += trk_pt.at(itrk)*sin(trk_phi.at(itrk));
				} 
			}else if(direction=="z"){
				for(int itrk=0; itrk<ntrk; itrk++){
					trk_p += trk_pt.at(itrk)*sinh(trk_eta.at(itrk));
				}
			}else{
				std::cerr<<"Invalid direction parameter. Use x,y or z"<<std::endl;
			}

			hist->Fill(pr_p, trk_p); };
	 	};
	auto pr_a = ("pr_p"+direction+"_a").c_str(); 
	auto pr_b = ("pr_p"+direction+"_b").c_str(); 
	df.Foreach(fill2D, {"trk_pt", "trk_phi", "trk_eta", pr_a, pr_b, "ntrk"});
	TFile* outfile = new TFile(outpath.c_str(), "RECREATE");
	hist->Draw("COLZ");
	c1->Write();
	outfile->Close();
}

void plot2D_correl_trkvars(std::string filepath, std::string outpath, std::string xbranch, std::string ybranch, int xnbins, int ynbins, float xmin, float ymin, float xmax, float ymax, bool logscale){
	TH2F* hist = new TH2F("Energy loss", "dE/dx  vs. trk momentum ", xnbins, xmin, xmax, ynbins, ymin, ymax);
	TCanvas* c1 = new TCanvas("fig", "fig", 1200, 1000);
	if(logscale){c1->SetLogz(); }
	hist->GetXaxis()->SetTitle("trk momentum [Mev]");
	hist->GetYaxis()->SetTitle("dE/dx");

	ROOT::RDataFrame df("tree", filepath);
	auto fill2D = [=](RVecF x, RVecF y, Int_t ntrk){
		for(int itrk=0; itrk<ntrk; itrk++){ 
			hist->Fill(x.at(itrk), y.at(itrk));
		 };
	 	};
	df.Foreach(fill2D, {xbranch.c_str(), ybranch.c_str(), "ntrk"});
	TFile* outfile = new TFile(outpath.c_str(), "RECREATE");
	hist->Draw("COLZ");
	c1->Write();
	outfile->Close();
}



void plot1D_trkvar(std::string filepath, std::string outpath, std::string branch, int nbins, float min, float max, bool logscale){
	auto fp = filepath.c_str();
	auto op = outpath.c_str();
	auto bname = branch.c_str();
	TH1F* hist = new TH1F("1d histo", bname, nbins, min, max);
	TCanvas* c1 = new TCanvas("Fig", "Fig", 1200, 1000);
	if(logscale){ c1->SetLogy(); }
	hist->GetXaxis()->SetTitle(bname);
	hist->GetYaxis()->SetTitle("events");
	
	ROOT::RDataFrame df("tree", fp);
	auto fill1D = [=](RVecF values, Int_t ntrk){
			for(int itrk=0; itrk<ntrk; itrk++){
				hist->Fill(values.at(itrk)); };
			}; 

	df.Foreach(fill1D, {bname, "ntrk"});
	TFile* outfile = new TFile(op, "RECREATE");
	hist->Draw();
	c1->Write();
	outfile->Close();
}
