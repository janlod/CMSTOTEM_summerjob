#pragma once

// Standard headers
#include <string>
#include <vector>
#include <iostream>
#include <cmath>

// ROOT headers
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TLegend.h"

/**
 * @brief Analyze events with 5 tracks and plot six different pion pair momentum combinations.
 * 
 * This function forms charged particle pairs from 5-track events and fills histograms 
 * of the combined momentum divided by pion mass. Six pairings are considered, each drawn and saved in a combined plot.
 * 
 * @param tree Pointer to TTree with branches: "trk_p", "trk_q", "ntrk".
 * @param filebasename Used for naming output files.
 */
void loopers_4trks(TTree* tree, std::string filebasename);

/**
 * @brief Analyze events with exactly 2 tracks and plot the combined momentum over pion mass.
 * 
 * Simpler case of two-track events used to analyze potential looper-like behavior.
 * 
 * @param tree Pointer to TTree with branches: "trk_p", "trk_q", "ntrk".
 * @param filebasename Used for naming output files.
 */
void loopers_2trks(TTree* tree, std::string filebasename);
