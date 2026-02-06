#include "hw_accelerator.h"
#include <cmath>

void HW_Accelerator::do_spiral_update() {
    while(true) {
        // Wait for the SW to signal the start of a calculation
        wait(start_sig.pos_edge_event());
        done_sig.write(false);

        for (int d = 0; d < DIMENSIONS; ++d) {
            // Simplified Logarithmic Spiral Update (Conceptual Hardware Logic)
            // In a real co-design, this math is unrolled for parallel execution
            double diff = penguin_best_pos[d] - penguin_i_pos[d];
            
            // Calculate spiral influence based on Q_ij (Attractiveness)
            // Following the logic: x_new = (1-Q) * x_i + Q * x_best + mutation
            double spiral_move = (1.0 - Q_ij) * penguin_i_pos[d] + (Q_ij * penguin_best_pos[d]);
            
            // Apply Mutation (Random deviation to prevent local optima) [cite: 159, 894, 967]
            double rand_val = ((double)rand() / (RAND_MAX)) * 2.0 - 1.0; // U(-1, 1)
            updated_pos[d] = spiral_move + (m_factor * rand_val);
        }

        // Signal completion back to the SW Controller
        done_sig.write(true);
    }
}