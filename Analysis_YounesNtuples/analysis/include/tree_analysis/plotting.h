#pragma once

#include <ROOT/RDataFrame.hxx>   
#include <TCanvas.h>             
#include <TH1F.h>                
#include <TH2F.h>                
#include <TFile.h>               
#include <TString.h>             
#include <TROOT.h>               
#include <ROOT/RVec.hxx>

#include <string>                
#include <vector>                
#include <iostream>
#include <cmath>              

using RVecF = ROOT::RVec<float>;

/**
 * @brief Fill and save a 2D correlation histogram for two event-level variables.
 * 
 * @param filepath Path to the ROOT file containing the tree.
 * @param outpath Path to save the output ROOT file with the histogram.
 * @param xbranch Name of the branch for x-axis.
 * @param ybranch Name of the branch for y-axis.
 * @param xnbins Number of bins for x-axis.
 * @param ynbins Number of bins for y-axis.
 * @param xmin Minimum value of x-axis.
 * @param ymin Minimum value of y-axis.
 * @param xmax Maximum value of x-axis.
 * @param ymax Maximum value of y-axis.
 * @param logscale Whether to use log scale for the z-axis (default false).
 */
void plot2D_correl_eventvar(std::string filepath, std::string outpath, std::string xbranch, std::string ybranch, int xnbins, int ynbins, float xmin, float ymin, float xmax, float ymax, bool logscale=false);

/**
 * @brief Plot 2D correlation of reconstructed invariant mass pairs.
 * 
 * @param correct True to use correctly paired mass combinations, false for wrong pairings.
 * @param filepath Path to input ROOT file.
 * @param outpath Path to output ROOT file.
 * @param nbins Number of bins along each axis.
 * @param min Minimum mass.
 * @param max Maximum mass.
 * @param logscale Use log scale for z-axis.
 */
void plot2D_masspairs(bool correct, std::string filepath, std::string outpath, int nbins, float min, float max, bool logscale=true);

/**
 * @brief Fill and save a 1D histogram for an event-level variable.
 */
void plot1D_eventvar(std::string filepath, std::string outpath, std::string branch, int nbins, float min, float max, bool logscale=false);

/**
 * @brief Plot 2D correlation between proton momentum and track momentum along a given direction.
 * 
 * @param direction Direction ("x", "y", or "z").
 */
void plot2D_correl_trkp_prp(std::string filepath, std::string outpath, std::string direction, int xnbins, int ynbins, float xmin, float ymin, float xmax, float ymax, bool logscale=false);

/**
 * @brief Plot 2D correlation between two track-level variables, e.g., dE/dx vs momentum.
 */
void plot2D_correl_trkvars(std::string filepath, std::string outpath, std::string xbranch, std::string ybranch, int xnbins, int ynbins, float xmin, float ymin, float xmax, float ymax, bool logscale=true);

/**
 * @brief Fill and save a 1D histogram for a track-level variable.
 */
void plot1D_trkvar(std::string filepath, std::string outpath, std::string branch, int nbins, float min, float max, bool logscale=false);

