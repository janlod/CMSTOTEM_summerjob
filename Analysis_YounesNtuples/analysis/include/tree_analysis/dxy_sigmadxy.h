#pragma once

#include <string>
#include <cmath>
#include <iostream>
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TF1.h"
#include "TPaveText.h"

/**
 * @brief Plot the distribution of dxy normalized by its uncertainty (dxy/dxyerr) for 4-track events.
 * 
 * This function loops over all events in the input TTree, selects events with exactly 4 tracks,
 * and fills a histogram with dxy/dxyerr for each track. It performs a Gaussian fit in the range [-1,1],
 * overlays the fit on the histogram, and shows the fit parameters in a TPaveText box.
 * 
 * @param tree Pointer to a TTree containing branches "trk_dxy", "trk_dxyerr", and "ntrk".
 * @param filebasename Base name used for labeling and saving the output PNG plot.
 */
void dxy_dist(TTree* tree, std::string filebasename);

