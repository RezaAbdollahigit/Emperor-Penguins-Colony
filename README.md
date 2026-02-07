# Emperor-Penguins-Colony


type:
make
./epc_sim


------------- OR --------------

1. Set Environment Variable: Run this once in your terminal: 
export SYSTEMC_HOME=/usr/local/systemc-2.3.1/


2. Compile: 
g++ -I$SYSTEMC_HOME/include -L$SYSTEMC_HOME/lib-linux64 -o epc_sim main.cpp sw_controller.cpp hw_accelerator.cpp -lsystemc -lm -std=c++98


3. Run: 
./epc_sim
