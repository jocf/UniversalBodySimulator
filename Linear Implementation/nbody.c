#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "nbody.h"


int main(int argc, char** argv) {
	struct helper* h_info = input_parser(argc, argv);
	h_info->energy = 0;
	
	if(h_info == NULL){
		exit(-1);
	}
	
	double *start_energy = malloc(sizeof(double));
	double *end_energy = malloc(sizeof(double));
	
	if(h_info->flag_type == 0){
		// b mode
		init_bodies_from_b(h_info);
		for(int i = 0; i < h_info->iterations; i++){
			step(h_info, i, start_energy, end_energy);
		}

	}
	else{
		
		// f mode
		init_bodies_from_f(h_info);
		for(int i = 0; i < h_info->iterations; i++){
			step(h_info, i, start_energy, end_energy);
		}
	}
	printf("Total change in system: %e\n",*end_energy - *start_energy);
	return 0;
}
