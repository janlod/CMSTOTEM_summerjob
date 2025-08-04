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

	std::vector<float> cutoffs = { 30., 30., 30. };
	



	//cut_rhoMassChi2("/eos/user/j/jloder/private/CMSTOTEM_summerjob/Analysis_YounesNtuples/analysis/data/simple_cutted_data/TOTEM2_corr_cut40.root", 10.,"TOTEM2_corr_cut40_rho10");
	
	auto fpTOTEM2 = "/eos/user/j/jloder/private/CMSTOTEM_summerjob/Analysis_YounesNtuples/analysis/data/chi2_combined/TOTEM2chi2rho.root";
	auto fpTOTEM4 = "/eos/user/j/jloder/private/CMSTOTEM_summerjob/Analysis_YounesNtuples/analysis/data/chi2_combined/TOTEM4chi2rho.root";

	auto fpTOTEM2corr = "/eos/user/j/jloder/private/CMSTOTEM_summerjob/Analysis_YounesNtuples/analysis/data/chi2_combined/TOTEM2cw.root";
	auto fpTOTEM4corr = "/eos/user/j/jloder/private/CMSTOTEM_summerjob/Analysis_YounesNtuples/analysis/data/chi2_combined/TOTEM4cw.root";

	
	//create_correct_massBranch(fpTOTEM4, "TOTEM4cw");

	auto fpTOTEM2_cut ="/eos/user/j/jloder/private/CMSTOTEM_summerjob/Analysis_YounesNtuples/analysis/data/simple_cutted_data/TOTEM2corr_eta15.root";
	auto fpTOTEM4_cut ="/eos/user/j/jloder/private/CMSTOTEM_summerjob/Analysis_YounesNtuples/analysis/data/simple_cutted_data/TOTEM4corr_eta15.root";
	
	auto outpath = "/eos/user/j/jloder/private/CMSTOTEM_summerjob/Analysis_YounesNtuples/analysis/plots/temp/TOTEM2cw_cut30_wrongPair.root";

	
	//cutChi2("tree", "/eos/user/j/jloder/private/CMSTOTEM_summerjob/Analysis_YounesNtuples/analysis/data/chi2_combined/TOTEM2cw.root", "TOTEM2cw_cut30", cutoffs);	

	//TH2F* hist = get2D_inv_mass_hist("tree", fpTOTEM2corr, "TOT2 eta cut", 600, 300, 1200);
	plot2D_masspairs(false, "data/simple_cutted_data/TOTEM2cw_cut30.root", outpath, 600, 300, 1200);
		return 0;

}
