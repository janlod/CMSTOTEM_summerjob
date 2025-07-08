#include "TMath.h"
#include "TTree.h"
#include "TF1.h"
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
#include "tools.cc"
#include "cuts.cc"



namespace fs = std::filesystem;

void analysis(){

    //Reading in filenames from dataList.txt
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
    for (int ifile=0; ifile<listSize; ifile++){
        std::string filename = fileList.at(ifile);
        std::string filebasename = filename.erase(filename.size() - 5);

        TFile *cutfile = new TFile(("cutted_data/" + filebasename + "cutted.root").c_str(), "read");
        TTree *cuttree = (TTree*)cutfile->Get("tree");


       TFile *uncutfile = new TFile(("/eos/cms/store/group/phys_diffraction/CMSTotemLowPU2018/YounesNtuples/" + filename+".root").c_str(), "read");

        TTree *uncuttree = (TTree*)uncutfile->Get("tree");
        
        // Put the analysis tool here that you want to use

        //primVertex_dist(tree, filebasename, 3);
        //dxy_dist(tree, filebasename);
        //dz_dist(tree, filebasename);
        //p_dist(tree, filebasename);
        //loopers_2trks(tree, filebasename);
        //pt_eta_correl(tree, filebasename);
        //loopers_4trks(tree, filebasename);
        //dxy_phi_correl(tree, filebasename, true);
        //loopers_4trks(tree, filebasename);
        //loopers_2trks(tree, filebasename);

        //cut_zPV(tree, filebasename);
        //cut_dzdzerr(tree, filebasename);
	cut_3sigma(tree, filebasename);
	

	//plot_invar_mass(tree, filebasename, 139.57);

	//plot_invar_mass(tree, filebasename, 0.13957);

	//std::cout<<"Performing cuts on file "<<filebasename<<".root \n"<<std::endl;
	//cut_3sigma(tree, filebasename);
	//std::cout<<"\n\n\n";
        }
    }


int main() {
   analysis();//BREAKPOINT
    
  // quick2Dplot("TOTEM20cutted.root", "trk_dxy", "trk_phi", 400, -0.3, 0.3, 400, -3.0, 3.0);

 // quick1Dplot("TOTEM20cutted.root", "zPV", "trk_dzerr", 400, -15,15, 0);

    return 0;
}

