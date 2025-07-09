using RVecF = ROOT::VecOps::RVec<float>;


bool all4Good(RVecF trks, float cutvalue){
	int goodtrks = 0;
	for(Float_t value : trks){
		if(abs(value) < cutvalue){
			goodtrks++;
		}
	}

	return goodtrks==4;
}


void simpleCut(std::string treename, std::string fileloc, std::string filename){
	auto tree = treename.c_str();
	auto file = fileloc.c_str();

	ROOT::RDataFrame df(tree, file);

	int ntrk = 4;	
	float pt_min = 0.0;
	float eta_max = 1.5;
	float zPV_max = 13.0;
	float dxy_max = 0.09;
	float dz_max = 0.65;
	float dxydxyerr_max = 2.5;
	float dzdzerr_max = 1.2;


	auto trk4_cut = df.Filter([ntrk](int x) { return x==ntrk; }, {"ntrk"});
	
	auto zPV_cut = trk4_cut.Filter([zPV_max](float x) { return abs(x)<zPV_max; }, {"zPV"});

	auto lowpt_cut = zPV_cut.Filter([pt_min](float x) { return abs(x) >= pt_min; }, {"alltrk_pt"});
	
	auto eta_cut = lowpt_cut.Filter([eta_max](RVecF x){ return all4Good(x, eta_max); }, {"trk_eta"});

	auto dxy_cut = eta_cut.Filter([dxy_max](RVecF x){ return all4Good(x, dxy_max); }, {"trk_dxy"});
	
	auto dz_cut = dxy_cut.Filter([dz_max](RVecF x){ return all4Good(x, dz_max); }, {"trk_dz"});

	auto dxydxyerr_cut = dz_cut.Filter([dxydxyerr_max](RVecF x, RVecF xerr){ 
		     		RVecF dxdxerr {};
		       		for(int i=0; i<x.size(); i++){
					dxdxerr.push_back(x.at(i)/xerr.at(i));						      	
				}
			return all4Good(dxdxerr, dxydxyerr_max); }, {"trk_dxy", "trk_dxyerr"});
	
	auto dzdzerr_cut = dxydxyerr_cut.Filter([dzdzerr_max](RVecF x, RVecF xerr){ 
		     		RVecF dxdxerr {};
		       		for(int i=0; i<x.size(); i++){
					dxdxerr.push_back(x.at(i)/xerr.at(i));						      	
				}
			return all4Good(dxdxerr, dzdzerr_max); }, {"trk_dz", "trk_dzerr"});

	dzdzerr_cut.Snapshot("tree", ("simple_cutted_data/"+filename+"simplecut.root").c_str());

}
