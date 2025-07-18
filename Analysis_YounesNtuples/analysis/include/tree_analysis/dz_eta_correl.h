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
 * Loops over events in the tree, selects events with exactly 4 tracks, and
 * fills a 2D histogram with dz vs eta for each track. Saves the resulting
 * histogram as a PNG image.
 * 
 * @param tree Pointer to the ROOT TTree with "trk_dz", "trk_eta", and "ntrk" branches.
 * @param filebasename String used for naming the output file.
 */
void dz_eta_correl(TTree* tree, std::string filebasename);
