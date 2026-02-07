#ifndef HW_ACCELERATOR_H
#define HW_ACCELERATOR_H

#include <systemc.h>
#include "config.h"

SC_MODULE(HW_Accelerator) {
    // Control Signals for HW/SW synchronization [cite: 876]
    sc_in<bool> start_sig;
    sc_out<bool> done_sig;

    // Hardware "Memory" Buffers for D dimensions [cite: 902]
    // These store the coordinates for the current and best penguins [cite: 279]
    double penguin_i_pos[DIMENSIONS]; 
    double penguin_best_pos[DIMENSIONS]; 
    double updated_pos[DIMENSIONS];    // Stores the resulting position 'k' [cite: 303]
    
    // Attractiveness and mutation factors received from SW [cite: 301, 967]
    double Q_ij; 
    double m_factor; 

    // The Hardware Logic Process 
    void do_spiral_update();

    SC_CTOR(HW_Accelerator) {
        // Changed to SC_THREAD to support wait() for synchronization [cite: 876]
        SC_THREAD(do_spiral_update);
        // Sensitivity list to monitor the software trigger
        sensitive << start_sig; 
    }
};

#endif