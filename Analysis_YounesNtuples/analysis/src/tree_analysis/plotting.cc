#include "tree_analysis/plotting.h"

void plot2D_correl_eventvar(std::string filepath, std::string outpath, std::string xbranch, std::string ybranch, int xnbins, int ynbins, float xmin, float ymin, float xmax, float ymax, bool logscale){
	TH2F* hist = new TH2F("2d correl", (xbranch + " vs. " + ybranch).c_str(), xnbins, xmin, xmax, ynbins, ymin, ymax);
	TCanvas* c1 = new TCanvas("fig", "fig", 1200, 1000);
	if(logscale){c1->SetLogz(); }
	hist->GetXaxis()->SetTitle(xbranch.c_str());
	hist->GetYaxis()->SetTitle(ybranch.c_str());

	ROOT::RDataFrame df("tree", filepath);
	auto fill2D = [=](float value1, float value2){ hist->Fill(value1, value2); };
	
	df.Foreach(fill2D, {xbranch.c_str(), ybranch.c_str()});
	TFile* outfile = new TFile(outpath.c_str(), "RECREATE");
	hist->Draw("COLZ");
	c1->Write();
	outfile->Close();
}


void plot2D_masspairs(bool correct, std::string filepath, std::string outpath, int nbins, float min, float max, bool logscale){
	TH2F* hist = new TH2F("2d correl", "Reconstructed invariant mass", nbins, min, max, nbins, min, max);
	TCanvas* c1 = new TCanvas("fig", "fig", 1200, 1000);
	if(logscale){c1->SetLogz(); }
	hist->GetXaxis()->SetTitle("mass [MeV]");
	hist->GetYaxis()->SetTitle("mass [MeV]");

	ROOT::RDataFrame df("tree", filepath);
	auto fill2D = [=](RVecF pair){ hist->Fill(pair.at(0)*1e3, pair.at(1)*1e3); };
	
	if(correct){
		df.Foreach(fill2D, {"correct_massPair"});
	}else{
		df.Foreach(fill2D, {"wrong_massPair"});
	}
	TFile* outfile = new TFile(outpath.c_str(), "RECREATE");
	hist->Draw("COLZ");
	c1->Write();
	outfile->Close();
}



void plot1D_eventvar(std::string filepath, std::string outpath, std::string branch, int nbins, float min, float max, bool logscale){
	auto fp = filepath.c_str();
	auto op = outpath.c_str();
	auto bname = branch.c_str();
	TH1F* hist = new TH1F("1d histo", bname, nbins, min, max);
	TCanvas* c1 = new TCanvas("Fig", "Fig", 1200, 1000);
	if(logscale){ c1->SetLogy(); }
	hist->GetXaxis()->SetTitle(bname);
	hist->GetYaxis()->SetTitle("events");
	
	ROOT::RDataFrame df("tree", fp);
	auto fill1D = [=](float value){ hist->Fill(value); };

	df.Foreach(fill1D, {bname});
	TFile* outfile = new TFile(op, "RECREATE");
	hist->Draw();
	c1->Write();
	outfile->Close();
}

void plot2D_correl_trkp_prp(std::string filepath, std::string outpath, std::string direction, int xnbins, int ynbins, float xmin, float ymin, float xmax, float ymax, bool logscale){
	TH2F* hist = new TH2F(("2d correl "+direction+"-direction").c_str(), "Proton momentum  vs. trk momentum ", xnbins, xmin, xmax, ynbins, ymin, ymax);
	TCanvas* c1 = new TCanvas("fig", "fig", 1200, 1000);
	if(logscale){c1->SetLogz(); }
	hist->GetYaxis()->SetTitle(("#sum_{trks}p_{"+direction+"}").c_str());
	hist->GetXaxis()->SetTitle(("#sum pr_p"+direction).c_str());

	ROOT::RDataFrame df("tree", filepath);
	auto fill2D = [=](RVecF trk_pt, RVecF trk_phi, RVecF trk_eta, Double_t pr_pa, Double_t pr_pb, Int_t ntrk){
		if(ntrk==4){ 
			Double_t pr_p = pr_pa + pr_pb;
			Float_t trk_p = 0.0;
			if(direction=="x"){
				for(int itrk=0; itrk<ntrk; itrk++){
					trk_p += trk_pt.at(itrk)*cos(trk_phi.at(itrk));
				} 
			}else if(direction=="y"){
				for(int itrk=0; itrk<ntrk; itrk++){
					trk_p += trk_pt.at(itrk)*sin(trk_phi.at(itrk));
				} 
			}else if(direction=="z"){
				for(int itrk=0; itrk<ntrk; itrk++){
					trk_p += trk_pt.at(itrk)*sinh(trk_eta.at(itrk));
				}
			}else{
				std::cerr<<"Invalid direction parameter. Use x,y or z"<<std::endl;
			}

			hist->Fill(pr_p, trk_p); };
	 	};
	auto pr_a = ("pr_p"+direction+"_a").c_str(); 
	auto pr_b = ("pr_p"+direction+"_b").c_str(); 
	df.Foreach(fill2D, {"trk_pt", "trk_phi", "trk_eta", pr_a, pr_b, "ntrk"});
	TFile* outfile = new TFile(outpath.c_str(), "RECREATE");
	hist->Draw("COLZ");
	c1->Write();
	outfile->Close();
}

void plot2D_correl_trkvars(std::string filepath, std::string outpath, std::string xbranch, std::string ybranch, int xnbins, int ynbins, float xmin, float ymin, float xmax, float ymax, bool logscale){
	TH2F* hist = new TH2F("Energy loss", "dE/dx  vs. trk momentum ", xnbins, xmin, xmax, ynbins, ymin, ymax);
	TCanvas* c1 = new TCanvas("fig", "fig", 1200, 1000);
	if(logscale){c1->SetLogz(); }
	hist->GetXaxis()->SetTitle("trk momentum [Mev]");
	hist->GetYaxis()->SetTitle("dE/dx");

	ROOT::RDataFrame df("tree", filepath);
	auto fill2D = [=](RVecF x, RVecF y, Int_t ntrk){
		for(int itrk=0; itrk<ntrk; itrk++){ 
			hist->Fill(x.at(itrk), y.at(itrk));
		 };
	 	};
	df.Foreach(fill2D, {xbranch.c_str(), ybranch.c_str(), "ntrk"});
	TFile* outfile = new TFile(outpath.c_str(), "RECREATE");
	hist->Draw("COLZ");
	c1->Write();
	outfile->Close();
}



void plot1D_trkvar(std::string filepath, std::string outpath, std::string branch, int nbins, float min, float max, bool logscale){
	auto fp = filepath.c_str();
	auto op = outpath.c_str();
	auto bname = branch.c_str();
	TH1F* hist = new TH1F("1d histo", bname, nbins, min, max);
	TCanvas* c1 = new TCanvas("Fig", "Fig", 1200, 1000);
	if(logscale){ c1->SetLogy(); }
	hist->GetXaxis()->SetTitle(bname);
	hist->GetYaxis()->SetTitle("events");
	
	ROOT::RDataFrame df("tree", fp);
	auto fill1D = [=](RVecF values, Int_t ntrk){
			for(int itrk=0; itrk<ntrk; itrk++){
				hist->Fill(values.at(itrk)); };
			}; 

	df.Foreach(fill1D, {bname, "ntrk"});
	TFile* outfile = new TFile(op, "RECREATE");
	hist->Draw();
	c1->Write();
	outfile->Close();
}

void plot_momentum_difference(std::string filepath, std::string outpath, int nbins, float min, float max){
	TH1F* histx = new TH1F("momentum x", "Total momentum", nbins, min, max);
	TH1F* histy = new TH1F("momentum ", "Proton momentum", nbins, min, max);
	TCanvas* c1 = new TCanvas("Fig", "fig", 1200, 1000);
	TLegend* leg = new TLegend(0.2, 0.7, 0.35, 0.85);
	leg->AddEntry(histx, "px", "l");
	leg->AddEntry(histy, "py", "l");
	leg->SetTextSize(0.05);
	
	ROOT::RDataFrame df("tree", filepath.c_str());
	auto fill = [=](double pr_px_a, double pr_px_b, double pr_py_a, double pr_py_b){
	
	float proton_px = static_cast<float>(pr_px_a + pr_px_b);
	float proton_py = static_cast<float>(pr_py_a + pr_py_b);
	histx->Fill(proton_px*1e3);
	histy->Fill(proton_py*1e3);
	};
	df.Foreach(fill, { "pr_px_a", "pr_px_b", "pr_py_a", "pr_py_b"});
	TFile* outfile = new TFile(outpath.c_str(), "RECREATE");
	
	histx->SetLineWidth(2.0);
	histy->SetLineWidth(2.0);
	c1->cd();
	histy->Draw();
	histy->GetXaxis()->SetTitle("Proton momentum in MeV");
	histx->Draw("same");
	leg->Draw("same");
	histy->SetLineColor(kRed);
	c1->Write();
	outfile->Close();
}

void prot_momentum_scatterplot(std::string filepath, std::string outpath, std::string option, int nbins, float min, float max, bool logscale){
	TCanvas* c1 = new TCanvas("Fig", "fig", 1200, 1200);
	if(logscale){ c1->SetLogz();  }
	TH2F* hist = new TH2F("2d scatter", "Proton momentum a vs. Proton momentum b", nbins, min, max, nbins, min, max);
	ROOT::RDataFrame df("tree", filepath.c_str());
	auto optionpar = option;	
	auto fill = [=](double pr_px_a, double pr_px_b, double pr_py_a, double pr_py_b){
	
	if(optionpar=="x"){
		hist->Fill(static_cast<float>(pr_px_a)*1e3, static_cast<float>(pr_px_b)*1e3);
	}else if(optionpar=="y"){
		hist->Fill(static_cast<float>(pr_py_a)*1e3, static_cast<float>(pr_py_b)*1e3);
	}
	};
	df.Foreach(fill, { "pr_px_a", "pr_px_b", "pr_py_a", "pr_py_b"});
	TFile* outfile = new TFile(outpath.c_str(),"RECREATE");
	if(option=="x"){
		hist->GetXaxis()->SetTitle("Proton px_a [MeV]");
		hist->GetYaxis()->SetTitle("Proton px_b [MeV]");
	}else if(option=="y"){
		hist->GetXaxis()->SetTitle("Proton py_a [MeV]");
		hist->GetYaxis()->SetTitle("Proton py_b [MeV]");
	}
	c1->cd();
	hist->Draw("COLZ");
	c1->Write();
	outfile->Close();
	
}

void prot_pt_scatterplot(std::string filepath, std::string outpath, int nbins, float min, float max, bool logscale){
	TCanvas* c1 = new TCanvas("Fig", "fig", 1200, 1200);
	if(logscale){ c1->SetLogz();  }
	TH2F* hist = new TH2F("2d scatter", "Proton pt a vs. Proton pt b", nbins, min, max, nbins, min, max);
	TH1F* hist2 = new TH1F("2d scatter", "Proton pt a vs. Proton pt b", 500, -1000, 1000);
	TH1F* hist1d = new TH1F("pt_a - pt_b", "pt_a - pt_b", 500, -1000, 1000);
	ROOT::RDataFrame df("tree", filepath.c_str());
	ROOT::RDataFrame dfveto("tree", "data/chi2_combined/TOTEM2cw_40veto.root");
	auto fill = [=](double pr_px_a, double pr_px_b, double pr_py_a, double pr_py_b){
		double pt_a = sqrt(pr_px_a*pr_px_a + pr_py_a*pr_py_a);
		double pt_b = sqrt(pr_px_b*pr_px_b + pr_py_b*pr_py_b);
		hist->Fill(static_cast<float>(pt_a)*1e3, static_cast<float>(pt_b)*1e3);
		hist1d->Fill(static_cast<float>(pt_a)*1e3 - static_cast<float>(pt_b)*1e3);

	};

	auto fill2 = [=](double pr_px_a, double pr_px_b, double pr_py_a, double pr_py_b){
		double pt_a = sqrt(pr_px_a*pr_px_a + pr_py_a*pr_py_a);
		double pt_b = sqrt(pr_px_b*pr_px_b + pr_py_b*pr_py_b);
		hist2->Fill(static_cast<float>(pt_a)*1e3 - static_cast<float>(pt_b)*1e3);
	};


	df.Foreach(fill, { "pr_px_a", "pr_px_b", "pr_py_a", "pr_py_b"});
	dfveto.Foreach(fill2, { "pr_px_a", "pr_px_b", "pr_py_a", "pr_py_b"});
	TFile* outfile = new TFile(outpath.c_str(),"RECREATE");
	
	hist->GetXaxis()->SetTitle("Proton pt_a [MeV]");
	hist->GetYaxis()->SetTitle("Proton pt_b [MeV]");
	c1->cd();
	//hist->Draw("COLZ");
	hist1d->SetLineWidth(2.0);
	hist2->SetLineWidth(2.0);
	hist1d->Draw();
	hist2->SetLineColor(kRed);
	hist2->Draw("same");
	c1->Write();
	outfile->Close();
	
}

void prot_azimuthal_difference(std::string filepath, std::string fpveto, std::string outpath, int nbins, float min, float max){
	TCanvas* c1 = new TCanvas("fig", "fig", 1200, 1200);	
	TH1F* hist = new TH1F("#Delta#Phi_{LR}", "Azimuthal angle difference", nbins, min, max);
	TH1F* hist2 = new TH1F("#Delta#Phi_{LR}", "Azimuthal angle difference", nbins, min, max);

	ROOT::RDataFrame df("tree", filepath.c_str());
	ROOT::RDataFrame dfveto("tree", fpveto.c_str());
	auto fill = [=](double ThxL, double ThyL, double ThxR, double ThyR){
		float phi_L = static_cast<float>(atan(ThxL/ThyL));	
		float phi_R = static_cast<float>(atan(ThxR/ThyR));
		hist->Fill(phi_L - phi_R);
	};
	auto fillveto = [=](double ThxL, double ThyL, double ThxR, double ThyR){
		float phi_L = static_cast<float>(atan(ThxL/ThyL));	
		float phi_R = static_cast<float>(atan(ThxR/ThyR));
		hist2->Fill(phi_L - phi_R);
	};

	df.Foreach(fill, {"pr_px_a", "pr_py_a", "pr_px_b", "pr_py_b"});
	dfveto.Foreach(fillveto,{"pr_px_a", "pr_py_a", "pr_px_b", "pr_py_b"});
	TFile* outfile = new TFile(outpath.c_str(), "RECREATE");
	
	hist->GetXaxis()->SetTitle("#Delta#Phi_{LR} in rad");
	hist->GetYaxis()->SetTitle("events");
	
	c1->cd();
	hist->Draw();
	hist2->SetLineColor(kRed);
	hist2->Draw("same");
	c1->Write();
	outfile->Close();
}
