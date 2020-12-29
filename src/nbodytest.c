#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "./lib/nbody.h"


// Base testing for input san and other basic stuff
void test_suite_1(){
	int argc = 0;
	char **argv = malloc(sizeof(char*)*5);
	struct helper* h_info = input_parser(argc, argv);
	assert(h_info == NULL);
	
	argc = 6;
	h_info = input_parser(argc, argv);
	assert(h_info == NULL);
	
	argc = 4;
	h_info = input_parser(argc, argv);
	assert(h_info == NULL);
	
	printf("1: Passed invalid argument length cases\n");
	
	argc = 5;
	argv[0] = "";
	argv[1] = "0";
	argv[2] = "1";
	argv[3] = "-b";
	argv[4] = "10";
	
	h_info = input_parser(argc, argv);
	assert(h_info == NULL);
	
	printf("1: Passed zero value iterations test\n");
	
	argv[0] = "";
	argv[1] = "abab";
	argv[2] = "1";
	argv[3] = "-b";
	argv[4] = "10";
	
	h_info = input_parser(argc, argv);
	assert(h_info == NULL);
	
	printf("1: Passed non numeric value iterations test\n");
	
	argc = 5;
	argv[0] = "";
	argv[1] = "1";
	argv[2] = "0";
	argv[3] = "-b";
	argv[4] = "10";
	
	h_info = input_parser(argc, argv);
	assert(h_info == NULL);
	
	printf("1: Passed zero value dt test\n");
	
	argv[0] = "";
	argv[1] = "1";
	argv[2] = "abab";
	argv[3] = "-b";
	argv[4] = "10";
	
	h_info = input_parser(argc, argv);
	assert(h_info == NULL);
	
	printf("1: Passed non numeric value dt test\n");
	
	argv[0] = "";
	argv[1] = "1";
	argv[2] = "1";
	argv[3] = "F";
	argv[4] = "10";
	
	h_info = input_parser(argc, argv);
	assert(h_info == NULL);
	
	printf("1: Passed invalid flag test\n");
	
	argv[0] = "";
	argv[1] = "1";
	argv[2] = "1";
	argv[3] = "-b";
	argv[4] = "0";
	
	h_info = input_parser(argc, argv);
	assert(h_info == NULL);
	
	printf("1: Passed zero body test\n");
	
	argv[0] = "";
	argv[1] = "1";
	argv[2] = "1";
	argv[3] = "-b";
	argv[4] = "abab";
	
	h_info = input_parser(argc, argv);
	assert(h_info == NULL);
	
	printf("1: Passed non numeric body test\n");
	
	argv[0] = "";
	argv[1] = "1";
	argv[2] = "1";
	argv[3] = "-f";
	argv[4] = "abab";
	
	h_info = input_parser(argc, argv);
	assert(init_bodies_from_f(h_info) == -1);
	
	printf("1: Passed invalid filename test\n");
	
	argv[0] = "";
	argv[1] = "1";
	argv[2] = "1";
	argv[3] = "-f";
	argv[4] = "csv_tests/sample.csv";
	
	h_info = input_parser(argc, argv);
	assert(init_bodies_from_f(h_info) == 0);
	
	printf("1: Passed valid filename test\n");
	
	
	free(argv);
	free(h_info);
	printf("1: Passed all tests\n");

}

// Testing with the randomized func
void test_suite_2(){
	int argc = 5;
	char **argv = malloc(sizeof(char*)*5);
	
	
	double *start_energy_1 = malloc(sizeof(double));
	double *end_energy_1 = malloc(sizeof(double));
	struct helper* h_info;
	
	// First we will test that multiple iterations with bodies less than 10 (5)
	// still return the same energy results after multiple runs
	// We will test with 100 iterations, and 1000 iterations
	// with dt values of 1, 100, and 1000
	
	
	//-----------
	// 5 bodies 
	
	// 100 iterations dt 1
	argv[0] = "";
	argv[1] = "100";
	argv[2] = "1";
	argv[3] = "-b";
	argv[4] = "5";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_b(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	
	assert(*start_energy_1 == 13762449620.153759);
	assert(*end_energy_1 == 13762365846.334694);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("2: Passed 5 bodies 100 it dt 1\n");
	
	// 100 iterations dt 100
	argv[0] = "";
	argv[1] = "100";
	argv[2] = "100";
	argv[3] = "-b";
	argv[4] = "5";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_b(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%f %f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 34788429756.019981);
	assert(*end_energy_1 == 34788307245.176804);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("2: Passed 5 bodies 100 it dt 100\n");
	
	
	// 100 iterations dt 1000
	argv[0] = "";
	argv[1] = "100";
	argv[2] = "1000";
	argv[3] = "-b";
	argv[4] = "5";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_b(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%f %f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 34024168743.718712);
	assert(*end_energy_1 == 34079069174.722046);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("2: Passed 5 bodies 100 it dt 1000\n");
	
	// 1000 iterations dt 1
	argv[0] = "";
	argv[1] = "1000";
	argv[2] = "1";
	argv[3] = "-b";
	argv[4] = "5";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_b(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%f %f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 33354992772.204304);
	assert(*end_energy_1 == 33355054468.818455);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("2: Passed 5 bodies 1000 it dt 1\n");
	
	
	// 1000 iterations dt 100
	argv[0] = "";
	argv[1] = "1000";
	argv[2] = "100";
	argv[3] = "-b";
	argv[4] = "5";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_b(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%f %f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 35185606318.637985);
	assert(*end_energy_1 == 35181486161.219070);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("2: Passed 5 bodies 1000 it dt 100\n");
	
	// 1000 iterations dt 1000
	argv[0] = "";
	argv[1] = "1000";
	argv[2] = "1000";
	argv[3] = "-b";
	argv[4] = "5";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_b(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%f %f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 41982717356.287285);
	assert(*end_energy_1 == 41887730019.087151);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("2: Passed 5 bodies 1000 it dt 1000\n");
	
	//------------
	// 100 bodies
	
	// 100 iterations dt 1
	argv[0] = "";
	argv[1] = "100";
	argv[2] = "1";
	argv[3] = "-b";
	argv[4] = "100";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_b(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%f %f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 613845536641.965698);
	assert(*end_energy_1 == 613927189920.300171);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("2: Passed 100 bodies 100 it dt 1\n");
	
	// 100 iterations dt 100
	argv[0] = "";
	argv[1] = "100";
	argv[2] = "100";
	argv[3] = "-b";
	argv[4] = "100";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_b(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%f %f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 657726298341.044434);
	assert(*end_energy_1 == 659187340183.927734);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("2: Passed 100 bodies 100 it dt 100\n");
	
	
	// 100 iterations dt 1000
	argv[0] = "";
	argv[1] = "100";
	argv[2] = "1000";
	argv[3] = "-b";
	argv[4] = "100";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_b(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%f %f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 678808450236.267822);
	assert(*end_energy_1 == 691961603182.647827);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("2: Passed 100 bodies 100 it dt 1000\n");
	
	// 1000 iterations dt 1
	argv[0] = "";
	argv[1] = "1000";
	argv[2] = "1";
	argv[3] = "-b";
	argv[4] = "100";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_b(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%f %f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 649361190870.743652);
	assert(*end_energy_1 == 649434209663.792969);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("2: Passed 100 bodies 1000 it dt 1\n");
	
	
	// 1000 iterations dt 100
	argv[0] = "";
	argv[1] = "1000";
	argv[2] = "100";
	argv[3] = "-b";
	argv[4] = "100";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_b(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%f %f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 595265178024.008545);
	assert(*end_energy_1 == 595953553052.646484);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("2: Passed 100 bodies 1000 it dt 100\n");
	
	// 1000 iterations dt 1000
	argv[0] = "";
	argv[1] = "1000";
	argv[2] = "1000";
	argv[3] = "-b";
	argv[4] = "100";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_b(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%f %f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 648492679639.652832);
	assert(*end_energy_1 == 728169006584.016357);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("2: Passed 00 bodies 1000 it dt 1000\n");
	
	//------------
	// 200 bodies
	
	// 100 iterations dt 1
	argv[0] = "";
	argv[1] = "100";
	argv[2] = "1";
	argv[3] = "-b";
	argv[4] = "200";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_b(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%f %f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 1314519903131.642334);
	assert(*end_energy_1 == 1315179846777.334717);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("2: Passed 200 bodies 100 it dt 1\n");
	
	// 100 iterations dt 100
	argv[0] = "";
	argv[1] = "100";
	argv[2] = "100";
	argv[3] = "-b";
	argv[4] = "200";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_b(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%f %f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 1264308203795.317383);
	assert(*end_energy_1 == 1270304782229.630371);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("2: Passed 200 bodies 100 it dt 100\n");
	
	
	// 100 iterations dt 1000
	argv[0] = "";
	argv[1] = "100";
	argv[2] = "1000";
	argv[3] = "-b";
	argv[4] = "200";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_b(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%f %f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 1267996832038.817627);
	assert(*end_energy_1 == 1411127142570.905273);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("2: Passed 200 bodies 100 it dt 1000\n");
	
	// 1000 iterations dt 1
	argv[0] = "";
	argv[1] = "1000";
	argv[2] = "1";
	argv[3] = "-b";
	argv[4] = "200";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_b(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%f %f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 1125040149291.287598);
	assert(*end_energy_1 == 1125279002292.099121);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("2: Passed 200 bodies 1000 it dt 1\n");
	
	
	// 1000 iterations dt 100
	argv[0] = "";
	argv[1] = "1000";
	argv[2] = "100";
	argv[3] = "-b";
	argv[4] = "200";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_b(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%f %f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 1292206246204.258301);
	assert(*end_energy_1 == 1288359936774.388916);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("2: Passed 200 bodies 1000 it dt 100\n");
	
	// 1000 iterations dt 1000
	argv[0] = "";
	argv[1] = "1000";
	argv[2] = "1000";
	argv[3] = "-b";
	argv[4] = "200";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_b(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%f %f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 1232230025268.144043);
	assert(*end_energy_1 == 1362477405261.938232);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("2: Passed 200 bodies 1000 it dt 1000\n");
	
	free(argv);
	free(start_energy_1);
	free(end_energy_1);
	printf("2: Passed all test cases\n");

}

// Testing with the load from file func
void test_suite_3(){
	// For this method, we will use the following CSV files:
	// - 10.csv, 50.csv, 100.csv
	int argc = 5;
	char **argv = malloc(sizeof(char*)*5);
	
	
	double *start_energy_1 = malloc(sizeof(double));
	double *end_energy_1 = malloc(sizeof(double));
	struct helper* h_info;
	
	// First we will test that multiple iterations with bodies less than 10 (5)
	// still return the same energy results after multiple runs
	// We will test with 100 iterations, and 1000 iterations
	// with dt values of 1, 100, and 1000
	
	
	//-----------
	// 10.csv bodies 
	
	// 100 iterations dt 1
	argv[0] = "";
	argv[1] = "100";
	argv[2] = "1";
	argv[3] = "-f";
	argv[4] = "csv_tests/10.csv";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_f(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%.50f %.50f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 780.9769999984172272888827137649059295654296875);
	assert(*end_energy_1 == 780.976999998421661075553856790065765380859375);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("3: Passed 10.csv bodies 100 it dt 1\n");
	
	// 100 iterations dt 100
	argv[0] = "";
	argv[1] = "100";
	argv[2] = "100";
	argv[3] = "-f";
	argv[4] = "csv_tests/10.csv";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_f(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%.50f %.50f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 780.9769999984172272888827137649059295654296875);
	assert(*end_energy_1 == 780.9770000004582470864988863468170166015625);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("3: Passed 10.csv bodies 100 it dt 100\n");
	
	
	// 100 iterations dt 1000
	argv[0] = "";
	argv[1] = "100";
	argv[2] = "1000";
	argv[3] = "-f";
	argv[4] = "csv_tests/10.csv";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_f(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%.50f %.50f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 780.9769999984172272888827137649059295654296875);
	assert(*end_energy_1 == 780.977000007130072845029644668102264404296875);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("3: Passed 10.csv bodies 100 it dt 1000\n");
	
	// 1000 iterations dt 1
	argv[0] = "";
	argv[1] = "1000";
	argv[2] = "1";
	argv[3] = "-f";
	argv[4] = "csv_tests/10.csv";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_f(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%.50f %.50f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 780.9769999984172272888827137649059295654296875);
	assert(*end_energy_1 == 780.976999998492601662292145192623138427734375);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("3: Passed 10.csv bodies 1000 it dt 1\n");
	
	
	// 1000 iterations dt 100
	argv[0] = "";
	argv[1] = "1000";
	argv[2] = "100";
	argv[3] = "-f";
	argv[4] = "csv_tests/10.csv";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_f(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%.50f %.50f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 780.9769999984172272888827137649059295654296875);
	assert(*end_energy_1 == 780.97700000045961132855154573917388916015625);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("3: Passed 10.csv bodies 1000 it dt 100\n");
	
	// 1000 iterations dt 1000
	argv[0] = "";
	argv[1] = "1000";
	argv[2] = "1000";
	argv[3] = "-f";
	argv[4] = "csv_tests/10.csv";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_f(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%.50f %.50f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 780.9769999984172272888827137649059295654296875);
	assert(*end_energy_1 == 780.9770000071303002187050879001617431640625);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("3: Passed 10.csv bodies 1000 it dt 1000\n");
	
	//------------
	// 50.csv bodies
	
	// 100 iterations dt 1
	argv[0] = "";
	argv[1] = "100";
	argv[2] = "1";
	argv[3] = "-f";
	argv[4] = "csv_tests/50.csv";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_f(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%.50f %.50f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 4410.6999999598456270177848637104034423828125);
	assert(*end_energy_1 == 4410.6999999614226908306591212749481201171875);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("3: Passed 50.csv bodies 100 it dt 1\n");
	
	// 100 iterations dt 100
	argv[0] = "";
	argv[1] = "100";
	argv[2] = "100";
	argv[3] = "-f";
	argv[4] = "csv_tests/50.csv";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_f(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%.50f %.50f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 4410.6999999598456270177848637104034423828125);
	assert(*end_energy_1 == 4410.700000006021582521498203277587890625);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("3: Passed 50.csv bodies 100 it dt 100\n");
	
	
	// 100 iterations dt 1000
	argv[0] = "";
	argv[1] = "100";
	argv[2] = "1000";
	argv[3] = "-f";
	argv[4] = "csv_tests/50.csv";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_f(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%.50f %.50f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 4410.6999999598456270177848637104034423828125);
	assert(*end_energy_1 == 4410.700000100883698905818164348602294921875);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("3: Passed 50.csv bodies 100 it dt 1000\n");
	
	// 1000 iterations dt 1
	argv[0] = "";
	argv[1] = "1000";
	argv[2] = "1";
	argv[3] = "-f";
	argv[4] = "csv_tests/50.csv";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_f(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%.50f %.50f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 4410.6999999598456270177848637104034423828125);
	assert(*end_energy_1 == 4410.6999999629870217177085578441619873046875);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("3: Passed 50.csv bodies 1000 it dt 1\n");
	
	
	// 1000 iterations dt 100
	argv[0] = "";
	argv[1] = "1000";
	argv[2] = "100";
	argv[3] = "-f";
	argv[4] = "csv_tests/50.csv";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_f(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%.50f %.50f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 4410.6999999598456270177848637104034423828125);
	assert(*end_energy_1 == 4410.7000000060334059526212513446807861328125);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("3: Passed 50.csv bodies 1000 it dt 100\n");
	
	// 1000 iterations dt 1000
	argv[0] = "";
	argv[1] = "1000";
	argv[2] = "1000";
	argv[3] = "-f";
	argv[4] = "csv_tests/50.csv";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_f(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%.50f %.50f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 4410.6999999598456270177848637104034423828125);
	assert(*end_energy_1 == 4410.700000100883698905818164348602294921875);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("3: Passed 50.csv bodies 1000 it dt 1000\n");
	
	//------------
	// 100.csv bodies
	
	// 100 iterations dt 1
	argv[0] = "";
	argv[1] = "100";
	argv[2] = "1";
	argv[3] = "-f";
	argv[4] = "csv_tests/100.csv";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_f(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%.50f %.50f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 7005.3044998667564868810586631298065185546875);
	assert(*end_energy_1 == 7005.304499872514497837983071804046630859375);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("3: Passed 100.csv bodies 100 it dt 1\n");
	
	// 100 iterations dt 100
	argv[0] = "";
	argv[1] = "100";
	argv[2] = "100";
	argv[3] = "-f";
	argv[4] = "csv_tests/100.csv";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_f(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%.50f %.50f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 7005.3044998667564868810586631298065185546875);
	assert(*end_energy_1 == 7005.304499987081726430915296077728271484375);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("3: Passed 100.csv bodies 100 it dt 100\n");
	
	
	// 100 iterations dt 1000
	argv[0] = "";
	argv[1] = "100";
	argv[2] = "1000";
	argv[3] = "-f";
	argv[4] = "csv_tests/100.csv";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_f(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%.50f %.50f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 7005.3044998667564868810586631298065185546875);
	assert(*end_energy_1 == 7005.30449997077812440693378448486328125);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("3: Passed 100.csv bodies 100 it dt 1000\n");
	
	// 1000 iterations dt 1
	argv[0] = "";
	argv[1] = "1000";
	argv[2] = "1";
	argv[3] = "-f";
	argv[4] = "csv_tests/100.csv";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_f(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%.50f %.50f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 7005.3044998667564868810586631298065185546875);
	assert(*end_energy_1 == 7005.304499878135175094939768314361572265625);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("3: Passed 100.csv bodies 1000 it dt 1\n");
	
	
	// 1000 iterations dt 100
	argv[0] = "";
	argv[1] = "1000";
	argv[2] = "100";
	argv[3] = "-f";
	argv[4] = "csv_tests/100.csv";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_f(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%.50f %.50f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 7005.3044998667564868810586631298065185546875);
	assert(*end_energy_1 == 7005.304499980937180225737392902374267578125);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("3: Passed 100.csv bodies 1000 it dt 100\n");
	
	// 1000 iterations dt 1000
	argv[0] = "";
	argv[1] = "1000";
	argv[2] = "1000";
	argv[3] = "-f";
	argv[4] = "csv_tests/100.csv";
	h_info = input_parser(argc, argv);
	printf("Broke\n");
	init_bodies_from_f(h_info);
	for(int i = 0; i < h_info->iterations; i++){
		step(h_info, i, start_energy_1, end_energy_1);
	}
	free(h_info);
	printf("%.50f %.50f\n",*start_energy_1, *end_energy_1);
	assert(*start_energy_1 == 7005.3044998667564868810586631298065185546875);
	assert(*end_energy_1 == 7005.304499891322848270647227764129638671875);
	*start_energy_1 = 0;
	*end_energy_1 = 0;
	printf("3: Passed 100.csv bodies 1000 it dt 1000\n");
	
	free(argv);
	free(start_energy_1);
	free(end_energy_1);
	printf("3: Passed all test cases\n");
	

}

int main(int argc, char **argv){
	if(argc != 2){
		printf("Invalid number of arguments\n");
	}else{
		if(strcmp(argv[1], "1") == 0){
			printf("Running test suite 1\n");
			test_suite_1();
		
		}else if(strcmp(argv[1],"2") == 0){
			printf("Running test suite 2\n");
			test_suite_2();
			
		}else if(strcmp(argv[1],"3") == 0){
			printf("Running test suite 3\n");
			test_suite_3();
			
		}else if(strcmp(argv[1],"all") == 0){
			printf("Running all test suites\n");
			test_suite_1();
			test_suite_2();
			test_suite_3();
			printf("All: Passed all test cases\n");
		}
	
	}

}
