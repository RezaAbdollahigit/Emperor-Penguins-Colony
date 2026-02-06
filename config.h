#ifndef CONFIG_H
#define CONFIG_H

// Simulation Scaling
const int POPULATION_SIZE = 20;  // Number of penguins (N) [cite: 400]
const int DIMENSIONS = 10;       // Number of decision variables (D) [cite: 401]
const int MAX_ITERATIONS = 100;  // Termination criteria [cite: 400]

// EPC Algorithm Parameters
const double SPIRAL_A = 1.0;     // Logarithmic spiral parameter 'a' [cite: 951]
const double SPIRAL_B = 0.5;     // Logarithmic spiral parameter 'b' [cite: 951]
const double MU_START = 0.05;    // Initial heat attenuation (mu) [cite: 946]
const double M_START = 0.5;      // Initial mutation/random factor (m) [cite: 967]

#endif