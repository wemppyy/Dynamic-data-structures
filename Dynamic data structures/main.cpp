#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>

struct Passenger {
    int arrivalTime;
};

struct Minibus {
    int freeSeats;
    int arrivalTime;
};

int main() {
    int simulationTime = 120;
    int averagePassengerInterval = 2;
    int averageMinibusInterval = 10;
    int maxQueueSize = 10;
    int minFreeSeats = 1, maxFreeSeats = 15;
    bool isTerminalStop = false;

    std::queue<Passenger> stopQueue;
    int currentTime = 0;
    int nextPassengerTime = 0;
    int nextMinibusTime = 0;
    int totalWaitTime = 0;
    int totalPassengers = 0;
    int maxQueueReached = 0;

    std::srand(std::time(0));

    while (currentTime < simulationTime) {
        if (currentTime >= nextPassengerTime) {
            if (stopQueue.size() < maxQueueSize) {
                stopQueue.push({ currentTime });
                totalPassengers++;
            }
            nextPassengerTime = currentTime + std::rand() % (2 * averagePassengerInterval);
        }

        if (currentTime >= nextMinibusTime) {
            Minibus bus = { std::rand() % (maxFreeSeats - minFreeSeats + 1) + minFreeSeats, currentTime };

            while (!stopQueue.empty() && bus.freeSeats > 0) {
                Passenger passenger = stopQueue.front();
                stopQueue.pop();
                bus.freeSeats--;
                totalWaitTime += currentTime - passenger.arrivalTime;
            }

            nextMinibusTime = currentTime + std::rand() % (2 * averageMinibusInterval);
        }

        if (stopQueue.size() > maxQueueReached) {
            maxQueueReached = stopQueue.size();
        }

        currentTime++;
    }

    double averageWaitTime = (totalPassengers > 0) ? (double)totalWaitTime / totalPassengers : 0.0;

    std::cout << "Simulation results:\n";
    std::cout << "Total number of passengers: " << totalPassengers << "\n";
    std::cout << "Average waiting time per passenger: " << averageWaitTime << " minutes\n";
    std::cout << "Maximum queue size at the stop: " << maxQueueReached << "\n";

    return 0;
}