#include "Path.hpp"

#include "Train.hpp"
#include "Station.hpp"
#include "Passenger.hpp"

using namespace std;

Path::Path(Station* st1, Station* st2) {
    waitingPassengers = {
        {st1, {}},
        {st2, {}}
    };
}

void Path::addTrain(Train* train) {
    trains.push_back(train);
}

void Path::addPassenger(Passenger* passenger, Station* station) {
    waitingPassengers[station].push_back(passenger);
}

void Path::advanceTime() {
    assignPassengers();

    for (Train* train : trains)
        train->advanceTime();

    for (std::map<Station*,std::vector<Passenger*>>::iterator iter = waitingPassengers.begin();
        iter != waitingPassengers.end(); ++iter) {

        for (Passenger* passenger: iter->second) {
            passenger->advanceTime();
            passenger->buyChocolate(iter->first->getChocolatePrice());
        }
    }
}

Station* Path::getOtherEnd(Station* st) {
    for (std::map<Station*,std::vector<Passenger*>>::iterator iter = waitingPassengers.begin();
        iter != waitingPassengers.end(); ++iter) {

        if (iter->first != st)
            return iter->first;
    }
    return nullptr;
}

vector<Passenger*> Path::extractPassengers(Station* st) {
    vector<Passenger*> newPassengers;
    for (Train* train: trains) {
        if (train->hasArrivedRecently(st) && train->hasPassengers()) {
            vector<Passenger*> trainPassengers = train->dropPassengers();
            newPassengers.insert(newPassengers.end(), trainPassengers.begin(), trainPassengers.end());        
        }
    }

    for (Passenger* passenger: newPassengers)
        passenger->getOffTrain(st->getName());

    return newPassengers;
}

void Path::assignPassengersToStation(Station* st) {
    for (Train* train: trains) {
        if (train->isInStation(st)) {
            for (Passenger* passenger: waitingPassengers[st])
                train->addPassenger(passenger);
            waitingPassengers[st].clear();
            return;
        }
    }
}

void Path::assignPassengers() {
    for (std::map<Station*,std::vector<Passenger*>>::iterator iter = waitingPassengers.begin();
        iter != waitingPassengers.end(); ++iter) {

        assignPassengersToStation(iter->first);
    }
}

pair<Station*, Station*> Path::getStations() {
    auto it = waitingPassengers.begin();
    auto it2 = next(it);
    return make_pair(it->first, it2->first);
    
}