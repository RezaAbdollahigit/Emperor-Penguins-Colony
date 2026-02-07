#include "hw_accelerator.h"
#include <cmath>
#include <cstdlib>

void HW_Accelerator::do_spiral_update() {
    // Initial hardware signal state
    done_sig.write(false);

    while(true) {
        // Wait for the SW to signal the start of calculation (Rising Edge) [cite: 172, 876]
        wait(start_sig.posedge_event());
        
        // Computationally expensive spiral update loop for D dimensions 
        for (int d = 0; d < DIMENSIONS; ++d) {
            // Spiral movement from current position i toward warmer penguin j [cite: 279, 955]
            // Mathematical model: (1-Q)*X_i + Q*X_best [cite: 956, 960]
            double spiral_base = (1.0 - Q_ij) * penguin_i_pos[d] + (Q_ij * penguin_best_pos[d]);
            
            // Random mutation component u ~ U(-1, 1) to prevent local optima [cite: 334, 967]
            double u = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
            
            // Final position update including the mutation factor [cite: 967]
            updated_pos[d] = spiral_base + (m_factor * u);
        }
        
        // Signal SW that the hardware calculation is finished [cite: 173, 876]
        done_sig.write(true);
        
        // Wait for SW to acknowledge by lowering the start signal (Falling Edge)
        wait(start_sig.negedge_event());
        
        // Reset the done signal for the next request
        done_sig.write(false);
    }
}