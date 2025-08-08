#include "include/tree_analysis/dxy_phi_correl.h"
#include "include/tree_analysis/dxy_sigmadxy.h"
#include "include/tree_analysis/dz_eta_correl.h"
#include "include/tree_analysis/dz_sigmadz.h"
#include "include/tree_analysis/loopers.h"
#include "include/tree_analysis/momentum_dist.h"
#include "include/tree_analysis/primVertex.h"
#include "include/tree_analysis/pt_eta_correl.h"
#include "include/tree_analysis/plot_chi2.h"
#include "include/tree_analysis/plotting.h"
#include "include/tree_analysis/four_trk_invMass_reco.h"
#include "include/tree_analysis/find_optimal_cutoff.h"

#include "include/invMass_analysis/analysis_inv_mass_hist.h"
#include "include/invMass_analysis/plot_inv_mass.h"

#include "include/data_manipulation/complicated_cuts.h"
#include "include/data_manipulation/dataCombiner.h"
#include "include/data_manipulation/inv_mass.h"
#include "include/data_manipulation/simplecuts.h"
#include "include/data_manipulation/create_chiSquared_tree.h"
#include "include/data_manipulation/find_correct_masspair.h"

#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;


int main(){

	float meanzPV_t2 = -0.291125;
	float meanzPV_t4 = -0.313448;
	float meandxy_sigmadxy_t2 = 0.0016423;
	float meandz_sigmadz_t2 = -0.000467749;
	float meandxy_sigmadxy_t4 = -0.00147728;
	float meandz_sigmadz_t4 = 4.27172e-05;//Fit says 0.00018


	std::vector<float> means_t2 = {meanzPV_t2, meandxy_sigmadxy_t2, meandz_sigmadz_t2};
	std::vector<float> means_t4 = {meanzPV_t4, meandxy_sigmadxy_t4, meandz_sigmadz_t4};

	//createChiSquared_tree(means_t4, "tree", fpTOTEM4, "TOTEM4_new");
	//createChiSquared_tree(means_t2, "tree", fpTOTEM2, "TOTEM2_new");

	



	
	auto fpTOTEM2 = "/eos/user/j/jloder/private/CMSTOTEM_summerjob/Analysis_YounesNtuples/analysis/data/chi2_combined/TOTEM2chi2rho.root";
	auto fpTOTEM4 = "/eos/user/j/jloder/private/CMSTOTEM_summerjob/Analysis_YounesNtuples/analysis/data/chi2_combined/TOTEM4chi2rho.root";

	auto fpTOTEM2corr = "/eos/user/j/jloder/private/CMSTOTEM_summerjob/Analysis_YounesNtuples/analysis/data/chi2_combined/TOTEM2cw.root";
	auto fpTOTEM4corr = "/eos/user/j/jloder/private/CMSTOTEM_summerjob/Analysis_YounesNtuples/analysis/data/chi2_combined/TOTEM4cw.root";

	
	//create_correct_massBranch(fpTOTEM4, "TOTEM4cw");

	auto fpTOTEM2_cut ="/eos/user/j/jloder/private/CMSTOTEM_summerjob/Analysis_YounesNtuples/analysis/data/simple_cutted_data/TOTEM2corr_eta15.root";
	auto fpTOTEM4_cut ="/eos/user/j/jloder/private/CMSTOTEM_summerjob/Analysis_YounesNtuples/analysis/data/simple_cutted_data/TOTEM4corr_eta15.root";
	
	auto outpath = "/eos/user/j/jloder/private/CMSTOTEM_summerjob/Analysis_YounesNtuples/analysis/plots/temp/TOTEM4cw_cut30_corrPair.root";

	
	//cutChi2("tree", "/eos/user/j/jloder/private/CMSTOTEM_summerjob/Analysis_YounesNtuples/analysis/data/chi2_combined/TOTEM2cw.root", "TOTEM2cw_cut30", cutoffs);	

	//plot2D_masspairs(true, "data/simple_cutted_data/TOTEM4cw_cut30.root", outpath, 600, 300, 1200);
		
	
	//cut_rhoMassChi2("/eos/user/j/jloder/private/CMSTOTEM_summerjob/Analysis_YounesNtuples/analysis/data/simple_cutted_data/TOTEM2cw_cut30.root", 20.,"TOTEM2cw_cut30_rho20");


	//TH2F* hist = get2D_inv_mass_hist("tree", "data/simple_cutted_data/TOTEM4cw_cut30.root", "TOTEM4cw_cut30_rho20", 600, 300, 1200);

	std::vector<float> chi2cutoffs = { 9, 12, 12};
	// Format: {pt_min, pt_max, eta_max, zPV_max, dxy_max, dz_max, dxydxyerr_max, dzdzerr_max}
	std::vector<float> kin_cuts = {0.0, 0.8, 1.5, 1e2, 1e2, 1e2, 1e2, 1e2};
	float rhocut = 20;

	//simpleCut(kin_cuts, "data/chi2_combined/TOTEM2cw.root","TOTEM2cw_simplecut");
	//cutChi2("tree", "data/4trk_invMass/TOTEM2cw_simplecut.root", "TOTEM2cw_simplecut_chi2cut", chi2cutoffs);	
	//cut_rhoMassChi2("data/4trk_invMass/TOTEM2cw_simplecut_chi2cut.root", rhocut,"TOTEM2cw_simplecut_chi2cut_rhocut");
	//TH1F* four_trk_invMass = get_4trk_invMass("data/4trk_invMass/TOTEM2cw_simplecut_chi2cut_rhocut.root", "plots/4trk_invMass/TOT2cw_temp.root", 300, 1000, 3000);
	
	std::vector<float> rhoWindow = {687.693, 811.995};
	std::vector<float> kaonWindow = {486.616, 509.114};
	std::pair<TH1F*, TH1F*> pdfs;
	pdfs = plot_chi2_inWindow("data/chi2_combined/TOTEM4cw.root", "plots/temp/chi2dxytest.root","chi2_dxy_dxyerr", rhoWindow, kaonWindow, 150, 0, 150);
	
	TH1F* bg = pdfs.first;
	TH1F* sg = pdfs.second;

	float perfect_cut = get_chi2Cutoff(bg, sg, 0.5);

	return 0;

}
