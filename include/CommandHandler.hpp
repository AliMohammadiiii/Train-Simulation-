#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <vector>
#include <string>

class Simulator;
class Station;
class Train;
class Passenger;

class CommandHandler {

public:
    CommandHandler();
    void run();

private:
    std::vector<std::string> tokenizeInput(std::string input);
    Train* createTrain(std::string input);
    Station* createStation(std::string input);
    Passenger* createPassenger(std::string input);
    size_t getTimeSteps(std::string input);
    int getObjectId(std::string input);

    Simulator* simulator;
};

#endif