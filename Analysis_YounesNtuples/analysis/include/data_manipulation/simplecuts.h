#pragma once

#include <string>
#include <vector>
#include <cmath>      // For std::abs
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RVec.hxx>

using namespace ROOT::VecOps;
using RVecF = ROOT::VecOps::RVec<float>;

/// @file simplecuts.h
/// @brief Functions for simple event and track cuts using ROOT RDataFrame.

/**
 * @brief Checks if exactly 4 elements in a vector are within a given cut value.
 * @param trks Vector of track-related values.
 * @param cutvalue Threshold value for the cut.
 * @return True if exactly 4 elements satisfy |value| < cutvalue, false otherwise.
 **/
bool all4Good(RVecF trks, float cutvalue);

/**
 * @brief Applies a series of simple cuts on track and event variables and saves the resulting tree.
 * @param cuts Vector of cut thresholds in the order: [pt_min, pt_max, eta_max, zPV_max, dxy_max, dz_max, dxydxyerr_max, dzdzerr_max].
 * @param fileloc Path to the input ROOT file containing the TTree named "tree".
 * @param outname Base name for the output ROOT file to store the cutted tree.
 **/
void simpleCut(std::vector<float> cuts, std::string fileloc, std::string outname);

/**
 * @brief Filters out tracks with invalid charge by requiring positive rho mass pair.
 * @param filepath Path to the input ROOT file containing the TTree named "tree".
 * @param outfilename Base name for the output ROOT file to store the cutted tree.
 **/
void cut_badChargeTrks(std::string filepath, std::string outfilename);

/**
 * @brief Applies chi2-based cuts on the tree for zPV, dxy/dxyerr, and dz/dzerr variables.
 * @param treename Name of the TTree to cut.
 * @param filepath Path to the input ROOT file containing the TTree.
 * @param outfilename Base name for the output ROOT file to store the cutted tree.
 * @param cutoffs Vector of chi2 cut thresholds in the order: [chi2_zPV, chi2_dxy_dxyerr, chi2_dz_dzerr].
 **/
void cutChi2(std::string treename, std::string filepath, std::string outfilename, std::vector<float> cutoffs);

/**
 * @brief Applies cuts on chi2_rhoMass variables for both rho candidates and saves the resulting tree.
 * @param filepath Path to the input ROOT file containing the TTree named "tree".
 * @param cutoff Threshold value to apply to both chi2_rhoMass_pair1 and chi2_rhoMass_pair2.
 * @param outname Base name for the output ROOT file to store the cutted tree.
 **/
void cut_rhoMassChi2(std::string filepath, float cutoff, std::string outname);

