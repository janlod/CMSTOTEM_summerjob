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

	   c1->SaveAs(("../plots/invariant_mass_pion/inv_mass"+filebasename+"cutted.png").c_str());
}
