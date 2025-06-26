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
         
        TF1* gausFit = new TF1("gausFit", "gaus", -15.0, 15.0);
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
    TF1* gausFit = new TF1("gausFit", "gaus", -4, 4);
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

int countNonzeroEntries(std::array<std::array<std::array<int, 3>, 2>, 4> arr){
    int* flat = &arr[0][0][0];
    int entrycounter = 0;
    for (int i = 0; i < 4 * 2 * 3; ++i) {
        if (flat[i] != 0) entrycounter++;
    }
    return entrycounter;
}


int countPions(std::array<std::array<std::array<int, 3>, 2>, 4> arr) {
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (arr[i][j][0] != 0) {
                ++count;
            }
        }
    }
    return count;
}

int countKaons(std::array<std::array<std::array<int, 3>, 2>, 4> arr) {
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (arr[i][j][1] != 0) {
                ++count;
            }
        }
    }
    return count;
}

int countProtons(std::array<std::array<std::array<int, 3>, 2>, 4> arr) {
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (arr[i][j][2] != 0) {
                ++count;
            }
        }
    }
    return count;
}


using Array3D = std::array<std::array<std::array<int, 3>, 2>, 4>;
std::vector<Array3D> arr_vec;

void loopers(TTree *tree, std::string filebasename){
    arr_vec.clear();
    Float_t trk_p[1000];
    Int_t ntrk;
    Int_t trk_q[1000], trk_isK[1000], trk_isPi[1000], trk_isP[1000];

    tree->SetBranchAddress("trk_p", trk_p);
    tree->SetBranchAddress("trk_q", trk_q);
    tree->SetBranchAddress("trk_isK", trk_isK);
    tree->SetBranchAddress("trk_isPi", trk_isPi);
    tree->SetBranchAddress("trk_isP", trk_isP);
    tree->SetBranchAddress("ntrk", &ntrk);

    TCanvas *c1 = new TCanvas("Figure","Figure",1000,800);
    TH1F* hist1 = new TH1F(("Pairing 1 from" + filebasename).c_str(), "|p3+p4|/m", 400, 0, 0.05);
    hist1->GetXaxis()->SetTitle("|p3+p4|/m");

    // Mass of possible particles in Mev taken from particle data group
    Float_t massPi = 139.570; 
    Float_t massK = 493.677;
    Float_t massP = 938.272;

    /**
    Multidimensional array holds information on what track is which particle and charge
    particles[trk number][charge][what kind of particle]
    can be 1 or 0*/
    Long64_t nentries = tree->GetEntries();
    int counter4 = 0;
    int counter4Pions = 0;
    int pionPairCounter = 0;
    for(int event=0; event<nentries; event++){
        tree->GetEntry(event);
        std::array<std::array<std::array<int, 3>, 2>, 4> particles {0};
        
        if(ntrk == 4){
            counter4++;
            for(int itrk=0; itrk<ntrk; itrk++){
                //check if charge has expected values
                if(trk_q[itrk]!=1 && trk_q[itrk]!=-1){
                    std::cerr <<"Unexpected charge +1 or -1 expected" << std::endl;
                    exit(0);
                }
                if(trk_isPi[itrk]!=0){
                    if(trk_q[itrk]==1){
                        //std::cout<<"Pi+ detected"<<std::endl;
                        particles[itrk][1][0] = 1;
                    }else{
                        //std::cout<<"Pi- detected"<<std::endl;
                        particles[itrk][0][0] = 1;
                    }   
                }else if(trk_isK[itrk]!=0){
                    if(trk_q[itrk]==1){
                        //std::cout<<"K+ detected"<<std::endl;
                        particles[itrk][1][1] = 1;
                    }else{
                        //std::cout<<"K+ detected"<<std::endl;
                        particles[itrk][0][1] = 1;
                    }   
                }else if(trk_isP[itrk]!=0){
                    if(trk_q[itrk]==1){
                        //std::cout<<"p+ detected"<<std::endl;
                        particles[itrk][1][2] = 1;
                    }else if(trk_q[itrk]==-1){
                        //std::cout<<"p- detected"<<std::endl;
                       particles[itrk][0][2] = 1;
                    }   
                }  
            }
        
            if(countPions(particles) == 2){
                pionPairCounter++;
            }
            if(countPions(particles) == 4){
                counter4Pions++;
            }

            if(countNonzeroEntries(particles) == 4){
                arr_vec.push_back(particles);
            }
        
        
        }

        
        int poscounter=0;
        int negcounter=0;
        int trkpos=6;
        int trkneg=6;
        // Pairing the particles
        if(countPions(particles) == 2){
            for(int itrk=0; itrk<ntrk; itrk++){
                if(particles[itrk][0][0]!=0){
                    trkneg = itrk;
                    negcounter++;
                }else if(particles[itrk][1][0]!=0){
                    trkpos = itrk;
                    poscounter++;
                }
            }
            // std::cout<<"Pi- track: "<<trkneg<<std::endl;
            // std::cout<<"Pi+ track: "<<trkpos<<std::endl;
            // std::cout<<"# of Pi+: "<<poscounter<<std::endl;
            // std::cout<<"# of Pi-: "<<negcounter<<std::endl;
        }
        if(poscounter==1 && negcounter==1){
            hist1->Fill(abs(trk_p[trkpos] + trk_p[trkneg])/massPi);
        }
    }

    int pions = 0;
    int kaons = 0;
    int protons = 0;
    for(std::array<std::array<std::array<int, 3>, 2>, 4> val : arr_vec){
        pions+=countPions(val);
        kaons+=countKaons(val);
        protons+=countProtons(val);
    }
    int all4identified = arr_vec.size();

    std::cout<<"Selecting events with all 4 tracks identified as Pi, K or p"<<std::endl;
    std::cout<<"Total # of selected events: " << all4identified<<std::endl;
    std::cout<<"Total # of Pions in selected events: "<<pions<<std::endl;
    std::cout<<"Total # of Kaons in selected events: "<<kaons<<std::endl;
    std::cout<<"Total # of Protons in selected events: "<<protons<<std::endl;
    // hist1->Draw();
    // c1->SaveAs(("plots/pion_loopers/Pionloopers_" + filebasename + ".png").c_str());
}







            
        
