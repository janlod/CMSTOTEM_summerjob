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


std::pair<TH1F*, TH1F*> plot_chi2_inWindow(std::string filepath, std::string outpath, std::string chi2_branch, std::vector<float> rhoWindow, std::vector<float> kaonWindow, int nbins, float plotmin, float plotmax){
	ROOT::RDataFrame df("tree", filepath.c_str());
	TCanvas* c1 = new TCanvas("fig", "fig", 1200, 1000);
	TH1F* histrho = new TH1F("chi2 rho", chi2_branch.c_str(), nbins, plotmin, plotmax);
	TH1F* histkaon = new TH1F("chi2 kaon", chi2_branch.c_str(), nbins, plotmin, plotmax);
	TFile* outfile = new TFile(outpath.c_str(), "RECREATE");	

	TLegend* leg = new TLegend(0.6, 0.7, 0.8, 0.85); // (x1, y1, x2, y2) in NDC
	leg->SetBorderSize(0);       // No border
	leg->SetFillStyle(0);        // Transparent fill
	leg->SetTextSize(0.04);      // Adjust text size if needed
	leg->AddEntry(histrho, "Rho", "l");   // "l" = line style
	leg->AddEntry(histkaon, "Kaon", "l");
	

	
	auto fill = [=](RVecF masspair1, RVecF masspair2, float chi2){ 
			if(masspair1.at(0)*1e3 < rhoWindow.at(1) && masspair1.at(0)*1e3 > rhoWindow.at(0) && masspair1.at(1)*1e3 < rhoWindow.at(1) && masspair1.at(1)*1e3 > rhoWindow.at(0)){
				histrho->Fill(chi2);
			}	
			if(masspair2.at(0)*1e3 < rhoWindow.at(1) && masspair2.at(0)*1e3 > rhoWindow.at(0) && masspair2.at(1)*1e3 < rhoWindow.at(1) && masspair2.at(1)*1e3 > rhoWindow.at(0)){
				histrho->Fill(chi2);
		  	};

			if(masspair1.at(0)*1e3 < kaonWindow.at(1) && masspair1.at(0)*1e3 > kaonWindow.at(0) && masspair1.at(1)*1e3 < kaonWindow.at(1) && masspair1.at(1)*1e3 > kaonWindow.at(0)){
				histkaon->Fill(chi2);
			}	
			if(masspair2.at(0)*1e3 < kaonWindow.at(1) && masspair2.at(0)*1e3 > kaonWindow.at(0) && masspair2.at(1)*1e3 < kaonWindow.at(1) && masspair2.at(1)*1e3 > kaonWindow.at(0)){
				histkaon->Fill(chi2);
		  	};

	};

	df.Foreach(fill, {"inv_mass_pair1", "inv_mass_pair2", chi2_branch.c_str()});			
	histrho->Scale(1.0 / histrho->Integral());	
	histkaon->Scale(1.0 / histkaon->Integral());	
	histrho->SetLineColor(kRed);
	histkaon->SetLineColor(kBlue);	
	histrho->Draw("HIST");
	histkaon->Draw("HIST SAME");
	leg->Draw();
	
	c1->Write();
	outfile->Close();

	return std::make_pair(histkaon, histrho);	
}
