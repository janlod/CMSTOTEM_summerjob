#pragma once

#include <ROOT/RVec.hxx>
#include <ROOT/RDataFrame.hxx>
#include <string>
#include <vector>
#include "RtypesCore.h" 

using RVecF = ROOT::RVec<float>;


template<typename T>
float calcChiSquared(float mean, Int_t ntrk, T branch, T branchErr={});

float getChi2_rhoMass(float mean, float sigma, RVecF inv_mass_pair);

void create_chi2_rhoMass(float meanpar, float sigmapar, std::string filename, std::string outfilename);

void createChiSquared_tree(std::vector<float> means, std::string treename, std::string filepath, std::string outfilename);
