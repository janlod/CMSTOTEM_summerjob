#include "TMath.h"
#include "TTree.h"
#include "TF1.h"
#include "TH2F.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TFile.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TGraphErrors.h"
#include "TLatex.h"
#include "TLine.h"
#include "TMinuit.h"
#include "TStyle.h"
#include "TProfile.h"
#include "TVector.h"
#include "TMatrix.h"
#include "TMarker.h"
#include "TRandom3.h"
#include "TMultiGraph.h"

#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "math.h"
#include "math.h"
#include "stdlib.h"
#include <cstdlib> 

void cut_zPV(TTree* tree, std::string filebasename){
    Float_t zPV;
    Int_t ntrk;

    tree->SetBranchAddress("zPV", &zPV);
    tree->SetBranchAddress("ntrk", &ntrk);
    
    TCanvas *c1 = new TCanvas("Figure","Figure",1000,800);
    TH1F* hist1d = new TH1F(("zPV from " + filebasename).c_str(), "zPV", 400, -15.0, 15.0);
    hist1d->GetXaxis()->SetTitle("z");

    Long64_t nentries = tree->GetEntries();
    for (Int_t i = 0; i < nentries; i++) {
        tree->GetEntry(i);
        if(ntrk == 4){
            hist1d->Fill(zPV);
        }
        
    }
        
    TF1* gausFit = new TF1("gausFit", "gaus", -5.0, 5.0);
    std::cout << "Fit for " << filebasename << ".root" <<std::endl;
    hist1d->Fit(gausFit, "R");

    double mean = gausFit->GetParameter(1);
    double sigma = gausFit->GetParameter(2);


   TFile* outfile = TFile::Open(("cutted_data/zPV/zPVcutted"+filebasename+".root").c_str(), "RECREATE");
   TTree* outtree = new TTree("tree", "cutted ZPV");
   outtree->Branch("zPV", &zPV, "zPV/F");

   for(Int_t i=0; i<nentries; i++){
    tree->GetEntry(i);
    if(ntrk==4  &&  mean - 3*sigma <= zPV  &&  zPV <= mean + 3*sigma  ){
        outtree->Fill();
    }
   }
   outtree->Write();
   outfile->Close();
}


void cut_dzdzerr(TTree* tree, std::string filebasename){
    Float_t trk_dz[1000], trk_dzerr[1000];
    Int_t ntrk;

    tree->SetBranchAddress("trk_dz", trk_dz);
    tree->SetBranchAddress("ntrk", &ntrk);
    tree->SetBranchAddress("trk_dzerr", trk_dzerr);
    
    TCanvas *c1 = new TCanvas("Figure","Figure",1000,800);
    TH1F* hist1d = new TH1F(("dz/dzerr from " + filebasename).c_str(), "dz/dzerr", 400, -15.0, 15.0);
    hist1d->GetXaxis()->SetTitle("z");

    Long64_t nentries = tree->GetEntries();
    for (Int_t i = 0; i < nentries; i++) {
        tree->GetEntry(i);
        if(ntrk == 4){
            for(int itrk=0; itrk<ntrk; itrk++){
                Float_t dz = trk_dz[itrk];
                Float_t dzerr = trk_dzerr[itrk];
                hist1d->Fill(dz/dzerr);
            }
        }
        
    }
        
    TF1* gausFit = new TF1("gausFit", "gaus", -1.0, 1.0);
    std::cout << "Fit for " << filebasename << ".root" <<std::endl;
    hist1d->Fit(gausFit, "R");

    double mean = gausFit->GetParameter(1);
    double sigma = gausFit->GetParameter(2);

    Float_t dzcut;
    Float_t dzerrcut;
    TFile* outfile = TFile::Open(("cutted_data/dz/dzcutted"+filebasename+".root").c_str(), "RECREATE");
    TTree* outtree = new TTree("tree", "cutted dz and dzerr");
    outtree->Branch("dz", &dzcut, "dz/F");
    outtree->Branch("dzerr", &dzerrcut, "dzerr/F");

    for(Int_t i=0; i<nentries; i++){
        tree->GetEntry(i);
        if(ntrk==4){
            for(int itrk=0; itrk<ntrk; itrk++){
                if(trk_dz[itrk]/trk_dzerr[itrk] <= mean+3*sigma && trk_dz[itrk]/trk_dzerr[itrk]>= mean-3*sigma){
                    dzcut = trk_dz[itrk];
                    dzerrcut = trk_dzerr[itrk];
                    outtree->Fill();
                }
            }   
        }
    }
    outtree->Write();
    outfile->Close();
    delete outfile;
}

bool isin_3sigma(Float_t val, Float_t mean, Float_t sigma){
   return (val <= mean + 3*sigma && val >= mean - 3*sigma);
}

void gaussian_3sigma_cut(TTree* tree, std::string filebasename){
    Float_t zPV;
    Int_t ntrk;
    Float_t trk_dz[1000];
    Float_t trk_dzerr[1000];
    Float_t trk_dxy[1000];
    Float_t trk_dxyerr[1000];
    Float_t trk_eta[1000];
    Float_t trk_phi[100];

    tree->SetBranchAddress("zPV", &zPV);
    tree->SetBranchAddress("ntrk", &ntrk);
    tree->SetBranchAddress("trk_dz", trk_dz);
    tree->SetBranchAddress("trk_dzerr", trk_dzerr);
    tree->SetBranchAddress("trk_dxy", trk_dxy);
    tree->SetBranchAddress("trk_dxyerr", trk_dxyerr);
    tree->SetBranchAddress("trk_eta", trk_eta);
    tree->SetBranchAddress("trk_phi", trk_phi);

    TF1* fit_zPV = new TF1("fit_zPV", "gaus", -5, 5);
    TF1* fit_dz = new TF1("fit_dz", "gaus", -1, 1);
    TF1* fit_dxy = new TF1("fit_dxy", "gaus", -1, 1);
    TF1* fit_dxy_phi = new TF1("fit_dxy_phi", "gaus", -0.1, 0.1);
    TF1* fit_dz_eta = new TF1("fit_dz_eta", "gaus", -0.1, 0.1);

    TH1F* hist_zPV = new TH1F("zPV", "zPV", 400, -15, 15);
    TH1F* hist_dzBydzerr = new TH1F("dz/dzerr", "dz/dzerr", 400, -3, 3);
    TH1F* hist_dxyBydxyerr = new TH1F("dxy/dxyerr", "dxy/dxyerr", 400, -3, 3);
    TH2F* hist_dxy_phi = new TH2F("dxy vs. phi", "dxy vs. phi",400, -0.3, 0.3, 400, -3.14, 3.14);
    TH2F* hist_dz_eta = new TH2F("dz vs. eta", "dz vs. eta", 400, -0.5, 0.5, 400, -3.0, 3.0);

    Long64_t nentries = tree->GetEntries();
    double sigma_zPV, mean_zPV;
    double sigma_dzBydzerr, mean_dzBydzerr;
    double sigma_dxyBydxyerr, mean_dxyBydxyerr;
    for(int i=0; i<nentries; i++){
        tree->GetEntry(i);
        if(ntrk == 4){
            hist_zPV->Fill(zPV);
            for(int itrk=0; itrk<ntrk; itrk++){
                hist_dzBydzerr->Fill(trk_dz[itrk]/trk_dzerr[itrk]);
                hist_dxyBydxyerr->Fill(trk_dxy[itrk]/trk_dxyerr[itrk]);
                hist_dxy_phi->Fill(trk_dxy[itrk], trk_phi[itrk]);
                hist_dz_eta->Fill(trk_dz[itrk], trk_eta[itrk]);
            }
        }
    }
    hist_zPV->Fit(fit_zPV, "R");
    mean_zPV = fit_zPV->GetParameter(1);
    sigma_zPV = fit_zPV->GetParameter(2);

    hist_dzBydzerr->Fit(fit_dz, "R");
    mean_dzBydzerr = fit_dz->GetParameter(1);
    sigma_dzBydzerr = fit_dz->GetParameter(2);

    hist_dxyBydxyerr->Fit(fit_dxy, "R");
    mean_dxyBydxyerr = fit_dxy->GetParameter(1);
    sigma_dxyBydxyerr = fit_dxy->GetParameter(2);

    std::map<int, std::vector<double>> dxy_fitParams_map;
    std::map<int, std::vector<double>> dz_fitParams_map;

    int dxy_nbinsY = hist_dxy_phi->GetNbinsY();
    int dz_nbinsY = hist_dz_eta->GetNbinsY();
    int dxy_nbinsX = hist_dxy_phi->GetNbinsX();
    int dz_nbinsX = hist_dz_eta->GetNbinsX();
	
    // Routine for dxy_phi
    std::vector<int> invalidFit_bins_dxy;
    std::vector<int> invalidFit_bins_dz;
    for(int ybin=1; ybin<=dxy_nbinsY; ybin++){
        std::vector<double> fitParams; //Always (mean, sigma)
	TH1F* projx = new TH1F("hist", "hist", dxy_nbinsX, hist_dxy_phi->GetXaxis()->GetXmin(), hist_dxy_phi->GetXaxis()->GetXmax());

	for(int xbin=1; xbin<=dxy_nbinsX; xbin++){
      		projx->Fill(hist_dxy_phi->GetBinContent(xbin, ybin));
	}
 	Int_t fitResult = projx->Fit(fit_dxy_phi, "R");
	
	if(fitResult==2){
		invalidFit_bins_dxy.push_back(ybin);
	}

	fitParams.push_back(fit_dxy_phi->GetParameter(1));
	fitParams.push_back(fit_dxy_phi->GetParameter(2));
	dxy_fitParams_map.insert({ybin, fitParams});
	delete projx;
    }
    
    // Routine for dz_eta
    for(int ybin=1; ybin<=dz_nbinsY; ybin++){
        std::vector<double> fitParams; //Always (mean, sigma)
	TH1F* projx = new TH1F("hist", "hist", dxy_nbinsX, hist_dxy_phi->GetXaxis()->GetXmin(), hist_dxy_phi->GetXaxis()->GetXmax());

	for(int xbin=1; xbin<=dz_nbinsX; xbin++){
      		projx->Fill(hist_dz_eta->GetBinContent(xbin, ybin));
	}
 	Int_t fitResult = projx->Fit(fit_dz_eta, "R");
	

	if(fitResult==2){
		invalidFit_bins_dz.push_back(ybin);
	}

	fitParams.push_back(fit_dz_eta->GetParameter(1));
	fitParams.push_back(fit_dz_eta->GetParameter(2));
	dz_fitParams_map.insert({ybin, fitParams});
	delete projx;
    } 
 

   std::cout<<dxy_fitParams_map.size()<<std::endl;
   std::cout<<dz_fitParams_map.size()<<std::endl;
  
   std::vector<double> mapTest = dxy_fitParams_map.at(237);
   for (auto it = invalidFit_bins_dxy.begin(); it != invalidFit_bins_dxy.end(); ++it) {
        std::cout << *it << std::endl;
    }

   std::cout<<"\n\n\n"<<std::endl;
   for (auto  it = invalidFit_bins_dz.begin(); it != invalidFit_bins_dz.end(); ++it) {
        std::cout << *it << std::endl;
    }

   // Fits on 2d plots often diverge, improve initial guesses maybe?

    //Figure out what to do about 2d plots and fits and then loop through tree and do something along the lines:
    /**TFile* inputFile = TFile::Open("input.root");
TTree* tree = (TTree*)inputFile->Get("tree");

TFile* outputFile = new TFile("output.root", "RECREATE");

// Apply cuts like: var1 > 0 && var2 < 10
TTree* cutTree = tree->CopyTree("var1 > 0 && var2 < 10");

cutTree->Write();
outputFile->Close();
inputFile->Close();


     */

}
