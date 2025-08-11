#include "tree_analysis/find_optimal_cutoff.h"

float get_chi2Cutoff(TH1F* bgHist, TH1F* sgHist, double significance){
	TH1* bgCDF = bgHist->GetCumulative(false);

	double alpha = significance; // Example significance level
	int nbins = bgCDF->GetNbinsX();
	double cutoff = -1;

	for (int i = 1; i <= nbins; i++) {
    		double ccdf = bgCDF->GetBinContent(i);  // P(x > bin edge)
    		if (ccdf <= alpha) {
        		cutoff = bgCDF->GetBinLowEdge(i);
        		break;
    		}
	}

	if (cutoff >= 0){
    		std::cout << "Cutoff x = " << cutoff << " gives background significance level alpha = " << alpha << std::endl;
	}else{
    		std::cout << "Could not find suitable cutoff for the given alpha" << std::endl;
	}

	return cutoff;
}

void draw_CDFs(TH1F* bgHist, TH1F* sgHist, std::string outpath){
	TH1* bgCDF = bgHist->GetCumulative();
	bgCDF->SetLineColor(kBlue);
	TH1* sgCDF = sgHist->GetCumulative();
	TH1* diff = (TH1*)sgCDF->Clone("diff");
	diff->Add(bgCDF, -1);
	diff->SetLineColor(kGreen+2);
	sgCDF->SetLineColor(kRed);
	sgCDF->SetTitle("Cumulative density function");
	sgCDF->GetXaxis()->SetTitle("chi2_dxy_dxyerr");
	sgCDF->GetYaxis()->SetTitle("probability");

	TCanvas* c1 = new TCanvas("fig", "fig", 1200, 1000);
	TLegend* leg = new TLegend(0.7, 0.2, 0.85, 0.35);
	leg->AddEntry(bgCDF, "Kaon CDF","l");
	leg->AddEntry(sgCDF, "Rho CDF", "l");
	leg->AddEntry(diff, "Difference", "l");
	leg->SetFillStyle(0);

	TFile* outfile = new TFile(outpath.c_str(), "RECREATE");
	sgCDF->Draw("HIST");
	bgCDF->Draw("HIST Same");
	diff->Draw("HIST same");
	leg->Draw("same");
	c1->Write();		
	outfile->Close();

}
