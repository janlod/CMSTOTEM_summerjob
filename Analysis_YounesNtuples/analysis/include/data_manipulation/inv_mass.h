#pragma once

#include <string>
#include <vector>
#include <cmath>
#include <utility>         // For std::pair
#include <TLorentzVector.h>
#include <TH2F.h>
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RVec.hxx>

using namespace ROOT::VecOps;
using RVecF = ROOT::RVec<float>;
using RVecI = ROOT::RVec<int>;

/// @file inv_mass.h
/// @brief Functions to calculate invariant masses of track pairs and glueball mass,
///        and to add the resulting branches to ROOT TTrees.

/**
 * @brief Adds two new branches to a ROOT TTree: "inv_mass_pair1" and "inv_mass_pair2".
 *        Calculates the invariant mass of opposite-charge track pairs.
 * 
 * @param treename Name of the TTree in the ROOT file.
 * @param filepath Path to the ROOT file.
 * @param filename Base name for the output ROOT file with new branches.
 * @param massPi Mass of the pion (default 0.13957 GeV).
 */
void add_inv_massBranches(std::string treename, std::string filepath, std::string filename, float massPi = 0.13957);

/**
 * @brief Adds a new branch to a ROOT TTree called "glueball_mass".
 *        Calculates the invariant mass of the full 4-track system.
 * 
 * @param filepath Path to the ROOT file containing the TTree "tree".
 * @param outname Base name for the output ROOT file with the new branch.
 * @param masspar Mass parameter for the tracks (default 0.13957 GeV).
 */
void add_Glueball_massBranch(std::string filepath, std::string outname, float masspar = 0.13957);

