#include <systemc.h>
#include "sw_controller.h"
#include "hw_accelerator.h"

int sc_main(int argc, char* argv[]) {
    // Signals for communication [cite: 876]
    sc_signal<bool> start_sig;
    sc_signal<bool> done_sig;

    // Instantiate Modules
    SW_Controller sw_mod("Software_Controller");
    HW_Accelerator hw_mod("Hardware_Accelerator");

    // Connect Ports
    sw_mod.hw_start(start_sig);
    sw_mod.hw_done(done_sig);
    hw_mod.start_sig(start_sig);
    hw_mod.done_sig(done_sig);

    // Run Simulation
    std::cout << "Starting Emperor Penguins Colony Simulation..." << std::endl;
    sc_start();

    return 0;
}