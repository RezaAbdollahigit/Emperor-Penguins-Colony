#ifndef SW_CONTROLLER_H
#define SW_CONTROLLER_H

#include <systemc.h>
#include <vector>
#include "config.h"

// Forward Declaration to fix circular dependency
class HW_Accelerator; 

SC_MODULE(SW_Controller) {
    // Communication Ports to HW Accelerator 
    sc_out<bool> hw_start;
    sc_in<bool> hw_done;
    
    // Pointer to access HW internal memory buffers directly
    HW_Accelerator* hw_mod;

    struct Penguin {
        std::vector<double> position; // D-dimensional vector 
        double fitness;               // Heat intensity/Quality [cite: 889]
    };

    std::vector<Penguin> colony;
    int best_penguin_idx;
    double current_mu;
    double current_m;

    // The Software Thread 
    void run_simulation();

    SC_CTOR(SW_Controller) {
        SC_THREAD(run_simulation);
    }
};

#endif