#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "nbody.h"

//NOTE: ALL OPERATIONS DONE BETWEEN TWO BODIES WITH DISTANCE ARE OF THE FOLLOWING ORDER: b1 - b2
double square(double a){
	return a*a;
}

/*
	REQUIRES:
	- PRE-CALCULATED DOUBLE ARRAY OF DISTANCE VECTOR B/W BODY 1 AND 2
	- MAGNITUDE
	- MASS OF BODY 1 (or body i)
	RETURNS:
	- ACCELERATION VECTORS X, Y, Z FROM BODY 1 TO BODY 2 (i to j)
*/
double* calculate_accelerations(double* dist_vectors, double magnitude, double mass){
	double *accel_vectors = malloc(sizeof(double)*3);
	
	//printf("Magnitude %f, Mass %f \n",magnitude,mass);
	
	// the x accel vector
	accel_vectors[0] = (dist_vectors[0] * magnitude)/mass;
	
	// the y accel vector
	accel_vectors[1] = (dist_vectors[1] * magnitude)/mass;
	
	// the z accel vector
	accel_vectors[2] = (dist_vectors[2] * magnitude)/mass;
	
	return accel_vectors;
}	

/*
	REQUIRES:
	- BODY 1
	- BODY 2
	- DISTANCE BETWEEN BODY 1 AND BODY 2
	RETURNS:
	- THE DISTANCE VECTOR BETWEEN THE TWO BODIES (FROM BODY 1 TO BODY 2 (i to j)
		- 3 DIM DOUBLE ARRAY IN ORDER: X, Y, Z
*/
double* calculate_dist_vectors(struct body* b1, struct body* b2, double dist_bodies){
	// will need to be free'd later in execution
	double *dist_vectors = malloc(sizeof(double)*3);
	// the x distance vector
	dist_vectors[0] = (b2->x - b1->x)/dist_bodies;
	
	// the y distance vector
	dist_vectors[1] = (b2->y - b1->y)/dist_bodies;
	
	// the z distance vector
	dist_vectors[2] = (b2->z - b1->z)/dist_bodies;
	
	return dist_vectors;
}	

/*
	REQUIRES:
	- BODY 1
	- BODY 2
	- DISTANCE BETWEEN BODY 1 AND BODY 2
	RETURNS:
	- DOUBLE VALUE FOR MAGNITUDE
*/
double calculate_magnitude(struct body* b1, struct body* b2, double dist_bodies){
	//printf("Calc mag %f\n",(GCONST*((b1->mass * b2->mass)/square(dist_bodies))));
	//printf("GCONST %f\n",GCONST);
	return(GCONST*((b1->mass * b2->mass)/square(dist_bodies)));

}

/*
	REQUIRES:
	- BODY 1
	- BODY 2
	RETURNS:
	- DOUBLE VALUE FOR DISTANCE
*/
double calculate_distance(struct body* b1, struct body* b2){
	// using formula provided in assignment spec we will calculate
	// distance between two provided bodies and then return result
	
	return(sqrt(square(b1->x - b2->x) + square(b1->y - b2->y) + square(b1->z - b2->z)));
}

void init_bodies_from_b(struct helper* h_info){
	// We need to create some randomized function to assign values to the number of bodies.
	// We will create a body array of the size n_bodies and assign each body within the array separately.
	/*
		PARAMS FOR RANDOMIZATION:
		
		x_pos: between -50 and 50
		y_pos: between -50 and 50
		z_pos: between -50 and 50
		
		x_velocity: between -5 and 5
		y_velocity: between -5 and 5
		z_velocity: between -5 and 5
		
		mass: between 0.001 and 0.1
	
	*/
	h_info->bodies = malloc(sizeof(struct body)*h_info->n_bodies);
	double max_x_pos = 50.0;
	double max_y_pos = 50.0;
	double max_z_pos = 50.0;
	double max_x_vel = 5.0;
	double max_y_vel = 5.0;
	double max_z_vel = 5.0;
	double max_mass = 1000000000.0;
	for(int i = 0; i < h_info->n_bodies; i++){
		// Malloc each struct body* and assign randomized params and store in bodies array
		struct body* temp_body = malloc(sizeof(struct body));
		temp_body->x = (((double)rand()/(double)(RAND_MAX)) * 2 * max_x_pos) - max_x_pos;
		temp_body->y = (((double)rand()/(double)(RAND_MAX)) * 2 * max_y_pos) - max_y_pos;
		temp_body->z = (((double)rand()/(double)(RAND_MAX)) * 2 * max_z_pos) - max_z_pos;
		temp_body->velocity_x = (((double)rand()/(double)(RAND_MAX)) * 2 * max_x_vel) - max_x_vel;
		temp_body->velocity_y = (((double)rand()/(double)(RAND_MAX)) * 2 * max_y_vel) - max_y_vel;
		temp_body->velocity_z = (((double)rand()/(double)(RAND_MAX)) * 2 * max_z_vel) - max_z_vel;
		temp_body->mass = (((double)rand()/(double)(RAND_MAX)) * max_mass);
		
		printf("x:%f\n",temp_body->x);
		printf("y:%f\n",temp_body->y);
		printf("z:%f\n",temp_body->z);
		printf("x_vl:%f\n",temp_body->velocity_x);
		printf("y_vl:%f\n",temp_body->velocity_y);
		printf("z_vl:%f\n",temp_body->velocity_z);
		printf("mass:%f\n",temp_body->mass);
		printf("\n\n");
		h_info->bodies[i] = temp_body;
	}

}

void load_bodies_from_file(struct helper* h_info, FILE *file){
	rewind(file);
	char buffer[BUFFER_SIZE];
	for(int i = 0; i < h_info->n_bodies; i++){
		struct body* temp_body = malloc(sizeof(struct body));
		h_info->bodies[i] = temp_body;
		fgets(buffer, sizeof(buffer), file);
		char *tok = strtok(buffer, ",");
		h_info->bodies[i]->x = atof(tok); 
		printf("%f, ",h_info->bodies[i]->x);
		
		tok = strtok(NULL, ","); 
		h_info->bodies[i]->y = atof(tok); 
		printf("%f, ",h_info->bodies[i]->y);
		
		tok = strtok(NULL, ","); 
		h_info->bodies[i]->z = atof(tok); 
		printf("%f, ",h_info->bodies[i]->z);
		
		tok = strtok(NULL, ","); 
		h_info->bodies[i]->velocity_x = atof(tok); 
		printf("%f, ",h_info->bodies[i]->velocity_x);
		
		tok = strtok(NULL, ","); 
		h_info->bodies[i]->velocity_y = atof(tok); 
		printf("%f, ",h_info->bodies[i]->velocity_y);
		
		tok = strtok(NULL, ","); 
		h_info->bodies[i]->velocity_z = atof(tok); 
		printf("%f, ",h_info->bodies[i]->velocity_z);
		
		tok = strtok(NULL, ","); 
		h_info->bodies[i]->mass = atof(tok); 
		printf("%f\n",h_info->bodies[i]->mass);
		
		
	
	}
	return;
}

void init_bodies_from_f(struct helper* h_info){
	
	// FILE PARSING WILL NEED TO OCCUR HERE
	// COUNT N_LINES TO DETERMINE NUMBER OF BODIES AND SAVE IN H_INFO
	// THE REWIND AND PROCESS EACH BODY LINE BY LINE, SAVE TO THE BODIES ARRAY TO BE RETURNED
	FILE *file;
	
	printf("%s\n",h_info->filename);
	file = fopen(h_info->filename,"r");
	if(file == NULL){
      		printf("Error openining specified filepath! Check the file exists.\n");   
      		return;            
   	}
   	int lines =0;

  	while (EOF != (fscanf(file, "%*[^\n]"), fscanf(file,"%*c"))){
        	++lines;
        }
   	printf("Nlines: %d\n",lines);
   	
	h_info->n_bodies = lines;
	h_info->bodies = malloc(sizeof(struct body)*h_info->n_bodies);
	
	load_bodies_from_file(h_info,file);
	
	
	
	// close opened file pointer
	fclose(file);
	return;
	

}

struct helper* input_parser(int argc, char** argv){
	if(argc < 5 || argc > 5){
		printf("Invalid number of input arguments were provided, you provided "
			"%d argument(s), when 5 should be provided.\n",argc);
		return NULL;
	}
	// Past this point correct num args provided
	if(atoi(argv[1]) == 0){
		printf("The iterations value provided was either invalid or equal to zero.\n");
		return NULL;
	}
	if(atof(argv[2]) == 0.0){
		printf("The dt value provided was either invalid or equal to zero.\n");
		return NULL;
	}
	
	struct helper* h_info = malloc(sizeof(struct helper));
	h_info->iterations = atoi(argv[1]);
	h_info->dt = atof(argv[2]);
	
	if(strcmp(argv[3],"-b") == 0){
		// the flag was -b
		if(atoi(argv[4]) == 0){
			printf("The number of bodies you specified was either invalid or equal to zero.\n");
			return NULL;
		}
		h_info->flag_type = 0;
		h_info->n_bodies = atoi(argv[4]);
		
		return h_info;
	}
	else if(strcmp(argv[3],"-f") == 0){
		// the flag was -f
		// Further work will need to be done to calculate the number of bodies
		char* tmp_filename = malloc(strlen(argv[4]));
		tmp_filename = argv[4];
		h_info->filename = argv[4];
		h_info->flag_type = 1;
		
		return h_info;
	}
	else{
		printf("The flag you provided was invalid! %s when it should have been either -b or -f.\n",argv[3]);
		return NULL;
	}
	
}

void update_element_positions(struct body* body, double dt){
	body->x = body->x + body->velocity_x * dt;
	body->y = body->y + body->velocity_y * dt;
	body->z = body->z + body->velocity_z * dt;
	
}

void update_velocities_and_positions(struct helper* h_info, double dt){
	
	for(int i = 0; i < h_info->n_bodies; i++){
		double temp_sum_x = h_info->bodies[i]->velocity_x;
		double temp_sum_y = h_info->bodies[i]->velocity_y;
		double temp_sum_z = h_info->bodies[i]->velocity_z;
		
		
		// This needs to be ported to a threadable method. We can also unroll this some amount
		for(int j = 0; j < h_info->n_bodies; j++){
			if(j != i){
				// do our stuff here. We now have a body i and a body j.
				// the calculation should be relatively basic from this point onward.
				// potentially update this to make some calls for pos updates too?? tbd
				
				
				// FIRST calculate distance between i and j
				// NEXT calculate magnitude between i and j
				// NEXT calculate unit vectors between i and j
				// FINALLY calculate acceleration between i and j (USE MASS OF i)
				double distance = calculate_distance(h_info->bodies[i], h_info->bodies[j]);
				double magnitude = calculate_magnitude(h_info->bodies[i], h_info->bodies[j], distance);
				//printf("MAGNITUDE: %f DISTANCE: %f\n",magnitude,distance);
				double* dist_vectors = calculate_dist_vectors(h_info->bodies[i], h_info->bodies[j], distance);
				double* accel_vectors = calculate_accelerations(dist_vectors, magnitude, h_info->bodies[i]->mass);
				
				//printf("Dist vectors for %d\n %f \n %f \n %f \n",j,dist_vectors[0],dist_vectors[1],dist_vectors[2]);
				//printf("Accel vectors for %d\n %f \n %f \n %f \n",j,accel_vectors[0],accel_vectors[1],accel_vectors[2]);
				// add x comp
				temp_sum_x += accel_vectors[0] * dt;
				// add y comp
				temp_sum_y += accel_vectors[1] * dt;
				// add z comp
				temp_sum_z += accel_vectors[2] * dt;
				
				
				// FREE UNIT VECTORS AND ACCELERATION HERE
				free(dist_vectors);
				free(accel_vectors);
				
			}
		}
		
		// Implement a barrier here
		
		
		
		//printf("Next     x position for body %d %f\n",i,h_info->bodies[i]->x);
		//printf("Next     y position for body %d %f\n",i,h_info->bodies[i]->y);
		
		// Now make a call to update new positions for the element 
		//printf("Previous x position for body %d %f\n",i,h_info->bodies[i]->x);
		//printf("Previous y position for body %d %f\n",i,h_info->bodies[i]->y);
		
		update_element_positions(h_info->bodies[i], dt);
		
		
		// Now update the velocity components
		//printf("Previous x velocity for body %d %f\n",i,h_info->bodies[i]->velocity_x);
		//printf("Previous y velocity for body %d %f\n",i,h_info->bodies[i]->velocity_y);
		h_info->bodies[i]->velocity_x = temp_sum_x;
		h_info->bodies[i]->velocity_y = temp_sum_y;
		h_info->bodies[i]->velocity_z = temp_sum_z;
		//printf("Next     x velocity for body %d %f\n",i,h_info->bodies[i]->velocity_x);
		//printf("Next     y velocity for body %d %f\n",i,h_info->bodies[i]->velocity_y);
		//printf("Updated velocities for body %d: \n %f \n %f \n %f \n",i,temp_sum_x, temp_sum_y, temp_sum_z);
		
		
	}
}

double calculate_energies(struct helper* h_info, int it_n){
	// reset energy before recalculating
	double prev_energy = h_info->energy;
	h_info->energy = 0;
	
	for(int i = 0; i < h_info->n_bodies; i++){
	
		h_info->energy += (h_info->bodies[i]->mass * (square(h_info->bodies[i]->velocity_x)
		 		+ square(h_info->bodies[i]->velocity_y) + square(h_info->bodies[i]->velocity_z))) / 2;
		
		for(int j = i + 1; j < h_info->n_bodies; j++){
		
			if(j != i){
				h_info->energy -= -(GCONST * ((h_info->bodies[i]->mass * h_info->bodies[j]->mass) / 
						calculate_distance(h_info->bodies[i], h_info->bodies[j])));
			}
			
		}
	}
	printf("CHANGE ENERGY IN SYSTEM IT %d: %e\n",it_n,prev_energy - h_info->energy);
	
	return(h_info->energy);
}

void step(struct helper* h_info, int current_it, double *start_energy, double *end_energy){


	if(current_it == 0){
		*start_energy = calculate_energies(h_info, current_it+1);
	}else{
		*end_energy = calculate_energies(h_info, current_it+1);
	}
		
	update_velocities_and_positions(h_info, h_info->dt);

	
}

