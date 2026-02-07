#include "hw_accelerator.h"
#include <cmath>
#include <cstdlib>

void HW_Accelerator::do_spiral_update() {
    // Initial state
    done_sig.write(false);

    // This method is sensitive to start_sig.pos()
    if (start_sig.read() == true) {
        for (int d = 0; d < DIMENSIONS; ++d) {
            // Logarithmic spiral movement logic [cite: 141, 893]
            // Represents movement from penguin i toward the warmer penguin best [cite: 279, 280]
            double spiral_influence = (1.0 - Q_ij) * penguin_i_pos[d] + (Q_ij * penguin_best_pos[d]);
            
            // Generate random mutation component u ~ U(-1, 1) [cite: 967]
            double u = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
            
            // Final position update with mutation factor [cite: 330, 967]
            updated_pos[d] = spiral_influence + (m_factor * u);
        }
        
        // Signal completion to the Software Controller [cite: 876]
        done_sig.write(true);
    }
}