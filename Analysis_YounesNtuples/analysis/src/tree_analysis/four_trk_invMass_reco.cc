#include "tree_analysis/four_trk_invMass_reco.h"

TH1F* get_4trk_invMass(std::string filepath, std::string outpath, int nbins, float min, float max, bool draw){
	TH1F* hist = new TH1F("Invariant mass", "Reconstructed invariant mass 4-track system", nbins, min, max);
	hist->GetXaxis()->SetTitle("mass [MeV]");
	hist->GetYaxis()->SetTitle("events");
	ROOT::RDataFrame df("tree", filepath.c_str());
	
	auto fill = [=](RVecF pt, RVecF eta, RVecF phi, Int_t ntrk)
		{ 	TLorentzVector all_trks {};
			if(ntrk==4){
				for(int itrk=0; itrk<ntrk; itrk++){
					TLorentzVector one_trk {};
  					one_trk.SetPtEtaPhiM(pt.at(itrk), eta.at(itrk), phi.at(itrk), 0.13957);
					all_trks += one_trk;
				}
			}	
			hist->Fill(all_trks.M()*1e3);
		};
	df.Foreach(fill, {"trk_pt", "trk_eta", "trk_phi", "ntrk"});
	if(draw){
		TCanvas* c1 = new TCanvas("Fig", "Fig", 1200, 1000);
		TFile* outfile = new TFile(outpath.c_str(), "RECREATE");
		hist->SetMarkerStyle(8);
		hist->SetMarkerColor(kBlue);
		hist->Draw("EP");
		c1->Write();
		outfile->Close();
	}

	return hist;
}
