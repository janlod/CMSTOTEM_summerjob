#pragma once

#include <TH1F.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include <iostream>
#include <string>

/**
 * @brief Calculate the chi2 cutoff for a desired significance level.
 * 
 * Computes the cutoff on the background histogram (bgHist) such that
 * the probability of observing a background event above this cutoff
 * is less than or equal to `significance`.
 * 
 * @param bgHist Pointer to the background histogram (TH1F*).
 * @param sgHist Pointer to the signal histogram (TH1F*). Optional here but may be used for reference.
 * @param significance Desired background significance level (alpha).
 * @return The x-value cutoff corresponding to the significance level, or -1 if not found.
 */
float get_chi2Cutoff(TH1F* bgHist, TH1F* sgHist, double significance);


/**
 * @brief Draw cumulative density functions (CDFs) for background and signal histograms.
 * 
 * Plots the CDFs for both bgHist and sgHist, as well as their difference,
 * and saves the resulting canvas to a ROOT file specified by `outpath`.
 * 
 * @param bgHist Pointer to the background histogram (TH1F*).
 * @param sgHist Pointer to the signal histogram (TH1F*).
 * @param outpath Path to save the output ROOT file containing the canvas.
 */
void draw_CDFs(TH1F* bgHist, TH1F* sgHist, std::string outpath);

