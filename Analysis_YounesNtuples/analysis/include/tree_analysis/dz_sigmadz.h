#pragma once

// Standard headers
#include <string>
#include <iostream>

// ROOT headers
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TF1.h"
#include "TPaveText.h"

/**
 * @brief Creates a histogram of dz/dzerr for events with exactly 4 tracks.
 * 
 * The function fits a Gaussian to the dz/dzerr distribution and annotates
 * the result on the histogram. The final plot is saved as a PNG.
 * 
 * @param tree Pointer to the TTree containing the branches: "trk_dz", "trk_dzerr", and "ntrk".
 * @param filebasename Base name for the output file (without extension).
 */
void dz_dist(TTree* tree, std::string filebasename);
