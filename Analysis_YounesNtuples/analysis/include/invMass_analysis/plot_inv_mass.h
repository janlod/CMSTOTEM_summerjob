#pragma once

#include <string>
#include <array>
#include <vector>
#include <cmath>

#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TLine.h"
#include "TLegend.h"
#include "TFile.h"

#include "../tree_analysis/four_trk_invMass_reco.h"
#include "../data_manipulation/simplecuts.h"

/**
 * @brief Plot the invariant mass of 4-track combinations assuming a common mass.
 *
 * Reconstructs the invariant mass using the provided mass hypothesis (massparam),
 * drawing a vertical reference line at 2220 MeV.
 *
 * @param tree Pointer to a TTree containing branches: trk_pt, trk_eta, trk_phi, ntrk.
 * @param filebasename Name to use in the output image filename.
 * @param massparam Hypothesized particle mass (e.g., pion mass in GeV).
 */
void plot_invar_mass(TTree* tree, std::string filebasename, float massparam);

/**
 * @brief Plot histograms after applying various cuts (pt, eta, dxy, chi2, rho).
 *
 * Loops over the cuts vector and draws each histogram on the same canvas with different colors.
 *
 * @param filepath Path to the ROOT file with initial data.
 * @param cut_option Cut type: "pt", "eta", "dxy", "chi2", or "rho".
 * @param initial_kin_cuts Initial kinematic cuts to apply.
 * @param initial_chi2cuts Initial chi2 cuts to apply.
 * @param initial_rho_cut Initial rho cut to apply.
 * @param cuts Vector of cut thresholds to scan.
 * @param nbins Number of histogram bins.
 * @param min Minimum histogram value.
 * @param max Maximum histogram value.
 * @param outpath Path to save the resulting combined histogram canvas.
 */
void plot_different_cuts(std::string filepath, std::string cut_option, 
                         std::vector<float> initial_kin_cuts, 
                         std::vector<float> initial_chi2cuts, 
                         float initial_rho_cut, std::vector<float> cuts, 
                         int nbins, float min, float max, std::string outpath);

