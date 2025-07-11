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


    int listSize = fileList.size();
    for (int ifile=0; ifile<listSize-7; ifile++){
        std::string filename = fileList.at(ifile);
        std::string filebasename = filename.erase(filename.size() - 5);

        TFile *cutfile = new TFile(("cutted_data/" + filebasename + "cutted.root").c_str(), "read");
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
    plot_rho_inv_mass("tree",("/eos/cms/store/group/phys_diffraction/CMSTotemLowPU2018/YounesNtuples/"+filename+".root").c_str(), filename, 0.13957);
    //plot_rho_inv_mass("tree",("simple_cutted_data/"+filename+"simplecut.root").c_str(), filename, 0.13957);
        }
//simpleCut("tree", "/eos/cms/store/group/phys_diffraction/CMSTotemLowPU2018/YounesNtuples/TOTEM20.root", "TOTEM20");
 

    return 0;

}
