#include "include/tree_analysis/dxy_phi_correl.h"
#include "include/tree_analysis/dxy_sigmadxy.h"
#include "include/tree_analysis/dz_eta_correl.h"
#include "include/tree_analysis/dz_sigmadz.h"
#include "include/tree_analysis/loopers.h"
#include "include/tree_analysis/momentum_dist.h"
#include "include/tree_analysis/primVertex.h"
#include "include/tree_analysis/pt_eta_correl.h"
#include "include/tree_analysis/plot_chi2.h"

#include "include/invMass_analysis/analysis_inv_mass_hist.h"
#include "include/invMass_analysis/plot_inv_mass.h"

#include "include/data_manipulation/complicated_cuts.h"
#include "include/data_manipulation/dataCombiner.h"
#include "include/data_manipulation/inv_mass.h"
#include "include/data_manipulation/simplecuts.h"
#include "include/data_manipulation/create_chiSquared_tree.h"

#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;


int main(){

    //First we read in all filenames from a text file to a list to loop over them
    std::string line;
    std::ifstream file;
    std::vector<std::string> fileList;
    file.open("dataFileList.txt");
    if(file.is_open()){
        while (getline(file, line)){
            fileList.push_back(line);
        }
        file.close();
    }

    std::string folderpath = "../data/inv_mass_data/"; 
    std::vector<std::string> files2 = { "TOTEM20.root", "TOTEM21.root", "TOTEM22.root", "TOTEM23.root" };
    std::vector<std::string> files4 = { "TOTEM40.root", "TOTEM41.root", "TOTEM42.root", "TOTEM43.root" };
    for(std::string& file : files2){
    	file = folderpath + file;
    }

    for(std::string& file : files4){
    	file = folderpath + file;
    }
    //std::cout<<files2.at(0)<<std::endl;
    //combineTrees(files2, "2");

    int listSize = fileList.size();
    for (int ifile=0; ifile<listSize; ifile++){
        std::string filename = fileList.at(ifile);
        std::string filebasename = filename.erase(filename.size() - 5);

	//add_inv_massBranches("tree", ("/eos/cms/store/group/phys_diffraction/CMSTotemLowPU2018/YounesNtuples/"+filename+".root").c_str(), filename, 0.13957);	

	//TH2F* inv_mass_hist2D = get2D_inv_mass_hist("tree",("../data/inv_mass_data/"+filename + ".root").c_str(), filename, 400, 300, 1200);
	//plot_2D_inv_mass_hist(inv_mass_hist2D, filename);
	//TH1D* projx = getProj(inv_mass_hist2D, 300, 1200, filename, "x");	
	//TH1D* projy = getProj(inv_mass_hist2D, 300, 1200, filename, "y");
	
	//std::array<float, 3> gauss_guess = {1000, 500, 20};
	//gaussfit_kaon_mass(inv_mass_hist2D, filename, gauss_guess, "y");
	//gaussfit_kaon_mass(inv_mass_hist2D, filename, gauss_guess, "x");

       	
    }
	//simpleCut("tree", "/eos/cms/store/group/phys_diffraction/CMSTotemLowPU2018/YounesNtuples/TOTEM20.root", "TOTEM20");


   	

	auto testfilepath = "/eos/user/j/jloder/private/CMSTOTEM_summerjob/Analysis_YounesNtuples/analysis/data/cutted_data/TOTEM20cutted.root";
	auto fpTOTEM2 = "/eos/user/j/jloder/private/CMSTOTEM_summerjob/Analysis_YounesNtuples/analysis/data/combined/TOTEM2.root";
	auto fpTOTEM4 = "/eos/user/j/jloder/private/CMSTOTEM_summerjob/Analysis_YounesNtuples/analysis/data/combined/TOTEM4.root";

	auto fpTOTEM20 = "/eos/cms/store/group/phys_diffraction/CMSTotemLowPU2018/YounesNtuples/TOTEM20.root";
	
	TFile* tot2 = new TFile(fpTOTEM2, "READ");
	TFile* tot4 = new TFile(fpTOTEM4, "READ");

	TTree* treetot2 = (TTree*)tot2->Get("tree");
	TTree* treetot4 = (TTree*)tot4->Get("tree");



	float meanzPV_t2 = -0.291125;
	float meanzPV_t4 = -0.313448;
	float meandxy_sigmadxy_t2 = 0.0016423;
	float meandz_sigmadz_t2 = -0.000467749;
	float meandxy_sigmadxy_t4 = -0.00147728;
	float meandz_sigmadz_t4 = 4.27172e-05;//Fit says 0.00018


	std::vector<float> means_t2 = {meanzPV_t2, meandxy_sigmadxy_t2, meandz_sigmadz_t2};
	std::vector<float> means_t4 = {meanzPV_t4, meandxy_sigmadxy_t4, meandz_sigmadz_t4};

//	std::vector<float> cutoffs = { 30., 30., 30. };
	
	std::vector<std::vector<float>> cutoffs_list;
	for(int i=1; i<10; i++){
		cutoffs_list.push_back({10.0*i, 10.0*i, 10.0*i});
	}
	

	
	auto fp_chi2_TOTEM2_cut30 = "/eos/user/j/jloder/private/CMSTOTEM_summerjob/Analysis_YounesNtuples/analysis/data/chi2_combined/TOTEM2chi2cut30.root";
	
	auto fp_chi2_TOTEM2 = "/eos/user/j/jloder/private/CMSTOTEM_summerjob/Analysis_YounesNtuples/analysis/data/chi2_combined/TOTEM2chi2.root";
	auto fp_chi2_TOTEM4 = "/eos/user/j/jloder/private/CMSTOTEM_summerjob/Analysis_YounesNtuples/analysis/data/chi2_combined/TOTEM4chi2.root";
	

	TH2F* tot2chi30 = get2D_inv_mass_hist("tree",fp_chi2_TOTEM2_cut30, "TOT2_cut30", 600, 300, 1200);
	
	std::vector<float> guessx = {2500., 750., 50., 100.};
	std::vector<float> guessy = {3500., 750., 50., 100.};
	
	TF1* gausfit2x = gaussfit_mass(tot2chi30, "testfit", guessx, "x");
	TF1* gausfit2y = gaussfit_mass(tot2chi30, "testfit", guessy, "y");
	
	overlay_fits(tot2chi30, gausfit2x, gausfit2y, "TOTEM2chi2cut");
	//overlay_fits(inv_mass_TOTEM4, gausfit4x, gausfit4y, "TOTEM4");


    return 0;

}
