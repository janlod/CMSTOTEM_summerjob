#pragma once

#include <string>
#include <vector>
#include <cmath>      // For std::abs
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RVec.hxx>

using namespace ROOT::VecOps;
using RVecF = ROOT::VecOps::RVec<float>;
// Returns true if exactly 4 elements in `trks` are within `cutvalue`
bool all4Good(RVecF trks, float cutvalue);

// Applies a series of simple cuts and saves the resulting tree
void simpleCut(std::string treename, std::string fileloc, std::string filename);

void cut_badChargeTrks(std::string filepath, std::string outfilename);

void cutChi2(std::string treename, std::string filepath, std::string outfilename, std::vector<float> cutoffs);

void cut_rhoMassChi2(std::string filepath, float cutoff, std::string outname);
