#pragma once

// Standard headers
#include <string>
#include <iostream>

// ROOT headers
#include "TTree.h"
#include "TCanvas.h"
#include "TH2F.h"

/**
 * @brief Plots the 2D correlation between dz and eta for 4-track events.
 * 
 * This function:
 * 1. Loops over all entries in the provided TTree.
 * 2. Selects events containing exactly 4 tracks.
 * 3. Fills a 2D histogram of dz vs eta for each track.
 * 4. Saves the histogram as a PNG file with a name based on `filebasename`.
 * 
 * @param tree Pointer to the ROOT TTree containing branches "trk_dz", "trk_eta", and "ntrk".
 * @param filebasename Base name used for saving the output PNG.
 * 
 * @note Dynamically allocated ROOT objects (TH2F and TCanvas) are deleted internally.
 */
void dz_eta_correl(TTree* tree, std::string filebasename);

