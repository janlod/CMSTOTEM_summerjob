#pragma once

#include <ROOT/RDataFrame.hxx>   
#include <TCanvas.h>             
#include <TH1F.h>                
#include <TH2F.h>                
#include <TFile.h>               
#include <TString.h>             
#include <TROOT.h>               

#include <string>                
#include <vector>                
#include <iostream>              



void plot2D_correl_eventvar(std::string filepath, std::string outpath, std::string xbranch, std::string ybranch, int xnbins, int ynbins, float xmin, float ymin, float xmax, float ymax, bool logscale=false);


void plot1D_eventvar(std::string filepath, std::string outpath, std::string branch, int nbins, float min, float max, bool logscale=false);
	
	
	
