#include "Passenger.hpp"

using namespace std;


Passenger::Passenger(int _chocolateAddiction, vector<string> stList)
    :chocolateAddiction(_chocolateAddiction), location(stList[0]), stationList(stList) {}

void Passenger::popDest() {
    stationList.erase(stationList.begin());
}

string Passenger::getNextDest() {
    return stationList[0];
}

bool Passenger::isFinished() {
    return stationList.size() == 1;
}

void Passenger::advanceTime() {
    timePassed++;
}

void Passenger::buyChocolate(int price) {
    totalSpent += price * chocolateAddiction;
}

void Passenger::setId(int _id) {
    id = _id;
}

string Passenger::getInfo() {
    string info = "status : ";
    if (isTravelling)
        info += "on train\n";
    else if (stationList.size() == 0)
        info += "arrived\n";
    else
        info += "in station\n";
    info += "spent : " + to_string(totalSpent) + "\n";
    info += "current ";
    info += isTravelling ? "train " : "station ";
    info += location;
    return info;
}

void Passenger::getOnTrain(int trainId) {
    isTravelling = true;
    location = to_string(trainId);
}
void Passenger::getOffTrain(string stationName) {
    isTravelling = false;
    location = stationName;
}