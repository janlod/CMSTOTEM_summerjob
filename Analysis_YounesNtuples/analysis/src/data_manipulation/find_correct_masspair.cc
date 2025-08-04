#include "data_manipulation/find_correct_masspair.h"

RVecF get_correct_massPair(RVecF pair1, RVecF pair2, float chi2_pair1, float chi2_pair2){
	if(chi2_pair1 < chi2_pair2){
		return pair1;
	}else{
		return pair2;
	}
}



RVecF get_wrong_massPair(RVecF pair1, RVecF pair2, float chi2_pair1, float chi2_pair2){
	if(chi2_pair1 > chi2_pair2){
		return pair1;
	}else{
		return pair2;
	}
}
void create_correct_massBranch(std::string filepath, std::string outname){
	ROOT::RDataFrame df("tree", filepath.c_str());
	
	auto df2 = df.Define("correct_massPair", [=](RVecF pair1, RVecF pair2, float chi2_pair1, float chi2_pair2){ return get_correct_massPair(pair1, pair2, chi2_pair1, chi2_pair2); }, {"inv_mass_pair1", "inv_mass_pair2", "chi2_rhoMass_pair1", "chi2_rhoMass_pair2"})
		     .Define("chi2_diff", [=](float chi2_p1, float chi2_p2){ return chi2_p1-chi2_p2; }, {"chi2_rhoMass_pair1", "chi2_rhoMass_pair2"})
		     .Define("wrong_massPair", [=](RVecF pair1, RVecF pair2, float chi2_pair1, float chi2_pair2){ return get_wrong_massPair(pair1, pair2, chi2_pair1, chi2_pair2); }, {"inv_mass_pair1", "inv_mass_pair2", "chi2_rhoMass_pair1", "chi2_rhoMass_pair2"});			


	df2.Snapshot("tree", ("data/chi2_combined/"+outname+".root").c_str());	
}
