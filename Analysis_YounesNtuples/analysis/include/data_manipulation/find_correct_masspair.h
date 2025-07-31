#pragma once

#include <ROOT/RVec.hxx>
#include <ROOT/RDataFrame.hxx>
#include <string>
#include <vector>

using RVecF = ROOT::RVec<float>;

RVecF get_correct_massPair(RVecF pair1, RVecF pair2, float chi2_pair1, float chi2_pair2);

void create_correct_massBranch(std::string filepath, std::string outname);
	 
