#pragma once  // Or use traditional include guards

#include <string>
#include <array>
#include <map>
#include <iostream>
#include <cmath>

// ROOT includes
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TAxis.h"
#include "TPaveText.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TMath.h"

/// @file complicated_cuts.h
/// @brief Functions for data manipulation, 1D/2D histogram generation, Gaussian fits, and 3-sigma cuts on ROOT TTrees.

/**
 * @brief Performs a Gaussian fit on zPV and saves only entries within 3σ of the mean.
 * @param tree Pointer to a TTree containing a branch "zPV".
 * @param filebasename Base name to use for output files and histogram titles.
 **/
void cut_zPV(TTree* tree, std::string filebasename);

/**
 * @brief Performs a Gaussian fit on dz/dzerr and saves only entries within 3σ of the mean.
 * @param tree Pointer to a TTree containing branches "trk_dz" and "trk_dzerr".
 * @param filebasename Base name to use for output files and histogram titles.
 **/
void cut_dzdzerr(TTree* tree, std::string filebasename);

/**
 * @brief Checks whether a value is within 3σ of a Gaussian distribution.
 * @param val Value to check.
 * @param fitparams Gaussian fit parameters {amplitude, mean, sigma}.
 * @return True if the value is within [mean-3*sigma, mean+3*sigma], false otherwise.
 **/
bool isin_3sigma(Float_t val, std::array<double,3> fitparams);

/**
 * @brief Creates a 1D histogram of an event-level variable from a TTree.
 * @param tree Pointer to a TTree containing the data.
 * @param svar Branch name of the variable to plot.
 * @param nbin Number of bins in the histogram.
 * @param minbin Minimum bin value.
 * @param maxbin Maximum bin value.
 * @return Pointer to the filled TH1F histogram.
 **/
TH1F* get1D_hist_eventvar(TTree* tree, std::string svar, float nbin, float minbin, float maxbin);

/**
 * @brief Creates a 1D histogram of a track-level variable normalized by its error.
 * @param tree Pointer to a TTree containing the data.
 * @param svar Branch name of the track variable.
 * @param svarerr Branch name of the track variable error.
 * @param nbin Number of bins in the histogram.
 * @param minbin Minimum bin value.
 * @param maxbin Maximum bin value.
 * @return Pointer to the filled TH1F histogram.
 **/
TH1F* get1D_hist_trkvar(TTree* tree, std::string svar, std::string svarerr, int nbin, float minbin, float maxbin);

/**
 * @brief Creates a 2D histogram of two variables from a TTree.
 * @param tree Pointer to a TTree containing the data.
 * @param svarX Branch name for the X-axis.
 * @param svarY Branch name for the Y-axis.
 * @param nbinX Number of bins along X-axis.
 * @param minbinX Minimum X value.
 * @param maxbinX Maximum X value.
 * @param nbinY Number of bins along Y-axis.
 * @param minbinY Minimum Y value.
 * @param maxbinY Maximum Y value.
 * @return Pointer to the filled TH2F histogram.
 **/
TH2F* get2D_hist(TTree* tree, std::string svarX, std::string svarY, int nbinX, float minbinX, float maxbinX, int nbinY, float minbinY, float maxbinY);

/**
 * @brief Performs a 1D Gaussian fit on a histogram and returns the fit parameters.
 * @param hist Pointer to the TH1F histogram to fit.
 * @param fitrangeMin Minimum of the fit range.
 * @param fitrangeMax Maximum of the fit range.
 * @return Array containing {amplitude, mean, sigma}.
 **/
std::array<double,3> fitParams1D_gausfit(TH1F* hist, float fitrangeMin, float fitrangeMax);

/**
 * @brief Performs Gaussian fits along all slices of a 2D histogram along the x-axis.
 * @param hist Pointer to the TH2F histogram to slice and fit.
 * @param fitrangeMin Minimum of the fit range for each slice.
 * @param fitrangeMax Maximum of the fit range for each slice.
 * @return Map with y-bin index as key and Gaussian fit parameters {amplitude, mean, sigma} as value.
 **/
std::map<int, std::array<double, 3>> fitParams2D_gausfit_allSlices(TH2F* hist, float fitrangeMin, float fitrangeMax);

/**
 * @brief Performs cuts on multiple variables using a 3-sigma criterion and saves the resulting TTree.
 * @param tree Pointer to the TTree to cut.
 * @param filebasename Base name for the output files.
 **/
void cut_3sigma(TTree* tree, std::string filebasename);

/**
 * @brief Quickly plots a 2D histogram from a ROOT file and saves the canvas.
 * @param filename Path to the ROOT file containing the TTree.
 * @param svarX Branch name for the X-axis.
 * @param svarY Branch name for the Y-axis.
 * @param nbinX Number of bins along X-axis.
 * @param minbinX Minimum X value.
 * @param maxbinX Maximum X value.
 * @param nbinY Number of bins along Y-axis.
 * @param minbinY Minimum Y value.
 * @param maxbinY Maximum Y value.
 **/
void quick2Dplot(std::string filename, std::string svarX, std::string svarY, int nbinX, float minbinX, float maxbinX, int nbinY, float minbinY, float maxbinY);

/**
 * @brief Quickly plots a 1D histogram (event or track variable) from a ROOT file and saves the canvas.
 * @param filename Path to the ROOT file containing the TTree.
 * @param svar Branch name for the variable.
 * @param svarerr Branch name for the variable error (if track variable).
 * @param nbin Number of bins.
 * @param minbin Minimum bin value.
 * @param maxbin Maximum bin value.
 * @param trkvar Set to 1 for track variable, 0 for event variable.
 **/
void quick1Dplot(std::string filename, std::string svar, std::string svarerr, int nbin, float minbin, float maxbin, int trkvar);

