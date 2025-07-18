#pragma once

#include <string>
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"

/**
 * @brief Plot the distribution of track momenta for events with exactly 4 tracks.
 * 
 * @param tree Pointer to a TTree with branches "trk_p" (momentum) and "ntrk" (number of tracks).
 * @param filebasename Base name for output plot files.
 */
void p_dist(TTree* tree, std::string filebasename);
