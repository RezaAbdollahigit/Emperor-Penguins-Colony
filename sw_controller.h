#ifndef SW_CONTROLLER_H
#define SW_CONTROLLER_H

#include <systemc.h>
#include <vector>
#include "config.h"

class HW_Accelerator; 

SC_MODULE(SW_Controller) {
    sc_out<bool> hw_start;
    sc_in<bool> hw_done;
    HW_Accelerator* hw_mod;

    struct Penguin {
        std::vector<double> position;
        double fitness;
    };

    std::vector<Penguin> colony;
    int best_penguin_idx;
    double current_mu;
    double current_m;

    void run_simulation();
    void reset_population(); // New helper function

    SC_CTOR(SW_Controller) {
        SC_THREAD(run_simulation);
    }
};

#endif