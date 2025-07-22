#pragma once

#include <string>
#include <TCanvas.h>
#include <TFile.h>
#include <ROOT/RDataFrame.hxx>


void plot_chi2(std::string branchname, std::string treename, std::string filepath, std::string outfilename, int nbin, float minbin, float maxbin);
