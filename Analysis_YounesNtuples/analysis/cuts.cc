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
    Float_t trk_dz[100], trk_dzerr[100];
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
                Float_t dzerr = trk_dz[itrk];
                hist1d->Fill(dz/dzerr);
            }
        }
        
    }
        
    TF1* gausFit = new TF1("gausFit", "gaus", -1.0, 1.0);
    std::cout << "Fit for " << filebasename << ".root" <<std::endl;
    hist1d->Fit(gausFit, "R");

    double mean = gausFit->GetParameter(1);
    double sigma = gausFit->GetParameter(2);

    Float_t dzcut, dzerrcut;
    TFile* outfile = TFile::Open(("cutted_data/dz/dzcutted"+filebasename+".root").c_str(), "RECREATE");
    TTree* outtree = new TTree("tree", "cutted dz and dzerr");
    outtree->Branch("dz", &dzcut, "dz/F");
    outtree->Branch("dzerr", &dzerrcut, "dzerr/F");

    for(Int_t i=0; i<nentries; i++){
        tree->GetEntry(i);
        if(ntrk==4){
            for(int itrk=0; itrk<ntrk; itrk++){
                if(trk_dz[itrk]/trk_dzerr[itrk] <= mean+3*sigma && trk_dz[itrk]/trk_dzerr[itrk]>= mean-3*sigma);
                outtree->Fill();
            }
            
        }
    }
    outtree->Write();
    outfile->Close();
}