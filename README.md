# Project structure
In the following I want to briefly explain how this project is structured and how you can use my code if you wish to do so.
Since this was my first bigger coding project most things are not optimally. I hope you may forgive me.
## Documentation
The documentation to my code in form of an html side can be found by opening the file
```
CMSTOTEM_summerjob/docs/html/index.html
```
There you can browse the documentation and familiarise yourself with the different functions. 

## Running the code
To run my code you first need to modify the main function to do what you want. With the help of the documentation you can write your own main function altogether if you wish. But be careful, for running the code in the way I describe below it is essential that there is only one file called `main.cc` in the same location where the initial main can be found.
To run the code, after navigating to the folder containing main and the makefile, there are two options:
1. You can compile and run the code separately. To do so type `make` to compile and `make run` to run. The object files and executable can be removed by `make clean`.
2. You can compile and run in one step by simply typing `./job.sh`. This bashscript will simply do make and them make run.

## Documentation of my results
All of the generated plots can be found in the plots folder in form of root files. This has the advantage that the histograms can be manipulated, after opening them in a TBrowser. Futhermore, you can access my progress reports and notes from some weekly meetings with my supervisor.

### Contacting me
If you any questions about my code please contact me via email: jan.loder@helsinki.fi 
