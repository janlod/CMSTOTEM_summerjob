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
/// Calculate invariant mass of opposite-charge track pairs.
/// Returns a pair of RVecF: (parallel pairs, cross pairs).

/// Add two new branches to the tree: inv_mass_pair1 and inv_mass_pair2.
void add_inv_massBranches(std::string treename, std::string filepath, std::string filename, float massPi = 0.13957);

/// Generate a 2D histogram of invariant mass combinations.
/// Units in output histogram: MeV.
TH2F* get2D_inv_mass_hist(std::string treename, std::string filepath, std::string filename,
                          int nbin, float min, float max);
