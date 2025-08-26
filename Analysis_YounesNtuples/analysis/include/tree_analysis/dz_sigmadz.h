#pragma once

#include <string>
#include <iostream>
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TF1.h"
#include "TPaveText.h"

/**
 * @brief Plot the distribution of dz normalized by its uncertainty (dz/dzerr) for 4-track events.
 * 
 * This function loops over all events in the input TTree, selects events with exactly 4 tracks,
 * and fills a histogram with dz/dzerr for each track. It performs a Gaussian fit in the range [-0.5, 0.5],
 * overlays the fit on the histogram, and shows the fit parameters in a TPaveText box.
 * 
 * @param tree Pointer to a TTree containing branches "trk_dz", "trk_dzerr", and "ntrk".
 * @param filebasename Base name for labeling and saving the output PNG plot.
 */
void dz_dist(TTree* tree, std::string filebasename);

