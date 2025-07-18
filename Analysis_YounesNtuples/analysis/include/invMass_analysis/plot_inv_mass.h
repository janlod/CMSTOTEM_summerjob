#pragma once

// Standard library includes
#include <string>
#include <array>
#include <cmath>

// ROOT includes
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TLine.h"

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
