#ifndef HW_ACCELERATOR_H
#define HW_ACCELERATOR_H

#include <systemc.h>
#include "config.h"

SC_MODULE(HW_Accelerator) {
    // Control Signals for HW/SW synchronization 
    sc_in<bool> start_sig;
    sc_out<bool> done_sig;

    // Hardware "Memory" Buffers for D dimensions 
    // These store the coordinates for the current and best penguins 
    double penguin_i_pos[DIMENSIONS]; 
    double penguin_best_pos[DIMENSIONS]; 
    double updated_pos[DIMENSIONS];    // Stores the resulting position 'k' 
    
    // Attractiveness and mutation factors received from SW 
    double Q_ij; 
    double m_factor; 

    // The Hardware Logic Process 
    void do_spiral_update();

    SC_CTOR(HW_Accelerator) {
        // Changed to SC_THREAD to support wait() for synchronization 
        SC_THREAD(do_spiral_update);
        // Sensitivity list to monitor the software trigger
        sensitive << start_sig; 
    }
};

#endif