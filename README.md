# Emperor Penguins Colony (EPC) Optimization: A HW/SW Co-Design Approach

## 🐧 Project Overview

This project implements a hardware-accelerated version of the **Emperor Penguins Colony (EPC)** metaheuristic optimization algorithm. The system is designed using a **Hardware/Software Co-Design** methodology, partitioning the high-computational spiral movement logic into a dedicated hardware module while maintaining high-level colony management in software.

### Key Features

* **Biological Logic**: Models huddling behavior and heat-sharing among penguins to find global optima.
* **HW/SW Partitioning**: Mathematical bottlenecks (Logarithmic Spiral updates) are moved to a simulated Hardware Accelerator.
* **Scalability**: Implementation is independent of parameters (), supporting high-dimensional search spaces.
* **Benchmarking**: Verified against the **Sphere** and **Rosenbrock** mathematical functions.

---

## 👥 Authors

* **Hamidreza Khodabandehlou** - 40117773
* **Reza Abdollahi** - 40120783

---

## 🛠 Prerequisites

* **SystemC 2.3.1** (Installed on Ubuntu/Linux environment)
* **G++ Compiler** supporting the `C++98` standard
* **Python 3.x** (for high-level analysis and plotting)

---

## 🚀 Running the SystemC Simulation

### Method 1: Using the Makefile (Recommended)

This is the fastest way to build the project if your environment variables are already set.

```bash
make
./epc_sim

```

### Method 2: Manual Compilation

If you need to define the paths manually, follow these steps:

1. **Set Environment Variable**:
```bash
export SYSTEMC_HOME=/usr/local/systemc-2.3.1/

```


2. **Compile**:
```bash
g++ -I$SYSTEMC_HOME/include -L$SYSTEMC_HOME/lib-linux64 -o epc_sim main.cpp sw_controller.cpp hw_accelerator.cpp -lsystemc -lm -std=c++98

```


3. **Run**:
```bash
./epc_sim

```



---

## 📊 Software Reference & Analysis

A standalone Python script is provided for high-level validation and convergence analysis.

```bash
python3 epc_python_analysis.py

```

This generates an `epc_convergence_plot.png` comparing the algorithm's performance on the **Sphere** and **Rosenbrock** landscapes.

---

## 🏗 System Architecture

* **`SW_Controller`**: Manages the population, identifies the "Effective" penguin, and coordinates data transfer.
* **`HW_Accelerator`**: A low-level module that performs the D-dimensional spiral updates and random mutations.
* **`Benchmarks`**: Contains the mathematical definitions for the optimization targets.

Would you like me to help you generate a ZIP file command to package all these files for your final submission?
