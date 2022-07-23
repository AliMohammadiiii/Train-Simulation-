#include "CommandHandler.hpp"

#include <iostream>
#include <iterator>
#include <sstream>

#include "Simulator.hpp"
#include "Station.hpp"
#include "Train.hpp"
#include "Passenger.hpp"

using namespace std;

constexpr char ADD_STATION[] = "add_station";
constexpr char ADD_TRAIN[] = "add_train";
constexpr char ADD_PASSENGER[] = "add_passenger";
constexpr char ADD_LINE[] = "add_line";
constexpr char ADVANCE_TIME[] = "advance_time";
constexpr char FINISH[] = "finish";
constexpr char SHOW_TRAIN_INFO[] = "show_train_info";
constexpr char SHOW_PASSENGER_INFO[] = "show_passenger_info";
constexpr char COMMAND_SUCCESS[] = "OK";


CommandHandler::CommandHandler()
: simulator(new Simulator())
{
}

void CommandHandler::run() {
    const int COMMAND_TYPE_INDEX = 0;
    string input;
    while (getline(cin, input)) {
        const string commandType = tokenizeInput(input)[COMMAND_TYPE_INDEX];

        if (commandType == ADD_STATION) {
            simulator->addStation(createStation(input));
            cout << COMMAND_SUCCESS << endl;
        }
        else if (commandType == ADD_TRAIN) {
            simulator->addTrain(createTrain(input));
            cout << COMMAND_SUCCESS << endl;
        }
        else if (commandType == ADD_PASSENGER) {
            simulator->addPassenger(createPassenger(input));
            cout << COMMAND_SUCCESS << endl;
        }
        else if (commandType == ADVANCE_TIME)  {
            simulator->advanceTime(getTimeSteps(input));
            cout << COMMAND_SUCCESS << endl;
        }
        else if (commandType == FINISH) {
            simulator->finish();
            cout << COMMAND_SUCCESS << endl;
        }
        else if (commandType == SHOW_TRAIN_INFO)
            cout << simulator->getTrainInfo(getObjectId(input)) << endl;
        else if (commandType == SHOW_PASSENGER_INFO)
            cout << simulator->getPassengerInfo(getObjectId(input)) << endl;
    }
}

vector<string> CommandHandler::tokenizeInput(string input) {
    stringstream inputStringStream(input);
    return vector<string>(istream_iterator<string>(inputStringStream),
                          istream_iterator<string>());
}

Station* CommandHandler::createStation(string input) {
    const int STATION_NAME_INDEX = 1;
    const int COFFEE_PRICE_INDEX = 2;
    vector<string> tokenizedInput = tokenizeInput(input);
    
    Station* new_station = new Station(tokenizedInput[STATION_NAME_INDEX], stoi(tokenizedInput[COFFEE_PRICE_INDEX])) ;
    return new_station;
}

Train* CommandHandler::createTrain(string input) {
    const int STARTING_STATION_NAME = 1;
    const int OTHER_STATION_NAME = 2;
    const int TRAVEL_TIME = 3;
    const int COOLDOWN_TIME = 4;
    vector<string> tokenizedInput = tokenizeInput(input);
    Train* newTrain = new Train(stoi(tokenizedInput[TRAVEL_TIME]), stoi(tokenizedInput[COOLDOWN_TIME]),
        tokenizedInput[STARTING_STATION_NAME], tokenizedInput[OTHER_STATION_NAME]);
    return newTrain;

}

Passenger* CommandHandler::createPassenger(string input) {
    const int CHOCOLATE_ADDICTION_INDEX = 1;
    const int FIRST_STATION_INDEX = 2;
    vector<string> tokenizedInput = tokenizeInput(input);
    vector<string> stationList;
    for (auto it = tokenizedInput.begin() + FIRST_STATION_INDEX; it != tokenizedInput.end(); it++)
        stationList.push_back(*it);
    return new Passenger(stoi(tokenizedInput[CHOCOLATE_ADDICTION_INDEX]), stationList);
}

size_t CommandHandler::getTimeSteps(string input) {
    const int TIME_STEPS_INDEX = 1;

    return (size_t)stoi(tokenizeInput(input)[TIME_STEPS_INDEX]);
}

int CommandHandler::getObjectId(string input) {
    const int ID_INDEX = 1;

    return stoi(tokenizeInput(input)[ID_INDEX]);
}