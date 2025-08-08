# Remarks

- Check mass of photoproduced rho rho (applicability?)
- Cut on eta and pt, we expect low pt and eta<1.5 from physics
- Compare rho mass fits with Tom
- Bias in 2d histogram because ROOT sorts trks by p or pt, which means that we always put the higher momentum trks on x axis (not big issue for me)
- Implement elastic veto for diagonal (TOTEM2)
- play with cuts for TOTEM4 and optimise final plot
- Cut on sum(trk\_p) - sum(pr\_p) to filter out events with good momentum matching
- In generla understands cuts better, which cuts push the beginning of the histogram high and low
- Look at typical chi2 (for dxy, dz) distribution of rhos and Kaons by zooming in on histogram to pure Kaon/Rho regions
- Look at 2015 analyis to learn about cuts on proton azimuthal angle
- Later if time assume Kaon masses and look at at 2d inv mass hist

# Priority

1. Refine cuts for TOTEM2 and TOTEM4
2. Look at chi2 distributions for rho and Kaon, could help finding values for 1.
3. Implement elastic veto
4. Cut on sum trk\_p - pr\_p
5. Cuts on proton azimuthal angles (look at 2015 analysis)
6. Assume Kaon mass and make 2d histo, only if 1.-5. is done
