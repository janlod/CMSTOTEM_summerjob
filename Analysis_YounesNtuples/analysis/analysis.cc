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
        TFile *rootfile = new TFile(("/eos/cms/store/group/phys_diffraction/CMSTotemLowPU2018/YounesNtuples/" + filename).c_str(), "read");
        TTree *tree = (TTree*)rootfile->Get("tree");

        std::string filebasename = filename.erase(filename.size() - 5);
        
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
        cutZPV(tree, filebasename);
        }
    }


int main() {
    analysis();
    return 0;
}

