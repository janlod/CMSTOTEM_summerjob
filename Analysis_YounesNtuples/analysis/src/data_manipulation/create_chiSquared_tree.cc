#include "data_manipulation/create_chiSquared_tree.h"

float mean = 0.0;
float sigma = 1.0;
auto calcChiSquared_eventVar = [mean, sigma](Int_t ntrk, Float_t branch, Float_t branchErr=0.0){
	Float_t dev = 0.0;
	Float_t value;
	if(branchErr==0.0){
		value = branch;
	}else{
		value = branch/branchErr;
	}

	if(ntrk==4){
		dev = (mean - value)*(mean - value)/(sigma*sigma);
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

float getChi2_rhoMass(float mean, float sigma, RVecF inv_mass_pair){
	float chi2 = 0.0;
	for(int i=0; i<2; i++){
		chi2 += (inv_mass_pair.at(i)*1e3 - mean)*(inv_mass_pair.at(i)*1e3 - mean)/(sigma*sigma);
	}
	return chi2;
}

// Expected order of meanpar [ zPV, dxy/dxyerr, dz/dzerr ]
void createChiSquared_tree(std::vector<float> meanpars, std::string treename, std::string filepath, std::string outfilename){
	ROOT::RDataFrame df(treename.c_str(), filepath.c_str());
	float mean = meanpars.at(0);
 	float sigma = 4.287;	
	int ntrk = 4;
	auto df2 = df
			.Define("chi2_zPV", [=](Int_t ntrk, Float_t zPV){ return calcChiSquared_eventVar(ntrk, zPV); }, {"ntrk", "zPV"})
			.Define("chi2_dxy_dxyerr", [=](Int_t ntrk, RVecF dxy, RVecF dxyerr){ return calcChiSquared<RVecF>(meanpars.at(1), ntrk, dxy, dxyerr); }, {"ntrk", "trk_dxy", "trk_dxyerr"})
		.Define("chi2_dz_dzerr", [=](Int_t ntrk, RVecF dz, RVecF dzerr){ return calcChiSquared<RVecF>(meanpars.at(2), ntrk, dz, dzerr); }, {"ntrk", "trk_dz", "trk_dzerr"})
 		.Filter([ntrk](int x) { return x==ntrk; }, {"ntrk"});

	
	auto trk4_cut = df2.Filter([ntrk](int x) { return x==ntrk; }, {"ntrk"});

	auto outfile = trk4_cut.Filter([=] (RVecF masspair){return masspair.at(0)>1e-8;}, {"inv_mass_pair1"});

	outfile.Snapshot(treename.c_str(), ("data/chi2_combined/" + outfilename + "chi2.root").c_str());

}

void create_chi2_rhoMass(float meanpar, float sigmapar, std::string filename, std::string outfilename){
	ROOT::RDataFrame df("tree", filename.c_str());
	float mean = meanpar;
	float sigma = sigmapar;
	std::cout<<mean<<std::endl;
	std::cout<<sigma<<std::endl;
	auto df2 = df.Define("chi2_rhoMass_pair1", [mean, sigma](RVecF inv_mass_pair1){ return getChi2_rhoMass(mean, sigma, inv_mass_pair1); }, {"inv_mass_pair1"})
		     .Define("chi2_rhoMass_pair2", [mean, sigma] (RVecF inv_mass_pair2){ return getChi2_rhoMass(mean, sigma, inv_mass_pair2); }, {"inv_mass_pair2"});

	df2.Snapshot("tree", ("data/chi2_combined/" + outfilename + "chi2rho.root").c_str());
}
