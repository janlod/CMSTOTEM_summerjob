#pragma once

#include <string>
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"

/**
 * @brief Plot the distribution of track momenta for events with exactly 4 tracks.
 * 
 * This function loops over all events in the input TTree, selects events with exactly
 * 4 tracks, and fills a histogram with the momentum of each track. The resulting histogram
 * is drawn and saved as a PNG file in the `plots/p_dist/` directory.
 * 
 * @param tree Pointer to a TTree containing branches:
 *             - "trk_p" (Float_t[1000]): momentum of each track
 *             - "ntrk" (Int_t): number of tracks in the event
 * @param filebasename Base name used for labeling and saving the output plot file.
 */
void p_dist(TTree* tree, std::string filebasename);

