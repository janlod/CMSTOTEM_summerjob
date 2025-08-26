#pragma once

#include <string>
#include <iostream>
#include "TTree.h"
#include "TCanvas.h"
#include "TH2F.h"

/**
 * @brief Plot 2D correlation histogram of track transverse momentum (pt) vs pseudorapidity (eta).
 * 
 * Only events with exactly 4 tracks are considered.
 * 
 * @param tree Pointer to the TTree containing branches "trk_pt", "trk_eta", and "ntrk".
 * @param filebasename Base name for saving the output plot file.
 */
void pt_eta_correl(TTree* tree, std::string filebasename);

