#include <systemc.h>
#include "sw_controller.h"
#include "hw_accelerator.h"
#include <iostream>

int sc_main(int argc, char* argv[]) {
    // 1. Define Communication Signals (The "Bus") [cite: 874, 876]
    sc_signal<bool> sig_start;
    sc_signal<bool> sig_done;

    // 2. Instantiate the HW/SW Modules [cite: 841, 876]
    SW_Controller software_unit("Software_Unit");
    HW_Accelerator hardware_accelerator("Hardware_Accelerator");

    // 3. Connect Ports to Signals 
    software_unit.hw_start(sig_start);
    software_unit.hw_done(sig_done);

    hardware_accelerator.start_sig(sig_start);
    hardware_accelerator.done_sig(sig_done);

    // 4. Start Simulation [cite: 871]
    std::cout << "--- EPC Optimization Simulation Started ---" << std::endl;
    std::cout << "Dimensions: " << DIMENSIONS << " | Population: " << POPULATION_SIZE << std::endl;
    
    sc_start(); // Triggers the SC_THREAD in sw_controller [cite: 871]

    std::cout << "--- Simulation Finished ---" << std::endl;

    return 0;
}