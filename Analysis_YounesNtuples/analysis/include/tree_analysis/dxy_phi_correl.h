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
 * @brief Return a cropped version of the input histogram between min and max x-values.
 * 
 * Creates a new histogram containing only the bins within [xmin, xmax]. 
 * Bin contents and errors are preserved.
 * 
 * @param hist Input histogram to crop.
 * @param xmin Minimum x-value for cropping.
 * @param xmax Maximum x-value for cropping.
 * @return TH1D* Newly allocated cropped histogram.
 * 
 * @note The caller is responsible for deleting the returned histogram.
 */
TH1D* CropHistogram(TH1D* hist, double xmin, double xmax);

/**
 * @brief Plot correlation between track dxy and phi, and optionally apply a Gaussian cut.
 * 
 * This function:
 * 1. Fills a 2D histogram of dxy vs. phi for 4-track events.
 * 2. Optionally fits a Gaussian to the X projection and applies a ±3σ cut.
 * 3. Saves the resulting plot to a PNG file.
 * 
 * @param tree Pointer to the input TTree with branches: trk_dxy, trk_phi, ntrk.
 * @param filebasename Base name used for labeling/saving the plot.
 * @param cut Whether to apply a Gaussian cut on the X projection.
 * 
 * @note Dynamically allocated ROOT objects (histograms, canvas) are managed internally.
 */
void dxy_phi_correl(TTree* tree, std::string filebasename, bool cut);

