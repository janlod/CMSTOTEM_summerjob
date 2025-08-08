#pragma once

#include <string>

#include <ROOT/RDataFrame.hxx>
#include <TLorentzVector.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH1F.h>
#include <TROOT.h>
#include <TMath.h>

#include <ROOT/RVec.hxx>
using namespace ROOT::VecOps;
using RVecF = ROOT::RVec<float>;

TH1F* get_4trk_invMass(std::string filepath, std::string outpath, int nbins, float min, float max, bool draw=true);

