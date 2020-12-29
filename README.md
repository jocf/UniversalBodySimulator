WHAT IS THIS?
- This code is a simulation that simulates graviational bodies in space. The code is multithreaded using pthread, so as to demonstrate how
we can implement performance improvements WITHOUT using MPI. 

HOW TO COMPILE THIS CODE:

- A makefile has been provided with this code. The makefile supports four different arguments with the following format:
	- make {argument}
		- Argument can take the following options (nbody | nbody-gui | test | clean)
			- nbody will compile the CLI simulation
			- nbody-gui will compile the GUI simulation
			- test will compile the test cases
			- clean will clean the repository

IMPORTANT INFORMATION WITH BENCHMARK:

- I have provided a very rudimentary benchmarker in this source code as well.
- It simply benchmarks 10, 50, 100, 250, and 500 bodies with iterations of 10, 100, 1000 and 2000, and dt values of 0.1, 1, 100, 1000, 10000
- The script is based off of Jayden Zangari's script provided on Ed.
- To run the script, the CLI MUST be compiled before trying to use it.
- To edit any of the values, this can easily be done within the bash script. I have selected values that provide a 
	broad range of data that is interesting.
- To execute the benchmark please use the following command:
		- bash benchmark.sh

IMPORTANT INFORMATION WITH CLI:

- The CLI accepts the following arguments:
		./nbody <iterations> <dt> (-b <bodies> | -f <filename>)
- Some formatted examples of input look as follows:
		./nbody 3000 0.01 -b 50
		./nbody 3000 0.01 -f csv_tests/data.csv

IMPORTANT INFORMATION WITH TESTS:

- The tests can be compiled with the makefile as when used as described above.
- Once they have been compiled, please run ./nbodytest {test argument}
	- The test argument field accepts 4 values:
		- 1 : execute test suite 1
		- 2 : execute test suite 2
		- 3 : execute test suite 3
		- all : execute all test suites
	- An example argument would look as follows:
		./nbodytest all
	
	- A breakdown of each test suite:
		- 1: Basic input sanitization tests, incorrect filenames etc.
		- 2: Randomized body tests with variations of dt and iterations
		- 3: File body tests with variations of dt and iterations using
			files included in the csv_tests folder


IMPORTANT INFORMATION WITH THE GUI:

- While using the GUI application, it is important that a dataset with ideal values is used.
	- Ideal values means that there are less than 10 planets, that are well spaced, and there is one large central mass.
	- While the GUI will still "work" with non-ideal datasets, it may not scale nicely.
	- Using the sample.csv provided in this repo, this command will display the GUI ideally:
		./nbodygui 800 600 100 12500 -f csv_tests/sample.csv 0.000000001
	- Setting an appropriate scaling factor is also very important! The command line argument provided above already includes
	  a suitable factor for the provided dataset.
	  
	- The GUI application accepts the following arguments:
		/nbody-gui <resolution_width> <resolution_height> <iterations> <dt> (-b <bodies> | -f <filename>) (scale)
	- An example formatted argument would look as follows:
		./nbodygui 800 600 100 12500 -f csv_tests/sample.csv 0.000000001
		
		
OTHER NOTES:
	- I have included the linear implementation of the code in the repository as well under the folder "Linear Implementation." 
	  This may be useful to look at in comparison to the non-linear approach.
