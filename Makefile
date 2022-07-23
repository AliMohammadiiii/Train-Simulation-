CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
CFLAGS = -std=c++11 -Wall -Werror -I$(INCLUDE_DIR) -g

EXECUTABLE_FILE = sim.out

OBJECTS = \
	$(BUILD_DIR)/CommandHandler.o \
	$(BUILD_DIR)/Simulator.o \
	$(BUILD_DIR)/Main.o \
	$(BUILD_DIR)/Train.o \
	$(BUILD_DIR)/Station.o \
	$(BUILD_DIR)/Passenger.o \
	$(BUILD_DIR)/Path.o \

CommandHandlerSensitivityList = \
	$(SRC_DIR)/CommandHandler.cpp \
	$(INCLUDE_DIR)/CommandHandler.hpp \
	$(INCLUDE_DIR)/Simulator.hpp \
	$(INCLUDE_DIR)/Station.hpp \
	$(INCLUDE_DIR)/Train.hpp \
	$(INCLUDE_DIR)/Passenger.hpp

SimulatorSensitivityList = \
	$(SRC_DIR)/Simulator.cpp \
	$(INCLUDE_DIR)/Simulator.hpp \
	$(INCLUDE_DIR)/Station.hpp \
	$(INCLUDE_DIR)/Path.hpp \
	$(INCLUDE_DIR)/Passenger.hpp \
	$(INCLUDE_DIR)/Train.hpp

StationSensitivityList = \
	$(SRC_DIR)/Station.cpp \
	$(INCLUDE_DIR)/Station.hpp \
	$(INCLUDE_DIR)/Passenger.hpp \
	$(INCLUDE_DIR)/Path.hpp

PassengerSensitivityList = \
	$(SRC_DIR)/Passenger.cpp\
	$(INCLUDE_DIR)/Passenger.hpp 

TrainSensitivityList = \
	$(SRC_DIR)/Train.cpp \
	$(INCLUDE_DIR)/Train.hpp \
	$(INCLUDE_DIR)/Passenger.hpp \
	$(INCLUDE_DIR)/Station.hpp

PathSensitivityList = \
	$(SRC_DIR)/Path.cpp \
	$(INCLUDE_DIR)/Path.hpp \
	$(INCLUDE_DIR)/Train.hpp \
	$(INCLUDE_DIR)/Station.hpp \
	$(INCLUDE_DIR)/Passenger.hpp

MainSensitivityList = \
	$(SRC_DIR)/Main.cpp \
	$(INCLUDE_DIR)/CommandHandler.hpp

all: $(BUILD_DIR) $(EXECUTABLE_FILE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/CommandHandler.o: $(CommandHandlerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/CommandHandler.cpp -o $(BUILD_DIR)/CommandHandler.o

$(BUILD_DIR)/Simulator.o: $(SimulatorSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Simulator.cpp -o $(BUILD_DIR)/Simulator.o

$(BUILD_DIR)/Station.o: $(StationSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Station.cpp -o $(BUILD_DIR)/Station.o

$(BUILD_DIR)/Passenger.o: $(PassengerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Passenger.cpp -o $(BUILD_DIR)/Passenger.o

$(BUILD_DIR)/Train.o: $(TrainSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Train.cpp -o $(BUILD_DIR)/Train.o

$(BUILD_DIR)/Path.o: $(PathSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Path.cpp -o $(BUILD_DIR)/Path.o

$(BUILD_DIR)/Main.o: $(MainSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Main.cpp -o $(BUILD_DIR)/Main.o

$(EXECUTABLE_FILE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE_FILE)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out