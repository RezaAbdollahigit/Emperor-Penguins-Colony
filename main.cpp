#include <systemc.h>
#include "sw_controller.h"
#include "hw_accelerator.h"
#include <iostream>

int sc_main(int argc, char* argv[]) {
    sc_signal<bool> sig_start;
    sc_signal<bool> sig_done;

    SW_Controller software_unit("Software_Unit");
    HW_Accelerator hardware_accelerator("Hardware_Accelerator");

    // Connect the Software to the Hardware instance
    // This allows the SW to access hw_mod.penguin_i_pos, etc.
    software_unit.hw_mod = &hardware_accelerator;

    software_unit.hw_start(sig_start);
    software_unit.hw_done(sig_done);
    hardware_accelerator.start_sig(sig_start);
    hardware_accelerator.done_sig(sig_done);

    std::cout << "--- EPC Optimization Simulation Started ---" << std::endl;
    sc_start();
    std::cout << "--- Simulation Finished ---" << std::endl;

    return 0;
}