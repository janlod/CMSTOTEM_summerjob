#pragma once

#include <string>
#include <TCanvas.h>
#include <TFile.h>
#include <TLegend.h>
#include <ROOT/RDataFrame.hxx>
#include <vector>
#include <ROOT/RVec.hxx>

using namespace ROOT::VecOps;
using RVecF = ROOT::RVec<float>;


void plot_chi2(std::string branchname, std::string treename, std::string filepath, std::string outfilename, int nbin, float minbin, float maxbin);


std::pair<TH1F*, TH1F*> plot_chi2_inWindow(std::string filepath, std::string outpath, std::string chi2_branch, std::vector<float> x_massWindow, std::vector<float> y_massWindow, int nbins, float plotmin, float plotmax);
