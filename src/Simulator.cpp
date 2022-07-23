#include "Simulator.hpp"

#include <utility>
#include <iostream>

#include "Station.hpp"
#include "Path.hpp"
#include "Passenger.hpp"
#include "Train.hpp"

using namespace std;

constexpr int FIRST_ID = 1;

Simulator::Simulator()
    :nextTrainId(FIRST_ID), nextPassengerId(FIRST_ID) {}

void Simulator::addStation(Station* station) {
    stations.push_back(station);
}

void Simulator::addPassenger(Passenger* passenger) {
    passengersCount++;
    passenger->setId(nextPassengerId);
    passengers[nextPassengerId++] = passenger;
    for (Station* station: stations) {
        if (station->getName() == passenger->getNextDest()) {
            station->addPassenger(passenger);
            break;
        }
    }
}

void Simulator::addTrain(Train* train) {
    train->setId(nextTrainId);
    trains[nextTrainId++] = train;
    pair<string, string> trainStations = train->getStations();
    Path* path = getPath(trainStations.first, trainStations.second);
    if (path == nullptr) {
        Station* firstSt = getStation(trainStations.first);
        Station* secondSt = getStation(trainStations.second);
        path = new Path(firstSt, secondSt);
        firstSt->addPath(path);
        secondSt->addPath(path);
        paths.push_back(path);
    }
    path->addTrain(train);
}

void Simulator::advanceTime(int steps) {
    for (int i = 0; i < steps; i++)
        advanceTime();
}

void Simulator::advanceTime() {
    for (Path* path : paths)
        path->advanceTime();

    for (Station* station : stations) {
        station->advanceTime();
        for (Passenger* passenger : station->getFinishedPassengers())
            finishedPassengers.push_back(passenger);
    }
}

void Simulator::finish() {
    while (finishedPassengers.size() < passengersCount)
        advanceTime();
}

Path* Simulator::getPath(string stName1, string stName2) {
    for (Path* path: paths) {
        pair<Station*, Station*> stList = path->getStations();
        
        if ((stName1 == stList.first->getName() && stName2 == stList.second->getName()) || 
            (stName2 == stList.first->getName() && stName1 == stList.second->getName())) {
            return path;
        }
        
    }
    return nullptr;
}

Station* Simulator::getStation(string name) {
    for (Station* station: stations)
        if (station->getName() == name)
            return station;
    return nullptr;
}

string Simulator::getTrainInfo(int id) {
    return trains[id]->getInfo();
}

string Simulator::getPassengerInfo(int id) {
    return passengers[id]->getInfo();
}