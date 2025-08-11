#include "invMass_analysis/plot_inv_mass.h"

void plot_invar_mass(TTree* tree, std::string filebasename, float massparam){
	   Float_t trk_pt[1000], trk_phi[1000], trk_eta[1000];
	   Int_t ntrk;

	   tree->SetBranchAddress("trk_pt", trk_pt);
	   tree->SetBranchAddress("trk_phi", trk_phi);
	   tree->SetBranchAddress("trk_eta", trk_eta);
	   tree->SetBranchAddress("ntrk", &ntrk);


	   TCanvas* c1 = new TCanvas("fig", "fig", 1000, 800);
	   TH1F* hist = new TH1F(("Invariant mass from " + filebasename+"cutted" ).c_str(), "Reconstructed invariant mass in MeV", 400, 500, 4000);

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
			
	   		hist->Fill(total_mass*1000);
		}
	   }
	   hist->Draw("E");
	   TLine *line = new TLine(2220, 0, 2220, hist->GetMaximum());
	   line->SetLineColor(kRed);
	   line->SetLineWidth(2);  
	   line->Draw("same");

	   c1->SaveAs(("../../plots/invariant_mass_pion/inv_mass"+filebasename+"cutted.png").c_str());
}


void plot_different_cuts(std::string filepath, std::string cut_option, std::vector<float> initial_kin_cuts, std::vector<float> initial_chi2cuts, float initial_rho_cut, std::vector<float> cuts, int nbins, float min, float max, std::string outpath){
	auto fp = filepath.c_str();
	auto op = outpath.c_str();
	simpleCut(initial_kin_cuts, fp, "init_simpleCuts");
	cutChi2("tree", "data/4trk_invMass/init_simpleCuts.root", "init_simpleCut_chi2Cut", initial_chi2cuts);
	cut_rhoMassChi2("data/4trk_invMass/init_simpleCut_chi2Cut.root", initial_rho_cut, "init_simpleCut_chi2Cut_rhoCut");
	
	auto data_path = "data/4trk_invMass/init_simpleCut_chi2Cut_rhoCut.root";
	auto cutted_outpath = "data/4trk_invMass/cutted_data.root";
	auto trash_path = "data/trash.root";

	TCanvas* c1 = new TCanvas("fig", "fig", 1200, 1000);
	TFile* outfile = new TFile(op, "RECREATE");
	TLegend* leg = new TLegend(0.62, 0.45, 0.8, 0.66);
	leg->SetTextSize(0.05);
	std::vector<int> colors = {kRed, kBlue, kGreen+2, kMagenta, kTeal-1, kOrange-3};
	if(cut_option == "pt"){
		for(int i=0; i<cuts.size(); i++){
			float pt_max = cuts.at(i);
			std::vector<float> cutval = {0.0, pt_max, 1e2, 1e2, 1e2, 1e2, 1e2, 1e2};
			simpleCut(cutval, data_path, "cutted_data");
			TH1F* temp_hist = get_4trk_invMass(cutted_outpath, trash_path, nbins, min, max);
			temp_hist->SetLineColor(colors.at(i));
			std::ostringstream oss;
			oss << std::fixed << std::setprecision(1) << pt_max;
			leg->AddEntry(temp_hist, ("pt_max " + oss.str()).c_str());
			c1->cd();
			temp_hist->SetLineWidth(2);
			if(i==0){temp_hist->Draw("HIST");}
			else {temp_hist->Draw("HIST SAME");}
		}
		leg->Draw("same");
		outfile->cd();
		c1->Write();
		outfile->Close();
		return;
	} else if(cut_option =="eta"){
		for(int i=0; i<cuts.size(); i++){
			float eta_max = cuts.at(i);
			std::vector<float> cutval = {0.0, 1e2, eta_max, 1e2, 1e2, 1e2, 1e2, 1e2};
			simpleCut(cutval, data_path, "cutted_data");
			TH1F* temp_hist = get_4trk_invMass(cutted_outpath, trash_path, nbins, min, max);
			temp_hist->SetLineColor(colors.at(i));
			std::ostringstream oss;
			oss << std::fixed << std::setprecision(1) << eta_max;
			leg->AddEntry(temp_hist, ("eta_max " + oss.str()).c_str());
			c1->cd();
			temp_hist->SetLineWidth(2);
			if(i==0){temp_hist->Draw("HIST");}
			else {temp_hist->Draw("HIST SAME");}
		}
	leg->Draw("same");
	outfile->cd();
	c1->Write();
	outfile->Close();
	return;
	}else if(cut_option =="dxy"){
		for(int i=0; i<cuts.size(); i++){
			float dxy_max = cuts.at(i);
			std::vector<float> cutval = {0.0, 1e2, 1e2, 1e2, dxy_max, 1e2, 1e2, 1e2};
			simpleCut(cutval, data_path, "cutted_data");
			TH1F* temp_hist = get_4trk_invMass(cutted_outpath, trash_path, nbins, min, max);
			temp_hist->SetLineColor(colors.at(i));
			std::ostringstream oss;
			oss << std::fixed << std::setprecision(1) << dxy_max;
			leg->AddEntry(temp_hist, ("dxy_max " + oss.str()).c_str());
			c1->cd();
			temp_hist->SetLineWidth(2);
			if(i==0){temp_hist->Draw("HIST");}
			else {temp_hist->Draw("HIST SAME");}
		}
	leg->Draw("same");
	outfile->cd();
	c1->Write();
	outfile->Close();
	return;
	} else if (cut_option=="rho"){
		for(int i=0; i<cuts.size(); i++){
			float chirho_max = cuts.at(i);
			std::vector<float> cutval = {0.0, 1e2, 1e2, 1e2, 1e2, 1e2, 1e2, 1e2};
			cut_rhoMassChi2(data_path, chirho_max, "cutted_data");
			TH1F* temp_hist = get_4trk_invMass(cutted_outpath, trash_path, nbins, min, max);
			temp_hist->SetLineColor(colors.at(i));
			std::ostringstream oss;
			oss << std::fixed << std::setprecision(1) << chirho_max;
			leg->AddEntry(temp_hist, ("chi2_rho_max " + oss.str()).c_str());
			c1->cd();
			temp_hist->SetLineWidth(2);
			if(i==0){temp_hist->Draw("HIST");}
			else {temp_hist->Draw("HIST SAME");}
		}
	leg->Draw("same");
	outfile->cd();
	c1->Write();
	outfile->Close();
	return;
	}else if (cut_option=="chi2"){
		for(int i=0; i<cuts.size(); i++){
			float chi2_max = cuts.at(i);
			std::vector<float> chi2cuts = {chi2_max, chi2_max, chi2_max};
			cutChi2("tree", data_path, "cutted_data", chi2cuts);
			TH1F* temp_hist = get_4trk_invMass(cutted_outpath, trash_path, nbins, min, max);
			temp_hist->SetLineColor(colors.at(i));
			std::ostringstream oss;
			oss << std::fixed << std::setprecision(1) << chi2_max;
			leg->AddEntry(temp_hist, ("chi2_max " + oss.str()).c_str());
			c1->cd();
			temp_hist->SetLineWidth(2);
			if(i==0){temp_hist->Draw("HIST");}
			else {temp_hist->Draw("HIST SAME");}
		}
	leg->Draw("same");
	outfile->cd();
	c1->Write();
	outfile->Close();
	return;
	}

}
