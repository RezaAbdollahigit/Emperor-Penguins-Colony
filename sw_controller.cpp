#include "sw_controller.h"
#include "benchmarks.h"
#include "hw_accelerator.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

void SW_Controller::reset_population() {
    colony.clear();
    current_mu = MU_START; [cite: 946]
    current_m = M_START;   [cite: 967]
    for (int i = 0; i < POPULATION_SIZE; ++i) { [cite: 400]
        Penguin p;
        p.position.resize(DIMENSIONS);
        for (int d = 0; d < DIMENSIONS; ++d) {
            p.position[d] = ((double)rand() / RAND_MAX) * 20.0 - 10.0; [cite: 906, 909]
        }
        colony.push_back(p);
    }
}

void SW_Controller::run_simulation() {
    srand(time(NULL));

    // Array of function names for display
    const char* func_names[] = {"Sphere", "Rosenbrock"};

    for (int f = 0; f < 2; ++f) {
        std::cout << "\n--- Starting Optimization for: " << func_names[f] << " ---" << std::endl;
        reset_population();

        for (int t = 0; t < MAX_ITERATIONS; ++t) {
            // Initial fitness evaluation for the current benchmark
            for (int i = 0; i < POPULATION_SIZE; ++i) {
                if (f == 0) colony[i].fitness = Benchmarks::sphere(colony[i].position); [cite: 973]
                else colony[i].fitness = Benchmarks::rosenbrock(colony[i].position); [cite: 975]
            }

            // Identify Best
            best_penguin_idx = 0;
            for (int i = 1; i < POPULATION_SIZE; ++i) {
                if (colony[i].fitness < colony[best_penguin_idx].fitness) {
                    best_penguin_idx = i;
                }
            }

            // HW-Accelerated Update
            for (int i = 0; i < POPULATION_SIZE; ++i) {
                if (i == best_penguin_idx) continue;

                double dist_sq = 0;
                for (int d = 0; d < DIMENSIONS; ++d) {
                    double diff = colony[best_penguin_idx].position[d] - colony[i].position[d];
                    dist_sq += diff * diff; [cite: 952]
                }
                double Q = exp(-current_mu * sqrt(dist_sq)); [cite: 944]

                // Transfer to HW Buffers
                hw_mod->Q_ij = Q; [cite: 301]
                hw_mod->m_factor = current_m; [cite: 967]
                for (int d = 0; d < DIMENSIONS; ++d) {
                    hw_mod->penguin_i_pos[d] = colony[i].position[d];
                    hw_mod->penguin_best_pos[d] = colony[best_penguin_idx].position[d];
                }

                hw_start.write(true);
                wait(hw_done.posedge_event());
                hw_start.write(false);
                wait(SC_ZERO_TIME);

                for (int d = 0; d < DIMENSIONS; ++d) {
                    colony[i].position[d] = hw_mod->updated_pos[d]; [cite: 172]
                }
            }

            current_mu *= 0.99; [cite: 945]
            current_m *= 0.99;  [cite: 967]

            if (t % 20 == 0) {
                std::cout << func_names[f] << " Iteration " << t << " | Best Fitness: " << colony[best_penguin_idx].fitness << std::endl;
            }
        }
        std::cout << "Final Best Fitness (" << func_names[f] << "): " << colony[best_penguin_idx].fitness << std::endl;
    }

    sc_stop();
}