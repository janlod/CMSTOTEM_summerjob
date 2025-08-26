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
 * @brief Plot distributions of primary vertex positions with selectable options.
 *
 * Only events with exactly 4 tracks are considered.
 *
 * Options:
 *  - 1: xPV histogram
 *  - 2: yPV histogram
 *  - 3: zPV histogram with Gaussian fit and display of mean, sigma, amplitude
 *  - 4: radius = sqrt(xPV^2 + yPV^2) histogram
 *  - 12: 2D xyPV correlation plot
 *
 * The function creates and saves plots in appropriate folders depending on the option.
 *
 * @param tree Pointer to the ROOT TTree with branches: "xPV", "yPV", "zPV", and "ntrk".
 * @param filebasename Base name for output plot filenames.
 * @param option Integer selecting the type of plot to generate (1, 2, 3, 4, 12).
 */
void primVertex_dist(TTree* tree, std::string filebasename, int option);

