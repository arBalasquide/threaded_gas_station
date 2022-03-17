#include <cstdint>
#include <ctime>
#include <iostream>
#include <thread>
#include <chrono>

#include "gas_station.h"
#include "car.h"
#include "safe_queue.h"

#define EXECUTION_TIME_S 30 // Program execution length in seconds

int main() {
    std::time_t boot_time_s = std::time(nullptr);
    uint32_t elapsed_time_s = 0;

    GasStation* station_instance = GasStation::get();
    SafeQueue<Car*> cars;

    for (auto i = 0; i < 10; i++) {
        cars.enqueue(new Car(station_instance, &cars, i));
    }

    while (elapsed_time_s < EXECUTION_TIME_S) {
        std::time_t current_time_s = std::time(nullptr);
        elapsed_time_s = difftime(current_time_s, boot_time_s);
    }

    // Close station and wait for remaining cars
    station_instance->close();
    while(station_instance->busy()){};

    while (!cars.empty()) {
        Car* car = cars.dequeue();

        std::cout << "Car #" << car->id() + 1 << "\tfillups: " << car->fillups() << "\n";
    }

    std::cout << "\n" << station_instance->str();

    return 0;
}