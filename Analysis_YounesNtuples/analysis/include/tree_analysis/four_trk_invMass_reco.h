#pragma once

#include <string>
#include <TLorentzVector.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH1F.h>
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RVec.hxx>

using namespace ROOT::VecOps;
using RVecF = ROOT::RVec<float>;

/**
 * @brief Compute and optionally draw the invariant mass of 4-track events.
 * 
 * This function loops over all events in the ROOT file, selects events with exactly 4 tracks,
 * and sums the TLorentzVectors of the tracks (assuming pion mass 0.13957 GeV) to compute
 * the invariant mass of the system. The resulting histogram is optionally drawn and saved.
 * 
 * @param filepath Path to the ROOT file containing the TTree named "tree".
 * @param outpath Path to save the ROOT file containing the histogram (if draw is true).
 * @param nbins Number of bins in the histogram.
 * @param min Minimum x-axis value for the histogram [MeV].
 * @param max Maximum x-axis value for the histogram [MeV].
 * @param draw Whether to draw and save the histogram in a ROOT file. Default is true.
 * @return TH1F* Pointer to the histogram of the 4-track invariant mass.
 */
TH1F* get_4trk_invMass(std::string filepath, std::string outpath, int nbins, float min, float max, bool draw=true);

/**
 * @note The function assumes the tracks are charged pions with mass 0.13957 GeV.
 *       The histogram x-axis is in MeV, hence the mass is multiplied by 1e3.
 */

