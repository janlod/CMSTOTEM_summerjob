#pragma once

#include <ROOT/RDataFrame.hxx>   
#include <TCanvas.h>             
#include <TH1F.h>                
#include <TH2F.h>                
#include <TFile.h>               
#include <TString.h>             
#include <TROOT.h>               
#include <ROOT/RVec.hxx>
#include <TLegend.h>

#include <string>                
#include <vector>                
#include <iostream>
#include <cmath>              

using RVecF = ROOT::RVec<float>;

/**
 * @brief Fill and save a 2D correlation histogram for two event-level variables.
 */
void plot2D_correl_eventvar(std::string filepath, std::string outpath, std::string xbranch, std::string ybranch,
                            int xnbins, int ynbins, float xmin, float ymin, float xmax, float ymax, bool logscale=false);

/**
 * @brief Plot 2D correlation of reconstructed invariant mass pairs.
 */
void plot2D_masspairs(bool correct, std::string filepath, std::string outpath, int nbins, float min, float max, bool logscale=true);

/**
 * @brief Fill and save a 1D histogram for an event-level variable.
 */
void plot1D_eventvar(std::string filepath, std::string outpath, std::string branch, int nbins, float min, float max, bool logscale=false);

/**
 * @brief Plot 2D correlation between proton momentum and track momentum along a given direction.
 */
void plot2D_correl_trkp_prp(std::string filepath, std::string outpath, std::string direction,
                            int xnbins, int ynbins, float xmin, float ymin, float xmax, float ymax, bool logscale=false);

/**
 * @brief Plot 2D correlation between two track-level variables, e.g., dE/dx vs momentum.
 */
void plot2D_correl_trkvars(std::string filepath, std::string outpath, std::string xbranch, std::string ybranch,
                           int xnbins, int ynbins, float xmin, float ymin, float xmax, float ymax, bool logscale=true);

/**
 * @brief Fill and save a 1D histogram for a track-level variable.
 */
void plot1D_trkvar(std::string filepath, std::string outpath, std::string branch, int nbins, float min, float max, bool logscale=false);

/**
 * @brief Plot the difference in proton momentum components px and py.
 */
void plot_momentum_difference(std::string filepath, std::string outpath, int nbins, float min, float max);

/**
 * @brief Scatter plot for proton momentum components a vs b.
 */
void prot_momentum_scatterplot(std::string filepath, std::string outpath, std::string option,
                               int nbins, float min, float max, bool logscale=false);

/**
 * @brief Scatter plot for proton transverse momentum pt_a vs pt_b and 1D difference.
 */
void prot_pt_scatterplot(std::string filepath, std::string outpath, int nbins, float min, float max, bool logscale=false);

/**
 * @brief Histogram of azimuthal angle differences between left and right protons.
 */
void prot_azimuthal_difference(std::string filepath, std::string fpveto, std::string outpath,
                               int nbins, float min, float max);

