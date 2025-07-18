void combineTrees(std::vector<std::string> fileList, std::string config){
	ROOT::RDataFrame df("tree", fileList);
	std::cout<<config<<std::endl;
	df.Snapshot("tree", ("../data/combined/" + config + ".root").c_str());

}
