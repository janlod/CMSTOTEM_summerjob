void loopers_4trks(TTree *tree, std::string filebasename){
	    Float_t trk_p[1000];
	    Int_t ntrk;
	    Int_t trk_q[1000];
		
            const float massPi = 0.13957;

	    tree->SetBranchAddress("trk_p", trk_p);
	    tree->SetBranchAddress("trk_q", trk_q);
	    tree->SetBranchAddress("ntrk", &ntrk);


	    float minbin = 0;
	    float maxbin = 100.0;
	    int nbin = 400;
	    TCanvas *c1 = new TCanvas("Figure","Figure",1000,800);
	    TH1F* hist1 = new TH1F(("Pairing 1 from" + filebasename).c_str(), "|p3+p4|/m", nbin, minbin, maxbin);
	    TH1F* hist2 = new TH1F(("Pairing 2 from" + filebasename).c_str(), "|p3+p4|/m", nbin, minbin, maxbin);
	    TH1F* hist3 = new TH1F(("Pairing 3 from" + filebasename).c_str(), "|p3+p4|/m", nbin, minbin, maxbin);
	    TH1F* hist4 = new TH1F(("Pairing 4 from" + filebasename).c_str(), "|p3+p4|/m", nbin, minbin, maxbin);
	    TH1F* hist5 = new TH1F(("Pairing 5 from" + filebasename).c_str(), "|p3+p4|/m", nbin, minbin, maxbin);
	    TH1F* hist6 = new TH1F(("Pairing 6 from" + filebasename).c_str(), "|p3+p4|/m", nbin, minbin, maxbin);
	    
	    hist1->GetXaxis()->SetTitle("|p3+p4|/m");
	    hist1->SetMaximum(1.3e3);

	    hist2->GetXaxis()->SetTitle("|p3+p4|/m");
	    hist2->SetLineColor(kRed);
	    
	    hist3->GetXaxis()->SetTitle("|p3+p4|/m");
	    hist3->SetLineColor(kGreen);
	    
	    hist4->GetXaxis()->SetTitle("|p3+p4|/m");
	    hist4->SetLineColor(kViolet);
	    
	    hist5->GetXaxis()->SetTitle("|p3+p4|/m");
	    hist5->SetLineColor(kCyan);
	    
	    hist6->GetXaxis()->SetTitle("|p3+p4|/m");
	    hist6->SetLineColor(kOrange);

	    TLegend *legend = new TLegend(0.45, 0.7, 0.55, 0.88);
	    legend->SetBorderSize(0);
	    legend->SetFillStyle(0);

	    legend->AddEntry(hist1, "Pairing 1", "l");
	    legend->AddEntry(hist2, "Pairing 2", "l");
	    legend->AddEntry(hist3, "Pairing 3", "l");
	    legend->AddEntry(hist4, "Pairing 4", "l");
	    legend->AddEntry(hist5, "Pairing 5", "l");
	    legend->AddEntry(hist6, "Pairing 6", "l");



	    /**
	    Multidimensional array holds information on what track is which particle and charge
	    particles[trk number][charge][what kind of particle]
	    can be 1 or 0*/
	    Long64_t nentries = tree->GetEntries();
	    for(int event=0; event<nentries; event++){
		tree->GetEntry(event);
		std::vector<int> posPart_trk;
		std::vector<int> negPart_trk;
		
		if(ntrk == 5){
		    for(int itrk=0; itrk<ntrk; itrk++){
		       if(trk_q[itrk] == -1){
			negPart_trk.push_back(itrk);
		       } else if(trk_q[itrk] == 1){
			posPart_trk.push_back(itrk);
		       }
		    }

		    if(negPart_trk.size() > abs(ntrk/2 + 1) || posPart_trk.size() > abs(ntrk/2 + 1)){
			continue;
		    }
		    if(negPart_trk.size() < posPart_trk.size()){
			Float_t p3 = trk_p[negPart_trk.at(0)];
			Float_t p4 = trk_p[posPart_trk.at(0)];
			hist1->Fill(abs(p3+p4)/massPi);

			p3 = trk_p[negPart_trk.at(0)];
			p4 = trk_p[posPart_trk.at(1)];
			hist2->Fill(abs(p3+p4)/massPi);
			
			p3 = trk_p[negPart_trk.at(0)];
			p4 = trk_p[posPart_trk.at(2)];
			hist3->Fill(abs(p3+p4)/massPi);

			p3 = trk_p[negPart_trk.at(1)];
			p4 = trk_p[posPart_trk.at(0)];
			hist4->Fill(abs(p3+p4)/massPi);

			p3 = trk_p[negPart_trk.at(1)];
			p4 = trk_p[posPart_trk.at(1)];
			hist5->Fill(abs(p3+p4)/massPi);

			p3 = trk_p[negPart_trk.at(1)];
			p4 = trk_p[posPart_trk.at(2)];
			hist6->Fill(abs(p3+p4)/massPi);
		    }else if(negPart_trk.size() > posPart_trk.size()){
			Float_t p3 = trk_p[posPart_trk.at(0)];
			Float_t p4 = trk_p[negPart_trk.at(0)];
			hist1->Fill(abs(p3+p4)/massPi);

			p3 = trk_p[posPart_trk.at(0)];
			p4 = trk_p[negPart_trk.at(1)];
			hist2->Fill(abs(p3+p4)/massPi);
			
			p3 = trk_p[posPart_trk.at(0)];
			p4 = trk_p[negPart_trk.at(2)];
			hist3->Fill(abs(p3+p4)/massPi);

			p3 = trk_p[posPart_trk.at(1)];
			p4 = trk_p[negPart_trk.at(0)];
			hist4->Fill(abs(p3+p4)/massPi);

			p3 = trk_p[posPart_trk.at(1)];
			p4 = trk_p[negPart_trk.at(1)];
			hist5->Fill(abs(p3+p4)/massPi);

			p3 = trk_p[posPart_trk.at(1)];
			p4 = trk_p[negPart_trk.at(2)];
			hist6->Fill(abs(p3+p4)/massPi);
		    }else{
		    std::cout<<"Logic incomplete"<<std::endl;
		    }
		    
		} 
	    }
	    hist1->Draw();
	    hist2->Draw("same");
	    hist3->Draw("same");
	    hist4->Draw("same");
	    hist5->Draw("same");
	    hist6->Draw("same");
	    
	    legend->Draw();

	    c1->SaveAs(("../plots/loopers_4trks/4trksloopers" + filebasename + ".png").c_str());
}

void loopers_2trks(TTree *tree, std::string filebasename){
	    Float_t trk_p[1000];
	    Int_t ntrk;
	    Int_t trk_q[1000];
            const float massPi =0.13957;


	    tree->SetBranchAddress("trk_p", trk_p);
	    tree->SetBranchAddress("trk_q", trk_q);
	    tree->SetBranchAddress("ntrk", &ntrk);

	    TCanvas *c1 = new TCanvas("Figure","Figure",1000,800);
	    TH1F* hist1 = new TH1F(("|p3+p4|/m " + filebasename).c_str(), "|p3+p4|/m", 400, 0, 100);

	    hist1->GetXaxis()->SetTitle("|p3+p4|/m");

	    Long64_t nentries = tree->GetEntries();
	    for (int event=0; event<nentries; event++){
		tree->GetEntry(event);
		if(ntrk == 2){
			Float_t p3 = trk_p[0];
			Float_t p4 = trk_p[1];
			hist1->Fill(abs(p3+p4)/massPi);
		}
	    }
	    hist1->Draw();
	    c1->SaveAs(("../plots/loopers_2trks/2trksloopers" + filebasename + ".png").c_str());
