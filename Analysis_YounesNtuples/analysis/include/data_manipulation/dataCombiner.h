#pragma once

#include <string>
#include <vector>
#include <iostream>

// ROOT includes
#include "ROOT/RDataFrame.hxx"

/// @file dataCombiner.h
/// @brief Functions to combine multiple ROOT TTrees into a single TTree.

/**
 * @brief Combines multiple ROOT TTrees from a list of files into a single TTree and saves it.
 * @param fileList Vector of paths to input ROOT files containing TTrees named "tree".
 * @param config Base name for the output ROOT file. The resulting file is saved as "../../data/combined/<config>.root".
 **/
void combineTrees(std::vector<std::string> fileList, std::string config);

