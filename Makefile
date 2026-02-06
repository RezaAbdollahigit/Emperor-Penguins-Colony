SYSTEMC_HOME = /usr/local/systemc-2.3.3
LIBS = -lsystemc -lm
LIB_DIR = -L$(SYSTEMC_HOME)/lib-linux64
INC_DIR = -I$(SYSTEMC_HOME)/include

APP = epc_simulation

all:
	g++ -o $(APP) main.cpp sw_controller.cpp hw_accelerator.cpp $(INC_DIR) $(LIB_DIR) $(LIBS)

clean:
	rm -f $(APP)