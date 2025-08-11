#pragma once

#include <TH1F.h>
#include <iostream>
#include <string>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>

float get_chi2Cutoff(TH1F* bgHist, TH1F* sgHist, double significance); 


void draw_CDFs(TH1F* bgHist, TH1F* sgHist, std::string outpath);
