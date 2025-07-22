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
	float mean = meanpar;
	T devs {};
	T values {};
	if(branchErr.empty()){
		values = branch;
	}else if(!branch.empty()){
		values = branch/branchErr;
	}else{
		std::cout<<"empty branch"<<std::endl;
	}
	
	for(int itrk=0; itrk<ntrk; itrk++){
		devs.push_back((mean - values[itrk])*(mean - values[itrk]));
	}
	
	
	float chi2 = 0.0;
	for(int itrk=0; itrk<ntrk; itrk++){
		chi2 += devs[itrk];
	}
	return chi2;
}

// Expected order of meanpar [ zPV, dxy/dxyerr, dz/dzerr ]
void getChiSquared_tree(std::vector<float> meanpars, std::string treename, std::string filepath, std::string outfilename){
	ROOT::RDataFrame df(treename.c_str(), filepath.c_str());
	float mean = meanpars.at(0);
	int ntrk = 4;
	auto df2 = df
			.Define("chi2_zPV", [=](Int_t ntrk, Float_t zPV){ return calcChiSquared_eventVar(ntrk, zPV); }, {"ntrk", "zPV"})
			.Define("chi2_dxy_dxyerr", [=](Int_t ntrk, RVecF dxy, RVecF dxyerr){ return calcChiSquared<RVecF>(meanpars.at(1), ntrk, dxy, dxyerr); }, {"ntrk", "trk_dxy", "trk_dxyerr"})
		.Define("chi2_dz_dzerr", [=](Int_t ntrk, RVecF dz, RVecF dzerr){ return calcChiSquared<RVecF>(meanpars.at(2), ntrk, dz, dzerr); }, {"ntrk", "trk_dz", "trk_dzerr"})
 		.Filter([ntrk](int x) { return x==ntrk; }, {"ntrk"});

	auto originalColumns = df.GetColumnNames();
	    
	std::vector<std::string> newColumns = {
		"chi2_zPV", "chi2_dxy_dxyerr", "chi2_dz_dzerr"
	};

	std::vector<std::string> allColumns(originalColumns.begin(), originalColumns.end());
	allColumns.insert(allColumns.end(), newColumns.begin(), newColumns.end());


	df2.Snapshot(treename.c_str(), ("data/chi2_combined/" + outfilename + "chi2.root").c_str(), allColumns);

}


