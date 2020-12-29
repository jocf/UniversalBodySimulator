#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "./lib/nbody.h"

#define VIEW_WIDTH (320)
#define VIEW_HEIGHT (240)

// METHOD DEFINITIONS


//THIS IS A SDL2 TEMPLATE

/**
 * Updates the x based on where it is, will invert the  
 * velocity when it reaches out of bounds.
 */
void update_x(int* cx, int* velocity, int width) {
	if(cx && velocity) {
		if(*cx <= 0) {
			*cx = 0;
			*velocity = 1;
		} else if(*cx >= width) {
			*cx = width;
			*velocity = -1;
		}
		*cx = *cx + *velocity;
	}
}

struct helper* input_parser_gui(int argc, char** argv, int *window_width, int *window_height){
	if(argc != 8){
		printf("Invalid number of arguments specified. You provided %d argument(s). 8 were expected\n",argc);
		return NULL;
	}
	
	if(atoi(argv[1]) == 0){
		printf("Invalid resolution width specified\n");
		return NULL;
	}
	
	if(atoi(argv[2]) == 0){
		printf("Invalid resolution height specified\n");
		return NULL;	
	}
	
	if(atoi(argv[3]) == 0){
		printf("The iterations value provided was either invalid or equal to zero.\n");
		return NULL;
	}
	
	if(atof(argv[4]) == 0.0){
		printf("The dt value you provided was either invalid or equal to zero.\n");
		return NULL;
	}
	
	struct helper* h_info = malloc(sizeof(struct helper));
	
	*window_width = atoi(argv[1]);
	*window_height = atoi(argv[2]);
	h_info->iterations = atoi(argv[3]);
	h_info->dt = atof(argv[4]);
	
	if(strcmp(argv[5],"-b") == 0){
		// the flag was -b
		if(atoi(argv[6]) == 0){
			printf("The number of bodies you specified was either invalid or equal to zero.\n");
			return NULL;
		}
		h_info->flag_type = 0;
		h_info->n_bodies = atoi(argv[6]);
		
	}
	else if(strcmp(argv[5],"-f") == 0){
		// the flag was -f
		// Further work will need to be done to calculate the number of bodies
		
		h_info->filename = argv[6];
		h_info->flag_type = 1;
		
	}
	else{
		printf("The flag you provided was invalid! %s when it should have been either -b or -f.\n",argv[5]);
		return NULL;
	}
	
	if(atof(argv[7]) == 0.0){
		printf("The scaling factor you provided was either incorrect or equal to zero.\n");
		return NULL;
	}
	
	h_info->scaling_factor = atof(argv[7]);
	
	
	printf("Startup options selected were: \n");
	printf("Res_width: %d\n",*window_width);
	printf("Res_height: %d\n",*window_height);
	printf("Iterations: %d\n",h_info->iterations);
	printf("Flag type: %d\n",h_info->flag_type);
	printf("N_bodies: %d\n",h_info->n_bodies);
	printf("Scaling factor: %f\n",h_info->scaling_factor);
	
	return h_info;
}



int main(int argc, char** argv) {
	
	int *window_width = malloc(sizeof(int));
	int *window_height = malloc(sizeof(int));
	
	struct helper* h_info = input_parser_gui(argc, argv, window_width, window_height);
	
	if(h_info == NULL){
		return -1;
	}
	
	if(h_info->flag_type == 0){
		// b mode
		init_bodies_from_b(h_info);
	}
	else{
		
		// f mode
		init_bodies_from_f(h_info);
		//exit(0);
	}
	
	if(*window_width <= 0){
		*window_width = VIEW_WIDTH;
	}
	
	if(*window_height <= 0){
		*window_height = VIEW_HEIGHT;
	}
	
	// Now we are initialized. We can start the actual program
	
	//Your SDL variables and variables for circle data and finished state
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Event event;
	int finished = 0;
	//int circle_x = 100;
	//int vel = 1;	
	
	
	//Initialises SDL Video Acceleration
	//Check if return value is < 0
	SDL_Init(SDL_INIT_VIDEO);
	
	/**
	 * Creates a window to display
	 * Allows you to specify the window x,y position
	 * Allows you to specify the width and height of the window
	 * Option for flags for the window and potentially the different instances
	 * you may want to use with it. SHOWN, makes the window visible
	 * Should check if it returns NULL
	 */
	 
	printf("Window width: %d\n",*window_width);
	
	printf("Window height: %d\n",*window_height);
	
	window = SDL_CreateWindow("nbody simulation",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		*window_width, *window_height, SDL_WINDOW_SHOWN);
	
	/**
	 * Create Renderer retrieves the 2D rendering context of the window
	 * You will need to use this to use with SDL2_gfx library 
	 * This will give you access to the underlying rederer of the window
	 * Should check if it returns NULL
	 */
	renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED 
		| SDL_RENDERER_PRESENTVSYNC);
	
	/**
	 * Render loop of your application
	 * You will perform your drawing in this loop here
	 */
	 
	int counter = 0;
	
	// calculate the mass division factor
	
	double max_value = 0.0;
	
	for(int i = 0; i < h_info->n_bodies; i++){
		if(h_info->bodies[i]->mass > max_value){
			max_value = h_info->bodies[i]->mass;
		}
	}
	
	double division_factor = max_value/10;
	
	double *start_energy = malloc(sizeof(double));
	double *end_energy = malloc(sizeof(double));
	
	while(!finished && (counter < h_info->iterations)) {
		//Sets the background colour 
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
		
		//Clears target with a specific drawing colour (prev function defines colour)
		SDL_RenderClear(renderer);
		
		for(int i = 0; i < h_info->n_bodies; i++){
			//Draws a circle using a specific colour
			//Pixel is RGBA (0x(RED)(GREEN)(BLUE)(ALPHA), each 0-255
			
			double x_coord = (h_info->scaling_factor * (h_info->bodies[i]->x)) + *window_width/2;
			double y_coord = -(h_info->scaling_factor * (h_info->bodies[i]->y)) + *window_height/2;
			double display_mass = (h_info->bodies[i]->mass)/division_factor;
			if(display_mass < 1.0){
				display_mass = 1.0;
			}
			if(display_mass > 10.0){
				display_mass = 10.0;
			}
			//printf("Body %d: Filling for x: %f y: %f mass: %f \n",i,x_coord, y_coord, display_mass);
			filledCircleColor(renderer, x_coord, y_coord, display_mass, 0xFF0000FF);
		}
		
		
		
		//Updates the screen with newly renderered image
		SDL_RenderPresent(renderer);
		
		step(h_info, counter, start_energy, end_energy);
		
		//Updates the x coordinate of circle
		//update_x(&circle_x, &vel, VIEW_WIDTH);

		//Retrieves the events captured from SDL (just watching for windows close)
		if(SDL_PollEvent(&event)) {
			finished = (event.type == SDL_QUIT);
		}
		counter++;
	}
	
	
	
	printf("Total change in system: %e\n", *start_energy - h_info->energy);
	
	free(start_energy);
	free(end_energy);
	free(window_width);
	free(window_height);
	
	for(int i = 0; i < h_info->n_bodies; i++){
		free(h_info->bodies[i]);
	}
	free(h_info->bodies);
	free(h_info);
	//Clean up functions
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();	

	return 0;	
}
