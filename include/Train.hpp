#ifndef TRAIN_H
#define TRAIN_H

#include <vector>
#include <utility>
#include <string>

class Passenger;
class Station;

class Train {
public:
    Train(int _travelTime, int _cooldown, std::string st1, std::string st2);
    void addPassenger(Passenger* passenger);
    void advanceTime();
    std::vector<Passenger*> dropPassengers();
    bool hasPassengers();
    bool isInStation(Station* station);
    bool hasArrivedRecently(Station* station);
    std::pair<std::string, std::string> getStations();
    std::string getInfo();
    void setId(int _id);

private:
    int id;
    int travelTime;
    int cooldownTime;
    int timeleft;
    bool travellng;
    std::string fromName;
    std::string toName;
    std::vector<Passenger*> passengers;
};

#endif