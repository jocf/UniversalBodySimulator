#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include "./lib/nbody.h"

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

int init_bodies_from_f(struct helper* h_info){
	
	// FILE PARSING WILL NEED TO OCCUR HERE
	// COUNT N_LINES TO DETERMINE NUMBER OF BODIES AND SAVE IN H_INFO
	// THE REWIND AND PROCESS EACH BODY LINE BY LINE, SAVE TO THE BODIES ARRAY TO BE RETURNED
	FILE *file;
	
	printf("%s\n",h_info->filename);
	file = fopen(h_info->filename,"r");
	if(file == NULL){
      		printf("Error openining specified filepath! Check the file exists.\n"); 
      		return -1;            
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
	return 0;
	

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
		//char* tmp_filename = malloc(strlen(argv[4]));
		//tmp_filename = argv[4];
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

void* thread_helper(void* args){
	struct thread_data* data = (struct thread_data*)(args);
	
	for(int i = data->start; i < data->end; i++){
		
		// Perform inner j loop for all other elements
		double register temp_sum_x = data->h_info->bodies[i]->velocity_x;
		double register temp_sum_y = data->h_info->bodies[i]->velocity_y;
		double register temp_sum_z = data->h_info->bodies[i]->velocity_z;
		double register distance;
		double register magnitude;

		// This needs to be ported to a threadable method. We can also unroll this some amount
		for(int j = 0; j < data->h_info->n_bodies; j++){
			if(j != i){
				// do our stuff here. We now have a body i and a body j.
				// the calculation should be relatively basic from this point onward.
				// potentially update this to make some calls for pos updates too?? tbd
				
				
				// FIRST calculate distance between i and j
				// NEXT calculate magnitude between i and j
				// NEXT calculate unit vectors between i and j
				// FINALLY calculate acceleration between i and j (USE MASS OF i)
				distance = calculate_distance(data->h_info->bodies[i], data->h_info->bodies[j]);
				magnitude = calculate_magnitude(data->h_info->bodies[i], data->h_info->bodies[j], distance);
				//printf("MAGNITUDE: %f DISTANCE: %f\n",magnitude,distance);
				double* dist_vectors = calculate_dist_vectors(data->h_info->bodies[i], data->h_info->bodies[j], distance);
				double* accel_vectors = calculate_accelerations(dist_vectors, magnitude, data->h_info->bodies[i]->mass);

				// add x comp
				temp_sum_x += accel_vectors[0] * data->dt;
				// add y comp
				temp_sum_y += accel_vectors[1] * data->dt;
				// add z comp
				temp_sum_z += accel_vectors[2] * data->dt;
				
				
				// FREE UNIT VECTORS AND ACCELERATION HERE
				free(dist_vectors);
				free(accel_vectors);

			}
		}
		
		// Implement a barrier here
		pthread_barrier_wait(data->barrier);
		// Now make a call to update new positions for the element 
		update_element_positions(data->h_info->bodies[i], data->dt);
		
		pthread_barrier_wait(data->barrier);
		// Now update the velocity components
		data->h_info->bodies[i]->velocity_x = temp_sum_x;
		data->h_info->bodies[i]->velocity_y = temp_sum_y;
		data->h_info->bodies[i]->velocity_z = temp_sum_z;
	}
	return NULL;
}

void update_velocities_and_positions(struct helper* h_info, double dt){
	
	if(h_info->n_bodies < 10){
		
		// Perform the calculation with threads equal to num bodies
		struct thread_data data[10];
		pthread_t threads[10];
		
		pthread_barrier_t barrier; 
 
		pthread_barrier_init(&barrier, NULL, h_info->n_bodies);

		for(int i = 0; i < h_info->n_bodies; i++){
			data[i].start = i;
			data[i].end = i + 1;
			data[i].h_info = h_info;
			data[i].dt = dt;
			data[i].barrier = &barrier;
		
		}
		
		for(int i = 0; i < h_info->n_bodies; i++){
			pthread_create(&threads[i], NULL, thread_helper, (void*)&data[i]);
		}
		
		for(int i = 0; i < h_info->n_bodies; i++){
			pthread_join(threads[i], NULL);
		}
	
	}else{
		if(h_info->n_bodies % 10 == 0){
			// We can neatly fit the algorithm into 10 threads
			struct thread_data data[10];
			pthread_t threads[10];
			
			pthread_barrier_t barrier; 
	 
			pthread_barrier_init(&barrier, NULL, 10);
			
			// Use 10 threads and perform calculations normally
			int interval = h_info->n_bodies / 10;
			for(int i = 0; i < 10; i++){
				data[i].start = i * interval;
				data[i].end = (i * interval) + interval;
				data[i].h_info = h_info;
				data[i].dt = dt;
				data[i].id = i;
				data[i].barrier = &barrier;
			
			}
			
			for(int i = 0; i < 10; i++){
				pthread_create(&threads[i], NULL, thread_helper, (void*)&data[i]);
			}
			
			for(int i = 0; i < 10; i++){
				pthread_join(threads[i], NULL);
			}
			
			pthread_barrier_destroy(&barrier);
		}else{
			// We are going to have a leftover amount, so we will need 11 threads :(
			struct thread_data data[11];
			pthread_t threads[11];
			
			pthread_barrier_t barrier;
			
			pthread_barrier_init(&barrier, NULL, 10);
			
			// Use our 11 threads, when we are filling the 11th data struct, use % n_bodies for end
			int interval = floor(h_info->n_bodies / 10);
			
			for(int i = 0; i < 11; i++){
				if(i != 10){
					data[i].start = i * interval;
					data[i].end = (i * interval) + interval;
					data[i].h_info = h_info;
					data[i].dt = dt;
					data[i].id = i;
					data[i].barrier = &barrier;	
				}else{
					data[i].start = i * interval;
					data[i].end = (i * interval) + (h_info->n_bodies % 10);
					data[i].h_info = h_info;
					data[i].dt = dt;
					data[i].id = i;
					data[i].barrier = &barrier;
				}
			}
			
			for(int i = 0; i < 10; i++){
				pthread_create(&threads[i], NULL, thread_helper, (void*)&data[i]);
			}
			
			for(int i = 0; i < 10; i++){
				pthread_join(threads[i], NULL);
			}
			// This implementation seems very weird. Originally, I wanted to keep 10 threads and just add a few
			// more elements ( % 10 bodies) to the end of the 10th thread, however, this seemed to break the barrier??
			// this is the only way I could work around this issue... if I figure out why its happening I will fix this
			pthread_barrier_destroy(&barrier);
			pthread_barrier_init(&barrier, NULL, 1);
			pthread_create(&threads[10], NULL, thread_helper, (void*)&data[10]);
			pthread_join(threads[10], NULL);
			
		}
	}
}

double calculate_energies(struct helper* h_info, int it_n){
	// reset energy before recalculating
	double prev_energy = h_info->energy;
	
	double register temp = 0;
	for(int i = 0; i < h_info->n_bodies; i++){
	
		temp += (h_info->bodies[i]->mass * (square(h_info->bodies[i]->velocity_x)
		 		+ square(h_info->bodies[i]->velocity_y) + square(h_info->bodies[i]->velocity_z))) / 2;
		
		for(int j = i + 1; j < h_info->n_bodies; j++){
		
			if(j != i){
				temp += -(GCONST * ((h_info->bodies[i]->mass * h_info->bodies[j]->mass) / 
						calculate_distance(h_info->bodies[i], h_info->bodies[j])));
			}
			
		}
	}
	h_info->energy = temp;
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

