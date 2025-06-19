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


namespace fs = std::filesystem;

void analysis(){
    std::string line;
    std::ifstream file;
    std::vector<std::string> fileList;
    file.open("dataFileList.txt");
    if(file.is_open()){
        while (getline(file, line)){
            fileList.push_back(line);
        }
        file.close();
    }

    // Scalar branches
    UInt_t Run;
    ULong64_t EventNum;
    UInt_t LumiSection;
    Float_t zPV, xPV, yPV;
    Int_t ntrk;
    Float_t alltrk_mass, alltrk_pt;
    Float_t ThxR, ThyR, ThxL, ThyL;
    UInt_t tree_prot_Run;
    ULong64_t tree_prot_EventNum;

    // Variable-length arrays (size = ntrk)
    Float_t* trk_p = new Float_t[1000];
    Float_t* trk_pt = new Float_t[1000];
    Float_t* trk_eta = new Float_t[1000];
    Float_t* trk_phi = new Float_t[1000];
    Int_t*   trk_q = new Int_t[1000];
    Int_t*   trk_isPi = new Int_t[1000];
    Int_t*   trk_isK = new Int_t[1000];
    Int_t*   trk_isP = new Int_t[1000];
    Float_t* trk_dz = new Float_t[1000];
    Float_t* trk_dxy = new Float_t[1000];
    Float_t* trk_dedx = new Float_t[1000];
    Float_t* trk_dedxerr = new Float_t[1000];
    Int_t*   trk_nSaturMeasure = new Int_t[1000];
    Int_t*   trk_nMeasure = new Int_t[1000];
    Int_t*   trk_nMeasureLayer = new Int_t[1000];
    Float_t* trk_dxyerr = new Float_t[1000];
    Float_t* trk_dzerr = new Float_t[1000];
    Float_t* trk_pterr = new Float_t[1000];

    // Proton-related scalars
    Double_t pr_px_a, pr_px_b;
    Double_t pr_py_a, pr_py_b;
    Double_t pr_pz_a, pr_pz_b;
    Double_t pr_ptx_a, pr_ptx_b;
    Double_t pr_pty_a, pr_pty_b;
    Double_t pr_ptx_sigma_a, pr_ptx_sigma_b;
    Double_t pr_pty_sigma_a, pr_pty_sigma_b;
    Double_t pr_posx_a, pr_posx_b;
    Double_t pr_posy_a, pr_posy_b;
    Double_t pr_posx_sigma_a, pr_posx_sigma_b;
    Double_t pr_posy_sigma_a, pr_posy_sigma_b;

    int listSize = fileList.size();
    for (int ifile=0; ifile<listSize; ifile++){
        std::string filename = fileList.at(ifile);
        TFile *rootfile = new TFile(("../YounesNtuples/" + filename).c_str(), "read");
        TTree *tree = (TTree*)rootfile->Get("tree");

        std::string filebasename = filename.erase(filename.size() - 5);
        
        tree->SetBranchAddress("Run", &Run);
        tree->SetBranchAddress("EventNum", &EventNum);
        tree->SetBranchAddress("LumiSection", &LumiSection);
        tree->SetBranchAddress("zPV", &zPV);
        tree->SetBranchAddress("xPV", &xPV);
        tree->SetBranchAddress("yPV", &yPV);
        tree->SetBranchAddress("ntrk", &ntrk);
        tree->SetBranchAddress("alltrk_mass", &alltrk_mass);
        tree->SetBranchAddress("alltrk_pt", &alltrk_pt);
        tree->SetBranchAddress("ThxR", &ThxR);
        tree->SetBranchAddress("ThyR", &ThyR);
        tree->SetBranchAddress("ThxL", &ThxL);
        tree->SetBranchAddress("ThyL", &ThyL);
        tree->SetBranchAddress("tree_prot_Run", &tree_prot_Run);
        tree->SetBranchAddress("tree_prot_EventNum", &tree_prot_EventNum);

        // Variable-length branches
        tree->SetBranchAddress("trk_p", trk_p);
        tree->SetBranchAddress("trk_pt", trk_pt);
        tree->SetBranchAddress("trk_eta", trk_eta);
        tree->SetBranchAddress("trk_phi", trk_phi);
        tree->SetBranchAddress("trk_q", trk_q);
        tree->SetBranchAddress("trk_isPi", trk_isPi);
        tree->SetBranchAddress("trk_isK", trk_isK);
        tree->SetBranchAddress("trk_isP", trk_isP);
        tree->SetBranchAddress("trk_dz", trk_dz);
        tree->SetBranchAddress("trk_dxy", trk_dxy);
        tree->SetBranchAddress("trk_dedx", trk_dedx);
        tree->SetBranchAddress("trk_dedxerr", trk_dedxerr);
        tree->SetBranchAddress("trk_nSaturMeasure", trk_nSaturMeasure);
        tree->SetBranchAddress("trk_nMeasure", trk_nMeasure);
        tree->SetBranchAddress("trk_nMeasureLayer", trk_nMeasureLayer);
        tree->SetBranchAddress("trk_dxyerr", trk_dxyerr);
        tree->SetBranchAddress("trk_dzerr", trk_dzerr);
        tree->SetBranchAddress("trk_pterr", trk_pterr);

        // Proton-related
        tree->SetBranchAddress("pr_px_a", &pr_px_a);
        tree->SetBranchAddress("pr_px_b", &pr_px_b);
        tree->SetBranchAddress("pr_py_a", &pr_py_a);
        tree->SetBranchAddress("pr_py_b", &pr_py_b);
        tree->SetBranchAddress("pr_pz_a", &pr_pz_a);
        tree->SetBranchAddress("pr_pz_b", &pr_pz_b);
        tree->SetBranchAddress("pr_ptx_a", &pr_ptx_a);
        tree->SetBranchAddress("pr_ptx_b", &pr_ptx_b);
        tree->SetBranchAddress("pr_pty_a", &pr_pty_a);
        tree->SetBranchAddress("pr_pty_b", &pr_pty_b);
        tree->SetBranchAddress("pr_ptx_sigma_a", &pr_ptx_sigma_a);
        tree->SetBranchAddress("pr_ptx_sigma_b", &pr_ptx_sigma_b);
        tree->SetBranchAddress("pr_pty_sigma_a", &pr_pty_sigma_a);
        tree->SetBranchAddress("pr_pty_sigma_b", &pr_pty_sigma_b);
        tree->SetBranchAddress("pr_posx_a", &pr_posx_a);
        tree->SetBranchAddress("pr_posx_b", &pr_posx_b);
        tree->SetBranchAddress("pr_posy_a", &pr_posy_a);
        tree->SetBranchAddress("pr_posy_b", &pr_posy_b);
        tree->SetBranchAddress("pr_posx_sigma_a", &pr_posx_sigma_a);
        tree->SetBranchAddress("pr_posx_sigma_b", &pr_posx_sigma_b);
        tree->SetBranchAddress("pr_posy_sigma_a", &pr_posy_sigma_a);
        tree->SetBranchAddress("pr_posy_sigma_b", &pr_posy_sigma_b);



        TCanvas *c1 = new TCanvas("Figure","Figure",1000,800);
        TH2F* hist = new TH2F("px_correl", "px_correl", 400, -1, 1, 400, -1, 1);
        TH1F* hist1d = new TH1F(("zPV from " + filebasename).c_str(), "zPV", 400, -15, 15);
        TH1F* hist1d2= new TH1F("pr_posx_b", "pr_posx_b", 10, 0, 10);
        hist->GetXaxis()->SetTitle("pr_px_a");
        hist->GetYaxis()->SetTitle("pr_px_b");
        hist1d->GetXaxis()->SetTitle("z");

        Long64_t nentries = tree->GetEntries();
        Int_t counter4 = 0;
        for (Int_t i = 0; i < nentries; i++) {
            tree->GetEntry(i);
            Float_t trk_pt_i = 0.0;
            Float_t trk_px_i = 0.0;
            Float_t trk_py_i = 0.0;
            if (ntrk > 1000) {
                std::cerr << "Warning: ntrk = " << ntrk << " exceeds array size 1000\n";
            continue;  // Skip this event or handle differently
        }

            if(ntrk==4){
                counter4+=1;
                for (Int_t j = 0; j < ntrk; j++) {
                    trk_pt_i += trk_pt[j];
                    trk_px_i += trk_pt[j]*cos(trk_phi[j]);
                    trk_py_i += trk_pt[j]*sin(trk_phi[j]);
                    }
                
                hist->Fill(pr_px_a, pr_px_b); // fill histogram with total momentum per event
                hist1d->Fill(zPV);
            }
            
        }
        std::cout << counter4 << std::endl;
        hist1d->SetLineColor(kBlue);     
        //hist1d2->SetLineColor(kBlue);
        

        TLegend *legend = new TLegend(0.1, 0.75, 0.3, 0.9); 
        legend->AddEntry(hist1d, "a", "l");        
        legend->AddEntry(hist1d2, "b", "l");
        legend->Draw();

        hist1d->Draw();                 // Draw first histogram
        //hist1d2->Draw();
        //hist->Draw();
        c1->SaveAs(("plots/zPV_dist/zPV_" + filebasename + ".png").c_str());
        delete hist;
        delete hist1d;
        delete hist1d2;
        delete legend;
        delete c1;
            
        }
    }

