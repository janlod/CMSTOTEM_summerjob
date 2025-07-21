#pragma once

#include <string>
#include <array>
#include <TH2F.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TF1.h>
#include <TFile.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RVec.hxx>

using namespace ROOT::VecOps;
using RVecF = ROOT::RVec<float>;
using RVecI = ROOT::RVec<int>;


// Get the inv mass histo from the modified tree, which has the inv mass pair branches
TH2F* get2D_inv_mass_hist(std::string treename, std::string filepath, std::string filename, int nbin, float min, float max);

/// Plot 2D invariant mass histogram and save PNG + ROOT file.
void plot_2D_inv_mass_hist(TH2F* hist, const std::string& filename);

/// Project TH2F onto X or Y axis within range [projmin, projmax].
/// Saves projection plots if save==true.
TH1D* getProj(TH2F* hist, float projmin, float projmax, const std::string filename, const std::string option,
              bool save=false);

/// Fit a Gaussian to invariant mass projection (X or Y),
/// refining initial guess in iterative fitting loop.
TF1* gaussfit_kaon_mass(TH2F* hist, const std::string filename,
                       const std::array<float,3> initial_guess,
                       const std::string option);

/// Overlay Gaussian fits on the 2D histogram projections,
/// optionally saving the resulting canvas.
void overlay_fits(TH2F* hist, TF1* gausfitx, TF1* gausfity,
                  const std::string filename,
                  bool saveplot=false);
