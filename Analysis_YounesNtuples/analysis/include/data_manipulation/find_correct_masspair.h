#pragma once

#include <ROOT/RVec.hxx>
#include <ROOT/RDataFrame.hxx>
#include <string>
#include <vector>

using RVecF = ROOT::RVec<float>;

/// @file find_correct_masspair.h
/// @brief Functions to determine correct and wrong mass pairs based on chi-squared values, and create new TTree branches.

/**
 * @brief Returns the mass pair with the lower chi-squared value.
 * @param pair1 First candidate mass pair.
 * @param pair2 Second candidate mass pair.
 * @param chi2_pair1 Chi-squared value for the first pair.
 * @param chi2_pair2 Chi-squared value for the second pair.
 * @return The mass pair (RVecF) with the lower chi-squared value.
 **/
RVecF get_correct_massPair(RVecF pair1, RVecF pair2, float chi2_pair1, float chi2_pair2);

/**
 * @brief Returns the mass pair with the higher chi-squared value.
 * @param pair1 First candidate mass pair.
 * @param pair2 Second candidate mass pair.
 * @param chi2_pair1 Chi-squared value for the first pair.
 * @param chi2_pair2 Chi-squared value for the second pair.
 * @return The mass pair (RVecF) with the higher chi-squared value.
 **/
RVecF get_wrong_massPair(RVecF pair1, RVecF pair2, float chi2_pair1, float chi2_pair2);

/**
 * @brief Creates new branches in a ROOT TTree: "correct_massPair", "wrong_massPair", and "chi2_diff".
 *        The branches are based on the chi-squared comparison of rho mass pairs.
 * @param filepath Path to the input ROOT file containing the TTree "tree".
 * @param outname Base name for the output ROOT file where the new TTree with added branches will be saved.
 **/
void create_correct_massBranch(std::string filepath, std::string outname);
	 
