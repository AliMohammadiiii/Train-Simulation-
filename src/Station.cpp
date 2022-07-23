#include "Station.hpp"

#include "Passenger.hpp"
#include "Path.hpp"

using namespace std;

Station::Station(string _name, int _chocolatePrice)
    :name(_name), chocolatePrice(_chocolatePrice){}

void Station::addPassenger(Passenger* passenger) {
    movePassenger(passenger);
}

void Station::addPath(Path* path) {
    paths.push_back(path);
}

void Station::advanceTime() {
    for (Passenger* passenger : extractPassengers()) {

        if (passenger->isFinished()) {
            finishedPassengers.push_back(passenger);
            passenger->popDest();
        }
        else
            movePassenger(passenger);
    }

}

vector<Passenger*> Station::extractPassengers() {
    vector<Passenger*> newPassengers;
    for (Path* path: paths) {
        vector<Passenger*> pathPassengers = path->extractPassengers(this);
        newPassengers.insert(newPassengers.end(), pathPassengers.begin(), pathPassengers.end());
    }

    return newPassengers;
}

void Station::movePassenger(Passenger* passenger) {
    passenger->popDest();
    for (Path* path : paths) {
        if (path->getOtherEnd(this)->getName() == passenger->getNextDest()) {
            path->addPassenger(passenger, this);
        }
    }
}

vector<Passenger*> Station::getFinishedPassengers() {
    vector<Passenger*> toReturn(finishedPassengers);
    finishedPassengers.clear();
    return toReturn;
}

int Station::getChocolatePrice() {
    return chocolatePrice;
}

string Station::getName() {
    return name;
}