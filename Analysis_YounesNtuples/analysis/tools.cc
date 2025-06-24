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
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "math.h"
#include "math.h"
#include "stdlib.h"

// This needs to be shortened and optimised, especially the option selction, right now very much code duplication
void primVertex_dist(TTree *tree, std::string filebasename, int option){
    if(option == 3){
        Float_t zPV;
        Int_t ntrk;
    
        tree->SetBranchAddress("zPV", &zPV);
        tree->SetBranchAddress("ntrk", &ntrk);
            
        TCanvas *c1 = new TCanvas("Figure","Figure",1000,800);
        TH1F* hist1d = new TH1F(("zPV from " + filebasename).c_str(), "zPV", 400, -15, 15);
        hist1d->GetXaxis()->SetTitle("z");

        Long64_t nentries = tree->GetEntries();
        Int_t counter4 = 0;
        for (Int_t i = 0; i < nentries; i++) {
            tree->GetEntry(i);
            if(ntrk == 4){
                hist1d->Fill(zPV);
                counter4++;
            }
            
        }
        std::cout<< counter4 << std::endl;
        hist1d->Draw();                
        c1->SaveAs(("plots/zPV_dist/zPV_" + filebasename + ".png").c_str());
        delete hist1d;
        delete c1;


    }else if(option == 2){
        Float_t yPV;
        Int_t ntrk;
   
        tree->SetBranchAddress("yPV", &yPV);
        tree->SetBranchAddress("ntrk", &ntrk);
            
        TCanvas *c1 = new TCanvas("Figure","Figure",1000,800);
        TH1F* hist1d = new TH1F(("yPV from " + filebasename).c_str(), "yPV", 400, 0.0, 0.2);
        hist1d->GetXaxis()->SetTitle("y");

        Long64_t nentries = tree->GetEntries();
        Int_t counter4 = 0;
        for (Int_t i = 0; i < nentries; i++) {
            tree->GetEntry(i);
            if(ntrk == 4){
                hist1d->Fill(yPV);
                counter4++;
            }
            
        }
        std::cout<< counter4 << std::endl;
        hist1d->Draw();                
        c1->SaveAs(("plots/yPV_dist/yPV_" + filebasename + ".png").c_str());
        delete hist1d;
        delete c1;


    }else if(option == 1){
        Float_t xPV;
        Int_t ntrk;
    
        tree->SetBranchAddress("xPV", &xPV);
        tree->SetBranchAddress("ntrk", &ntrk);
            
        TCanvas *c1 = new TCanvas("Figure","Figure",1000,800);
        TH1F* hist1d = new TH1F(("xPV from " + filebasename).c_str(), "xPV", 400, 0.0, 0.2);
        hist1d->GetXaxis()->SetTitle("x");

        Long64_t nentries = tree->GetEntries();
        Int_t counter4 = 0;
        for (Int_t i = 0; i < nentries; i++) {
            tree->GetEntry(i);
            if(ntrk == 4){
                hist1d->Fill(xPV);
                counter4++;
            }
            
        }
        std::cout<< counter4 << std::endl;
        hist1d->Draw();                
        c1->SaveAs(("plots/xPV_dist/xPV_" + filebasename + ".png").c_str());
        delete hist1d;
        delete c1;
    

    }else if(option == 4){
        Float_t xPV, yPV;
        Int_t ntrk;
    
        tree->SetBranchAddress("xPV", &xPV);
        tree->SetBranchAddress("yPV", &yPV);
        tree->SetBranchAddress("ntrk", &ntrk);
            
        TCanvas *c1 = new TCanvas("Figure","Figure",1000,800);
        TH1F* hist1d = new TH1F(("sqrt(xPV^2 + yPV^2) from " + filebasename).c_str(), "radius", 400, 0.1, 0.2);
        hist1d->GetXaxis()->SetTitle("squareSum");

        Long64_t nentries = tree->GetEntries();
        Int_t counter4 = 0;
        for (Int_t i = 0; i < nentries; i++) {
            tree->GetEntry(i);
            if(ntrk == 4){
                hist1d->Fill(sqrt(xPV*xPV + yPV*yPV));
                counter4++;
            }
            
        }
        std::cout<< counter4 << std::endl;
        hist1d->Draw();                
        c1->SaveAs(("plots/rPV_dist/radiusPV_" + filebasename + ".png").c_str());
        delete hist1d;
        delete c1;
    
        
    }else if(option == 12){
    Float_t xPV, yPV;
    Int_t ntrk;

    tree->SetBranchAddress("xPV", &xPV);
    tree->SetBranchAddress("yPV", &yPV);
    tree->SetBranchAddress("ntrk", &ntrk);
        
    TCanvas *c1 = new TCanvas("Figure","Figure",1000,800);
    TH2F* hist2d = new TH2F(("xyPV from " + filebasename).c_str(), "xyPV", 400, 0.0, 0.2, 400, 0.0, 0.2);
    hist2d->GetXaxis()->SetTitle("x");
    hist2d->GetYaxis()->SetTitle("y");

    Long64_t nentries = tree->GetEntries();
    Int_t counter4 = 0;
    for (Int_t i = 0; i < nentries; i++) {
        tree->GetEntry(i);
        if(ntrk == 4){
            hist2d->Fill(xPV, yPV);
            counter4++;
        }
    }
    std::cout<< counter4 << std::endl;
    hist2d->Draw();                
    c1->SaveAs(("plots/xyPV_dist/xyPV_" + filebasename + ".png").c_str());
    delete hist2d;
    delete c1;
    
    }else{
        std::cerr << "Invalid option\n Only these are allowed:\n 1 for xPV histo\n 2 for yPV histo\n 3 for zPV histo\n 4 for x^2+y^2 histo\n 12 for xyPV colorplot" <<std::endl; 
        exit(0);
    }
}


void dz_dist(TTree *tree, std::string filebasename){
    Float_t trk_dz[1000], trk_dzerr[1000];
    Int_t ntrk;

    tree->SetBranchAddress("trk_dz", trk_dz);
    tree->SetBranchAddress("trk_dzerr", trk_dzerr);
    tree->SetBranchAddress("ntrk", &ntrk);
        
    TCanvas *c1 = new TCanvas("Figure","Figure",1000,800);
    TH1F* hist1d = new TH1F(("dzerr from" + filebasename).c_str(), "dzerr", 400, 0.0, 0.3);
    hist1d->GetXaxis()->SetTitle("dz");
    //c1->SetLogy();

    Long64_t nentries = tree->GetEntries();
    Int_t counter4 = 0;
    for (Int_t i = 0; i < nentries; i++) {
        tree->GetEntry(i);
        if(ntrk == 4){
            for(Int_t i_trk = 0; i_trk < ntrk; i_trk++){
                //Choose what to plot
                //hist1d->Fill(trk_dz[i_trk]);
                hist1d->Fill(trk_dzerr[i_trk]);
            }
            
            counter4++;
        }
    }
    std::cout<< counter4 << std::endl;
    hist1d->Draw("E1");                
    c1->SaveAs(("plots/dzerr_dist/dzerr_" + filebasename + ".png").c_str());
    delete hist1d;
    delete c1;
}


void dz_eta_correl(TTree *tree, std::string filebasename){
    Float_t trk_dz[1000], trk_eta[1000];
    Int_t ntrk;

    tree->SetBranchAddress("trk_dz", trk_dz);
    tree->SetBranchAddress("trk_eta", trk_eta);
    tree->SetBranchAddress("ntrk", &ntrk);
        
    TCanvas *c1 = new TCanvas("Figure","Figure",1000,800);
    TH2F* hist2d = new TH2F(("dz vs eta from " + filebasename).c_str(), "dz eta correl", 400, -0.5, 0.5, 400, -3.0, 3.0);
    hist2d->GetXaxis()->SetTitle("dz");
    hist2d->GetYaxis()->SetTitle("#eta");
    //c1->SetLogy();

    Long64_t nentries = tree->GetEntries();
    Int_t counter4 = 0;
    for (Int_t i = 0; i < nentries; i++) {
        tree->GetEntry(i);
        if(ntrk == 4){
            for(Int_t i_trk = 0; i_trk < ntrk; i_trk++){
                hist2d->Fill(trk_dz[i_trk], trk_eta[i_trk]);
            }
            
            counter4++;
        }
    }
    std::cout<< counter4 << std::endl;
    hist2d->Draw();                
    c1->SaveAs(("plots/dz_eta_correl/dz_eta_" + filebasename + ".png").c_str());
    delete hist2d;
    delete c1;
}


void dxy_phi_correl(TTree *tree, std::string filebasename){
    Float_t trk_dxy[1000], trk_phi[1000];
    Int_t ntrk;

    tree->SetBranchAddress("trk_dxy", trk_dxy);
    tree->SetBranchAddress("trk_phi", trk_phi);
    tree->SetBranchAddress("ntrk", &ntrk);
        
    TCanvas *c1 = new TCanvas("Figure","Figure",1000,800);
    TH2F* hist2d = new TH2F(("dxy vs phi from " + filebasename).c_str(), "dxy phi correl", 400, -0.3, 0.3, 400, -3.14, 3.14);
    hist2d->GetXaxis()->SetTitle("dxy");
    hist2d->GetYaxis()->SetTitle("#phi");
    //c1->SetLogy();

    Long64_t nentries = tree->GetEntries();
    Int_t counter4 = 0;
    for (Int_t i = 0; i < nentries; i++) {
        tree->GetEntry(i);
        if(ntrk == 4){
            for(Int_t i_trk = 0; i_trk < ntrk; i_trk++){
                hist2d->Fill(trk_dxy[i_trk], trk_phi[i_trk]);
            }
            
            counter4++;
        }
    }
    std::cout<< counter4 << std::endl;
    hist2d->Draw();                
    c1->SaveAs(("plots/dxy_phi_correl/dxy_phi_" + filebasename + ".png").c_str());
    delete hist2d;
    delete c1;
}


void dxy_dist(TTree *tree, std::string filebasename){
    Float_t trk_dxy[1000], trk_dxyerr[1000];
    Int_t ntrk;

    tree->SetBranchAddress("trk_dxy", trk_dxy);
    tree->SetBranchAddress("trk_dxyerr", trk_dxyerr);
    tree->SetBranchAddress("ntrk", &ntrk);
        
    TCanvas *c1 = new TCanvas("Figure","Figure",1000,800);
    TH1F* hist1d = new TH1F(("dxy from" + filebasename).c_str(), "dxy", 400, 0.0, 0.15);
    hist1d->GetXaxis()->SetTitle("dxy");
    //c1->SetLogy();

    Long64_t nentries = tree->GetEntries();
    Int_t counter4 = 0;
    for (Int_t i = 0; i < nentries; i++) {
        tree->GetEntry(i);
        if(ntrk == 4){
            for(Int_t i_trk = 0; i_trk < ntrk; i_trk++){
                //Choose what to plot
                //hist1d->Fill(trk_dxy[i_trk]);
                hist1d->Fill(trk_dxyerr[i_trk]);
            }
            
            counter4++;
        }
    }
    std::cout<< counter4 << std::endl;
    hist1d->Draw("E1");                
    c1->SaveAs(("plots/dxyerr_dist/dxy_" + filebasename + ".png").c_str());
    delete hist1d;
    delete c1;
}



            
        
