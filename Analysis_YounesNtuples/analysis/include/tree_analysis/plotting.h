#pragma once

#include <ROOT/RDataFrame.hxx>   
#include <TCanvas.h>             
#include <TH1F.h>                
#include <TH2F.h>                
#include <TFile.h>               
#include <TString.h>             
#include <TROOT.h>               
#include <ROOT/RVec.hxx>

#include <string>                
#include <vector>                
#include <iostream>
#include <cmath>              

using RVecF = ROOT::RVec<float>;

void plot2D_correl_eventvar(std::string filepath, std::string outpath, std::string xbranch, std::string ybranch, int xnbins, int ynbins, float xmin, float ymin, float xmax, float ymax, bool logscale=false);


void plot2D_masspairs(bool correct, std::string filepath, std::string outpath, int nbins, float min, float max, bool logscale=true);

void plot1D_eventvar(std::string filepath, std::string outpath, std::string branch, int nbins, float min, float max, bool logscale=false);

	
void plot2D_correl_trkp_prp(std::string filepath, std::string outpath, std::string direction, int xnbins, int ynbins, float xmin, float ymin, float xmax, float ymax, bool logscale=false);

void plot2D_correl_trkvars(std::string filepath, std::string outpath, std::string xbranch, std::string ybranch, int xnbins, int ynbins, float xmin, float ymin, float xmax, float ymax, bool logscale=true);

void plot1D_trkvar(std::string filepath, std::string outpath, std::string branch, int nbins, float min, float max, bool logscale=false);
	
	
