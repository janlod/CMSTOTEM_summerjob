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

// This needs to be shortened and optimised, especially the option selction, right now very much code duplication
void primVertex_dist(TTree *tree, std::string filebasename, int option){
    if(option == 3){
        Float_t zPV;
        Int_t ntrk;
    
        tree->SetBranchAddress("zPV", &zPV);
        tree->SetBranchAddress("ntrk", &ntrk);
            
        TCanvas *c1 = new TCanvas("Figure","Figure",1000,800);
        TH1F* hist1d = new TH1F(("zPV from " + filebasename).c_str(), "zPV", 400, -15.0, 15.0);
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
         
        TF1* gausFit = new TF1("gausFit", "gaus", -5.0, 5.0);
        std::cout << "Fit for " << filebasename << ".root" <<std::endl;
        hist1d->Fit(gausFit, "R");

        gausFit->SetLineColor(kRed);
        gausFit->SetLineWidth(2);

        double amplitude = gausFit->GetParameter(0);
        double mean      = gausFit->GetParameter(1);
        double sigma     = gausFit->GetParameter(2);


        TPaveText* pave = new TPaveText(0.125, 0.7, 0.425, 0.88, "NDC"); 
        pave->SetFillColor(0);     
        pave->SetTextAlign(12);    
        pave->SetTextSize(0.03);   
        pave->AddText(Form("Gaussian Fit:"));
        pave->AddText(Form("Mean = %.3f", mean));
        pave->AddText(Form("Sigma = %.3f", sigma));
        pave->AddText(Form("Amplitude = %.1f", amplitude));
          
        hist1d->Draw("E1");
        gausFit->Draw("same"); 
        pave->Draw("same");
        c1->SaveAs(("plots/zPV_dist/zPV_" + filebasename + ".png").c_str());


        delete hist1d;
        delete gausFit;
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
    TH1F* hist1d = new TH1F(("dz/dzerr from" + filebasename).c_str(), "dz/dzerr", 400, -4, 4);
    hist1d->GetXaxis()->SetTitle("dz/dzerr");
    //c1->SetLogy();

    Long64_t nentries = tree->GetEntries();
    Int_t counter4 = 0;
    for (Int_t i = 0; i < nentries; i++) {
        tree->GetEntry(i);
        if(ntrk == 4){
            for(Int_t i_trk = 0; i_trk < ntrk; i_trk++){
                //Choose what to plot
                hist1d->Fill(trk_dz[i_trk]/trk_dzerr[i_trk]);
                
            }
            
            counter4++;
        }
    }
    //std::cout<< counter4 << std::endl;
    TF1* gausFit = new TF1("gausFit", "gaus", -1, 1);
    std::cout << "Fit for " << filebasename << ".root" <<std::endl;
    hist1d->Fit(gausFit, "R");

    gausFit->SetLineColor(kRed);
    gausFit->SetLineWidth(2);

    // Extract fit parameters
    double amplitude = gausFit->GetParameter(0);
    double mean      = gausFit->GetParameter(1);
    double sigma     = gausFit->GetParameter(2);

    // Create a TPaveText in NDC (normalized device coords, 0-1 range)
    TPaveText* pave = new TPaveText(0.125, 0.7, 0.425, 0.88, "NDC"); 
    pave->SetFillColor(0);     
    pave->SetTextAlign(12);    
    pave->SetTextSize(0.03);   
    pave->AddText(Form("Gaussian Fit:"));
    pave->AddText(Form("Mean = %.3f", mean));
    pave->AddText(Form("Sigma = %.3f", sigma));
    pave->AddText(Form("Amplitude = %.1f", amplitude));
    

    hist1d->Draw("E1");   
    gausFit->Draw("same");   
    pave->Draw();          
    c1->SaveAs(("plots/dz_dist/dz_" + filebasename + ".png").c_str());
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

TH1D* CropHistogram(TH1D* h_original, double x_min, double x_max) {
    // Get bin range corresponding to x_min and x_max
    int bin_min = h_original->FindBin(x_min);
    int bin_max = h_original->FindBin(x_max);

    int new_nbins = bin_max - bin_min + 1;
    double new_xmin = h_original->GetBinLowEdge(bin_min);
    double new_xmax = h_original->GetBinLowEdge(bin_max + 1); // upper edge

    // Create cropped histogram
    TH1D* h_cropped = new TH1D("h_cropped", "Cropped Histogram;X;Entries", new_nbins, new_xmin, new_xmax);

    for (int i = 1; i <= new_nbins; ++i) {
        int original_bin = bin_min + i - 1;
        double content = h_original->GetBinContent(original_bin);
        double error = h_original->GetBinError(original_bin);
        h_cropped->SetBinContent(i, content);
        h_cropped->SetBinError(i, error);
    }

    return h_cropped;
}


void dxy_phi_correl(TTree *tree, std::string filebasename, bool cut){
    Float_t trk_dxy[1000], trk_phi[1000];
    Int_t ntrk;

    tree->SetBranchAddress("trk_dxy", trk_dxy);
    tree->SetBranchAddress("trk_phi", trk_phi);
    tree->SetBranchAddress("ntrk", &ntrk);
        
    TCanvas *c1 = new TCanvas("Figure","Figure",1000,800);
    TH2F* hist2d = new TH2F(("dxy vs phi from " + filebasename).c_str(), "dxy phi correl", 400, -0.3, 0.3, 400, -3.14, 3.14);
    hist2d->GetXaxis()->SetTitle("dxy");
    hist2d->GetYaxis()->SetTitle("#phi");

    TF1* gausFit = new TF1("gausFit", "gaus", -0.02, 0.02);
    

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
    //hist2d->Draw();              
    //c1->SaveAs(("plots/dxy_phi_correl/dxy_phi_" + filebasename + ".png").c_str());
     if(cut){
            TH1D *histslice = hist2d->ProjectionX("slice");
            histslice->Fit(gausFit, "R");
           
            double mean      = gausFit->GetParameter(1);
            double sigma     = gausFit->GetParameter(2);
            TH1D *cuttedHisto = CropHistogram(histslice, mean-3*sigma, mean +3*sigma);
            gausFit->SetLineColor(kRed);
            gausFit->SetLineWidth(2);

            // cuttedHisto->Draw();
            // gausFit->Draw("same");
            //histslice->Draw();
            cuttedHisto->Draw();

        }
    c1->SaveAs("test.png");
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
    TH1F* hist1d = new TH1F(("dxy/dxyerr from" + filebasename).c_str(), "dxy/dxyerr", 400, -4.5, 4.5);
    hist1d->GetXaxis()->SetTitle("dxy/dxyerr");
    //c1->SetLogy();

    Long64_t nentries = tree->GetEntries();
    Int_t counter4 = 0;
    for (Int_t i = 0; i < nentries; i++) {
        tree->GetEntry(i);
        if(ntrk == 4){
            for(Int_t i_trk = 0; i_trk < ntrk; i_trk++){
                //Choose what to plot
                //hist1d->Fill(trk_dxy[i_trk]);
                hist1d->Fill(trk_dxy[i_trk]/trk_dxyerr[i_trk]);
            }
            
            counter4++;
        }
    }
    //std::cout<< counter4 << std::endl;
    TF1* gausFit = new TF1("gausFit", "gaus", -4.5, 4.5);
    std::cout << "Fit for " << filebasename << ".root" <<std::endl;
    hist1d->Fit(gausFit, "R");

    gausFit->SetLineColor(kRed);
    gausFit->SetLineWidth(2);


    // Extract fit parameters
    double amplitude = gausFit->GetParameter(0);
    double mean      = gausFit->GetParameter(1);
    double sigma     = gausFit->GetParameter(2);

    // Create a TPaveText in NDC (normalized device coords, 0-1 range)
    TPaveText* pave = new TPaveText(0.125, 0.7, 0.425, 0.88, "NDC"); 
    pave->SetFillColor(0);     
    pave->SetTextAlign(12);    
    pave->SetTextSize(0.03);   
    pave->AddText(Form("Gaussian Fit:"));
    pave->AddText(Form("Mean = %.3f", mean));
    pave->AddText(Form("Sigma = %.3f", sigma));
    pave->AddText(Form("Amplitude = %.1f", amplitude));
    

    hist1d->Draw("E1");  
    gausFit->Draw("same"); 
    pave->Draw();             
    c1->SaveAs(("plots/dxy_dist/dxy_" + filebasename + ".png").c_str());
    delete hist1d;
    delete c1;
}


void p_dist(TTree *tree, std::string filebasename){
    Float_t trk_p[1000];
    Int_t ntrk;

    tree->SetBranchAddress("trk_p", trk_p);
    tree->SetBranchAddress("ntrk", &ntrk);
        
    TCanvas *c1 = new TCanvas("Figure","Figure",1000,800);
    TH1F* hist1d = new TH1F(("#trk_momentum from" + filebasename).c_str(), "momentum", 400, 0, 4);
    hist1d->GetXaxis()->SetTitle("p");
    //c1->SetLogy();

    Long64_t nentries = tree->GetEntries();
    Int_t counter4 = 0;
    for (Int_t i = 0; i < nentries; i++) {
        tree->GetEntry(i);
        if(ntrk == 4){
            for(Int_t i_trk = 0; i_trk < ntrk; i_trk++){
                hist1d->Fill(trk_p[i_trk]);
            }
            
            counter4++;
        }
    }


    hist1d->Draw("E1");  
    c1->SaveAs(("plots/p_dist/p_" + filebasename + ".png").c_str());
    delete hist1d;
    delete c1;
}


void pt_eta_correl(TTree *tree, std::string filebasename){
    Float_t trk_pt[1000], trk_eta[1000];
    Int_t ntrk;

    tree->SetBranchAddress("trk_pt", trk_pt);
    tree->SetBranchAddress("trk_eta", trk_eta);
    tree->SetBranchAddress("ntrk", &ntrk);
        
    TCanvas *c1 = new TCanvas("Figure","Figure",1000,800);
    TH2F* hist2d = new TH2F(("pt vs eta from " + filebasename).c_str(), "pt eta correl", 400, 0, 3.0, 400, 0, 3);
    hist2d->GetXaxis()->SetTitle("pt");
    hist2d->GetYaxis()->SetTitle("eta");
    //c1->SetLogy();

    Long64_t nentries = tree->GetEntries();
    Int_t counter4 = 0;
    for (Int_t i = 0; i < nentries; i++) {
        tree->GetEntry(i);
        if(ntrk == 4){
            for(Int_t i_trk = 0; i_trk < ntrk; i_trk++){
                hist2d->Fill(trk_pt[i_trk], trk_eta[i_trk]);
            }
        }
    }
    std::cout<< counter4 << std::endl;
    hist2d->Draw();                
    c1->SaveAs(("plots/pt_dedx_correl/pt_eta_" + filebasename + ".png").c_str());
    delete hist2d;
    delete c1;
}
//Printing array for testing purposes
void print(std::array<std::array<std::array<int, 3>, 2>, 4> arr){ 
    for(int i=0; i<4; i++){
        for(int j=0; j<2; j++){
            for(int k=0; k<3; k++){
                std::cout << "Array entry "<<i<<" "<<j<<" "<<k<<" : "<< arr[i][j][k]<<std::endl; 
            }
        }
    }
}

void loopers_4trks(TTree *tree, std::string filebasename){
    Float_t trk_p[1000];
    Int_t ntrk;
    Int_t trk_q[1000];

    tree->SetBranchAddress("trk_p", trk_p);
    tree->SetBranchAddress("trk_q", trk_q);
    tree->SetBranchAddress("ntrk", &ntrk);


    float minbin = 0;
    float maxbin = 0.1;
    int nbin = 400;
    TCanvas *c1 = new TCanvas("Figure","Figure",1000,800);
    TH1F* hist1 = new TH1F(("Pairing 1 from" + filebasename).c_str(), "|p3+p4|/m", nbin, minbin, maxbin);
    TH1F* hist2 = new TH1F(("Pairing 2 from" + filebasename).c_str(), "|p3+p4|/m", nbin, minbin, maxbin);
    TH1F* hist3 = new TH1F(("Pairing 3 from" + filebasename).c_str(), "|p3+p4|/m", nbin, minbin, maxbin);
    TH1F* hist4 = new TH1F(("Pairing 4 from" + filebasename).c_str(), "|p3+p4|/m", nbin, minbin, maxbin);
    TH1F* hist5 = new TH1F(("Pairing 5 from" + filebasename).c_str(), "|p3+p4|/m", nbin, minbin, maxbin);
    TH1F* hist6 = new TH1F(("Pairing 6 from" + filebasename).c_str(), "|p3+p4|/m", nbin, minbin, maxbin);
    
    hist1->GetXaxis()->SetTitle("|p3+p4|/m");
    hist1->SetMaximum(1.3e3);

    hist2->GetXaxis()->SetTitle("|p3+p4|/m");
    hist2->SetLineColor(kRed);
    
    hist3->GetXaxis()->SetTitle("|p3+p4|/m");
    hist3->SetLineColor(kGreen);
    
    hist4->GetXaxis()->SetTitle("|p3+p4|/m");
    hist4->SetLineColor(kViolet);
    
    hist5->GetXaxis()->SetTitle("|p3+p4|/m");
    hist5->SetLineColor(kCyan);
    
    hist6->GetXaxis()->SetTitle("|p3+p4|/m");
    hist6->SetLineColor(kOrange);

    TLegend *legend = new TLegend(0.45, 0.7, 0.55, 0.88);
    legend->SetBorderSize(0);
    legend->SetFillStyle(0);

    legend->AddEntry(hist1, "Pairing 1", "l");
    legend->AddEntry(hist2, "Pairing 2", "l");
    legend->AddEntry(hist3, "Pairing 3", "l");
    legend->AddEntry(hist4, "Pairing 4", "l");
    legend->AddEntry(hist5, "Pairing 5", "l");
    legend->AddEntry(hist6, "Pairing 6", "l");


    // Mass of possible particles in Mev taken from particle data group
    Float_t massPi = 139.570; 
    Float_t massK = 493.677;
    Float_t massP = 938.272;

    /**
    Multidimensional array holds information on what track is which particle and charge
    particles[trk number][charge][what kind of particle]
    can be 1 or 0*/
    Long64_t nentries = tree->GetEntries();
    int counter4Pions = 0;
    int pionPairCounter = 0;
    for(int event=0; event<nentries; event++){
        tree->GetEntry(event);
        std::vector<int> posPart_trk;
        std::vector<int> negPart_trk;
        
        if(ntrk == 5){
            for(int itrk=0; itrk<ntrk; itrk++){
               if(trk_q[itrk] == -1){
                negPart_trk.push_back(itrk);
                //std::cout<<"Pos"<<std::endl;
               } else if(trk_q[itrk] == 1){
                posPart_trk.push_back(itrk);
                //std::cout<<"Neg"<<std::endl;
               }
            }

            if(negPart_trk.size() > ntrk/2 + 1 || posPart_trk.size() > ntrk/2 + 1){
                continue;
            }
            if(negPart_trk.size() < posPart_trk.size()){
                Float_t p3 = trk_p[negPart_trk.at(0)];
                Float_t p4 = trk_p[posPart_trk.at(0)];
                hist1->Fill(abs(p3+p4)/massPi);

                p3 = trk_p[negPart_trk.at(0)];
                p4 = trk_p[posPart_trk.at(1)];
                hist2->Fill(abs(p3+p4)/massPi);
                
                p3 = trk_p[negPart_trk.at(0)];
                p4 = trk_p[posPart_trk.at(2)];
                hist3->Fill(abs(p3+p4)/massPi);

                p3 = trk_p[negPart_trk.at(1)];
                p4 = trk_p[posPart_trk.at(0)];
                hist4->Fill(abs(p3+p4)/massPi);

                p3 = trk_p[negPart_trk.at(1)];
                p4 = trk_p[posPart_trk.at(1)];
                hist5->Fill(abs(p3+p4)/massPi);

                p3 = trk_p[negPart_trk.at(1)];
                p4 = trk_p[posPart_trk.at(2)];
                hist6->Fill(abs(p3+p4)/massPi);
            }else if(negPart_trk.size() > posPart_trk.size()){
                Float_t p3 = trk_p[posPart_trk.at(0)];
                Float_t p4 = trk_p[negPart_trk.at(0)];
                hist1->Fill(abs(p3+p4)/massPi);

                p3 = trk_p[posPart_trk.at(0)];
                p4 = trk_p[negPart_trk.at(1)];
                hist2->Fill(abs(p3+p4)/massPi);
                
                p3 = trk_p[posPart_trk.at(0)];
                p4 = trk_p[negPart_trk.at(2)];
                hist3->Fill(abs(p3+p4)/massPi);

                p3 = trk_p[posPart_trk.at(1)];
                p4 = trk_p[negPart_trk.at(0)];
                hist4->Fill(abs(p3+p4)/massPi);

                p3 = trk_p[posPart_trk.at(1)];
                p4 = trk_p[negPart_trk.at(1)];
                hist5->Fill(abs(p3+p4)/massPi);

                p3 = trk_p[posPart_trk.at(1)];
                p4 = trk_p[negPart_trk.at(2)];
                hist6->Fill(abs(p3+p4)/massPi);
            }else{
            std::cout<<"Logic incomplete"<<std::endl;
            }
            
        } 
    }
    hist1->Draw();
    hist2->Draw("same");
    hist3->Draw("same");
    hist4->Draw("same");
    hist5->Draw("same");
    hist6->Draw("same");
    
    legend->Draw();

    c1->SaveAs(("plots/loopers_4trks/4trksloopers" + filebasename + ".png").c_str());
}

void loopers_2trks(TTree *tree, std::string filebasename){
    
    Float_t trk_p[1000];
    Int_t ntrk;
    Int_t trk_q[1000], trk_isK[1000], trk_isPi[1000], trk_isP[1000];

    tree->SetBranchAddress("trk_p", trk_p);
    tree->SetBranchAddress("trk_q", trk_q);
    tree->SetBranchAddress("ntrk", &ntrk);

    TCanvas *c1 = new TCanvas("Figure","Figure",1000,800);
    TH1F* hist1 = new TH1F((" " + filebasename).c_str(), "|p3+p4|/m", 400, 0, 5);
    TH1F* hist2 = new TH1F(("Pairing 2 " + filebasename).c_str(), "|p3+p4|/m", 400, 0, 5);

    TLegend *legend = new TLegend(0.45, 0.7, 0.55, 0.88);
    legend->SetBorderSize(0);
    legend->SetFillStyle(0);

    hist1->GetXaxis()->SetTitle("|p3+p4|/m");
    hist2->SetLineColor(kRed);

    legend->AddEntry(hist1, "Pairing 1", "l");
    legend->AddEntry(hist2, "Pairing 2", "l");

    // Mass of possible particles in Mev taken from particle data group
    Float_t massPi = 139.570; 
    Float_t massK = 493.677;
    Float_t massP = 938.272;

    Long64_t nentries = tree->GetEntries();
    int counter3 = 0;
    for (int event=0; event<nentries; event++){
        
        tree->GetEntry(event);
        std::vector<int> negPart_trk;
        std::vector<int> posPart_trk;
        if(ntrk == 3){
            counter3++;
            for(int itrk=0; itrk<ntrk; itrk++){
               if(trk_q[itrk] == -1){
                negPart_trk.push_back(itrk);
                //std::cout<<"Pos"<<std::endl;
               } else if(trk_q[itrk] == 1){
                posPart_trk.push_back(itrk);
                //std::cout<<"Neg"<<std::endl;
               }
            }
            std::cout<<"HALLOOO"<<negPart_trk.size()<<std::endl;
            if(negPart_trk.size() < posPart_trk.size()){
                Float_t p3 = trk_p[negPart_trk.at(0)];
                Float_t p4 = trk_p[posPart_trk.at(0)];
                std::cout<< abs(p3+p4)/massPi <<std::endl;
                hist1->Fill(abs(p3+p4)/massPi);

                p3 = trk_p[negPart_trk.at(0)];
                p4 = trk_p[posPart_trk.at(1)];
                hist2->Fill(abs(p3+p4)/massPi);
            }else if(negPart_trk.size() > posPart_trk.size()){
                Float_t p3 = trk_p[posPart_trk.at(0)];
                Float_t p4 = trk_p[negPart_trk.at(0)];
                hist1->Fill(abs(p3+p4)/massPi);
                std::cout<< abs(p3+p4)/massPi <<std::endl;

                p3 = trk_p[posPart_trk.at(0)];
                p4 = trk_p[negPart_trk.at(1)];
                hist2->Fill(abs(p3+p4)/massPi);
            }else{
                std::cerr<<"Logic incomplete"<<std::endl;
                continue;
            }
        
        }
    }
    std::cout<<"Number of events with 3 tracks: "<<counter3<<std::endl;
    hist1->Draw();
    hist2->Draw("same");
    legend->Draw();
    c1->SaveAs(("plots/loopers_2trks_alt/2trksloopers" + filebasename + ".png").c_str());
}

// mass is assumed particle mass in MeV
void plot_invar_mass(TTree* tree, std::string filebasename, float massparam){
	Float_t trk_pt[1000], trk_phi[1000], trk_eta[1000];
	Int_t ntrk;

	tree->SetBranchAddress("trk_pt", trk_pt);
	tree->SetBranchAddress("trk_phi", trk_phi);
	tree->SetBranchAddress("trk_eta", trk_eta);
	tree->SetBranchAddress("ntrk", &ntrk);
	

	TCanvas* c1 = new TCanvas("fig", "fig", 1000, 800);
	TH1F* hist = new TH1F(("Invariant mass from " + filebasename+"cutted" ).c_str(), "Invariant mass in MeV", 400, 500, 4000);
	
	Long64_t nentries =  tree->GetEntries();
	for (int event=0; event<nentries; event++){
		std::array<std::array<Float_t, 4>, 4> fourvectors {};
		tree->GetEntry(event);
		if(ntrk==4){
			for(int itrk=0; itrk<ntrk; itrk++){
				 	Float_t px = 0;
					Float_t py = 0;
					Float_t pz = 0;
					Float_t energy = 0;

					px = trk_pt[itrk]*cos(trk_phi[itrk]);
					py = trk_pt[itrk]*sin(trk_phi[itrk]);
					pz = trk_pt[itrk]*sinh(trk_eta[itrk]);
					energy = sqrt(massparam*massparam + trk_pt[itrk]*trk_pt[itrk] + pz*pz);
					
					fourvectors[itrk][0] = energy;
					fourvectors[itrk][1] = px;
					fourvectors[itrk][2] = py;
					fourvectors[itrk][3] = pz;

			}
		std::array<Float_t, 4> comb_fourvector {};
			for(int j=0; j<4; j++){
				comb_fourvector[0] += fourvectors[j][0];
				comb_fourvector[1] += fourvectors[j][1];
				comb_fourvector[2] += fourvectors[j][2];
				comb_fourvector[3] += fourvectors[j][3];
			}
			Float_t total_mass = 0.0;
			total_mass = sqrt(comb_fourvector[0]*comb_fourvector[0] - comb_fourvector[1]*comb_fourvector[1] 
					- comb_fourvector[2]*comb_fourvector[2] - comb_fourvector[3]*comb_fourvector[3]);
			
			//std::cout<<total_mass*1000<<std::endl;
			hist->Fill(total_mass*1000);
		}
	}
	hist->Draw("E");
	TLine *line = new TLine(2220, 0, 2220, hist->GetMaximum());
	line->SetLineColor(kRed);
	line->SetLineWidth(2);  // Optional: makes line thicker
	line->Draw("same");
	
	
	c1->SaveAs(("invariant_mass_pion/inv_mass"+filebasename+"cutted.png").c_str());
	
}




            
        
