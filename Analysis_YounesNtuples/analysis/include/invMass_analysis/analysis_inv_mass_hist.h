#pragma once

#include <string>
#include <vector>
#include <TH2F.h>
#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RVec.hxx>

using namespace ROOT::VecOps;
using RVecF = ROOT::RVec<float>;
using RVecI = ROOT::RVec<int>;

/// Get 2D histogram of reconstructed invariant mass from a tree
TH2F* get2D_inv_mass_hist(std::string treename, std::string filepath, std::string filename, int nbin, float min, float max);

/// Plot 2D histogram of rho mass pairs and save ROOT file
TH2F* plot_2D_rhoMass_hist(std::string filepath, std::string outname, int nbin, float min, float max);

/// Plot 2D invariant mass histogram to PNG + ROOT
void plot_2D_inv_mass_hist(TH2F* hist, const std::string filename);

/// Project 2D histogram onto X or Y axis in a range; optionally save
TH1D* getProj(TH2F* hist, float projmin, float projmax, const std::string filename, const std::string option, bool save=false);

/// Gaussian fit to invariant mass projection (iterative refinement)
TF1* gaussfit_mass(TH2F* hist, const std::string filename, const std::vector<float> initial_guess, const std::string option);

/// Overlay fits on 2D histogram projections and optionally save
void overlay_fits(TH2F* hist, TF1* gausfitx, TF1* gausfity, const std::string filename, bool saveplot=false);

/// Fit rho mass distribution with background + Gaussian signal
TF1* rhoMassFit(TH2F* hist, std::string filename, std::vector<float> initial_guess, std::string option);

