#include "tree_analysis/primVertex.h"

void primVertex_dist(TTree *tree, std::string filebasename, int option){

           TCanvas* c1 = new TCanvas("Figure", "Figure", 1000, 800);
           if(option == 3){
                Float_t zPV;
                Int_t ntrk;

                tree->SetBranchAddress("zPV", &zPV);
                tree->SetBranchAddress("ntrk", &ntrk);

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
                c1->SaveAs(("../../plots/zPV_dist/zPV_" + filebasename + ".png").c_str());


                delete hist1d;
                delete gausFit;
                delete c1;


            }else if(option == 2){
                Float_t yPV;
                Int_t ntrk;

                tree->SetBranchAddress("yPV", &yPV);
                tree->SetBranchAddress("ntrk", &ntrk);

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
                c1->SaveAs(("../../plots/yPV_dist/yPV_" + filebasename + ".png").c_str());
                delete hist1d;
                delete c1;


            }else if(option == 1){
                Float_t xPV;
                Int_t ntrk;

                tree->SetBranchAddress("xPV", &xPV);
                tree->SetBranchAddress("ntrk", &ntrk);
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
                c1->SaveAs(("../../plots/xPV_dist/xPV_" + filebasename + ".png").c_str());
                delete hist1d;
                delete c1;


            }else if(option == 4){
                Float_t xPV, yPV;
                Int_t ntrk;

                tree->SetBranchAddress("xPV", &xPV);
                tree->SetBranchAddress("yPV", &yPV);
                tree->SetBranchAddress("ntrk", &ntrk);

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
                c1->SaveAs(("../../plots/rPV_dist/radiusPV_" + filebasename + ".png").c_str());
                delete hist1d;
           }else if(option == 12){
                Float_t xPV, yPV;
                Int_t ntrk;

                tree->SetBranchAddress("xPV", &xPV);
                tree->SetBranchAddress("yPV", &yPV);
                tree->SetBranchAddress("ntrk", &ntrk);

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
                c1->SaveAs(("../../plots/xyPV_dist/xyPV_" + filebasename + ".png").c_str());
                delete hist2d;
                delete c1;

            }else{
                std::cerr << "Invalid option\n Only these are allowed:\n 1 for xPV histo\n 2 for yPV histo\n 3 for zPV histo\n 4 for x^2+y^2 histo\n 12 for xyPV colorplot" <<std::endl;
                exit(0);
            }
}

