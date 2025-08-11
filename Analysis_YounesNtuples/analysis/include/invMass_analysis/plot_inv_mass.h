#pragma once

// Standard library includes
#include <string>
#include <array>
#include <cmath>
#include <vector>

// ROOT includes
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
 * This function assumes the tracks come from a 4-body decay and reconstructs
 * the invariant mass using the provided mass hypothesis (massparam).
 * 
 * @param tree Pointer to a TTree containing branches: trk_pt, trk_eta, trk_phi, ntrk.
 * @param filebasename Name to use in the output image filename.
 * @param massparam Hypothesized particle mass (e.g., pion mass in GeV).
 */
void plot_invar_mass(TTree* tree, std::string filebasename, float massparam);

void plot_different_cuts(std::string filepath, std::string cut_option, std::vector<float> initial_kin_cuts, std::vector<float> initial_chi2cuts, float initial_rho_cut, std::vector<float> cuts, int nbins, float min, float max, std::string outpath);
