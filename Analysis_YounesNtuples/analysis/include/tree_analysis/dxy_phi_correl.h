#pragma once

// Standard C++ headers
#include <string>
#include <cmath>
#include <iostream>

// ROOT headers
#include "TTree.h"
#include "TCanvas.h"
#include "TH2F.h"
#include "TH1D.h"
#include "TF1.h"

/**
 * @brief Plot correlation between track dxy and phi, and optionally apply a Gaussian cut.
 * 
 * This function fills a 2D histogram of dxy vs. phi for tracks from 4-track events.
 * If `cut == true`, it fits a Gaussian to the X projection and applies a ±3σ cut,
 * showing the cut histogram.
 * 
 * @param tree Pointer to the input TTree with branches: trk_dxy, trk_phi, ntrk.
 * @param filebasename Name used for labeling the plot.
 * @param cut Whether to apply a Gaussian cut on the X projection.
 */
void dxy_phi_correl(TTree* tree, std::string filebasename, bool cut);

/**
 * @brief Return a cropped version of the input histogram between min and max x-values.
 * 
 * This utility function should be implemented elsewhere.
 * 
 * @param hist Input histogram to crop.
 * @param xmin Minimum x-value for cropping.
 * @param xmax Maximum x-value for cropping.
 * @return Cropped TH1D* histogram (newly allocated).
 */
TH1D* CropHistogram(TH1D* hist, double xmin, double xmax);

 
