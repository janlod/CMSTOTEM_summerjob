#include "data_manipulation/simplecuts.h"

using RVecF = ROOT::VecOps::RVec<float>;


bool all4Good(RVecF trks, float cutvalue){
	int goodtrks = 0;
	for(Float_t value : trks){
		if(abs(value) < cutvalue){
			goodtrks++;
		}
	}

	return goodtrks==4;
}



void simpleCut(std::vector<float> cuts, std::string fileloc, std::string outname){
	auto file = fileloc.c_str();

	ROOT::RDataFrame df("tree", file);

	int ntrk = 4;	
	float pt_min = cuts.at(0);
	float pt_max = cuts.at(1);
	float eta_max = cuts.at(2);  //1.5
	float zPV_max = cuts.at(3); //13
	float dxy_max = cuts.at(4); //0.09
	float dz_max = cuts.at(5); // 0.65
	float dxydxyerr_max = cuts.at(6); //2.5
	float dzdzerr_max = cuts.at(7); //1.2


	auto trk4_cut = df.Filter([ntrk](int x) { return x==ntrk; }, {"ntrk"});
	
	auto zPV_cut = trk4_cut.Filter([zPV_max](float x) { return abs(x)<zPV_max; }, {"zPV"});

	auto pt_cut = zPV_cut.Filter([pt_min, pt_max](float x) { return abs(x) >= pt_min && abs(x) <= pt_max; }, {"alltrk_pt"});
	
	auto eta_cut = pt_cut.Filter([eta_max](RVecF x){ return all4Good(x, eta_max); }, {"trk_eta"});

	auto dxy_cut = eta_cut.Filter([dxy_max](RVecF x){ return all4Good(x, dxy_max); }, {"trk_dxy"});
	
	auto dz_cut = dxy_cut.Filter([dz_max](RVecF x){ return all4Good(x, dz_max); }, {"trk_dz"});

	auto dxydxyerr_cut = dz_cut.Filter([dxydxyerr_max](RVecF x, RVecF xerr){ 
		     		RVecF dxdxerr {};
		       		for(size_t i=0; i<x.size(); i++){
					dxdxerr.push_back(x.at(i)/xerr.at(i));						      	
				}
			return all4Good(dxdxerr, dxydxyerr_max); }, {"trk_dxy", "trk_dxyerr"});
	
	auto dzdzerr_cut = dxydxyerr_cut.Filter([dzdzerr_max](RVecF x, RVecF xerr){ 
		     		RVecF dxdxerr {};
		       		for(size_t i=0; i<x.size(); i++){
					dxdxerr.push_back(x.at(i)/xerr.at(i));						      	
				}
			return all4Good(dxdxerr, dzdzerr_max); }, {"trk_dz", "trk_dzerr"});

	dzdzerr_cut.Snapshot("tree", ("data/4trk_invMass/"+outname+".root").c_str());

}


void cut_badChargeTrks(std::string filepath, std::string outfilename){
	ROOT::RDataFrame df("tree", filepath.c_str());
	
	auto df2 = df.Filter([=](RVecF rhopair1){ return rhopair1.at(0)>1e-8; }, {"inv_mass_pair1"});
	df2.Snapshot("tree", ("data/chi2_combined/"+outfilename+".root").c_str());
}

// cutoffs expected in order [zPV, dxy_dxyerr, dz_dzerr]
void cutChi2(std::string treename, std::string filepath, std::string outfilename, std::vector<float> cutoffs){
	ROOT::RDataFrame df(treename.c_str(), filepath.c_str());
	
	float chi2cut_zPV = cutoffs.at(0);
	float chi2cut_dxy_dxyerr = cutoffs.at(1);
	float chi2cut_dz_dzerr = cutoffs.at(2);	

	auto zPV_cut = df.Filter([chi2cut_zPV](float x) { return x<chi2cut_zPV; }, {"chi2_zPV"});
	auto dxy_dxyerr_cut = zPV_cut.Filter([chi2cut_dxy_dxyerr](float x) { return x<chi2cut_dxy_dxyerr; }, {"chi2_dxy_dxyerr"});
	auto dz_dzerr_cut = dxy_dxyerr_cut.Filter([chi2cut_dz_dzerr](float x) { return x<chi2cut_dz_dzerr; }, {"chi2_dz_dzerr"});

	dz_dzerr_cut.Snapshot("tree", ("data/4trk_invMass/"+outfilename+".root").c_str());
}

void cut_rhoMassChi2(std::string filepath, float cutoff, std::string outname){
	ROOT::RDataFrame df("tree", filepath);
	
	auto cutted = df.Filter([=](float x) { return x<cutoff; }, {"chi2_rhoMass_pair1"})
			.Filter([=](float y) { return y<cutoff; }, {"chi2_rhoMass_pair2"});

	cutted.Snapshot("tree", ("data/4trk_invMass/" + outname + ".root").c_str());
}



