#pragma once

#include <ROOT/RVec.hxx>
#include <ROOT/RDataFrame.hxx>
#include <string>
#include <vector>
#include "RtypesCore.h"

using RVecF = ROOT::RVec<float>;

/// @file create_chiSquared_tree.h
/// @brief Functions to compute chi-squared variables for tracks and events, and create new TTrees with these chi2 branches.

/**
 * @brief Computes chi-squared for a branch with optional error, given the mean and number of tracks.
 * @tparam T Type of the branch (e.g., RVecF or scalar Float_t).
 * @param mean Expected mean value of the branch.
 * @param ntrk Number of tracks in the event.
 * @param branch Branch values (scalar or vector).
 * @param branchErr Branch errors (scalar or vector). Optional, defaults to empty.
 * @return Computed chi-squared value.
 **/
template<typename T>
float calcChiSquared(float mean, Int_t ntrk, T branch, T branchErr={});

/**
 * @brief Computes chi-squared for rho mass pairs relative to an expected mean and sigma.
 * @param mean Expected mean value of rho mass (in MeV).
 * @param sigma Standard deviation for the rho mass.
 * @param inv_mass_pair Vector of two invariant mass values for rho candidates.
 * @return Computed chi-squared value for the rho mass pair.
 **/
float getChi2_rhoMass(float mean, float sigma, RVecF inv_mass_pair);

/**
 * @brief Creates chi2 branches for rho mass pairs and saves them to a new ROOT file.
 * @param meanpar Mean value for the chi2 calculation.
 * @param sigmapar Standard deviation for the chi2 calculation.
 * @param filename Path to the input ROOT file containing the TTree named "tree".
 * @param outfilename Base name for the output ROOT file.
 **/
void create_chi2_rhoMass(float meanpar, float sigmapar, std::string filename, std::string outfilename);

/**
 * @brief Creates a new TTree with chi-squared variables for zPV, dxy/dxyerr, and dz/dzerr for all events with ntrk=4.
 * @param means Vector of mean values [zPV_mean, dxy/dxyerr_mean, dz/dzerr_mean].
 * @param treename Name of the TTree to process.
 * @param filepath Path to the input ROOT file.
 * @param outfilename Base name for the output ROOT file where the new TTree will be saved.
 **/
void createChiSquared_tree(std::vector<float> means, std::string treename, std::string filepath, std::string outfilename);

