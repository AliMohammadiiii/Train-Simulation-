#ifndef STATION_H
#define STATION_H

#include <vector>
#include <string>

class Passenger;
class Path;

class Station {
public:
    Station(std::string _name, int _chocolatePrice);
    void addPassenger(Passenger* passenger);
    std::vector<Passenger*> getFinishedPassengers();
    void advanceTime();
    std::string getName();
    int getChocolatePrice();
    void addPath(Path* path);

private:
    void movePassenger(Passenger* passenger);
    std::vector<Passenger*> extractPassengers();

    std::string name;
    int chocolatePrice;
    std::vector<Path*> paths;
    std::vector<Passenger*> finishedPassengers;

};

#endif