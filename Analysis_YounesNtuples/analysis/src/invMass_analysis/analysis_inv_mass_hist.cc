#include "invMass_analysis/analysis_inv_mass_hist.h"

void plot_2D_inv_mass_hist(TH2F* hist, std::string filename){
	TCanvas* c1 = new TCanvas("Figure","Fig", 1200, 1000);
	c1->SetLogz();
	hist->Draw("COLZ");
	c1->SaveAs(("../../plots/Invariant_rho_"+filename+".png").c_str());
	TFile* outfile = new TFile(("../../plots/Invariant_rho_"+filename+".root").c_str(),"RECREATE");
	c1->Write();
	c1->Clear();
	outfile->Close();
}


TH1D* getProj(TH2F* hist, float projmin, float projmax, std::string filename, std::string option, bool save=true){
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
	std::string name = "../../plots/kaon_mass_fits/" + option + "projection_" + filename + ".root";
	TFile* outfile = new TFile(name.c_str(), "RECREATE");
	c1->Write();
	outfile->Close();
	delete c1;
	delete outfile;
	}

	return proj;
}


TF1* gaussfit_kaon_mass(TH2F* hist, std::string filename, std::array<float,3> initial_guess, std::string option){
	
	float amp = initial_guess[0];
	float mean = initial_guess[1];
	float sigma = initial_guess[2];

	TF1* gausfit = new TF1("gausfit", "gaus", mean - 1.2*sigma, mean + 1.2*sigma);	
	TCanvas* c2 = new TCanvas("Fig1", "Fig1", 1200, 1000);
	for (int i=0; i<10; i++){
		std::string projname = option + "projection_it" + std::to_string(i);
		TH1D* proj = getProj(hist, mean - 3*sigma, mean + 3*sigma, filename, option);
		gausfit->SetParameters(amp, mean, sigma);
		gausfit->SetRange(mean - 1.0*sigma, mean + 1.0*sigma);
		proj->Fit(gausfit,"R", "",  mean - 1.0* sigma, mean + 1.0*sigma);
		
		if(abs(amp - gausfit->GetParameter(0))<0.0001 && abs(mean - gausfit->GetParameter(1))<0.0001 && abs(sigma - gausfit->GetParameter(2))<0.0001){
			proj->Draw();
			gausfit->SetLineColor(proj->GetLineColor()-2);
			gausfit->Draw("same");
			TPad *pad_proj = new TPad(("pad_proj"+option).c_str(), "Zoom inset", 0.35, 0.55, 0.68, 0.88);
			pad_proj->SetFillStyle(0);  // transparent
			pad_proj->SetLineColor(kGray + 1);
			pad_proj->Draw();
			pad_proj->cd();

			TH1D* zoom_proj = (TH1D*)proj->Clone(("zoom_proj"+option).c_str());
			zoom_proj->GetXaxis()->SetRangeUser(450, 550);
			zoom_proj->Draw("same");
			gausfit->Draw("same");

			TFile* outFile = new TFile(("../../plots/kaon_mass_fits/combined_data/inv_mass_rho_proj" + option + filename + ".root").c_str(), "RECREATE");
			c2->Write();  // writes the canvas into the file
			outFile->Close();
			c2->Clear();
			std::cout<<"\n"<<std::endl;
			std::cout <<filename<< option + " proj Amplitude: " << gausfit->GetParameter(0) << " ± " << gausfit->GetParError(0) << std::endl;
			std::cout <<filename<< option +  " proj Mean:      " << gausfit->GetParameter(1) << " ± " << gausfit->GetParError(1) << std::endl;
			std::cout <<filename<< option + " proj Sigma:     " << gausfit->GetParameter(2) << " ± " << gausfit->GetParError(2) << std::endl;
			std::cout <<filename<< option + " proj FWHM:     " << 2.35482*gausfit->GetParameter(2) << " ± " << 2.35482*gausfit->GetParError(2) << std::endl;
			std::cout<<"\n"<<std::endl;
			
			break;
		}	
		amp = gausfit->GetParameter(0);
		mean = gausfit->GetParameter(1);
		sigma = gausfit->GetParameter(2);
		
	}
return gausfit;
}



void overlay_fits(TH2F* hist, TF1* gausfitx, TF1* gausfity, std::string filename, bool saveplot=false){
	TCanvas* c2 = new TCanvas("Canvas", "Figure", 1200, 1000);
	float sigmax = gausfitx->GetParameter(2);
	float sigmay = gausfity->GetParameter(2);
	float meanx = gausfitx->GetParameter(1);
	float meany = gausfity->GetParameter(1);
	float sigmaxerr = gausfitx->GetParError(2);
	float sigmayerr = gausfity->GetParError(2);
	float meanxerr = gausfitx->GetParError(1);
	float meanyerr = gausfity->GetParError(1);


	TH1D* projx = getProj(hist, meanx - 3*sigmax, meanx + 3*sigmax, filename.c_str(), "x", saveplot);
	TH1D* projy = getProj(hist, meany - 3*sigmay, meany + 3*sigmay, filename.c_str(), "y", saveplot);

	c2->cd();
	projx->SetLineColor(kBlue+3);
	projx->SetTitle("Reconstructed invariant mass");
	projx->SetName(("Projections " + filename).c_str());
	projx->GetXaxis()->SetTitle("Energy [MeV]");
	projy->SetLineColor(kRed+2);	
	projx->Draw();
	projy->Draw("same");

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
	
	TPad *pad_proj = new TPad("Zoom", "Zoom inset", 0.45, 0.38, 0.9, 0.68);
	pad_proj->SetFillStyle(0);  // transparent
	pad_proj->SetLineColor(kGray + 1);
	pad_proj->Draw();
	pad_proj->cd();

	TH1D* zoom_projx = (TH1D*)projx->Clone("zoom");
	zoom_projx->GetXaxis()->SetRangeUser(480, 520);
	zoom_projx->Draw("same");
	gausfitx->Draw("same");

	TH1D* zoom_projy = (TH1D*)projy->Clone("zoom_projy");
	zoom_projy->GetXaxis()->SetRangeUser(480, 520);
	zoom_projy->Draw("same");
	gausfity->Draw("same");

	c2->Update();

	TFile* outfile = new TFile(("../../plots/kaon_mass_fits/combined_data/overlay"+filename+".root").c_str(), "RECREATE");
	c2->Write();
	outfile->Close();
	
}
