#ifndef NBODY_H
#define NBODY_H
#define PI (3.141592653589793)
#define SOLARMASS (4 * PI * PI)
#define NDAYS (365.25)
#define GCONST (6.67e-11)
#define BUFFER_SIZE 1024



struct body {
	double x;
	double y;
	double z;
	double velocity_x;
	double velocity_y;
	double velocity_z;
	double mass;
};

struct helper {
	int iterations;
	int flag_type; // 0 = -b, 1 = -f
	int n_bodies; // can be -1 or not assigned if flag_type == 1
	double dt;
	double energy;
	double scaling_factor;
	char* filename;
	struct body** bodies;
};

struct thread_data {
	struct helper* h_info;
	int start;
	int end;
	double dt;
	int id;
	pthread_barrier_t *barrier;

};	

double square(double a);
double* calculate_accelerations(double* dist_vectors, double magnitude, double mass);
double* calculate_dist_vectors(struct body* b1, struct body* b2, double dist_bodies);
double calculate_magnitude(struct body* b1, struct body* b2, double dist_bodies);
double calculate_distance(struct body* b1, struct body* b2);
void init_bodies_from_b(struct helper* h_info);
void load_bodies_from_file(struct helper* h_info, FILE *file);
int init_bodies_from_f(struct helper* h_info);
struct helper* input_parser(int argc, char** argv);
void update_element_positions(struct body* body, double dt);
void update_velocities_and_positions(struct helper* h_info, double dt);
void step(struct helper* h_info, int current_it, double *start_energy, double *end_energy);
double calculate_energies(struct helper* h_info, int it_n);

#endif
