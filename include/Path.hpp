#ifndef PATH_H
#define PATH_H

#include <vector>
#include <map>
#include <utility>
#include <string>

class Train;
class Station;
class Passenger;

class Path {

public:
    Path(Station* st1, Station* st2);
    void addTrain(Train* train);
    void addPassenger(Passenger* passenger, Station* station);
    void advanceTime();
    Station* getOtherEnd(Station* st);
    std::vector<Passenger*> extractPassengers(Station* st);
    std::pair<Station*, Station*> getStations();
    
private:
    void assignPassengers();
    void assignPassengersToStation(Station* st);

    int length;
    std::vector<Train*> trains;
    std::map<Station*, std::vector<Passenger*>> waitingPassengers;
};

#endif