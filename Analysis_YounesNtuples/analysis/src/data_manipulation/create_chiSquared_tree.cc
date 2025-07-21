#include "data_manipulation/create_chiSquared_tree.h"

float mean = 0.0;
auto calcChiSquared_eventVar = [mean](Int_t ntrk, Float_t branch, Float_t branchErr=0.0){
	Float_t dev = 0.0;
	Float_t value;
	if(branchErr==0.0){
		value = branch;
	}else{
		value = branch/branchErr;
	}

	if(ntrk==4){
		dev = (mean - value)*(mean - value);
	}
	return dev;
};


template<typename T>
float calcChiSquared(float meanpar, Int_t ntrk, T branch, T branchErr){
	float dev = 0.0;
	float mean = meanpar;
	T devs;
	T values;
	if(branchErr.empty()){
		values = branch;
	}else{
		values = branch/branchErr;
	}

	if(ntrk==4){
		for(int itrk=0; itrk<ntrk; itrk++){
			devs.push_back((mean - values.at(itrk))*(mean - values.at(itrk)));
		}
	}
	// For testting purposes do sum here
	
	float chi2 = 0.0;
	for(int itrk=0; itrk<4; itrk++){
		chi2 += devs.at(itrk);
	}
	return chi2;
}


void getChiSquared_tree(float meanpar, std::string treename, std::string filepath, std::string outfilename){
	ROOT::RDataFrame df(treename.c_str(), filepath.c_str());
	float mean = meanpar;
	auto df2 = df
			.Define("chi2_zPV", [=](Int_t ntrk, Float_t zPV){ return calcChiSquared_eventVar(ntrk, zPV); }, {"ntrk", "zPV"})
			.Define("chi2_dxy_dxyerr", [=](Int_t ntrk, RVecF dxy, RVecF dxyerr){ return calcChiSquared<RVecF>(mean, ntrk, dxy, dxyerr); }, {"ntrk", "trk_dxy", "trk_dxyerr"});

	df2.Snapshot("tree", (outfilename+"chi2.root").c_str(), {"chi2_zPV", "chi2_dxy_dxyerr"});

}
