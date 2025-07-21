#include "data_manipulation/inv_mass.h"

float massPi = 0.13957;
auto calcInvMassPairs = [massPi](RVecF pt, RVecF eta, RVecF phi, RVecI q, Int_t ntrk){
	TLorentzVector pos0, pos1, neg0, neg1;
	
	std::vector<Int_t> trk_pos {};
	std::vector<Int_t> trk_neg {};
	if(ntrk==4){
		for(int itrk=0; itrk<ntrk; itrk++){
			if(q.at(itrk) == -1){
				trk_neg.push_back(itrk);
			}else if(q.at(itrk) == 1){
				trk_pos.push_back(itrk);
			}else if(q.at(itrk) == 0){
				std::cout<<"Neutral particle"<<std::endl;
			}else{
				std::cout<<"Irregular charge"<<std::endl;
			}
		}
		int pos_charge = trk_pos.size();
		int neg_charge = trk_neg.size();
	//	std::cout<<pos_charge-neg_charge<<std::endl;
		if(pos_charge - neg_charge == 0){

			int p0 = trk_pos.at(0);
			int p1 = trk_pos.at(1);
			int n0 = trk_neg.at(0);
			int n1 = trk_neg.at(1);
			
			//combination 1: p0n0 and p1n1, call it "par"
			pos0.SetPtEtaPhiM(pt.at(p0), eta.at(p0), phi.at(p0), massPi);
			pos1.SetPtEtaPhiM(pt.at(p1), eta.at(p1), phi.at(p1), massPi);

			// combination 2: p0n1 and p1n0, call it "cross"
			neg0.SetPtEtaPhiM(pt.at(n0), eta.at(n0), phi.at(n0), massPi);
			neg1.SetPtEtaPhiM(pt.at(n1), eta.at(n1), phi.at(n1), massPi);

		
		
		TLorentzVector pair00 = pos0 + neg0;
		TLorentzVector pair11 = pos1 + neg1;
		TLorentzVector pair01 = pos0 + neg1;
		TLorentzVector pair10 = pos1 + neg0;
		
		// LEave it in GeV here so it is in GeV in the tree
		float rho_inv00 = pair00.M();
		float rho_inv11 = pair11.M();
		float rho_inv01 = pair01.M();
		float rho_inv10 = pair10.M();

	RVecF rho_inv_mass_pair1 = { rho_inv00, rho_inv11 };
	RVecF rho_inv_mass_pair2 = { rho_inv01, rho_inv10 };


	return std::make_pair(rho_inv_mass_pair1, rho_inv_mass_pair2);
		}
	}
	return std::make_pair(RVecF{0,0}, RVecF{0,0});
};


void add_inv_massBranches(std::string treename, std::string filepath, std::string filename, float massPi){
	auto tree = treename.c_str();
	auto file = filepath.c_str();

	ROOT::RDataFrame df(tree, file);

	auto df2 = df
	 	.Define("inv_mass_pair1", [=](RVecF pt, RVecF eta, RVecF phi, RVecI q, int ntrk) {				
		return calcInvMassPairs(pt, eta, phi, q, ntrk).first; }, {"trk_pt", "trk_eta", "trk_phi", "trk_q", "ntrk"})
		.Define("inv_mass_pair2", [=](RVecF pt, RVecF eta, RVecF phi, RVecI q, int ntrk) {
		return calcInvMassPairs(pt, eta, phi, q, ntrk).second; }, {"trk_pt", "trk_eta", "trk_phi", "trk_q", "ntrk"});

	df2.Snapshot("tree", ("../../data/inv_mass_data/" + filename + ".root").c_str());
	
}

