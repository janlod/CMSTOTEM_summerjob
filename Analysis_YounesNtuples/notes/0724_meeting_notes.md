# Remarks:
- To obtain better rho mass fit we need to account for background (probably by describing functional form)
- For details see emails with pdfs from Kenneth
- $\chi^2$ for dxy/dxyerr and dz/dzerr is already normalised, but zPV need normalisation We should normalise to sigma, i.e. $\chi^2 = \sum \frac{(\mu/ - x\_i)^2}{\sigma^2}$


# Priority:
1. Check chi2 branches order of magnitude after correct normalisation on zPV
2. Make cuts on one chi2 brnach and keep other two constant to see effect
3. Find reasonable chi2 cut for rho mass fit. Maybe more restrictive for initial fit and then for later analysis to get more statistics
4. Include Background and refit rho masses 
5. Use resulting mean and sigma to define another chi2-like variable on the rho mass
6. Use the chi2-like variable to identify wrong pairings in rho mass reconstruction on event to event basis (we should have 2 chi like values per event)
7. Remove wrong pairings
8. Reconstruct total invariant mass of 4 trk system. 
