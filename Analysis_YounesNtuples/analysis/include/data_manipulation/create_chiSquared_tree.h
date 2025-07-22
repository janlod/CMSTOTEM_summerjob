#pragma once

#include <ROOT/RVec.hxx>
#include <ROOT/RDataFrame.hxx>
#include <string>
#include <vector>
#include "RtypesCore.h" 

using RVecF = ROOT::RVec<float>;


template<typename T>
float calcChiSquared(float mean, Int_t ntrk, T branch, T branchErr={});

void getChiSquared_tree(std::vector<float> means, std::string treename, std::string filepath, std::string outfilename);
