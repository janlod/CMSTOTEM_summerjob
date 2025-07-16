void combineTrees(std::vector<std::string> fileList, std::string config){
	ROOT::RDataFrame df("tree", fileList);
	std::cout<<config<<std::endl;
	df.Snapshot("tree", ("../data/combined/combinedData_TOTEM" + config + "x.root").c_str());

}
