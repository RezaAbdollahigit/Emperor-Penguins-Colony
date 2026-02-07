#include "sw_controller.h"
#include "benchmarks.h"
#include "hw_accelerator.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

void SW_Controller::run_simulation() {
    // 1. Initialize Simulation Parameters 
    srand(time(NULL)); 
    current_mu = MU_START; // [cite: 946]
    current_m = M_START;   // [cite: 967]
    colony.clear();

    std::cout << "SW: Initializing population of " << POPULATION_SIZE << " penguins..." << std::endl;

    for (int i = 0; i < POPULATION_SIZE; ++i) { // [cite: 400]
        Penguin p;
        p.position.resize(DIMENSIONS);
        for (int d = 0; d < DIMENSIONS; ++d) {
            // Random initialization within range [-10, 10] [cite: 906, 909]
            p.position[d] = ((double)rand() / RAND_MAX) * 20.0 - 10.0;
        }
        // Evaluate initial fitness using chosen benchmark [cite: 912, 914]
        p.fitness = Benchmarks::sphere(p.position);
        colony.push_back(p);
    }

    // 2. Main Optimization Loop [cite: 922]
    for (int t = 0; t < MAX_ITERATIONS; ++t) {
        // Identify the Effective (Best) Penguin [cite: 915, 918]
        best_penguin_idx = 0;
        for (int i = 1; i < POPULATION_SIZE; ++i) {
            if (colony[i].fitness < colony[best_penguin_idx].fitness) {
                best_penguin_idx = i;
            }
        }

        // 3. Update Population via Hardware Acceleration 
        for (int i = 0; i < POPULATION_SIZE; ++i) {
            if (i == best_penguin_idx) continue;

            // Calculate Euclidean distance and Attractiveness Q [cite: 944, 952]
            double dist_sq = 0;
            for (int d = 0; d < DIMENSIONS; ++d) {
                double diff = colony[best_penguin_idx].position[d] - colony[i].position[d];
                dist_sq += diff * diff;
            }
            double Q = exp(-current_mu * sqrt(dist_sq)); // [cite: 944]

            // DATA TRANSFER: Write to HW Memory Buffers 
            hw_mod->Q_ij = Q;
            hw_mod->m_factor = current_m;
            for (int d = 0; d < DIMENSIONS; ++d) {
                hw_mod->penguin_i_pos[d] = colony[i].position[d];
                hw_mod->penguin_best_pos[d] = colony[best_penguin_idx].position[d];
            }

            // TRIGGER HARDWARE [cite: 934]
            hw_start.write(true);
            wait(hw_done.posedge_event()); // Wait for HW result [cite: 172]
            hw_start.write(false);
            wait(SC_ZERO_TIME); // Synchronization delta cycle

            // DATA RETRIEVAL: Read results from Hardware 
            for (int d = 0; d < DIMENSIONS; ++d) {
                colony[i].position[d] = hw_mod->updated_pos[d];
            }

            // Re-evaluate fitness [cite: 935]
            colony[i].fitness = Benchmarks::sphere(colony[i].position);
        }

        // 4. Update Dynamic Parameters (Damping) [cite: 895, 896]
        current_mu *= 0.99; // [cite: 945]
        current_m *= 0.99;  // [cite: 967]

        if (t % 10 == 0) {
            std::cout << "Iteration " << t << " | Best Fitness: " << colony[best_penguin_idx].fitness << std::endl;
        }
    }

    std::cout << "Final Best Fitness: " << colony[best_penguin_idx].fitness << std::endl;
    sc_stop();
}