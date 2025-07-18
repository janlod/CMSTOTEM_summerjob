#pragma once

// Standard headers
#include <string>
#include <cmath>
#include <iostream>

// ROOT headers
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TF1.h"
#include "TPaveText.h"

/**
 * @brief Plots the distribution of dxy/dxyerr for 4-track events and fits a Gaussian.
 * 
 * The function loops over all events in the input tree, selects those with exactly 4 tracks,
 * and fills a histogram with dxy/dxyerr for each track. It then performs a Gaussian fit
 * and overlays the result on the histogram, with statistics printed in a TPaveText.
 * 
 * @param tree Pointer to the ROOT TTree containing "trk_dxy", "trk_dxyerr", and "ntrk" branches.
 * @param filebasename A base name for labeling and saving output plots.
 */
void dxy_dist(TTree* tree, std::string filebasename);
