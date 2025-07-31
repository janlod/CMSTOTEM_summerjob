#include "invMass_analysis/analysis_inv_mass_hist.h"


TH2F* get2D_inv_mass_hist(std::string treename, std::string filepath, std::string filename, int nbin, float min, float max){
        auto tree = treename.c_str();
        auto file = filepath.c_str();

        ROOT::RDataFrame df(tree, file);

        TH2F* hist = new TH2F(("rec. inv. mass from "+filename).c_str(), "Reconstruncted invariant mass in MeV", nbin, min, max, nbin, min, max);


        int eventnumber = 0;
        int empty_count = 0;
        auto fillhisto = [hist, &eventnumber, &empty_count] (RVecF pair1, RVecF pair2, Int_t ntrk){
                if(ntrk==4){
                                eventnumber++;
                        float rho_inv00 = pair1.at(0);
                        float rho_inv11 = pair1.at(1);
                        float rho_inv01 = pair2.at(0);
                        float rho_inv10 = pair2.at(1);
                        if(abs(rho_inv00-0.0)<1e-8 && abs(rho_inv01-0.0)<1e-8 && abs(rho_inv11-0.0)<1e-8 && abs(rho_inv10-0.0)<1e-8){
                        empty_count++;
                        }else{
                                hist->Fill(rho_inv00*1e3, rho_inv11*1e3);
                                hist->Fill(rho_inv01*1e3, rho_inv10*1e3);
                        }


                }
        };

        df.Foreach(fillhisto, {"inv_mass_pair1", "inv_mass_pair2", "ntrk"});
        std::cout<<"Total number of 4-trks events: "<<eventnumber<<std::endl;
        std::cout<<"Number of charge zero 4-trks events: "<<eventnumber-empty_count<<std::endl;
return hist;
}


TH2F* plot_2D_rhoMass_hist(std::string filepath, std::string outname, int nbin, float min, float max){
	TH2F* hist = new TH2F("Mass pairs", "Correct reconstructed mass pair", nbin, min, max, nbin, min, max);
	TCanvas* c1 = new TCanvas("fig", "Fig", 1200, 1000);
	ROOT::RDataFrame df("tree", filepath.c_str());
	auto fill = [=](RVecF correct_pair){
		hist->Fill(correct_pair.at(0)*1e3, correct_pair.at(1)*1e3);
	};
	
	df.Foreach(fill, {"correct_massPair"});
	TFile* outfile = new TFile(("plots/correct_2D_mass/"+outname+".root").c_str(),"RECREATE");
	hist->GetXaxis()->SetTitle("mass in MeV");
	hist->GetYaxis()->SetTitle("mass in Mev");
	c1->SetLogz();
	hist->Draw("COLZ");
	c1->Write();
	outfile->Close();
	
	return hist;
}


void plot_2D_inv_mass_hist(TH2F* hist, std::string filename){
	TCanvas* c1 = new TCanvas("Figure","Fig", 1200, 1000);
	c1->SetLogz();
	hist->Draw("COLZ");
	c1->SaveAs(("plots/2D_invariant_mass/chi2cut/Invariant_"+filename+".png").c_str());
	TFile* outfile = new TFile(("plots/2D_invariant_mass/chi2cut/Invariant_"+filename+".root").c_str(),"RECREATE");
	c1->Write();
	c1->Clear();
	outfile->Close();
}


TH1D* getProj(TH2F* hist, float projmin, float projmax, std::string filename, std::string option, bool save){
	TCanvas* c1 = new TCanvas("Figure", "Fig", 1200, 1000);
	TH1D* proj;
	if(option=="x"){	
		int minbin = hist->GetYaxis()->FindBin(projmin);	
		int maxbin = hist->GetYaxis()->FindBin(projmax);
		proj = hist->ProjectionX(("xprojection" + filename).c_str(), minbin, maxbin);
		proj->SetMarkerStyle(4);
       		proj->SetMarkerColor(kBlue+3);
		proj->SetLineColor(kBlue+3);	
		proj->Sumw2();
	}else if(option=="y"){	
		int minbin = hist->GetXaxis()->FindBin(projmin);
		int maxbin = hist->GetXaxis()->FindBin(projmax);	
		proj = hist->ProjectionY(("yprojection" + filename).c_str(), minbin, maxbin);
		proj->SetMarkerStyle(26);
       		proj->SetMarkerColor(kRed+2);
		proj->SetLineColor(kRed+2);	
		proj->Sumw2();
	}else{
		std::cerr<<"Invalid option! Chose \"x\" or \"y\"."<<std::endl;
	}

	proj->Draw();

	if(save==true){
	std::string name = "plots/rho_inv_mass/" + option + "projection_" + filename + ".root";
	TFile* outfile = new TFile(name.c_str(), "RECREATE");
	c1->Write();
	outfile->Close();
	delete c1;
	delete outfile;
	}

	return proj;
}


TF1* gaussfit_mass(TH2F* hist, std::string filename, std::vector<float> initial_guess, std::string option){
	
	float amp = initial_guess[0];
	float mean = initial_guess[1];
	float sigma = initial_guess[2];
	float offset = initial_guess[3];

	TF1* gausfit_off = new TF1("gausfit_off", "[0]*exp(-0.5*((x-[1])/[2])**2) + [3]", mean - 1*sigma, mean + 1*sigma);
	TF1* gausfit = new TF1("gausfit", "gaus", mean - 1*sigma, mean + 1*sigma);	
	TCanvas* c2 = new TCanvas("Fig1", "Fig1", 1200, 1000);
	for (int i=0; i<100; i++){

		std::string projname = option + "projection_it" + std::to_string(i);
		TH1D* proj = getProj(hist, mean - 2*sigma, mean + 2*sigma, filename, option);
		gausfit_off->SetParameters(amp, mean, sigma, offset);
		gausfit_off->SetRange(mean - 1.0*sigma, mean + 1.0*sigma);
		proj->Fit(gausfit_off,"R", "",  mean - 2.0* sigma, mean + 2.0*sigma);
		
		if(abs(amp - gausfit_off->GetParameter(0))<0.0001 && abs(mean - gausfit_off->GetParameter(1))<0.0001 && abs(sigma - gausfit_off->GetParameter(2))<0.0001){
			proj->Draw();
			gausfit_off->SetLineColor(proj->GetLineColor()-2);
			gausfit_off->Draw("same");
			TPad *pad_proj = new TPad(("pad_proj"+option).c_str(), "Zoom inset", 0.35, 0.55, 0.68, 0.88);
			pad_proj->SetFillStyle(0);  // transparent
			pad_proj->SetLineColor(kGray + 1);
			pad_proj->Draw();
			pad_proj->cd();

			TH1D* zoom_proj = (TH1D*)proj->Clone(("zoom_proj"+option).c_str());
			zoom_proj->GetXaxis()->SetRangeUser(450, 550);
		//	zoom_proj->Draw("same");
		//	gausfit_off->Draw("same");

		std::cout<<"\n"<<std::endl;
			std::cout <<filename<< option + " proj Amplitude: " << gausfit_off->GetParameter(0) << " ± " << gausfit_off->GetParError(0) << std::endl;
			std::cout <<filename<< option +  " proj Mean:      " << gausfit_off->GetParameter(1) << " ± " << gausfit_off->GetParError(1) << std::endl;
			std::cout <<filename<< option + " proj Sigma:     " << gausfit_off->GetParameter(2) << " ± " << gausfit_off->GetParError(2) << std::endl;
			std::cout <<filename<< option + " proj FWHM:     " << 2.35482*gausfit_off->GetParameter(2) << " ± " << 2.35482*gausfit_off->GetParError(2) << std::endl;
			std::cout<<"\n"<<std::endl;

			TFile* outFile = new TFile(("plots/rho_mass_fits/inv_mass_rho_proj" + option + filename + ".root").c_str(), "RECREATE");
			c2->Write();  // writes the canvas into the file
			outFile->Close();
			
			break;
		}	
		amp = gausfit_off->GetParameter(0);
		mean = gausfit_off->GetParameter(1);
		sigma = gausfit_off->GetParameter(2);
		offset = gausfit_off->GetParameter(3);
		
	}
return gausfit_off;
}



void overlay_fits(TH2F* hist, TF1* gausfitx, TF1* gausfity, std::string filename, bool saveplot){
	TCanvas* c2 = new TCanvas("Canvas", "Figure", 1200, 1000);

	// For kaon mass fit (just gaussian)
	//float sigmax = gausfitx->GetParameter(2);
	//float sigmay = gausfity->GetParameter(2);
	//float meanx = gausfitx->GetParameter(1);
	//float meany = gausfity->GetParameter(1);
	//float sigmaxerr = gausfitx->GetParError(2);
	//float sigmayerr = gausfity->GetParError(2);
	//float meanxerr = gausfitx->GetParError(1);
	//float meanyerr = gausfity->GetParError(1);
	

	//For rho mas fit with background	
	float sigmax = gausfitx->GetParameter(6);
	float sigmay = gausfity->GetParameter(6);
	float meanx = gausfitx->GetParameter(5);
	float meany = gausfity->GetParameter(5);
	float sigmaxerr = gausfitx->GetParError(6);
	float sigmayerr = gausfity->GetParError(6);
	float meanxerr = gausfitx->GetParError(5);
	float meanyerr = gausfity->GetParError(5);

	//For Kaon fit use this
	//TH1D* projx = getProj(hist, meanx - 3*sigmax, meanx + 3*sigmax, filename.c_str(), "x", saveplot);
	//TH1D* projy = getProj(hist, meany - 3*sigmay, meany + 3*sigmay, filename.c_str(), "y", saveplot);
	
	//For rho mass fits use this
	TH1D* projx = getProj(hist, 600, 900, filename.c_str(), "x", saveplot);
	TH1D* projy = getProj(hist, 600, 900, filename.c_str(), "y", saveplot);
	
	c2->cd();
	projx->SetLineColor(kBlue+3);
	projx->SetTitle("Reconstructed invariant mass");
	projx->SetName(("Projections " + filename).c_str());
	projx->GetXaxis()->SetTitle("Energy [MeV]");
	projy->SetLineColor(kRed+2);	
	projy->Draw();
	projx->Draw("same");

	gausfitx->SetLineColor(kBlue);
	gausfity->SetLineColor(kRed);
	gausfitx->Draw("same");
	gausfity->Draw("same");

	TLegend* legend = new TLegend(0.35, 0.7, 0.45, 0.89);
	legend->SetBorderSize(0);
	legend->SetFillStyle(0);
	legend->AddEntry(projx, "x-projection", "l");
	legend->AddEntry(projy, "y-projection", "l");
	legend->AddEntry(gausfitx, "Gaussian fit x", "l");
	legend->AddEntry(gausfity, "Gaussian fit y", "l");
	legend->Draw();
	
	TPaveText* box = new TPaveText(0.55, 0.7, 0.70, 0.90, "NDC");
	box->SetFillColor(0);
	box->SetBorderSize(1);
	box->SetTextFont(42);     
	box->SetTextSize(0.05);
	box->SetTextAlign(12);
	box->AddText(Form("#mu_{x} =( %.3f #pm %.3f) MeV", meanx, meanxerr));
	box->AddText(Form("#sigma_{x} =( %.3f #pm %.3f) MeV", sigmax, sigmaxerr));
	box->AddText(Form("#mu_{y} =( %.3f #pm %.3f) MeV", meany, meanyerr));
	box->AddText(Form("#sigma_{y} =( %.3f #pm %.3f) MeV", sigmay, sigmayerr));
	box->Draw("same");
	
	TPad *pad_proj = new TPad("Zoom", "Zoom inset", 0.25, 0.08, 0.55, 0.38);
	pad_proj->SetFillStyle(0);  // transparent
	pad_proj->SetLineColor(kGray + 1);
	pad_proj->Draw();
	pad_proj->cd();


	TH1D* zoom_projy = (TH1D*)projy->Clone("zoom_projy");
	zoom_projy->GetXaxis()->SetRangeUser(570, 970);
	//zoom_projy->Draw("same");
	//gausfity->Draw("same");

	TH1D* zoom_projx = (TH1D*)projx->Clone("zoom");
	zoom_projx->GetXaxis()->SetRangeUser(570, 970);
	//zoom_projx->Draw("same");
	//gausfitx->Draw("same");
	c2->Update();

	auto outpath = "plots/rho_mass_fits/overlay" + filename + ".root";
	TFile* outfile = new TFile(outpath.c_str(), "RECREATE");
	c2->Write();
	outfile->Close();
	
}


TF1* rhoMassFit(TH2F* hist, std::string filename, std::vector<float> initial_guess, std::string option){
	// Function from Anna's summer student report
	//TF1* bg = new TF1("expo-poly","[0]*(x-[1])**[2]*exp([3]*x + [4]*x**2 + [5]*x**3)", 200, 1000);
	//TF1* sg = new TF1("gauss", "gaus", 600, 900);
	
	
	float bgAmp = initial_guess[0];
	float bgShift = initial_guess[1];
	float bgExp = initial_guess[2];
	float bgA = initial_guess[3];
	float bgB = initial_guess[4];
	float bgC = initial_guess[5];
	float sgAmp = initial_guess[6];
	float sgMean = initial_guess[7];
	float sgSigma = initial_guess[8];

	//TF1* total = new TF1("total", "[0]*(x-[1])**[2]*exp([3]*x + [4]*x**2 + [5]*x**3) + [6]*exp(-0.5*((x-[7])/[8])**2)", 400, 1000);
	//total->SetParNames("BG_amp", "BG_shift", "BG_exp","BG_a", "BG_b", "BG_c", "SG_amp", "SG_mean", "SG_sigma");
	TF1* total = new TF1("total", "[0]*(x-[1])**[2]*exp([3]*x) + [4]*exp(-0.5*((x-[5])/[6])**2)", 300, 1200);
	total->SetParNames("BG_amp", "BG_shift", "BG_exp","BG_a", "SG_amp", "SG_mean", "SG_sigma");
	TH1D* proj = getProj(hist, 600, 900, "TOT2", option);

	for(int i=0; i<100; i++){
		total->SetParameters(bgAmp, bgShift, bgExp, bgA, sgAmp, sgMean, sgSigma);
		proj->Fit("total");

		bgAmp = total->GetParameter(0);
		bgShift = total->GetParameter(1);
		bgExp = total->GetParameter(2);
		bgA = total->GetParameter(3);
		sgAmp = total->GetParameter(4);
		sgMean = total->GetParameter(5);
		sgSigma = total->GetParameter(6);
	}

	TCanvas* c1 = new TCanvas("Fig", "fig", 1000, 1200);
	c1->cd();
	proj->Draw();
	if(option=="x"){
		total->SetLineColor(kBlue);
	}else if (option=="y"){
		total->SetLineColor(kRed);
	}
	total->Draw("same");

	auto pave = new TPaveText(0.11, 0.65, 0.32, 0.89, "NDC");
	pave->SetFillColor(kWhite);
	pave->SetBorderSize(1);
	pave->SetTextAlign(12);
	pave->AddText("Fit Parameters:");

	for (int i = 0; i < total->GetNpar(); ++i) {
	    TString parName = total->GetParName(i);
	    double parVal = total->GetParameter(i);
	    double parErr = total->GetParError(i);
	    TString line;
	    line.Form("%s = %.3f #pm %.3f", parName.Data(), parVal, parErr);
	    pave->AddText(line);
	}

	pave->Draw();



	TFile* outfile = new TFile(("/plots/rho_mass_fits/"+filename+option+"proj"+"_BGfit.root").c_str(), "RECREATE");
	c1->Write();
	outfile->Close();

	return total;
}


