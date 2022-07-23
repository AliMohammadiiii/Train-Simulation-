#include "Train.hpp"

#include "Passenger.hpp"
#include "Station.hpp"

using namespace std;

Train::Train(int _travelTime, int _cooldown, string st1, string st2)
    :travelTime(_travelTime), cooldownTime(_cooldown), travellng(false), fromName(st1), toName(st2) {
        
        timeleft = cooldownTime;
    }

void Train::addPassenger(Passenger* passenger) {
    passenger->getOnTrain(id);
    passengers.push_back(passenger);
}

void Train::advanceTime() {
    timeleft--;
    if (timeleft <= 0) {
        if (travellng) {
            string tmp = toName;
            toName = fromName;
            fromName = tmp;
            timeleft = cooldownTime;
        } else {
            timeleft = travelTime;
        }
        travellng = !travellng;
    }

    for (Passenger* passenger: passengers)
        passenger->advanceTime();
}

bool Train::isInStation(Station* station) {
    return !travellng && station->getName() == fromName;
}

bool Train::hasPassengers() {
    return passengers.size() != 0;
}

bool Train::hasArrivedRecently(Station* station) {
    return isInStation(station) && timeleft == cooldownTime;
}

vector<Passenger*> Train::dropPassengers() {
    vector<Passenger*> toReturn(passengers);
    passengers.clear();
    return toReturn;
}

pair<string, string> Train::getStations() {
    return make_pair(fromName, toName);
}

string Train::getInfo() {
    string info = "status : ";
    if (travellng) 
        info += "moving\n";
    else
        info += "resting\n";
    info += "estimated remaining time : " + to_string(timeleft);
    info += "\nnext station : " + toName;
    info += "\npassengers count : " + to_string(passengers.size());
    return info;
}

void Train::setId(int _id) {
    id = _id;
}