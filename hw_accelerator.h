#ifndef HW_ACCELERATOR_H
#define HW_ACCELERATOR_H

#include <systemc.h>
#include "config.h"

SC_MODULE(HW_Accelerator) {
    // Control Signals [cite: 876]
    sc_in<bool> start_sig;
    sc_out<bool> done_sig;

    // Hardware "Memory" Buffers for D dimensions [cite: 902]
    double penguin_i_pos[DIMENSIONS]; // Position of penguin needing heat [cite: 279]
    double penguin_best_pos[DIMENSIONS]; // Position of warmer penguin [cite: 279]
    double updated_pos[DIMENSIONS];    // The result (Position k) [cite: 303]
    
    // Attractiveness input from SW [cite: 301]
    double Q_ij; 
    double m_factor; // Current mutation coefficient [cite: 967]

    // The Hardware Logic Process 
    void do_spiral_update();

    SC_CTOR(HW_Accelerator) {
        SC_METHOD(do_spiral_update);
        sensitive << start_sig.pos(); // Trigger on SW command
    }
};

#endif