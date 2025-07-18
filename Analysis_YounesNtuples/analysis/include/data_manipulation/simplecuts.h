#pragma once

#include <string>
#include <cmath>      // For std::abs
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RVec.hxx>

using namespace ROOT::VecOps;
using RVecF = ROOT::VecOps::RVec<float>;
// Returns true if exactly 4 elements in `trks` are within `cutvalue`
bool all4Good(RVecF trks, float cutvalue);

// Applies a series of simple cuts and saves the resulting tree
void simpleCut(std::string treename, std::string fileloc, std::string filename);
