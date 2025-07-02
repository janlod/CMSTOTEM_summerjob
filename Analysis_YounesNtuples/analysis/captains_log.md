
# Analysis of YounesNtuples

-Data taken from: 
```
/eos/cms/store/group/phys_diffraction/CMSTotemLowPU2018/YounesNtuples/
```

- June 19 17:41:
    Implemented Analysis on YounesNtuples. Until now only PV distributions

- June 24 17:14:
    Implmented everything from Tracks in CMS Tracker part of glueball_study_topics doc except last two bullet points

- June 25 16:50:
    Worked on analysis for loopers

- June 26 17:08:
    countinued on loopers

- June 30 10:05:
    - There seem to be no loopers for 2trk events, since there are no 3-trk events (ntrk histo looks interesting) at all and for all 2-trk events there is no peak around zero in the |p3+p4|/m distribution
    - There also seem to be no loopers for 4trk events (if I implemented the analysis correctly). We have no peaks around zero in the |p3+p4|/m
    distribution for any of the 6 possible pairings
    - Working on cuts 2-3

- July 2 17:48:
    - Worked on cuts, becasue I realised yesterday that I need to do all cuts simultaneously so I can check range for all variables of events at the same time
    - Problem now is that the Fits on the 2d plots often get invalid fit results because root fit does not converge for some reason    
