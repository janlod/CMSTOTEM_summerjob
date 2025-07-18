#pragma once  // Or use traditional include guards

#include <string>
#include <array>
#include <map>
#include <iostream>
#include <cmath>

// ROOT includes
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TAxis.h"
#include "TPaveText.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TMath.h"

// Function declarations
void cut_zPV(TTree* tree, std::string filebasename);
void cut_dzdzerr(TTree* tree, std::string filebasename);
bool isin_3sigma(Float_t val, std::array<double,3> fitparams);

TH1F* get1D_hist_eventvar(TTree* tree, std::string svar, float nbin, float minbin, float maxbin);
TH1F* get1D_hist_trkvar(TTree* tree, std::string svar, std::string svarerr, int nbin, float minbin, float maxbin);
TH2F* get2D_hist(TTree* tree, std::string svarX, std::string svarY, int nbinX, float minbinX, float maxbinX, float nbinY, float minbinY, float maxbinY);

std::array<double,3> fitParams1D_gausfit(TH1F* hist, float fitrangeMin, float fitrangeMax);
std::map<int, std::array<double, 3>> fitParams2D_gausfit_allSlices(TH2F* hist, float fitrangeMin, float fitrangeMax);

void cut_3sigma(TTree* tree, std::string filebasename);
void quick2Dplot(std::string filename, std::string svarX, std::string svarY, int nbinX, float minbinX, float maxbinX, float nbinY, float minbinY, float maxbinY);
void quick1Dplot(std::string filename, std::string svar, std::string svarerr, int nbin, float minbin, float maxbin, int trkvar);
