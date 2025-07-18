#pragma once

#include <string>
#include <vector>
#include <iostream>

// ROOT includes
#include "ROOT/RDataFrame.hxx"

// Function declaration
void combineTrees(std::vector<std::string> fileList, std::string config);
