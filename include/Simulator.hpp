#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include <string>
#include <map>

class Station;
class Path;
class Passenger;
class Train;

class Simulator {

public:
    Simulator();
    void addStation(Station* station);
    void addPassenger(Passenger* passenger);
    void addTrain(Train* train);
    void showPathInfo(int pathId);
    void advanceTime(int steps);
    void finish();
    std::string getTrainInfo(int id);
    std::string getPassengerInfo(int id);

private:
    void advanceTime();
    Path* getPath(std::string stName1, std::string stName);
    Station* getStation(std::string name);

    unsigned int nextTrainId;
    unsigned int nextPassengerId;
    unsigned int passengersCount;
    std::vector<Station*> stations;
    std::vector<Path*> paths;
    std::vector<Passenger*> finishedPassengers;
    std::map<int, Train*> trains;
    std::map<int, Passenger*> passengers;
};

#endif