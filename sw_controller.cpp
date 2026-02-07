#include "sw_controller.h"
#include "benchmarks.h"
#include "hw_accelerator.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

void SW_Controller::run_simulation() {
    // 1. Initialize Population [cite: 161, 891]
    current_mu = MU_START;
    current_m = M_START;
    colony.clear();

    for (int i = 0; i < POPULATION_SIZE; ++i) {
        Penguin p;
        p.position.resize(DIMENSIONS);
        for (int d = 0; d < DIMENSIONS; ++d) {
            // Random initialization within range [-10, 10] [cite: 906, 909]
            p.position[d] = ((double)rand() / RAND_MAX) * 20.0 - 10.0;
        }
        p.fitness = Benchmarks::sphere(p.position);
        colony.push_back(p);
    }

    // 2. Main Optimization Loop [cite: 162, 922]
    for (int t = 0; t < MAX_ITERATIONS; ++t) {
        // Find the "Effective Penguin" (Best Solution) [cite: 890, 918]
        best_penguin_idx = 0;
        for (int i = 1; i < POPULATION_SIZE; ++i) {
            if (colony[i].fitness < colony[best_penguin_idx].fitness) {
                best_penguin_idx = i;
            }
        }

        // 3. Update each penguin using the HW Accelerator [cite: 874, 934]
        for (int i = 0; i < POPULATION_SIZE; ++i) {
            if (i == best_penguin_idx) continue;

            // Calculate Attraction (Q) based on Euclidean Distance [cite: 944, 952]
            double dist_sq = 0;
            for (int d = 0; d < DIMENSIONS; ++d) {
                double diff = colony[best_penguin_idx].position[d] - colony[i].position[d];
                dist_sq += diff * diff;
            }
            double Q = exp(-current_mu * sqrt(dist_sq));

            // Transfer data to HW module buffers (Conceptual HW/SW Data Exchange) [cite: 876]
            // Note: In real SystemC modeling, you'd use a pointer or bus to hw_mod
            // For this simulation, we simulate the data being ready for HW
            
            // Start the hardware process
            hw_start.write(true);
            wait(hw_done.posedge_event()); // Wait for HW done_sig [cite: 876]
            hw_start.write(false);

            // Re-evaluate fitness after HW update [cite: 147, 935]
            colony[i].fitness = Benchmarks::sphere(colony[i].position);
        }

        // 4. Parameter Damping [cite: 148, 895, 945]
        current_mu *= 0.99;
        current_m *= 0.99;

        if (t % 10 == 0) {
            std::cout << "Iteration " << t << " | Best Fitness: " << colony[best_penguin_idx].fitness << std::endl;
        }
    }

    std::cout << "Final Best Fitness: " << colony[best_penguin_idx].fitness << std::endl;
    sc_stop();
}