#ifndef CONFIG_H
#define CONFIG_H

// Simulation Scaling
const int POPULATION_SIZE = 20;  // Number of penguins (N) 
const int DIMENSIONS = 10;       // Number of decision variables (D) 
const int MAX_ITERATIONS = 100;  // Termination criteria 

// EPC Algorithm Parameters
const double SPIRAL_A = 1.0;     // Logarithmic spiral parameter 'a' 
const double SPIRAL_B = 0.5;     // Logarithmic spiral parameter 'b' 
const double MU_START = 0.05;    // Initial heat attenuation (mu) 
const double M_START = 0.5;      // Initial mutation/random factor (m) 

#endif