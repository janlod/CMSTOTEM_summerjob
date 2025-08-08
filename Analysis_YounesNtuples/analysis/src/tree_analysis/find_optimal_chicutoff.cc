#include "tree_analysis/find_optimal_cutoff.h"

float get_chi2Cutoff(TH1F* bgHist, TH1F* sgHist, double significance){
	TH1* bgCDF = bgHist->GetCumulative();

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
