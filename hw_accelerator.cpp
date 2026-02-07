#include "hw_accelerator.h"
#include <cmath>
#include <cstdlib>

void HW_Accelerator::do_spiral_update() {
    // Initial hardware signal state
    done_sig.write(false);

    while(true) {
        // Wait for the SW to signal the start of calculation [cite: 172]
        wait(start_sig.pos_edge_event());
        
        // Computationally expensive spiral update [cite: 873, 874]
        for (int d = 0; d < DIMENSIONS; ++d) {
            // Spiral movement from i to warmer penguin [cite: 279, 955]
            // Models logic: (1-Q)*X_i + Q*X_best [cite: 956, 960]
            double spiral_base = (1.0 - Q_ij) * penguin_i_pos[d] + (Q_ij * penguin_best_pos[d]);
            
            // Random mutation component u ~ U(-1, 1) [cite: 334, 967]
            double u = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
            
            // Final position update including mutation [cite: 967]
            updated_pos[d] = spiral_base + (m_factor * u);
        }
        
        // Signal SW that the calculation is finished [cite: 173]
        done_sig.write(true);
        wait(start_sig.neg_edge_event());
        done_sig.write(false);
    }
}