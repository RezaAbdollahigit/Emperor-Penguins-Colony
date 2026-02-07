SYSTEMC_HOME = /usr/local/systemc-2.3.1/

LIBS = -lsystemc -lm
LIB_DIR = -L$(SYSTEMC_HOME)/lib-linux64
INC_DIR = -I$(SYSTEMC_HOME)/include

# Project name
APP = epc_sim

all:
	g++ $(INC_DIR) $(LIB_DIR) -o $(APP) main.cpp sw_controller.cpp hw_accelerator.cpp $(LIBS) -std=c++98

clean:
	rm -f $(APP)