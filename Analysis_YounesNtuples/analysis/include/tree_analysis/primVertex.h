#pragma once

#include <string>
#include <iostream>
#include <cmath>
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include "TPaveText.h"
#include "TMath.h"

/**
 * @brief Plot distributions of primary vertex positions with various options.
 * 
 * Depending on the option parameter, plots histograms for:
 *  - 1: xPV distribution
 *  - 2: yPV distribution
 *  - 3: zPV distribution with Gaussian fit
 *  - 4: radius = sqrt(xPV^2 + yPV^2)
 *  - 12: 2D xyPV distribution
 * 
 * Only events with exactly 4 tracks are considered.
 * 
 * @param tree Pointer to a TTree containing branches "xPV", "yPV", "zPV", and "ntrk".
 * @param filebasename Base name for the output plot filenames.
 * @param option Plot option as described above.
 */
void primVertex_dist(TTree* tree, std::string filebasename, int option);
