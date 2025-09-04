#include "data_manipulation/elastic_veto.h"

bool isElastic(double pr_px_a, double pr_px_b, double pr_py_a, double pr_py_b, float threshold){

	double pr_px = pr_px_a + pr_px_b;
	double pr_py = pr_py_a + pr_py_b;

	float prot_px = static_cast<float>(pr_px);
	float prot_py = static_cast<float>(pr_py);

	
	if(abs(pr_px)<threshold && abs(pr_py)<threshold){
		return false;
	}
	
	return true;
}

void cutElastic_veto(std::string filepath, std::string outpath, float threshold_par){
	ROOT::RDataFrame df("tree", filepath.c_str());
	float threshold = threshold_par;

	auto elasticVetoed = df.Filter([threshold](double pr_px_a, double pr_px_b, double pr_py_a, double pr_py_b){ return isElastic(pr_px_a, pr_px_b, pr_py_a, pr_py_b, threshold); }, {"pr_px_a", "pr_px_b", "pr_py_a", "pr_py_b"});

	elasticVetoed.Snapshot("tree", outpath.c_str());
}

