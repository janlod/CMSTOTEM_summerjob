#include "TMath.h"
#include "TTree.h"
#include "TF1.h"
#include "TPad.h"
#include "TH2F.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TFile.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TGraphErrors.h"
#include "TLatex.h"
#include "TLine.h"
#include "TPaveText.h"
#include "TMinuit.h"
#include "TStyle.h"
#include "TProfile.h"
#include "TVector.h"
#include "TMatrix.h"
#include "TMarker.h"
#include "TRandom3.h"
#include "TMultiGraph.h"
#include <ROOT/RDataFrame.hxx>
#include "TPaletteAxis.h"

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "math.h"
#include "math.h"
#include "stdlib.h"
#include <cstdlib>  
#include "tools.cc"
#include "cuts.cc"
#include "simplecuts.cc"
#include "dataCombiner.cc"

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
    std::cout<<files2.at(0)<<std::endl;
    combineTrees(files2, "2");

    int listSize = fileList.size();
    for (int ifile=0; ifile<listSize; ifile++){
        std::string filename = fileList.at(ifile);
        std::string filebasename = filename.erase(filename.size() - 5);

        TFile *cutfile = new TFile(("../data/cutted_data/" + filebasename + "cutted.root").c_str(), "read");
        TTree *cuttree = (TTree*)cutfile->Get("tree");


       TFile *uncutfile = new TFile(("/eos/cms/store/group/phys_diffraction/CMSTotemLowPU2018/YounesNtuples/" + filename+".root").c_str(), "read");

        TTree *uncuttree = (TTree*)uncutfile->Get("tree");
        
        // Put the analysis tool here that you want to use

        //primVertex_dist(cuttree, filebasename, 3);
        //dxy_dist(cuttree, filebasename);
        //dz_dist(cuttree, filebasename);
        //p_dist(cuttree, filebasename);
        //pt_eta_correl(cuttree, filebasename);
        //loopers_4trks(uncuttree, filebasename);
        //dxy_phi_correl(cuttree, filebasename, true);

        //cut_zPV(cuttree, filebasename);
        //cut_dzdzerr(cuttree, filebasename);
	
	//loopers_2trks(uncuttree, filebasename);

	//plot_invar_mass(cuttree, filebasename, 0.13957);

	//std::cout<<"Performing cuts on file "<<filebasename<<".root \n"<<std::endl;
	//cut_3sigma(cuttree, filebasename);
	//std::cout<<"\n\n\n";
   // simpleCut("tree", ("/eos/cms/store/group/phys_diffraction/CMSTotemLowPU2018/YounesNtuples/"+filename+".root").c_str(), filename);
    //plot_rho_inv_mass("tree",("../data/simple_cutted_data/"+filename+"simplecut.root").c_str(), filename, 0.13957);
   
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
 

    return 0;

}
