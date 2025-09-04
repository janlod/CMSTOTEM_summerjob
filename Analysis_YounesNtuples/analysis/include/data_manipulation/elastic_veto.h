#pragma once

#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <ROOT/RDataFrame.hxx>

/**
 * @brief Determine if a proton pair passes the elastic veto.
 * 
 * @param pr_px_a x-momentum of proton a
 * @param pr_px_b x-momentum of proton b
 * @param pr_py_a y-momentum of proton a
 * @param pr_py_b y-momentum of proton b
 * @param threshold Threshold value for veto
 * @return true if the event is considered elastic, false otherwise
 */
bool isElastic(double pr_px_a, double pr_px_b, double pr_py_a, double pr_py_b, float threshold);

/**
 * @brief Apply elastic veto filter to a ROOT tree and save filtered tree.
 * 
 * @param filepath Path to input ROOT file
 * @param outpath Path to output ROOT file
 * @param threshold Threshold value for veto
 */
void cutElastic_veto(std::string filepath, std::string outpath, float threshold);

