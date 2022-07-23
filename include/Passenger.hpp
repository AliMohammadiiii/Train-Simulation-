#ifndef PASSENGER_H
#define PASSENGER_H

#include <vector>
#include <string>

class Passenger {

public:
    Passenger(int _chocolateAddiction, std::vector<std::string> stList);
    std::string getNextDest();
    void popDest();
    void advanceTime();
    bool isFinished();
    void buyChocolate(int price);
    void setId(int _id);
    std::string getInfo();
    void getOnTrain(int trainId);
    void getOffTrain(std::string stationName);

private:
    int id;
    int timePassed;
    int chocolateAddiction;
    int totalSpent;
    bool isTravelling;
    std::string location;
    std::vector<std::string> stationList;

};

#endif