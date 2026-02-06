#include "sw_controller.h"
#include "benchmarks.h"
#include <iostream>
#include <algorithm>

void SW_Controller::run_simulation() {
    // 1. Initialization [cite: 161, 905]
    current_mu = MU_START;
    current_m = M_START;
    colony.resize(POPULATION_SIZE);

    for (auto& p : colony) {
        p.position.resize(DIMENSIONS);
        for (int d = 0; d < DIMENSIONS; ++d) {
            p.position[d] = ((double)rand() / RAND_MAX) * 20.0 - 10.0; // Range [-10, 10] [cite: 980]
        }
        p.fitness = Benchmarks::sphere(p.position);
    }

    // 2. Main Iteration Loop [cite: 162, 922]
    for (int t = 0; t < MAX_ITERATIONS; ++t) {
        // Find Effective (Best) Penguin [cite: 175, 915, 933]
        best_penguin_idx = 0;
        for (int i = 1; i < POPULATION_SIZE; ++i) {
            if (colony[i].fitness < colony[best_penguin_idx].fitness) {
                best_penguin_idx = i;
            }
        }

        // 3. Update Population using HW Accelerator [cite: 172, 874, 934]
        for (int i = 0; i < POPULATION_SIZE; ++i) {
            if (i == best_penguin_idx) continue;

            // Calculate Attractiveness Q based on distance [cite: 170, 944, 947]
            double dist_sq = 0;
            for (int d = 0; d < DIMENSIONS; ++d) {
                double diff = colony[best_penguin_idx].position[d] - colony[i].position[d];
                dist_sq += diff * diff;
            }
            double Q = exp(-current_mu * sqrt(dist_sq));

            // Setup HW Registers/Buffers
            // (In SystemC simulation, we access the HW module's internal variables)
            // ... (Mapping data to HW_Accelerator instance) ...

            // Trigger HW [cite: 876]
            hw_start.write(true);
            wait(hw_done.posedge_event());
            hw_start.write(false);

            // Retrieve updated position from HW and update fitness [cite: 173, 935]
            // ... (Mapping results back to colony[i]) ...
            colony[i].fitness = Benchmarks::sphere(colony[i].position);
        }

        // 4. Update Parameters (Damping) [cite: 176, 177, 895, 945]
        current_mu *= 0.99;
        current_m *= 0.99;

        std::cout << "Iteration " << t << " | Best Fitness: " << colony[best_penguin_idx].fitness << std::endl;
    }

    sc_stop();
}