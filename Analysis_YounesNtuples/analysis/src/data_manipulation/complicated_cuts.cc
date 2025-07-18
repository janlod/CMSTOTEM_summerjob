#include "data_manipulation/complicated_cuts.h"

void cut_zPV(TTree* tree, std::string filebasename){
            Float_t zPV;
	    Int_t ntrk;

	    tree->SetBranchAddress("zPV", &zPV);
	    tree->SetBranchAddress("ntrk", &ntrk);
	    
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


	   TFile* outfile = TFile::Open(("../../data/cutted_data/zPV/zPVcutted"+filebasename+".root").c_str(), "RECREATE");
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
	    TFile* outfile = TFile::Open(("../../data/cutted_data/dz/dzcutted"+filebasename+".root").c_str(), "RECREATE");
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



bool isin_3sigma(Float_t val, std::array<double,3> fitparams){
	    Float_t mean =(Float_t)fitparams.at(1);
	    Float_t sigma =(Float_t)fitparams.at(2);

	    return (val <= mean + 3*sigma && val >= mean - 3*sigma);
}



TH1F* get1D_hist_eventvar(TTree* tree, std::string svar, float nbin, float minbin, float maxbin){
	    Float_t var;
	    Int_t ntrk;
	    tree->SetBranchAddress(svar.c_str(), &var);
	    tree->SetBranchAddress("ntrk", &ntrk);

	    TH1F* hist = new TH1F(svar.c_str(), svar.c_str(), nbin, minbin, maxbin);
	    
	    Long64_t nentries = tree->GetEntries();
	    for(int event=0; event<nentries; event++){
		tree->GetEntry(event);
		if(ntrk==4){
			hist->Fill(var);
		}
	    }

	   return hist;
}



TH1F* get1D_hist_trkvar(TTree* tree, std::string svar, std::string svarerr, int nbin, float minbin, float maxbin){
	    Float_t var[1000];
	    Float_t varerr[1000];
	    Int_t ntrk;
	    tree->SetBranchAddress(svar.c_str(), var);
	    tree->SetBranchAddress(svarerr.c_str(), varerr); 
	    tree->SetBranchAddress("ntrk", &ntrk);

	    TH1F* hist = new TH1F(svar.c_str(), svar.c_str(), nbin, minbin, maxbin);
	    
	    Long64_t nentries = tree->GetEntries();
	    for(int event=0; event<nentries; event++){
		tree->GetEntry(event);
		if(ntrk==4){
			for(int itrk=0; itrk<ntrk; itrk++){	
				hist->Fill(var[itrk]/varerr[itrk]);
			}
		}
	    }

	   return hist;
}
   


TH2F* get2D_hist(TTree* tree, std::string svarX, std::string svarY, int nbinX, float minbinX, float maxbinX, float nbinY, float minbinY, float maxbinY){
	   Float_t varX[1000];
	   Float_t varY[1000];
	   Int_t ntrk;
	   tree->SetBranchAddress(svarX.c_str(), varX);
	   tree->SetBranchAddress(svarY.c_str(), varY);
	   tree->SetBranchAddress("ntrk", &ntrk);

	   TH2F* hist = new TH2F((svarX + " vs. " + svarY).c_str(), (svarX + " vs. " + svarY).c_str(), nbinX, minbinX, maxbinX, nbinY, minbinY, maxbinY);

	 Long64_t nentries = tree->GetEntries();
	for(int event=0; event<nentries; event++){
		tree->GetEvent(event);
		if(ntrk==4){
			for(int itrk=0; itrk<ntrk; itrk++){
				hist->Fill(varX[itrk], varY[itrk]);
			}
		}
	   }
	   hist->GetXaxis()->SetTitle(svarX.c_str());
	   hist->GetYaxis()->SetTitle(svarY.c_str());

	   return hist;
}


//Returned as [ampl, mean, sigma]
std::array<double,3> fitParams1D_gausfit(TH1F* hist, float fitrangeMin, float fitrangeMax){ 
	   TF1* gausfit = new TF1("gausfit", "gaus", fitrangeMin, fitrangeMax);
	   hist->Fit(gausfit, "R");

	   double ampl = gausfit->GetParameter(0); 
	   double mean = gausfit->GetParameter(1); 
	   double sigma = gausfit->GetParameter(2); 

	   return {ampl, mean, sigma};
}


std::map<int, std::array<double, 3>> fitParams2D_gausfit_allSlices(TH2F* hist, float fitrangeMin, float fitrangeMax){
	    std::map<int, std::array<double, 3>> fitParams_map;  
	    int nbinsY = hist->GetNbinsY();
	    int nbinsX = hist->GetNbinsX();
	    
	    for(int ybin=1; ybin<=nbinsY; ybin++){
	    	TH1F* projx = new TH1F("projx", "Slice along x-axis", nbinsX, hist->GetXaxis()->GetXmin(), hist->GetXaxis()->GetXmax());

		for(int xbin=1; xbin<=nbinsX; xbin++){
			projx->SetBinContent(xbin, (Float_t)hist->GetBinContent(xbin, ybin));
		}
		
		std::array<double, 3> fitParams = fitParams1D_gausfit(projx, fitrangeMin, fitrangeMax);
		fitParams_map.insert({ybin, fitParams});
		
		// Save apicture for every 20th slice with the fit
		
		if(ybin%20==0){
			TCanvas* c1 = new TCanvas("slicetest", "slicetest", 1000, 800);
			TF1* gaus = new TF1("gaus", "[0]*exp(-0.5*((x-[1])/[2])**2)", fitrangeMin, fitrangeMax);
			gaus->SetParameters(fitParams.at(0), fitParams.at(1), fitParams.at(2));
			projx->GetXaxis()->SetTitle(hist->GetXaxis()->GetTitle());
			projx->Draw();
			gaus->SetLineColor(kRed);
			gaus->Draw("same");
			auto pave = new TPaveText(0.15,0.75,0.4,0.9,"NDC");
			pave->SetFillColor(0);
			pave->SetBorderSize(1);
			pave->SetTextAlign(12);
			pave->SetTextSize(0.03);
			pave->AddText(Form("Mean = %.3f", fitParams.at(1)));
			pave->AddText(Form("Sigma = %.3f", fitParams.at(2)));
			pave->AddText(Form("Amplitude = %.1f",fitParams.at(0)));
			pave->Draw();
			gPad->Update();

			std::string xvar = hist->GetXaxis()->GetTitle();
			std::string yvar = hist->GetYaxis()->GetTitle();
			xvar = xvar.erase(0,4);
			yvar = yvar.erase(0,4);	
			std::string filename = "../../plots/sliceplots/" + xvar + "_" + yvar + "/sliceat" + std::to_string(ybin) + ".png";
			c1->SaveAs(filename.c_str());
		}
		delete projx;
	    }

	    return fitParams_map;
}



void cut_3sigma(TTree* tree, std::string filebasename){	
	   TFile* outfile = TFile::Open(("cutted_data/" + filebasename + "cutted.root").c_str(), "RECREATE");
	   TTree* cuttedTree = tree->CloneTree(0);

	   TH1F* zPV_hist = get1D_hist_eventvar(tree, "zPV", 400, -15, 15);
	   TH1F* dxy_hist = get1D_hist_trkvar(tree, "trk_dxy", "trk_dxyerr", 400, -4, 4);
	   TH1F* dz_hist = get1D_hist_trkvar(tree, "trk_dz", "trk_dzerr", 400, -4, 4);

	   // You need to choose y range such that all data is included otherwise you get an outof bounds error
	   // range for phi and eta is -pi to pi
	   TH2F* dxy_phi_hist = get2D_hist(tree, "trk_dxy", "trk_phi", 400, -.3, .3, 400, -3.2, 3.2);
	   TH2F* dz_eta_hist = get2D_hist(tree, "trk_dz", "trk_eta", 400, -.5, .5, 400, -3.2, 3.2);

	   auto zPV_fitParams = fitParams1D_gausfit(zPV_hist, -5,5);
	   auto dxy_fitParams = fitParams1D_gausfit(dxy_hist, -1, 1);
	   auto dz_fitParams = fitParams1D_gausfit(dz_hist, -1, 1);
	   auto dxy_phi_fitParams_map = fitParams2D_gausfit_allSlices(dxy_phi_hist, -0.05, 0.05);
	   auto dz_eta_fitParams_map = fitParams2D_gausfit_allSlices(dz_eta_hist, -0.05, 0.05); //BREAKPOINT


	   for (auto& [bin, params] : dz_eta_fitParams_map) {
	  	float eta_center = dz_eta_hist->GetYaxis()->GetBinCenter(bin);
	    	std::cout << "Bin " << bin << " eta: " << eta_center
			      << " mean: " << params.at(1)
		     		 << " sigma: " << params.at(2)
		     		 << std::endl;
	   }


	   Long64_t nentries = tree->GetEntries();
	   // Scalars
	   Int_t ntrk, trk_q[1000], trk_isPi[1000], trk_isK[1000], trk_isP[1000];
	   ULong64_t EventNum, tree_prot_EventNum;
	   UInt_t Run, LumiSection, tree_prot_Run;
	   Float_t zPV, xPV, yPV;
	   Float_t alltrk_mass, alltrk_pt;
	   Float_t ThxR, ThyR, ThxL, ThyL;

	   // Float arrays
	   Float_t trk_p[1000], trk_pt[1000], trk_eta[1000], trk_phi[1000];
	   Float_t trk_dz[1000], trk_dxy[1000];
	   Float_t trk_dedx[1000], trk_dedxerr[1000];
	   Float_t trk_dxyerr[1000], trk_dzerr[1000], trk_pterr[1000];
	   Int_t trk_nSaturMeasure[1000], trk_nMeasure[1000], trk_nMeasureLayer[1000];

	   // Double (for prot branches)
	   Double_t pr_px_a, pr_px_b, pr_py_a, pr_py_b, pr_pz_a, pr_pz_b;
	   Double_t pr_ptx_a, pr_ptx_b, pr_pty_a, pr_pty_b;
	   Double_t pr_ptx_sigma_a, pr_ptx_sigma_b, pr_pty_sigma_a, pr_pty_sigma_b;
	   Double_t pr_posx_a, pr_posx_b, pr_posy_a, pr_posy_b;
	   Double_t pr_posx_sigma_a, pr_posx_sigma_b, pr_posy_sigma_a, pr_posy_sigma_b;

	   tree->SetBranchAddress("Run", &Run);
	   tree->SetBranchAddress("EventNum", &EventNum);
	   tree->SetBranchAddress("LumiSection", &LumiSection);
	   tree->SetBranchAddress("zPV", &zPV);
	   tree->SetBranchAddress("xPV", &xPV);
	   tree->SetBranchAddress("yPV", &yPV);
	   tree->SetBranchAddress("ntrk", &ntrk);
	   tree->SetBranchAddress("trk_p", trk_p);
	   tree->SetBranchAddress("trk_pt", trk_pt);
	   tree->SetBranchAddress("trk_eta", trk_eta);
 	   tree->SetBranchAddress("trk_phi", trk_phi);
	   tree->SetBranchAddress("trk_q", trk_q);
	   tree->SetBranchAddress("alltrk_mass", &alltrk_mass);
	   tree->SetBranchAddress("alltrk_pt", &alltrk_pt);
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
	   tree->SetBranchAddress("ThxR", &ThxR);
	   tree->SetBranchAddress("ThyR", &ThyR);
	   tree->SetBranchAddress("ThxL", &ThxL);
	   tree->SetBranchAddress("ThyL", &ThyL);
	   tree->SetBranchAddress("tree_prot_Run", &tree_prot_Run);
	   tree->SetBranchAddress("tree_prot_EventNum", &tree_prot_EventNum);
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



	   for(int event=0; event<nentries; event++){
		 tree->GetEntry(event); 
		 bool zPV_cut = isin_3sigma(zPV, zPV_fitParams);

		 if(ntrk==4){
			int dxy_good = 0;
			int dz_good = 0;
			int dxy_phi_good = 0;
			int dz_eta_good =0;
			for(int itrk=0; itrk<ntrk; itrk++){
				if(abs(trk_eta[itrk])<1.5){
					if(isin_3sigma(trk_dxy[itrk]/trk_dxyerr[itrk], dxy_fitParams)){
					dxy_good++;
					}
					if(isin_3sigma(trk_dz[itrk]/trk_dzerr[itrk], dz_fitParams)){
						dz_good++;
					}
					Float_t phi = trk_phi[itrk];
					Float_t eta = trk_eta[itrk];
					Float_t dxy = trk_dxy[itrk];
					Float_t dz = trk_dz[itrk];
					int phi_bin = dxy_phi_hist->GetYaxis()->FindBin(phi);
					int eta_bin = dz_eta_hist->GetYaxis()->FindBin(eta);
					//std::cout<<phi_bin<<std::endl;
					//std::cout<<eta_bin<<std::endl;
					//std::cout<<"\n\n";
					if(isin_3sigma(dxy, dxy_phi_fitParams_map.at(phi_bin))){
						dxy_phi_good++;
					}
					if(isin_3sigma(dz, dz_eta_fitParams_map.at(eta_bin))){
						dz_eta_good++;
					}


				}
			}
			if(zPV_cut && dxy_good==4 && dz_good==4 && dxy_phi_good==4  && dz_eta_good==4){
				tree->GetEntry(event);
				cuttedTree->Fill();		
			}
		 }
		
	   }
	   cuttedTree->Write();
	   outfile->Close();
}



void quick2Dplot(std::string filename, std::string svarX, std::string svarY, int nbinX, float minbinX, float maxbinX, float nbinY, float minbinY, float maxbinY){
        TFile* file = new TFile(filename.c_str(), "read");
       	TTree* tree = (TTree*)file->Get("tree");	
	TCanvas* c1 = new TCanvas("fig", "fig", 1000, 800);
	TH2F* hist = get2D_hist(tree, svarX, svarY, nbinX, minbinX, maxbinX, nbinY, minbinY, maxbinY);
       	hist->Draw();

	std::string filebasename = filename.erase(filename.size() - 5);
	filebasename = filebasename.erase(0,12);
	c1->SaveAs("testitest.png");
	//c1->SaveAs(("cutted_data/plots/dxy_phi/dxy_phi_correl" + filebasename + ".png").c_str());

	file->Close();
}


void quick1Dplot(std::string filename, std::string svar, std::string svarerr, int nbin, float minbin, float maxbin, int trkvar){
        TFile* file = new TFile(filename.c_str(), "read");
	std::string filebasename = filename.erase(filename.size() - 5);
        filebasename = filebasename.erase(0,12);

       	TTree* tree = (TTree*)file->Get("tree");	
	TCanvas* c1 = new TCanvas("fig", "fig", 1000, 800);
	TH1F* hist;
	if(trkvar==0){
		 hist = get1D_hist_eventvar(tree, svar, nbin, minbin, maxbin);
	}else{
		 hist = get1D_hist_trkvar(tree, svar, svarerr, nbin, minbin, maxbin);
		 hist->GetXaxis()->SetTitle((svar + "/" + svarerr).c_str());
	}
       	hist->Draw();
	c1->SaveAs(("cutted_data/plots/dz_dist/dzBydzerr" + filebasename + ".png").c_str());
	file->Close();
}
