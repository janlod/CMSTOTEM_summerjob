# Remarks:
- Invariant mass 2D scatter histo seems to be fine, but it has some asymmetry
- Kaon fits seem to be good, but sigma\_y is signific bigger than sigma\_x, possibly due to track ordering by highest momentum first and then resulting asymmetry in invariant masses
- Put x and y projection in same plot and check if peaks match
- Asymmetry is probably negligible, not a problem for now
- Do not do any pt cuts 
- Valid to combine data of all TOTEM20s with each other and then also combine TOTEM40s among themselves
- Next general idea: Introduce $\chi^2$-like variable
	- $\chi^2 = \sum_\text{trks}(x_{\text{mean}} - x_{\text{trk}})^2$, where $x_{\text{mean}}$ is from gaussian fits from uncutted $x$ distribution and $x_{\text{trk}}$ is the value of some trks
	- Then you can look at $\chi^2$ distribution and cut that to avoid to uch loss of events
	- Idea: It doesn't matter if one trk is poorly reconstructed, rather the average of all reconstructions should decide whether event is "good" or "bad"
	- Do this for all $x$ : dxy/sigma\_dxy, dz/sigma\_dz, zPV, dxy (from 2d correl plot), dz (from 2d correl plot), kaon mass and eventually rho mass
- Think about backround fits (just fits on functional form), only under the peak and only polynomial or exponential, noting too complicated

# Priority:
1. Check charges of 4 trk events and compare with Tom
2. Finish dataCombiner to combine the datafiles
3. Rerun invariant mass reconstruction on larger data (i.e. make 2d plots and then kaonmass fits)
4. Put x and y projections in one plot to compare peak positions and widths
5. Introduce chi^2 variable for combined data files (for each of above mentioned quantities)
6. Improve leat square fit exercise (Lagrange multipliers)
7. Structure code and clean up
8. Have fun :-) (should be 1.)
