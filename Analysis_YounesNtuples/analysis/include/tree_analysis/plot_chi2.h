#pragma once

#include <string>
#include <vector>
#include <utility>
#include <TCanvas.h>
#include <TFile.h>
#include <TLegend.h>
#include <TH1F.h>
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RVec.hxx>

using namespace ROOT::VecOps;
using RVecF = ROOT::RVec<float>;

/**
 * @brief Plot a 1D histogram of a chi2 branch from a ROOT TTree.
 * 
 * @param branchname Name of the branch to histogram.
 * @param treename Name of the TTree in the file.
 * @param filepath Path to the ROOT file containing the TTree.
 * @param outfilename Name of the output ROOT file (without extension).
 * @param nbins Number of histogram bins.
 * @param minbin Minimum x-axis value.
 * @param maxbin Maximum x-axis value.
 */
void plot_chi2(std::string branchname, std::string treename, std::string filepath,
               std::string outfilename, int nbins, float minbin, float maxbin);

/**
 * @brief Plot normalized chi2 distributions in mass windows for Rho and Kaon.
 * 
 * Iterates over events in the tree, checks if invariant mass pairs are within
 * specified mass windows, and fills two histograms for chi2 values corresponding
 * to rho and kaon candidates. Draws histograms and saves to a ROOT file.
 * 
 * @param filepath Path to the ROOT file with the tree "tree".
 * @param outpath Path to save the output ROOT file.
 * @param chi2_branch Branch name containing chi2 values.
 * @param rhoWindow Mass window for rho candidate selection {min, max}.
 * @param kaonWindow Mass window for kaon candidate selection {min, max}.
 * @param nbins Number of bins for histograms.
 * @param plotmin Minimum x-axis value.
 * @param plotmax Maximum x-axis value.
 * @return std::pair of pointers to the kaon and rho histograms.
 */
std::pair<TH1F*, TH1F*> plot_chi2_inWindow(std::string filepath, std::string outpath,
                                           std::string chi2_branch, std::vector<float> rhoWindow,
                                           std::vector<float> kaonWindow, int nbins,
                                           float plotmin, float plotmax);

